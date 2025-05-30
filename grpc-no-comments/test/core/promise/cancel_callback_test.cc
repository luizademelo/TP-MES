// Copyright 2022 gRPC authors.

#include "src/core/lib/promise/cancel_callback.h"

#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

TEST(CancelCallback, DoesntCallCancelIfCompleted) {
  auto x = OnCancel([]() { return 42; },
                    []() { FAIL() << "Should never reach here"; });
  EXPECT_EQ(x(), Poll<int>(42));
}

TEST(CancelCallback, CallsCancelIfNotCompleted) {
  bool called = false;
  {
    auto x = OnCancel([]() { return 42; }, [&called]() { called = true; });
    EXPECT_EQ(called, false);
  }
  EXPECT_EQ(called, true);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
