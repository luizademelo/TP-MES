
// Copyright 2015 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

void SimpleRequest(CoreEnd2endTest& test) {
  auto c = test.NewClientCall("/foo").Timeout(Duration::Minutes(1)).Create();
  IncomingMetadata server_initial_metadata;
  IncomingStatusOnClient server_status;
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

  test.Step();
}

void TenRequests(CoreEnd2endTest& test, int initial_sequence_number) {
  test.InitServer(ChannelArgs());
  test.InitClient(ChannelArgs().Set(GRPC_ARG_HTTP2_INITIAL_SEQUENCE_NUMBER,
                                    initial_sequence_number));
  for (int i = 0; i < 10; i++) {
    SimpleRequest(test);
  }
}

CORE_END2END_TEST(Http2Tests, HighInitialSeqno) {
  TenRequests(*this, 16777213);
}
CORE_END2END_TEST(RetryHttp2Tests, HighInitialSeqno) {
  TenRequests(*this, 2147483645);
}

}
}
