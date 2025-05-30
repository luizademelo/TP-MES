
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

CORE_END2END_TEST(RetryTests, RetryStreamingAfterCommit) {
  SKIP_IF_V3();
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
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Minutes(1)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMessage server_message;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(2)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message);

  c.NewBatch(3).SendInitialMetadata({}).SendMessage("foo");
  Expect(3, true);
  Step();

  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  EXPECT_NE(s.GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMessage client_message;
  s.NewBatch(102).RecvMessage(client_message);
  Expect(102, true);
  Step();

  s.NewBatch(103).SendInitialMetadata({}).SendMessage("bar");
  Expect(103, true);

  Expect(2, true);
  Step();

  c.NewBatch(4).SendMessage("baz").SendCloseFromClient();
  Expect(4, true);
  Step();

  IncomingMessage client_message2;
  s.NewBatch(104).RecvMessage(client_message2);
  Expect(104, true);
  Step();

  IncomingCloseOnServer client_close;
  s.NewBatch(105)
      .RecvCloseOnServer(client_close)
      .SendMessage("quux")
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {});
  Expect(105, true);
  Step();

  IncomingMessage server_message2;
  c.NewBatch(5).RecvMessage(server_message2);
  Expect(5, true);
  Step();

  IncomingStatusOnClient server_status;
  c.NewBatch(1).RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_ABORTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(client_message.payload(), "foo");
  EXPECT_EQ(server_message.payload(), "bar");
  EXPECT_EQ(client_message2.payload(), "baz");
  EXPECT_EQ(server_message2.payload(), "quux");
}

}
}
