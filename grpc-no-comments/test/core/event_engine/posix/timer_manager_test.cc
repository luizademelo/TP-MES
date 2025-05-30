// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/timer_manager.h"

#include <grpc/grpc.h>

#include <atomic>
#include <memory>
#include <random>

#include "absl/functional/any_invocable.h"
#include "absl/log/log.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/posix_engine/timer.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "test/core/test_util/test_config.h"

namespace grpc_event_engine {
namespace experimental {

TEST(TimerManagerTest, StressTest) {
  grpc_core::ExecCtx exec_ctx;
  auto now = grpc_core::Timestamp::Now();
  auto test_deadline = now + grpc_core::Duration::Seconds(15);
  std::vector<Timer> timers;
  constexpr int kTimerCount = 500;
  timers.resize(kTimerCount);
  std::atomic_int called{0};
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis_millis(100, 3000);
  auto pool = MakeThreadPool(8);
  {
    TimerManager manager(pool);
    for (auto& timer : timers) {
      exec_ctx.InvalidateNow();
      manager.TimerInit(
          &timer, now + grpc_core::Duration::Milliseconds(dis_millis(gen)),
          experimental::SelfDeletingClosure::Create([&called]() {
            absl::SleepFor(absl::Milliseconds(50));
            ++called;
          }));
    }

    while (called.load(std::memory_order_relaxed) < kTimerCount) {
      exec_ctx.InvalidateNow();
      if (grpc_core::Timestamp::Now() > test_deadline) {
        FAIL() << "Deadline exceeded. "
               << called.load(std::memory_order_relaxed) << "/" << kTimerCount
               << " callbacks executed";
      }
      VLOG(2) << "Processed " << called.load(std::memory_order_relaxed) << "/"
              << kTimerCount << " callbacks";
      absl::SleepFor(absl::Milliseconds(333));
    }
  }
  pool->Quiesce();
}

TEST(TimerManagerTest, ShutDownBeforeAllCallbacksAreExecuted) {

  grpc_core::ExecCtx exec_ctx;
  std::vector<Timer> timers;
  constexpr int kTimerCount = 100;
  timers.resize(kTimerCount);
  std::atomic_int called{0};
  experimental::AnyInvocableClosure closure([&called] { ++called; });
  auto pool = MakeThreadPool(8);
  {
    TimerManager manager(pool);
    for (auto& timer : timers) {
      manager.TimerInit(&timer, grpc_core::Timestamp::InfFuture(), &closure);
    }
  }
  ASSERT_EQ(called.load(), 0);
  pool->Quiesce();
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
