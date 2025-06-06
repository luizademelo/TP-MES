// Copyright 2022 gRPC authors.

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
#include <inttypes.h>
#include <string.h>

#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/host_port.h"
#include "src/core/util/sync.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

namespace {

class TestServer {
 public:
  explicit TestServer(grpc_completion_queue* cq,
                      grpc_channel_args* channel_args)
      : cq_(cq) {
    server_ = grpc_server_create(channel_args, nullptr);
    address_ = grpc_core::JoinHostPort("[::1]", grpc_pick_unused_port_or_die());
    grpc_server_register_completion_queue(server_, cq_, nullptr);
    grpc_server_credentials* server_creds =
        grpc_insecure_server_credentials_create();
    CHECK(grpc_server_add_http2_port(server_, address_.c_str(), server_creds));
    grpc_server_credentials_release(server_creds);
    grpc_server_start(server_);
  }

  ~TestServer() {
    grpc_server_shutdown_and_notify(server_, cq_, this );
    grpc_event event = grpc_completion_queue_next(
        cq_, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
    CHECK(event.type == GRPC_OP_COMPLETE);
    CHECK(event.success);
    CHECK(event.tag == this);
    grpc_server_destroy(server_);
  }

  void HandleRpc() {
    grpc_call_details call_details;
    grpc_call_details_init(&call_details);
    grpc_metadata_array request_metadata_recv;
    grpc_metadata_array_init(&request_metadata_recv);
    grpc_slice status_details = grpc_slice_from_static_string("xyz");
    int was_cancelled;

    void* tag = this;
    grpc_call* call;
    grpc_call_error error = grpc_server_request_call(
        server_, &call, &call_details, &request_metadata_recv, cq_, cq_, tag);
    CHECK_EQ(error, GRPC_CALL_OK);
    grpc_event event = grpc_completion_queue_next(
        cq_, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
    CHECK(event.type == GRPC_OP_COMPLETE);
    grpc_call_details_destroy(&call_details);
    grpc_metadata_array_destroy(&request_metadata_recv);
    CHECK(event.success);
    CHECK(event.tag == tag);

    grpc_slice response_payload_slice = grpc_slice_from_static_string("a");
    grpc_byte_buffer* response_payload =
        grpc_raw_byte_buffer_create(&response_payload_slice, 1);
    grpc_op ops[4];
    grpc_op* op;
    memset(ops, 0, sizeof(ops));
    op = ops;
    op->op = GRPC_OP_RECV_CLOSE_ON_SERVER;
    op->data.recv_close_on_server.cancelled = &was_cancelled;
    op++;
    op->op = GRPC_OP_SEND_INITIAL_METADATA;
    op++;
    op->op = GRPC_OP_SEND_MESSAGE;
    op->data.send_message.send_message = response_payload;
    op++;
    op->op = GRPC_OP_SEND_STATUS_FROM_SERVER;
    op->data.send_status_from_server.status = GRPC_STATUS_OK;
    op->data.send_status_from_server.status_details = &status_details;
    op++;
    error = grpc_call_start_batch(call, ops, static_cast<size_t>(op - ops), tag,
                                  nullptr);
    CHECK_EQ(error, GRPC_CALL_OK);
    event = grpc_completion_queue_next(cq_, gpr_inf_future(GPR_CLOCK_REALTIME),
                                       nullptr);
    CHECK(event.type == GRPC_OP_COMPLETE);
    CHECK(event.success);
    CHECK(event.tag == tag);
    grpc_byte_buffer_destroy(response_payload);
    grpc_call_unref(call);
  }

  std::string address() const { return address_; }

 private:
  grpc_server* server_;
  grpc_completion_queue* cq_;
  std::string address_;
};

void StartCallAndCloseWrites(grpc_call* call, grpc_completion_queue* cq) {
  grpc_op ops[2];
  grpc_op* op;
  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op++;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  op++;
  void* tag = call;
  grpc_call_error error = grpc_call_start_batch(
      call, ops, static_cast<size_t>(op - ops), tag, nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);
  grpc_event event = grpc_completion_queue_next(
      cq, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
  CHECK(event.type == GRPC_OP_COMPLETE);
  CHECK(event.success);
  CHECK(event.tag == tag);
}

void FinishCall(grpc_call* call, grpc_completion_queue* cq) {
  grpc_metadata_array initial_metadata_recv;
  grpc_metadata_array_init(&initial_metadata_recv);
  grpc_metadata_array trailing_metadata_recv;
  grpc_metadata_array_init(&trailing_metadata_recv);
  grpc_status_code status = GRPC_STATUS_UNKNOWN;
  grpc_slice details;
  grpc_byte_buffer* recv_payload = nullptr;
  void* tag = call;
  // Note: we're only doing read ops here.  The goal here is to finish the call

  grpc_op ops[3];
  grpc_op* op;
  memset(ops, 0, sizeof(ops));
  op = ops;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata = &initial_metadata_recv;
  op++;
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &recv_payload;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &trailing_metadata_recv;
  op->data.recv_status_on_client.status = &status;
  op->data.recv_status_on_client.status_details = &details;
  op++;
  grpc_call_error error = grpc_call_start_batch(
      call, ops, static_cast<size_t>(op - ops), tag, nullptr);
  CHECK_EQ(error, GRPC_CALL_OK);
  grpc_event event = grpc_completion_queue_next(
      cq, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
  CHECK(event.type == GRPC_OP_COMPLETE);
  CHECK(event.success);
  CHECK(event.tag == tag);
  EXPECT_EQ(status, GRPC_STATUS_OK);
  grpc_byte_buffer_destroy(recv_payload);
  grpc_metadata_array_destroy(&initial_metadata_recv);
  grpc_metadata_array_destroy(&trailing_metadata_recv);
  grpc_slice_unref(details);
}

class TransportCounter {
 public:
  void InitCallback() {
    grpc_core::MutexLock lock(&mu_);
    ++num_created_;
    ++num_live_;
    LOG(INFO) << "TransportCounter num_created_=" << num_created_
              << " num_live_=" << num_live_ << " InitCallback";
  }

  void DestructCallback() {
    grpc_core::MutexLock lock(&mu_);
    --num_live_;
    LOG(INFO) << "TransportCounter num_created_=" << num_created_
              << " num_live_=" << num_live_ << " DestructCallback";
  }

  int64_t num_live() {
    grpc_core::MutexLock lock(&mu_);
    return num_live_;
  }

  size_t num_created() {
    grpc_core::MutexLock lock(&mu_);
    return num_created_;
  }

 private:
  grpc_core::Mutex mu_;
  int64_t num_live_ ABSL_GUARDED_BY(mu_) = 0;
  size_t num_created_ ABSL_GUARDED_BY(mu_) = 0;
};

TransportCounter* g_transport_counter;

void CounterInitCallback() { g_transport_counter->InitCallback(); }

void CounterDestructCallback() { g_transport_counter->DestructCallback(); }

void EnsureConnectionsArentLeaked(grpc_completion_queue* cq) {
  LOG(INFO) << "The channel has been destroyed, wait for it to shut down and "
               "close...";

  CHECK(grpc_completion_queue_next(
            cq,
            gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                         gpr_time_from_millis(1, GPR_TIMESPAN)),
            nullptr)
            .type == GRPC_QUEUE_TIMEOUT);
  if (g_transport_counter->num_created() < 2) {
    LOG(ERROR) << "g_transport_counter->num_created() == "
               << g_transport_counter->num_created()
               << ". This means that g_transport_counter isn't working and "
                  "this test is broken. At least a couple of transport objects "
                  "should have been created.";
    CHECK(0);
  }
  gpr_timespec overall_deadline = grpc_timeout_seconds_to_deadline(120);
  for (;;) {
    // Note: the main goal of this test is to try to repro a chttp2 stream

    int64_t live_transports = g_transport_counter->num_live();
    if (live_transports == 0) return;
    if (gpr_time_cmp(gpr_now(GPR_CLOCK_MONOTONIC), overall_deadline) > 0) {
      LOG(INFO) << "g_transport_counter->num_live() never returned 0. "
                   "It's likely this test has triggered a connection leak.";
      CHECK(0);
    }
    LOG(INFO) << "g_transport_counter->num_live() returned " << live_transports
              << ", keep waiting until it reaches 0";
    CHECK(grpc_completion_queue_next(
              cq,
              gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                           gpr_time_from_seconds(1, GPR_TIMESPAN)),
              nullptr)
              .type == GRPC_QUEUE_TIMEOUT);
  }
}

TEST(
    Chttp2,
    TestStreamDoesntLeakWhenItsWriteClosedAndThenReadClosedBeforeStartOfReadingMessageAndStatus) {
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);
  {

    auto channel_args =
        grpc_core::ChannelArgs().Set(GRPC_ARG_HTTP2_BDP_PROBE, 0);
    TestServer server(cq,
                      const_cast<grpc_channel_args*>(channel_args.ToC().get()));
    grpc_channel_credentials* creds = grpc_insecure_credentials_create();
    grpc_channel* channel =
        grpc_channel_create(absl::StrCat("ipv6:", server.address()).c_str(),
                            creds, channel_args.ToC().get());
    grpc_channel_credentials_release(creds);
    grpc_call* call =
        grpc_channel_create_call(channel, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
                                 grpc_slice_from_static_string("/foo"), nullptr,
                                 gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);

    StartCallAndCloseWrites(call, cq);

    server.HandleRpc();

    CHECK(grpc_completion_queue_next(
              cq, grpc_timeout_milliseconds_to_deadline(20), nullptr)
              .type == GRPC_QUEUE_TIMEOUT);

    FinishCall(call, cq);
    grpc_call_unref(call);
    grpc_channel_destroy(channel);

    EnsureConnectionsArentLeaked(cq);
  }
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
  grpc_init();
  g_transport_counter = new TransportCounter();
  grpc_core::TestOnlySetGlobalHttp2TransportInitCallback(CounterInitCallback);
  grpc_core::TestOnlySetGlobalHttp2TransportDestructCallback(
      CounterDestructCallback);
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
