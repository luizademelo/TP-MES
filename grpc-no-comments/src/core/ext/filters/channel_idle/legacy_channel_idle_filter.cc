// Copyright 2022 gRPC authors.

#include "src/core/ext/filters/channel_idle/legacy_channel_idle_filter.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <optional>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/meta/type_traits.h"
#include "absl/random/random.h"
#include "absl/status/statusor.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/exec_ctx_wakeup_scheduler.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/per_cpu.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/sync.h"

namespace grpc_core {

using http2::Http2ErrorCode;

namespace {
constexpr Duration kDefaultIdleTimeout = Duration::Minutes(30);

const auto kDefaultMaxConnectionAge = Duration::Infinity();
const auto kDefaultMaxConnectionAgeGrace = Duration::Infinity();
const auto kDefaultMaxConnectionIdle = Duration::Infinity();
const auto kMaxConnectionAgeJitter = 0.1;

}

Duration GetClientIdleTimeout(const ChannelArgs& args) {
  return args.GetDurationFromIntMillis(GRPC_ARG_CLIENT_IDLE_TIMEOUT_MS)
      .value_or(kDefaultIdleTimeout);
}

struct LegacyMaxAgeFilter::Config {
  Duration max_connection_age;
  Duration max_connection_idle;
  Duration max_connection_age_grace;

  bool enable() const {
    return max_connection_age != Duration::Infinity() ||
           max_connection_idle != Duration::Infinity();
  }

  static Config FromChannelArgs(const ChannelArgs& args) {
    const Duration args_max_age =
        args.GetDurationFromIntMillis(GRPC_ARG_MAX_CONNECTION_AGE_MS)
            .value_or(kDefaultMaxConnectionAge);
    const Duration args_max_idle =
        args.GetDurationFromIntMillis(GRPC_ARG_MAX_CONNECTION_IDLE_MS)
            .value_or(kDefaultMaxConnectionIdle);
    const Duration args_max_age_grace =
        args.GetDurationFromIntMillis(GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS)
            .value_or(kDefaultMaxConnectionAgeGrace);

    struct BitGen {
      Mutex mu;
      absl::BitGen bit_gen ABSL_GUARDED_BY(mu);
      double MakeUniformDouble(double min, double max) {
        MutexLock lock(&mu);
        return absl::Uniform(bit_gen, min, max);
      }
    };
    const double multiplier = []() {
      SharedBitGen g;
      return absl::Uniform(g, 1.0 - kMaxConnectionAgeJitter,
                           1.0 + kMaxConnectionAgeJitter);
    }();

    return Config{args_max_age * multiplier, args_max_idle * multiplier,
                  args_max_age_grace};
  }
};

ABSL_INTERNAL_DISABLE_DEPRECATED_DECLARATION_WARNING
absl::StatusOr<std::unique_ptr<LegacyClientIdleFilter>>
LegacyClientIdleFilter::Create(const ChannelArgs& args,
                               ChannelFilter::Args filter_args) {
  return std::make_unique<LegacyClientIdleFilter>(filter_args.channel_stack(),
                                                  GetClientIdleTimeout(args));
}

absl::StatusOr<std::unique_ptr<LegacyMaxAgeFilter>> LegacyMaxAgeFilter::Create(
    const ChannelArgs& args, ChannelFilter::Args filter_args) {
  return std::make_unique<LegacyMaxAgeFilter>(filter_args.channel_stack(),
                                              Config::FromChannelArgs(args));
}
ABSL_INTERNAL_RESTORE_DEPRECATED_DECLARATION_WARNING

void LegacyMaxAgeFilter::Shutdown() {
  max_age_activity_.Reset();
  LegacyChannelIdleFilter::Shutdown();
}

void LegacyMaxAgeFilter::PostInit() {
  struct StartupClosure {
    RefCountedPtr<grpc_channel_stack> channel_stack;
    LegacyMaxAgeFilter* filter;
    grpc_closure closure;
  };
  auto run_startup = [](void* p, grpc_error_handle) {
    auto* startup = static_cast<StartupClosure*>(p);

    startup->filter->IncreaseCallCount();
    startup->filter->DecreaseCallCount();
    grpc_transport_op* op = grpc_make_transport_op(nullptr);
    op->start_connectivity_watch.reset(
        new ConnectivityWatcher(startup->filter));
    op->start_connectivity_watch_state = GRPC_CHANNEL_IDLE;
    grpc_channel_next_op(
        grpc_channel_stack_element(startup->channel_stack.get(), 0), op);
    delete startup;
  };
  auto* startup =
      new StartupClosure{this->channel_stack()->Ref(), this, grpc_closure{}};
  GRPC_CLOSURE_INIT(&startup->closure, run_startup, startup, nullptr);
  ExecCtx::Run(DEBUG_LOCATION, &startup->closure, absl::OkStatus());

  auto channel_stack = this->channel_stack()->Ref();

  if (max_connection_age_ != Duration::Infinity()) {
    auto arena = SimpleArenaAllocator(0)->MakeArena();
    arena->SetContext<grpc_event_engine::experimental::EventEngine>(
        channel_stack->EventEngine());
    max_age_activity_.Set(MakeActivity(
        TrySeq(

            Sleep(Timestamp::Now() + max_connection_age_),

            [this] {
              GRPC_CHANNEL_STACK_REF(this->channel_stack(),
                                     "max_age send_goaway");

              auto fn = [](void* arg, grpc_error_handle) {
                auto* channel_stack = static_cast<grpc_channel_stack*>(arg);
                grpc_transport_op* op = grpc_make_transport_op(nullptr);
                op->goaway_error = grpc_error_set_int(
                    GRPC_ERROR_CREATE("max_age"),
                    StatusIntProperty::kHttp2Error,
                    static_cast<intptr_t>(Http2ErrorCode::kNoError));
                grpc_channel_element* elem =
                    grpc_channel_stack_element(channel_stack, 0);
                elem->filter->start_transport_op(elem, op);
                GRPC_CHANNEL_STACK_UNREF(channel_stack, "max_age send_goaway");
              };
              ExecCtx::Run(
                  DEBUG_LOCATION,
                  GRPC_CLOSURE_CREATE(fn, this->channel_stack(), nullptr),
                  absl::OkStatus());
              return Immediate(absl::OkStatus());
            },

            [this] {
              return Sleep(Timestamp::Now() + max_connection_age_grace_);
            }),
        ExecCtxWakeupScheduler(),
        [channel_stack, this](absl::Status status) {

          if (status.ok()) CloseChannel("max connection age");
        },
        std::move(arena)));
  }
}

ArenaPromise<ServerMetadataHandle> LegacyChannelIdleFilter::MakeCallPromise(
    CallArgs call_args, NextPromiseFactory next_promise_factory) {
  using Decrementer =
      std::unique_ptr<LegacyChannelIdleFilter, CallCountDecreaser>;
  IncreaseCallCount();
  return ArenaPromise<ServerMetadataHandle>(
      [decrementer = Decrementer(this),
       next = next_promise_factory(std::move(call_args))]() mutable
          -> Poll<ServerMetadataHandle> { return next(); });
}

bool LegacyChannelIdleFilter::StartTransportOp(grpc_transport_op* op) {

  if (!op->disconnect_with_error.ok()) Shutdown();

  return false;
}

void LegacyChannelIdleFilter::Shutdown() {

  IncreaseCallCount();
  activity_.Reset();
}

void LegacyChannelIdleFilter::IncreaseCallCount() {
  idle_filter_state_->IncreaseCallCount();
}

void LegacyChannelIdleFilter::DecreaseCallCount() {
  if (idle_filter_state_->DecreaseCallCount()) {

    StartIdleTimer();
  }
}

void LegacyChannelIdleFilter::StartIdleTimer() {
  GRPC_TRACE_LOG(client_idle_filter, INFO)
      << "(client idle filter) timer has started";
  auto idle_filter_state = idle_filter_state_;

  auto channel_stack = channel_stack_->Ref();
  auto timeout = client_idle_timeout_;
  auto promise = Loop([timeout, idle_filter_state]() {
    return TrySeq(Sleep(Timestamp::Now() + timeout),
                  [idle_filter_state]() -> Poll<LoopCtl<absl::Status>> {
                    if (idle_filter_state->CheckTimer()) {
                      return Continue{};
                    } else {
                      return absl::OkStatus();
                    }
                  });
  });
  auto arena = SimpleArenaAllocator()->MakeArena();
  arena->SetContext<grpc_event_engine::experimental::EventEngine>(
      channel_stack_->EventEngine());
  activity_.Set(MakeActivity(
      std::move(promise), ExecCtxWakeupScheduler{},
      [channel_stack, this](absl::Status status) {
        if (status.ok()) CloseChannel("connection idle");
      },
      std::move(arena)));
}

void LegacyChannelIdleFilter::CloseChannel(absl::string_view reason) {
  auto* op = grpc_make_transport_op(nullptr);
  op->disconnect_with_error = grpc_error_set_int(
      GRPC_ERROR_CREATE(reason), StatusIntProperty::ChannelConnectivityState,
      GRPC_CHANNEL_IDLE);

  auto* elem = grpc_channel_stack_element(channel_stack_, 0);
  elem->filter->start_transport_op(elem, op);
}

const grpc_channel_filter LegacyClientIdleFilter::kFilter =
    MakePromiseBasedFilter<LegacyClientIdleFilter, FilterEndpoint::kClient>();
const grpc_channel_filter LegacyMaxAgeFilter::kFilter =
    MakePromiseBasedFilter<LegacyMaxAgeFilter, FilterEndpoint::kServer>();

void RegisterLegacyChannelIdleFilters(CoreConfiguration::Builder* builder) {
  builder->channel_init()
      ->RegisterV2Filter<LegacyClientIdleFilter>(GRPC_CLIENT_CHANNEL)
      .ExcludeFromMinimalStack()
      .If([](const ChannelArgs& channel_args) {
        return GetClientIdleTimeout(channel_args) != Duration::Infinity();
      });
  builder->channel_init()
      ->RegisterV2Filter<LegacyMaxAgeFilter>(GRPC_SERVER_CHANNEL)
      .ExcludeFromMinimalStack()
      .If([](const ChannelArgs& channel_args) {
        return LegacyMaxAgeFilter::Config::FromChannelArgs(channel_args)
            .enable();
      });
}

LegacyMaxAgeFilter::LegacyMaxAgeFilter(grpc_channel_stack* channel_stack,
                                       const Config& max_age_config)
    : LegacyChannelIdleFilter(channel_stack,
                              max_age_config.max_connection_idle),
      max_connection_age_(max_age_config.max_connection_age),
      max_connection_age_grace_(max_age_config.max_connection_age_grace) {}

}
