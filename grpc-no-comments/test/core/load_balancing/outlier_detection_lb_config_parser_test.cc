
// Copyright 2022 gRPC authors.

#include <grpc/grpc.h>

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class OutlierDetectionConfigParsingTest : public ::testing::Test {
 public:
  static void SetUpTestSuite() { grpc_init(); }

  static void TearDownTestSuite() { grpc_shutdown_blocking(); }
};

TEST_F(OutlierDetectionConfigParsingTest, ValidConfig) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"outlier_detection_experimental\":{\n"
      "      \"interval\":\"1.2s\",\n"
      "      \"baseEjectionTime\":\"2.3s\",\n"
      "      \"maxEjectionTime\":\"3.4s\",\n"
      "      \"maxEjectionPercent\":3,\n"
      "      \"successRateEjection\":{\n"
      "        \"stdevFactor\":1,\n"
      "        \"enforcementPercentage\":2,\n"
      "        \"minimumHosts\":3,\n"
      "        \"requestVolume\":4\n"
      "      },\n"
      "      \"failurePercentageEjection\":{\n"
      "        \"threshold\":1,\n"
      "        \"enforcementPercentage\":2,\n"
      "        \"minimumHosts\":3,\n"
      "        \"requestVolume\":4\n"
      "      },\n"
      "      \"childPolicy\":[\n"
      "        {\"unknown\":{}},\n"
      "        {\"grpclb\":{}}\n"
      "      ]\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  ASSERT_TRUE(service_config.ok()) << service_config.status();
  EXPECT_NE(*service_config, nullptr);
}

TEST_F(OutlierDetectionConfigParsingTest, InvalidValues) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"outlier_detection_experimental\":{\n"
      "      \"interval\":\"-1s\",\n"
      "      \"baseEjectionTime\":\"315576000001s\",\n"
      "      \"maxEjectionTime\":\"-3.4s\",\n"
      "      \"maxEjectionPercent\":101,\n"
      "      \"successRateEjection\":{\n"
      "        \"enforcementPercentage\":101\n"
      "      },\n"
      "      \"failurePercentageEjection\":{\n"
      "        \"threshold\":101,\n"
      "        \"enforcementPercentage\":101\n"
      "      },\n"
      "      \"childPolicy\":[\n"
      "        {\"unknown\":{}}\n"
      "      ]\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(service_config.status().message(),
              ::testing::HasSubstr(
                  "errors validating outlier_detection LB policy config: ["
                  "field:baseEjectionTime "
                  "error:seconds must be in the range [0, 315576000000]; "
                  "field:childPolicy error:No known policies in list: unknown; "
                  "field:failurePercentageEjection.enforcement_percentage "
                  "error:value must be <= 100; "
                  "field:failurePercentageEjection.threshold "
                  "error:value must be <= 100; "
                  "field:interval "
                  "error:seconds must be in the range [0, 315576000000]; "
                  "field:maxEjectionTime "
                  "error:seconds must be in the range [0, 315576000000]; "
                  "field:max_ejection_percent error:value must be <= 100; "
                  "field:successRateEjection.enforcement_percentage "
                  "error:value must be <= 100]"))
      << service_config.status();
}

TEST_F(OutlierDetectionConfigParsingTest, MissingChildPolicyField) {
  const char* service_config_json =
      "{\n"
      "  \"loadBalancingConfig\":[{\n"
      "    \"outlier_detection_experimental\":{\n"
      "      \"interval\":\"1.2s\",\n"
      "      \"baseEjectionTime\":\"2.3s\",\n"
      "      \"maxEjectionTime\":\"3.4s\",\n"
      "      \"maxEjectionPercent\":3,\n"
      "      \"successRateEjection\":{\n"
      "        \"stdevFactor\":1,\n"
      "        \"enforcementPercentage\":2,\n"
      "        \"minimumHosts\":3,\n"
      "        \"requestVolume\":4\n"
      "      },\n"
      "      \"failurePercentageEjection\":{\n"
      "        \"threshold\":1,\n"
      "        \"enforcementPercentage\":2,\n"
      "        \"minimumHosts\":3,\n"
      "        \"requestVolume\":4\n"
      "      }\n"
      "    }\n"
      "  }]\n"
      "}\n";
  auto service_config =
      ServiceConfigImpl::Create(ChannelArgs(), service_config_json);
  EXPECT_EQ(service_config.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(service_config.status().message(),
              ::testing::HasSubstr(
                  "errors validating outlier_detection LB policy config: ["
                  "field:childPolicy error:field not present]"))
      << service_config.status();
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
