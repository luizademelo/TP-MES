
// Copyright 2015 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <inttypes.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/notification.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"
#include "src/core/util/work_serializer.h"
#include "test/core/test_util/test_config.h"

using ::grpc_event_engine::experimental::GetDefaultEventEngine;

constexpr int kMinResolutionPeriodMs = 1000;

static std::shared_ptr<grpc_core::WorkSerializer>* g_work_serializer;

static grpc_ares_request* (*g_default_dns_lookup_ares)(
    const char* dns_server, const char* name, const char* default_port,
    grpc_pollset_set* interested_parties, grpc_closure* on_done,
    std::unique_ptr<grpc_core::EndpointAddressesList>* addresses,
    int query_timeout_ms);

static int g_resolution_count;

static struct iomgr_args {
  gpr_event ev;
  gpr_atm done_atm;
  gpr_mu* mu;
  grpc_pollset* pollset;
  grpc_pollset_set* pollset_set;
} g_iomgr_args;

namespace {

class TestDNSResolver : public grpc_core::DNSResolver {
 public:
  explicit TestDNSResolver(
      std::shared_ptr<grpc_core::DNSResolver> default_resolver)
      : default_resolver_(std::move(default_resolver)),
        engine_(GetDefaultEventEngine()) {}

  TaskHandle LookupHostname(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_resolved,
      absl::string_view name, absl::string_view default_port,
      grpc_core::Duration timeout, grpc_pollset_set* interested_parties,
      absl::string_view name_server) override {
    auto result = default_resolver_->LookupHostname(
        std::move(on_resolved), name, default_port, timeout, interested_parties,
        name_server);
    ++g_resolution_count;
    static grpc_core::Timestamp last_resolution_time =
        grpc_core::Timestamp::ProcessEpoch();
    if (last_resolution_time == grpc_core::Timestamp::ProcessEpoch()) {
      last_resolution_time = grpc_core::Timestamp::FromTimespecRoundUp(
          gpr_now(GPR_CLOCK_MONOTONIC));
    } else {
      auto now = grpc_core::Timestamp::FromTimespecRoundUp(
          gpr_now(GPR_CLOCK_MONOTONIC));
      EXPECT_GE(now - last_resolution_time,
                grpc_core::Duration::Milliseconds(kMinResolutionPeriodMs));
      last_resolution_time = now;
    }

    grpc_core::ExecCtx::Get()->InvalidateNow();
    return result;
  }

  absl::StatusOr<std::vector<grpc_resolved_address>> LookupHostnameBlocking(
      absl::string_view name, absl::string_view default_port) override {
    return default_resolver_->LookupHostnameBlocking(name, default_port);
  }

  TaskHandle LookupSRV(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_resolved,
      absl::string_view , grpc_core::Duration ,
      grpc_pollset_set* ,
      absl::string_view ) override {
    engine_->Run([on_resolved] {
      grpc_core::ExecCtx exec_ctx;
      on_resolved(absl::UnimplementedError(
          "The Testing DNS resolver does not support looking up SRV records"));
    });
    return {-1, -1};
  };

  TaskHandle LookupTXT(
      std::function<void(absl::StatusOr<std::string>)> on_resolved,
      absl::string_view , grpc_core::Duration ,
      grpc_pollset_set* ,
      absl::string_view ) override {

    engine_->Run([on_resolved] {
      grpc_core::ExecCtx exec_ctx;
      on_resolved(absl::UnimplementedError(
          "The Testing DNS resolver does not support looking up TXT records"));
    });
    return {-1, -1};
  };

  bool Cancel(TaskHandle ) override { return false; }

 private:
  std::shared_ptr<grpc_core::DNSResolver> default_resolver_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine_;
};

}

static grpc_ares_request* test_dns_lookup_ares(
    const char* dns_server, const char* name, const char* default_port,
    grpc_pollset_set* , grpc_closure* on_done,
    std::unique_ptr<grpc_core::EndpointAddressesList>* addresses,
    int query_timeout_ms) {

  grpc_ares_request* result = g_default_dns_lookup_ares(
      dns_server, name, default_port, g_iomgr_args.pollset_set, on_done,
      addresses, query_timeout_ms);
  ++g_resolution_count;
  static auto last_resolution_time = grpc_core::Timestamp::ProcessEpoch();
  auto now =
      grpc_core::Timestamp::FromTimespecRoundUp(gpr_now(GPR_CLOCK_MONOTONIC));
  VLOG(2) << "last_resolution_time:"
          << last_resolution_time.milliseconds_after_process_epoch()
          << " now:" << now.milliseconds_after_process_epoch()
          << " min_time_between:" << kMinResolutionPeriodMs;
  if (last_resolution_time != grpc_core::Timestamp::ProcessEpoch()) {
    EXPECT_GE(now - last_resolution_time,
              grpc_core::Duration::Milliseconds(kMinResolutionPeriodMs));
  }
  last_resolution_time = now;

  grpc_core::ExecCtx::Get()->InvalidateNow();
  return result;
}

static gpr_timespec test_deadline(void) {
  return grpc_timeout_seconds_to_deadline(100);
}

static void do_nothing(void* , grpc_error_handle ) {}

static void iomgr_args_init(iomgr_args* args) {
  gpr_event_init(&args->ev);
  args->pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(args->pollset, &args->mu);
  args->pollset_set = grpc_pollset_set_create();
  grpc_pollset_set_add_pollset(args->pollset_set, args->pollset);
  gpr_atm_rel_store(&args->done_atm, 0);
}

static void iomgr_args_finish(iomgr_args* args) {
  ASSERT_TRUE(gpr_event_wait(&args->ev, test_deadline()));
  grpc_pollset_set_del_pollset(args->pollset_set, args->pollset);
  grpc_pollset_set_destroy(args->pollset_set);
  grpc_closure do_nothing_cb;
  GRPC_CLOSURE_INIT(&do_nothing_cb, do_nothing, nullptr,
                    grpc_schedule_on_exec_ctx);
  gpr_mu_lock(args->mu);
  grpc_pollset_shutdown(args->pollset, &do_nothing_cb);
  gpr_mu_unlock(args->mu);

  grpc_core::ExecCtx::Get()->Flush();
  grpc_pollset_destroy(args->pollset);
  gpr_free(args->pollset);
}

static grpc_core::Timestamp n_sec_deadline(int seconds) {
  return grpc_core::Timestamp::FromTimespecRoundUp(
      grpc_timeout_seconds_to_deadline(seconds));
}

static void poll_pollset_until_request_done(iomgr_args* args) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::Timestamp deadline = n_sec_deadline(10);
  while (true) {
    bool done = gpr_atm_acq_load(&args->done_atm) != 0;
    if (done) {
      break;
    }
    grpc_core::Duration time_left = deadline - grpc_core::Timestamp::Now();
    VLOG(2) << "done=" << done << ", time_left=" << time_left.millis();
    ASSERT_GE(time_left, grpc_core::Duration::Zero());
    grpc_pollset_worker* worker = nullptr;
    gpr_mu_lock(args->mu);
    GRPC_LOG_IF_ERROR("pollset_work", grpc_pollset_work(args->pollset, &worker,
                                                        n_sec_deadline(1)));
    gpr_mu_unlock(args->mu);
    grpc_core::ExecCtx::Get()->Flush();
  }
  gpr_event_set(&args->ev, reinterpret_cast<void*>(1));
}

struct OnResolutionCallbackArg;

class ResultHandler : public grpc_core::Resolver::ResultHandler {
 public:
  using ResultCallback = void (*)(OnResolutionCallbackArg* state);

  void SetCallback(ResultCallback result_cb, OnResolutionCallbackArg* state) {
    ASSERT_EQ(result_cb_, nullptr);
    result_cb_ = result_cb;
    ASSERT_EQ(state_, nullptr);
    state_ = state;
  }

  void ReportResult(grpc_core::Resolver::Result result) override {
    if (result.result_health_callback != nullptr) {
      result.result_health_callback(absl::OkStatus());
    }
    ASSERT_NE(result_cb_, nullptr);
    ASSERT_NE(state_, nullptr);
    ResultCallback cb = result_cb_;
    OnResolutionCallbackArg* state = state_;
    result_cb_ = nullptr;
    state_ = nullptr;
    cb(state);
  }

 private:
  ResultCallback result_cb_ = nullptr;
  OnResolutionCallbackArg* state_ = nullptr;
};

struct OnResolutionCallbackArg {
  const char* uri_str = nullptr;
  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver;
  ResultHandler* result_handler;
};

static grpc_core::NoDestruct<grpc_core::Notification> g_all_callbacks_invoked;

static void on_fourth_resolution(OnResolutionCallbackArg* cb_arg) {
  LOG(INFO) << "4th: g_resolution_count: " << g_resolution_count;
  ASSERT_EQ(g_resolution_count, 4);
  cb_arg->resolver.reset();
  gpr_atm_rel_store(&g_iomgr_args.done_atm, 1);
  gpr_mu_lock(g_iomgr_args.mu);
  GRPC_LOG_IF_ERROR("pollset_kick",
                    grpc_pollset_kick(g_iomgr_args.pollset, nullptr));
  gpr_mu_unlock(g_iomgr_args.mu);
  delete cb_arg;
  g_all_callbacks_invoked->Notify();
}

static void on_third_resolution(OnResolutionCallbackArg* cb_arg) {
  LOG(INFO) << "3rd: g_resolution_count: " << g_resolution_count;
  ASSERT_EQ(g_resolution_count, 3);
  cb_arg->result_handler->SetCallback(on_fourth_resolution, cb_arg);
  cb_arg->resolver->RequestReresolutionLocked();
  gpr_mu_lock(g_iomgr_args.mu);
  GRPC_LOG_IF_ERROR("pollset_kick",
                    grpc_pollset_kick(g_iomgr_args.pollset, nullptr));
  gpr_mu_unlock(g_iomgr_args.mu);
}

static void on_second_resolution(OnResolutionCallbackArg* cb_arg) {
  LOG(INFO) << "2nd: g_resolution_count: " << g_resolution_count;

  ASSERT_EQ(g_resolution_count, 2);
  cb_arg->result_handler->SetCallback(on_third_resolution, cb_arg);
  cb_arg->resolver->RequestReresolutionLocked();
  gpr_mu_lock(g_iomgr_args.mu);
  GRPC_LOG_IF_ERROR("pollset_kick",
                    grpc_pollset_kick(g_iomgr_args.pollset, nullptr));
  gpr_mu_unlock(g_iomgr_args.mu);
}

static void on_first_resolution(OnResolutionCallbackArg* cb_arg) {
  LOG(INFO) << "1st: g_resolution_count: " << g_resolution_count;

  ASSERT_EQ(g_resolution_count, 1);
  cb_arg->result_handler->SetCallback(on_second_resolution, cb_arg);
  cb_arg->resolver->RequestReresolutionLocked();
  gpr_mu_lock(g_iomgr_args.mu);
  GRPC_LOG_IF_ERROR("pollset_kick",
                    grpc_pollset_kick(g_iomgr_args.pollset, nullptr));
  gpr_mu_unlock(g_iomgr_args.mu);
}

static void start_test_under_work_serializer(void* arg) {
  OnResolutionCallbackArg* res_cb_arg =
      static_cast<OnResolutionCallbackArg*>(arg);
  res_cb_arg->result_handler = new ResultHandler();
  grpc_core::ResolverFactory* factory = grpc_core::CoreConfiguration::Get()
                                            .resolver_registry()
                                            .LookupResolverFactory("dns");
  absl::StatusOr<grpc_core::URI> uri =
      grpc_core::URI::Parse(res_cb_arg->uri_str);
  VLOG(2) << "test: '" << res_cb_arg->uri_str << "' should be valid for '"
          << factory->scheme() << "'";
  if (!uri.ok()) {
    LOG(ERROR) << uri.status();
    ASSERT_TRUE(uri.ok());
  }
  grpc_core::ResolverArgs args;
  args.uri = std::move(*uri);
  args.work_serializer = *g_work_serializer;
  args.result_handler = std::unique_ptr<grpc_core::Resolver::ResultHandler>(
      res_cb_arg->result_handler);
  g_resolution_count = 0;

  grpc_arg cooldown_arg = grpc_channel_arg_integer_create(
      const_cast<char*>(GRPC_ARG_DNS_MIN_TIME_BETWEEN_RESOLUTIONS_MS),
      kMinResolutionPeriodMs);
  grpc_channel_args cooldown_args = {1, &cooldown_arg};
  args.args = grpc_core::ChannelArgs::FromC(&cooldown_args);
  args.args = args.args.SetObject(GetDefaultEventEngine());
  res_cb_arg->resolver = factory->CreateResolver(std::move(args));
  ASSERT_NE(res_cb_arg->resolver, nullptr);

  res_cb_arg->result_handler->SetCallback(on_first_resolution, res_cb_arg);
  res_cb_arg->resolver->StartLocked();
}

static void test_cooldown() {
  grpc_core::ExecCtx exec_ctx;
  iomgr_args_init(&g_iomgr_args);
  OnResolutionCallbackArg* res_cb_arg = new OnResolutionCallbackArg();
  res_cb_arg->uri_str = "dns:127.0.0.1";

  (*g_work_serializer)->Run([res_cb_arg]() {
    start_test_under_work_serializer(res_cb_arg);
  });
  grpc_core::ExecCtx::Get()->Flush();
  poll_pollset_until_request_done(&g_iomgr_args);
  iomgr_args_finish(&g_iomgr_args);
}

TEST(DnsResolverCooldownTest, MainTest) {

  if (grpc_core::IsEventEngineDnsEnabled()) {
    GTEST_SKIP() << "Not with event engine dns";
  }
  grpc_init();

  auto work_serializer = std::make_shared<grpc_core::WorkSerializer>(
      grpc_event_engine::experimental::GetDefaultEventEngine());
  g_work_serializer = &work_serializer;

  g_default_dns_lookup_ares = grpc_dns_lookup_hostname_ares;
  grpc_dns_lookup_hostname_ares = test_dns_lookup_ares;
  grpc_core::ResetDNSResolver(
      std::make_unique<TestDNSResolver>(grpc_core::GetDNSResolver()));

  test_cooldown();

  grpc_shutdown();
  g_all_callbacks_invoked->WaitForNotification();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
