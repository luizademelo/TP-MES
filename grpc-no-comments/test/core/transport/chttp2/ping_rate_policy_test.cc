// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"

#include <chrono>
#include <thread>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/experiments/experiments.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace {

using ::testing::PrintToString;

Chttp2PingRatePolicy::RequestSendPingResult SendGranted() {
  return Chttp2PingRatePolicy::SendGranted{};
}

Chttp2PingRatePolicy::RequestSendPingResult TooManyRecentPings() {
  return Chttp2PingRatePolicy::TooManyRecentPings{};
}

TEST(PingRatePolicy, NoOpClient) {
  Chttp2PingRatePolicy policy{ChannelArgs(), true};
  EXPECT_EQ(policy.TestOnlyMaxPingsWithoutData(), 2);
}

TEST(PingRatePolicy, NoOpServer) {
  Chttp2PingRatePolicy policy{ChannelArgs(), false};
  EXPECT_EQ(policy.TestOnlyMaxPingsWithoutData(), 0);
}

TEST(PingRatePolicy, ServerCanSendAtStart) {
  Chttp2PingRatePolicy policy{ChannelArgs(), false};
  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(100), 0),
            SendGranted());
}

TEST(PingRatePolicy, ClientBlockedUntilDataSent) {
  if (IsMaxPingsWoDataThrottleEnabled()) {
    GTEST_SKIP()
        << "Pings are not blocked if max_pings_wo_data_throttle is enabled.";
  }
  Chttp2PingRatePolicy policy{ChannelArgs(), true};
  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(10), 0),
            TooManyRecentPings());
  policy.ResetPingsBeforeDataRequired();
  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(10), 0),
            SendGranted());
  policy.SentPing();
  EXPECT_EQ(policy.RequestSendPing(Duration::Zero(), 0), SendGranted());
  policy.SentPing();
  EXPECT_EQ(policy.RequestSendPing(Duration::Zero(), 0), TooManyRecentPings());
}

MATCHER_P2(IsWithinRange, lo, hi,
           absl::StrCat(negation ? "isn't" : "is", " between ",
                        PrintToString(lo), " and ", PrintToString(hi))) {
  return lo <= arg && arg <= hi;
}

TEST(PingRatePolicy, ClientThrottledUntilDataSent) {
  if (!IsMaxPingsWoDataThrottleEnabled()) {
    GTEST_SKIP()
        << "Throttling behavior is enabled with max_pings_wo_data_throttle.";
  }
  Chttp2PingRatePolicy policy{ChannelArgs(), true};

  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(10), 0),
            SendGranted());
  policy.SentPing();

  auto result = policy.RequestSendPing(Duration::Zero(), 0);
  EXPECT_TRUE(std::holds_alternative<Chttp2PingRatePolicy::TooSoon>(result));
  EXPECT_THAT(std::get<Chttp2PingRatePolicy::TooSoon>(result).wait,
              IsWithinRange(Duration::Seconds(59), Duration::Minutes(1)));
  policy.ResetPingsBeforeDataRequired();

  EXPECT_EQ(policy.RequestSendPing(Duration::Zero(), 0), SendGranted());
  policy.SentPing();
  EXPECT_EQ(policy.RequestSendPing(Duration::Zero(), 0), SendGranted());
  policy.SentPing();

  result = policy.RequestSendPing(Duration::Zero(), 0);
  EXPECT_TRUE(std::holds_alternative<Chttp2PingRatePolicy::TooSoon>(result));
  EXPECT_THAT(std::get<Chttp2PingRatePolicy::TooSoon>(result).wait,
              IsWithinRange(Duration::Seconds(59), Duration::Minutes(1)));
}

TEST(PingRatePolicy, RateThrottlingWorks) {
  Chttp2PingRatePolicy policy{ChannelArgs(), false};

  while (policy.RequestSendPing(Duration::Milliseconds(10), 0) ==
         SendGranted()) {
    policy.SentPing();
  }

  for (int i = 0; i < 100; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(10), 0),
              SendGranted());
    policy.SentPing();
  }
}

TEST(PingRatePolicy, TooManyPingsInflightBlocksSendingPings) {
  Chttp2PingRatePolicy policy{ChannelArgs(), false};
  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(1), 100000000),
            TooManyRecentPings());
}

TEST(PingRatePolicy, TooManyPingsInflightBlocksSendingPingsStrictLimit) {
  if (!IsMaxInflightPingsStrictLimitEnabled()) {
    GTEST_SKIP() << "Strict limit is not enabled.";
  }
  int max_inflight_pings = 1;
  auto channel_args =
      ChannelArgs().Set(GRPC_ARG_HTTP2_MAX_INFLIGHT_PINGS, max_inflight_pings);
  Chttp2PingRatePolicy policy{channel_args, false};

  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(1), 0),
            SendGranted());
  EXPECT_EQ(
      policy.RequestSendPing(Duration::Milliseconds(1), max_inflight_pings),
      TooManyRecentPings());
  EXPECT_EQ(policy.RequestSendPing(Duration::Milliseconds(1), 100000000),
            TooManyRecentPings());
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
