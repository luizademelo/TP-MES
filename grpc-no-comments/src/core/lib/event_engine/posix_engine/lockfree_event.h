// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_LOCKFREE_EVENT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_LOCKFREE_EVENT_H
#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstdint>

#include "absl/status/status.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"

namespace grpc_event_engine::experimental {

class Scheduler;

class LockfreeEvent {
 public:
  explicit LockfreeEvent(Scheduler* scheduler) : scheduler_(scheduler) {}

  LockfreeEvent(const LockfreeEvent&) = delete;
  LockfreeEvent& operator=(const LockfreeEvent&) = delete;

  void InitEvent();
  void DestroyEvent();

  bool IsShutdown() const {
    return (state_.load(std::memory_order_relaxed) & kShutdownBit) != 0;
  }

  void NotifyOn(PosixEngineClosure* closure);

  bool SetShutdown(absl::Status shutdown_error);

  void SetReady();

 private:
  enum State { kClosureNotReady = 0, kClosureReady = 2, kShutdownBit = 1 };

  std::atomic<intptr_t> state_;
  Scheduler* scheduler_;
};

}

#endif
