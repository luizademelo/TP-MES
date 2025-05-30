// Copyright 2024 gRPC authors.

#include "src/core/util/wait_for_single_owner.h"

#include <memory>
#include <thread>

#include "gtest/gtest.h"

TEST(WaitForSingleOwner, Finishes) {
  auto i = std::make_shared<int>(3);
  grpc_core::WaitForSingleOwner(std::move(i));
}

TEST(WaitForSingleOwner, DoesNotFinishWithAHeldInstance) {
  auto i = std::make_shared<int>(3);
  auto timeout = grpc_core::Duration::Seconds(1);
  auto start = grpc_core::Timestamp::Now();
  std::thread t{[i, &timeout]() {

    absl::SleepFor(absl::Milliseconds(timeout.millis()));
  }};
  grpc_core::WaitForSingleOwner(std::move(i));
  auto duration = grpc_core::Timestamp::Now() - start;
  ASSERT_GE(duration, timeout);
  t.join();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
