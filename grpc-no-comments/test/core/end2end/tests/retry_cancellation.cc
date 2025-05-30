
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/end2end/tests/cancel_test_helpers.h"

namespace grpc_core {
namespace {

void TestRetryCancellation(CoreEnd2endTest& test,
                           std::unique_ptr<CancellationMode> mode) {
  test.InitServer(ChannelArgs());
  test.InitClient(ChannelArgs().Set(
      GRPC_ARG_SERVICE_CONFIG,
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"service\", \"method\": \"method\" }\n"
      "    ],\n"
      "    \"retryPolicy\": {\n"
      "      \"maxAttempts\": 5,\n"
      "      \"initialBackoff\": \"1s\",\n"
      "      \"maxBackoff\": \"120s\",\n"
      "      \"backoffMultiplier\": 1.6,\n"
      "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
      "    },\n"
      "    \"timeout\": \"10s\"\n"
      "  } ]\n"
      "}"));
  auto c = test.NewClientCall("/service/method")
               .Timeout(Duration::Seconds(5))
               .Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .RecvMessage(server_message)
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);

  std::optional<CoreEnd2endTest::IncomingCall> s = test.RequestCall(101);
  test.Expect(101, true);
  test.Step();
  EXPECT_NE(s->GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);
  IncomingCloseOnServer client_close;
  s->NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  test.Expect(102, true);
  test.Step();
  s.reset();

  s.emplace(test.RequestCall(201));
  test.Expect(201, true);
  test.Step();

  mode->Apply(c);
  test.Expect(1, true);
  test.Step();
  EXPECT_EQ(server_status.status(), mode->ExpectedStatus());
  EXPECT_FALSE(client_close.was_cancelled());
}

CORE_END2END_TEST(RetryTests, RetryCancellation) {
  if (!IsRetryInCallv3Enabled()) SKIP_IF_V3();
  TestRetryCancellation(*this, std::make_unique<CancelCancellationMode>());
}

CORE_END2END_TEST(RetryTests, RetryDeadline) {
  if (!IsRetryInCallv3Enabled()) SKIP_IF_V3();
  TestRetryCancellation(*this, std::make_unique<DeadlineCancellationMode>());
}

}
}
