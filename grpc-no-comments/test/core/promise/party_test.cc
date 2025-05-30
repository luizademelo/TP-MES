// Copyright 2023 gRPC authors.

#include "src/core/lib/promise/party.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/grpc.h>
#include <stdio.h>

#include <algorithm>
#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/inter_activity_latch.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {

constexpr int kNumThreads = 8;
constexpr int kNumSpawns = 100;
constexpr int kLargeNumSpawns = 10000;
constexpr int kStressTestSleepMs = 10;

class PartyTest : public ::testing::Test {
 protected:
  RefCountedPtr<Party> MakeParty() {
    auto arena = SimpleArenaAllocator()->MakeArena();
    arena->SetContext<grpc_event_engine::experimental::EventEngine>(
        event_engine_.get());
    return Party::Make(std::move(arena));
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_ =
      grpc_event_engine::experimental::GetDefaultEventEngine();
};

TEST_F(PartyTest, Noop) {

  auto party = MakeParty();
}

TEST_F(PartyTest, SpawnAndRunOneParty) {

  std::string execution_order;
  auto party = MakeParty();
  Notification n;
  party->Spawn(
      "TestSpawn",
      [i = 5, &execution_order]() mutable -> Poll<int> {
        EXPECT_GT(i, 0);
        GetContext<Activity>()->ForceImmediateRepoll();
        --i;
        if (i == 0) {
          absl::StrAppend(&execution_order, "1");
          return 42;
        }
        absl::StrAppend(&execution_order, "P");
        return Pending{};
      },
      [&n, &execution_order](int x) {
        EXPECT_EQ(x, 42);
        absl::StrAppend(&execution_order, "2");
        n.Notify();
      });
  n.WaitForNotification();
  absl::StrAppend(&execution_order, "3");
  EXPECT_STREQ(execution_order.c_str(), "PPPP123");
  VLOG(2) << "Execution order : " << execution_order;
}

TEST_F(PartyTest, SpawnAndFail) {

  std::string execution_order;
  auto party = MakeParty();
  Notification n;
  party->Spawn(
      "TestSpawn",
      [&execution_order]() mutable -> absl::StatusOr<int> {
        absl::StrAppend(&execution_order, "1");
        return absl::CancelledError();
      },
      [&n, &execution_order](absl::StatusOr<int> x) {
        absl::StrAppend(&execution_order, "2");
        n.Notify();
      });
  n.WaitForNotification();
  absl::StrAppend(&execution_order, "3");
  EXPECT_STREQ(execution_order.c_str(), "123");
  VLOG(2) << "Execution order : " << execution_order;
}

auto MakePromise(std::string& execution_order, int num) {
  return [i = num, &execution_order]() mutable -> Poll<int> {
    absl::StrAppend(&execution_order, "L");
    absl::StrAppend(&execution_order, i);
    return i;
  };
}

auto MakeOnDone(std::string& execution_order) {
  return [&execution_order](int num) mutable -> Poll<int> {
    absl::StrAppend(&execution_order, "D");
    absl::StrAppend(&execution_order, num);
    return num;
  };
}

TEST_F(PartyTest, TestLargeNumberOfSpawnedPromises) {

  const int kNumPromises = 256;
  std::string execution_order;
  auto party = MakeParty();
  for (int i = 1; i <= kNumPromises; ++i) {
    absl::StrAppend(&execution_order, ".");
    party->Spawn(absl::StrCat("p", i), MakePromise(execution_order, i),
                 MakeOnDone(execution_order));
  }
  for (int i = 1; i <= kNumPromises; ++i) {
    std::string current = absl::StrFormat(".L%dD%d", i, i);
    EXPECT_TRUE(absl::StrContains(execution_order, current));
  }
  VLOG(2) << "Execution order : " << execution_order;
}

auto MakePendingPromise(std::string& execution_order, int num) {
  return [i = num, &execution_order]() mutable -> Poll<int> {
    absl::StrAppend(&execution_order, "P");
    absl::StrAppend(&execution_order, i);
    return Pending{};
  };
}

TEST_F(PartyTest, Test16SpawnedPendingPromises) {

  const int kNumPromises = 16;
  std::string execution_order;
  auto party = MakeParty();
  for (int i = 1; i <= kNumPromises; ++i) {
    party->Spawn(absl::StrCat("p", i), MakePendingPromise(execution_order, i),
                 MakeOnDone(execution_order));
  }
  for (int i = 1; i <= kNumPromises; ++i) {
    std::string current = absl::StrFormat("P%d", i);
    EXPECT_TRUE(absl::StrContains(execution_order, current));
  }

  EXPECT_FALSE(absl::StrContains(execution_order, 'D'));
  VLOG(2) << "Execution order : " << execution_order;
}

TEST_F(PartyTest, SpawnWaitableAndRunTwoParties) {

  std::string execution_order;
  auto party1 = MakeParty();
  auto party2 = MakeParty();
  Notification test_done;
  InterActivityLatch<void> inter_activity_latch;

  party1->Spawn(
      "party1_main",
      [&party2, &inter_activity_latch]() {
        return party2->SpawnWaitable("party2_main", [&inter_activity_latch]() {
          return inter_activity_latch.Wait();
        });
      },
      [&test_done, &execution_order](Empty) {
        absl::StrAppend(&execution_order, "2");
        test_done.Notify();
      });
  ASSERT_FALSE(test_done.HasBeenNotified());
  party1->Spawn(
      "party1_notify_latch",
      [&inter_activity_latch, &execution_order]() {
        absl::StrAppend(&execution_order, "1");
        inter_activity_latch.Set();
      },
      [](Empty) {});
  test_done.WaitForNotification();
  absl::StrAppend(&execution_order, "3");
  EXPECT_STREQ(execution_order.c_str(), "123");
}

TEST_F(PartyTest, CanSpawnFromSpawn) {

  std::string execution_order;
  auto party = MakeParty();
  Notification n1;
  Notification n2;
  party->Spawn(
      "TestSpawn",
      [party, &n2, &execution_order]() -> Poll<int> {
        absl::StrAppend(&execution_order, "1");
        party->Spawn(
            "TestSpawnInner",
            [i = 5, &execution_order]() mutable -> Poll<int> {
              GetContext<Activity>()->ForceImmediateRepoll();
              --i;
              if (i == 0) {
                absl::StrAppend(&execution_order, "4");
                return 42;
              }
              absl::StrAppend(&execution_order, "P");
              return Pending{};
            },
            [&n2, &execution_order](int x) {
              absl::StrAppend(&execution_order, "5");
              EXPECT_EQ(x, 42);
              n2.Notify();
            });
        absl::StrAppend(&execution_order, "2");
        return 1234;
      },
      [&n1, &execution_order](int x) {
        absl::StrAppend(&execution_order, "3");
        EXPECT_EQ(x, 1234);
        n1.Notify();
      });
  n1.WaitForNotification();
  n2.WaitForNotification();
  absl::StrAppend(&execution_order, "6");
  EXPECT_STREQ(execution_order.c_str(), "123PPPP456");
  VLOG(2) << "Execution order : " << execution_order;
}

TEST_F(PartyTest, CanWakeupWithOwningWaker) {

  auto party = MakeParty();
  Notification n[10];
  Notification complete;
  std::string execution_order;
  Waker waker;
  party->Spawn(
      "TestSpawn",
      [num = 0, &waker, &n, &execution_order]() mutable -> Poll<int> {
        absl::StrAppend(&execution_order, "A");
        waker = GetContext<Activity>()->MakeOwningWaker();
        n[num].Notify();
        num++;
        if (num == 10) return num;
        absl::StrAppend(&execution_order, "P");
        return Pending{};
      },
      [&complete, &execution_order](int val) {
        absl::StrAppend(&execution_order, "B");
        EXPECT_EQ(val, 10);
        complete.Notify();
      });
  EXPECT_TRUE(n[0].HasBeenNotified());
  for (int i = 0; i < 10; i++) {
    absl::StrAppend(&execution_order, " ");
    absl::StrAppend(&execution_order, i);
    n[i].WaitForNotification();
    if (i < 9) {
      EXPECT_FALSE(n[i + 1].HasBeenNotified());
    }
    EXPECT_FALSE(waker.is_unwakeable());
    waker.Wakeup();
  }
  EXPECT_TRUE(waker.is_unwakeable());
  complete.WaitForNotification();
  absl::StrAppend(&execution_order, " End");
  EXPECT_TRUE(waker.is_unwakeable());

  EXPECT_STREQ(execution_order.c_str(),
               "AP 0AP 1AP 2AP 3AP 4AP 5AP 6AP 7AP 8AB 9 End");
  VLOG(2) << "Execution order : " << execution_order;
}

TEST_F(PartyTest, CanWakeupWithNonOwningWaker) {

  auto party = MakeParty();
  Notification n[10];
  Notification complete;
  std::string execution_order;
  Waker waker;
  party->Spawn(
      "TestSpawn",
      [i = 10, &waker, &n, &execution_order]() mutable -> Poll<int> {
        absl::StrAppend(&execution_order, "A");
        waker = GetContext<Activity>()->MakeNonOwningWaker();
        --i;
        n[9 - i].Notify();
        if (i == 0) return 42;
        absl::StrAppend(&execution_order, "P");
        return Pending{};
      },
      [&complete, &execution_order](int x) {
        absl::StrAppend(&execution_order, "B");
        EXPECT_EQ(x, 42);
        complete.Notify();
      });
  EXPECT_TRUE(n[0].HasBeenNotified());
  for (int i = 0; i <= 9; i++) {
    absl::StrAppend(&execution_order, " ");
    absl::StrAppend(&execution_order, i);
    n[i].WaitForNotification();
    if (i < 9) EXPECT_FALSE(n[i + 1].HasBeenNotified());
    EXPECT_FALSE(waker.is_unwakeable());
    waker.Wakeup();
  }
  complete.WaitForNotification();
  EXPECT_TRUE(waker.is_unwakeable());
  absl::StrAppend(&execution_order, " End");
  VLOG(2) << "Execution order : " << execution_order;
  EXPECT_STREQ(execution_order.c_str(),
               "AP 0AP 1AP 2AP 3AP 4AP 5AP 6AP 7AP 8AB 9 End");
}

TEST_F(PartyTest, CanWakeupWithNonOwningWakerAfterOrphaning) {
  auto party = MakeParty();
  Notification set_waker;
  Waker waker;
  std::string execution_order;
  party->Spawn(
      "TestSpawn",
      [&waker, &set_waker, &execution_order]() mutable -> Poll<int> {
        absl::StrAppend(&execution_order, "A");
        EXPECT_FALSE(set_waker.HasBeenNotified());
        waker = GetContext<Activity>()->MakeNonOwningWaker();
        set_waker.Notify();
        return Pending{};
      },
      [](int) { Crash("unreachable"); });
  set_waker.WaitForNotification();
  absl::StrAppend(&execution_order, "1");
  party.reset();

  EXPECT_FALSE(waker.is_unwakeable());
  waker.Wakeup();
  EXPECT_TRUE(waker.is_unwakeable());
  EXPECT_STREQ(execution_order.c_str(), "A1");
}

TEST_F(PartyTest, CanDropNonOwningWakeAfterOrphaning) {

  auto party = MakeParty();
  Notification set_waker;
  std::unique_ptr<Waker> waker;
  std::string execution_order;
  party->Spawn(
      "TestSpawn",
      [&waker, &set_waker, &execution_order]() mutable -> Poll<int> {
        absl::StrAppend(&execution_order, "A");
        EXPECT_FALSE(set_waker.HasBeenNotified());
        waker = std::make_unique<Waker>(
            GetContext<Activity>()->MakeNonOwningWaker());
        set_waker.Notify();
        return Pending{};
      },
      [](int) { Crash("unreachable"); });
  set_waker.WaitForNotification();
  absl::StrAppend(&execution_order, "1");
  party.reset();
  EXPECT_NE(waker, nullptr);
  waker.reset();
  EXPECT_STREQ(execution_order.c_str(), "A1");
}

TEST_F(PartyTest, CanWakeupNonOwningOrphanedWakerWithNoEffect) {

  auto party = MakeParty();
  Notification set_waker;
  Waker waker;
  std::string execution_order;
  party->Spawn(
      "TestSpawn",
      [&waker, &set_waker, &execution_order]() mutable -> Poll<int> {
        absl::StrAppend(&execution_order, "A");
        EXPECT_FALSE(set_waker.HasBeenNotified());
        waker = GetContext<Activity>()->MakeNonOwningWaker();
        set_waker.Notify();
        return Pending{};
      },
      [](int) { Crash("unreachable"); });
  set_waker.WaitForNotification();
  absl::StrAppend(&execution_order, "1");
  EXPECT_FALSE(waker.is_unwakeable());
  party.reset();
  absl::StrAppend(&execution_order, "2");

  waker.Wakeup();
  EXPECT_TRUE(waker.is_unwakeable());
  EXPECT_STREQ(execution_order.c_str(), "A12");
}

TEST_F(PartyTest, CanBulkSpawn) {

  auto party = MakeParty();
  Notification n1;
  Notification n2;
  {
    Party::WakeupHold hold(party.get());
    party->Spawn("spawn1", []() {}, [&n1](Empty) { n1.Notify(); });
    party->Spawn("spawn2", []() {}, [&n2](Empty) { n2.Notify(); });
    for (int i = 0; i < 5000; i++) {
      EXPECT_FALSE(n1.HasBeenNotified());
      EXPECT_FALSE(n2.HasBeenNotified());
    }
  }
  n1.WaitForNotification();
  n2.WaitForNotification();
}

TEST_F(PartyTest, CanNestWakeupHold) {

  auto party = MakeParty();
  Notification n1;
  Notification n2;
  std::string execution_order_a;
  std::string execution_order_b;
  {
    Party::WakeupHold hold1(party.get());
    Party::WakeupHold hold2(party.get());
    party->Spawn(
        "spawn1",
        [&execution_order_a]() { absl::StrAppend(&execution_order_a, "A"); },
        [&n1, &execution_order_a](Empty) {
          absl::StrAppend(&execution_order_a, "1");
          n1.Notify();
        });
    party->Spawn(
        "spawn2",
        [&execution_order_b]() { absl::StrAppend(&execution_order_b, "B"); },
        [&n2, &execution_order_b](Empty) {
          absl::StrAppend(&execution_order_b, "2");
          n2.Notify();
        });
    for (int i = 0; i < 5000; i++) {
      EXPECT_FALSE(n1.HasBeenNotified());
      EXPECT_FALSE(n2.HasBeenNotified());
      EXPECT_STREQ(execution_order_a.c_str(), "");
      EXPECT_STREQ(execution_order_b.c_str(), "");
    }
  }
  n1.WaitForNotification();
  n2.WaitForNotification();
  EXPECT_STREQ(execution_order_a.c_str(), "A1");
  EXPECT_STREQ(execution_order_b.c_str(), "B2");
}

void StressTestAsserts(std::vector<Timestamp>& start_times,
                       std::vector<Timestamp>& end_times,
                       int average_sleep_ms) {

  Duration fastest_thread_run_time = end_times[0] - start_times[0];
  Timestamp last_finished_thread = end_times[0];
  for (int i = 1; i < kNumThreads; i++) {
    if ((end_times[i] - start_times[i]) < fastest_thread_run_time) {
      fastest_thread_run_time = end_times[i] - start_times[i];
    }
    if (last_finished_thread < end_times[i]) {
      last_finished_thread = end_times[i];
    }
  }

  LOG(INFO) << "Small thread run time : " << fastest_thread_run_time;

  Duration total_sleep_time =
      Duration::Milliseconds(kNumThreads * kNumSpawns * average_sleep_ms);
  float run_time_by_sleep_time = 3.5;

  EXPECT_LE(last_finished_thread - start_times[0],
            (total_sleep_time / kNumThreads) * run_time_by_sleep_time);

  for (int i = 0; i < kNumThreads; i++) {
    LOG(INFO) << "Thread " << i << " started at " << start_times[i]
              << " and finished at " << end_times[i];

    EXPECT_LE(start_times[i], end_times[1]);

    EXPECT_LE(start_times[i] - start_times[0], (fastest_thread_run_time / 5));

    if (i >= 2) {

      EXPECT_LE((end_times[i - 2] - end_times[i]),
                (fastest_thread_run_time / 5));
    }
  }
}

TEST_F(PartyTest, ThreadStressTest) {

  auto party = MakeParty();
  std::vector<std::string> execution_order(kNumThreads);
  std::vector<Timestamp> start_times(kNumThreads);
  std::vector<Timestamp> end_times(kNumThreads);
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);

  for (int i = 0; i < kNumThreads; i++) {
    Timestamp& start_time = start_times[i];
    Timestamp& end_time = end_times[i];
    std::string& order = execution_order[i];
    absl::StrAppend(&order, absl::StrFormat("Thread %d : ", i));
    threads.emplace_back([&start_time, &end_time, thread_num = i, &order,
                          party]() mutable {
      start_time = Timestamp::Now();
      for (int j = 0; j < kNumSpawns; j++) {
        const int sleep_ms =
            (thread_num % 2 == 1) ? kStressTestSleepMs : 3 * kStressTestSleepMs;
        ExecCtx ctx;
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(Sleep(Timestamp::Now() + Duration::Milliseconds(sleep_ms)),
                [thread_num, &order, spawn_num = j]() mutable -> Poll<int> {
                  absl::StrAppend(&order, absl::StrFormat("%d(P%d,", thread_num,
                                                          spawn_num));
                  return spawn_num + 42;
                }),
            [&order, &promise_complete, spawn_num = j](int val) {
              EXPECT_EQ(val, spawn_num + 42);
              absl::StrAppend(&order, absl::StrFormat("D%d)", spawn_num));
              promise_complete.Notify();
            });
        promise_complete.WaitForNotification();
        absl::StrAppend(&order, ".");
      }
      end_time = Timestamp::Now();
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }

  std::vector<std::string> expected_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {

    absl::StrAppend(&expected_order[i], absl::StrFormat("Thread %d : ", i));
    for (int j = 0; j < kNumSpawns; j++) {
      absl::StrAppend(&expected_order[i],
                      absl::StrFormat("%d(P%d,D%d).", i, j, j));
    }

    EXPECT_STREQ(execution_order[i].c_str(), expected_order[i].c_str());
  }
  StressTestAsserts(start_times, end_times, 2 * kStressTestSleepMs);
}

TEST_F(PartyTest, ThreadStressTestQuickSpawn) {

  auto party = MakeParty();
  std::vector<std::string> execution_order(kNumThreads);
  std::vector<Notification> promises_complete(kNumThreads);
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);

  for (int i = 0; i < kNumThreads; i++) {
    std::string& order = execution_order[i];
    Notification& promise_complete = promises_complete[i];
    EXPECT_FALSE(promise_complete.HasBeenNotified());
    threads.emplace_back([&promise_complete, &party, &order]() mutable {
      for (int j = 0; j < kNumSpawns; j++) {
        party->Spawn(
            "TestSpawn",
            [spawn_num = j, &order]() mutable -> Poll<int> {
              absl::StrAppend(&order, absl::StrFormat("(P%d,", spawn_num));
              return spawn_num + 42;
            },
            [&promise_complete, spawn_num = j, &order](int val) {
              EXPECT_EQ(val, spawn_num + 42);
              absl::StrAppend(&order, absl::StrFormat("D%d)", spawn_num));
              if (order.length() == 880) {

                EXPECT_EQ(order.length(), 880);
                VLOG(2) << "Notification by spawn " << spawn_num;
                promise_complete.Notify();
              }
            });
      }
    });
  }
  for (int i = 0; i < kNumThreads; i++) {
    VLOG(2) << "Waiting for thread " << i;
    promises_complete[i].WaitForNotification();
    VLOG(2) << "Got notification for thread " << i;
  }
  for (auto& thread : threads) {
    thread.join();
  }
  for (int i = 0; i < kNumThreads; i++) {
    for (int j = 0; j < kNumSpawns; j++) {
      std::string current = absl::StrFormat("(P%d,D%d)", j, j);

      EXPECT_TRUE(absl::StrContains(execution_order[i], current));
    }
  }
}

class PromiseNotification {
 public:
  explicit PromiseNotification(bool owning_waker)
      : owning_waker_(owning_waker) {}

  auto Wait() {
    return [this]() -> Poll<int> {
      MutexLock lock(&mu_);
      if (done_) return 42;
      if (!polled_) {
        if (owning_waker_) {
          waker_ = GetContext<Activity>()->MakeOwningWaker();
        } else {
          waker_ = GetContext<Activity>()->MakeNonOwningWaker();
        }
        polled_ = true;
      }
      return Pending{};
    };
  }

  void Notify() {
    Waker waker;
    {
      MutexLock lock(&mu_);
      done_ = true;
      waker = std::move(waker_);
    }
    waker.Wakeup();
  }

  void NotifyUnderLock() {
    MutexLock lock(&mu_);
    done_ = true;
    waker_.WakeupAsync();
  }

 private:
  Mutex mu_;
  const bool owning_waker_;
  bool done_ ABSL_GUARDED_BY(mu_) = false;
  bool polled_ ABSL_GUARDED_BY(mu_) = false;
  Waker waker_ ABSL_GUARDED_BY(mu_);
};

TEST_F(PartyTest, ThreadStressTestWithOwningWaker) {

  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  std::vector<std::string> execution_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    std::string& order = execution_order[i];
    absl::StrAppend(&order, absl::StrFormat("Thread %d : ", i));
    threads.emplace_back([party, &order]() {
      for (int i = 0; i < kNumSpawns; i++) {
        ExecCtx ctx;
        PromiseNotification promise_start(true);
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(promise_start.Wait(),
                         Sleep(Timestamp::Now() +
                               Duration::Milliseconds(kStressTestSleepMs)),
                         [&order, i]() -> Poll<int> {
                           absl::StrAppend(&order, absl::StrFormat("B%d", i));
                           return i + 42;
                         }),
                     [&order, &promise_complete, i](int val) {
                       EXPECT_EQ(val, i + 42);
                       absl::StrAppend(&order, absl::StrFormat("C%d", i));
                       promise_complete.Notify();
                     });
        absl::StrAppend(&order, absl::StrFormat("A%d", i));
        promise_start.Notify();
        promise_complete.WaitForNotification();
        absl::StrAppend(&order, ".");
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  std::vector<std::string> expected_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    absl::StrAppend(&expected_order[i], absl::StrFormat("Thread %d : ", i));
    for (int j = 0; j < kNumSpawns; j++) {
      absl::StrAppend(&expected_order[i],
                      absl::StrFormat("A%dB%dC%d.", j, j, j));
    }

    EXPECT_STREQ(execution_order[i].c_str(), expected_order[i].c_str());
  }
}

TEST_F(PartyTest, ThreadStressTestWithOwningWakerHoldingLock) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  std::vector<std::string> execution_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    std::string& order = execution_order[i];
    absl::StrAppend(&order, absl::StrFormat("Thread %d : ", i));
    threads.emplace_back([party, &order]() {
      for (int i = 0; i < kNumSpawns; i++) {
        ExecCtx ctx;
        PromiseNotification promise_start(true);
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(promise_start.Wait(),
                         Sleep(Timestamp::Now() +
                               Duration::Milliseconds(kStressTestSleepMs)),
                         [&order, i]() -> Poll<int> {
                           absl::StrAppend(&order, absl::StrFormat("B%d", i));
                           return 42;
                         }),
                     [&order, &promise_complete, i](int val) {
                       EXPECT_EQ(val, 42);
                       absl::StrAppend(&order, absl::StrFormat("C%d", i));
                       promise_complete.Notify();
                     });
        absl::StrAppend(&order, absl::StrFormat("A%d", i));
        promise_start.NotifyUnderLock();
        promise_complete.WaitForNotification();
        absl::StrAppend(&order, ".");
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  std::vector<std::string> expected_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    absl::StrAppend(&expected_order[i], absl::StrFormat("Thread %d : ", i));
    for (int j = 0; j < kNumSpawns; j++) {
      absl::StrAppend(&expected_order[i],
                      absl::StrFormat("A%dB%dC%d.", j, j, j));
    }

    EXPECT_STREQ(execution_order[i].c_str(), expected_order[i].c_str());
  }
}

TEST_F(PartyTest, ThreadStressTestWithNonOwningWaker) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  std::vector<std::string> execution_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    std::string& order = execution_order[i];
    absl::StrAppend(&order, absl::StrFormat("Thread %d : ", i));
    threads.emplace_back([party, &order]() {
      for (int i = 0; i < kNumSpawns; i++) {
        ExecCtx ctx;
        PromiseNotification promise_start(false);
        Notification promise_complete;
        party->Spawn("TestSpawn",
                     Seq(promise_start.Wait(),
                         Sleep(Timestamp::Now() +
                               Duration::Milliseconds(kStressTestSleepMs)),
                         [&order, i]() -> Poll<int> {
                           absl::StrAppend(&order, absl::StrFormat("B%d", i));
                           return 42;
                         }),
                     [&order, &promise_complete, i](int val) {
                       EXPECT_EQ(val, 42);
                       absl::StrAppend(&order, absl::StrFormat("C%d", i));
                       promise_complete.Notify();
                     });
        absl::StrAppend(&order, absl::StrFormat("A%d", i));
        promise_start.Notify();
        promise_complete.WaitForNotification();
        absl::StrAppend(&order, ".");
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  std::vector<std::string> expected_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    absl::StrAppend(&expected_order[i], absl::StrFormat("Thread %d : ", i));
    for (int j = 0; j < kNumSpawns; j++) {
      absl::StrAppend(&expected_order[i],
                      absl::StrFormat("A%dB%dC%d.", j, j, j));
    }

    EXPECT_STREQ(execution_order[i].c_str(), expected_order[i].c_str());
  }
}

TEST_F(PartyTest, ThreadStressTestWithOwningWakerNoSleep) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < kLargeNumSpawns; i++) {
        PromiseNotification promise_start(true);
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(promise_start.Wait(), []() -> Poll<int> { return 42; }),
            [&promise_complete](int i) {
              EXPECT_EQ(i, 42);
              promise_complete.Notify();
            });
        promise_start.Notify();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithNonOwningWakerNoSleep) {
  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([party]() {
      for (int i = 0; i < kLargeNumSpawns; i++) {
        PromiseNotification promise_start(false);
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(promise_start.Wait(), []() -> Poll<int> { return 42; }),
            [&promise_complete](int i) {
              EXPECT_EQ(i, 42);
              promise_complete.Notify();
            });
        promise_start.Notify();
        promise_complete.WaitForNotification();
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
}

TEST_F(PartyTest, ThreadStressTestWithInnerSpawn) {

  auto party = MakeParty();
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  std::vector<std::string> execution_order(kNumThreads);
  std::vector<Timestamp> start_times(kNumThreads);
  std::vector<Timestamp> end_times(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    std::string& order = execution_order[i];
    absl::StrAppend(&order, absl::StrFormat("Thread %d : ", i));
    Timestamp& start_time = start_times[i];
    Timestamp& end_time = end_times[i];
    threads.emplace_back([party, &order, &start_time, &end_time]() {
      start_time = Timestamp::Now();
      for (int j = 0; j < kNumSpawns; j++) {
        ExecCtx ctx;
        PromiseNotification inner_start(true);
        PromiseNotification inner_complete(false);
        Notification promise_complete;
        party->Spawn(
            "TestSpawn",
            Seq(
                [party, &inner_start, &inner_complete, &order,
                 j]() -> Poll<int> {
                  absl::StrAppend(&order, absl::StrFormat("A%d", j));
                  party->Spawn(
                      "TestSpawnInner",
                      Seq(inner_start.Wait(),
                          [&order, j]() {
                            absl::StrAppend(&order, absl::StrFormat("D%d", j));
                            return j;
                          }),
                      [&inner_complete, &order, j](int val) {
                        EXPECT_EQ(val, j);
                        absl::StrAppend(&order, absl::StrFormat("E%d", j));
                        inner_complete.Notify();
                      });
                  absl::StrAppend(&order, absl::StrFormat("B%d", j));
                  return 0;
                },
                Sleep(Timestamp::Now() +
                      Duration::Milliseconds(kStressTestSleepMs)),
                [&inner_start, &order, j]() {
                  absl::StrAppend(&order, absl::StrFormat("C%d", j));
                  inner_start.Notify();
                  return 0;
                },
                inner_complete.Wait(),
                [&order, j]() -> Poll<int> {
                  absl::StrAppend(&order, absl::StrFormat("F%d", j));
                  return 42;
                }),
            [&promise_complete, &order, j](int val) {
              EXPECT_EQ(val, 42);
              absl::StrAppend(&order, absl::StrFormat("G%d", j));
              promise_complete.Notify();
            });
        promise_complete.WaitForNotification();
        absl::StrAppend(&order, ".");
      }
      end_time = Timestamp::Now();
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }
  std::vector<std::string> expected_order(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    absl::StrAppend(&expected_order[i], absl::StrFormat("Thread %d : ", i));
    for (int j = 0; j < kNumSpawns; j++) {
      absl::StrAppend(
          &expected_order[i],
          absl::StrFormat("A%dB%dC%dD%dE%dF%dG%d.", j, j, j, j, j, j, j));
    }

    EXPECT_STREQ(execution_order[i].c_str(), expected_order[i].c_str());
  }
  StressTestAsserts(start_times, end_times, kStressTestSleepMs);
}

TEST_F(PartyTest, NestedWakeup) {

  auto party1 = MakeParty();
  auto party2 = MakeParty();
  auto party3 = MakeParty();
  std::string execution_order;
  int whats_going_on = 0;
  Notification done1;
  Notification started2;
  Notification done2;
  Notification started3;
  Notification notify_done;
  party1->Spawn(
      "p1",
      [&]() {
        absl::StrAppend(&execution_order, "1");
        EXPECT_EQ(whats_going_on, 0);
        whats_going_on = 1;
        party2->Spawn(
            "p2",
            [&]() {
              done1.WaitForNotification();
              absl::StrAppend(&execution_order, "5");
              started2.Notify();
              started3.WaitForNotification();
              absl::StrAppend(&execution_order, "7");
              EXPECT_EQ(whats_going_on, 3);
              whats_going_on = 4;
            },
            [&](Empty) {
              absl::StrAppend(&execution_order, "8");
              EXPECT_EQ(whats_going_on, 4);
              whats_going_on = 5;
              done2.Notify();
            });
        absl::StrAppend(&execution_order, "2");
        party3->Spawn(
            "p3",
            [&]() {
              started2.WaitForNotification();
              absl::StrAppend(&execution_order, "6");
              started3.Notify();
              done2.WaitForNotification();
              EXPECT_EQ(whats_going_on, 5);
              whats_going_on = 6;
              absl::StrAppend(&execution_order, "9");
            },
            [&](Empty) {
              EXPECT_EQ(whats_going_on, 6);
              whats_going_on = 7;
              absl::StrAppend(&execution_order, "A");
              notify_done.Notify();
            });
        EXPECT_EQ(whats_going_on, 1);
        whats_going_on = 2;
        absl::StrAppend(&execution_order, "3");
      },
      [&](Empty) {
        EXPECT_EQ(whats_going_on, 2);
        whats_going_on = 3;
        absl::StrAppend(&execution_order, "4");
        done1.Notify();
      });
  notify_done.WaitForNotification();
  absl::StrAppend(&execution_order, "B");
  EXPECT_STREQ(execution_order.c_str(), "123456789AB");
}

TEST_F(PartyTest, SpawnSerializerSerializes) {

  auto party = MakeParty();
  Notification notification;
  int expect_next = 0;
  std::thread thd([party, &notification, &expect_next]() {
    Party::SpawnSerializer* serializer = party->MakeSpawnSerializer();
    for (int i = 0; i < 1000000; i++) {
      serializer->Spawn(
          [i = std::make_unique<int>(i), &expect_next]() -> Poll<Empty> {
            EXPECT_EQ(expect_next, *i);
            ++expect_next;
            return Empty{};
          });
    }
    serializer->Spawn([&notification]() { notification.Notify(); });
  });
  notification.WaitForNotification();
  EXPECT_EQ(expect_next, 1000000);
  thd.join();
}

TEST_F(PartyTest, SimpleJson) {
  auto party = MakeParty();
  Notification notification;
  party->ToJson([&](Json::Object json) {
    LOG(INFO) << "json: " << JsonDump(Json::FromObject(json));
    int refs;
    ASSERT_TRUE(absl::SimpleAtoi(json["ref_count"].string(), &refs));
    EXPECT_GE(refs, 1);
    notification.Notify();
  });
  notification.WaitForNotification();
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
