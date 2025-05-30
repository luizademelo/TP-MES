
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>

#include <memory>
#include <optional>

#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryTests, RetryCancelAfterFirstAttemptStarts) {
  if (!IsRetryInCallv3Enabled()) SKIP_IF_V3();

  InitServer(ChannelArgs().Set(GRPC_ARG_PING_TIMEOUT_MS, 4000));
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
  std::optional<Call> c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(6)).Create();

  c->NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .SendCloseFromClient();

  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c->NewBatch(2)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message);

  IncomingStatusOnClient server_status;
  c->NewBatch(3).RecvStatusOnClient(server_status);

  c.reset();

  Expect(1, AnyStatus());
  Expect(2, AnyStatus());
  Expect(3, true);
  Step();
}

}
}
