
// Copyright 2015 gRPC authors.

#include "src/core/lib/surface/legacy_channel.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/channelz/channelz.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/channel_stack_builder_impl.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/channel_init.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/lib/surface/init_internally.h"
#include "src/core/lib/surface/lame_client.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/crash.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {

absl::StatusOr<RefCountedPtr<Channel>> LegacyChannel::Create(
    std::string target, ChannelArgs args,
    grpc_channel_stack_type channel_stack_type) {
  if (grpc_channel_stack_type_is_client(channel_stack_type)) {
    auto channel_args_mutator =
        grpc_channel_args_get_client_channel_creation_mutator();
    if (channel_args_mutator != nullptr) {
      args = channel_args_mutator(target.c_str(), args, channel_stack_type);
    }
  }
  std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
      stats_plugin_group;
  if (channel_stack_type == GRPC_SERVER_CHANNEL) {
    stats_plugin_group =
        GlobalStatsPluginRegistry::GetStatsPluginsForServer(args);

    auto* stats_plugin_list = args.GetPointer<
        std::shared_ptr<std::vector<std::shared_ptr<StatsPlugin>>>>(
        GRPC_ARG_EXPERIMENTAL_STATS_PLUGINS);
    if (stats_plugin_list != nullptr) {
      for (const auto& plugin : **stats_plugin_list) {
        stats_plugin_group->AddStatsPlugin(plugin,
                                           plugin->GetServerScopeConfig(args));
      }
    }
  } else {
    std::string authority = args.GetOwnedString(GRPC_ARG_DEFAULT_AUTHORITY)
                                .value_or(CoreConfiguration::Get()
                                              .resolver_registry()
                                              .GetDefaultAuthority(target));
    grpc_event_engine::experimental::ChannelArgsEndpointConfig endpoint_config(
        args);
    experimental::StatsPluginChannelScope scope(target, authority,
                                                endpoint_config);
    stats_plugin_group =
        GlobalStatsPluginRegistry::GetStatsPluginsForChannel(scope);

    auto* stats_plugin_list = args.GetPointer<
        std::shared_ptr<std::vector<std::shared_ptr<StatsPlugin>>>>(
        GRPC_ARG_EXPERIMENTAL_STATS_PLUGINS);
    if (stats_plugin_list != nullptr) {
      for (const auto& plugin : **stats_plugin_list) {
        stats_plugin_group->AddStatsPlugin(
            plugin, plugin->GetChannelScopeConfig(scope));
      }
    }
  }
  args = args.SetObject(stats_plugin_group);
  ChannelStackBuilderImpl builder(
      grpc_channel_stack_type_string(channel_stack_type), channel_stack_type,
      args);
  builder.SetTarget(target.c_str());
  if (!CoreConfiguration::Get().channel_init().CreateStack(&builder)) {
    return nullptr;
  }

  if (builder.channel_stack_type() == GRPC_SERVER_CHANNEL) {
    global_stats().IncrementServerChannelsCreated();
  }
  absl::StatusOr<RefCountedPtr<grpc_channel_stack>> r = builder.Build();
  if (!r.ok()) {
    auto status = r.status();
    LOG(ERROR) << "channel stack builder failed: " << status;
    return status;
  }
  *(*r)->stats_plugin_group = std::move(stats_plugin_group);
  return MakeRefCounted<LegacyChannel>(
      grpc_channel_stack_type_is_client(builder.channel_stack_type()),
      std::move(target), args, std::move(*r));
}

LegacyChannel::LegacyChannel(bool is_client, std::string target,
                             const ChannelArgs& channel_args,
                             RefCountedPtr<grpc_channel_stack> channel_stack)
    : Channel(std::move(target), channel_args),
      is_client_(is_client),
      channel_stack_(std::move(channel_stack)) {

  InitInternally();
  RefCountedPtr<channelz::ChannelNode> node;
  if (channelz_node() != nullptr) {
    node = channelz_node()->RefAsSubclass<channelz::ChannelNode>();
  }
  *channel_stack_->on_destroy = [node = std::move(node)]() {
    if (node != nullptr) {
      node->AddTraceEvent(channelz::ChannelTrace::Severity::Info,
                          grpc_slice_from_static_string("Channel destroyed"));
    }
    ShutdownInternally();
  };
}

void LegacyChannel::Orphaned() {
  grpc_transport_op* op = grpc_make_transport_op(nullptr);
  op->disconnect_with_error = GRPC_ERROR_CREATE("Channel Destroyed");
  grpc_channel_element* elem =
      grpc_channel_stack_element(channel_stack_.get(), 0);
  elem->filter->start_transport_op(elem, op);
}

bool LegacyChannel::IsLame() const {
  grpc_channel_element* elem =
      grpc_channel_stack_last_element(channel_stack_.get());
  return elem->filter == &LameClientFilter::kFilter;
}

grpc_call* LegacyChannel::CreateCall(grpc_call* parent_call,
                                     uint32_t propagation_mask,
                                     grpc_completion_queue* cq,
                                     grpc_pollset_set* pollset_set_alternative,
                                     Slice path, std::optional<Slice> authority,
                                     Timestamp deadline,
                                     bool registered_method) {
  CHECK(is_client_);
  CHECK(!(cq != nullptr && pollset_set_alternative != nullptr));
  grpc_call_create_args args;
  args.channel = RefAsSubclass<LegacyChannel>();
  args.server = nullptr;
  args.parent = parent_call;
  args.propagation_mask = propagation_mask;
  args.cq = cq;
  args.pollset_set_alternative = pollset_set_alternative;
  args.server_transport_data = nullptr;
  args.path = std::move(path);
  args.authority = std::move(authority);
  args.send_deadline = deadline;
  args.registered_method = registered_method;
  grpc_call* call;
  GRPC_LOG_IF_ERROR("call_create", grpc_call_create(&args, &call));
  return call;
}

grpc_connectivity_state LegacyChannel::CheckConnectivityState(
    bool try_to_connect) {

  ClientChannelFilter* client_channel = GetClientChannelFilter();
  if (GPR_UNLIKELY(client_channel == nullptr)) {
    if (IsLame()) return GRPC_CHANNEL_TRANSIENT_FAILURE;
    LOG(ERROR) << "grpc_channel_check_connectivity_state called on something "
                  "that is not a client channel";
    return GRPC_CHANNEL_SHUTDOWN;
  }
  return client_channel->CheckConnectivityState(try_to_connect);
}

bool LegacyChannel::SupportsConnectivityWatcher() const {
  return GetClientChannelFilter() != nullptr;
}

class LegacyChannel::StateWatcher final : public DualRefCounted<StateWatcher> {
 public:
  StateWatcher(WeakRefCountedPtr<LegacyChannel> channel,
               grpc_completion_queue* cq, void* tag,
               grpc_connectivity_state last_observed_state, Timestamp deadline)
      : channel_(std::move(channel)),
        cq_(cq),
        tag_(tag),
        state_(last_observed_state) {
    CHECK(grpc_cq_begin_op(cq, tag));
    GRPC_CLOSURE_INIT(&on_complete_, WatchComplete, this, nullptr);
    ClientChannelFilter* client_channel = channel_->GetClientChannelFilter();
    if (client_channel == nullptr) {

      if (channel_->IsLame()) {

        StartTimer(deadline);

        Unref();
        return;
      }
      Crash(
          "grpc_channel_watch_connectivity_state called on something that is "
          "not a client channel");
    }

    auto* watcher_timer_init_state = new WatcherTimerInitState(this, deadline);
    client_channel->AddExternalConnectivityWatcher(
        grpc_polling_entity_create_from_pollset(grpc_cq_pollset(cq)), &state_,
        &on_complete_, watcher_timer_init_state->closure());
  }

 private:

  class WatcherTimerInitState final {
   public:
    WatcherTimerInitState(StateWatcher* state_watcher, Timestamp deadline)
        : state_watcher_(state_watcher), deadline_(deadline) {
      GRPC_CLOSURE_INIT(&closure_, WatcherTimerInit, this, nullptr);
    }

    grpc_closure* closure() { return &closure_; }

   private:
    static void WatcherTimerInit(void* arg, grpc_error_handle ) {
      auto* self = static_cast<WatcherTimerInitState*>(arg);
      self->state_watcher_->StartTimer(self->deadline_);
      delete self;
    }

    StateWatcher* state_watcher_;
    Timestamp deadline_;
    grpc_closure closure_;
  };

  void StartTimer(Timestamp deadline) {
    const Duration timeout = deadline - Timestamp::Now();
    MutexLock lock(&mu_);
    timer_handle_ =
        channel_->event_engine()->RunAfter(timeout, [self = Ref()]() mutable {
          ExecCtx exec_ctx;
          self->TimeoutComplete();

          self.reset();
        });
  }

  void TimeoutComplete() {
    timer_fired_ = true;

    ClientChannelFilter* client_channel = channel_->GetClientChannelFilter();
    if (client_channel != nullptr) {
      client_channel->CancelExternalConnectivityWatcher(&on_complete_);
    }
  }

  static void WatchComplete(void* arg, grpc_error_handle error) {
    RefCountedPtr<StateWatcher> self(static_cast<StateWatcher*>(arg));
    if (GRPC_TRACE_FLAG_ENABLED(op_failure)) {
      GRPC_LOG_IF_ERROR("watch_completion_error", error);
    }
    MutexLock lock(&self->mu_);
    if (self->timer_handle_.has_value()) {
      self->channel_->event_engine()->Cancel(*self->timer_handle_);
    }
  }

  void Orphaned() override {
    WeakRef().release();
    grpc_error_handle error =
        timer_fired_
            ? GRPC_ERROR_CREATE("Timed out waiting for connection state change")
            : absl::OkStatus();
    grpc_cq_end_op(cq_, tag_, error, FinishedCompletion, this,
                   &completion_storage_);
  }

  static void FinishedCompletion(void* arg, grpc_cq_completion* ) {
    auto* self = static_cast<StateWatcher*>(arg);
    self->WeakUnref();
  }

  WeakRefCountedPtr<LegacyChannel> channel_;
  grpc_completion_queue* cq_;
  void* tag_;

  grpc_connectivity_state state_;
  grpc_cq_completion completion_storage_;
  grpc_closure on_complete_;

  Mutex mu_;
  std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
      timer_handle_ ABSL_GUARDED_BY(mu_);
  bool timer_fired_ = false;
};

void LegacyChannel::WatchConnectivityState(
    grpc_connectivity_state last_observed_state, Timestamp deadline,
    grpc_completion_queue* cq, void* tag) {
  new StateWatcher(WeakRefAsSubclass<LegacyChannel>(), cq, tag,
                   last_observed_state, deadline);
}

void LegacyChannel::AddConnectivityWatcher(
    grpc_connectivity_state initial_state,
    OrphanablePtr<AsyncConnectivityStateWatcherInterface> watcher) {
  auto* client_channel = GetClientChannelFilter();
  CHECK_NE(client_channel, nullptr);
  client_channel->AddConnectivityWatcher(initial_state, std::move(watcher));
}

void LegacyChannel::RemoveConnectivityWatcher(
    AsyncConnectivityStateWatcherInterface* watcher) {
  auto* client_channel = GetClientChannelFilter();
  CHECK_NE(client_channel, nullptr);
  client_channel->RemoveConnectivityWatcher(watcher);
}

void LegacyChannel::GetInfo(const grpc_channel_info* channel_info) {
  grpc_channel_element* elem =
      grpc_channel_stack_element(channel_stack_.get(), 0);
  elem->filter->get_channel_info(elem, channel_info);
}

void LegacyChannel::ResetConnectionBackoff() {
  grpc_transport_op* op = grpc_make_transport_op(nullptr);
  op->reset_connect_backoff = true;
  grpc_channel_element* elem =
      grpc_channel_stack_element(channel_stack_.get(), 0);
  elem->filter->start_transport_op(elem, op);
}

namespace {

struct ping_result {
  grpc_closure closure;
  void* tag;
  grpc_completion_queue* cq;
  grpc_cq_completion completion_storage;
};
void ping_destroy(void* arg, grpc_cq_completion* ) { gpr_free(arg); }

void ping_done(void* arg, grpc_error_handle error) {
  ping_result* pr = static_cast<ping_result*>(arg);
  grpc_cq_end_op(pr->cq, pr->tag, error, ping_destroy, pr,
                 &pr->completion_storage);
}

}

void LegacyChannel::Ping(grpc_completion_queue* cq, void* tag) {
  ping_result* pr = static_cast<ping_result*>(gpr_malloc(sizeof(*pr)));
  pr->tag = tag;
  pr->cq = cq;
  GRPC_CLOSURE_INIT(&pr->closure, ping_done, pr, grpc_schedule_on_exec_ctx);
  grpc_transport_op* op = grpc_make_transport_op(nullptr);
  op->send_ping.on_ack = &pr->closure;
  op->bind_pollset = grpc_cq_pollset(cq);
  CHECK(grpc_cq_begin_op(cq, tag));
  grpc_channel_element* top_elem =
      grpc_channel_stack_element(channel_stack_.get(), 0);
  top_elem->filter->start_transport_op(top_elem, op);
}

ClientChannelFilter* LegacyChannel::GetClientChannelFilter() const {
  grpc_channel_element* elem =
      grpc_channel_stack_last_element(channel_stack_.get());
  if (elem->filter != &ClientChannelFilter::kFilter) {
    return nullptr;
  }
  return static_cast<ClientChannelFilter*>(elem->channel_data);
}

}
