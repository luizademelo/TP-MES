
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>

#include <memory>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_split.h"
#include "src/core/util/string.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/client_helper.h"
#include "test/cpp/interop/interop_client.h"
#include "test/cpp/util/create_test_channel.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(std::string, server_uris, "",
          "Comma-separated list of sever URIs to make RPCs to");
ABSL_FLAG(std::string, credentials_types, "",
          "Comma-separated list of credentials, each entry is used for the "
          "server of the corresponding index in server_uris. Supported values: "
          "compute_engine_channel_creds, INSECURE_CREDENTIALS");
ABSL_FLAG(int32_t, soak_iterations, 10,
          "The number of iterations to use for the two soak tests: rpc_soak "
          "and channel_soak");
ABSL_FLAG(int32_t, soak_max_failures, 0,
          "The number of iterations in soak tests that are allowed to fail "
          "(either due to non-OK status code or exceeding the per-iteration "
          "max acceptable latency).");
ABSL_FLAG(int32_t, soak_per_iteration_max_acceptable_latency_ms, 1000,
          "The number of milliseconds a single iteration in the two soak tests "
          "(rpc_soak and channel_soak) should take.");
ABSL_FLAG(
    int32_t, soak_overall_timeout_seconds, 10,
    "The overall number of seconds after which a soak test should stop and "
    "fail, if the desired number of iterations have not yet completed.");
ABSL_FLAG(int32_t, soak_min_time_ms_between_rpcs, 0,
          "The minimum time in milliseconds between consecutive RPCs in a soak "
          "test (rpc_soak or channel_soak), useful for limiting QPS");
ABSL_FLAG(
    int32_t, soak_request_size, 271828,
    "The request size in a soak RPC. "
    "The default value is set based on the interop large unary test case.");
ABSL_FLAG(
    int32_t, soak_response_size, 314159,
    "The response size in a soak RPCi. "
    "The default value is set based on the interop large unary test case.");
ABSL_FLAG(std::string, test_case, "rpc_soak",
          "Configure different test cases. Valid options are: "
          "rpc_soak: sends --soak_iterations large_unary RPCs; "
          "channel_soak: sends --soak_iterations RPCs, rebuilding the channel "
          "each time");

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  LOG(INFO) << "Testing these cases: " << absl::GetFlag(FLAGS_test_case);
  std::string test_case = absl::GetFlag(FLAGS_test_case);

  std::vector<std::string> uris =
      absl::StrSplit(absl::GetFlag(FLAGS_server_uris), ',');
  std::vector<std::string> creds =
      absl::StrSplit(absl::GetFlag(FLAGS_credentials_types), ',');
  if (uris.size() != creds.size()) {
    LOG(ERROR) << "Number of entries in --server_uris " << uris.size()
               << " != number of entries in --credentials_types "
               << creds.size();
    CHECK(0);
  }
  if (uris.empty()) {
    LOG(ERROR) << "--server_uris has zero entries";
    CHECK(0);
  }

  std::vector<std::thread> threads;
  for (size_t i = 0; i < uris.size(); i++) {
    threads.push_back(std::thread([uris, creds, i, test_case]() {
      auto channel_creation_func = [uris, creds, i](grpc::ChannelArguments) {
        return grpc::CreateTestChannel(uris[i], creds[i],
                                       nullptr );
      };
      grpc::testing::InteropClient client(channel_creation_func, true, false);
      if (test_case == "rpc_soak") {
        client.DoRpcSoakTest(
            uris[i], absl::GetFlag(FLAGS_soak_iterations),
            absl::GetFlag(FLAGS_soak_max_failures),
            absl::GetFlag(FLAGS_soak_per_iteration_max_acceptable_latency_ms),
            absl::GetFlag(FLAGS_soak_min_time_ms_between_rpcs),
            absl::GetFlag(FLAGS_soak_overall_timeout_seconds),
            absl::GetFlag(FLAGS_soak_request_size),
            absl::GetFlag(FLAGS_soak_response_size));
      } else if (test_case == "channel_soak") {
        client.DoChannelSoakTest(
            uris[i], absl::GetFlag(FLAGS_soak_iterations),
            absl::GetFlag(FLAGS_soak_max_failures),
            absl::GetFlag(FLAGS_soak_per_iteration_max_acceptable_latency_ms),
            absl::GetFlag(FLAGS_soak_min_time_ms_between_rpcs),
            absl::GetFlag(FLAGS_soak_overall_timeout_seconds),
            absl::GetFlag(FLAGS_soak_request_size),
            absl::GetFlag(FLAGS_soak_response_size));
      } else {
        LOG(ERROR)
            << "Invalid test case, must be either rpc_soak or channel_soak";
        CHECK(0);
      }
    }));
  }
  for (auto& thd : threads) {
    thd.join();
  }
  LOG(INFO) << "All clients done!";
  return 0;
}
