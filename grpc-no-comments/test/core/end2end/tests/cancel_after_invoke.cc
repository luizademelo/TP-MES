
// Copyright 2015 gRPC authors.

#include <grpc/status.h>

#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/end2end/tests/cancel_test_helpers.h"

namespace grpc_core {
namespace {
const Duration kCancelTimeout = Duration::Seconds(20);
const Duration kDeadlineTimeout = Duration::Seconds(2);
}

void CancelAfterInvoke6(CoreEnd2endTest& test,
                        std::unique_ptr<CancellationMode> mode,
                        Duration timeout) {
  test.InitClient(ChannelArgs());

  test.InitServer(ChannelArgs().Set(GRPC_ARG_PING_TIMEOUT_MS, 5000));
  auto c = test.NewClientCall("/service/method").Timeout(timeout).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .RecvInitialMetadata(server_initial_metadata)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024))
      .SendCloseFromClient()
      .RecvMessage(server_message);
  mode->Apply(c);
  test.Expect(1, true);
  test.Step();
  EXPECT_THAT(server_status.status(),
              ::testing::AnyOf(mode->ExpectedStatus(), GRPC_STATUS_INTERNAL));
}

void CancelAfterInvoke5(CoreEnd2endTest& test,
                        std::unique_ptr<CancellationMode> mode,
                        Duration timeout) {
  test.InitClient(ChannelArgs());

  test.InitServer(ChannelArgs().Set(GRPC_ARG_PING_TIMEOUT_MS, 5000));
  auto c = test.NewClientCall("/service/method").Timeout(timeout).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .RecvInitialMetadata(server_initial_metadata)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024))
      .SendCloseFromClient();
  mode->Apply(c);
  test.Expect(1, true);
  test.Step();
  EXPECT_THAT(server_status.status(),
              ::testing::AnyOf(mode->ExpectedStatus(), GRPC_STATUS_INTERNAL));
}

void CancelAfterInvoke4(CoreEnd2endTest& test,
                        std::unique_ptr<CancellationMode> mode,
                        Duration timeout) {
  test.InitClient(ChannelArgs());

  test.InitServer(ChannelArgs().Set(GRPC_ARG_PING_TIMEOUT_MS, 5000));
  auto c = test.NewClientCall("/service/method").Timeout(timeout).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .RecvInitialMetadata(server_initial_metadata)
      .SendInitialMetadata({})
      .SendMessage(RandomSlice(1024));
  mode->Apply(c);
  test.Expect(1, true);
  test.Step();
  EXPECT_THAT(server_status.status(),
              ::testing::AnyOf(mode->ExpectedStatus(), GRPC_STATUS_INTERNAL));
}

void CancelAfterInvoke3(CoreEnd2endTest& test,
                        std::unique_ptr<CancellationMode> mode,
                        Duration timeout) {
  test.InitClient(ChannelArgs());

  test.InitServer(ChannelArgs().Set(GRPC_ARG_PING_TIMEOUT_MS, 5000));
  auto c = test.NewClientCall("/service/method").Timeout(timeout).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .RecvStatusOnClient(server_status)
      .RecvInitialMetadata(server_initial_metadata)
      .SendInitialMetadata({});
  mode->Apply(c);
  test.Expect(1, true);
  test.Step();
  EXPECT_THAT(server_status.status(),
              ::testing::AnyOf(mode->ExpectedStatus(), GRPC_STATUS_INTERNAL));
}

CORE_END2END_TEST(CoreEnd2endTests, CancelAfterInvoke6) {
  CancelAfterInvoke6(*this, std::make_unique<CancelCancellationMode>(),
                     kCancelTimeout);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelAfterInvoke5) {
  CancelAfterInvoke5(*this, std::make_unique<CancelCancellationMode>(),
                     kCancelTimeout);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelAfterInvoke4) {
  CancelAfterInvoke4(*this, std::make_unique<CancelCancellationMode>(),
                     kCancelTimeout);
}

CORE_END2END_TEST(CoreEnd2endTests, CancelAfterInvoke3) {
  CancelAfterInvoke3(*this, std::make_unique<CancelCancellationMode>(),
                     kCancelTimeout);
}

CORE_END2END_TEST(CoreDeadlineTests, DeadlineAfterInvoke6) {
  CancelAfterInvoke6(*this, std::make_unique<DeadlineCancellationMode>(),
                     kDeadlineTimeout);
}

CORE_END2END_TEST(CoreDeadlineTests, DeadlineAfterInvoke5) {
  CancelAfterInvoke5(*this, std::make_unique<DeadlineCancellationMode>(),
                     kDeadlineTimeout);
}

CORE_END2END_TEST(CoreDeadlineTests, DeadlineAfterInvoke4) {
  CancelAfterInvoke4(*this, std::make_unique<DeadlineCancellationMode>(),
                     kDeadlineTimeout);
}

CORE_END2END_TEST(CoreDeadlineTests, DeadlineAfterInvoke3) {
  CancelAfterInvoke3(*this, std::make_unique<DeadlineCancellationMode>(),
                     kDeadlineTimeout);
}

}
