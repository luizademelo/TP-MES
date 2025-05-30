// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/event_engine_wakeup_scheduler.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <stdlib.h>

#include <memory>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/notification.h"

namespace grpc_core {

TEST(EventEngineWakeupSchedulerTest, Works) {
  int state = 0;
  Notification done;
  auto activity = MakeActivity(
      [&state]() mutable -> Poll<absl::Status> {
        ++state;
        switch (state) {
          case 1:
            return Pending();
          case 2:
            return absl::OkStatus();
          default:
            abort();
        }
      },
      EventEngineWakeupScheduler(
          grpc_event_engine::experimental::CreateEventEngine()),
      [&done](absl::Status status) {
        EXPECT_EQ(status, absl::OkStatus());
        done.Notify();
      });

  EXPECT_EQ(state, 1);
  EXPECT_FALSE(done.HasBeenNotified());
  activity->ForceWakeup();
  done.WaitForNotification();
  EXPECT_EQ(state, 2);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  auto r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
