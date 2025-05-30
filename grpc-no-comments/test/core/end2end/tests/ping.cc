
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

CORE_END2END_TEST(RetryHttp2Tests, Ping) {
  const int kPingCount = 5;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0)
                 .Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1));
  InitServer(ChannelArgs()
                 .Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 0)
                 .Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1));
  PingServerFromClient(0);
  Expect(0, false);
  Step();

  EXPECT_EQ(CheckConnectivityState(true), GRPC_CHANNEL_IDLE);

  while (state != GRPC_CHANNEL_READY) {
    WatchConnectivityState(state, Duration::Seconds(3), 99);
    Expect(99, true);
    Step();
    state = CheckConnectivityState(false);
    EXPECT_THAT(state,
                ::testing::AnyOf(GRPC_CHANNEL_READY, GRPC_CHANNEL_CONNECTING,
                                 GRPC_CHANNEL_TRANSIENT_FAILURE));
  }
  for (int i = 1; i <= kPingCount; i++) {
    PingServerFromClient(i);
    Expect(i, true);
    Step();
  }
  ShutdownServerAndNotify(1000);
  Expect(1000, true);
  Step();
}

}
}
