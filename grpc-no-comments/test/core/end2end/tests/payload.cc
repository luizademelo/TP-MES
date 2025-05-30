
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {

namespace {
void RequestResponseWithPayload(CoreEnd2endTest& test) {

  auto request_slice = RandomSlice(1024 * 1024);
  auto response_slice = RandomSlice(1024 * 1024);

  auto c = test.NewClientCall("/foo").Timeout(Duration::Seconds(60)).Create();

  IncomingMetadata server_initial_md;
  IncomingMessage server_message;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage(request_slice.Ref())
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_md)
      .RecvMessage(server_message)
      .RecvStatusOnClient(server_status);

  CoreEnd2endTest::IncomingCall s = test.RequestCall(101);
  test.Expect(101, true);
  test.Step();

  IncomingMessage client_message;
  s.NewBatch(102).SendInitialMetadata({}).RecvMessage(client_message);
  test.Expect(102, true);
  test.Step();

  IncomingCloseOnServer client_close;
  s.NewBatch(103)
      .RecvCloseOnServer(client_close)
      .SendMessage(response_slice.Ref())
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});
  test.Expect(103, true);
  test.Expect(1, true);
  test.Step();

  EXPECT_EQ(server_status.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status.message(), IsErrorFlattenEnabled() ? "" : "xyz");
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(client_message.payload(), request_slice);
  EXPECT_EQ(server_message.payload(), response_slice);
}
}

CORE_END2END_TEST(CoreLargeSendTests, RequestResponseWithPayload) {
  RequestResponseWithPayload(*this);
}

CORE_END2END_TEST(CoreLargeSendTests, RequestResponseWithPayload10Times) {
  for (int i = 0; i < 10; i++) {
    RequestResponseWithPayload(*this);
  }
}

}
