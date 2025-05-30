// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/wait_for_callback.h"

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/map.h"
#include "src/core/util/notification.h"
#include "test/core/promise/test_wakeup_schedulers.h"

namespace grpc_core {

TEST(WaitForCallbackTest, Works) {
  WaitForCallback w4cb;
  auto callback = w4cb.MakeCallback();
  Notification done;
  auto activity = MakeActivity(
      [&w4cb]() {
        return Map(w4cb.MakeWaitPromise(),
                   [](Empty) { return absl::OkStatus(); });
      },
      InlineWakeupScheduler{},
      [&done](const absl::Status& s) {
        EXPECT_TRUE(s.ok());
        done.Notify();
      });
  EXPECT_FALSE(done.HasBeenNotified());
  callback();
  done.WaitForNotification();
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
