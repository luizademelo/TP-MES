
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(CoreDeadlineTests, NegativeDeadline) {
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(-1)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .RecvInitialMetadata(server_initial_metadata)
      .SendInitialMetadata({})
      .SendCloseFromClient();
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_DEADLINE_EXCEEDED);
}

}
}
