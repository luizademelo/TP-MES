
// Copyright 2018 gRPC authors.

#include <grpc++/grpc++.h>
#include <grpcpp/opencensus.h>

#include <string>
#include <thread>
#include <vector>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "opencensus/stats/stats.h"
#include "opencensus/stats/testing/test_utils.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/tags/with_tag_map.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/cpp/ext/filters/census/context.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"
#include "src/cpp/ext/filters/census/open_census_call_tracer.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/ext/filters/census/library.h"

namespace grpc {
namespace testing {
namespace {

using ::opencensus::stats::Aggregation;
using ::opencensus::stats::Distribution;
using ::opencensus::stats::View;
using ::opencensus::stats::ViewDescriptor;
using ::opencensus::stats::testing::TestUtils;
using ::opencensus::tags::WithTagMap;

TEST_F(StatsPluginEnd2EndTest, ErrorCount) {
  const auto client_method_descriptor =
      ViewDescriptor()
          .set_measure(kRpcClientRoundtripLatencyMeasureName)
          .set_name("client_method")
          .set_aggregation(Aggregation::Count())
          .add_column(ClientMethodTagKey())
          .add_column(TEST_TAG_KEY);
  View client_method_view(client_method_descriptor);
  const auto server_method_descriptor =
      ViewDescriptor()
          .set_measure(kRpcServerServerLatencyMeasureName)
          .set_name("server_method")
          .set_aggregation(Aggregation::Count())
          .add_column(ServerMethodTagKey());

  View server_method_view(server_method_descriptor);

  const auto client_status_descriptor =
      ViewDescriptor()
          .set_measure(kRpcClientRoundtripLatencyMeasureName)
          .set_name("client_status")
          .set_aggregation(Aggregation::Count())
          .add_column(ClientStatusTagKey())
          .add_column(TEST_TAG_KEY);
  View client_status_view(client_status_descriptor);
  const auto server_status_descriptor =
      ViewDescriptor()
          .set_measure(kRpcServerServerLatencyMeasureName)
          .set_name("server_status")
          .set_aggregation(Aggregation::Count())
          .add_column(ServerStatusTagKey());
  View server_status_view(server_status_descriptor);

  for (int i = 0; i <= 16; ++i) {
    EchoRequest request;
    request.set_message("foo");
    request.mutable_param()->mutable_expected_error()->set_code(i);
    EchoResponse response;
    grpc::ClientContext context;
    {
      WithTagMap tags({{TEST_TAG_KEY, TEST_TAG_VALUE}});
      grpc::Status status = stub_->Echo(&context, request, &response);
    }
  }
  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();

  EXPECT_THAT(
      client_method_view.GetData().int_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre(client_method_name_, TEST_TAG_VALUE), 17)));

  EXPECT_THAT(server_method_view.GetData().int_data(),
              ::testing::UnorderedElementsAre(::testing::Pair(
                  ::testing::ElementsAre(server_method_name_), 17)));

  auto client_tags = {
      ::testing::Pair(::testing::ElementsAre("OK", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("CANCELLED", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("UNKNOWN", TEST_TAG_VALUE), 1),
      ::testing::Pair(
          ::testing::ElementsAre("INVALID_ARGUMENT", TEST_TAG_VALUE), 1),
      ::testing::Pair(
          ::testing::ElementsAre("DEADLINE_EXCEEDED", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("NOT_FOUND", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("ALREADY_EXISTS", TEST_TAG_VALUE),
                      1),
      ::testing::Pair(
          ::testing::ElementsAre("PERMISSION_DENIED", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("UNAUTHENTICATED", TEST_TAG_VALUE),
                      1),
      ::testing::Pair(
          ::testing::ElementsAre("RESOURCE_EXHAUSTED", TEST_TAG_VALUE), 1),
      ::testing::Pair(
          ::testing::ElementsAre("FAILED_PRECONDITION", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("ABORTED", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("OUT_OF_RANGE", TEST_TAG_VALUE),
                      1),
      ::testing::Pair(::testing::ElementsAre("UNIMPLEMENTED", TEST_TAG_VALUE),
                      1),
      ::testing::Pair(::testing::ElementsAre("INTERNAL", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("UNAVAILABLE", TEST_TAG_VALUE), 1),
      ::testing::Pair(::testing::ElementsAre("DATA_LOSS", TEST_TAG_VALUE), 1),
  };

  auto server_tags = {
      ::testing::Pair(::testing::ElementsAre("OK"), 1),
      ::testing::Pair(::testing::ElementsAre("CANCELLED"), 1),
      ::testing::Pair(::testing::ElementsAre("UNKNOWN"), 1),
      ::testing::Pair(::testing::ElementsAre("INVALID_ARGUMENT"), 1),
      ::testing::Pair(::testing::ElementsAre("DEADLINE_EXCEEDED"), 1),
      ::testing::Pair(::testing::ElementsAre("NOT_FOUND"), 1),
      ::testing::Pair(::testing::ElementsAre("ALREADY_EXISTS"), 1),
      ::testing::Pair(::testing::ElementsAre("PERMISSION_DENIED"), 1),
      ::testing::Pair(::testing::ElementsAre("UNAUTHENTICATED"), 1),
      ::testing::Pair(::testing::ElementsAre("RESOURCE_EXHAUSTED"), 1),
      ::testing::Pair(::testing::ElementsAre("FAILED_PRECONDITION"), 1),
      ::testing::Pair(::testing::ElementsAre("ABORTED"), 1),
      ::testing::Pair(::testing::ElementsAre("OUT_OF_RANGE"), 1),
      ::testing::Pair(::testing::ElementsAre("UNIMPLEMENTED"), 1),
      ::testing::Pair(::testing::ElementsAre("INTERNAL"), 1),
      ::testing::Pair(::testing::ElementsAre("UNAVAILABLE"), 1),
      ::testing::Pair(::testing::ElementsAre("DATA_LOSS"), 1),
  };

  EXPECT_THAT(client_status_view.GetData().int_data(),
              ::testing::UnorderedElementsAreArray(client_tags));
  EXPECT_THAT(server_status_view.GetData().int_data(),
              ::testing::UnorderedElementsAreArray(server_tags));
}

TEST_F(StatsPluginEnd2EndTest, RequestReceivedBytesPerRpc) {
  View client_sent_bytes_per_rpc_view(ClientSentBytesPerRpcCumulative());
  View client_received_bytes_per_rpc_view(
      ClientReceivedBytesPerRpcCumulative());
  View server_sent_bytes_per_rpc_view(ServerSentBytesPerRpcCumulative());
  View server_received_bytes_per_rpc_view(
      ServerReceivedBytesPerRpcCumulative());

  {
    EchoRequest request;
    request.set_message("foo");
    EchoResponse response;
    grpc::ClientContext context;
    grpc::Status status = stub_->Echo(&context, request, &response);
    ASSERT_TRUE(status.ok());
    EXPECT_EQ("foo", response.message());
  }
  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();

  EXPECT_THAT(client_received_bytes_per_rpc_view.GetData().distribution_data(),
              ::testing::UnorderedElementsAre(::testing::Pair(
                  ::testing::ElementsAre(client_method_name_),
                  ::testing::AllOf(::testing::Property(&Distribution::count, 1),
                                   ::testing::Property(&Distribution::mean,
                                                       ::testing::Gt(0.0))))));
  EXPECT_THAT(client_sent_bytes_per_rpc_view.GetData().distribution_data(),
              ::testing::UnorderedElementsAre(::testing::Pair(
                  ::testing::ElementsAre(client_method_name_),
                  ::testing::AllOf(::testing::Property(&Distribution::count, 1),
                                   ::testing::Property(&Distribution::mean,
                                                       ::testing::Gt(0.0))))));
  EXPECT_THAT(server_received_bytes_per_rpc_view.GetData().distribution_data(),
              ::testing::UnorderedElementsAre(::testing::Pair(
                  ::testing::ElementsAre(server_method_name_),
                  ::testing::AllOf(::testing::Property(&Distribution::count, 1),
                                   ::testing::Property(&Distribution::mean,
                                                       ::testing::Gt(0.0))))));
  EXPECT_THAT(server_sent_bytes_per_rpc_view.GetData().distribution_data(),
              ::testing::UnorderedElementsAre(::testing::Pair(
                  ::testing::ElementsAre(server_method_name_),
                  ::testing::AllOf(::testing::Property(&Distribution::count, 1),
                                   ::testing::Property(&Distribution::mean,
                                                       ::testing::Gt(0.0))))));
}

TEST_F(StatsPluginEnd2EndTest, Latency) {
  View client_latency_view(ClientRoundtripLatencyCumulative());
  View client_server_latency_view(ClientServerLatencyCumulative());
  View server_server_latency_view(ServerServerLatencyCumulative());
  View client_transport_latency_view(experimental::ClientTransportLatency());
  View client_api_latency_view(grpc::internal::ClientApiLatency());

  const absl::Time start_time = absl::Now();
  {
    EchoRequest request;
    request.set_message("foo");
    EchoResponse response;
    grpc::ClientContext context;
    grpc::Status status = stub_->Echo(&context, request, &response);
    ASSERT_TRUE(status.ok());
    EXPECT_EQ("foo", response.message());
  }

  const double max_time = absl::ToDoubleMilliseconds(absl::Now() - start_time);

  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();

  EXPECT_THAT(
      client_latency_view.GetData().distribution_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre(client_method_name_),
          ::testing::AllOf(
              ::testing::Property(&Distribution::count, 1),
              ::testing::Property(&Distribution::mean, ::testing::Gt(0.0)),
              ::testing::Property(&Distribution::mean,
                                  ::testing::Lt(max_time))))));

  const auto client_latency = client_latency_view.GetData()
                                  .distribution_data()
                                  .find({client_method_name_})
                                  ->second.mean();
  EXPECT_THAT(
      client_server_latency_view.GetData().distribution_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre(client_method_name_),
          ::testing::AllOf(
              ::testing::Property(&Distribution::count, 1),
              ::testing::Property(&Distribution::mean, ::testing::Gt(0.0)),
              ::testing::Property(&Distribution::mean,
                                  ::testing::Lt(client_latency))))));

  EXPECT_THAT(
      client_api_latency_view.GetData().distribution_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre(client_method_name_, "OK"),
          ::testing::AllOf(::testing::Property(&Distribution::count, 1),
                           ::testing::Property(&Distribution::mean,
                                               ::testing::Gt(client_latency)),
                           ::testing::Property(&Distribution::mean,
                                               ::testing::Lt(max_time))))));

  const auto client_elapsed_time = client_server_latency_view.GetData()
                                       .distribution_data()
                                       .find({client_method_name_})
                                       ->second.mean();
  EXPECT_THAT(
      server_server_latency_view.GetData().distribution_data(),
      ::testing::UnorderedElementsAre(::testing::Pair(
          ::testing::ElementsAre(server_method_name_),
          ::testing::AllOf(
              ::testing::Property(&Distribution::count, 1),
              ::testing::Property(&Distribution::mean,
                                  ::testing::DoubleEq(client_elapsed_time))))));
}

TEST_F(StatsPluginEnd2EndTest, StartedRpcs) {
  View client_started_rpcs_view(ClientStartedRpcsCumulative());
  View server_started_rpcs_view(ServerStartedRpcsCumulative());

  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;
  const int count = 5;
  for (int i = 0; i < count; ++i) {
    {
      grpc::ClientContext context;
      grpc::Status status = stub_->Echo(&context, request, &response);
      ASSERT_TRUE(status.ok());
      EXPECT_EQ("foo", response.message());
    }
    absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
    TestUtils::Flush();

    EXPECT_THAT(client_started_rpcs_view.GetData().int_data(),
                ::testing::UnorderedElementsAre(::testing::Pair(
                    ::testing::ElementsAre(client_method_name_), i + 1)));
    EXPECT_THAT(server_started_rpcs_view.GetData().int_data(),
                ::testing::UnorderedElementsAre(::testing::Pair(
                    ::testing::ElementsAre(server_method_name_), i + 1)));
  }

  {
    ClientContext ctx;
    auto stream = stub_->BidiStream(&ctx);
    absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
    TestUtils::Flush();
    EXPECT_THAT(
        client_started_rpcs_view.GetData().int_data(),
        ::testing::Contains(::testing::Pair(
            ::testing::ElementsAre("grpc.testing.EchoTestService/BidiStream"),
            1)));
    EXPECT_THAT(
        server_started_rpcs_view.GetData().int_data(),
        ::testing::Contains(::testing::Pair(
            ::testing::ElementsAre("grpc.testing.EchoTestService/BidiStream"),
            1)));
    ctx.TryCancel();
  }
  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();
}

TEST_F(StatsPluginEnd2EndTest, CompletedRpcs) {
  View client_completed_rpcs_view(ClientCompletedRpcsCumulative());
  View server_completed_rpcs_view(ServerCompletedRpcsCumulative());

  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;
  const int count = 5;
  for (int i = 0; i < count; ++i) {
    {
      grpc::ClientContext context;
      grpc::Status status = stub_->Echo(&context, request, &response);
      ASSERT_TRUE(status.ok());
      EXPECT_EQ("foo", response.message());
    }
    absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
    TestUtils::Flush();

    EXPECT_THAT(client_completed_rpcs_view.GetData().int_data(),
                ::testing::UnorderedElementsAre(::testing::Pair(
                    ::testing::ElementsAre(client_method_name_, "OK"), i + 1)));
    EXPECT_THAT(server_completed_rpcs_view.GetData().int_data(),
                ::testing::UnorderedElementsAre(::testing::Pair(
                    ::testing::ElementsAre(server_method_name_, "OK"), i + 1)));
  }

  {
    ClientContext ctx;
    auto stream = stub_->BidiStream(&ctx);
    ctx.TryCancel();
  }
  absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
  TestUtils::Flush();
  EXPECT_THAT(client_completed_rpcs_view.GetData().int_data(),
              ::testing::Contains(::testing::Pair(
                  ::testing::ElementsAre(
                      "grpc.testing.EchoTestService/BidiStream", "CANCELLED"),
                  1)));
}

TEST_F(StatsPluginEnd2EndTest, RequestReceivedMessagesPerRpc) {

  View client_received_messages_per_rpc_view(
      ClientSentMessagesPerRpcCumulative());
  View client_sent_messages_per_rpc_view(
      ClientReceivedMessagesPerRpcCumulative());
  View server_received_messages_per_rpc_view(
      ServerSentMessagesPerRpcCumulative());
  View server_sent_messages_per_rpc_view(
      ServerReceivedMessagesPerRpcCumulative());

  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;
  const int count = 5;
  for (int i = 0; i < count; ++i) {
    {
      grpc::ClientContext context;
      grpc::Status status = stub_->Echo(&context, request, &response);
      ASSERT_TRUE(status.ok());
      EXPECT_EQ("foo", response.message());
    }
    absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
    TestUtils::Flush();

    EXPECT_THAT(
        client_received_messages_per_rpc_view.GetData().distribution_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_),
            ::testing::AllOf(::testing::Property(&Distribution::count, i + 1),
                             ::testing::Property(&Distribution::mean,
                                                 ::testing::DoubleEq(1.0))))));
    EXPECT_THAT(
        client_sent_messages_per_rpc_view.GetData().distribution_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_),
            ::testing::AllOf(::testing::Property(&Distribution::count, i + 1),
                             ::testing::Property(&Distribution::mean,
                                                 ::testing::DoubleEq(1.0))))));
    EXPECT_THAT(
        server_received_messages_per_rpc_view.GetData().distribution_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(server_method_name_),
            ::testing::AllOf(::testing::Property(&Distribution::count, i + 1),
                             ::testing::Property(&Distribution::mean,
                                                 ::testing::DoubleEq(1.0))))));
    EXPECT_THAT(
        server_sent_messages_per_rpc_view.GetData().distribution_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(server_method_name_),
            ::testing::AllOf(::testing::Property(&Distribution::count, i + 1),
                             ::testing::Property(&Distribution::mean,
                                                 ::testing::DoubleEq(1.0))))));
  }
}

TEST_F(StatsPluginEnd2EndTest, TestRetryStatsWithoutAdditionalRetries) {
  View client_retries_cumulative_view(ClientRetriesCumulative());
  View client_transparent_retries_cumulative_view(
      ClientTransparentRetriesCumulative());
  View client_retry_delay_per_call_view(ClientRetryDelayPerCallCumulative());
  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;
  const int count = 5;
  for (int i = 0; i < count; ++i) {
    {
      grpc::ClientContext context;
      grpc::Status status = stub_->Echo(&context, request, &response);
      ASSERT_TRUE(status.ok());
      EXPECT_EQ("foo", response.message());
    }
    absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
    TestUtils::Flush();
    EXPECT_THAT(
        client_retries_cumulative_view.GetData().int_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_), ::testing::Eq(0))));
    EXPECT_THAT(
        client_transparent_retries_cumulative_view.GetData().int_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_), ::testing::Eq(0))));
    EXPECT_THAT(
        client_retry_delay_per_call_view.GetData().distribution_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_),
            ::testing::Property(&Distribution::mean, ::testing::Eq(0)))));
  }
}

TEST_F(StatsPluginEnd2EndTest, TestRetryStatsWithAdditionalRetries) {
  View client_retries_cumulative_view(ClientRetriesCumulative());
  View client_transparent_retries_cumulative_view(
      ClientTransparentRetriesCumulative());
  View client_retry_delay_per_call_view(ClientRetryDelayPerCallCumulative());
  ChannelArguments args;
  args.SetString(GRPC_ARG_SERVICE_CONFIG,
                 "{\n"
                 "  \"methodConfig\": [ {\n"
                 "    \"name\": [\n"
                 "      { \"service\": \"grpc.testing.EchoTestService\" }\n"
                 "    ],\n"
                 "    \"retryPolicy\": {\n"
                 "      \"maxAttempts\": 3,\n"
                 "      \"initialBackoff\": \"0.1s\",\n"
                 "      \"maxBackoff\": \"120s\",\n"
                 "      \"backoffMultiplier\": 1,\n"
                 "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
                 "    }\n"
                 "  } ]\n"
                 "}");
  auto channel =
      CreateCustomChannel(server_address_, InsecureChannelCredentials(), args);
  ResetStub(channel);
  EchoRequest request;
  request.mutable_param()->mutable_expected_error()->set_code(
      StatusCode::ABORTED);
  request.set_message("foo");
  EchoResponse response;
  const int count = 5;
  for (int i = 0; i < count; ++i) {
    {
      grpc::ClientContext context;
      grpc::Status status = stub_->Echo(&context, request, &response);
      EXPECT_EQ(status.error_code(), StatusCode::ABORTED);
    }
    absl::SleepFor(absl::Milliseconds(500 * grpc_test_slowdown_factor()));
    TestUtils::Flush();
    EXPECT_THAT(client_retries_cumulative_view.GetData().int_data(),
                ::testing::UnorderedElementsAre(
                    ::testing::Pair(::testing::ElementsAre(client_method_name_),
                                    ::testing::Eq((i + 1) * 2))));
    EXPECT_THAT(
        client_transparent_retries_cumulative_view.GetData().int_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_), ::testing::Eq(0))));
    auto data = client_retry_delay_per_call_view.GetData().distribution_data();
    for (const auto& entry : data) {
      LOG(ERROR) << "Mean Retry Delay " << entry.first[0] << ": "
                 << entry.second.mean() << " ms";
    }

    EXPECT_THAT(
        client_retry_delay_per_call_view.GetData().distribution_data(),
        ::testing::UnorderedElementsAre(::testing::Pair(
            ::testing::ElementsAre(client_method_name_),
            ::testing::Property(
                &Distribution::mean,
                ::testing::AllOf(
                    ::testing::Ge(50),
                    ::testing::Le(500 * grpc_test_slowdown_factor()))))));
  }
}

TEST_F(StatsPluginEnd2EndTest, TestApplicationCensusContextFlows) {
  auto channel = CreateChannel(server_address_, InsecureChannelCredentials());
  ResetStub(channel);
  EchoRequest request;
  request.set_message("foo");
  EchoResponse response;
  grpc::ClientContext context;
  grpc::CensusContext app_census_context("root", ::opencensus::tags::TagMap{});
  context.set_census_context(
      reinterpret_cast<census_context*>(&app_census_context));
  context.AddMetadata(kExpectedTraceIdKey,
                      app_census_context.Span().context().trace_id().ToHex());
  grpc::Status status = stub_->Echo(&context, request, &response);
  EXPECT_TRUE(status.ok());
}

std::vector<opencensus::trace::exporter::SpanData>::const_iterator
GetSpanByName(
    const std::vector<::opencensus::trace::exporter::SpanData>& recorded_spans,
    absl::string_view name) {
  return std::find_if(
      recorded_spans.begin(), recorded_spans.end(),
      [name](auto const& span_data) { return span_data.name() == name; });
}

TEST_F(StatsPluginEnd2EndTest, TestAllSpansAreExported) {
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
  auto recorded_spans = traces_recorder_->GetAndClearSpans(3);
  traces_recorder_->StopRecording();

  ASSERT_EQ(3, recorded_spans.size());
  auto sent_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Sent.", client_method_name_));
  ASSERT_NE(sent_span_data, recorded_spans.end());
  auto attempt_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_NE(attempt_span_data, recorded_spans.end());
  EXPECT_EQ(sent_span_data->context().span_id(),
            attempt_span_data->parent_span_id());
  auto recv_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Recv.", server_method_name_));
  ASSERT_NE(recv_span_data, recorded_spans.end());
  EXPECT_EQ(attempt_span_data->context().span_id(),
            recv_span_data->parent_span_id());
}

bool IsAnnotationPresent(
    std::vector<opencensus::trace::exporter::SpanData>::const_iterator span,
    absl::string_view annotation) {
  for (const auto& event : span->annotations().events()) {
    if (absl::StrContains(event.event().description(), annotation)) {
      return true;
    } else if (::testing::Matches(::testing::ContainsRegex(annotation))(
                   event.event().description())) {
      return true;
    }
  }
  return false;
}

TEST_F(StatsPluginEnd2EndTest,
       TestRemovePendingResolverResultAndPendingLbPickQueueAnnotations) {
  {

    ChannelArguments args;
    args.SetLoadBalancingPolicyName("queue_once");
    auto channel = CreateCustomChannel(server_address_,
                                       InsecureChannelCredentials(), args);
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
  auto recorded_spans = traces_recorder_->GetAndClearSpans(3);
  traces_recorder_->StopRecording();

  auto sent_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Sent.", client_method_name_));
  ASSERT_NE(sent_span_data, recorded_spans.end());

  if (!grpc_core::IsEventEngineDnsEnabled()) {
    EXPECT_TRUE(IsAnnotationPresent(sent_span_data,
                                    "Delayed name resolution complete."));
  }

  auto attempt_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_NE(attempt_span_data, recorded_spans.end());
  EXPECT_TRUE(
      IsAnnotationPresent(attempt_span_data, "Delayed LB pick complete."));
}

TEST_F(StatsPluginEnd2EndTest, TestMessageSizeAnnotations) {
  {

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
  auto recorded_spans = traces_recorder_->GetAndClearSpans(3);
  traces_recorder_->StopRecording();

  auto attempt_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_NE(attempt_span_data, recorded_spans.end());
  EXPECT_TRUE(IsAnnotationPresent(attempt_span_data, "Send message: 5 bytes"));
  EXPECT_FALSE(IsAnnotationPresent(attempt_span_data,
                                   "Send compressed message: 5 bytes"));
  EXPECT_TRUE(
      IsAnnotationPresent(attempt_span_data, "Received message: 5 bytes"));
  EXPECT_FALSE(IsAnnotationPresent(attempt_span_data,
                                   "Received decompressed message: 5 bytes"));

  auto server_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Recv.", client_method_name_));
  ASSERT_NE(server_span_data, recorded_spans.end());
  EXPECT_TRUE(IsAnnotationPresent(server_span_data, "Send message: 5 bytes"));
  EXPECT_FALSE(IsAnnotationPresent(attempt_span_data,
                                   "Send compressed message: 5 bytes"));
  EXPECT_TRUE(
      IsAnnotationPresent(server_span_data, "Received message: 5 bytes"));
  EXPECT_FALSE(IsAnnotationPresent(server_span_data,
                                   "Received decompressed message: 5 bytes"));
}

std::string CreateLargeMessage() {
  char str[1024];
  for (int i = 0; i < 1023; ++i) {
    str[i] = 'a';
  }
  str[1023] = '\0';
  return std::string(str);
}

TEST_F(StatsPluginEnd2EndTest, TestMessageSizeWithCompressionAnnotations) {
  {

    EchoRequest request;
    request.set_message(CreateLargeMessage());
    EchoResponse response;

    grpc::ClientContext context;
    context.set_compression_algorithm(GRPC_COMPRESS_GZIP);
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
  auto recorded_spans = traces_recorder_->GetAndClearSpans(3);
  traces_recorder_->StopRecording();

  auto attempt_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_NE(attempt_span_data, recorded_spans.end());
  EXPECT_TRUE(
      IsAnnotationPresent(attempt_span_data, "Send message: 1026 bytes"));

  EXPECT_TRUE(
      IsAnnotationPresent(attempt_span_data, "Send compressed message:"));
  EXPECT_TRUE(IsAnnotationPresent(attempt_span_data, "Received message:"));
  EXPECT_TRUE(IsAnnotationPresent(attempt_span_data,
                                  "Received decompressed message: 1026 bytes"));

  auto server_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Recv.", client_method_name_));
  ASSERT_NE(server_span_data, recorded_spans.end());
  EXPECT_TRUE(
      IsAnnotationPresent(server_span_data, "Send message: 1026 bytes"));

  EXPECT_TRUE(
      IsAnnotationPresent(attempt_span_data, "Send compressed message:"));
  EXPECT_TRUE(IsAnnotationPresent(server_span_data, "Received message:"));
  EXPECT_TRUE(IsAnnotationPresent(server_span_data,
                                  "Received decompressed message: 1026 bytes"));
}

TEST_F(StatsPluginEnd2EndTest, TestMetadataSizeAnnotations) {
  {

    EchoRequest request;
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
  auto recorded_spans = traces_recorder_->GetAndClearSpans(3);
  traces_recorder_->StopRecording();

  auto sent_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_NE(sent_span_data, recorded_spans.end());
  EXPECT_TRUE(IsAnnotationPresent(
      sent_span_data,
      "gRPC metadata soft_limit:[0-9]{4,5},hard_limit:[0-9]{5},:status:["
      "0-9]{1,2},content-type:[0-9]{1,2},grpc-encoding:[0-"
      "9]{1,2},grpc-accept-encoding:[0-9]{1,2},"));
  EXPECT_TRUE(IsAnnotationPresent(
      sent_span_data,
      "gRPC metadata "
      "soft_limit:[0-9]{4,5},hard_limit:[0-9]{5},grpc-status:[0-9]{1,2},grpc-"
      "server-stats-bin:[0-9]{1,2},"));
}

TEST_F(StatsPluginEnd2EndTest, TestHttpAnnotations) {
  {

    EchoRequest request;
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
  auto recorded_spans = traces_recorder_->GetAndClearSpans(3);
  traces_recorder_->StopRecording();
  auto client_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_NE(client_span_data, recorded_spans.end());
  EXPECT_TRUE(IsAnnotationPresent(client_span_data,
                                  "HttpAnnotation type: Start time: .* "
                                  "transport:\\[.*\\] stream:\\[.*\\]"));
  EXPECT_TRUE(IsAnnotationPresent(client_span_data,
                                  "HttpAnnotation type: HeadWritten time: .* "
                                  "transport:\\[.*\\] stream:\\[.*\\]"));
  EXPECT_TRUE(IsAnnotationPresent(client_span_data,
                                  "HttpAnnotation type: End time: .* "
                                  "transport:\\[.*\\] stream:\\[.*\\]"));
  auto server_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Recv.", client_method_name_));
  ASSERT_NE(server_span_data, recorded_spans.end());
  EXPECT_TRUE(IsAnnotationPresent(server_span_data,
                                  "HttpAnnotation type: Start time: .* "
                                  "transport:\\[.*\\] stream:\\[.*\\]"));
  EXPECT_TRUE(IsAnnotationPresent(server_span_data,
                                  "HttpAnnotation type: HeadWritten time: .* "
                                  "transport:\\[.*\\] stream:\\[.*\\]"));
  EXPECT_TRUE(IsAnnotationPresent(server_span_data,
                                  "HttpAnnotation type: End time: .* "
                                  "transport:\\[.*\\] stream:\\[.*\\]"));
}

TEST_F(StatsPluginEnd2EndTest, TestObservabilityDisabledChannelArg) {
  {

    ChannelArguments args;
    args.SetInt(GRPC_ARG_ENABLE_OBSERVABILITY, 0);
    auto channel = CreateCustomChannel(server_address_,
                                       InsecureChannelCredentials(), args);
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
    traces_recorder_->StartRecording();
    grpc::Status status = stub_->Echo(&context, request, &response);
    EXPECT_TRUE(status.ok());
  }
  auto recorded_spans = traces_recorder_->GetAndClearSpans(0);
  traces_recorder_->StopRecording();

  ASSERT_LE(recorded_spans.size(), 1);

  auto sent_span_data =
      GetSpanByName(recorded_spans, absl::StrCat("Sent.", client_method_name_));
  ASSERT_EQ(sent_span_data, recorded_spans.end());
  auto attempt_span_data = GetSpanByName(
      recorded_spans, absl::StrCat("Attempt.", client_method_name_));
  ASSERT_EQ(attempt_span_data, recorded_spans.end());
}

TEST_F(StatsPluginEnd2EndTest, TestGlobalEnableOpenCensusStats) {
  grpc::internal::EnableOpenCensusStats(false);

  View client_started_rpcs_view(ClientStartedRpcsCumulative());
  View server_started_rpcs_view(ServerStartedRpcsCumulative());
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

  EXPECT_TRUE(client_started_rpcs_view.GetData().int_data().empty());
  EXPECT_TRUE(server_started_rpcs_view.GetData().int_data().empty());
  EXPECT_TRUE(client_completed_rpcs_view.GetData().int_data().empty());
  EXPECT_TRUE(server_completed_rpcs_view.GetData().int_data().empty());

  grpc::internal::EnableOpenCensusStats(true);
}

TEST_F(StatsPluginEnd2EndTest, TestGlobalEnableOpenCensusTracing) {
  grpc::internal::EnableOpenCensusTracing(false);

  {

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
    traces_recorder_->StartRecording();
    grpc::Status status = stub_->Echo(&context, request, &response);
    EXPECT_TRUE(status.ok());
  }
  auto recorded_spans = traces_recorder_->GetAndClearSpans(0);
  traces_recorder_->StopRecording();

  ASSERT_EQ(0, recorded_spans.size());

  grpc::internal::EnableOpenCensusTracing(true);
}

TEST(StatsPluginDeclarationTest, Declarations) {
  LOG(INFO) << ClientMethodTagKey;
  LOG(INFO) << ClientStatusTagKey;
  LOG(INFO) << ServerMethodTagKey;
  LOG(INFO) << ServerStatusTagKey;

  LOG(INFO) << kRpcClientReceivedBytesPerRpcMeasureName.data();
  LOG(INFO) << kRpcClientReceivedMessagesPerRpcMeasureName.data();
  LOG(INFO) << kRpcClientRetriesPerCallMeasureName.data();
  LOG(INFO) << kRpcClientRetryDelayPerCallMeasureName.data();
  LOG(INFO) << kRpcClientRoundtripLatencyMeasureName.data();
  LOG(INFO) << kRpcClientSentBytesPerRpcMeasureName.data();
  LOG(INFO) << kRpcClientSentMessagesPerRpcMeasureName.data();
  LOG(INFO) << kRpcClientServerLatencyMeasureName.data();
  LOG(INFO) << kRpcClientStartedRpcsMeasureName.data();
  LOG(INFO) << kRpcClientTransparentRetriesPerCallMeasureName.data();

  LOG(INFO) << kRpcServerReceivedBytesPerRpcMeasureName.data();
  LOG(INFO) << kRpcServerReceivedMessagesPerRpcMeasureName.data();
  LOG(INFO) << kRpcServerSentBytesPerRpcMeasureName.data();
  LOG(INFO) << kRpcServerSentMessagesPerRpcMeasureName.data();
  LOG(INFO) << kRpcServerServerLatencyMeasureName.data();
  LOG(INFO) << kRpcServerStartedRpcsMeasureName.data();

  LOG(INFO) << ClientCompletedRpcsCumulative;
  LOG(INFO) << ClientReceivedBytesPerRpcCumulative;
  LOG(INFO) << ClientReceivedMessagesPerRpcCumulative;
  LOG(INFO) << ClientRetriesCumulative;
  LOG(INFO) << ClientRetriesPerCallCumulative;
  LOG(INFO) << ClientRetryDelayPerCallCumulative;
  LOG(INFO) << ClientRoundtripLatencyCumulative;
  LOG(INFO) << ClientSentBytesPerRpcCumulative;
  LOG(INFO) << ClientSentMessagesPerRpcCumulative;
  LOG(INFO) << ClientServerLatencyCumulative;
  LOG(INFO) << ClientStartedRpcsCumulative;
  LOG(INFO) << ClientTransparentRetriesCumulative;
  LOG(INFO) << ClientTransparentRetriesPerCallCumulative;

  LOG(INFO) << ServerCompletedRpcsCumulative;
  LOG(INFO) << ServerReceivedBytesPerRpcCumulative;
  LOG(INFO) << ServerReceivedMessagesPerRpcCumulative;
  LOG(INFO) << ServerSentBytesPerRpcCumulative;
  LOG(INFO) << ServerSentMessagesPerRpcCumulative;
  LOG(INFO) << ServerServerLatencyCumulative;
  LOG(INFO) << ServerStartedRpcsCumulative;

  LOG(INFO) << ClientCompletedRpcsMinute;
  LOG(INFO) << ClientReceivedBytesPerRpcMinute;
  LOG(INFO) << ClientReceivedMessagesPerRpcMinute;
  LOG(INFO) << ClientRetriesMinute;
  LOG(INFO) << ClientRetriesPerCallMinute;
  LOG(INFO) << ClientRetryDelayPerCallMinute;
  LOG(INFO) << ClientRoundtripLatencyMinute;
  LOG(INFO) << ClientSentBytesPerRpcMinute;
  LOG(INFO) << ClientSentMessagesPerRpcMinute;
  LOG(INFO) << ClientServerLatencyMinute;
  LOG(INFO) << ClientStartedRpcsMinute;
  LOG(INFO) << ClientTransparentRetriesMinute;
  LOG(INFO) << ClientTransparentRetriesPerCallMinute;

  LOG(INFO) << ServerCompletedRpcsMinute;
  LOG(INFO) << ServerReceivedBytesPerRpcMinute;
  LOG(INFO) << ServerReceivedMessagesPerRpcMinute;
  LOG(INFO) << ServerSentBytesPerRpcMinute;
  LOG(INFO) << ServerSentMessagesPerRpcMinute;
  LOG(INFO) << ServerServerLatencyMinute;
  LOG(INFO) << ServerStartedRpcsMinute;

  LOG(INFO) << ClientCompletedRpcsHour;
  LOG(INFO) << ClientReceivedBytesPerRpcHour;
  LOG(INFO) << ClientReceivedMessagesPerRpcHour;
  LOG(INFO) << ClientRetriesHour;
  LOG(INFO) << ClientRetriesPerCallHour;
  LOG(INFO) << ClientRetryDelayPerCallHour;
  LOG(INFO) << ClientRoundtripLatencyHour;
  LOG(INFO) << ClientSentBytesPerRpcHour;
  LOG(INFO) << ClientSentMessagesPerRpcHour;
  LOG(INFO) << ClientServerLatencyHour;
  LOG(INFO) << ClientStartedRpcsHour;
  LOG(INFO) << ClientTransparentRetriesHour;
  LOG(INFO) << ClientTransparentRetriesPerCallHour;

  LOG(INFO) << ServerCompletedRpcsHour;
  LOG(INFO) << ServerReceivedBytesPerRpcHour;
  LOG(INFO) << ServerReceivedMessagesPerRpcHour;
  LOG(INFO) << ServerSentBytesPerRpcHour;
  LOG(INFO) << ServerSentMessagesPerRpcHour;
  LOG(INFO) << ServerServerLatencyHour;
  LOG(INFO) << ServerStartedRpcsHour;
}

}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
