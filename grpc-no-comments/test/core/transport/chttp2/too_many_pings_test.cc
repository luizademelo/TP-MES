
// Copyright 2020 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <string.h>

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/resolver/resolver.h"
#include "src/core/util/host_port.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"
#include "src/core/util/useful.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/test_config.h"

namespace {

class TransportCounter {
 public:
  static void CounterInitCallback() {
    grpc_core::MutexLock lock(&mu());
    ++count_;
  }

  static void CounterDestructCallback() {
    grpc_core::MutexLock lock(&mu());
    if (--count_ == 0) {
      cv().SignalAll();
    }
  }

  static void WaitForTransportsToBeDestroyed() {
    grpc_core::MutexLock lock(&mu());
    while (count_ != 0) {
      ASSERT_FALSE(cv().WaitWithTimeout(&mu(), absl::Seconds(10)));
    }
  }

  static int count() {
    grpc_core::MutexLock lock(&mu());
    return count_;
  }

  static grpc_core::Mutex& mu() {
    static grpc_core::Mutex* mu = new grpc_core::Mutex();
    return *mu;
  }

  static grpc_core::CondVar& cv() {
    static grpc_core::CondVar* cv = new grpc_core::CondVar();
    return *cv;
  }

 private:
  static int count_;
};

int TransportCounter::count_ = 0;

grpc_status_code PerformCall(grpc_channel* channel, grpc_server* server,
                             grpc_completion_queue* cq) {
  grpc_call* c;
  grpc_call* s;
  grpc_core::CqVerifier cqv(cq);
  grpc_op ops[6];
  grpc_op* op;
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_call_details call_details;
  grpc_status_code status;
  grpc_call_error error;
  grpc_slice details;
  gpr_timespec deadline = grpc_timeout_seconds_to_deadline(30);

  c = grpc_channel_create_call(channel, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
                               grpc_slice_from_static_string("/foo"), nullptr,
                               deadline, nullptr);
  CHECK(c);
  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details_init(&call_details);
  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(c, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(1), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();
  grpc_call_cancel_with_status(s, GRPC_STATUS_PERMISSION_DENIED, "test status",
                               nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(1), true);
  cqv.Verify();

  grpc_slice_unref(details);
  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);
  grpc_call_unref(c);
  grpc_call_unref(s);
  return status;
}

TEST(TooManyPings, TestLotsOfServerCancelledRpcsDoesntGiveTooManyPings) {
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);

  grpc_server* server = grpc_server_create(nullptr, nullptr);
  std::string server_address = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  grpc_server_register_completion_queue(server, cq, nullptr);
  grpc_server_credentials* server_creds =
      grpc_insecure_server_credentials_create();
  CHECK(
      grpc_server_add_http2_port(server, server_address.c_str(), server_creds));
  grpc_server_credentials_release(server_creds);
  grpc_server_start(server);

  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* channel = grpc_channel_create(server_address.c_str(), creds,
                                              nullptr );
  grpc_channel_credentials_release(creds);
  std::map<grpc_status_code, int> statuses_and_counts;
  const int kNumTotalRpcs = 100;

  LOG(INFO) << "Performing " << kNumTotalRpcs
            << " total RPCs and expecting them all to receive status "
               "PERMISSION_DENIED ("
            << GRPC_STATUS_PERMISSION_DENIED << ")";
  for (int i = 0; i < kNumTotalRpcs; i++) {
    grpc_status_code status = PerformCall(channel, server, cq);
    statuses_and_counts[status] += 1;
  }
  int num_not_cancelled = 0;
  for (auto itr = statuses_and_counts.begin(); itr != statuses_and_counts.end();
       itr++) {
    if (itr->first != GRPC_STATUS_PERMISSION_DENIED) {
      num_not_cancelled += itr->second;
    }
    LOG(INFO) << itr->second << " / " << kNumTotalRpcs
              << " RPCs received status code: " << itr->first;
  }
  if (num_not_cancelled > 0) {
    LOG(ERROR) << "Expected all RPCs to receive status PERMISSION_DENIED ("
               << GRPC_STATUS_PERMISSION_DENIED << ") but " << num_not_cancelled
               << " received other status codes";
    FAIL();
  }

  grpc_channel_destroy(channel);
  grpc_server_shutdown_and_notify(server, cq, nullptr);
  grpc_completion_queue_shutdown(cq);
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .type != GRPC_QUEUE_SHUTDOWN) {
  }
  grpc_server_destroy(server);
  grpc_completion_queue_destroy(cq);
}

grpc_status_code PerformWaitingCall(grpc_channel* channel, grpc_server* server,
                                    grpc_completion_queue* cq) {
  grpc_call* c;
  grpc_call* s;
  grpc_core::CqVerifier cqv(cq);
  grpc_op ops[6];
  grpc_op* op;
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_call_details call_details;
  grpc_status_code status;
  grpc_call_error error;
  grpc_slice details;
  gpr_timespec deadline = grpc_timeout_seconds_to_deadline(30);

  c = grpc_channel_create_call(channel, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
                               grpc_slice_from_static_string("/foo"), nullptr,
                               deadline, nullptr);
  CHECK(c);
  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details_init(&call_details);
  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(c, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(1), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();

  cqv.Expect(grpc_core::CqVerifier::tag(1), true);

  cqv.Verify(grpc_core::Duration::Seconds(60));

  grpc_slice_unref(details);
  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);
  grpc_call_unref(c);
  grpc_call_unref(s);
  return status;
}

void ServerShutdownAndDestroy(grpc_server* server, grpc_completion_queue* cq) {

  grpc_server_shutdown_and_notify(server, cq, reinterpret_cast<void*>(1000));
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .tag != reinterpret_cast<void*>(1000)) {
  }
  grpc_server_destroy(server);
}

void VerifyChannelReady(grpc_channel* channel, grpc_completion_queue* cq) {
  grpc_connectivity_state state =
      grpc_channel_check_connectivity_state(channel, 1 );
  while (state != GRPC_CHANNEL_READY) {
    grpc_channel_watch_connectivity_state(
        channel, state, grpc_timeout_seconds_to_deadline(5), cq, nullptr);
    grpc_completion_queue_next(cq, grpc_timeout_seconds_to_deadline(5),
                               nullptr);
    state = grpc_channel_check_connectivity_state(channel, 0);
  }
}

void VerifyChannelDisconnected(grpc_channel* channel,
                               grpc_completion_queue* cq) {

  grpc_channel_ping(channel, cq, reinterpret_cast<void*>(2000), nullptr);
  grpc_event ev = grpc_completion_queue_next(
      cq, grpc_timeout_seconds_to_deadline(5), nullptr);
  CHECK(ev.type == GRPC_OP_COMPLETE);
  CHECK(ev.tag == reinterpret_cast<void*>(2000));
  CHECK_EQ(ev.success, 0);

}

class KeepaliveThrottlingTest : public ::testing::Test {
 protected:

  grpc_server* ServerStart(const char* addr, grpc_completion_queue* cq) {

    grpc_arg server_args[] = {
        grpc_channel_arg_integer_create(
            const_cast<char*>(
                GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS),
            5 * 1000),
        grpc_channel_arg_integer_create(
            const_cast<char*>(GRPC_ARG_HTTP2_MAX_PING_STRIKES), 1)};
    grpc_channel_args server_channel_args = {GPR_ARRAY_SIZE(server_args),
                                             server_args};

    grpc_server* server = grpc_server_create(&server_channel_args, nullptr);
    grpc_server_register_completion_queue(server, cq, nullptr);
    grpc_server_credentials* server_creds =
        grpc_insecure_server_credentials_create();
    CHECK(grpc_server_add_http2_port(server, addr, server_creds));
    grpc_server_credentials_release(server_creds);
    grpc_server_start(server);
    return server;
  }
};

TEST_F(KeepaliveThrottlingTest, KeepaliveThrottlingMultipleChannels) {
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  std::string server_address = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  grpc_server* server = ServerStart(server_address.c_str(), cq);

  grpc_arg client_args[] = {
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA), 0),
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_KEEPALIVE_TIME_MS), 1 * 1000),
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_HTTP2_BDP_PROBE), 0)};
  grpc_channel_args client_channel_args = {GPR_ARRAY_SIZE(client_args),
                                           client_args};
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* channel =
      grpc_channel_create(server_address.c_str(), creds, &client_channel_args);
  grpc_channel* channel_dup =
      grpc_channel_create(server_address.c_str(), creds, &client_channel_args);
  grpc_channel_credentials_release(creds);
  int expected_keepalive_time_sec = 1;

  for (int i = 0; i < 3; i++) {
    LOG(INFO) << "Expected keepalive time : " << expected_keepalive_time_sec;
    EXPECT_EQ(PerformWaitingCall(channel, server, cq), GRPC_STATUS_UNAVAILABLE);
    expected_keepalive_time_sec *= 2;
  }
  LOG(INFO) << "Client keepalive time " << expected_keepalive_time_sec
            << " should now be in sync with the server settings";
  EXPECT_EQ(PerformWaitingCall(channel, server, cq),
            GRPC_STATUS_DEADLINE_EXCEEDED);

  LOG(INFO) << "Now testing second channel sharing the same subchannel";
  EXPECT_EQ(PerformWaitingCall(channel_dup, server, cq),
            GRPC_STATUS_DEADLINE_EXCEEDED);

  grpc_channel_destroy(channel);
  grpc_channel_destroy(channel_dup);
  ServerShutdownAndDestroy(server, cq);
  grpc_completion_queue_shutdown(cq);
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .type != GRPC_QUEUE_SHUTDOWN) {
  }
  grpc_completion_queue_destroy(cq);
}

grpc_core::Resolver::Result BuildResolverResult(
    const std::vector<std::string>& addresses) {
  grpc_core::Resolver::Result result;
  result.addresses = grpc_core::EndpointAddressesList();
  for (const auto& address_str : addresses) {
    absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(address_str);
    if (!uri.ok()) {
      LOG(ERROR) << "Failed to parse uri. Error: " << uri.status();
      CHECK_OK(uri);
    }
    grpc_resolved_address address;
    CHECK(grpc_parse_uri(*uri, &address));
    result.addresses->emplace_back(address, grpc_core::ChannelArgs());
  }
  return result;
}

TEST_F(KeepaliveThrottlingTest, NewSubchannelsUseUpdatedKeepaliveTime) {
  grpc_core::ExecCtx exec_ctx;
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  std::string server_address1 = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  std::string server_address2 = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  grpc_server* server1 = ServerStart(server_address1.c_str(), cq);
  grpc_server* server2 = ServerStart(server_address2.c_str(), cq);

  auto response_generator =
      grpc_core::MakeRefCounted<grpc_core::FakeResolverResponseGenerator>();
  auto client_channel_args =
      grpc_core::ChannelArgs()
          .Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0)
          .Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 0)
          .Set(GRPC_ARG_KEEPALIVE_TIME_MS, 1 * 1000)
          .Set(GRPC_ARG_HTTP2_BDP_PROBE, 0)
          .SetObject(response_generator)
          .ToC();
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* channel =
      grpc_channel_create("fake:///", creds, client_channel_args.get());
  grpc_channel_credentials_release(creds);

  int expected_keepalive_time_sec = 1;
  for (int i = 0; i < 3; i++) {
    LOG(INFO) << "Expected keepalive time : " << expected_keepalive_time_sec;
    response_generator->SetResponseSynchronously(
        BuildResolverResult({absl::StrCat(
            "ipv4:", i % 2 == 0 ? server_address1 : server_address2)}));

    grpc_core::ExecCtx::Get()->Flush();
    gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
    EXPECT_EQ(PerformWaitingCall(channel, i % 2 == 0 ? server1 : server2, cq),
              GRPC_STATUS_UNAVAILABLE);
    expected_keepalive_time_sec *= 2;
  }
  LOG(INFO) << "Client keepalive time " << expected_keepalive_time_sec
            << " should now be in sync with the server settings";
  response_generator->SetResponseSynchronously(
      BuildResolverResult({absl::StrCat("ipv4:", server_address2)}));
  grpc_core::ExecCtx::Get()->Flush();
  gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
  EXPECT_EQ(PerformWaitingCall(channel, server2, cq),
            GRPC_STATUS_DEADLINE_EXCEEDED);

  grpc_channel_destroy(channel);
  ServerShutdownAndDestroy(server1, cq);
  ServerShutdownAndDestroy(server2, cq);
  grpc_completion_queue_shutdown(cq);
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .type != GRPC_QUEUE_SHUTDOWN) {
  }
  grpc_completion_queue_destroy(cq);
}

TEST_F(KeepaliveThrottlingTest,
       ExistingSubchannelsUseNewKeepaliveTimeWhenReconnecting) {
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  std::string server_address1 = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  std::string server_address2 = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());

  auto response_generator =
      grpc_core::MakeRefCounted<grpc_core::FakeResolverResponseGenerator>();
  auto client_channel_args =
      grpc_core::ChannelArgs()
          .Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0)
          .Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 0)
          .Set(GRPC_ARG_KEEPALIVE_TIME_MS, 1 * 1000)
          .Set(GRPC_ARG_HTTP2_BDP_PROBE, 0)
          .SetObject(response_generator)
          .ToC();
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* channel =
      grpc_channel_create("fake:///", creds, client_channel_args.get());
  grpc_channel_credentials_release(creds);
  response_generator->SetResponseSynchronously(
      BuildResolverResult({absl::StrCat("ipv4:", server_address1),
                           absl::StrCat("ipv4:", server_address2)}));

  int expected_keepalive_time_sec = 1;
  for (int i = 0; i < 3; i++) {
    LOG(ERROR) << "Expected keepalive time : " << expected_keepalive_time_sec;
    grpc_server* server = ServerStart(
        i % 2 == 0 ? server_address1.c_str() : server_address2.c_str(), cq);
    VerifyChannelReady(channel, cq);
    EXPECT_EQ(PerformWaitingCall(channel, server, cq), GRPC_STATUS_UNAVAILABLE);
    ServerShutdownAndDestroy(server, cq);
    VerifyChannelDisconnected(channel, cq);
    expected_keepalive_time_sec *= 2;
  }
  LOG(INFO) << "Client keepalive time " << expected_keepalive_time_sec
            << " should now be in sync with the server settings";
  grpc_server* server = ServerStart(server_address1.c_str(), cq);
  VerifyChannelReady(channel, cq);
  EXPECT_EQ(PerformWaitingCall(channel, server, cq),
            GRPC_STATUS_DEADLINE_EXCEEDED);
  ServerShutdownAndDestroy(server, cq);

  grpc_channel_destroy(channel);
  grpc_completion_queue_shutdown(cq);
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .type != GRPC_QUEUE_SHUTDOWN) {
  }
  grpc_completion_queue_destroy(cq);
}

void PerformCallWithResponsePayload(grpc_channel* channel, grpc_server* server,
                                    grpc_completion_queue* cq) {
  grpc_slice response_payload_slice = grpc_slice_from_static_string("hello");

  grpc_call* c;
  grpc_call* s;
  grpc_byte_buffer* response_payload =
      grpc_raw_byte_buffer_create(&response_payload_slice, 1);
  grpc_core::CqVerifier cqv(cq);
  grpc_op ops[6];
  grpc_op* op;
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array request_metadata_recv;
  grpc_byte_buffer* response_payload_recv = nullptr;
  grpc_call_details call_details;
  grpc_status_code status;
  grpc_call_error error;
  grpc_slice details;
  int was_cancelled = 2;

  gpr_timespec deadline = grpc_timeout_seconds_to_deadline(60);
  c = grpc_channel_create_call(channel, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
                               grpc_slice_from_static_string("/foo"), nullptr,
                               deadline, nullptr);
  CHECK(c);

  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_metadata_array_init(&request_metadata_recv);
  grpc_call_details_init(&call_details);

  memset(ops, 0, sizeof(ops));
  op = ops;
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
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &response_payload_recv;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(c, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(1), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  error = grpc_server_request_call(server, &s, &call_details,
                                   &request_metadata_recv, cq, cq,
                                   grpc_core::CqVerifier::tag(101));
  CHECK_EQ(error, GRPC_CALL_OK);
  cqv.Expect(grpc_core::CqVerifier::tag(101), true);
  cqv.Verify();

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(s, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(102), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  cqv.Expect(grpc_core::CqVerifier::tag(102), true);
  cqv.Verify();

  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_RECV_CLOSE_ON_SERVER;
  op->data.recv_close_on_server.cancelled = &was_cancelled;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_MESSAGE;
  op->data.send_message.send_message = response_payload;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  op->op = GRPC_OP_SEND_STATUS_FROM_SERVER;
  op->data.send_status_from_server.trailing_metadata_count = 0;
  op->data.send_status_from_server.status = GRPC_STATUS_OK;
  op->flags = 0;
  op->reserved = nullptr;
  op++;
  error = grpc_call_start_batch(s, ops, static_cast<size_t>(op - ops),
                                grpc_core::CqVerifier::tag(103), nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);

  cqv.Expect(grpc_core::CqVerifier::tag(103), true);
  cqv.Expect(grpc_core::CqVerifier::tag(1), true);
  cqv.Verify();

  EXPECT_EQ(status, GRPC_STATUS_OK);
  EXPECT_EQ(grpc_core::StringViewFromSlice(call_details.method), "/foo");
  EXPECT_EQ(was_cancelled, 0);
  EXPECT_TRUE(
      byte_buffer_eq_slice(response_payload_recv, response_payload_slice));

  grpc_slice_unref(details);
  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_metadata_array_destroy(&request_metadata_recv);
  grpc_call_details_destroy(&call_details);

  grpc_call_unref(c);
  grpc_call_unref(s);

  grpc_byte_buffer_destroy(response_payload);
  grpc_byte_buffer_destroy(response_payload_recv);
}

TEST(TooManyPings, BdpPingNotSentWithoutReceiveSideActivity) {
  TransportCounter::WaitForTransportsToBeDestroyed();
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);

  std::string server_address = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  grpc_arg server_args[] = {
      grpc_channel_arg_integer_create(
          const_cast<char*>(
              GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS),
          60 * 1000),
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_HTTP2_MAX_PING_STRIKES), 1)};
  grpc_channel_args server_channel_args = {GPR_ARRAY_SIZE(server_args),
                                           server_args};
  grpc_server* server = grpc_server_create(&server_channel_args, nullptr);
  grpc_server_register_completion_queue(server, cq, nullptr);
  grpc_server_credentials* server_creds =
      grpc_insecure_server_credentials_create();
  CHECK(
      grpc_server_add_http2_port(server, server_address.c_str(), server_creds));
  grpc_server_credentials_release(server_creds);
  grpc_server_start(server);

  grpc_arg client_args[] = {
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA), 0),
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS), 1)};
  grpc_channel_args client_channel_args = {GPR_ARRAY_SIZE(client_args),
                                           client_args};
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* channel =
      grpc_channel_create(server_address.c_str(), creds, &client_channel_args);
  grpc_channel_credentials_release(creds);
  VerifyChannelReady(channel, cq);
  EXPECT_EQ(TransportCounter::count(), 2 );
  grpc_core::CqVerifier cqv(cq);

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(1), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(1), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(2), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(2), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));
  ASSERT_EQ(grpc_channel_check_connectivity_state(channel, 0),
            GRPC_CHANNEL_READY);
  PerformCallWithResponsePayload(channel, server, cq);

  cqv.VerifyEmpty(grpc_core::Duration::Seconds(1));

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(3), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(3), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(4), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(4), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));

  VerifyChannelDisconnected(channel, cq);
  TransportCounter::WaitForTransportsToBeDestroyed();

  ServerShutdownAndDestroy(server, cq);
  grpc_channel_destroy(channel);
  grpc_completion_queue_shutdown(cq);
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .type != GRPC_QUEUE_SHUTDOWN) {
  }
  grpc_completion_queue_destroy(cq);
}

TEST(TooManyPings, TransportsGetCleanedUpOnDisconnect) {
  TransportCounter::WaitForTransportsToBeDestroyed();
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);

  std::string server_address = grpc_core::JoinHostPort(
      grpc_core::LocalIp(), grpc_pick_unused_port_or_die());
  grpc_arg server_args[] = {
      grpc_channel_arg_integer_create(
          const_cast<char*>(
              GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS),
          60 * 1000),
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_HTTP2_MAX_PING_STRIKES), 1)};
  grpc_channel_args server_channel_args = {GPR_ARRAY_SIZE(server_args),
                                           server_args};
  grpc_server* server = grpc_server_create(&server_channel_args, nullptr);
  grpc_server_register_completion_queue(server, cq, nullptr);
  grpc_server_credentials* server_creds =
      grpc_insecure_server_credentials_create();
  CHECK(
      grpc_server_add_http2_port(server, server_address.c_str(), server_creds));
  grpc_server_credentials_release(server_creds);
  grpc_server_start(server);
  grpc_arg client_args[] = {
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA), 0),
      grpc_channel_arg_integer_create(
          const_cast<char*>(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS), 1)};
  grpc_channel_args client_channel_args = {GPR_ARRAY_SIZE(client_args),
                                           client_args};
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  grpc_channel* channel =
      grpc_channel_create(server_address.c_str(), creds, &client_channel_args);
  grpc_channel_credentials_release(creds);
  VerifyChannelReady(channel, cq);
  EXPECT_EQ(TransportCounter::count(), 2 );
  grpc_core::CqVerifier cqv(cq);

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(1), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(1), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(2), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(2), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));

  grpc_channel_ping(channel, cq, grpc_core::CqVerifier::tag(2), nullptr);
  cqv.Expect(grpc_core::CqVerifier::tag(2), true);
  cqv.Verify(grpc_core::Duration::Seconds(5));

  VerifyChannelDisconnected(channel, cq);
  TransportCounter::WaitForTransportsToBeDestroyed();

  ServerShutdownAndDestroy(server, cq);
  grpc_channel_destroy(channel);
  grpc_completion_queue_shutdown(cq);
  while (grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                    nullptr)
             .type != GRPC_QUEUE_SHUTDOWN) {
  }
  grpc_completion_queue_destroy(cq);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_core::TestOnlySetGlobalHttp2TransportInitCallback(
      TransportCounter::CounterInitCallback);
  grpc_core::TestOnlySetGlobalHttp2TransportDestructCallback(
      TransportCounter::CounterDestructCallback);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
