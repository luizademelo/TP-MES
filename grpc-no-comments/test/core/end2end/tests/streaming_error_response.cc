
// Copyright 2016 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(CoreEnd2endTests, StreamingErrorResponse) {
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingMessage response_payload1_recv;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(response_payload1_recv);
  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  s.NewBatch(102).SendInitialMetadata({}).SendMessage("hello");
  Expect(102, true);
  Expect(1, true);
  Step();
  s.NewBatch(103).SendMessage("world");

  Expect(103, AnyStatus());
  IncomingMessage response_payload2_recv;
  c.NewBatch(2).RecvMessage(response_payload2_recv);
  Expect(2, true);
  Step();
  EXPECT_FALSE(response_payload2_recv.is_end_of_stream());

  c.Cancel();
  IncomingCloseOnServer client_close;
  s.NewBatch(104).RecvCloseOnServer(client_close);
  Expect(104, true);
  Step();
  IncomingStatusOnClient server_status;
  c.NewBatch(3).RecvStatusOnClient(server_status);
  Expect(3, true);
  Step();
  EXPECT_FALSE(response_payload1_recv.is_end_of_stream());
  EXPECT_FALSE(response_payload2_recv.is_end_of_stream());
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
  EXPECT_TRUE(client_close.was_cancelled());
}

CORE_END2END_TEST(CoreEnd2endTests, StreamingErrorResponseRequestStatusEarly) {
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingMessage response_payload1_recv;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(response_payload1_recv)
      .RecvStatusOnClient(server_status);
  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  s.NewBatch(102).SendInitialMetadata({}).SendMessage("hello");
  Expect(102, true);
  Step();
  s.NewBatch(103).SendMessage("world");

  Expect(103, AnyStatus());

  c.Cancel();
  IncomingCloseOnServer client_close;
  s.NewBatch(104).RecvCloseOnServer(client_close);
  Expect(104, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
  EXPECT_TRUE(client_close.was_cancelled());
}

CORE_END2END_TEST(
    CoreEnd2endTests,
    StreamingErrorResponseRequestStatusEarlyAndRecvMessageSeparately) {
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  s.NewBatch(102).SendInitialMetadata({}).SendMessage("hello");
  IncomingMessage response_payload1_recv;
  c.NewBatch(4).RecvMessage(response_payload1_recv);
  Expect(102, true);
  Expect(4, true);
  Step();
  s.NewBatch(103).SendMessage("world");

  Expect(103, AnyStatus());

  c.Cancel();
  IncomingCloseOnServer client_close;
  s.NewBatch(104).RecvCloseOnServer(client_close);
  Expect(104, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
  EXPECT_TRUE(client_close.was_cancelled());
}

}
}
