
// Copyright 2022 gRPC authors.

#include "src/cpp/ext/gcp/observability_logging_sink.h"

#include "absl/strings/escaping.h"
#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "google/protobuf/text_format.h"
#include "gtest/gtest.h"
#include "src/core/util/json/json_reader.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace internal {

namespace {

using grpc_core::LoggingSink;

TEST(GcpObservabilityLoggingSinkTest, LoggingConfigEmpty) {
  const char* json_str = R"json({
      "cloud_logging": {
      }
    })json";
  auto json = grpc_core::JsonParse(json_str);
  ASSERT_TRUE(json.ok()) << json.status();
  grpc_core::ValidationErrors errors;
  auto config = grpc_core::LoadFromJson<GcpObservabilityConfig>(
      *json, grpc_core::JsonArgs(), &errors);
  ASSERT_TRUE(errors.ok()) << errors.status(absl::StatusCode::kInvalidArgument,
                                            "unexpected errors");
  ObservabilityLoggingSink sink(config.cloud_logging.value(), "test", {});

  EXPECT_FALSE(sink.FindMatch(true, "foo", "bar").ShouldLog());

  EXPECT_FALSE(sink.FindMatch(false, "foo", "bar").ShouldLog());
}

TEST(GcpObservabilityLoggingSinkTest, LoggingConfigClientWildCardEntries) {
  const char* json_str = R"json({
      "cloud_logging": {
        "client_rpc_events": [
          {
            "methods": ["*"],
            "max_metadata_bytes": 1024,
            "max_message_bytes": 4096
          }
        ]
      }
    })json";
  auto json = grpc_core::JsonParse(json_str);
  ASSERT_TRUE(json.ok()) << json.status();
  grpc_core::ValidationErrors errors;
  auto config = grpc_core::LoadFromJson<GcpObservabilityConfig>(
      *json, grpc_core::JsonArgs(), &errors);
  ASSERT_TRUE(errors.ok()) << errors.status(absl::StatusCode::kInvalidArgument,
                                            "unexpected errors");
  ObservabilityLoggingSink sink(config.cloud_logging.value(), "test", {});

  EXPECT_EQ(sink.FindMatch(true, "foo", "bar"),
            LoggingSink::Config(1024, 4096));

  EXPECT_FALSE(sink.FindMatch(false, "foo", "bar").ShouldLog());
}

TEST(GcpObservabilityLoggingSinkTest, LoggingConfigBadPath) {
  const char* json_str = R"json({
      "cloud_logging": {
        "client_rpc_events": [
          {
            "methods": ["*"],
            "max_metadata_bytes": 1024,
            "max_message_bytes": 4096
          }
        ]
      }
    })json";
  auto json = grpc_core::JsonParse(json_str);
  ASSERT_TRUE(json.ok()) << json.status();
  grpc_core::ValidationErrors errors;
  auto config = grpc_core::LoadFromJson<GcpObservabilityConfig>(
      *json, grpc_core::JsonArgs(), &errors);
  ASSERT_TRUE(errors.ok()) << errors.status(absl::StatusCode::kInvalidArgument,
                                            "unexpected errors");
  ObservabilityLoggingSink sink(config.cloud_logging.value(), "test", {});
  EXPECT_FALSE(sink.FindMatch(true, "foo", "").ShouldLog());
}

TEST(GcpObservabilityLoggingSinkTest,
     LoggingConfigClientWildCardServiceEntries) {
  const char* json_str = R"json({
      "cloud_logging": {
        "client_rpc_events": [
          {
            "methods": ["service
