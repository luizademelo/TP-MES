
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {

CORE_END2END_TEST(CoreEnd2endTests, CancelBeforeInvoke6) {
  auto c = NewClientCall("/service/method").Create();
  c.Cancel();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024))
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message);
  Expect(1, AnyStatus());
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelBeforeInvoke5) {
  auto c = NewClientCall("/service/method").Create();
  c.Cancel();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024))
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata);
  Expect(1, AnyStatus());
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelBeforeInvoke4) {
  auto c = NewClientCall("/service/method").Create();
  c.Cancel();
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024))
      .SendCloseFromClient();
  Expect(1, AnyStatus());
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelBeforeInvoke3) {
  auto c = NewClientCall("/service/method").Create();
  c.Cancel();
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024));
  Expect(1, AnyStatus());
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelBeforeInvoke2) {
  auto c = NewClientCall("/service/method").Create();
  c.Cancel();
  IncomingStatusOnClient server_status;
  c.NewBatch(1).RecvStatusOnClient(server_status).SendInitialMetadata({});
  Expect(1, AnyStatus());
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelBeforeInvoke1) {
  auto c = NewClientCall("/service/method").Create();
  c.Cancel();
  IncomingStatusOnClient server_status;
  c.NewBatch(1).RecvStatusOnClient(server_status);
  Expect(1, AnyStatus());
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
}

}
