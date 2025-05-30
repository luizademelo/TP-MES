
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryHttp2Tests, ConnectivityWatch) {
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS, 1000)
                 .Set(GRPC_ARG_MAX_RECONNECT_BACKOFF_MS, 1000)
                 .Set(GRPC_ARG_MIN_RECONNECT_BACKOFF_MS, 5000));

  EXPECT_EQ(CheckConnectivityState(false), GRPC_CHANNEL_IDLE);
  Step(Duration::Milliseconds(100));
  EXPECT_EQ(CheckConnectivityState(false), GRPC_CHANNEL_IDLE);

  WatchConnectivityState(GRPC_CHANNEL_IDLE, Duration::Milliseconds(500), 1);
  Expect(1, false);
  Step(Duration::Minutes(1));

  EXPECT_EQ(CheckConnectivityState(true), GRPC_CHANNEL_IDLE);

  WatchConnectivityState(GRPC_CHANNEL_IDLE, Duration::Seconds(10), 2);

  Expect(2, true);
  Step();
  grpc_connectivity_state state = CheckConnectivityState(false);
  EXPECT_THAT(state, ::testing::AnyOf(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                      GRPC_CHANNEL_CONNECTING));

  WatchConnectivityState(GRPC_CHANNEL_CONNECTING, Duration::Seconds(10), 3);
  Expect(3, true);
  Step();
  state = CheckConnectivityState(false);
  EXPECT_EQ(state, GRPC_CHANNEL_TRANSIENT_FAILURE);

  InitServer(ChannelArgs());

  WatchConnectivityState(state, Duration::Seconds(10), 4);
  Expect(4, true);
  Step(Duration::Seconds(20));
  state = CheckConnectivityState(false);
  EXPECT_EQ(state, GRPC_CHANNEL_READY);

  WatchConnectivityState(GRPC_CHANNEL_READY, Duration::Seconds(10), 5);
  ShutdownServerAndNotify(1000);
  Expect(5, true);
  Expect(1000, true);
  Step();
  state = CheckConnectivityState(false);
  EXPECT_EQ(state, GRPC_CHANNEL_IDLE);
}

}
}
