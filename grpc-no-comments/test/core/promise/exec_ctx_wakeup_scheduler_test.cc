// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/exec_ctx_wakeup_scheduler.h"

#include <stdlib.h>

#include <memory>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

TEST(ExecCtxWakeupSchedulerTest, Works) {
  int state = 0;
  bool done = false;
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
      ExecCtxWakeupScheduler(),
      [&done](absl::Status status) {
        EXPECT_EQ(status, absl::OkStatus());
        done = true;
      });

  EXPECT_EQ(state, 1);
  EXPECT_FALSE(done);
  {
    ExecCtx exec_ctx;
    EXPECT_FALSE(exec_ctx.HasWork());
    activity->ForceWakeup();
    EXPECT_TRUE(exec_ctx.HasWork());
    EXPECT_EQ(state, 1);
    EXPECT_FALSE(done);
  }
  EXPECT_EQ(state, 2);
  EXPECT_TRUE(done);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
