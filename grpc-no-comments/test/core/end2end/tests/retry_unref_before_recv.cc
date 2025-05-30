
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryTests, UnrefBeforeRecv) {
  if (!IsRetryInCallv3Enabled()) SKIP_IF_V3();
  InitServer(ChannelArgs());
  InitClient(ChannelArgs().Set(
      GRPC_ARG_SERVICE_CONFIG,
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"service\", \"method\": \"method\" }\n"
      "    ],\n"
      "    \"retryPolicy\": {\n"
      "      \"maxAttempts\": 3,\n"
      "      \"initialBackoff\": \"1s\",\n"
      "      \"maxBackoff\": \"120s\",\n"
      "      \"backoffMultiplier\": 1.6,\n"
      "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
      "    }\n"
      "  } ]\n"
      "}"));
  std::optional<Call> c{
      NewClientCall("/service/method").Timeout(Duration::Seconds(60)).Create()};

  c->NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .SendCloseFromClient();

  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c->NewBatch(2)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message);

  auto s = RequestCall(101);
  Expect(1, true);
  Expect(101, true);
  Step();

  c.reset();

  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_FAILED_PRECONDITION, "xyz", {})
      .RecvCloseOnServer(client_close);

  if (test_config()->feature_mask & FEATURE_MASK_IS_CALL_V3) {

    Expect(2, true);
  } else {
    Expect(2, false);
  }
  Expect(102, true);
  Step();

  EXPECT_EQ(s.method(), "/service/method");
  // Note: Not checking the value of was_cancelled here, because it will

}

}
}
