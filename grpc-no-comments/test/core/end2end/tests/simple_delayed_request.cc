
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(Http2SingleHopTests, SimpleDelayedRequestShort) {
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS, 1000)
                 .Set(GRPC_ARG_MAX_RECONNECT_BACKOFF_MS, 1000)
                 .Set(GRPC_ARG_MIN_RECONNECT_BACKOFF_MS, 5000));
  LOG(ERROR) << "Create client side call";
  auto c = NewClientCall("/foo").Timeout(Duration::Minutes(1)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
  LOG(ERROR) << "Start initial batch";
  c.NewBatch(1)
      .SendInitialMetadata({}, GRPC_INITIAL_METADATA_WAIT_FOR_READY)
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  LOG(ERROR) << "Start server";
  InitServer(ChannelArgs());
  auto s = RequestCall(101);
  Expect(101, true);
  Step();
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  Expect(102, true);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_FALSE(client_close.was_cancelled());
}

}
}
