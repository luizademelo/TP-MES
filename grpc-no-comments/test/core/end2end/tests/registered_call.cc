
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include "gtest/gtest.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

void SimpleRequestBody(CoreEnd2endTest& test,
                       CoreEnd2endTest::RegisteredCall rc) {
  auto c = test.NewClientCall(rc).Timeout(Duration::Seconds(5)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = test.RequestCall(101);
  test.Expect(101, true);
  test.Step();
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  test.Expect(102, true);
  test.Expect(1, true);
  test.Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_FALSE(client_close.was_cancelled());
}

CORE_END2END_TEST(CoreEnd2endTests, InvokeRegisteredCall) {
  SimpleRequestBody(*this, RegisterCallOnClient("/foo", nullptr));
}

CORE_END2END_TEST(CoreEnd2endTests, Invoke10RegisteredCalls) {
  auto rc = RegisterCallOnClient("/foo", nullptr);
  for (int i = 0; i < 10; i++) {
    SimpleRequestBody(*this, rc);
  }
}

}
}
