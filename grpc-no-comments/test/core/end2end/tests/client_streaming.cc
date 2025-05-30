
// Copyright 2020 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

void ClientStreaming(CoreEnd2endTest& test, int messages) {
  auto c = test.NewClientCall("/foo").Timeout(Duration::Seconds(30)).Create();

  IncomingMetadata server_initial_metadata;
  c.NewBatch(1).SendInitialMetadata({}).RecvInitialMetadata(
      server_initial_metadata);
  auto s = test.RequestCall(100);
  test.Expect(100, true);
  test.Step();
  s.NewBatch(101).SendInitialMetadata({});
  test.Expect(101, true);
  test.Expect(1, true);
  test.Step();

  for (int i = 0; i < messages; i++) {
    c.NewBatch(2).SendMessage("hello world");
    IncomingMessage client_message;
    s.NewBatch(102).RecvMessage(client_message);
    test.Expect(2, true);
    test.Expect(102, true);
    test.Step();
    EXPECT_EQ(client_message.payload(), "hello world");
  }

  s.NewBatch(103).SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  test.Expect(103, true);
  test.Step();

  test.Step();

  c.NewBatch(3).SendMessage("hello world");
  test.Expect(3, false);
  test.Step();

  IncomingStatusOnClient server_status;
  c.NewBatch(4).SendCloseFromClient().RecvStatusOnClient(server_status);
  test.Expect(4, true);
  test.Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
}

CORE_END2END_TEST(CoreEnd2endTests, ClientStreaming0) {
  ClientStreaming(*this, 0);
}
CORE_END2END_TEST(CoreEnd2endTests, ClientStreaming1) {
  ClientStreaming(*this, 1);
}
CORE_END2END_TEST(CoreEnd2endTests, ClientStreaming3) {
  ClientStreaming(*this, 3);
}
CORE_END2END_TEST(CoreEnd2endTests, ClientStreaming10) {
  ClientStreaming(*this, 10);
}
CORE_END2END_TEST(CoreEnd2endTests, ClientStreaming30) {
  ClientStreaming(*this, 30);
}

}
}
