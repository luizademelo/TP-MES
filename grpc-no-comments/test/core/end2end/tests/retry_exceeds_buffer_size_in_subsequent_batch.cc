
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryTests, RetryExceedsBufferSizeInSubsequentBatch) {
  SKIP_IF_V3();
  InitServer(ChannelArgs());
  InitClient(
      ChannelArgs()
          .Set(GRPC_ARG_SERVICE_CONFIG,
               "{\n"
               "  \"methodConfig\": [ {\n"
               "    \"name\": [\n"
               "      { \"service\": \"service\", \"method\": \"method\" }\n"
               "    ],\n"
               "    \"retryPolicy\": {\n"
               "      \"maxAttempts\": 2,\n"
               "      \"initialBackoff\": \"1s\",\n"
               "      \"maxBackoff\": \"120s\",\n"
               "      \"backoffMultiplier\": 1.6,\n"
               "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
               "    }\n"
               "  } ]\n"
               "}")
          .Set(GRPC_ARG_PER_RPC_RETRY_BUFFER_SIZE, 102400));
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(5)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);
  c.NewBatch(1).SendInitialMetadata({});
  Expect(1, true);
  Step();
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  IncomingStatusOnClient server_status;
  c.NewBatch(2)
      .SendMessage(std::string(102400, 'a'))
      .RecvMessage(server_message)
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
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);
  Expect(2, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_ABORTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
}

}
}
