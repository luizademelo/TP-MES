Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header includes for timer functionality in gRPC's event engine
#include "src/core/lib/event_engine/posix_engine/timer.h"

// System and gRPC core includes
#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

// Standard library includes
#include <algorithm>
#include <atomic>
#include <limits>
#include <utility>

// Internal gRPC includes
#include "src/core/lib/event_engine/posix_engine/timer_heap.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_event_engine::experimental {

// Constants for timer management
static const size_t kInvalidHeapIndex = std::numeric_limits<size_t>::max();
static const double kAddDeadlineScale = 0.33;  // Scale factor for deadline calculation
static const double kMinQueueWindowDuration = 0.01;  // Minimum queue window duration in seconds
static const double kMaxQueueWindowDuration = 1.0;   // Maximum queue window duration in seconds

// Computes the minimum deadline for a shard
grpc_core::Timestamp TimerList::Shard::ComputeMinDeadline() {
  return heap.is_empty()
             ? queue_deadline_cap + grpc_core::Duration::Epsilon()  // If heap is empty, use cap + epsilon
             : grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
                   heap.Top()->deadline);  // Otherwise use top timer's deadline
}

// Shard constructor initializes statistics with given parameters
TimerList::Shard::Shard() : stats(1.0 / kAddDeadlineScale, 0.1, 0.5) {}

// TimerList constructor initializes shards based on CPU cores
TimerList::TimerList(TimerListHost* host)
    : host_(host),
      num_shards_(grpc_core::Clamp(2 * gpr_cpu_num_cores(), 1u, 32u)),  // Number of shards is 2x CPU cores, clamped
      min_timer_(host_->Now().milliseconds_after_process_epoch()),  // Initialize minimum timer
      shards_(new Shard[num_shards_]),  // Allocate shards
      shard_queue_(new Shard*[num_shards_]) {  // Allocate shard queue
  // Initialize each shard
  for (size_t i = 0; i < num_shards_; i++) {
    Shard& shard = shards_[i];
    shard.queue_deadline_cap =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            min_timer_.load(std::memory_order_relaxed));
    shard.shard_queue_index = i;
    shard.list.next = shard.list.prev = &shard.list;  // Initialize circular list
    shard.min_deadline = shard.ComputeMinDeadline();
    shard_queue_[i] = &shard;
  }
}

namespace {

// Helper function to join a timer to a list
void ListJoin(Timer* head, Timer* timer) {
  timer->next = head;
  timer->prev = head->prev;
  timer->next->prev = timer->prev->next = timer;
}

// Helper function to remove a timer from a list
void ListRemove(Timer* timer) {
  timer->next->prev = timer->prev;
  timer->prev->next = timer->next;
}
}

// Swaps two adjacent shards in the queue
void TimerList::SwapAdjacentShardsInQueue(uint32_t first_shard_queue_index) {
  Shard* temp;
  temp = shard_queue_[first_shard_queue_index];
  shard_queue_[first_shard_queue_index] =
      shard_queue_[first_shard_queue_index + 1];
  shard_queue_[first_shard_queue_index + 1] = temp;
  // Update indices after swap
  shard_queue_[first_shard_queue_index]->shard_queue_index =
      first_shard_queue_index;
  shard_queue_[first_shard_queue_index + 1]->shard_queue_index =
      first_shard_queue_index + 1;
}

// Adjusts shard position in queue based on deadline changes
void TimerList::NoteDeadlineChange(Shard* shard) {
  // Move shard left in queue if its deadline is earlier than previous
  while (shard->shard_queue_index > 0 &&
         shard->min_deadline <
             shard_queue_[shard->shard_queue_index - 1]->min_deadline) {
    SwapAdjacentShardsInQueue(shard->shard_queue_index - 1);
  }
  // Move shard right in queue if its deadline is later than next
  while (shard->shard_queue_index < num_shards_ - 1 &&
         shard->min_deadline >
             shard_queue_[shard->shard_queue_index + 1]->min_deadline) {
    SwapAdjacentShardsInQueue(shard->shard_queue_index);
  }
}

// Initializes a timer with deadline and closure
void TimerList::TimerInit(Timer* timer, grpc_core::Timestamp deadline,
                          experimental::EventEngine::Closure* closure) {
  bool is_first_timer = false;
  // Select shard based on timer pointer hash
  Shard* shard = &shards_[grpc_core::HashPointer(timer, num_shards_)];
  timer->closure = closure;
  timer->deadline = deadline.milliseconds_after_process_epoch();

#ifndef NDEBUG
  timer->hash_table_next = nullptr;  // Debug-only field initialization
#endif

  {
    grpc_core::MutexLock lock(&shard->mu);
    timer->pending = true;
    grpc_core::Timestamp now = host_->Now();
    if (deadline <= now) {
      deadline = now;  // Ensure deadline is in the future
    }

    // Add statistics sample for this timer
    shard->stats.AddSample((deadline - now).millis() / 1000.0);

    // Add timer to heap or list based on deadline
    if (deadline < shard->queue_deadline_cap) {
      is_first_timer = shard->heap.Add(timer);
    } else {
      timer->heap_index = kInvalidHeapIndex;
      ListJoin(&shard->list, timer);
    }
  }

  // If this is the first timer in heap, update deadlines
  if (is_first_timer) {
    grpc_core::MutexLock lock(&mu_);
    if (deadline < shard->min_deadline) {
      grpc_core::Timestamp old_min_deadline = shard_queue_[0]->min_deadline;
      shard->min_deadline = deadline;
      NoteDeadlineChange(shard);
      // If this affects the global minimum timer, update and kick
      if (shard->shard_queue_index == 0 && deadline < old_min_deadline) {
        min_timer_.store(deadline.milliseconds_after_process_epoch(),
                         std::memory_order_relaxed);
        host_->Kick();
      }
    }
  }
}

// Cancels a pending timer
bool TimerList::TimerCancel(Timer* timer) {
  Shard* shard = &shards_[grpc_core::HashPointer(timer, num_shards_)];
  grpc_core::MutexLock lock(&shard->mu);

  if (timer->pending) {
    timer->pending = false;
    // Remove from either heap or list
    if (timer->heap_index == kInvalidHeapIndex) {
      ListRemove(timer);
    } else {
      shard->heap.Remove(timer);
    }
    return true;  // Timer was successfully canceled
  }

  return false;  // Timer wasn't pending
}

// Refills the heap from the list when needed
bool TimerList::Shard::RefillHeap(grpc_core::Timestamp now) {
  // Calculate new deadline cap based on statistics
  double computed_deadline_delta = stats.UpdateAverage() * kAddDeadlineScale;
  double deadline_delta =
      grpc_core::Clamp(computed_deadline_delta, kMinQueueWindowDuration,
                       kMaxQueueWindowDuration);
  Timer *timer, *next;

  // Update queue deadline cap
  queue_deadline_cap = std::max(now, queue_deadline_cap) +
                       grpc_core::Duration::FromSecondsAsDouble(deadline_delta);

  // Move timers from list to heap if their deadline is within new cap
  for (timer = list.next; timer != &list; timer = next) {
    next = timer->next;
    auto timer_deadline =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            timer->deadline);

    if (timer_deadline < queue_deadline_cap) {
      ListRemove(timer);
      heap.Add(timer);
    }
  }
  return !heap.is_empty();  // Return whether heap has timers
}

// Pops one expired timer from the heap
Timer* TimerList::Shard::PopOne(grpc_core::Timestamp now) {
  Timer* timer;
  for (;;) {
    if (heap.is_empty()) {
      if (now < queue_deadline_cap) return nullptr;  // No timers ready
      if (!RefillHeap(now)) return nullptr;  // Couldn't refill heap
    }
    timer = heap.Top();
    auto timer_deadline =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            timer->deadline);
    if (timer_deadline > now) return nullptr;  // Timer not yet expired
    timer->pending = false;
    heap.Pop();
    return timer;
  }
}

// Pops all expired timers from a shard
void TimerList::Shard::PopTimers(
    grpc_core::Timestamp now, grpc_core::Timestamp* new_min_deadline,
    std::vector<experimental::EventEngine::Closure*>* out) {
  grpc_core::MutexLock lock(&mu);
  while (Timer* timer = PopOne(now)) {
    out->push_back(timer->closure);  // Add expired timer's closure to output
  }
  *new_min_deadline = ComputeMinDeadline();  // Update new minimum deadline
}

// Finds all expired timers across all shards
std::vector<experimental::EventEngine::Closure*> TimerList::FindExpiredTimers(
    grpc_core::Timestamp now, grpc_core::Timestamp* next) {
  grpc_core::Timestamp min_timer =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
          min_timer_.load(std::memory_order_relaxed));

  std::vector<experimental::EventEngine::Closure*> done;
  if (now < min_timer) {
    if (next != nullptr) *next = std::min(*next, min_timer);
    return done;  // No timers expired yet
  }

  grpc_core::MutexLock lock(&mu_);

  // Process all shards with expired timers
  while (shard_queue_[0]->min_deadline < now ||
         (now != grpc_core::Timestamp::InfFuture() &&
          shard_queue_[0]->min_deadline == now)) {
    grpc_core::Timestamp new_min_deadline;

    shard_queue_[0]->PopTimers(now, &new_min_deadline, &done);

    shard_queue_[0]->min_deadline = new_min_deadline;
    NoteDeadlineChange(shard_queue_[0]);  // Reorder shard queue if needed
  }

  if (next) {
    *next = std::min(*next, shard_queue_[0]->min_deadline);  // Update next deadline
  }

  // Update global minimum timer
  min_timer_.store(
      shard_queue_[0]->min_deadline.milliseconds_after_process_epoch(),
      std::memory_order_relaxed);

  return done;
}

// Checks for expired timers and returns closures to run
std::optional<std::vector<experimental::EventEngine::Closure*>>
TimerList::TimerCheck(grpc_core::Timestamp* next) {
  grpc_core::Timestamp now = host_->Now();

  grpc_core::Timestamp min_timer =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
          min_timer_.load(std::memory_order_relaxed));

  if (now < min_timer) {
    if (next != nullptr) {
      *next = std::min(*next, min_timer);
    }
    return std::vector<experimental::EventEngine::Closure*>();  // No timers expired
  }

  // Try to acquire checker lock to avoid concurrent checks
  if (!checker_mu_.TryLock()) return std::nullopt;
  std::vector<experimental::EventEngine::Closure*> run =
      FindExpiredTimers(now, next);
  checker_mu_.Unlock();

  return std::move(run);
}

}  // namespace grpc_event_engine::experimental
```