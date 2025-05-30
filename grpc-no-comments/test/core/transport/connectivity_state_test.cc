
// Copyright 2015 gRPC authors.

#include "src/core/lib/transport/connectivity_state.h"

#include <grpc/grpc.h>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tracer_util.h"

namespace grpc_core {
namespace {

TEST(ConnectivityStateName, Basic) {
  EXPECT_STREQ("IDLE", ConnectivityStateName(GRPC_CHANNEL_IDLE));
  EXPECT_STREQ("CONNECTING", ConnectivityStateName(GRPC_CHANNEL_CONNECTING));
  EXPECT_STREQ("READY", ConnectivityStateName(GRPC_CHANNEL_READY));
  EXPECT_STREQ("TRANSIENT_FAILURE",
               ConnectivityStateName(GRPC_CHANNEL_TRANSIENT_FAILURE));
  EXPECT_STREQ("SHUTDOWN", ConnectivityStateName(GRPC_CHANNEL_SHUTDOWN));
}

class Watcher : public ConnectivityStateWatcherInterface {
 public:
  Watcher(int* count, grpc_connectivity_state* output, absl::Status* status,
          bool* destroyed = nullptr)
      : count_(count),
        output_(output),
        status_(status),
        destroyed_(destroyed) {}

  ~Watcher() override {
    if (destroyed_ != nullptr) *destroyed_ = true;
  }

  void Notify(grpc_connectivity_state new_state,
              const absl::Status& status) override {
    ++*count_;
    *output_ = new_state;
    *status_ = status;
  }

 private:
  int* count_;
  grpc_connectivity_state* output_;
  absl::Status* status_;
  bool* destroyed_;
};

TEST(StateTracker, SetAndGetState) {
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_CONNECTING,
                                   absl::Status());
  EXPECT_EQ(tracker.state(), GRPC_CHANNEL_CONNECTING);
  EXPECT_TRUE(tracker.status().ok());
  tracker.SetState(GRPC_CHANNEL_READY, absl::Status(), "whee");
  EXPECT_EQ(tracker.state(), GRPC_CHANNEL_READY);
  EXPECT_TRUE(tracker.status().ok());
  absl::Status transient_failure_status(absl::StatusCode::kUnavailable,
                                        "status for testing");
  tracker.SetState(GRPC_CHANNEL_TRANSIENT_FAILURE, transient_failure_status,
                   "reason");
  EXPECT_EQ(tracker.state(), GRPC_CHANNEL_TRANSIENT_FAILURE);
  EXPECT_EQ(tracker.status(), transient_failure_status);
}

TEST(StateTracker, NotificationUponAddingWatcher) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_CONNECTING);
  tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                     MakeOrphanable<Watcher>(&count, &state, &status));
  EXPECT_EQ(count, 1);
  EXPECT_EQ(state, GRPC_CHANNEL_CONNECTING);
  EXPECT_TRUE(status.ok());
}

TEST(StateTracker, NotificationUponAddingWatcherWithTransientFailure) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  absl::Status transient_failure_status(absl::StatusCode::kUnavailable,
                                        "status for testing");
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   transient_failure_status);
  tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                     MakeOrphanable<Watcher>(&count, &state, &status));
  EXPECT_EQ(count, 1);
  EXPECT_EQ(state, GRPC_CHANNEL_TRANSIENT_FAILURE);
  EXPECT_EQ(status, transient_failure_status);
}

TEST(StateTracker, NotificationUponStateChange) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_IDLE);
  tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                     MakeOrphanable<Watcher>(&count, &state, &status));
  EXPECT_EQ(count, 0);
  EXPECT_EQ(state, GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(status.ok());
  absl::Status transient_failure_status(absl::StatusCode::kUnavailable,
                                        "status for testing");
  tracker.SetState(GRPC_CHANNEL_TRANSIENT_FAILURE, transient_failure_status,
                   "whee");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(state, GRPC_CHANNEL_TRANSIENT_FAILURE);
  EXPECT_EQ(status, transient_failure_status);
}

TEST(StateTracker, SubscribeThenUnsubscribe) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  bool destroyed = false;
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_IDLE);
  ConnectivityStateWatcherInterface* watcher =
      new Watcher(&count, &state, &status, &destroyed);
  tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                     OrphanablePtr<ConnectivityStateWatcherInterface>(watcher));

  EXPECT_EQ(count, 0);
  EXPECT_EQ(state, GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(status.ok());

  tracker.RemoveWatcher(watcher);
  EXPECT_TRUE(destroyed);
  EXPECT_EQ(count, 0);
  EXPECT_EQ(state, GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(status.ok());
}

TEST(StateTracker, OrphanUponShutdown) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  bool destroyed = false;
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_IDLE);
  ConnectivityStateWatcherInterface* watcher =
      new Watcher(&count, &state, &status, &destroyed);
  tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                     OrphanablePtr<ConnectivityStateWatcherInterface>(watcher));

  EXPECT_EQ(count, 0);
  EXPECT_EQ(state, GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(status.ok());

  tracker.SetState(GRPC_CHANNEL_SHUTDOWN, absl::Status(), "shutting down");
  EXPECT_TRUE(destroyed);
  EXPECT_EQ(count, 1);
  EXPECT_EQ(state, GRPC_CHANNEL_SHUTDOWN);
  EXPECT_TRUE(status.ok());
}

TEST(StateTracker, AddWhenAlreadyShutdown) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  bool destroyed = false;
  ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_SHUTDOWN,
                                   absl::Status());
  ConnectivityStateWatcherInterface* watcher =
      new Watcher(&count, &state, &status, &destroyed);
  tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                     OrphanablePtr<ConnectivityStateWatcherInterface>(watcher));
  EXPECT_TRUE(destroyed);
  EXPECT_EQ(count, 1);
  EXPECT_EQ(state, GRPC_CHANNEL_SHUTDOWN);
  EXPECT_TRUE(status.ok());
}

TEST(StateTracker, NotifyShutdownAtDestruction) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  absl::Status status;
  {
    ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_IDLE);
    tracker.AddWatcher(GRPC_CHANNEL_IDLE,
                       MakeOrphanable<Watcher>(&count, &state, &status));

    EXPECT_EQ(count, 0);
    EXPECT_EQ(state, GRPC_CHANNEL_IDLE);
  }

  EXPECT_EQ(count, 1);
  EXPECT_EQ(state, GRPC_CHANNEL_SHUTDOWN);
}

TEST(StateTracker, DoNotNotifyShutdownAtDestructionIfAlreadyInShutdown) {
  int count = 0;
  grpc_connectivity_state state = GRPC_CHANNEL_SHUTDOWN;
  absl::Status status;
  {
    ConnectivityStateTracker tracker("xxx", GRPC_CHANNEL_SHUTDOWN);
    tracker.AddWatcher(GRPC_CHANNEL_SHUTDOWN,
                       MakeOrphanable<Watcher>(&count, &state, &status));

    EXPECT_EQ(count, 0);
    EXPECT_EQ(state, GRPC_CHANNEL_SHUTDOWN);
  }

  EXPECT_EQ(count, 0);
  EXPECT_EQ(state, GRPC_CHANNEL_SHUTDOWN);
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  grpc_core::testing::grpc_tracer_enable_flag(
      &grpc_core::connectivity_state_trace);
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
