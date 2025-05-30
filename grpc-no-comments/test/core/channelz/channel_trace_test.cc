
// Copyright 2017 gRPC authors.

#include "src/core/channelz/channel_trace.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <stdlib.h>

#include <list>
#include <string>
#include <thread>

#include "absl/synchronization/notification.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/channelz/channelz.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/channel_trace_proto_helper.h"

namespace grpc_core {
namespace channelz {
namespace testing {

class SubchannelNodePeer {
 public:
  explicit SubchannelNodePeer(SubchannelNode* node) : node_(node) {}
  ChannelTrace* trace() const { return &node_->trace_; }

 private:
  SubchannelNode* node_;
};

size_t GetSizeofTraceEvent() { return sizeof(ChannelTrace::TraceEvent); }

namespace {

MATCHER_P(IsJsonString, expected, "is JSON string") {
  if (!::testing::ExplainMatchResult(Json::Type::kString, arg.type(),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(expected, arg.string(), result_listener);
}

MATCHER_P(IsJsonStringNumber, expected, "is JSON string containing number") {
  if (!::testing::ExplainMatchResult(Json::Type::kString, arg.type(),
                                     result_listener)) {
    return false;
  }
  int actual;
  if (!absl::SimpleAtoi(arg.string(), &actual)) {
    *result_listener << "JSON string \"" << arg.string()
                     << " does not contain numeric value";
    return false;
  }
  return ::testing::ExplainMatchResult(expected, actual, result_listener);
}

MATCHER_P(IsJsonObject, matcher, "is JSON object") {
  if (!::testing::ExplainMatchResult(Json::Type::kObject, arg.type(),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, arg.object(), result_listener);
}

MATCHER_P(IsJsonArray, matcher, "is JSON array") {
  if (!::testing::ExplainMatchResult(Json::Type::kArray, arg.type(),
                                     result_listener)) {
    return false;
  }
  return ::testing::ExplainMatchResult(matcher, arg.array(), result_listener);
}

MATCHER_P2(IsTraceEvent, description, severity, "is trace event") {
  return ::testing::ExplainMatchResult(
      IsJsonObject(::testing::ElementsAre(
          ::testing::Pair("description", IsJsonString(description)),
          ::testing::Pair("severity", IsJsonString(severity)),
          ::testing::Pair("timestamp", IsJsonString(::testing::_)))),
      arg, result_listener);
}

MATCHER_P3(IsTraceEventWithChannelRef, description, severity, channel_ref,
           "is trace event with channel ref") {
  return ::testing::ExplainMatchResult(
      IsJsonObject(::testing::ElementsAre(
          ::testing::Pair("channelRef",
                          IsJsonObject(::testing::ElementsAre(::testing::Pair(
                              "channelId", IsJsonStringNumber(channel_ref))))),
          ::testing::Pair("description", IsJsonString(description)),
          ::testing::Pair("severity", IsJsonString(severity)),
          ::testing::Pair("timestamp", IsJsonString(::testing::_)))),
      arg, result_listener);
}

MATCHER_P3(IsTraceEventWithSubchannelRef, description, severity, subchannel_ref,
           "is trace event with subchannel ref") {
  return ::testing::ExplainMatchResult(
      IsJsonObject(::testing::ElementsAre(
          ::testing::Pair("description", IsJsonString(description)),
          ::testing::Pair("severity", IsJsonString(severity)),
          ::testing::Pair(
              "subchannelRef",
              IsJsonObject(::testing::ElementsAre(::testing::Pair(
                  "subchannelId", IsJsonStringNumber(subchannel_ref))))),
          ::testing::Pair("timestamp", IsJsonString(::testing::_)))),
      arg, result_listener);
}

MATCHER(IsEmptyChannelTrace, "is empty channel trace") {
  return ::testing::ExplainMatchResult(
      IsJsonObject(::testing::ElementsAre(
          ::testing::Pair("creationTimestamp", IsJsonString(::testing::_)))),
      arg, result_listener);
}

MATCHER_P2(IsChannelTrace, num_events_logged_expected, events_matcher,
           "is channel trace") {
  return ::testing::ExplainMatchResult(
      IsJsonObject(::testing::ElementsAre(
          ::testing::Pair("creationTimestamp", IsJsonString(::testing::_)),
          ::testing::Pair("events", IsJsonArray(events_matcher)),
          ::testing::Pair("numEventsLogged",
                          IsJsonStringNumber(num_events_logged_expected)))),
      arg, result_listener);
}

MATCHER_P(IsEmptyChannelTrace, num_events_logged_expected,
          "is empty channel trace") {
  return ::testing::ExplainMatchResult(
      IsJsonObject(::testing::ElementsAre(
          ::testing::Pair("creationTimestamp", IsJsonString(::testing::_)),
          ::testing::Pair("numEventsLogged",
                          IsJsonStringNumber(num_events_logged_expected)))),
      arg, result_listener);
}

void ValidateJsonProtoTranslation(const Json& json) {
  std::string json_str = JsonDump(json);
  grpc::testing::ValidateChannelTraceProtoJsonTranslation(json_str);
}

}

const int kEventListMemoryLimit = 1024 * 1024;

TEST(ChannelTracerTest, BasicTest) {
  ExecCtx exec_ctx;
  ChannelTrace tracer(kEventListMemoryLimit);
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("one"));
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("two"));
  tracer.AddTraceEvent(ChannelTrace::Severity::Warning,
                       grpc_slice_from_static_string("three"));
  tracer.AddTraceEvent(ChannelTrace::Severity::Error,
                       grpc_slice_from_static_string("four"));
  Json json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(json, IsChannelTrace(4, ::testing::ElementsAre(
                                          IsTraceEvent("one", "CT_INFO"),
                                          IsTraceEvent("two", "CT_INFO"),
                                          IsTraceEvent("three", "CT_WARNING"),
                                          IsTraceEvent("four", "CT_ERROR"))))
      << JsonDump(json);
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("five"));
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("six"));
  json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(json, IsChannelTrace(6, ::testing::ElementsAre(
                                          IsTraceEvent("one", "CT_INFO"),
                                          IsTraceEvent("two", "CT_INFO"),
                                          IsTraceEvent("three", "CT_WARNING"),
                                          IsTraceEvent("four", "CT_ERROR"),
                                          IsTraceEvent("five", "CT_INFO"),
                                          IsTraceEvent("six", "CT_INFO"))))
      << JsonDump(json);
}

TEST(ChannelTracerTest, ComplexTest) {
  ExecCtx exec_ctx;
  ChannelTrace tracer(kEventListMemoryLimit);
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("one"));
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("two"));
  auto subchannel_node = MakeRefCounted<SubchannelNode>("ipv4:1.2.3.4:5678",
                                                        kEventListMemoryLimit);
  auto* subchannel_node_trace =
      SubchannelNodePeer(subchannel_node.get()).trace();
  tracer.AddTraceEventWithReference(
      ChannelTrace::Severity::Info,
      grpc_slice_from_static_string("subchannel one created"), subchannel_node);
  Json json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(json,
              IsChannelTrace(3, ::testing::ElementsAre(
                                    IsTraceEvent("one", "CT_INFO"),
                                    IsTraceEvent("two", "CT_INFO"),
                                    IsTraceEventWithSubchannelRef(
                                        "subchannel one created", "CT_INFO",
                                        subchannel_node->uuid()))))
      << JsonDump(json);
  subchannel_node_trace->AddTraceEvent(ChannelTrace::Severity::Info,
                                       grpc_slice_from_static_string("one"));
  json = subchannel_node_trace->RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(
      json,
      IsChannelTrace(1, ::testing::ElementsAre(IsTraceEvent("one", "CT_INFO"))))
      << JsonDump(json);
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_static_string("three"));
  auto channel_node =
      MakeRefCounted<ChannelNode>("fake_target", kEventListMemoryLimit, 0);
  tracer.AddTraceEventWithReference(
      ChannelTrace::Severity::Info,
      grpc_slice_from_static_string("LB channel two created"), channel_node);
  tracer.AddTraceEventWithReference(
      ChannelTrace::Severity::Warning,
      grpc_slice_from_static_string("subchannel one inactive"),
      subchannel_node);
  json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(
      json,
      IsChannelTrace(
          6,
          ::testing::ElementsAre(
              IsTraceEvent("one", "CT_INFO"), IsTraceEvent("two", "CT_INFO"),
              IsTraceEventWithSubchannelRef("subchannel one created", "CT_INFO",
                                            subchannel_node->uuid()),
              IsTraceEvent("three", "CT_INFO"),
              IsTraceEventWithChannelRef("LB channel two created", "CT_INFO",
                                         channel_node->uuid()),
              IsTraceEventWithSubchannelRef("subchannel one inactive",
                                            "CT_WARNING",
                                            subchannel_node->uuid()))))
      << JsonDump(json);
}

TEST(ChannelTracerTest, TestSmallMemoryLimit) {
  ExecCtx exec_ctx;

  const int kSmallMemoryLimit = 1;
  ChannelTrace tracer(kSmallMemoryLimit);
  const size_t kNumEvents = 4;
  for (size_t i = 0; i < kNumEvents; ++i) {
    tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                         grpc_slice_from_static_string("trace"));
  }
  Json json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(json, IsEmptyChannelTrace(kNumEvents)) << JsonDump(json);
}

TEST(ChannelTracerTest, TestEviction) {
  ExecCtx exec_ctx;
  const int kTraceEventSize = GetSizeofTraceEvent();
  const int kNumEvents = 5;
  ChannelTrace tracer(kTraceEventSize * kNumEvents);
  std::list<::testing::Matcher<Json>> matchers;
  for (int i = 1; i <= kNumEvents; ++i) {
    tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                         grpc_slice_from_static_string("trace"));
    matchers.push_back(IsTraceEvent("trace", "CT_INFO"));
    Json json = tracer.RenderJson();
    ValidateJsonProtoTranslation(json);
    EXPECT_THAT(json, IsChannelTrace(i, ::testing::ElementsAreArray(matchers)))
        << JsonDump(json);
  }

  for (int i = 1; i <= kNumEvents; ++i) {
    tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                         grpc_slice_from_static_string("new"));
    matchers.pop_front();
    matchers.push_back(IsTraceEvent("new", "CT_INFO"));
    Json json = tracer.RenderJson();
    ValidateJsonProtoTranslation(json);
    EXPECT_THAT(json, IsChannelTrace(kNumEvents + i,
                                     ::testing::ElementsAreArray(matchers)))
        << JsonDump(json);
  }
}

TEST(ChannelTracerTest, TestMultipleEviction) {
  ExecCtx exec_ctx;
  const size_t kTraceEventSize = GetSizeofTraceEvent();
  const int kNumEvents = 5;
  ChannelTrace tracer(kTraceEventSize * kNumEvents);
  std::list<::testing::Matcher<Json>> matchers;
  for (int i = 1; i <= kNumEvents; ++i) {
    tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                         grpc_slice_from_static_string("trace"));
    matchers.push_back(IsTraceEvent("trace", "CT_INFO"));
    Json json = tracer.RenderJson();
    ValidateJsonProtoTranslation(json);
    EXPECT_THAT(json, IsChannelTrace(i, ::testing::ElementsAreArray(matchers)))
        << JsonDump(json);
  }

  std::string msg(GRPC_SLICE_INLINED_SIZE + 1, 'x');
  tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                       grpc_slice_from_cpp_string(msg));
  matchers.pop_front();
  matchers.pop_front();
  matchers.push_back(IsTraceEvent(msg, "CT_INFO"));
  Json json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(json, IsChannelTrace(kNumEvents + 1,
                                   ::testing::ElementsAreArray(matchers)))
      << JsonDump(json);
}

TEST(ChannelTracerTest, TestTotalEviction) {
  ExecCtx exec_ctx;
  const int kTraceEventSize = GetSizeofTraceEvent();
  const int kNumEvents = 5;
  ChannelTrace tracer(kTraceEventSize * kNumEvents);
  std::list<::testing::Matcher<Json>> matchers;
  for (int i = 1; i <= kNumEvents; ++i) {
    tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                         grpc_slice_from_static_string("trace"));
    matchers.push_back(IsTraceEvent("trace", "CT_INFO"));
    Json json = tracer.RenderJson();
    ValidateJsonProtoTranslation(json);
    EXPECT_THAT(json, IsChannelTrace(i, ::testing::ElementsAreArray(matchers)))
        << JsonDump(json);
  }

  grpc_slice huge_slice = grpc_slice_malloc(kTraceEventSize * (kNumEvents + 1));
  tracer.AddTraceEvent(ChannelTrace::Severity::Info, huge_slice);
  Json json = tracer.RenderJson();
  ValidateJsonProtoTranslation(json);
  EXPECT_THAT(json, IsEmptyChannelTrace(kNumEvents + 1)) << JsonDump(json);
}

TEST(ChannelTracerTest, ThreadSafety) {
  ExecCtx exec_ctx;
  ChannelTrace tracer(kEventListMemoryLimit);
  absl::Notification done;
  std::vector<std::unique_ptr<std::thread>> threads;
  for (size_t i = 0; i < 10; ++i) {
    threads.push_back(std::make_unique<std::thread>([&]() {
      do {
        tracer.AddTraceEvent(ChannelTrace::Severity::Info,
                             grpc_slice_from_static_string("trace"));
      } while (!done.HasBeenNotified());
    }));
  }
  for (size_t i = 0; i < 10; ++i) {
    tracer.RenderJson();
  }
  done.Notify();
  for (const auto& thd : threads) {
    thd->join();
  }
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
