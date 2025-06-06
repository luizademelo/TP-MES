
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <unordered_map>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/string.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/client_helper.h"
#include "test/cpp/interop/interop_client.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(bool, use_alts, false,
          "Whether to use alts. Enable alts will disable tls.");
ABSL_FLAG(bool, use_tls, false, "Whether to use tls.");
ABSL_FLAG(std::string, custom_credentials_type, "",
          "User provided credentials type.");
ABSL_FLAG(bool, use_test_ca, false, "False to use SSL roots for google");
ABSL_FLAG(int32_t, server_port, 0, "Server port.");
ABSL_FLAG(std::string, server_host, "localhost", "Server host to connect to");
ABSL_FLAG(std::string, server_host_override, "",
          "Override the server host which is sent in HTTP header");
ABSL_FLAG(
    std::string, test_case, "large_unary",
    "Configure different test cases. Valid options are:\n\n"
    "all : all test cases;\n"

);
ABSL_FLAG(std::string, default_service_account, "",
          "Email of GCE default service account");
ABSL_FLAG(std::string, service_account_key_file, "",
          "Path to service account json key file.");
ABSL_FLAG(std::string, oauth_scope, "", "Scope for OAuth tokens.");
ABSL_FLAG(bool, do_not_abort_on_transient_failures, false,
          "If set to 'true', abort() is not called in case of transient "
          "failures (i.e failures that are temporary and will likely go away "
          "on retrying; like a temporary connection failure) and an error "
          "message is printed instead. Note that this flag just controls "
          "whether abort() is called or not. It does not control whether the "
          "test is retried in case of transient failures (and currently the "
          "interop tests are not retried even if this flag is set to true)");
ABSL_FLAG(int32_t, soak_iterations, 1000,
          "The number of iterations to use for the two soak tests; rpc_soak "
          "and channel_soak.");
ABSL_FLAG(int32_t, soak_max_failures, 0,
          "The number of iterations in soak tests that are allowed to fail "
          "(either due to non-OK status code or exceeding the "
          "per-iteration max acceptable latency).");
ABSL_FLAG(int32_t, soak_per_iteration_max_acceptable_latency_ms, 0,
          "The number of milliseconds a single iteration in the two soak "
          "tests (rpc_soak and channel_soak) should take.");
ABSL_FLAG(int32_t, soak_overall_timeout_seconds, 0,
          "The overall number of seconds after which a soak test should "
          "stop and fail, if the desired number of iterations have not yet "
          "completed.");
ABSL_FLAG(int32_t, soak_min_time_ms_between_rpcs, 0,
          "The minimum time in milliseconds between consecutive RPCs in a "
          "soak test (rpc_soak or channel_soak), useful for limiting QPS");
ABSL_FLAG(int32_t, iteration_interval, 10,
          "The interval in seconds between rpcs. This is used by "
          "long_connection test");
ABSL_FLAG(
    int32_t, soak_request_size, 271828,
    "The request size in a soak RPC. "
    "The default value is set based on the interop large unary test case.");
ABSL_FLAG(
    int32_t, soak_response_size, 314159,
    "The response size in a soak RPC. "
    "The default value is set based on the interop large unary test case.");
ABSL_FLAG(std::string, additional_metadata, "",
          "Additional metadata to send in each request, as a "
          "semicolon-separated list of key:value pairs.");
ABSL_FLAG(
    bool, log_metadata_and_status, false,
    "If set to 'true', will print received initial and trailing metadata, "
    "grpc-status and error message to the console, in a stable format.");
ABSL_FLAG(std::string, service_config_json, "",
          "Disables service config lookups and sets the provided string as the "
          "default service config");

using grpc::testing::CreateChannelForTestCase;
using grpc::testing::GetServiceAccountJsonKey;
using grpc::testing::UpdateActions;

namespace {

absl::StatusOr<std::multimap<std::string, std::string>>
ParseAdditionalMetadataFlag(const std::string& flag) {
  std::multimap<std::string, std::string> additional_metadata;
  if (flag.empty()) {
    return additional_metadata;
  }
  size_t start_pos = 0;
  while (start_pos < flag.length()) {
    size_t colon_pos = flag.find(':', start_pos);
    if (colon_pos == std::string::npos) {
      return absl::InvalidArgumentError(
          "Couldn't parse metadata flag: extra characters at end of flag");
    }
    size_t semicolon_pos = flag.find(';', colon_pos);

    std::string key = flag.substr(start_pos, colon_pos - start_pos);
    std::string value =
        flag.substr(colon_pos + 1, semicolon_pos - colon_pos - 1);

    constexpr char alphanum_and_hyphen[] =
        "-0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (key.find_first_not_of(alphanum_and_hyphen) != std::string::npos) {
      return absl::InvalidArgumentError(absl::StrCat(
          "Couldn't parse metadata flag: key contains characters other "
          "than alphanumeric and hyphens: ",
          key));
    }

    for (char& c : key) {
      if (c >= 'A' && c <= 'Z') {
        c += ('a' - 'A');
      }
    }

    LOG(INFO) << "Adding additional metadata with key " << key << " and value "
              << value;
    additional_metadata.insert({key, value});

    if (semicolon_pos == std::string::npos) {
      break;
    } else {
      start_pos = semicolon_pos + 1;
    }
  }

  return additional_metadata;
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  LOG(INFO) << "Testing these cases: " << absl::GetFlag(FLAGS_test_case);
  int ret = 0;

  std::string test_case = absl::GetFlag(FLAGS_test_case);
  auto additional_metadata =
      ParseAdditionalMetadataFlag(absl::GetFlag(FLAGS_additional_metadata));
  if (!additional_metadata.ok()) {
    LOG(ERROR) << additional_metadata.status().message();
    return 1;
  }
  grpc::testing::ChannelCreationFunc channel_creation_func =
      [test_case, &additional_metadata](grpc::ChannelArguments arguments) {
        std::vector<std::unique_ptr<
            grpc::experimental::ClientInterceptorFactoryInterface>>
            factories;
        if (!additional_metadata->empty()) {
          factories.emplace_back(
              new grpc::testing::AdditionalMetadataInterceptorFactory(
                  *additional_metadata));
        }
        if (absl::GetFlag(FLAGS_log_metadata_and_status)) {
          factories.emplace_back(
              new grpc::testing::MetadataAndStatusLoggerInterceptorFactory());
        }
        std::string service_config_json =
            absl::GetFlag(FLAGS_service_config_json);
        if (!service_config_json.empty()) {
          arguments.SetServiceConfigJSON(service_config_json);
        }
        return CreateChannelForTestCase(test_case, std::move(factories),
                                        arguments);
      };

  grpc::testing::InteropClient client(
      channel_creation_func, true,
      absl::GetFlag(FLAGS_do_not_abort_on_transient_failures));

  std::unordered_map<std::string, std::function<bool()>> actions;
  actions["empty_unary"] =
      std::bind(&grpc::testing::InteropClient::DoEmpty, &client);
  actions["large_unary"] =
      std::bind(&grpc::testing::InteropClient::DoLargeUnary, &client);
  actions["server_compressed_unary"] = std::bind(
      &grpc::testing::InteropClient::DoServerCompressedUnary, &client);
  actions["client_compressed_unary"] = std::bind(
      &grpc::testing::InteropClient::DoClientCompressedUnary, &client);
  actions["client_streaming"] =
      std::bind(&grpc::testing::InteropClient::DoRequestStreaming, &client);
  actions["server_streaming"] =
      std::bind(&grpc::testing::InteropClient::DoResponseStreaming, &client);
  actions["server_compressed_streaming"] = std::bind(
      &grpc::testing::InteropClient::DoServerCompressedStreaming, &client);
  actions["client_compressed_streaming"] = std::bind(
      &grpc::testing::InteropClient::DoClientCompressedStreaming, &client);
  actions["slow_consumer"] = std::bind(
      &grpc::testing::InteropClient::DoResponseStreamingWithSlowConsumer,
      &client);
  actions["half_duplex"] =
      std::bind(&grpc::testing::InteropClient::DoHalfDuplex, &client);
  actions["ping_pong"] =
      std::bind(&grpc::testing::InteropClient::DoPingPong, &client);
  actions["cancel_after_begin"] =
      std::bind(&grpc::testing::InteropClient::DoCancelAfterBegin, &client);
  actions["cancel_after_first_response"] = std::bind(
      &grpc::testing::InteropClient::DoCancelAfterFirstResponse, &client);
  actions["timeout_on_sleeping_server"] = std::bind(
      &grpc::testing::InteropClient::DoTimeoutOnSleepingServer, &client);
  actions["empty_stream"] =
      std::bind(&grpc::testing::InteropClient::DoEmptyStream, &client);
  actions["pick_first_unary"] =
      std::bind(&grpc::testing::InteropClient::DoPickFirstUnary, &client);
  actions["orca_per_rpc"] =
      std::bind(&grpc::testing::InteropClient::DoOrcaPerRpc, &client);
  actions["orca_oob"] =
      std::bind(&grpc::testing::InteropClient::DoOrcaOob, &client);
  if (absl::GetFlag(FLAGS_use_tls)) {
    actions["compute_engine_creds"] =
        std::bind(&grpc::testing::InteropClient::DoComputeEngineCreds, &client,
                  absl::GetFlag(FLAGS_default_service_account),
                  absl::GetFlag(FLAGS_oauth_scope));
    actions["jwt_token_creds"] =
        std::bind(&grpc::testing::InteropClient::DoJwtTokenCreds, &client,
                  GetServiceAccountJsonKey());
    actions["oauth2_auth_token"] =
        std::bind(&grpc::testing::InteropClient::DoOauth2AuthToken, &client,
                  absl::GetFlag(FLAGS_default_service_account),
                  absl::GetFlag(FLAGS_oauth_scope));
    actions["per_rpc_creds"] =
        std::bind(&grpc::testing::InteropClient::DoPerRpcCreds, &client,
                  GetServiceAccountJsonKey());
  }
  if (absl::GetFlag(FLAGS_custom_credentials_type) ==
      "google_default_credentials") {
    actions["google_default_credentials"] =
        std::bind(&grpc::testing::InteropClient::DoGoogleDefaultCredentials,
                  &client, absl::GetFlag(FLAGS_default_service_account));
  }
  actions["status_code_and_message"] =
      std::bind(&grpc::testing::InteropClient::DoStatusWithMessage, &client);
  actions["special_status_message"] =
      std::bind(&grpc::testing::InteropClient::DoSpecialStatusMessage, &client);
  actions["custom_metadata"] =
      std::bind(&grpc::testing::InteropClient::DoCustomMetadata, &client);
  actions["unimplemented_method"] =
      std::bind(&grpc::testing::InteropClient::DoUnimplementedMethod, &client);
  actions["unimplemented_service"] =
      std::bind(&grpc::testing::InteropClient::DoUnimplementedService, &client);
  actions["channel_soak"] = std::bind(
      &grpc::testing::InteropClient::DoChannelSoakTest, &client,
      absl::GetFlag(FLAGS_server_host), absl::GetFlag(FLAGS_soak_iterations),
      absl::GetFlag(FLAGS_soak_max_failures),
      absl::GetFlag(FLAGS_soak_per_iteration_max_acceptable_latency_ms),
      absl::GetFlag(FLAGS_soak_min_time_ms_between_rpcs),
      absl::GetFlag(FLAGS_soak_overall_timeout_seconds),
      absl::GetFlag(FLAGS_soak_request_size),
      absl::GetFlag(FLAGS_soak_response_size));
  actions["rpc_soak"] = std::bind(
      &grpc::testing::InteropClient::DoRpcSoakTest, &client,
      absl::GetFlag(FLAGS_server_host), absl::GetFlag(FLAGS_soak_iterations),
      absl::GetFlag(FLAGS_soak_max_failures),
      absl::GetFlag(FLAGS_soak_per_iteration_max_acceptable_latency_ms),
      absl::GetFlag(FLAGS_soak_min_time_ms_between_rpcs),
      absl::GetFlag(FLAGS_soak_overall_timeout_seconds),
      absl::GetFlag(FLAGS_soak_request_size),
      absl::GetFlag(FLAGS_soak_response_size));
  actions["long_lived_channel"] =
      std::bind(&grpc::testing::InteropClient::DoLongLivedChannelTest, &client,
                absl::GetFlag(FLAGS_soak_iterations),
                absl::GetFlag(FLAGS_iteration_interval));

  UpdateActions(&actions);

  if (absl::GetFlag(FLAGS_test_case) == "all") {
    for (const auto& action : actions) {
      action.second();
    }
  } else if (actions.find(absl::GetFlag(FLAGS_test_case)) != actions.end()) {
    actions.find(absl::GetFlag(FLAGS_test_case))->second();
  } else {
    std::string test_cases;
    for (const auto& action : actions) {
      if (!test_cases.empty()) test_cases += "\n";
      test_cases += action.first;
    }
    LOG(ERROR) << "Unsupported test case " << absl::GetFlag(FLAGS_test_case)
               << ". Valid options are\n"
               << test_cases;
    ret = 1;
  }

  return ret;
}
