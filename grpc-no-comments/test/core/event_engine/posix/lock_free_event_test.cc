// Copyright 2022 The gRPC Authors

#include <benchmark/benchmark.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>

#include <algorithm>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/lockfree_event.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/util/sync.h"

using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::Scheduler;

namespace {
class TestScheduler : public Scheduler {
 public:
  explicit TestScheduler(std::shared_ptr<EventEngine> engine)
      : engine_(std::move(engine)) {}
  void Run(
      grpc_event_engine::experimental::EventEngine::Closure* closure) override {
    engine_->Run(closure);
  }

  void Run(absl::AnyInvocable<void()> cb) override {
    engine_->Run(std::move(cb));
  }

 private:
  std::shared_ptr<EventEngine> engine_;
};

TestScheduler* g_scheduler;

}

namespace grpc_event_engine {
namespace experimental {

TEST(LockFreeEventTest, BasicTest) {
  LockfreeEvent event(g_scheduler);
  grpc_core::Mutex mu;
  grpc_core::CondVar cv;
  event.InitEvent();
  grpc_core::MutexLock lock(&mu);

  event.NotifyOn(
      PosixEngineClosure::TestOnlyToClosure([&mu, &cv](absl::Status status) {
        grpc_core::MutexLock lock(&mu);
        EXPECT_TRUE(status.ok());
        cv.Signal();
      }));
  event.SetReady();
  EXPECT_FALSE(cv.WaitWithTimeout(&mu, absl::Seconds(10)));

  event.SetReady();
  event.NotifyOn(
      PosixEngineClosure::TestOnlyToClosure([&mu, &cv](absl::Status status) {
        grpc_core::MutexLock lock(&mu);
        EXPECT_TRUE(status.ok());
        cv.Signal();
      }));
  EXPECT_FALSE(cv.WaitWithTimeout(&mu, absl::Seconds(10)));

  event.NotifyOn(
      PosixEngineClosure::TestOnlyToClosure([&mu, &cv](absl::Status status) {
        grpc_core::MutexLock lock(&mu);
        EXPECT_FALSE(status.ok());
        EXPECT_EQ(status, absl::CancelledError("Shutdown"));
        cv.Signal();
      }));
  event.SetShutdown(absl::CancelledError("Shutdown"));
  EXPECT_FALSE(cv.WaitWithTimeout(&mu, absl::Seconds(10)));
  event.DestroyEvent();
}

TEST(LockFreeEventTest, MultiThreadedTest) {
  std::vector<std::thread> threads;
  LockfreeEvent event(g_scheduler);
  grpc_core::Mutex mu;
  grpc_core::CondVar cv;
  bool signalled = false;
  int active = 0;
  static constexpr int kNumOperations = 100;
  threads.reserve(2);
  event.InitEvent();

  for (int i = 0; i < 2; i++) {
    threads.emplace_back([&, thread_id = i]() {
      for (int j = 0; j < kNumOperations; j++) {
        grpc_core::MutexLock lock(&mu);

        while (signalled) {
          cv.Wait(&mu);
        }
        active++;
        if (thread_id == 0) {
          event.NotifyOn(PosixEngineClosure::TestOnlyToClosure(
              [&mu, &cv, &signalled](absl::Status status) {
                grpc_core::MutexLock lock(&mu);
                EXPECT_TRUE(status.ok());
                signalled = true;
                cv.SignalAll();
              }));
        } else {
          event.SetReady();
        }
        while (!signalled) {
          cv.Wait(&mu);
        }

        if (--active == 0) {
          signalled = false;
          cv.Signal();
        }
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
  event.SetShutdown(absl::OkStatus());
  event.DestroyEvent();
}

namespace {

class BenchmarkCallbackScheduler : public Scheduler {
 public:
  BenchmarkCallbackScheduler() = default;
  void Run(
      grpc_event_engine::experimental::EventEngine::Closure* closure) override {
    closure->Run();
  }

  void Run(absl::AnyInvocable<void()> cb) override { cb(); }
};

void BM_LockFreeEvent(benchmark::State& state) {
  BenchmarkCallbackScheduler cb_scheduler;
  LockfreeEvent event(&cb_scheduler);
  event.InitEvent();
  PosixEngineClosure* notify_on_closure =
      PosixEngineClosure::ToPermanentClosure([](absl::Status ) {});
  for (auto s : state) {
    event.NotifyOn(notify_on_closure);
    event.SetReady();
  }
  event.SetShutdown(absl::CancelledError("Shutting down"));
  delete notify_on_closure;
  event.DestroyEvent();
}
BENCHMARK(BM_LockFreeEvent)->ThreadRange(1, 64);

}

}
}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  grpc_init();
  g_scheduler = new TestScheduler(
      grpc_event_engine::experimental::GetDefaultEventEngine());
  int r = RUN_ALL_TESTS();
  benchmark::RunTheBenchmarksNamespaced();
  grpc_shutdown();
  return r;
}
