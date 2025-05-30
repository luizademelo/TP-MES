
// Copyright 2023 gRPC authors.

#include <grpc++/grpc++.h>
#include <grpcpp/opencensus.h>

#include <string>
#include <thread>
#include <vector>

#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "opencensus/stats/stats.h"
#include "opencensus/stats/testing/test_utils.h"
#include "opencensus/tags/tag_map.h"
#include "src/cpp/ext/filters/census/context.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/ext/filters/census/library.h"

namespace grpc {
namespace testing {

namespace {

using ::opencensus::stats::View;
using ::opencensus::stats::testing::TestUtils;

class ConstantLabelsTest : public StatsPluginEnd2EndTest {
 protected:
  static void SetUpTestSuite() {
    grpc::internal::OpenCensusRegistry::Get().RegisterConstantLabels(
        {{"key", "value"}});
    grpc::internal::OpenCensusRegistry::Get().RegisterConstantAttributes(
        {{"key", "value"}});
    StatsPluginEnd2EndTest::SetUpTestSuite();
  }
};

TEST_F(ConstantLabelsTest, ConstantLabelsTest) {
  View client_completed_rpcs_view(ClientCompletedRpcsCumulative());
  View server_completed_rpcs_view(ServerCompletedRpcsCumulative());

  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;

  {
    grpc::ClientContext context;
    grpc::Status status = stub_->Echo(&context, request, &response);
    ASSERT_TRUE(status.ok());
    EXPECT_EQ("foo", response.message());
  }

  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();

  EXPECT_THAT(
      client_completed_rpcs_view.GetData().int_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre("value", client_method_name_, "OK"), 1)));
  EXPECT_THAT(
      server_completed_rpcs_view.GetData().int_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre("value", server_method_name_, "OK"), 1)));
}

TEST_F(ConstantLabelsTest, ConstantAttributesTest) {
  {

    auto channel = CreateChannel(server_address_, InsecureChannelCredentials());
    ResetStub(channel);
    EchoRequest request;
    request.set_message("foo");
    EchoResponse response;

    grpc::ClientContext context;
    ::opencensus::trace::AlwaysSampler always_sampler;
    ::opencensus::trace::StartSpanOptions options;
    options.sampler = &always_sampler;
    auto sampling_span =
        ::opencensus::trace::Span::StartSpan("sampling", nullptr, options);
    grpc::CensusContext app_census_context("root", &sampling_span,
                                           ::opencensus::tags::TagMap{});
    context.set_census_context(
        reinterpret_cast<census_context*>(&app_census_context));
    context.AddMetadata(kExpectedTraceIdKey,
                        app_census_context.Span().context().trace_id().ToHex());
    traces_recorder_->StartRecording();
    grpc::Status status = stub_->Echo(&context, request, &response);
    EXPECT_TRUE(status.ok());
  }
  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();
  ::opencensus::trace::exporter::SpanExporterTestPeer::ExportForTesting();
  traces_recorder_->StopRecording();
  auto recorded_spans = traces_recorder_->GetAndClearSpans();

  for (const auto& span : recorded_spans) {
    bool found = false;
    for (const auto& attribute : span.attributes()) {
      if (attribute.first == "key" &&
          attribute.second.string_value() == "value") {
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found);
  }
}

}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
