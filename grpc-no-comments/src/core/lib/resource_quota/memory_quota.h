// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_MEMORY_QUOTA_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_MEMORY_QUOTA_H

#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/memory_request.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <array>
#include <atomic>
#include <cstddef>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_set.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/resource_quota/periodic_update.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class BasicMemoryQuota;
class MemoryQuota;
class GrpcMemoryAllocatorImpl;

using grpc_event_engine::experimental::MemoryRequest;

using EventEngineMemoryAllocatorImpl =
    grpc_event_engine::experimental::internal::MemoryAllocatorImpl;
using grpc_event_engine::experimental::MemoryAllocator;
template <typename T>
using Vector = grpc_event_engine::experimental::Vector<T>;

enum class ReclamationPass {

  kBenign = 0,

  kIdle = 1,

  kDestructive = 2,
};
static constexpr size_t kNumReclamationPasses = 3;

class ReclamationSweep {
 public:
  ReclamationSweep() = default;
  ReclamationSweep(std::shared_ptr<BasicMemoryQuota> memory_quota,
                   uint64_t sweep_token, Waker waker)
      : memory_quota_(std::move(memory_quota)),
        sweep_token_(sweep_token),
        waker_(std::move(waker)) {}
  ~ReclamationSweep();

  ReclamationSweep(const ReclamationSweep&) = delete;
  ReclamationSweep& operator=(const ReclamationSweep&) = delete;
  ReclamationSweep(ReclamationSweep&&) = default;
  ReclamationSweep& operator=(ReclamationSweep&&) = default;

  bool IsSufficient() const;

  void Finish();

 private:
  std::shared_ptr<BasicMemoryQuota> memory_quota_;
  uint64_t sweep_token_;
  Waker waker_;
};

class ReclaimerQueue {
 private:
  struct QueuedNode;
  struct State;

 public:
  class Handle : public InternallyRefCounted<Handle> {
   public:
    Handle() = default;
    template <typename F>
    explicit Handle(F reclaimer, std::shared_ptr<State> state)
        : sweep_(new SweepFn<F>(std::move(reclaimer), std::move(state))) {}
    ~Handle() override {
      DCHECK_EQ(sweep_.load(std::memory_order_relaxed), nullptr);
    }

    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;

    void Orphan() final;
    void Run(ReclamationSweep reclamation_sweep);
    bool Requeue(ReclaimerQueue* new_queue);

   private:
    friend class ReclaimerQueue;
    using InternallyRefCounted<Handle>::Ref;

    class Sweep {
     public:
      virtual void RunAndDelete(std::optional<ReclamationSweep> sweep) = 0;

     protected:
      explicit Sweep(std::shared_ptr<State> state) : state_(std::move(state)) {}
      ~Sweep() = default;
      void MarkCancelled();

     private:
      std::shared_ptr<State> state_;
    };

    template <typename F>
    class SweepFn final : public Sweep {
     public:
      explicit SweepFn(F&& f, std::shared_ptr<State> state)
          : Sweep(std::move(state)), f_(std::move(f)) {}
      void RunAndDelete(std::optional<ReclamationSweep> sweep) override {
        if (!sweep.has_value()) MarkCancelled();
        f_(std::move(sweep));
        delete this;
      }

     private:
      F f_;
    };

    std::atomic<Sweep*> sweep_{nullptr};
  };

  ReclaimerQueue();
  ~ReclaimerQueue();

  ReclaimerQueue(const ReclaimerQueue&) = delete;
  ReclaimerQueue& operator=(const ReclaimerQueue&) = delete;

  template <typename F>
  GRPC_MUST_USE_RESULT OrphanablePtr<Handle> Insert(F reclaimer) {
    auto p = MakeOrphanable<Handle>(std::move(reclaimer), state_);
    Enqueue(p->Ref());
    return p;
  }

  Poll<RefCountedPtr<Handle>> PollNext();

  class NextPromise {
   public:
    explicit NextPromise(ReclaimerQueue* queue) : queue_(queue) {}
    Poll<RefCountedPtr<Handle>> operator()() { return queue_->PollNext(); }

   private:

    ReclaimerQueue* queue_;
  };
  GRPC_MUST_USE_RESULT NextPromise Next() { return NextPromise(this); }

 private:
  void Enqueue(RefCountedPtr<Handle> handle);

  std::shared_ptr<State> state_;
};

namespace memory_quota_detail {

class PressureController {
 public:
  PressureController(uint8_t max_ticks_same, uint8_t max_reduction_per_tick)
      : max_ticks_same_(max_ticks_same),
        max_reduction_per_tick_(max_reduction_per_tick) {}

  double Update(double error);

  std::string DebugString() const;

 private:

  uint8_t ticks_same_ = 0;

  const uint8_t max_ticks_same_;

  const uint8_t max_reduction_per_tick_;

  bool last_was_low_ = true;

  double min_ = 0.0;

  double max_ = 2.0;

  double last_control_ = 0.0;
};

class PressureTracker {
 public:
  double AddSampleAndGetControlValue(double sample);

 private:
  std::atomic<double> max_this_round_{0.0};
  std::atomic<double> report_{0.0};
  PeriodicUpdate update_{Duration::Seconds(1)};
  PressureController controller_{100, 3};
};
}

static constexpr size_t kBigAllocatorThreshold = 0.5 * 1024 * 1024;

static constexpr size_t kSmallAllocatorThreshold = 0.1 * 1024 * 1024;

class BasicMemoryQuota final
    : public std::enable_shared_from_this<BasicMemoryQuota> {
 public:

  struct PressureInfo {

    double instantaneous_pressure = 0.0;

    double pressure_control_value = 0.0;

    size_t max_recommended_allocation_size = 0;
  };

  explicit BasicMemoryQuota(std::string name);

  void Start();

  void Stop();

  void SetSize(size_t new_size);

  void Take(GrpcMemoryAllocatorImpl* allocator, size_t amount);

  void FinishReclamation(uint64_t token, Waker waker);

  void Return(size_t amount);

  void AddNewAllocator(GrpcMemoryAllocatorImpl* allocator);

  void RemoveAllocator(GrpcMemoryAllocatorImpl* allocator);

  void MaybeMoveAllocator(GrpcMemoryAllocatorImpl* allocator,
                          size_t old_free_bytes, size_t new_free_bytes);

  PressureInfo GetPressureInfo();

  ReclaimerQueue* reclaimer_queue(size_t i) { return &reclaimers_[i]; }

  absl::string_view name() const { return name_; }

 private:
  friend class ReclamationSweep;
  class WaitForSweepPromise;

  class AllocatorBucket {
   public:
    struct Shard {
      absl::flat_hash_set<GrpcMemoryAllocatorImpl*> allocators
          ABSL_GUARDED_BY(shard_mu);
      Mutex shard_mu;
    };

    Shard& SelectShard(void* key) {
      const size_t hash = HashPointer(key, shards.size());
      return shards[hash % shards.size()];
    }

    std::array<Shard, 16> shards;
  };

  static constexpr intptr_t kInitialSize = std::numeric_limits<intptr_t>::max();

  void MaybeMoveAllocatorBigToSmall(GrpcMemoryAllocatorImpl* allocator);

  void MaybeMoveAllocatorSmallToBig(GrpcMemoryAllocatorImpl* allocator);

  std::atomic<intptr_t> free_bytes_{kInitialSize};

  std::atomic<size_t> quota_size_{kInitialSize};

  ReclaimerQueue reclaimers_[kNumReclamationPasses];

  AllocatorBucket small_allocators_;
  AllocatorBucket big_allocators_;

  ActivityPtr reclaimer_activity_;

  std::atomic<uint64_t> reclamation_counter_{0};

  memory_quota_detail::PressureTracker pressure_tracker_;

  std::string name_;
};

class GrpcMemoryAllocatorImpl final : public EventEngineMemoryAllocatorImpl {
 public:
  explicit GrpcMemoryAllocatorImpl(
      std::shared_ptr<BasicMemoryQuota> memory_quota);
  ~GrpcMemoryAllocatorImpl() override;

  size_t Reserve(MemoryRequest request) override;

  grpc_slice MakeSlice(MemoryRequest request) override;

  void Release(size_t n) override {

    size_t prev_free = free_bytes_.fetch_add(n, std::memory_order_release);
    if ((!IsUnconstrainedMaxQuotaBufferSizeEnabled() &&
         prev_free + n > kMaxQuotaBufferSize) ||
        donate_back_.Tick([](Duration) {})) {

      MaybeDonateBack();
    }
    size_t new_free = free_bytes_.load(std::memory_order_relaxed);
    memory_quota_->MaybeMoveAllocator(this, prev_free, new_free);
  }

  void ReturnFree() {
    size_t ret = free_bytes_.exchange(0, std::memory_order_acq_rel);
    if (ret == 0) return;
    GRPC_TRACE_LOG(resource_quota, INFO)
        << "Allocator " << this << " returning " << ret << " bytes to quota";
    taken_bytes_.fetch_sub(ret, std::memory_order_relaxed);
    memory_quota_->Return(ret);
    memory_quota_->MaybeMoveAllocator(this, ret,
                                      0);
  }

  template <typename F>
  void PostReclaimer(ReclamationPass pass, F fn) {
    MutexLock lock(&reclaimer_mu_);
    CHECK(!shutdown_);
    InsertReclaimer(static_cast<size_t>(pass), std::move(fn));
  }

  void Shutdown() override;

  BasicMemoryQuota::PressureInfo GetPressureInfo() const {
    return memory_quota_->GetPressureInfo();
  }

  size_t GetFreeBytes() const {
    return free_bytes_.load(std::memory_order_relaxed);
  }

  size_t IncrementShardIndex() {
    return chosen_shard_idx_.fetch_add(1, std::memory_order_relaxed);
  }

 private:
  static constexpr size_t kMaxQuotaBufferSize = 1024 * 1024;

  GRPC_MUST_USE_RESULT std::optional<size_t> TryReserve(MemoryRequest request);

  void MaybeDonateBack();

  void Replenish();
  template <typename F>
  void InsertReclaimer(size_t pass, F fn)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(reclaimer_mu_) {
    reclamation_handles_[pass] =
        memory_quota_->reclaimer_queue(pass)->Insert(std::move(fn));
  }

  const std::shared_ptr<BasicMemoryQuota> memory_quota_;

  std::atomic<size_t> free_bytes_{0};

  std::atomic<size_t> taken_bytes_{sizeof(GrpcMemoryAllocatorImpl)};

  std::atomic<size_t> chosen_shard_idx_{0};

  PeriodicUpdate donate_back_{Duration::Seconds(10)};
  Mutex reclaimer_mu_;
  bool shutdown_ ABSL_GUARDED_BY(reclaimer_mu_) = false;

  OrphanablePtr<ReclaimerQueue::Handle>
      reclamation_handles_[kNumReclamationPasses] ABSL_GUARDED_BY(
          reclaimer_mu_);
};

class MemoryOwner final : public MemoryAllocator {
 public:
  MemoryOwner() = default;

  explicit MemoryOwner(std::shared_ptr<GrpcMemoryAllocatorImpl> allocator)
      : MemoryAllocator(std::move(allocator)) {}

  template <typename F>
  void PostReclaimer(ReclamationPass pass, F fn) {
    impl()->PostReclaimer(pass, std::move(fn));
  }

  BasicMemoryQuota::PressureInfo GetPressureInfo() const {
    if (!is_valid()) return {};
    return impl()->GetPressureInfo();
  }

  template <typename T, typename... Args>
  OrphanablePtr<T> MakeOrphanable(Args&&... args) {
    return OrphanablePtr<T>(New<T>(std::forward<Args>(args)...));
  }

  bool is_valid() const { return impl() != nullptr; }

  static double memory_pressure_high_threshold() { return 0.99; }

  bool IsMemoryPressureHigh() const {
    return GetPressureInfo().pressure_control_value >
           memory_pressure_high_threshold();
  }

 private:
  const GrpcMemoryAllocatorImpl* impl() const {
    return static_cast<const GrpcMemoryAllocatorImpl*>(get_internal_impl_ptr());
  }

  GrpcMemoryAllocatorImpl* impl() {
    return static_cast<GrpcMemoryAllocatorImpl*>(get_internal_impl_ptr());
  }
};

class MemoryQuota final
    : public grpc_event_engine::experimental::MemoryAllocatorFactory {
 public:
  explicit MemoryQuota(std::string name)
      : memory_quota_(std::make_shared<BasicMemoryQuota>(std::move(name))) {
    memory_quota_->Start();
  }
  ~MemoryQuota() override {
    if (memory_quota_ != nullptr) memory_quota_->Stop();
  }

  MemoryQuota(const MemoryQuota&) = delete;
  MemoryQuota& operator=(const MemoryQuota&) = delete;
  MemoryQuota(MemoryQuota&&) = default;
  MemoryQuota& operator=(MemoryQuota&&) = default;

  MemoryAllocator CreateMemoryAllocator(absl::string_view name) override;
  MemoryOwner CreateMemoryOwner();

  void SetSize(size_t new_size) { memory_quota_->SetSize(new_size); }

  bool IsMemoryPressureHigh() const {
    return memory_quota_->GetPressureInfo().pressure_control_value >
           MemoryOwner::memory_pressure_high_threshold();
  }

 private:
  friend class MemoryOwner;
  std::shared_ptr<BasicMemoryQuota> memory_quota_;
};

using MemoryQuotaRefPtr = std::shared_ptr<MemoryQuota>;
inline MemoryQuotaRefPtr MakeMemoryQuota(std::string name) {
  return std::make_shared<MemoryQuota>(std::move(name));
}

std::vector<std::shared_ptr<BasicMemoryQuota>> AllMemoryQuotas();

void SetContainerMemoryPressure(double pressure);

double ContainerMemoryPressure();

}

#endif
