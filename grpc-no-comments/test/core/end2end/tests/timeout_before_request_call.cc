// Copyright 2023 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>
#include <string.h>

#include <memory>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(CoreDeadlineTests, TimeoutBeforeRequestCall) {
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(1)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_DEADLINE_EXCEEDED);
  auto s = RequestCall(2);
  bool got_call = false;
  std::unique_ptr<IncomingCloseOnServer> client_close;
  Expect(2, MaybePerformAction{[this, &s, &got_call, &client_close](bool ok) {
           got_call = true;
           if (ok) {

             client_close = std::make_unique<IncomingCloseOnServer>();
             s.NewBatch(3).RecvCloseOnServer(*client_close);
             Expect(3, true);
           }
         }});
  Step();
  if (client_close != nullptr) {

    EXPECT_TRUE(got_call);
    EXPECT_TRUE(client_close->was_cancelled());
  }
  if (!got_call) {

    ShutdownServerAndNotify(4);
    Expect(2, false);
    Expect(4, true);
    Step();
  }
}

CORE_END2END_TEST(CoreDeadlineTests,
                  TimeoutBeforeRequestCallWithRegisteredMethod) {
  auto method = RegisterServerMethod("/foo", GRPC_SRM_PAYLOAD_NONE);

  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(1)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_DEADLINE_EXCEEDED);
  auto s = RequestRegisteredCall(method, 2);
  bool got_call = false;
  std::unique_ptr<IncomingCloseOnServer> client_close;
  Expect(2, MaybePerformAction{[this, &s, &got_call, &client_close](bool ok) {
           got_call = true;
           if (ok) {

             client_close = std::make_unique<IncomingCloseOnServer>();
             s.NewBatch(3).RecvCloseOnServer(*client_close);
             Expect(3, true);
           }
         }});
  Step();
  if (client_close != nullptr) {

    EXPECT_TRUE(got_call);
    EXPECT_TRUE(client_close->was_cancelled());
  }
  if (!got_call) {

    ShutdownServerAndNotify(4);
    Expect(2, false);
    Expect(4, true);
    Step();
  }
}

CORE_END2END_TEST(CoreDeadlineSingleHopTests,
                  TimeoutBeforeRequestCallWithRegisteredMethodWithPayload) {
  auto method =
      RegisterServerMethod("/foo", GRPC_SRM_PAYLOAD_READ_INITIAL_BYTE_BUFFER);

  const size_t kMessageSize = 10 * 1024 * 1024;
  auto send_from_client = RandomSlice(kMessageSize);
  InitServer(
      ChannelArgs().Set(GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH, kMessageSize));
  InitClient(
      ChannelArgs().Set(GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH, kMessageSize));

  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(1)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendCloseFromClient()
      .SendMessage(send_from_client.Ref())
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_DEADLINE_EXCEEDED);
  IncomingMessage client_message;
  auto s = RequestRegisteredCall(method, &client_message, 2);
  bool got_call = false;
  std::unique_ptr<IncomingCloseOnServer> client_close;
  Expect(2, MaybePerformAction{[this, &s, &got_call, &client_close](bool ok) {
           LOG(INFO) << "\n***\n*** got call: " << ok << "\n***";
           got_call = true;
           if (ok) {

             client_close = std::make_unique<IncomingCloseOnServer>();
             s.NewBatch(3).RecvCloseOnServer(*client_close);
             Expect(3, true);
           }
         }});
  Step();
  if (client_close != nullptr) {

    EXPECT_TRUE(got_call);
    EXPECT_TRUE(client_close->was_cancelled());
  }
  if (!got_call) {

    ShutdownServerAndNotify(4);
    Expect(2, false);
    Expect(4, true);
    Step();
  }
}

}
}
