// Copyright 2023 gRPC authors.

#include "src/core/lib/promise/promise_mutex.h"

#include <memory>
#include <optional>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/join.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/seq.h"
#include "test/core/promise/test_wakeup_schedulers.h"

namespace grpc_core {
namespace {

TEST(PromiseMutexTest, Basic) {
  PromiseMutex<int> mutex{1};
  bool done = false;
  MakeActivity(
      [&]() {
        return Seq(
            Join(Seq(mutex.Acquire(),
                     [](PromiseMutex<int>::Lock l) {
                       EXPECT_EQ(*l, 1);
                       *l = 2;
                     }),
                 Seq(mutex.Acquire(),
                     [](PromiseMutex<int>::Lock l) {
                       EXPECT_EQ(*l, 2);
                       *l = 3;
                     }),
                 Seq(mutex.Acquire(),
                     [](PromiseMutex<int>::Lock l) { EXPECT_EQ(*l, 3); })),
            []() { return absl::OkStatus(); });
      },
      InlineWakeupScheduler(),
      [&done](absl::Status status) {
        EXPECT_TRUE(status.ok());
        done = true;
      });
  EXPECT_TRUE(done);
  EXPECT_EQ(**NowOrNever(mutex.Acquire()), 3);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
