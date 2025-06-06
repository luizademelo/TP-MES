
// Copyright 2016 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/match.h"
#include "src/core/ext/transport/chaotic_good/chaotic_good.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/transport/endpoint_transport.h"
#include "src/core/util/useful.h"
#include "test/core/memory_usage/memstats.h"
#include "test/core/test_util/test_config.h"

static grpc_channel* channel;
static grpc_completion_queue* cq;
static grpc_op metadata_ops[2];
static grpc_op status_ops[2];
static grpc_op snapshot_ops[6];
static grpc_op* op;

typedef struct {
  grpc_call* call;
  grpc_metadata_array initial_metadata_recv;
  grpc_status_code status;
  grpc_slice details;
  grpc_metadata_array trailing_metadata_recv;
} fling_call;

static fling_call calls[100001];

static void* tag(intptr_t t) { return reinterpret_cast<void*>(t); }

static void init_ping_pong_request(int call_idx) {
  grpc_metadata_array_init(&calls[call_idx].initial_metadata_recv);

  memset(metadata_ops, 0, sizeof(metadata_ops));
  op = metadata_ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = GRPC_INITIAL_METADATA_WAIT_FOR_READY;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata =
      &calls[call_idx].initial_metadata_recv;
  op++;

  grpc_slice hostname = grpc_slice_from_static_string("localhost");
  calls[call_idx].call = grpc_channel_create_call(
      channel, nullptr, GRPC_PROPAGATE_DEFAULTS, cq,
      grpc_slice_from_static_string("/Reflector/reflectUnary"), &hostname,
      gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);

  CHECK(GRPC_CALL_OK == grpc_call_start_batch(calls[call_idx].call,
                                              metadata_ops,
                                              (size_t)(op - metadata_ops),
                                              tag(call_idx), nullptr));
  grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
}

static void finish_ping_pong_request(int call_idx) {
  grpc_metadata_array_init(&calls[call_idx].trailing_metadata_recv);

  memset(status_ops, 0, sizeof(status_ops));
  op = status_ops;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata =
      &calls[call_idx].trailing_metadata_recv;
  op->data.recv_status_on_client.status = &calls[call_idx].status;
  op->data.recv_status_on_client.status_details = &calls[call_idx].details;
  op++;

  CHECK(GRPC_CALL_OK == grpc_call_start_batch(calls[call_idx].call, status_ops,
                                              (size_t)(op - status_ops),
                                              tag(call_idx), nullptr));
  grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
  grpc_metadata_array_destroy(&calls[call_idx].initial_metadata_recv);
  grpc_metadata_array_destroy(&calls[call_idx].trailing_metadata_recv);
  grpc_slice_unref(calls[call_idx].details);
  grpc_call_unref(calls[call_idx].call);
  calls[call_idx].call = nullptr;
}

static MemStats send_snapshot_request(int call_idx, grpc_slice call_type) {
  grpc_metadata_array_init(&calls[call_idx].initial_metadata_recv);
  grpc_metadata_array_init(&calls[call_idx].trailing_metadata_recv);

  grpc_byte_buffer* response_payload_recv = nullptr;
  memset(snapshot_ops, 0, sizeof(snapshot_ops));
  op = snapshot_ops;

  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = GRPC_INITIAL_METADATA_WAIT_FOR_READY;
  op++;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  op++;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata =
      &calls[call_idx].initial_metadata_recv;
  op++;
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &response_payload_recv;
  op++;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata =
      &calls[call_idx].trailing_metadata_recv;
  op->data.recv_status_on_client.status = &calls[call_idx].status;
  op->data.recv_status_on_client.status_details = &calls[call_idx].details;
  op++;

  grpc_slice hostname = grpc_slice_from_static_string("localhost");
  calls[call_idx].call = grpc_channel_create_call(
      channel, nullptr, GRPC_PROPAGATE_DEFAULTS, cq, call_type, &hostname,
      gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
  CHECK(GRPC_CALL_OK == grpc_call_start_batch(calls[call_idx].call,
                                              snapshot_ops,
                                              (size_t)(op - snapshot_ops),
                                              (void*)nullptr, nullptr));
  grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);

  LOG(INFO) << "Call " << call_idx << " status " << calls[call_idx].status
            << " (" << grpc_core::StringViewFromSlice(calls[call_idx].details)
            << ")";

  CHECK_NE(response_payload_recv, nullptr);
  grpc_byte_buffer_reader reader;
  grpc_byte_buffer_reader_init(&reader, response_payload_recv);
  grpc_slice response = grpc_byte_buffer_reader_readall(&reader);
  MemStats snapshot =
      *reinterpret_cast<MemStats*>(GRPC_SLICE_START_PTR(response));

  grpc_metadata_array_destroy(&calls[call_idx].initial_metadata_recv);
  grpc_metadata_array_destroy(&calls[call_idx].trailing_metadata_recv);
  grpc_slice_unref(response);
  grpc_byte_buffer_reader_destroy(&reader);
  grpc_byte_buffer_destroy(response_payload_recv);
  grpc_slice_unref(calls[call_idx].details);
  calls[call_idx].details = grpc_empty_slice();
  grpc_call_unref(calls[call_idx].call);
  calls[call_idx].call = nullptr;

  return snapshot;
}

std::pair<MemStats, MemStats> run_test_loop(int iterations, int* call_idx) {
  grpc_event event;

  for (int i = 0; i < iterations; ++i) {
    init_ping_pong_request(*call_idx + i + 1);
  }

  auto peak = std::pair(

      MemStats::Snapshot(),

      send_snapshot_request(
          0, grpc_slice_from_static_string("Reflector/DestroyCalls")));

  do {
    event = grpc_completion_queue_next(
        cq,
        gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                     gpr_time_from_micros(10000, GPR_TIMESPAN)),
        nullptr);
  } while (event.type != GRPC_QUEUE_TIMEOUT);

  for (int i = 0; i < iterations; ++i) {
    finish_ping_pong_request(*call_idx + i + 1);
  }

  do {
    event = grpc_completion_queue_next(
        cq,
        gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                     gpr_time_from_micros(10000, GPR_TIMESPAN)),
        nullptr);
  } while (event.type != GRPC_QUEUE_TIMEOUT);

  *call_idx += iterations;

  return peak;
}

ABSL_FLAG(std::string, target, "localhost:443", "Target host:port");
ABSL_FLAG(int, warmup, 100, "Warmup iterations");
ABSL_FLAG(int, benchmark, 1000, "Benchmark iterations");
ABSL_FLAG(bool, minstack, false, "Use minimal stack");
ABSL_FLAG(bool, chaotic_good, false, "Use chaotic good");

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  grpc_slice slice = grpc_slice_from_copied_string("x");
  char* fake_argv[1];

  CHECK_GE(argc, 1);
  fake_argv[0] = argv[0];
  grpc::testing::TestEnvironment env(&argc, argv);

  grpc_init();

  for (size_t k = 0; k < GPR_ARRAY_SIZE(calls); k++) {
    calls[k].details = grpc_empty_slice();
  }

  cq = grpc_completion_queue_create_for_next(nullptr);

  std::vector<grpc_arg> args_vec;
  if (absl::GetFlag(FLAGS_minstack)) {
    args_vec.push_back(grpc_channel_arg_integer_create(
        const_cast<char*>(GRPC_ARG_MINIMAL_STACK), 1));
  }
  const std::string kChaoticGoodWireFormatPreferences(
      grpc_core::chaotic_good::WireFormatPreferences());
  if (absl::GetFlag(FLAGS_chaotic_good)) {
    args_vec.push_back(grpc_channel_arg_integer_create(
        const_cast<char*>(GRPC_ARG_ENABLE_RETRIES), 0));
    args_vec.push_back(grpc_channel_arg_string_create(
        const_cast<char*>(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS),
        const_cast<char*>(kChaoticGoodWireFormatPreferences.c_str())));
  }
  grpc_channel_args args = {args_vec.size(), args_vec.data()};

  channel = grpc_channel_create(absl::GetFlag(FLAGS_target).c_str(),
                                grpc_insecure_credentials_create(), &args);

  int call_idx = 0;
  const int warmup_iterations = absl::GetFlag(FLAGS_warmup);
  const int benchmark_iterations = absl::GetFlag(FLAGS_benchmark);

  MemStats server_benchmark_calls_start = send_snapshot_request(
      0, grpc_slice_from_static_string("Reflector/SimpleSnapshot"));
  MemStats client_benchmark_calls_start = MemStats::Snapshot();

  run_test_loop(warmup_iterations, &call_idx);

  std::pair<MemStats, MemStats> peak =
      run_test_loop(benchmark_iterations, &call_idx);

  MemStats client_calls_inflight = peak.first;
  MemStats server_calls_inflight = peak.second;

  grpc_channel_destroy(channel);
  grpc_completion_queue_shutdown(cq);

  grpc_event event;
  do {
    event = grpc_completion_queue_next(cq, gpr_inf_future(GPR_CLOCK_REALTIME),
                                       nullptr);
  } while (event.type != GRPC_QUEUE_SHUTDOWN);
  grpc_slice_unref(slice);

  grpc_completion_queue_destroy(cq);
  grpc_shutdown_blocking();

  const char* prefix = "";
  if (absl::StartsWith(absl::GetFlag(FLAGS_target), "xds:")) prefix = "xds ";
  printf("---------client stats--------\n");
  printf("%sclient call memory usage: %f bytes per call\n", prefix,
         static_cast<double>(client_calls_inflight.rss -
                             client_benchmark_calls_start.rss) /
             benchmark_iterations * 1024);

  printf("---------server stats--------\n");
  printf("%sserver call memory usage: %f bytes per call\n", prefix,
         static_cast<double>(server_calls_inflight.rss -
                             server_benchmark_calls_start.rss) /
             benchmark_iterations * 1024);

  return 0;
}
