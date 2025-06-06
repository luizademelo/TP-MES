
// Copyright 2022 gRPC authors.

#include <grpc/grpc.h>

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gtest/gtest.h"
#include "src/core/client_channel/client_channel_service_config.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/load_balancing/xds/xds_override_host.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/xds/grpc/xds_health_status.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

using internal::ClientChannelGlobalParsedConfig;
using internal::ClientChannelServiceConfigParser;

TEST(XdsOverrideHostConfigParsingTest, ValidConfig) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"xds_override_host_experimental\":{\n"
      "      \"clusterName\": \"foo\",\n"
      "      \"childPolicy\":[\n"
      "        {\"grpclb\":{}}\n"
      "      ]\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  EXPECT_NE(*service_config, nullptr);
  auto global_config = static_cast<ClientChannelGlobalParsedConfig*>(
      (*service_config)
          ->GetGlobalParsedConfig(
              ClientChannelServiceConfigParser::ParserIndex()));
  ASSERT_NE(global_config, nullptr);
  auto lb_config = global_config->parsed_lb_config();
  ASSERT_NE(lb_config, nullptr);
  ASSERT_EQ(lb_config->name(), XdsOverrideHostLbConfig::Name());
  auto* override_host_lb_config =
      static_cast<XdsOverrideHostLbConfig*>(lb_config.get());
  EXPECT_EQ(override_host_lb_config->cluster_name(), "foo");
  ASSERT_NE(override_host_lb_config->child_config(), nullptr);
  EXPECT_EQ(override_host_lb_config->child_config()->name(), "grpclb");
}

TEST(XdsOverrideHostConfigParsingTest, ValidConfigWithRR) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"xds_override_host_experimental\":{\n"
      "      \"clusterName\": \"foo\",\n"
      "      \"childPolicy\":[\n"
      "        {\"round_robin\":{}}\n"
      "      ]\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_TRUE(service_config.ok());
  EXPECT_NE(*service_config, nullptr);
  auto global_config = static_cast<ClientChannelGlobalParsedConfig*>(
      (*service_config)
          ->GetGlobalParsedConfig(
              ClientChannelServiceConfigParser::ParserIndex()));
  ASSERT_NE(global_config, nullptr);
  auto lb_config = global_config->parsed_lb_config();
  ASSERT_NE(lb_config, nullptr);
  ASSERT_EQ(lb_config->name(), XdsOverrideHostLbConfig::Name());
  auto* override_host_lb_config =
      static_cast<XdsOverrideHostLbConfig*>(lb_config.get());
  EXPECT_EQ(override_host_lb_config->cluster_name(), "foo");
  ASSERT_NE(override_host_lb_config->child_config(), nullptr);
  EXPECT_EQ(override_host_lb_config->child_config()->name(), "round_robin");
}

TEST(XdsOverrideHostConfigParsingTest, MissingClusterName) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"xds_override_host_experimental\":{\n"
      "      \"childPolicy\":[\n"
      "        {\"round_robin\":{}}\n"
      "      ]\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_FALSE(service_config.ok());
  EXPECT_EQ(service_config.status(),
            absl::InvalidArgumentError(
                "errors validating service config: [field:loadBalancingConfig "
                "error:errors validating xds_override_host LB policy config: "
                "[field:clusterName error:field not present]]"));
}

TEST(XdsOverrideHostConfigParsingTest, ReportsMissingChildPolicyField) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"xds_override_host_experimental\":{\n"
      "      \"clusterName\": \"foo\"\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_FALSE(service_config.ok());
  EXPECT_EQ(service_config.status(),
            absl::InvalidArgumentError(
                "errors validating service config: [field:loadBalancingConfig "
                "error:errors validating xds_override_host LB policy config: "
                "[field:childPolicy error:field not present]]"));
}

TEST(XdsOverrideHostConfigParsingTest, ReportsChildPolicyShouldBeArray) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"xds_override_host_experimental\":{\n"
      "      \"clusterName\": \"foo\",\n"
      "      \"childPolicy\":{\n"
      "        \"grpclb\":{}\n"
      "      }\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_FALSE(service_config.ok()) << service_config.status();
  EXPECT_EQ(service_config.status(),
            absl::InvalidArgumentError(
                "errors validating service config: [field:loadBalancingConfig "
                "error:errors validating xds_override_host LB policy config: "
                "[field:childPolicy error:type should be array]]"));
}

TEST(XdsOverrideHostConfigParsingTest, ReportsEmptyChildPolicyArray) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"xds_override_host_experimental\":{\n"
      "      \"clusterName\": \"foo\",\n"
      "      \"childPolicy\":[\n"
      "      ]\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_FALSE(service_config.ok()) << service_config.status();
  EXPECT_EQ(service_config.status(),
            absl::InvalidArgumentError(
                "errors validating service config: [field:loadBalancingConfig "
                "error:errors validating xds_override_host LB policy config: "
                "[field:childPolicy error:No known policies in list: ]]"));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
