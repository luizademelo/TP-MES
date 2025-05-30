// Copyright 2021 gRPC authors.

#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/memory_request.h>
#include <stddef.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <initializer_list>
#include <memory>
#include <optional>
#include <random>
#include <thread>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/sync.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {

namespace {
class StressTest {
 public:

  StressTest(size_t num_quotas, size_t num_allocators) {
    for (size_t i = 0; i < num_quotas; ++i) {
      quotas_.emplace_back(absl::StrCat("quota[", i, "]"));
    }
    std::random_device g;
    std::uniform_int_distribution<size_t> dist(0, num_quotas - 1);
    for (size_t i = 0; i < num_allocators; ++i) {
      allocators_.emplace_back(quotas_[dist(g)].CreateMemoryOwner());
    }
  }

  ~StressTest() {
    ExecCtx exec_ctx;
    allocators_.clear();
    quotas_.clear();
  }

  void Run(int seconds) {
    std::vector<std::thread> threads;

    threads.reserve(2 + allocators_.size());
    for (int i = 0; i < 2; i++) threads.push_back(Run(Resizer));

    for (size_t i = 0; i < allocators_.size(); i++) {
      auto* allocator = &allocators_[i];
      for (ReclamationPass pass :
           {ReclamationPass::kBenign, ReclamationPass::kIdle,
            ReclamationPass::kDestructive}) {
        threads.push_back(Run([allocator, pass](StatePtr st) mutable {
          if (st->RememberReservation(
                  allocator->MakeReservation(st->RandomRequest()))) {
            allocator->PostReclaimer(
                pass, [st](std::optional<ReclamationSweep> sweep) {
                  if (!sweep.has_value()) return;
                  st->ForgetReservations();
                });
          }
        }));
      }
    }

    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    done_.store(true, std::memory_order_relaxed);
    while (!threads.empty()) {
      threads.back().join();
      threads.pop_back();
    }
  }

 private:

  class State {
   public:
    explicit State(StressTest* test)
        : test_(test),
          quotas_distribution_(0, test_->quotas_.size() - 1),
          allocators_distribution_(0, test_->allocators_.size() - 1),
          size_distribution_(1, 4 * 1024 * 1024),
          quota_size_distribution_(1024 * 1024, size_t{8} * 1024 * 1024 * 1024),
          choose_variable_size_(1, 100) {}

    MemoryQuota* RandomQuota() {
      return &test_->quotas_[quotas_distribution_(g_)];
    }

    MemoryOwner* RandomAllocator() {
      return &test_->allocators_[allocators_distribution_(g_)];
    }

    MemoryRequest RandomRequest() {
      size_t a = size_distribution_(g_);
      if (choose_variable_size_(g_) == 1) {
        size_t b = size_distribution_(g_);
        return MemoryRequest(std::min(a, b), std::max(a, b));
      }
      return MemoryRequest(a);
    }

    size_t RandomQuotaSize() { return quota_size_distribution_(g_); }

    bool RememberReservation(MemoryAllocator::Reservation reservation)
        ABSL_LOCKS_EXCLUDED(mu_) {
      MutexLock lock(&mu_);
      bool was_empty = reservations_.empty();
      reservations_.emplace_back(std::move(reservation));
      return was_empty;
    }

    std::vector<MemoryAllocator::Reservation> ForgetReservations()
        ABSL_LOCKS_EXCLUDED(mu_) {
      MutexLock lock(&mu_);
      return std::move(reservations_);
    }

   private:

    StressTest* const test_;

    std::mt19937 g_{std::random_device()()};

    std::uniform_int_distribution<size_t> quotas_distribution_;

    std::uniform_int_distribution<size_t> allocators_distribution_;

    std::uniform_int_distribution<size_t> size_distribution_;

    std::uniform_int_distribution<size_t> quota_size_distribution_;

    std::uniform_int_distribution<size_t> choose_variable_size_;

    Mutex mu_;

    std::vector<MemoryAllocator::Reservation> reservations_
        ABSL_GUARDED_BY(mu_);
  };

  using StatePtr = std::shared_ptr<State>;

  static void Resizer(StatePtr st) {
    auto* quota = st->RandomQuota();
    size_t size = st->RandomQuotaSize();
    quota->SetSize(size);
  }

  template <typename Fn>
  std::thread Run(Fn fn) {
    return std::thread([this, fn]() mutable {
      auto state = std::make_shared<State>(this);
      while (!done_.load(std::memory_order_relaxed)) {
        ExecCtx exec_ctx;
        fn(state);
      }
    });
  }

  std::atomic<bool> done_{false};

  std::vector<MemoryQuota> quotas_;

  std::vector<MemoryOwner> allocators_;
};
}

}

TEST(MemoryQuotaStressTest, MainTest) {
  if (sizeof(void*) != 8) {
    LOG(ERROR) << "This test assumes 64-bit processors in the values it uses "
                  "for sizes. Since this test is mostly aimed at TSAN "
                  "coverage, and that's mostly platform independent, we simply "
                  "skip this test in 32-bit builds.";
    GTEST_SKIP();
  }
  grpc_core::StressTest(16, 20).Run(8);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment give_me_a_name(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
