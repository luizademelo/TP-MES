
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/status.h>

#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryTests, RetrySendInitialMetadataRefs) {
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
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(5)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);
  c.NewBatch(1)
      .SendInitialMetadata(
          {
           {"foo", "bar"},

           {std::string(GRPC_SLICE_INLINED_SIZE + 1, 'x'),
            std::string(GRPC_SLICE_INLINED_SIZE + 1, 'y')}})
      .SendMessage("foo")
      .SendCloseFromClient();
  Expect(1, true);
  Step();
  IncomingMessage server_message;
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(2)
      .RecvMessage(server_message)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = RequestCall(101);
  Expect(101, true);
  Step();

  EXPECT_EQ(s.GetInitialMetadata("grpc-previous-rpc-attempts"), std::nullopt);
  EXPECT_NE(s.GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);
  Step();
  auto s2 = RequestCall(201);
  Expect(201, true);
  Step();

  EXPECT_EQ(s2.GetInitialMetadata("grpc-previous-rpc-attempts"), "1");

  EXPECT_EQ(s2.GetInitialMetadata("foo"), "bar");
  EXPECT_EQ(
      s2.GetInitialMetadata(std::string(GRPC_SLICE_INLINED_SIZE + 1, 'x')),
      std::string(GRPC_SLICE_INLINED_SIZE + 1, 'y'));
  EXPECT_NE(s.GetPeer(), std::nullopt);
  EXPECT_NE(c.GetPeer(), std::nullopt);
  IncomingMessage client_message;
  s2.NewBatch(202).RecvMessage(client_message);
  IncomingCloseOnServer client_close2;
  s2.NewBatch(203)
      .SendInitialMetadata({})
      .SendMessage("bar")
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {})
      .RecvCloseOnServer(client_close2);
  Expect(202, true);
  Expect(203, true);
  Expect(2, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status.message(), IsErrorFlattenEnabled() ? "" : "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
}

}
}
