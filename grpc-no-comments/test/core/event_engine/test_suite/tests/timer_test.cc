// Copyright 2021 gRPC authors.

#include <grpc/event_engine/event_engine.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <random>
#include <thread>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "absl/functional/bind_front.h"
#include "absl/functional/function_ref.h"
#include "absl/log/log.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/time_util.h"
#include "src/core/util/sync.h"
#include "test/core/event_engine/test_suite/event_engine_test_framework.h"

using ::testing::ElementsAre;
using namespace std::chrono_literals;

namespace grpc_event_engine {
namespace experimental {

void InitTimerTests() {}

}
}

class EventEngineTimerTest : public EventEngineTest {
 public:
  void ScheduleCheckCB(std::chrono::steady_clock::time_point when,
                       std::atomic<int>* call_count,
                       std::atomic<int>* fail_count, int total_expected);

 protected:
  void WaitForSignalled(absl::Duration timeout)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    absl::Time deadline = absl::Now() + timeout;
    while (!signaled_) {
      timeout = deadline - absl::Now();
      ASSERT_GT(timeout, absl::ZeroDuration());
      cv_.WaitWithTimeout(&mu_, timeout);
    }
  }

  grpc_core::Mutex mu_;
  grpc_core::CondVar cv_;
  bool signaled_ ABSL_GUARDED_BY(mu_) = false;
};

TEST_F(EventEngineTimerTest, ImmediateCallbackIsExecutedQuickly) {
  auto engine = this->NewEventEngine();
  grpc_core::MutexLock lock(&mu_);
  engine->RunAfter(0ms, [this]() {
    grpc_core::MutexLock lock(&mu_);
    signaled_ = true;
    cv_.Signal();
  });
  WaitForSignalled(absl::Seconds(5));
}

TEST_F(EventEngineTimerTest, SupportsCancellation) {
  auto engine = this->NewEventEngine();
  auto handle = engine->RunAfter(24h, []() {});
  ASSERT_TRUE(engine->Cancel(handle));
}

TEST_F(EventEngineTimerTest, CancelledCallbackIsNotExecuted) {
  {
    auto engine = this->NewEventEngine();
    auto handle = engine->RunAfter(24h, [this]() {
      grpc_core::MutexLock lock(&mu_);
      signaled_ = true;
    });
    ASSERT_TRUE(engine->Cancel(handle));
  }

  grpc_core::MutexLock lock(&mu_);
  ASSERT_FALSE(signaled_);
}

TEST_F(EventEngineTimerTest, TimersRespectScheduleOrdering) {
  // Note: this is a brittle test if the first call to `RunAfter` takes longer

  std::vector<uint8_t> ordered;
  uint8_t count = 0;
  grpc_core::MutexLock lock(&mu_);
  {
    auto engine = this->NewEventEngine();
    engine->RunAfter(3000ms, [&]() {
      grpc_core::MutexLock lock(&mu_);
      ordered.push_back(2);
      ++count;
      cv_.Signal();
    });
    engine->RunAfter(0ms, [&]() {
      grpc_core::MutexLock lock(&mu_);
      ordered.push_back(1);
      ++count;
      cv_.Signal();
    });

    while (count != 2) {
      cv_.WaitWithTimeout(&mu_, absl::Milliseconds(8));
    }
  }

  ASSERT_THAT(ordered, ElementsAre(1, 2));
}

TEST_F(EventEngineTimerTest, CancellingExecutedCallbackIsNoopAndReturnsFalse) {
  auto engine = this->NewEventEngine();
  grpc_core::MutexLock lock(&mu_);
  auto handle = engine->RunAfter(0ms, [this]() {
    grpc_core::MutexLock lock(&mu_);
    signaled_ = true;
    cv_.Signal();
  });
  WaitForSignalled(absl::Seconds(10));

  ASSERT_FALSE(engine->Cancel(handle));
}

void EventEngineTimerTest::ScheduleCheckCB(
    std::chrono::steady_clock::time_point when, std::atomic<int>* call_count,
    std::atomic<int>* fail_count, int total_expected) {
  auto now = std::chrono::steady_clock::now();
  EXPECT_LE(when, now) << "Callback was run "
                       << grpc_event_engine::experimental::Milliseconds(when -
                                                                        now)
                       << " ms too early: ";
  if (when > now) ++(*fail_count);
  if (++(*call_count) == total_expected) {
    grpc_core::MutexLock lock(&mu_);
    signaled_ = true;
    cv_.Signal();
  }
}

TEST_F(EventEngineTimerTest, StressTestTimersNotCalledBeforeScheduled) {
  auto engine = this->NewEventEngine();
  constexpr int thread_count = 10;
  constexpr int call_count_per_thread = 100;
  constexpr float timeout_min_seconds = 1;
  constexpr float timeout_max_seconds = 10;
  std::atomic<int> call_count{0};
  std::atomic<int> failed_call_count{0};
  std::vector<std::thread> threads;
  threads.reserve(thread_count);
  for (int thread_n = 0; thread_n < thread_count; ++thread_n) {
    threads.emplace_back([&]() {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> dis(timeout_min_seconds,
                                           timeout_max_seconds);
      for (int call_n = 0; call_n < call_count_per_thread; ++call_n) {
        const auto dur = static_cast<int64_t>(1e9 * dis(gen));
        auto deadline =
            std::chrono::steady_clock::now() + std::chrono::nanoseconds(dur);
        engine->RunAfter(
            std::chrono::nanoseconds(dur),
            absl::bind_front(&EventEngineTimerTest::ScheduleCheckCB, this,
                             deadline, &call_count, &failed_call_count,
                             thread_count * call_count_per_thread));
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  grpc_core::MutexLock lock(&mu_);

  while (!signaled_) {
    cv_.Wait(&mu_);
  }
  if (failed_call_count.load() != 0) {
    VLOG(2) << "failed timer count: " << failed_call_count.load() << " of "
            << (thread_count * call_count);
  }
  ASSERT_EQ(0, failed_call_count.load());
}

void ImmediateRunTestInternal(
    absl::FunctionRef<void(absl::AnyInvocable<void()>)> run_fn,
    grpc_core::Mutex& mu, grpc_core::CondVar& cv) {
  constexpr int num_concurrent_runs = 32;
  constexpr int num_iterations = 100;
  constexpr absl::Duration run_timeout = absl::Seconds(60);
  std::atomic<int> waiters{0};
  std::atomic<int> execution_count{0};
  auto cb = [&mu, &cv, &run_timeout, &waiters, &execution_count]() {
    waiters.fetch_add(1);
    grpc_core::MutexLock lock(&mu);
    EXPECT_FALSE(cv.WaitWithTimeout(&mu, run_timeout))
        << "callback timed out waiting.";
    execution_count.fetch_add(1);
  };
  for (int i = 0; i < num_iterations; i++) {
    waiters.store(0);
    execution_count.store(0);
    for (int run = 0; run < num_concurrent_runs; run++) {
      run_fn(cb);
    }
    while (waiters.load() != num_concurrent_runs) {
      absl::SleepFor(absl::Milliseconds(33));
    }
    cv.SignalAll();
    while (execution_count.load() != num_concurrent_runs) {
      absl::SleepFor(absl::Milliseconds(33));
    }
  }
}

TEST_F(EventEngineTimerTest,
       DISABLED_RunDoesNotImmediatelyExecuteInTheSameThread) {
  auto engine = this->NewEventEngine();
  ImmediateRunTestInternal(
      [&engine](absl::AnyInvocable<void()> cb) { engine->Run(std::move(cb)); },
      mu_, cv_);
}

TEST_F(EventEngineTimerTest,
       DISABLED_RunAfterDoesNotImmediatelyExecuteInTheSameThread) {
  auto engine = this->NewEventEngine();
  ImmediateRunTestInternal(
      [&engine](absl::AnyInvocable<void()> cb) {
        engine->RunAfter(std::chrono::seconds(0), std::move(cb));
      },
      mu_, cv_);
}
