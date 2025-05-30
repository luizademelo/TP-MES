
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include <memory>
#include <optional>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

using testing::AnyOf;
using testing::StartsWith;

namespace grpc_core {
namespace {

CORE_END2END_TEST(CoreClientChannelTests, DefaultHost) {
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);
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
  EXPECT_NE(s.GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/foo");
  if (test_config()->overridden_call_host != nullptr) {
    EXPECT_EQ(test_config()->overridden_call_host, s.host());
  } else {
    EXPECT_THAT(s.host(),
                AnyOf(StartsWith("localhost"), StartsWith("127.0.0.1"),
                      StartsWith("[::1]"), StartsWith("grpc_fullstack_test."),
                      StartsWith("tmp%2Fgrpc_fullstack_test."),
                      StartsWith("C:%2Ftmp%2Fgrpc_fullstack_test.")));
  }
  EXPECT_FALSE(client_close.was_cancelled());
}

}
}
