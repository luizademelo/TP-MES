
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

CORE_END2END_TEST(RetryTests, RetryStreamSucceedsBeforeReplayFinished) {
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
      NewClientCall("/service/method").Timeout(Duration::Seconds(5)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message)
      .RecvStatusOnClient(server_status);

  c.NewBatch(2).SendInitialMetadata({}).SendMessage("foo");
  Expect(2, true);
  Step();

  std::optional<IncomingCall> s = RequestCall(101);
  Expect(101, true);
  Step();
  EXPECT_NE(s->GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMessage client_message;
  s->NewBatch(102).RecvMessage(client_message);
  Expect(102, true);
  Step();

  c.NewBatch(3).SendMessage("bar");
  Expect(3, true);
  Step();

  IncomingMessage client_message2;
  s->NewBatch(103).RecvMessage(client_message2);
  Expect(103, true);
  Step();

  c.NewBatch(4).SendMessage("baz");
  Expect(4, true);
  Step();

  IncomingMessage client_message3;
  s->NewBatch(104).RecvMessage(client_message3);
  Expect(104, true);
  Step();

  IncomingCloseOnServer client_close;
  s->NewBatch(105)
      .RecvCloseOnServer(client_close)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {});
  Expect(105, true);
  Step();

  s.reset();
  EXPECT_EQ(client_message.payload(), "foo");
  EXPECT_EQ(client_message2.payload(), "bar");
  EXPECT_EQ(client_message3.payload(), "baz");

  s.emplace(RequestCall(201));
  Expect(201, true);
  Step();
  EXPECT_NE(s->GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMessage client_message4;
  s->NewBatch(202).RecvMessage(client_message4);
  Expect(202, true);
  Step();

  s->NewBatch(205)
      .SendInitialMetadata({})
      .SendMessage("qux")

      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {});
  Expect(205, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_ABORTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s->method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(client_message4.payload(), "foo");
}

}
}
