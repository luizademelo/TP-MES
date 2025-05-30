// Copyright 2023 gRPC authors.

#include "src/core/lib/promise/inter_activity_latch.h"

#include <grpc/grpc.h>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/promise/event_engine_wakeup_scheduler.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/util/notification.h"

using grpc_event_engine::experimental::GetDefaultEventEngine;

namespace grpc_core {
namespace {

TEST(InterActivityLatchTest, Works) {
  InterActivityLatch<void> latch;

  Notification n1;
  auto a1 = MakeActivity(
      [&] {
        return Seq(latch.Wait(), [&](Empty) {
          n1.Notify();
          return absl::OkStatus();
        });
      },
      EventEngineWakeupScheduler{GetDefaultEventEngine()}, [](absl::Status) {});
  Notification n2;
  auto a2 = MakeActivity(
      [&] {
        return Seq(latch.Wait(), [&](Empty) {
          n2.Notify();
          return absl::OkStatus();
        });
      },
      EventEngineWakeupScheduler{GetDefaultEventEngine()}, [](absl::Status) {});
  Notification n3;
  auto a3 = MakeActivity(
      [&] {
        return Seq(latch.Wait(), [&](Empty) {
          n3.Notify();
          return absl::OkStatus();
        });
      },
      EventEngineWakeupScheduler{GetDefaultEventEngine()}, [](absl::Status) {});

  ASSERT_FALSE(n1.HasBeenNotified());
  ASSERT_FALSE(n2.HasBeenNotified());
  ASSERT_FALSE(n3.HasBeenNotified());

  auto kicker = MakeActivity(
      [&] {
        latch.Set();
        return absl::OkStatus();
      },
      EventEngineWakeupScheduler{GetDefaultEventEngine()}, [](absl::Status) {});

  Notification n4;
  auto a4 = MakeActivity(
      [&] {
        return Seq(latch.Wait(), [&](Empty) {
          n4.Notify();
          return absl::OkStatus();
        });
      },
      EventEngineWakeupScheduler{GetDefaultEventEngine()}, [](absl::Status) {});

  n1.WaitForNotification();
  n2.WaitForNotification();
  n3.WaitForNotification();
  n4.WaitForNotification();
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
