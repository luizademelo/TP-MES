
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <stdio.h>
#include <string.h>

#include <string>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "src/core/config/config_vars.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/ares_resolver.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/crash.h"
#include "src/core/util/notification.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/string.h"
#include "src/core/util/thd.h"
#include "src/core/util/work_serializer.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/cmdline.h"
#include "test/core/test_util/fake_udp_and_tcp_server.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/socket_use_after_close_detector.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/test_config.h"

#ifdef GPR_WINDOWS
#include "src/core/lib/iomgr/sockaddr_windows.h"
#include "src/core/lib/iomgr/socket_windows.h"
#define BAD_SOCKET_RETURN_VAL INVALID_SOCKET
#else
#include "src/core/lib/iomgr/sockaddr_posix.h"
#define BAD_SOCKET_RETURN_VAL (-1)
#endif

namespace {

using ::grpc_event_engine::experimental::GetDefaultEventEngine;

void* Tag(intptr_t t) { return reinterpret_cast<void*>(t); }

gpr_timespec FiveSecondsFromNow(void) {
  return grpc_timeout_seconds_to_deadline(5);
}

void DrainCq(grpc_completion_queue* cq) {
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(cq, FiveSecondsFromNow(), nullptr);
  } while (ev.type != GRPC_QUEUE_SHUTDOWN);
}

void EndTest(grpc_channel* client, grpc_completion_queue* cq) {
  grpc_channel_destroy(client);
  grpc_completion_queue_shutdown(cq);
  DrainCq(cq);
  grpc_completion_queue_destroy(cq);
}

struct ArgsStruct {
  gpr_atm done_atm;
  gpr_mu* mu;
  grpc_pollset* pollset;
  grpc_pollset_set* pollset_set;
  std::shared_ptr<grpc_core::WorkSerializer> lock;
  grpc_channel_args* channel_args;
};

void ArgsInit(ArgsStruct* args) {
  args->pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(args->pollset, &args->mu);
  args->pollset_set = grpc_pollset_set_create();
  grpc_pollset_set_add_pollset(args->pollset_set, args->pollset);
  args->lock = std::make_shared<grpc_core::WorkSerializer>(
      grpc_event_engine::experimental::GetDefaultEventEngine());
  gpr_atm_rel_store(&args->done_atm, 0);
  args->channel_args = nullptr;
}

void DoNothing(void* , grpc_error_handle ) {}

void ArgsFinish(ArgsStruct* args) {
  grpc_core::Notification notification;
  args->lock->Run([&notification]() { notification.Notify(); });
  args->lock.reset();
  notification.WaitForNotification();
  grpc_pollset_set_del_pollset(args->pollset_set, args->pollset);
  grpc_pollset_set_destroy(args->pollset_set);
  grpc_closure DoNothing_cb;
  GRPC_CLOSURE_INIT(&DoNothing_cb, DoNothing, nullptr,
                    grpc_schedule_on_exec_ctx);
  grpc_pollset_shutdown(args->pollset, &DoNothing_cb);

  grpc_channel_args_destroy(args->channel_args);
  grpc_core::ExecCtx::Get()->Flush();
  grpc_pollset_destroy(args->pollset);
  gpr_free(args->pollset);
}

void PollPollsetUntilRequestDone(ArgsStruct* args) {
  while (true) {
    bool done = gpr_atm_acq_load(&args->done_atm) != 0;
    if (done) {
      break;
    }
    grpc_pollset_worker* worker = nullptr;
    grpc_core::ExecCtx exec_ctx;
    gpr_mu_lock(args->mu);
    GRPC_LOG_IF_ERROR("pollset_work",
                      grpc_pollset_work(args->pollset, &worker,
                                        grpc_core::Timestamp::InfFuture()));
    gpr_mu_unlock(args->mu);
  }
}

class AssertFailureResultHandler : public grpc_core::Resolver::ResultHandler {
 public:
  explicit AssertFailureResultHandler(ArgsStruct* args) : args_(args) {}

  ~AssertFailureResultHandler() override {
    gpr_atm_rel_store(&args_->done_atm, 1);
    gpr_mu_lock(args_->mu);
    GRPC_LOG_IF_ERROR("pollset_kick",
                      grpc_pollset_kick(args_->pollset, nullptr));
    gpr_mu_unlock(args_->mu);
  }

  void ReportResult(grpc_core::Resolver::Result ) override {
    grpc_core::Crash("unreachable");
  }

 private:
  ArgsStruct* args_;
};

void TestCancelActiveDNSQuery(ArgsStruct* args) {
  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  std::string client_target = absl::StrFormat(
      "dns://[::1]:%d/dont-care-since-wont-be-resolved.test.com:1234",
      fake_dns_server.port());

  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver =
      grpc_core::CoreConfiguration::Get().resolver_registry().CreateResolver(
          client_target.c_str(),
          grpc_core::ChannelArgs().SetObject(GetDefaultEventEngine()),
          args->pollset_set, args->lock,
          std::unique_ptr<grpc_core::Resolver::ResultHandler>(
              new AssertFailureResultHandler(args)));
  resolver->StartLocked();

  resolver.reset();
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone(args);
  ArgsFinish(args);
}

class CancelDuringAresQuery : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    grpc_core::ConfigVars::Overrides overrides;
    overrides.dns_resolver = "ares";
    grpc_core::ConfigVars::SetOverrides(overrides);
    grpc_init();
  }

  static void TearDownTestSuite() { grpc_shutdown(); }
};

TEST_F(CancelDuringAresQuery, TestCancelActiveDNSQuery) {
  grpc_core::ExecCtx exec_ctx;
  ArgsStruct args;
  ArgsInit(&args);
  TestCancelActiveDNSQuery(&args);
}

#ifdef GPR_WINDOWS

void MaybePollArbitraryPollsetTwice() {
  grpc_pollset* pollset = (grpc_pollset*)gpr_zalloc(grpc_pollset_size());
  gpr_mu* mu;
  grpc_pollset_init(pollset, &mu);
  grpc_pollset_worker* worker = nullptr;

  gpr_mu_lock(mu);
  GRPC_LOG_IF_ERROR(
      "pollset_work",
      grpc_pollset_work(pollset, &worker, grpc_core::Timestamp::Now()));
  gpr_mu_unlock(mu);
  grpc_core::ExecCtx::Get()->Flush();

  gpr_mu_lock(mu);
  GRPC_LOG_IF_ERROR(
      "pollset_work",
      grpc_pollset_work(pollset, &worker, grpc_core::Timestamp::Now()));
  gpr_mu_unlock(mu);
  grpc_core::ExecCtx::Get()->Flush();
  grpc_pollset_destroy(pollset);
  gpr_free(pollset);
}

#else

void MaybePollArbitraryPollsetTwice() {}

#endif

TEST_F(CancelDuringAresQuery, TestFdsAreDeletedFromPollsetSet) {
  grpc_core::ExecCtx exec_ctx;
  ArgsStruct args;
  ArgsInit(&args);

  grpc_pollset_set* fake_other_pollset_set = grpc_pollset_set_create();
  grpc_pollset_set_add_pollset_set(fake_other_pollset_set, args.pollset_set);

  TestCancelActiveDNSQuery(&args);

  MaybePollArbitraryPollsetTwice();
  EXPECT_EQ(grpc_iomgr_count_objects_for_testing(), 0u);
  grpc_pollset_set_destroy(fake_other_pollset_set);
}

std::string kFakeName = "dont-care-since-wont-be-resolved.test.com:1234";

void TestCancelDuringActiveQuery(
    grpc_status_code expected_status_code,
    absl::string_view expected_error_message_substring,
    gpr_timespec rpc_deadline, int dns_query_timeout_ms,
    int fake_dns_server_port) {

  std::string client_target =
      absl::StrFormat("dns://[::1]:%d/%s", fake_dns_server_port, kFakeName);
  grpc_channel_args* client_args = nullptr;
  if (dns_query_timeout_ms >= 0) {
    grpc_arg arg;
    arg.type = GRPC_ARG_INTEGER;
    arg.key = const_cast<char*>(GRPC_ARG_DNS_ARES_QUERY_TIMEOUT_MS);
    arg.value.integer = dns_query_timeout_ms;
    client_args = grpc_channel_args_copy_and_add(nullptr, &arg, 1);
  }
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* client =
      grpc_channel_create(client_target.c_str(), creds, client_args);
  grpc_channel_credentials_release(creds);
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  grpc_core::CqVerifier cqv(cq);
  grpc_call* call = grpc_channel_create_call(
      client, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
      grpc_slice_from_static_string("/foo"), nullptr, rpc_deadline, nullptr);
  CHECK(call);
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details call_details;
  grpc_call_details_init(&call_details);
  grpc_status_code status;
  const char* error_string;
  grpc_slice details;

  grpc_op ops_base[6];
  memset(ops_base, 0, sizeof(ops_base));
  grpc_op* op = ops_base;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->data.recv_status_on_client.error_string = &error_string;
  op->flags = 0;
  op->reserved = nullptr;
  op++;

  grpc_call_error error = grpc_call_start_batch(
      call, ops_base, static_cast<size_t>(op - ops_base), Tag(1), nullptr);
  EXPECT_EQ(GRPC_CALL_OK, error);
  cqv.Expect(Tag(1), true);
  cqv.Verify();
  EXPECT_EQ(status, expected_status_code);
  EXPECT_THAT(std::string(error_string),
              testing::HasSubstr(expected_error_message_substring));

  grpc_channel_args_destroy(client_args);
  grpc_slice_unref(details);
  gpr_free(const_cast<char*>(error_string));
  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);
  grpc_call_unref(call);
  EndTest(client, cq);
}

TEST_F(CancelDuringAresQuery,
       TestHitDeadlineAndDestroyChannelDuringAresResolutionIsGraceful) {
  grpc_core::testing::SocketUseAfterCloseDetector
      socket_use_after_close_detector;
  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  grpc_status_code expected_status_code = GRPC_STATUS_DEADLINE_EXCEEDED;

  gpr_timespec rpc_deadline = grpc_timeout_milliseconds_to_deadline(100);
  int dns_query_timeout_ms = -1;
  TestCancelDuringActiveQuery(
      expected_status_code, "" ,
      rpc_deadline, dns_query_timeout_ms, fake_dns_server.port());
}

TEST_F(
    CancelDuringAresQuery,
    TestHitDeadlineAndDestroyChannelDuringAresResolutionWithQueryTimeoutIsGraceful) {
  grpc_core::testing::SocketUseAfterCloseDetector
      socket_use_after_close_detector;
  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  grpc_status_code expected_status_code = GRPC_STATUS_UNAVAILABLE;
  std::string expected_error_message_substring;
  if (grpc_core::IsEventEngineDnsEnabled()) {
    expected_error_message_substring =
        absl::StrCat("errors resolving ", kFakeName);
  } else {
    expected_error_message_substring =
        absl::StrCat("DNS resolution failed for ", kFakeName);
  }

  gpr_timespec rpc_deadline = grpc_timeout_seconds_to_deadline(10);
  int dns_query_timeout_ms = 1;
  TestCancelDuringActiveQuery(expected_status_code,
                              expected_error_message_substring, rpc_deadline,
                              dns_query_timeout_ms, fake_dns_server.port());
}

TEST_F(
    CancelDuringAresQuery,
    TestHitDeadlineAndDestroyChannelDuringAresResolutionWithZeroQueryTimeoutIsGraceful) {
  grpc_core::testing::SocketUseAfterCloseDetector
      socket_use_after_close_detector;
  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  grpc_status_code expected_status_code = GRPC_STATUS_DEADLINE_EXCEEDED;

  gpr_timespec rpc_deadline = grpc_timeout_milliseconds_to_deadline(100);
  int dns_query_timeout_ms = 0;
  TestCancelDuringActiveQuery(
      expected_status_code, "" ,
      rpc_deadline, dns_query_timeout_ms, fake_dns_server.port());
}

TEST_F(CancelDuringAresQuery, TestQueryFailsBecauseTcpServerClosesSocket) {
  grpc_core::testing::SocketUseAfterCloseDetector
      socket_use_after_close_detector;

  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::
          CloseSocketUponReceivingBytesFromPeer);
  if (grpc_core::IsEventEngineDnsEnabled()) {
    g_event_engine_grpc_ares_test_only_force_tcp = true;
  } else {
    g_grpc_ares_test_only_force_tcp = true;
  }
  grpc_status_code expected_status_code = GRPC_STATUS_UNAVAILABLE;
  std::string expected_error_message_substring;
  if (grpc_core::IsEventEngineDnsEnabled()) {
    expected_error_message_substring =
        absl::StrCat("errors resolving ", kFakeName);
  } else {
    expected_error_message_substring =
        absl::StrCat("DNS resolution failed for ", kFakeName);
  }

  gpr_timespec rpc_deadline = grpc_timeout_seconds_to_deadline(100);
  int dns_query_timeout_ms = -1;
  TestCancelDuringActiveQuery(expected_status_code,
                              expected_error_message_substring, rpc_deadline,
                              dns_query_timeout_ms, fake_dns_server.port());
  if (grpc_core::IsEventEngineDnsEnabled()) {
    g_event_engine_grpc_ares_test_only_force_tcp = false;
  } else {
    g_grpc_ares_test_only_force_tcp = false;
  }
}

TEST_F(CancelDuringAresQuery, TestQueryFailsWithDataRemainingInReadBuffer) {
  if (grpc_core::IsEventEngineDnsEnabled()) {
    g_event_engine_grpc_ares_test_only_force_tcp = true;
  } else {
    g_grpc_ares_test_only_force_tcp = true;
  }
  grpc_core::testing::SocketUseAfterCloseDetector
      socket_use_after_close_detector;
  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::SendThreeAllZeroBytes);
  grpc_status_code expected_status_code = GRPC_STATUS_UNAVAILABLE;

  gpr_timespec rpc_deadline = grpc_timeout_seconds_to_deadline(100);
  int dns_query_timeout_ms = -1;
  TestCancelDuringActiveQuery(
      expected_status_code, "" ,
      rpc_deadline, dns_query_timeout_ms, fake_dns_server.port());
  if (grpc_core::IsEventEngineDnsEnabled()) {
    g_event_engine_grpc_ares_test_only_force_tcp = false;
  } else {
    g_grpc_ares_test_only_force_tcp = false;
  }
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  grpc::testing::TestEnvironment env(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
