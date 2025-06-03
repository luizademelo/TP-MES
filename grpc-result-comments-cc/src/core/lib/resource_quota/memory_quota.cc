Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/memory_quota.h"

#include <grpc/event_engine/internal/memory_allocator_impl.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <tuple>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/exec_ctx_wakeup_scheduler.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/race.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/slice/slice_refcount.h"
#include "src/core/util/mpscq.h"
#include "src/core/util/useful.h"

namespace grpc_core {

namespace {
// Constants for memory replenishment parameters
constexpr size_t kMaxReplenishBytes = 1024 * 1024; // Maximum bytes to replenish at once
constexpr size_t kMinReplenishBytes = 4096;        // Minimum bytes to replenish at once

// Singleton class to track all memory quotas in the system
class MemoryQuotaTracker {
 public:
  // Get the singleton instance
  static MemoryQuotaTracker& Get() {
    static MemoryQuotaTracker* tracker = new MemoryQuotaTracker();
    return *tracker;
  }

  // Add a new memory quota to track
  void Add(std::shared_ptr<BasicMemoryQuota> quota) {
    MutexLock lock(&mu_);
    GatherAndGarbageCollect();
    quotas_.push_back(quota);
  }

  // Get all currently active memory quotas
  std::vector<std::shared_ptr<BasicMemoryQuota>> All() {
    MutexLock lock(&mu_);
    return GatherAndGarbageCollect();
  }

 private:
  MemoryQuotaTracker() {}

  // Remove expired weak pointers and return active quotas
  std::vector<std::shared_ptr<BasicMemoryQuota>> GatherAndGarbageCollect()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    std::vector<std::weak_ptr<BasicMemoryQuota>> new_quotas;
    std::vector<std::shared_ptr<BasicMemoryQuota>> all_quotas;
    for (const auto& quota : quotas_) {
      auto p = quota.lock();
      if (p == nullptr) continue;
      new_quotas.push_back(quota);
      all_quotas.push_back(p);
    }
    quotas_.swap(new_quotas);
    return all_quotas;
  }

  Mutex mu_;
  std::vector<std::weak_ptr<BasicMemoryQuota>> quotas_ ABSL_GUARDED_BY(mu_);
};

// Custom slice refcount that returns memory to allocator when destroyed
class SliceRefCount : public grpc_slice_refcount {
 public:
  SliceRefCount(
      std::shared_ptr<
          grpc_event_engine::experimental::internal::MemoryAllocatorImpl>
          allocator,
      size_t size)
      : grpc_slice_refcount(Destroy),
        allocator_(std::move(allocator)),
        size_(size) {}
  
  ~SliceRefCount() {
    allocator_->Release(size_);
    allocator_.reset();
  }

 private:
  // Static destroy function called when refcount reaches zero
  static void Destroy(grpc_slice_refcount* p) {
    auto* rc = static_cast<SliceRefCount*>(p);
    rc->~SliceRefCount();
    free(rc);
  }

  std::shared_ptr<
      grpc_event_engine::experimental::internal::MemoryAllocatorImpl>
      allocator_;
  size_t size_;
};

// Global container memory pressure tracking
std::atomic<double> container_memory_pressure{0.0};

} // namespace

// Set the container-wide memory pressure value
void SetContainerMemoryPressure(double pressure) {
  container_memory_pressure.store(pressure, std::memory_order_relaxed);
}

// Get the container-wide memory pressure value
double ContainerMemoryPressure() {
  return container_memory_pressure.load(std::memory_order_relaxed);
}

// Destructor for reclamation sweep - ensures reclamation is finished
ReclamationSweep::~ReclamationSweep() {
  if (memory_quota_ != nullptr) {
    memory_quota_->FinishReclamation(sweep_token_, std::move(waker_));
  }
}

// Explicitly finish reclamation
void ReclamationSweep::Finish() {
  auto memory_quota = std::move(memory_quota_);
  if (memory_quota != nullptr) {
    auto sweep_token = sweep_token_;
    auto waker = std::move(waker_);
    memory_quota->FinishReclamation(sweep_token, std::move(waker));
  }
}

// Node structure for reclaimer queue
struct ReclaimerQueue::QueuedNode
    : public MultiProducerSingleConsumerQueue::Node {
  explicit QueuedNode(RefCountedPtr<Handle> reclaimer_handle)
      : reclaimer_handle(std::move(reclaimer_handle)) {}
  RefCountedPtr<Handle> reclaimer_handle;
};

// State for reclaimer queue
struct ReclaimerQueue::State {
  Mutex reader_mu;
  MultiProducerSingleConsumerQueue queue;
  Waker waker ABSL_GUARDED_BY(reader_mu);

  ~State() {
    // Clean up any remaining nodes
    bool empty = false;
    do {
      delete static_cast<QueuedNode*>(queue.PopAndCheckEnd(&empty));
    } while (!empty);
  }
};

// Handle orphan implementation - cancels any pending sweep
void ReclaimerQueue::Handle::Orphan() {
  if (auto* sweep = sweep_.exchange(nullptr, std::memory_order_acq_rel)) {
    sweep->RunAndDelete(std::nullopt);
  }
  Unref();
}

// Run the reclaimer with the given sweep
void ReclaimerQueue::Handle::Run(ReclamationSweep reclamation_sweep) {
  if (auto* sweep = sweep_.exchange(nullptr, std::memory_order_acq_rel)) {
    sweep->RunAndDelete(std::move(reclamation_sweep));
  }
}

// Requeue this handle in a new queue
bool ReclaimerQueue::Handle::Requeue(ReclaimerQueue* new_queue) {
  if (sweep_.load(std::memory_order_relaxed)) {
    new_queue->Enqueue(Ref());
    return true;
  } else {
    return false;
  }
}

// Mark the sweep as cancelled
void ReclaimerQueue::Handle::Sweep::MarkCancelled() {
  MutexLock lock(&state_->reader_mu);
  while (true) {
    bool empty = false;
    std::unique_ptr<QueuedNode> node(
        static_cast<QueuedNode*>(state_->queue.PopAndCheckEnd(&empty)));
    if (node == nullptr) break;
    if (node->reclaimer_handle->sweep_.load(std::memory_order_relaxed) !=
        nullptr) {
      state_->queue.Push(node.release());
      break;
    }
  }
}

// Create a new reclaimer queue
ReclaimerQueue::ReclaimerQueue() : state_(std::make_shared<State>()) {}

ReclaimerQueue::~ReclaimerQueue() = default;

// Enqueue a new reclaimer handle
void ReclaimerQueue::Enqueue(RefCountedPtr<Handle> handle) {
  if (state_->queue.Push(new QueuedNode(std::move(handle)))) {
    MutexLock lock(&state_->reader_mu);
    state_->waker.Wakeup();
  }
}

// Poll for next reclaimer handle
Poll<RefCountedPtr<ReclaimerQueue::Handle>> ReclaimerQueue::PollNext() {
  MutexLock lock(&state_->reader_mu);
  bool empty = false;

  std::unique_ptr<QueuedNode> node(
      static_cast<QueuedNode*>(state_->queue.PopAndCheckEnd(&empty)));

  if (node != nullptr) return std::move(node->reclaimer_handle);
  if (!empty) {
    // More items may come - repoll immediately
    GetContext<Activity>()->ForceImmediateRepoll();
  } else {
    // Queue is empty - set waker for when new items arrive
    state_->waker = GetContext<Activity>()->MakeNonOwningWaker();
  }
  return Pending{};
}

// Memory allocator implementation constructor
GrpcMemoryAllocatorImpl::GrpcMemoryAllocatorImpl(
    std::shared_ptr<BasicMemoryQuota> memory_quota)
    : memory_quota_(memory_quota) {
  // Take initial memory from quota
  memory_quota_->Take(this, taken_bytes_);
  memory_quota_->AddNewAllocator(this);
}

// Memory allocator destructor - returns all taken memory
GrpcMemoryAllocatorImpl::~GrpcMemoryAllocatorImpl() {
  CHECK_EQ(free_bytes_.load(std::memory_order_acquire) +
               sizeof(GrpcMemoryAllocatorImpl),
           taken_bytes_.load(std::memory_order_relaxed));
  memory_quota_->Return(taken_bytes_.load(std::memory_order_relaxed));
}

// Shutdown the allocator
void GrpcMemoryAllocatorImpl::Shutdown() {
  memory_quota_->RemoveAllocator(this);
  std::shared_ptr<BasicMemoryQuota> memory_quota;
  OrphanablePtr<ReclaimerQueue::Handle>
      reclamation_handles[kNumReclamationPasses];
  {
    MutexLock lock(&reclaimer_mu_);
    CHECK(!shutdown_);
    shutdown_ = true;
    memory_quota = memory_quota_;
    for (size_t i = 0; i < kNumReclamationPasses; i++) {
      reclamation_handles[i] = std::exchange(reclamation_handles_[i], nullptr);
    }
  }
}

// Reserve memory from the allocator
size_t GrpcMemoryAllocatorImpl::Reserve(MemoryRequest request) {
  CHECK(request.min() <= request.max());
  CHECK(request.max() <= MemoryRequest::max_allowed_size());
  size_t old_free = free_bytes_.load(std::memory_order_relaxed);

  while (true) {
    // Try to reserve memory
    auto reservation = TryReserve(request);
    if (reservation.has_value()) {
      size_t new_free = free_bytes_.load(std::memory_order_relaxed);
      // Notify quota if allocator state changed significantly
      memory_quota_->MaybeMoveAllocator(this, old_free, new_free);
      return *reservation;
    }

    // If reservation failed, replenish and try again
    Replenish();
  }
}

// Try to reserve memory without blocking
std::optional<size_t> GrpcMemoryAllocatorImpl::TryReserve(
    MemoryRequest request) {
  // Calculate scaled size based on memory pressure
  size_t scaled_size_over_min = request.max() - request.min();

  if (scaled_size_over_min != 0) {
    const auto pressure_info = memory_quota_->GetPressureInfo();
    double pressure = pressure_info.pressure_control_value;
    size_t max_recommended_allocation_size =
        pressure_info.max_recommended_allocation_size;

    // Reduce allocation size under high pressure
    if (pressure > 0.8) {
      scaled_size_over_min =
          std::min(scaled_size_over_min,
                   static_cast<size_t>((request.max() - request.min()) *
                                       (1.0 - pressure) / 0.2));
    }
    // Further limit allocation size based on recommendations
    if (max_recommended_allocation_size < request.min()) {
      scaled_size_over_min = 0;
    } else if (request.min() + scaled_size_over_min >
               max_recommended_allocation_size) {
      scaled_size_over_min = max_recommended_allocation_size - request.min();
    }
  }

  const size_t reserve = request.min() + scaled_size_over_min;

  // Try to reserve the calculated amount
  size_t available = free_bytes_.load(std::memory_order_acquire);
  while (true) {
    if (available < reserve) {
      return {};
    }

    if (free_bytes_.compare_exchange_weak(available, available - reserve,
                                          std::memory_order_acq_rel,
                                          std::memory_order_acquire)) {
      return reserve;
    }
  }
}

// Donate back unused memory to the quota
void GrpcMemoryAllocatorImpl::MaybeDonateBack() {
  size_t free = free_bytes_.load(std::memory_order_relaxed);
  while (free > 0) {
    size_t ret = 0;
    // Return half of free memory above threshold
    if (!IsUnconstrainedMaxQuotaBufferSizeEnabled() &&
        free > kMaxQuotaBufferSize / 2) {
      ret = std::max(ret, free - (kMaxQuotaBufferSize / 2));
    }
    ret = std::max(ret, free > 8192 ? free / 2 : free);
    const size_t new_free = free - ret;
    if (free_bytes_.compare_exchange_weak(free, new_free,
                                          std::memory_order_acq_rel,
                                          std::memory_order_acquire)) {
      GRPC_TRACE_LOG(resource_quota, INFO)
          << "[" << this << "] Early return " << ret << " bytes";
      CHECK(taken_bytes_.fetch_sub(ret, std::memory_order_relaxed) >= ret);
      memory_quota_->Return(ret);
      return;
    }
  }
}

// Replenish memory from the quota
void GrpcMemoryAllocatorImpl::Replenish() {
  // Calculate amount to take (1/3 of current taken bytes, clamped)
  auto amount = Clamp(taken_bytes_.load(std::memory_order_relaxed) / 3,
                      kMinReplenishBytes, kMaxReplenishBytes);

  // Take memory from quota
  memory_quota_->Take(this, amount);

  // Update counters
  taken_bytes_.fetch_add(amount, std::memory_order_relaxed);
  free_bytes_.fetch_add(amount, std::memory_order_acq_rel);
}

// Create a slice using this allocator
grpc_slice GrpcMemoryAllocatorImpl::MakeSlice(MemoryRequest request) {
  // Reserve memory including space for refcount
  auto size = Reserve(request.Increase(sizeof(SliceRefCount)));
  void* p = malloc(size);
  // Create refcount that will return memory to allocator
  new (p) SliceRefCount(shared_from_this(), size);
  grpc_slice slice;
  slice.refcount = static_cast<SliceRefCount*>(p);
  slice.data.refcounted.bytes =
      static_cast<uint8_t*>(p) + sizeof(SliceRefCount);
  slice.data.refcounted.length = size - sizeof(SliceRefCount);
  return slice;
}

// Promise that waits for a memory sweep to complete
class BasicMemoryQuota::WaitForSweepPromise {
 public:
  WaitForSweepPromise(std::shared_ptr<BasicMemoryQuota> memory_quota,
                      uint64_t token)
      : memory_quota_(std::move(memory_quota)), token_(token) {}

  Poll<Empty> operator()() {
    // Check if sweep with our token has completed
    if (memory_quota_->reclamation_counter_.load(std::memory_order_relaxed) !=
        token_) {
      return Empty{};
    } else {
      return Pending{};
    }
  }

 private:
  std::shared_ptr<BasicMemoryQuota> memory_quota_;
  uint64_t token_;
};

// Basic memory quota constructor
BasicMemoryQuota::BasicMemoryQuota(std::string name) : name_(std::move(name)) {}

// Start the memory quota reclamation system
void BasicMemoryQuota::Start() {
  auto self = shared_from_this();

  // Register with global tracker
  MemoryQuotaTracker::Get().Add(self);

  // Create reclamation loop that:
  // 1. Waits until memory is low
  // 2. Selects a reclaimer to run
  // 3. Runs the reclaimer
  // 4. Waits for reclamation to complete
  auto reclamation_loop = Loop([self]() {
    return Seq(
        [self]() -> Poll<int> {
          if (self->free_bytes_.load(std::memory_order_acquire) > 0) {
            return Pending{};
          }
          return 0;
        },
        [self]() {
          // Annotate reclaimers with their priority
          auto annotate = [](const char* name) {
            return [name](RefCountedPtr<ReclaimerQueue::Handle> f) {
              return std::tuple(name, std::move(f));
            };
          };
          // Race between different priority reclaimers
          return Race(
              Map(self->reclaimers_[0].Next(), annotate("benign")),
              Map(self->reclaimers_[1].Next(), annotate("idle")),
              Map(self->reclaimers_[2].Next(), annotate("destructive")));
        },
        [self](std::tuple<const char*, RefCountedPtr<ReclaimerQueue::Handle>>
                   arg) {
          // Run the selected reclaimer
          auto reclaimer = std::move(std::get<1>(arg));
          if (GRPC_TRACE_FLAG_ENABLED(resource_quota)) {
            double free = std::max(intptr_t{0}, self->free_bytes_.load());
            size_t quota_size = self->quota_size_.load();
            LOG(INFO) << "RQ: " << self->name_ << " perform "
                      << std::get<0>(arg)
                      << " reclamation. Available free bytes: " << free
                      << ", total quota_size: " << quota_size;
          }

          // Generate sweep token and run reclaimer
          const uint64_t token = self->reclamation_counter_.fetch_add(
                                     1, std::memory_order_relaxed) +
                                 1;
          reclaimer->Run(ReclamationSweep(