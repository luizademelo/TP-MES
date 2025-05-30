
// Copyright 2017 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(RetryHttp2Tests, RetryTransparentMaxConcurrentStreams) {
  const auto server_args =
      ChannelArgs()
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS, 1)
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION, false);
  InitServer(server_args);
  InitClient(ChannelArgs());
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Minutes(1)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message)
      .RecvStatusOnClient(server_status);

  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  EXPECT_EQ(s.method(), "/service/method");

  auto c2 =
      NewClientCall("/service/method").Timeout(Duration::Minutes(1)).Create();
  IncomingStatusOnClient server_status2;
  IncomingMetadata server_initial_metadata2;
  IncomingMessage server_message2;
  c2.NewBatch(2)
      .SendInitialMetadata({}, GRPC_INITIAL_METADATA_WAIT_FOR_READY)
      .SendMessage("bar")
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata2)
      .RecvMessage(server_message2)
      .RecvStatusOnClient(server_status2);

  ShutdownServerAndNotify(102);

  IncomingMessage client_message;
  s.NewBatch(103).RecvMessage(client_message);
  Expect(103, true);
  Step();
  IncomingCloseOnServer client_close;
  s.NewBatch(104)
      .RecvCloseOnServer(client_close)
      .SendInitialMetadata({})
      .SendMessage("baz")
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});

  Expect(104, true);
  Expect(102, true);
  Expect(1, true);
  Step();

  EXPECT_EQ(client_message.payload(), "foo");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(server_message.payload(), "baz");
  EXPECT_EQ(server_status.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status.message(), IsErrorFlattenEnabled() ? "" : "xyz");

  absl::SleepFor(absl::Milliseconds(250));
  InitServer(server_args);

  auto s2 = RequestCall(201);
  Expect(201, true);

  Step(Duration::Seconds(30));
  EXPECT_EQ(s2.method(), "/service/method");

  EXPECT_EQ(s2.GetInitialMetadata("grpc-previous-rpc-attempts"), std::nullopt);

  IncomingMessage client_message2;
  IncomingCloseOnServer client_close2;
  s2.NewBatch(202).RecvMessage(client_message2);
  Expect(202, true);
  Step();
  s2.NewBatch(203)
      .RecvCloseOnServer(client_close2)
      .SendInitialMetadata({})
      .SendMessage("qux")
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});

  Expect(203, true);
  Expect(2, true);
  Step();

  EXPECT_EQ(client_message2.payload(), "bar");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(server_message2.payload(), "qux");
  EXPECT_EQ(server_status2.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status2.message(), IsErrorFlattenEnabled() ? "" : "xyz");
}
}
}
