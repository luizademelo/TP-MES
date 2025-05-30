
// Copyright 2015 gRPC authors.

#include <grpc/status.h>
#include <grpc/support/time.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(CoreEnd2endTests, EarlyServerShutdownFinishesInflightCalls) {
  SKIP_IF_V3();
  SKIP_IF_FUZZING();

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
  IncomingCloseOnServer client_close;
  s.NewBatch(102).RecvCloseOnServer(client_close);

  gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));

  ShutdownServerAndNotify(1000);
  CancelAllCallsOnServer();

  Expect(1000, true);
  Expect(102, true);
  Expect(1, true);
  Step();

  DestroyServer();

  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNAVAILABLE);
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_TRUE(client_close.was_cancelled());
}

}
}
