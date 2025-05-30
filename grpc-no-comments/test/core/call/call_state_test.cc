// Copyright 2024 gRPC authors.

#include "src/core/call/call_state.h"

#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/core/promise/poll_matcher.h"

using testing::Mock;
using testing::StrictMock;

namespace grpc_core {

namespace {

class MockActivity : public Activity, public Wakeable {
 public:
  MOCK_METHOD(void, WakeupRequested, ());

  void ForceImmediateRepoll(WakeupMask ) override { WakeupRequested(); }
  void Orphan() override {}
  Waker MakeOwningWaker() override { return Waker(this, 0); }
  Waker MakeNonOwningWaker() override { return Waker(this, 0); }
  void Wakeup(WakeupMask ) override { WakeupRequested(); }
  void WakeupAsync(WakeupMask ) override { WakeupRequested(); }
  void Drop(WakeupMask ) override {}
  std::string DebugTag() const override { return "MockActivity"; }
  std::string ActivityDebugTag(WakeupMask ) const override {
    return DebugTag();
  }

  void Activate() {
    if (scoped_activity_ == nullptr) {
      scoped_activity_ = std::make_unique<ScopedActivity>(this);
    }
  }

  void Deactivate() { scoped_activity_.reset(); }

 private:
  std::unique_ptr<ScopedActivity> scoped_activity_;
};

#define EXPECT_WAKEUP(activity, statement)                                 \
  EXPECT_CALL((activity), WakeupRequested()).Times(::testing::AtLeast(1)); \
  statement;                                                               \
  Mock::VerifyAndClearExpectations(&(activity));

}

TEST(CallStateTest, NoOp) { CallState state; }

TEST(CallStateTest, StartTwiceCrashes) {
  CallState state;
  state.Start();
  EXPECT_DEATH(state.Start(), "");
}

TEST(CallStateTest, PullServerInitialMetadataBlocksUntilStart) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.PushServerInitialMetadata());
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.Start());
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady());
}

TEST(CallStateTest, PullClientInitialMetadata) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  EXPECT_DEATH(state.FinishPullClientInitialMetadata(), "");
  state.BeginPullClientInitialMetadata();
  state.FinishPullClientInitialMetadata();
}

TEST(CallStateTest, ClientToServerMessagesWaitForInitialMetadata) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsPending());
  state.BeginPushClientToServerMessage();
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsPending());
  state.BeginPullClientInitialMetadata();
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientInitialMetadata());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsReady(Success{}));
}

TEST(CallStateTest, RepeatedClientToServerMessagesWithHalfClose) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.BeginPullClientInitialMetadata();
  state.FinishPullClientInitialMetadata();

  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.BeginPushClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsReady(Success{}));

  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.BeginPushClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsReady(Success{}));

  state.BeginPushClientToServerMessage();
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsReady(Success{}));

  state.BeginPushClientToServerMessage();
  state.ClientToServerHalfClose();
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsReady(Success{}));

  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(false));
}

TEST(CallStateTest, ImmediateClientToServerHalfClose) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.BeginPullClientInitialMetadata();
  state.FinishPullClientInitialMetadata();
  state.ClientToServerHalfClose();
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady(false));
}

TEST(CallStateTest, ServerToClientMessagesWaitForInitialMetadata) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.Start());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.PushServerInitialMetadata());
  state.BeginPushServerToClientMessage();
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity,
                EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(),
                            IsReady(true)));
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullServerInitialMetadata());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady(true));
  EXPECT_WAKEUP(activity, state.FinishPullServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsReady(Success{}));
}

TEST(CallStateTest, RepeatedServerToClientMessages) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.PushServerInitialMetadata();
  state.Start();
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady(true));
  state.FinishPullServerInitialMetadata();

  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.BeginPushServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsReady(Success{}));

  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.BeginPushServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsReady(Success{}));

  state.BeginPushServerToClientMessage();
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsReady(Success{}));

  state.BeginPushServerToClientMessage();
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady(true));
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsReady(Success{}));
}

TEST(CallStateTest, ReceiveTrailersOnly) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  state.PushServerTrailingMetadata(false);
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady(false));
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollServerTrailingMetadataAvailable(), IsReady());
}

TEST(CallStateTest, ReceiveTrailersOnlySkipsInitialMetadataOnUnstartedCalls) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.PushServerTrailingMetadata(false);
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady(false));
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollServerTrailingMetadataAvailable(), IsReady());
}

TEST(CallStateTest, RecallNoCancellation) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  EXPECT_EQ(state.WasCancelledPushed(), false);
  state.PushServerTrailingMetadata(false);
  EXPECT_EQ(state.WasCancelledPushed(), false);
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady(false));
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollServerTrailingMetadataAvailable(), IsReady());
  EXPECT_THAT(state.PollWasCancelled(), IsReady(false));
  EXPECT_EQ(state.WasCancelledPushed(), false);
}

TEST(CallStateTest, RecallCancellation) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  EXPECT_EQ(state.WasCancelledPushed(), false);
  state.PushServerTrailingMetadata(true);
  EXPECT_EQ(state.WasCancelledPushed(), true);
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady(false));
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollServerTrailingMetadataAvailable(), IsReady());
  EXPECT_THAT(state.PollWasCancelled(), IsReady(true));
  EXPECT_EQ(state.WasCancelledPushed(), true);
}

TEST(CallStateTest, ReceiveTrailingMetadataAfterMessageRead) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  state.PushServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady(true));
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.PushServerTrailingMetadata(false));
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady(false));
  EXPECT_THAT(state.PollServerTrailingMetadataAvailable(), IsReady());
}

TEST(CallStateTest, CanWaitForPullClientMessage) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  EXPECT_THAT(state.PollPullClientToServerMessageStarted(), IsPending());
  state.BeginPullClientInitialMetadata();
  EXPECT_THAT(state.PollPullClientToServerMessageStarted(), IsPending());

  EXPECT_WAKEUP(activity, state.FinishPullClientInitialMetadata());
  EXPECT_THAT(state.PollPullClientToServerMessageStarted(), IsPending());
  EXPECT_WAKEUP(activity, state.PollPullClientToServerMessageAvailable());
  EXPECT_THAT(state.PollPullClientToServerMessageStarted(), IsReady(Success{}));
}

TEST(CallStateTest, CanWaitForPullServerMessage) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  EXPECT_THAT(state.PollPullServerToClientMessageStarted(), IsPending());
  state.PushServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerToClientMessageStarted(), IsPending());
  EXPECT_WAKEUP(
      activity,
      EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady()));
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerToClientMessageStarted(), IsPending());
  EXPECT_WAKEUP(activity, state.PollPullServerToClientMessageAvailable());
  EXPECT_THAT(state.PollPullServerToClientMessageStarted(), IsReady(Success{}));
}

TEST(CallStateTest, ClientSendBlockedUntilPullCompletes) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  state.PushServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady());
  state.FinishPullServerInitialMetadata();
  state.BeginPullClientInitialMetadata();
  state.FinishPullClientInitialMetadata();
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.BeginPushClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_THAT(state.PollPullClientToServerMessageAvailable(), IsReady());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullClientToServerMessage());
  EXPECT_THAT(state.PollPushClientToServerMessage(), IsReady(Success{}));
}

TEST(CallStateTest, ServerSendBlockedUntilPullCompletes) {
  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  state.PushServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady());
  state.FinishPullServerInitialMetadata();
  state.BeginPullClientInitialMetadata();
  state.FinishPullClientInitialMetadata();
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsPending());
  EXPECT_WAKEUP(activity, state.BeginPushServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsPending());
  EXPECT_WAKEUP(activity, state.FinishPullServerToClientMessage());
  EXPECT_THAT(state.PollPushServerToClientMessage(), IsReady(Success{}));
}

TEST(CallStateTest, CanSendMessageThenInitialMetadataOnServer) {

  StrictMock<MockActivity> activity;
  activity.Activate();
  CallState state;
  state.Start();
  state.BeginPushServerToClientMessage();
  state.PushServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerInitialMetadataAvailable(), IsReady());
  state.FinishPullServerInitialMetadata();
  EXPECT_THAT(state.PollPullServerToClientMessageAvailable(), IsReady());
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_tracer_init();
  return RUN_ALL_TESTS();
}
