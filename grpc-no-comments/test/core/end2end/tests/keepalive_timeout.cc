
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>

#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(Http2SingleHopTests, KeepaliveTimeout) {

  InitServer(ChannelArgs().Set("grpc.http2.ack_pings", false));
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_KEEPALIVE_TIME_MS, 10)
                 .Set(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 0)
                 .Set(GRPC_ARG_PING_TIMEOUT_MS, 0)
                 .Set(GRPC_ARG_HTTP2_BDP_PROBE, false));
  auto c = NewClientCall("/foo").Timeout(Duration::Minutes(1)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNAVAILABLE);
  EXPECT_THAT(server_status.message(), ::testing::HasSubstr("ping timeout"));
}

CORE_END2END_TEST(Http2SingleHopTests, ReadDelaysKeepalive) {
#ifdef GRPC_POSIX_SOCKET

  if (ConfigVars::Get().PollStrategy() == "poll") {
    GTEST_SKIP() << "Skipping test under poll poller";
  }
#endif
  const auto kPingInterval = Duration::Milliseconds(100);

  InitServer(ChannelArgs().Set("grpc.http2.ack_pings", false));
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_KEEPALIVE_TIME_MS, (20 * kPingInterval).millis())
                 .Set(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 0)
                 .Set(GRPC_ARG_HTTP2_BDP_PROBE, false));
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(60)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = RequestCall(100);
  Expect(100, true);
  Step();
  IncomingCloseOnServer client_close;
  s.NewBatch(101).SendInitialMetadata({}).RecvCloseOnServer(client_close);
  for (int i = 0; i < 30; i++) {
    IncomingMessage server_message;
    IncomingMessage client_message;
    c.NewBatch(2).SendMessage("hello world").RecvMessage(server_message);
    s.NewBatch(102).RecvMessage(client_message);
    Expect(102, true);
    Step();
    s.NewBatch(103).SendMessage("hello you");
    Expect(103, true);
    Expect(2, true);
    Step();

    Step(kPingInterval);
  }
  c.NewBatch(3).SendCloseFromClient();
  s.NewBatch(104).SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  Expect(1, true);
  Expect(3, true);
  Expect(101, true);
  Expect(104, true);
  Step();
}

}
}
