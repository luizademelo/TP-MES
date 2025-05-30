
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {

static void OneRequestAndShutdownServer(CoreEnd2endTest& test) {
  LOG(ERROR) << "Create client side call";
  auto c = test.NewClientCall("/service/method")
               .Timeout(Duration::Seconds(30))
               .Create();
  IncomingMetadata server_initial_md;
  IncomingStatusOnClient server_status;
  LOG(ERROR) << "Start initial batch";
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_md)
      .RecvStatusOnClient(server_status);
  auto s = test.RequestCall(101);
  test.Expect(101, true);
  test.Step();
  test.ShutdownServerAndNotify(1000);
  IncomingCloseOnServer client_closed;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_closed);
  test.Expect(102, true);
  test.Expect(1, true);
  test.Expect(1000, true);
  test.Step();

  test.Step();

  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_closed.was_cancelled());
}

CORE_END2END_TEST(CoreClientChannelTests, DisappearingServer) {

  SKIP_IF_V3();
  OneRequestAndShutdownServer(*this);
  InitServer(ChannelArgs());
  OneRequestAndShutdownServer(*this);
}

}
