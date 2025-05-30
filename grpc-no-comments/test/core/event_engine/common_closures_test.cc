// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/common_closures.h"

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "gtest/gtest.h"
#include "src/core/util/notification.h"

using ::grpc_event_engine::experimental::AnyInvocableClosure;
using ::grpc_event_engine::experimental::SelfDeletingClosure;

class AnyInvocableClosureTest : public testing::Test {};

TEST_F(AnyInvocableClosureTest, CallsItsFunction) {
  grpc_core::Notification signal;
  AnyInvocableClosure closure([&signal] { signal.Notify(); });
  closure.Run();
  signal.WaitForNotification();
}

class SelfDeletingClosureTest : public testing::Test {};

TEST_F(SelfDeletingClosureTest, CallsItsFunction) {
  grpc_core::Notification signal;
  auto* closure = SelfDeletingClosure::Create([&signal] { signal.Notify(); });
  closure->Run();
  signal.WaitForNotification();

}

TEST_F(SelfDeletingClosureTest, CallsItsFunctionAndIsDestroyed) {
  grpc_core::Notification fn_called;
  grpc_core::Notification destroyed;
  auto* closure =
      SelfDeletingClosure::Create([&fn_called] { fn_called.Notify(); },
                                  [&destroyed] { destroyed.Notify(); });
  closure->Run();
  fn_called.WaitForNotification();
  destroyed.WaitForNotification();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
