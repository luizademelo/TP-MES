// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_abuse_policy.h"

#include <grpc/impl/channel_arg_names.h>

#include <chrono>
#include <thread>

#include "gtest/gtest.h"

namespace grpc_core {
namespace {

TEST(PingAbusePolicy, NoOp) {
  Chttp2PingAbusePolicy policy{ChannelArgs()};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 2);
  EXPECT_EQ(policy.TestOnlyMinPingIntervalWithoutData(), Duration::Minutes(5));
}

TEST(PingAbusePolicy, WithChannelArgs) {
  Chttp2PingAbusePolicy policy{
      ChannelArgs()
          .Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 100)
          .Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, 42)};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 42);
  EXPECT_EQ(policy.TestOnlyMinPingIntervalWithoutData(),
            Duration::Milliseconds(100));
}

TEST(PingAbusePolicy, ChannelArgsRangeCheck) {
  Chttp2PingAbusePolicy policy{
      ChannelArgs()
          .Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, -1000)
          .Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, -100)};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 0);
  EXPECT_EQ(policy.TestOnlyMinPingIntervalWithoutData(), Duration::Zero());
}

TEST(PingAbusePolicy, BasicOut) {
  Chttp2PingAbusePolicy policy{ChannelArgs()};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 2);

  EXPECT_FALSE(policy.ReceivedOnePing(false));

  EXPECT_FALSE(policy.ReceivedOnePing(false));

  EXPECT_FALSE(policy.ReceivedOnePing(false));

  EXPECT_TRUE(policy.ReceivedOnePing(false));
}

TEST(PingAbusePolicy, TimePreventsOut) {
  Chttp2PingAbusePolicy policy{ChannelArgs().Set(
      GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 1000)};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 2);

  EXPECT_FALSE(policy.ReceivedOnePing(false));

  EXPECT_FALSE(policy.ReceivedOnePing(false));

  EXPECT_FALSE(policy.ReceivedOnePing(false));

  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_FALSE(policy.ReceivedOnePing(false));
}

TEST(PingAbusePolicy, TimerSustains) {
  Chttp2PingAbusePolicy policy{ChannelArgs().Set(
      GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 10)};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 2);
  for (int i = 0; i < 100; i++) {
    EXPECT_FALSE(policy.ReceivedOnePing(false));
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}

TEST(PingAbusePolicy, IdleIncreasesTimeout) {
  Chttp2PingAbusePolicy policy{ChannelArgs().Set(
      GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 1000)};
  EXPECT_EQ(policy.TestOnlyMaxPingStrikes(), 2);

  EXPECT_FALSE(policy.ReceivedOnePing(true));

  EXPECT_FALSE(policy.ReceivedOnePing(true));

  EXPECT_FALSE(policy.ReceivedOnePing(true));

  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_TRUE(policy.ReceivedOnePing(true));
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  grpc_core::Chttp2PingAbusePolicy::SetDefaults(
      grpc_core::ChannelArgs()
          .Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, 2)
          .Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS,
               grpc_core::Duration::Minutes(5).millis()));
  return RUN_ALL_TESTS();
}
