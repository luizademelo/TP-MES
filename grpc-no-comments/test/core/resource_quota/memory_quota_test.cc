// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/memory_quota.h"

#include <grpc/slice.h>
#include <grpc/support/log.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <random>
#include <set>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "test/core/resource_quota/call_checker.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {

template <size_t kSize>
struct Sized {
  char blah[kSize];
  virtual ~Sized() {}
};

TEST(MemoryRequestTest, ConversionFromSize) {
  MemoryRequest request = 3;
  EXPECT_EQ(request.min(), 3);
  EXPECT_EQ(request.max(), 3);
}

TEST(MemoryRequestTest, MinMax) {
  MemoryRequest request(3, 7);
  EXPECT_EQ(request.min(), 3);
  EXPECT_EQ(request.max(), 7);
}

TEST(MemoryQuotaTest, NoOp) { MemoryQuota("foo"); }

TEST(MemoryQuotaTest, CreateAllocatorNoOp) {
  MemoryQuota memory_quota("foo");
  auto memory_allocator = memory_quota.CreateMemoryAllocator("bar");
}

TEST(MemoryQuotaTest, CreateObjectFromAllocator) {
  ExecCtx exec_ctx;
  MemoryQuota memory_quota("foo");
  auto memory_allocator = memory_quota.CreateMemoryAllocator("bar");
  auto object = memory_allocator.MakeUnique<Sized<4096>>();
}

TEST(MemoryQuotaTest, CreateSomeObjectsAndExpectReclamation) {
  ExecCtx exec_ctx;

  MemoryQuota memory_quota("foo");
  memory_quota.SetSize(4096);
  auto memory_allocator = memory_quota.CreateMemoryOwner();
  auto object = memory_allocator.MakeUnique<Sized<2048>>();

  auto checker1 = CallChecker::Make();
  memory_allocator.PostReclaimer(
      ReclamationPass::kDestructive,
      [&object, checker1](std::optional<ReclamationSweep> sweep) {
        checker1->Called();
        EXPECT_TRUE(sweep.has_value());
        object.reset();
      });
  auto object2 = memory_allocator.MakeUnique<Sized<2048>>();
  exec_ctx.Flush();
  EXPECT_EQ(object.get(), nullptr);

  auto checker2 = CallChecker::Make();
  memory_allocator.PostReclaimer(
      ReclamationPass::kDestructive,
      [&object2, checker2](std::optional<ReclamationSweep> sweep) {
        checker2->Called();
        EXPECT_TRUE(sweep.has_value());
        object2.reset();
      });
  auto object3 = memory_allocator.MakeUnique<Sized<2048>>();
  exec_ctx.Flush();
  EXPECT_EQ(object2.get(), nullptr);
}

TEST(MemoryQuotaTest, ReserveRangeNoPressure) {
  MemoryQuota memory_quota("foo");
  auto memory_allocator = memory_quota.CreateMemoryAllocator("bar");
  size_t total = 0;
  for (int i = 0; i < 10000; i++) {
    ExecCtx exec_ctx;
    auto n = memory_allocator.Reserve(MemoryRequest(100, 40000));
    EXPECT_EQ(n, 40000);
    total += n;
  }
  memory_allocator.Release(total);
}

TEST(MemoryQuotaTest, MakeSlice) {
  MemoryQuota memory_quota("foo");
  auto memory_allocator = memory_quota.CreateMemoryAllocator("bar");
  std::vector<grpc_slice> slices;
  for (int i = 1; i < 1000; i++) {
    ExecCtx exec_ctx;
    int min = i;
    int max = (10 * i) - 9;
    slices.push_back(memory_allocator.MakeSlice(MemoryRequest(min, max)));
  }
  ExecCtx exec_ctx;
  for (grpc_slice slice : slices) {
    grpc_slice_unref(slice);
  }
}

TEST(MemoryQuotaTest, ContainerAllocator) {
  ExecCtx exec_ctx;
  MemoryQuota memory_quota("foo");
  auto memory_allocator = memory_quota.CreateMemoryAllocator("bar");
  Vector<int> vec(&memory_allocator);
  for (int i = 0; i < 100000; i++) {
    vec.push_back(i);
  }
}

TEST(MemoryQuotaTest, NoBunchingIfIdle) {

  MemoryQuota memory_quota("foo");
  std::atomic<size_t> count_reclaimers_called{0};

  for (size_t i = 0; i < 10000; i++) {
    ExecCtx exec_ctx;
    auto memory_owner = memory_quota.CreateMemoryOwner();
    memory_owner.PostReclaimer(
        ReclamationPass::kDestructive,
        [&count_reclaimers_called](std::optional<ReclamationSweep> sweep) {
          EXPECT_FALSE(sweep.has_value());
          count_reclaimers_called.fetch_add(1, std::memory_order_relaxed);
        });
    auto object = memory_owner.MakeUnique<Sized<2048>>();
  }

  EXPECT_GE(count_reclaimers_called.load(std::memory_order_relaxed), 8000);
}

TEST(MemoryQuotaTest, AllMemoryQuotas) {
  auto gather = []() {
    std::set<std::string> all_names;
    for (const auto& q : AllMemoryQuotas()) {
      all_names.emplace(q->name());
    }
    return all_names;
  };

  auto m1 = MakeMemoryQuota("m1");
  auto m2 = MakeMemoryQuota("m2");

  EXPECT_EQ(gather(), std::set<std::string>({"m1", "m2"}));
  m1.reset();
  EXPECT_EQ(gather(), std::set<std::string>({"m2"}));
}

TEST(MemoryQuotaTest, ContainerMemoryAccountedFor) {
  MemoryQuota memory_quota("foo");
  memory_quota.SetSize(1000000);
  EXPECT_EQ(ContainerMemoryPressure(), 0.0);
  auto owner = memory_quota.CreateMemoryOwner();
  const double original_memory_pressure =
      owner.GetPressureInfo().instantaneous_pressure;
  EXPECT_LT(original_memory_pressure, 0.01);
  SetContainerMemoryPressure(1.0);
  EXPECT_EQ(owner.GetPressureInfo().instantaneous_pressure, 1.0);
  SetContainerMemoryPressure(0.0);
  EXPECT_EQ(owner.GetPressureInfo().instantaneous_pressure,
            original_memory_pressure);
  SetContainerMemoryPressure(0.0);
}

}

namespace memory_quota_detail {
namespace testing {

TEST(PressureControllerTest, Init) {
  PressureController c{100, 3};
  EXPECT_EQ(c.Update(-1.0), 0.0);
  EXPECT_EQ(c.Update(1.0), 1.0);
}

TEST(PressureControllerTest, LowDecays) {
  PressureController c{100, 3};
  EXPECT_EQ(c.Update(1.0), 1.0);
  double last = 1.0;
  while (last > 1e-30) {
    double x = c.Update(-1.0);
    EXPECT_LE(x, last);
    last = x;
  }
}

TEST(PressureTrackerTest, NoOp) { PressureTracker(); }

TEST(PressureTrackerTest, Decays) {
  PressureTracker tracker;
  int cur_ms = 0;
  auto step_time = [&] {
    ++cur_ms;
    return Timestamp::ProcessEpoch() + Duration::Seconds(1) +
           Duration::Milliseconds(cur_ms);
  };

  {
    ExecCtx exec_ctx;
    exec_ctx.TestOnlySetNow(step_time());
    EXPECT_EQ(tracker.AddSampleAndGetControlValue(0.0), 0.0);
  }

  {
    ExecCtx exec_ctx;
    exec_ctx.TestOnlySetNow(step_time());
    EXPECT_EQ(tracker.AddSampleAndGetControlValue(1.0), 1.0);
  }

  const int got_full = cur_ms;
  double last_reported = 1.0;
  while (true) {
    ExecCtx exec_ctx;
    exec_ctx.TestOnlySetNow(step_time());
    double new_reported = tracker.AddSampleAndGetControlValue(0.0);
    EXPECT_LE(new_reported, last_reported);
    last_reported = new_reported;
    if (new_reported < 0.1) break;
  }

  ASSERT_LE(cur_ms, got_full + 1000000);
}

TEST(PressureTrackerTest, ManyThreads) {
  PressureTracker tracker;
  std::vector<std::thread> threads;
  std::atomic<bool> shutdown{false};
  threads.reserve(10);
  for (int i = 0; i < 10; i++) {
    threads.emplace_back([&tracker, &shutdown] {
      std::random_device rng;
      std::uniform_real_distribution<double> dist(0.0, 1.0);
      while (!shutdown.load(std::memory_order_relaxed)) {
        ExecCtx exec_ctx;
        tracker.AddSampleAndGetControlValue(dist(rng));
      }
    });
  }
  std::this_thread::sleep_for(std::chrono::seconds(5));
  shutdown.store(true, std::memory_order_relaxed);
  for (auto& thread : threads) {
    thread.join();
  }
}

}
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment give_me_a_name(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  gpr_log_verbosity_init();
  return RUN_ALL_TESTS();
}
