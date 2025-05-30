
// Copyright 2015 gRPC authors.

#include "src/core/lib/event_engine/posix_engine/timer_heap.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <algorithm>

#include "src/core/lib/event_engine/posix_engine/timer.h"

namespace grpc_event_engine::experimental {

void TimerHeap::AdjustUpwards(size_t i, Timer* t) {
  while (i > 0) {
    size_t parent = (i - 1) / 2;
    if (timers_[parent]->deadline <= t->deadline) break;
    timers_[i] = timers_[parent];
    timers_[i]->heap_index = i;
    i = parent;
  }
  timers_[i] = t;
  t->heap_index = i;
}

void TimerHeap::AdjustDownwards(size_t i, Timer* t) {
  for (;;) {
    size_t left_child = 1 + (2 * i);
    if (left_child >= timers_.size()) break;
    size_t right_child = left_child + 1;
    size_t next_i =
        right_child < timers_.size() &&
                timers_[left_child]->deadline > timers_[right_child]->deadline
            ? right_child
            : left_child;
    if (t->deadline <= timers_[next_i]->deadline) break;
    timers_[i] = timers_[next_i];
    timers_[i]->heap_index = i;
    i = next_i;
  }
  timers_[i] = t;
  t->heap_index = i;
}

void TimerHeap::NoteChangedPriority(Timer* timer) {
  uint32_t i = timer->heap_index;
  uint32_t parent = static_cast<uint32_t>((static_cast<int>(i) - 1) / 2);
  if (timers_[parent]->deadline > timer->deadline) {
    AdjustUpwards(i, timer);
  } else {
    AdjustDownwards(i, timer);
  }
}

bool TimerHeap::Add(Timer* timer) {
  timer->heap_index = timers_.size();
  timers_.push_back(timer);
  AdjustUpwards(timer->heap_index, timer);
  return timer->heap_index == 0;
}

void TimerHeap::Remove(Timer* timer) {
  uint32_t i = timer->heap_index;
  if (i == timers_.size() - 1) {
    timers_.pop_back();
    return;
  }
  timers_[i] = timers_[timers_.size() - 1];
  timers_[i]->heap_index = i;
  timers_.pop_back();
  NoteChangedPriority(timers_[i]);
}

bool TimerHeap::is_empty() { return timers_.empty(); }

Timer* TimerHeap::Top() { return timers_[0]; }

void TimerHeap::Pop() { Remove(Top()); }

}
