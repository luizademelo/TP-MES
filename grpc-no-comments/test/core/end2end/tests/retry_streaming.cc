
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <optional>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/channelz/channelz.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

using testing::HasSubstr;

namespace grpc_core {
namespace {

// FIXME: We should also test the case where the retry is committed after

CORE_END2END_TEST(RetryTests, RetryStreaming) {
  SKIP_IF_V3();
  InitServer(ChannelArgs());
  InitClient(
      ChannelArgs()
          .Set(GRPC_ARG_MAX_CHANNEL_TRACE_EVENT_MEMORY_PER_NODE, 1024 * 8)
          .Set(GRPC_ARG_ENABLE_CHANNELZ, true)
          .Set(GRPC_ARG_SERVICE_CONFIG,
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
  channelz::ChannelNode* channelz_channel =
      grpc_channel_get_channelz_node(client());
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c.NewBatch(1)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message)
      .RecvStatusOnClient(server_status);

  c.NewBatch(2).SendInitialMetadata({}).SendMessage("foo");
  Expect(2, true);
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

  c.NewBatch(3).SendMessage("bar");
  Expect(3, true);
  Step();

  IncomingMessage client_message2;
  s.NewBatch(103).RecvMessage(client_message2);
  Expect(103, true);
  Step();

  IncomingCloseOnServer client_close;
  s.NewBatch(104)
      .RecvCloseOnServer(client_close)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {});
  Expect(104, true);
  Step();

  EXPECT_EQ(client_message.payload(), "foo");
  EXPECT_EQ(client_message2.payload(), "bar");

  auto s2 = RequestCall(201);
  Expect(201, true);
  Step();
  EXPECT_NE(s.GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMessage client_message3;
  s2.NewBatch(202).RecvMessage(client_message3);
  Expect(202, true);
  Step();

  IncomingMessage client_message4;
  s2.NewBatch(203).RecvMessage(client_message4);
  Expect(203, true);
  Step();

  c.NewBatch(4).SendMessage("baz").SendCloseFromClient();
  Expect(4, true);
  Step();

  IncomingMessage client_message5;
  s2.NewBatch(204).RecvMessage(client_message5);
  Expect(204, true);
  Step();

  IncomingCloseOnServer client_close2;
  s2.NewBatch(205)
      .RecvCloseOnServer(client_close2)
      .SendInitialMetadata({})
      .SendMessage("quux")

      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {});
  Expect(205, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_ABORTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_NE(channelz_channel, nullptr);

  std::string json = channelz_channel->RenderJsonString();
  EXPECT_THAT(json, HasSubstr("\"trace\""));
  EXPECT_THAT(json, HasSubstr("\"description\":\"Channel created\""));
  EXPECT_THAT(json, HasSubstr("\"severity\":\"CT_INFO\""));
  EXPECT_THAT(json, HasSubstr("Resolution event"));
  EXPECT_THAT(json, HasSubstr("Created new LB policy"));
  EXPECT_THAT(json, HasSubstr("Service config changed"));
  EXPECT_THAT(json, HasSubstr("Address list became non-empty"));
  EXPECT_THAT(json, HasSubstr("Channel state change to CONNECTING"));
  EXPECT_EQ(client_message3.payload(), "foo");
  EXPECT_EQ(client_message4.payload(), "bar");
  EXPECT_EQ(client_message5.payload(), "baz");
}

}
}
