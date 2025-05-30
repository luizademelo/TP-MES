// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_POOL_THREAD_COUNT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_POOL_THREAD_COUNT_H

#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_event_engine::experimental {

class BusyThreadCount {
 public:

  class AutoThreadCounter {
   public:
    AutoThreadCounter(BusyThreadCount* counter, size_t idx)
        : counter_(counter), idx_(idx) {
      counter_->Increment(idx_);
    }
    ~AutoThreadCounter() {
      if (counter_ != nullptr) counter_->Decrement(idx_);
    }

    AutoThreadCounter(const AutoThreadCounter&) = delete;
    AutoThreadCounter& operator=(const AutoThreadCounter&) = delete;

    AutoThreadCounter(AutoThreadCounter&& other) noexcept {
      counter_ = std::exchange(other.counter_, nullptr);
      idx_ = other.idx_;
    }
    AutoThreadCounter& operator=(AutoThreadCounter&& other) noexcept {
      counter_ = std::exchange(other.counter_, nullptr);
      idx_ = other.idx_;
      return *this;
    }

   private:
    BusyThreadCount* counter_;
    size_t idx_;
  };

  BusyThreadCount() : shards_(grpc_core::Clamp(gpr_cpu_num_cores(), 2u, 64u)) {}
  AutoThreadCounter MakeAutoThreadCounter(size_t idx) {
    return AutoThreadCounter(this, idx);
  };
  void Increment(size_t idx) {
    shards_[idx].busy_count.fetch_add(1, std::memory_order_relaxed);
  }
  void Decrement(size_t idx) {
    shards_[idx].busy_count.fetch_sub(1, std::memory_order_relaxed);
  }
  size_t count() {
    return std::accumulate(
        shards_.begin(), shards_.end(), 0, [](size_t running, ShardedData& d) {
          return running + d.busy_count.load(std::memory_order_relaxed);
        });
  }

  size_t NextIndex() { return next_idx_.fetch_add(1) % shards_.size(); }

 private:

  struct ShardedData {
    std::atomic<size_t> busy_count{0};
  } GPR_ALIGN_STRUCT(GPR_CACHELINE_SIZE);

  std::vector<ShardedData> shards_;
  std::atomic<size_t> next_idx_{0};
};

class LivingThreadCount {
 public:

  class AutoThreadCounter {
   public:
    explicit AutoThreadCounter(LivingThreadCount* counter) : counter_(counter) {
      counter_->Increment();
    }
    ~AutoThreadCounter() {
      if (counter_ != nullptr) counter_->Decrement();
    }

    AutoThreadCounter(const AutoThreadCounter&) = delete;
    AutoThreadCounter& operator=(const AutoThreadCounter&) = delete;

    AutoThreadCounter(AutoThreadCounter&& other) noexcept {
      counter_ = std::exchange(other.counter_, nullptr);
    }
    AutoThreadCounter& operator=(AutoThreadCounter&& other) noexcept {
      counter_ = std::exchange(other.counter_, nullptr);
      return *this;
    }

   private:
    LivingThreadCount* counter_;
  };

  AutoThreadCounter MakeAutoThreadCounter() { return AutoThreadCounter(this); };
  void Increment() ABSL_LOCKS_EXCLUDED(mu_) {
    grpc_core::MutexLock lock(&mu_);
    ++living_count_;
    cv_.SignalAll();
  }
  void Decrement() ABSL_LOCKS_EXCLUDED(mu_) {
    grpc_core::MutexLock lock(&mu_);
    --living_count_;
    cv_.SignalAll();
  }

  absl::Status BlockUntilThreadCount(size_t desired_threads, const char* why,
                                     grpc_core::Duration stuck_timeout)
      ABSL_LOCKS_EXCLUDED(mu_);
  size_t count() ABSL_LOCKS_EXCLUDED(mu_) {
    grpc_core::MutexLock lock(&mu_);
    return CountLocked();
  }

 private:
  size_t CountLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return living_count_;
  }
  size_t WaitForCountChange(size_t desired_threads,
                            grpc_core::Duration timeout);

  grpc_core::Mutex mu_;
  grpc_core::CondVar cv_ ABSL_GUARDED_BY(mu_);
  size_t living_count_ ABSL_GUARDED_BY(mu_) = 0;
};

}

#endif
