
// Copyright 2015 gRPC authors.

#include "src/core/lib/event_engine/posix_engine/timer.h"

#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <atomic>
#include <limits>
#include <utility>

#include "src/core/lib/event_engine/posix_engine/timer_heap.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_event_engine::experimental {

static const size_t kInvalidHeapIndex = std::numeric_limits<size_t>::max();
static const double kAddDeadlineScale = 0.33;
static const double kMinQueueWindowDuration = 0.01;
static const double kMaxQueueWindowDuration = 1.0;

grpc_core::Timestamp TimerList::Shard::ComputeMinDeadline() {
  return heap.is_empty()
             ? queue_deadline_cap + grpc_core::Duration::Epsilon()
             : grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
                   heap.Top()->deadline);
}

TimerList::Shard::Shard() : stats(1.0 / kAddDeadlineScale, 0.1, 0.5) {}

TimerList::TimerList(TimerListHost* host)
    : host_(host),
      num_shards_(grpc_core::Clamp(2 * gpr_cpu_num_cores(), 1u, 32u)),
      min_timer_(host_->Now().milliseconds_after_process_epoch()),
      shards_(new Shard[num_shards_]),
      shard_queue_(new Shard*[num_shards_]) {
  for (size_t i = 0; i < num_shards_; i++) {
    Shard& shard = shards_[i];
    shard.queue_deadline_cap =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            min_timer_.load(std::memory_order_relaxed));
    shard.shard_queue_index = i;
    shard.list.next = shard.list.prev = &shard.list;
    shard.min_deadline = shard.ComputeMinDeadline();
    shard_queue_[i] = &shard;
  }
}

namespace {

void ListJoin(Timer* head, Timer* timer) {
  timer->next = head;
  timer->prev = head->prev;
  timer->next->prev = timer->prev->next = timer;
}

void ListRemove(Timer* timer) {
  timer->next->prev = timer->prev;
  timer->prev->next = timer->next;
}
}

void TimerList::SwapAdjacentShardsInQueue(uint32_t first_shard_queue_index) {
  Shard* temp;
  temp = shard_queue_[first_shard_queue_index];
  shard_queue_[first_shard_queue_index] =
      shard_queue_[first_shard_queue_index + 1];
  shard_queue_[first_shard_queue_index + 1] = temp;
  shard_queue_[first_shard_queue_index]->shard_queue_index =
      first_shard_queue_index;
  shard_queue_[first_shard_queue_index + 1]->shard_queue_index =
      first_shard_queue_index + 1;
}

void TimerList::NoteDeadlineChange(Shard* shard) {
  while (shard->shard_queue_index > 0 &&
         shard->min_deadline <
             shard_queue_[shard->shard_queue_index - 1]->min_deadline) {
    SwapAdjacentShardsInQueue(shard->shard_queue_index - 1);
  }
  while (shard->shard_queue_index < num_shards_ - 1 &&
         shard->min_deadline >
             shard_queue_[shard->shard_queue_index + 1]->min_deadline) {
    SwapAdjacentShardsInQueue(shard->shard_queue_index);
  }
}

void TimerList::TimerInit(Timer* timer, grpc_core::Timestamp deadline,
                          experimental::EventEngine::Closure* closure) {
  bool is_first_timer = false;
  Shard* shard = &shards_[grpc_core::HashPointer(timer, num_shards_)];
  timer->closure = closure;
  timer->deadline = deadline.milliseconds_after_process_epoch();

#ifndef NDEBUG
  timer->hash_table_next = nullptr;
#endif

  {
    grpc_core::MutexLock lock(&shard->mu);
    timer->pending = true;
    grpc_core::Timestamp now = host_->Now();
    if (deadline <= now) {
      deadline = now;
    }

    shard->stats.AddSample((deadline - now).millis() / 1000.0);

    if (deadline < shard->queue_deadline_cap) {
      is_first_timer = shard->heap.Add(timer);
    } else {
      timer->heap_index = kInvalidHeapIndex;
      ListJoin(&shard->list, timer);
    }
  }

  if (is_first_timer) {
    grpc_core::MutexLock lock(&mu_);
    if (deadline < shard->min_deadline) {
      grpc_core::Timestamp old_min_deadline = shard_queue_[0]->min_deadline;
      shard->min_deadline = deadline;
      NoteDeadlineChange(shard);
      if (shard->shard_queue_index == 0 && deadline < old_min_deadline) {
        min_timer_.store(deadline.milliseconds_after_process_epoch(),
                         std::memory_order_relaxed);
        host_->Kick();
      }
    }
  }
}

bool TimerList::TimerCancel(Timer* timer) {
  Shard* shard = &shards_[grpc_core::HashPointer(timer, num_shards_)];
  grpc_core::MutexLock lock(&shard->mu);

  if (timer->pending) {
    timer->pending = false;
    if (timer->heap_index == kInvalidHeapIndex) {
      ListRemove(timer);
    } else {
      shard->heap.Remove(timer);
    }
    return true;
  }

  return false;
}

bool TimerList::Shard::RefillHeap(grpc_core::Timestamp now) {

  double computed_deadline_delta = stats.UpdateAverage() * kAddDeadlineScale;
  double deadline_delta =
      grpc_core::Clamp(computed_deadline_delta, kMinQueueWindowDuration,
                       kMaxQueueWindowDuration);
  Timer *timer, *next;

  queue_deadline_cap = std::max(now, queue_deadline_cap) +
                       grpc_core::Duration::FromSecondsAsDouble(deadline_delta);

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
  return !heap.is_empty();
}

Timer* TimerList::Shard::PopOne(grpc_core::Timestamp now) {
  Timer* timer;
  for (;;) {
    if (heap.is_empty()) {
      if (now < queue_deadline_cap) return nullptr;
      if (!RefillHeap(now)) return nullptr;
    }
    timer = heap.Top();
    auto timer_deadline =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            timer->deadline);
    if (timer_deadline > now) return nullptr;
    timer->pending = false;
    heap.Pop();
    return timer;
  }
}

void TimerList::Shard::PopTimers(
    grpc_core::Timestamp now, grpc_core::Timestamp* new_min_deadline,
    std::vector<experimental::EventEngine::Closure*>* out) {
  grpc_core::MutexLock lock(&mu);
  while (Timer* timer = PopOne(now)) {
    out->push_back(timer->closure);
  }
  *new_min_deadline = ComputeMinDeadline();
}

std::vector<experimental::EventEngine::Closure*> TimerList::FindExpiredTimers(
    grpc_core::Timestamp now, grpc_core::Timestamp* next) {
  grpc_core::Timestamp min_timer =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
          min_timer_.load(std::memory_order_relaxed));

  std::vector<experimental::EventEngine::Closure*> done;
  if (now < min_timer) {
    if (next != nullptr) *next = std::min(*next, min_timer);
    return done;
  }

  grpc_core::MutexLock lock(&mu_);

  while (shard_queue_[0]->min_deadline < now ||
         (now != grpc_core::Timestamp::InfFuture() &&
          shard_queue_[0]->min_deadline == now)) {
    grpc_core::Timestamp new_min_deadline;

    shard_queue_[0]->PopTimers(now, &new_min_deadline, &done);

    shard_queue_[0]->min_deadline = new_min_deadline;
    NoteDeadlineChange(shard_queue_[0]);
  }

  if (next) {
    *next = std::min(*next, shard_queue_[0]->min_deadline);
  }

  min_timer_.store(
      shard_queue_[0]->min_deadline.milliseconds_after_process_epoch(),
      std::memory_order_relaxed);

  return done;
}

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
    return std::vector<experimental::EventEngine::Closure*>();
  }

  if (!checker_mu_.TryLock()) return std::nullopt;
  std::vector<experimental::EventEngine::Closure*> run =
      FindExpiredTimers(now, next);
  checker_mu_.Unlock();

  return std::move(run);
}

}
