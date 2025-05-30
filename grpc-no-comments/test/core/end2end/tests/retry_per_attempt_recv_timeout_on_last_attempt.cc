
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>
#include <optional>

#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryTests, RetryPerAttemptRecvTimeoutOnLastAttempt) {
  SKIP_IF_V3();
  InitServer(ChannelArgs());
  InitClient(
      ChannelArgs()
          .Set(GRPC_ARG_EXPERIMENTAL_ENABLE_HEDGING, true)
          .Set(
              GRPC_ARG_SERVICE_CONFIG,
              absl::StrFormat(
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
                  "      \"perAttemptRecvTimeout\": \"%ds\",\n"
                  "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
                  "    }\n"
                  "  } ]\n"
                  "}",
                  2 * grpc_test_slowdown_factor())));
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(10)).Create();
  IncomingMessage server_message;
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .RecvMessage(server_message)
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);

  std::optional<IncomingCall> s0 = RequestCall(101);
  Expect(101, true);
  Step();

  EXPECT_EQ(s0->GetInitialMetadata("grpc-previous-rpc-attempts"), std::nullopt);

  std::optional<IncomingCall> s1 = RequestCall(201);
  Expect(201, true);
  Step();

  s0.reset();

  EXPECT_EQ(s1->GetInitialMetadata("grpc-previous-rpc-attempts"), "1");

  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_CANCELLED);
  EXPECT_THAT(server_status.message(),
              ::testing::HasSubstr("retry perAttemptRecvTimeout exceeded"));
  EXPECT_EQ(s1->method(), "/service/method");
}

}
}
