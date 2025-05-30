
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TIMER_HEAP_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TIMER_HEAP_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <vector>

namespace grpc_event_engine::experimental {

struct Timer;

class TimerHeap {
 public:

  bool Add(Timer* timer);

  void Remove(Timer* timer);
  Timer* Top();
  void Pop();

  bool is_empty();

  const std::vector<Timer*>& TestOnlyGetTimers() const { return timers_; }

 private:
  void AdjustUpwards(size_t i, Timer* t);
  void AdjustDownwards(size_t i, Timer* t);
  void NoteChangedPriority(Timer* timer);

  std::vector<Timer*> timers_;
};

}

#endif
