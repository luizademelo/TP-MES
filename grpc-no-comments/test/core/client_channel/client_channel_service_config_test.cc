
// Copyright 2019 gRPC authors.

#include "src/core/client_channel/client_channel_service_config.h"

#include <grpc/grpc.h>
#include <grpc/slice.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/time.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {

#define CHILD_ERROR_TAG ".*children.*"

class ClientChannelParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    parser_index_ =
        CoreConfiguration::Get().service_config_parser().GetParserIndex(
            "client_channel");
  }

  size_t parser_index_;
};

TEST_F(ClientChannelParserTest, ValidLoadBalancingConfigPickFirst) {
  const char* test_json = "{\"loadBalancingConfig\": [{\"pick_first\":{}}]}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* parsed_config =
      static_cast<internal::ClientChannelGlobalParsedConfig*>(
          (*service_config)->GetGlobalParsedConfig(parser_index_));
  auto lb_config = parsed_config->parsed_lb_config();
  EXPECT_EQ(lb_config->name(), "pick_first");
}

TEST_F(ClientChannelParserTest, ValidLoadBalancingConfigRoundRobin) {
  const char* test_json =
      "{\"loadBalancingConfig\": [{\"round_robin\":{}}, {}]}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  auto parsed_config = static_cast<internal::ClientChannelGlobalParsedConfig*>(
      (*service_config)->GetGlobalParsedConfig(parser_index_));
  auto lb_config = parsed_config->parsed_lb_config();
  EXPECT_EQ(lb_config->name(), "round_robin");
}

TEST_F(ClientChannelParserTest, ValidLoadBalancingConfigGrpclb) {
  const char* test_json =
      "{\"loadBalancingConfig\": "
      "[{\"grpclb\":{\"childPolicy\":[{\"pick_first\":{}}]}}]}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* parsed_config =
      static_cast<internal::ClientChannelGlobalParsedConfig*>(
          (*service_config)->GetGlobalParsedConfig(parser_index_));
  auto lb_config = parsed_config->parsed_lb_config();
  EXPECT_EQ(lb_config->name(), "grpclb");
}

TEST_F(ClientChannelParserTest, UnknownLoadBalancingConfig) {
  const char* test_json = "{\"loadBalancingConfig\": [{\"unknown\":{}}]}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "errors validating service config: ["
            "field:loadBalancingConfig error:"
            "No known policies in list: unknown]")
      << service_config.status();
}

TEST_F(ClientChannelParserTest, InvalidGrpclbLoadBalancingConfig) {
  const char* test_json =
      "{\"loadBalancingConfig\": ["
      "  {\"grpclb\":{\"childPolicy\":1}},"
      "  {\"round_robin\":{}}"
      "]}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "errors validating service config: ["
            "field:loadBalancingConfig error:"
            "errors validating grpclb LB policy config: ["
            "field:childPolicy error:type should be array]]")
      << service_config.status();
}

TEST_F(ClientChannelParserTest, ValidLoadBalancingPolicy) {
  const char* test_json = "{\"loadBalancingPolicy\":\"pick_first\"}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* parsed_config =
      static_cast<internal::ClientChannelGlobalParsedConfig*>(
          (*service_config)->GetGlobalParsedConfig(parser_index_));
  EXPECT_EQ(parsed_config->parsed_deprecated_lb_policy(), "pick_first");
}

TEST_F(ClientChannelParserTest, ValidLoadBalancingPolicyAllCaps) {
  const char* test_json = "{\"loadBalancingPolicy\":\"PICK_FIRST\"}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* parsed_config =
      static_cast<internal::ClientChannelGlobalParsedConfig*>(
          (*service_config)->GetGlobalParsedConfig(parser_index_));
  EXPECT_EQ(parsed_config->parsed_deprecated_lb_policy(), "pick_first");
}

TEST_F(ClientChannelParserTest, UnknownLoadBalancingPolicy) {
  const char* test_json = "{\"loadBalancingPolicy\":\"unknown\"}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "errors validating service config: ["
            "field:loadBalancingPolicy error:unknown LB policy \"unknown\"]")
      << service_config.status();
}

TEST_F(ClientChannelParserTest,
       LegacyLoadBalancingPolicySpecifiesPolicyThatRequiresConfig) {
  const char* test_json = "{\"loadBalancingPolicy\":\"rls_experimental\"}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "errors validating service config: ["
            "field:loadBalancingPolicy error:LB policy "
            "\"rls_experimental\" requires a config. Please "
            "use loadBalancingConfig instead.]")
      << service_config.status();
}

TEST_F(ClientChannelParserTest, ValidTimeout) {
  const char* test_json =
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"TestServ\", \"method\": \"TestMethod\" }\n"
      "    ],\n"
      "    \"timeout\": \"5s\"\n"
      "  } ]\n"
      "}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* vector_ptr =
      (*service_config)
          ->GetMethodParsedConfigVector(
              grpc_slice_from_static_string("/TestServ/TestMethod"));
  ASSERT_NE(vector_ptr, nullptr);
  auto parsed_config = ((*vector_ptr)[parser_index_]).get();
  EXPECT_EQ(
      (static_cast<internal::ClientChannelMethodParsedConfig*>(parsed_config))
          ->timeout(),
      Duration::Seconds(5));
}

TEST_F(ClientChannelParserTest, InvalidTimeout) {
  const char* test_json =
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"service\", \"method\": \"method\" }\n"
      "    ],\n"
      "    \"timeout\": \"5sec\"\n"
      "  } ]\n"
      "}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "errors validating service config: ["
            "field:methodConfig[0].timeout "
            "error:Not a duration (no s suffix)]")
      << service_config.status();
}

TEST_F(ClientChannelParserTest, ValidWaitForReady) {
  const char* test_json =
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"TestServ\", \"method\": \"TestMethod\" }\n"
      "    ],\n"
      "    \"waitForReady\": true\n"
      "  } ]\n"
      "}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* vector_ptr =
      (*service_config)
          ->GetMethodParsedConfigVector(
              grpc_slice_from_static_string("/TestServ/TestMethod"));
  ASSERT_NE(vector_ptr, nullptr);
  auto parsed_config = ((*vector_ptr)[parser_index_]).get();
  ASSERT_TRUE(
      (static_cast<internal::ClientChannelMethodParsedConfig*>(parsed_config))
          ->wait_for_ready()
          .has_value());
  EXPECT_TRUE(
      (static_cast<internal::ClientChannelMethodParsedConfig*>(parsed_config))
          ->wait_for_ready()
          .value());
}

TEST_F(ClientChannelParserTest, InvalidWaitForReady) {
  const char* test_json =
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"service\", \"method\": \"method\" }\n"
      "    ],\n"
      "    \"waitForReady\": \"true\"\n"
      "  } ]\n"
      "}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "errors validating service config: ["
            "field:methodConfig[0].waitForReady error:is not a boolean]")
      << service_config.status();
}

TEST_F(ClientChannelParserTest, ValidHealthCheck) {
  const char* test_json =
      "{\n"
      "  \"healthCheckConfig\": {\n"
      "    \"serviceName\": \"health_check_service_name\"\n"
      "    }\n"
      "}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  const auto* parsed_config =
      static_cast<internal::ClientChannelGlobalParsedConfig*>(
          (*service_config)->GetGlobalParsedConfig(parser_index_));
  ASSERT_NE(parsed_config, nullptr);
  EXPECT_EQ(parsed_config->health_check_service_name(),
            "health_check_service_name");
}

TEST_F(ClientChannelParserTest, InvalidHealthCheckMultipleEntries) {
  const char* test_json =
      "{\n"
      "  \"healthCheckConfig\": {\n"
      "    \"serviceName\": \"health_check_service_name\"\n"
      "    },\n"
      "  \"healthCheckConfig\": {\n"
      "    \"serviceName\": \"health_check_service_name1\"\n"
      "    }\n"
      "}";
  auto service_config = ServiceConfigImpl::Create(ChannelArgs(), test_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(service_config.status().message(),
            "JSON parsing failed: ["
            "duplicate key \"healthCheckConfig\" at index 82]")
      << service_config.status();
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
