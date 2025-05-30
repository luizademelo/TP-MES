
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/csm/csm_observability.h"

#include <grpcpp/ext/csm_observability.h>
#include <grpcpp/ext/otel_plugin.h>

#include "google/cloud/opentelemetry/resource_detector.h"
#include "gtest/gtest.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "src/core/xds/grpc/xds_enabled_server.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace testing {
namespace {

TEST(CsmObservabilityBuilderTest, Basic) {
  EXPECT_EQ(
      CsmObservabilityBuilder()
          .SetMeterProvider(
              std::make_shared<opentelemetry::sdk::metrics::MeterProvider>())
          .BuildAndRegister()
          .status(),
      absl::OkStatus());
}

TEST(CsmDependencyTest, GoogleCloudOpenTelemetryDependency) {
  EXPECT_NE(google::cloud::otel::MakeResourceDetector(), nullptr);
}

TEST(CsmChannelTargetSelectorTest, NonXdsTargets) {
  auto obs = CsmObservabilityBuilder().BuildAndRegister();
  EXPECT_FALSE(internal::CsmChannelTargetSelector("foo.bar.google.com"));
  EXPECT_FALSE(internal::CsmChannelTargetSelector("dns:///foo.bar.google.com"));
  EXPECT_FALSE(
      internal::CsmChannelTargetSelector("dns:///foo.bar.google.com:1234"));
  EXPECT_FALSE(internal::CsmChannelTargetSelector(
      "dns://authority/foo.bar.google.com:1234"));
}

TEST(CsmChannelTargetSelectorTest, XdsTargets) {
  auto obs = CsmObservabilityBuilder().BuildAndRegister();
  EXPECT_TRUE(internal::CsmChannelTargetSelector("xds:///foo"));
  EXPECT_TRUE(internal::CsmChannelTargetSelector("xds:///foo.bar"));
}

TEST(CsmChannelTargetSelectorTest, XdsTargetsWithNonTDAuthority) {
  auto obs = CsmObservabilityBuilder().BuildAndRegister();
  EXPECT_FALSE(internal::CsmChannelTargetSelector("xds://authority/foo"));
}

TEST(CsmChannelTargetSelectorTest, XdsTargetsWithTDAuthority) {
  auto obs = CsmObservabilityBuilder().BuildAndRegister();
  EXPECT_TRUE(internal::CsmChannelTargetSelector(
      "xds://traffic-director-global.xds.googleapis.com/foo"));
}

TEST(CsmChannelTargetSelectorTest, CsmObservabilityOutOfScope) {
  {
    auto obs =
        CsmObservabilityBuilder()
            .SetMeterProvider(
                std::make_shared<opentelemetry::sdk::metrics::MeterProvider>())
            .BuildAndRegister();
  }

  EXPECT_FALSE(internal::CsmChannelTargetSelector("foo.bar.google.com"));
  EXPECT_FALSE(internal::CsmChannelTargetSelector("xds:///foo"));
  EXPECT_FALSE(internal::CsmChannelTargetSelector(
      "xds://traffic-director-global.xds.googleapis.com/foo"));
}

TEST(CsmServerSelectorTest, ChannelArgs) {
  auto obs = CsmObservabilityBuilder().BuildAndRegister();
  EXPECT_TRUE(internal::CsmServerSelector(grpc_core::ChannelArgs()));
}

TEST(CsmServerSelectorTest, CsmObservabilityOutOfScope) {
  {
    auto obs =
        CsmObservabilityBuilder()
            .SetMeterProvider(
                std::make_shared<opentelemetry::sdk::metrics::MeterProvider>())
            .BuildAndRegister();
  }

  EXPECT_FALSE(internal::CsmServerSelector(grpc_core::ChannelArgs()));
  EXPECT_FALSE(internal::CsmServerSelector(
      grpc_core::ChannelArgs().Set(GRPC_ARG_XDS_ENABLED_SERVER, true)));
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
