
// Copyright 2023 The gRPC Authors

#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"

#include <grpc/support/port_platform.h>

#include "absl/synchronization/notification.h"
#include "gtest/gtest.h"
#include "src/core/util/time.h"

using ::grpc_event_engine::experimental::FuzzingEventEngine;

TEST(FuzzingEventEngine, RunAfterAndTickForDuration) {
  auto fuzzing_ee = std::make_shared<FuzzingEventEngine>(
      FuzzingEventEngine::Options(), fuzzing_event_engine::Actions());
  absl::Notification notification1;
  absl::Notification notification2;
  fuzzing_ee->RunAfter(grpc_core::Duration::Milliseconds(250), [&]() {
    notification1.Notify();
    fuzzing_ee->RunAfter(grpc_core::Duration::Milliseconds(250),
                         [&]() { notification2.Notify(); });
  });
  EXPECT_FALSE(notification1.HasBeenNotified());
  fuzzing_ee->TickForDuration(grpc_core::Duration::Milliseconds(250));
  EXPECT_TRUE(notification1.HasBeenNotified());
  EXPECT_FALSE(notification2.HasBeenNotified());
  fuzzing_ee->TickForDuration(grpc_core::Duration::Milliseconds(250));
  EXPECT_TRUE(notification2.HasBeenNotified());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
