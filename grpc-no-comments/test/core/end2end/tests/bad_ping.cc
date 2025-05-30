
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

#define MAX_PING_STRIKES 2

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryHttp2Tests, BadPing) {
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0)
                 .Set(GRPC_ARG_HTTP2_BDP_PROBE, 0));
  InitServer(ChannelArgs()
                 .Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS,
                      Duration::Minutes(5).millis())
                 .Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, MAX_PING_STRIKES)
                 .Set(GRPC_ARG_HTTP2_BDP_PROBE, 0));
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(10)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = RequestCall(101);
  Expect(101, true);
  Step();

  int i;
  for (i = 1; i <= MAX_PING_STRIKES + 2; i++) {
    PingServerFromClient(200 + i);
    Expect(200 + i, true);
    if (i == MAX_PING_STRIKES + 2) {
      Expect(1, true);
    }
    Step();
  }
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);
  Step();
  ShutdownServerAndNotify(103);
  Expect(103, true);
  Step();

  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNAVAILABLE);
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_TRUE(client_close.was_cancelled());
}

CORE_END2END_TEST(RetryHttp2Tests, PingsWithoutData) {
  if (IsMaxPingsWoDataThrottleEnabled()) {
    GTEST_SKIP() << "pings are not limited if this experiment is enabled";
  }

  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, MAX_PING_STRIKES)
                 .Set(GRPC_ARG_HTTP2_BDP_PROBE, 0));
  InitServer(ChannelArgs()
                 .Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS,
                      Duration::Minutes(5).millis())
                 .Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, MAX_PING_STRIKES)
                 .Set(GRPC_ARG_HTTP2_BDP_PROBE, 0));
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(10)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = RequestCall(101);
  Expect(101, true);
  Step();

  int i;
  for (i = 1; i <= MAX_PING_STRIKES + 2; i++) {
    PingServerFromClient(200 + i);
    if (i <= MAX_PING_STRIKES) {
      Expect(200 + i, true);
    }
    Step();
  }
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);

  Expect(1, true);
  Step();
  ShutdownServerAndNotify(103);
  Expect(103, true);

  Expect(200 + MAX_PING_STRIKES + 1, false);
  Expect(200 + MAX_PING_STRIKES + 2, false);
  Step();

  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(s.method(), "/foo");
}

}
}
