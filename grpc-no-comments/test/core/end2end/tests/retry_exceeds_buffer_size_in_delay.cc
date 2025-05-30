
// Copyright 2021 gRPC authors.

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

CORE_END2END_TEST(RetryTests, RetryExceedsBufferSizeInDelay) {
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
               "      \"maxAttempts\": 3,\n"
               "      \"initialBackoff\": \"2s\",\n"
               "      \"maxBackoff\": \"120s\",\n"
               "      \"backoffMultiplier\": 1.6,\n"
               "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
               "    }\n"
               "  } ]\n"
               "}")
          .Set(GRPC_ARG_PER_RPC_RETRY_BUFFER_SIZE, 102400));
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(15)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMessage server_message;
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .RecvMessage(server_message)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);

  std::optional<IncomingCall> s = RequestCall(101);
  Expect(101, true);
  Step();
  EXPECT_NE(s->GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingCloseOnServer client_close;
  s->NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "message1", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);
  Step();
  s.reset();

  Step(Duration::Seconds(1));

  c.NewBatch(2).SendMessage(std::string(102401, 'a')).SendCloseFromClient();
  Expect(2, true);
  Step();

  auto s2 = RequestCall(201);
  Expect(201, true);
  Step();

  IncomingCloseOnServer client_close2;
  s2.NewBatch(202)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "message2", {})
      .RecvCloseOnServer(client_close2);
  Expect(202, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_ABORTED);
  EXPECT_EQ(server_status.message(), "message2");
  EXPECT_EQ(s2.method(), "/service/method");
  EXPECT_FALSE(client_close2.was_cancelled());
}

}
}
