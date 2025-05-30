
// Copyright 2015 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

void SimpleRequestBody(CoreEnd2endTest& test) {
  auto c = test.NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  auto s = test.RequestCall(101);
  test.Expect(101, true);
  test.Step();
  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {})
      .RecvCloseOnServer(client_close);
  test.Expect(102, true);
  test.Expect(1, true);
  test.Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNIMPLEMENTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/foo");
  EXPECT_FALSE(client_close.was_cancelled());
}

CORE_END2END_TEST(Http2SingleHopTests, MaxConcurrentStreams) {
  SKIP_IF_MINSTACK();
  InitServer(
      ChannelArgs()
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS, 1)
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION, false));
  InitClient(ChannelArgs());

  SimpleRequestBody(*this);

  SimpleRequestBody(*this);

  auto c1 = NewClientCall("/alpha").Timeout(Duration::Seconds(1000)).Create();
  auto c2 = NewClientCall("/beta").Timeout(Duration::Seconds(1000)).Create();
  auto s1 = RequestCall(101);
  c1.NewBatch(301).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata1;
  IncomingStatusOnClient server_status1;
  c1.NewBatch(302)
      .RecvStatusOnClient(server_status1)
      .RecvInitialMetadata(server_initial_metadata1);
  c2.NewBatch(401).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata2;
  IncomingStatusOnClient server_status2;
  c2.NewBatch(402)
      .RecvStatusOnClient(server_status2)
      .RecvInitialMetadata(server_initial_metadata2);
  bool got_client_start = false;
  bool got_server_start = false;
  int live_call;
  Expect(101, MaybePerformAction{[&got_server_start](bool ok) {
           EXPECT_TRUE(ok);
           got_server_start = ok;
         }});
  Expect(301, MaybePerformAction{[&got_client_start, &live_call](bool ok) {
           EXPECT_FALSE(got_client_start);
           EXPECT_TRUE(ok);
           got_client_start = ok;
           live_call = 300;
         }});
  Expect(401, MaybePerformAction{[&got_client_start, &live_call](bool ok) {
           EXPECT_FALSE(got_client_start);
           EXPECT_TRUE(ok);
           got_client_start = ok;
           live_call = 400;
         }});
  Step();
  if (got_client_start && !got_server_start) {
    Expect(101, true);
    Step();
    got_server_start = true;
  } else if (got_server_start && !got_client_start) {
    Expect(301, MaybePerformAction{[&got_client_start, &live_call](bool ok) {
             EXPECT_FALSE(got_client_start);
             EXPECT_TRUE(ok);
             got_client_start = ok;
             live_call = 300;
           }});
    Expect(401, MaybePerformAction{[&got_client_start, &live_call](bool ok) {
             EXPECT_FALSE(got_client_start);
             EXPECT_TRUE(ok);
             got_client_start = ok;
             live_call = 400;
           }});
    Step();
    EXPECT_TRUE(got_client_start);
  }
  IncomingCloseOnServer client_close;
  s1.NewBatch(102)
      .SendInitialMetadata({})
      .RecvCloseOnServer(client_close)
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  Expect(102, true);
  Expect(live_call + 2, true);

  live_call = (live_call == 300) ? 400 : 300;
  Expect(live_call + 1, true);
  Step();

  Step();
  auto s2 = RequestCall(201);
  Expect(201, true);
  Step();
  s2.NewBatch(202)
      .SendInitialMetadata({})
      .RecvCloseOnServer(client_close)
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  Expect(live_call + 2, true);
  Expect(202, true);
  Step();
}

CORE_END2END_TEST(Http2SingleHopTests, MaxConcurrentStreamsTimeoutOnFirst) {
  SKIP_IF_MINSTACK();
  InitServer(
      ChannelArgs()
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS, 1)
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION, false));
  InitClient(ChannelArgs());

  SimpleRequestBody(*this);

  SimpleRequestBody(*this);

  auto c1 = NewClientCall("/alpha").Timeout(Duration::Seconds(3)).Create();
  auto c2 = NewClientCall("/beta").Timeout(Duration::Seconds(1000)).Create();
  auto s1 = RequestCall(101);
  c1.NewBatch(301).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata1;
  IncomingStatusOnClient server_status1;
  c1.NewBatch(302)
      .RecvStatusOnClient(server_status1)
      .RecvInitialMetadata(server_initial_metadata1);
  Expect(101, true);
  Expect(301, true);
  Step();
  c2.NewBatch(401).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata2;
  IncomingStatusOnClient server_status2;
  c2.NewBatch(402)
      .RecvStatusOnClient(server_status2)
      .RecvInitialMetadata(server_initial_metadata2);
  auto s2 = RequestCall(201);
  Expect(302, true);

  Expect(401, true);
  Expect(201, true);
  Step();
  IncomingCloseOnServer client_close2;
  s2.NewBatch(202)
      .SendInitialMetadata({})
      .RecvCloseOnServer(client_close2)
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  Expect(402, true);
  Expect(202, true);
  Step();
}

CORE_END2END_TEST(Http2SingleHopTests, MaxConcurrentStreamsTimeoutOnSecond) {
  SKIP_IF_MINSTACK();
  InitServer(
      ChannelArgs()
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS, 1)
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION, false));
  InitClient(ChannelArgs());

  SimpleRequestBody(*this);

  SimpleRequestBody(*this);

  auto c1 = NewClientCall("/alpha").Timeout(Duration::Seconds(1000)).Create();
  auto c2 = NewClientCall("/beta").Timeout(Duration::Seconds(3)).Create();
  auto s1 = RequestCall(101);
  c1.NewBatch(301).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata1;
  IncomingStatusOnClient server_status1;
  c1.NewBatch(302)
      .RecvStatusOnClient(server_status1)
      .RecvInitialMetadata(server_initial_metadata1);
  Expect(101, true);
  Expect(301, true);
  Step();
  c2.NewBatch(401).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata2;
  IncomingStatusOnClient server_status2;
  c2.NewBatch(402)
      .RecvStatusOnClient(server_status2)
      .RecvInitialMetadata(server_initial_metadata2);

  Expect(401, false);
  Expect(402, true);
  Step();

  IncomingCloseOnServer client_close1;
  s1.NewBatch(102)
      .SendInitialMetadata({})
      .RecvCloseOnServer(client_close1)
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  Expect(302, true);
  Expect(102, true);
  Step();
  EXPECT_EQ(server_status2.status(), GRPC_STATUS_DEADLINE_EXCEEDED);
}

CORE_END2END_TEST(Http2SingleHopTests, MaxConcurrentStreamsRejectOnClient) {
  SKIP_IF_MINSTACK();
  InitServer(
      ChannelArgs()
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS, 1)
          .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION, false));
  InitClient(ChannelArgs()
                 .Set(GRPC_ARG_MAX_CONCURRENT_STREAMS_REJECT_ON_CLIENT, true)
                 .Set(GRPC_ARG_ENABLE_RETRIES, false));

  SimpleRequestBody(*this);
  auto c1 = NewClientCall("/alpha").Timeout(Duration::Seconds(1000)).Create();
  auto c2 = NewClientCall("/beta").Timeout(Duration::Seconds(3)).Create();
  auto s1 = RequestCall(101);
  c1.NewBatch(301).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata1;
  IncomingStatusOnClient server_status1;
  c1.NewBatch(302)
      .RecvStatusOnClient(server_status1)
      .RecvInitialMetadata(server_initial_metadata1);
  Expect(101, true);
  Expect(301, true);
  Step();
  c2.NewBatch(401).SendInitialMetadata({}).SendCloseFromClient();
  IncomingMetadata server_initial_metadata2;
  IncomingStatusOnClient server_status2;
  c2.NewBatch(402)
      .RecvStatusOnClient(server_status2)
      .RecvInitialMetadata(server_initial_metadata2);

  Expect(401, false);
  Expect(402, true);
  Step();

  IncomingCloseOnServer client_close1;
  s1.NewBatch(102)
      .SendInitialMetadata({})
      .RecvCloseOnServer(client_close1)
      .SendStatusFromServer(GRPC_STATUS_UNIMPLEMENTED, "xyz", {});
  Expect(302, true);
  Expect(102, true);
  Step();
  EXPECT_EQ(server_status2.status(), GRPC_STATUS_RESOURCE_EXHAUSTED);
}

}
}
