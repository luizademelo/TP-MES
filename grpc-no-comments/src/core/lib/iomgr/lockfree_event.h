
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_LOCKFREE_EVENT_H
#define GRPC_SRC_CORE_LIB_IOMGR_LOCKFREE_EVENT_H

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/closure.h"

namespace grpc_core {

class LockfreeEvent {
 public:
  LockfreeEvent();

  LockfreeEvent(const LockfreeEvent&) = delete;
  LockfreeEvent& operator=(const LockfreeEvent&) = delete;

  void InitEvent();
  void DestroyEvent();

  bool IsShutdown() const {
    return (gpr_atm_no_barrier_load(&state_) & kShutdownBit) != 0;
  }

  void NotifyOn(grpc_closure* closure);

  bool SetShutdown(grpc_error_handle shutdown_error);

  void SetReady();

 private:
  enum State { kClosureNotReady = 0, kClosureReady = 2, kShutdownBit = 1 };

  gpr_atm state_;
};

}

#endif
