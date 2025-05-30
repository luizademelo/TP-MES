
// Copyright 2017 gRPC authors.

#include "src/core/lib/iomgr/lockfree_event.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/crash.h"

namespace grpc_core {

LockfreeEvent::LockfreeEvent() { InitEvent(); }

void LockfreeEvent::InitEvent() {

  gpr_atm_no_barrier_store(&state_, kClosureNotReady);
}

void LockfreeEvent::DestroyEvent() {
  gpr_atm curr;
  do {
    curr = gpr_atm_no_barrier_load(&state_);
    if (curr & kShutdownBit) {
      internal::StatusFreeHeapPtr(curr & ~kShutdownBit);
    } else {
      CHECK(curr == kClosureNotReady || curr == kClosureReady);
    }

  } while (!gpr_atm_no_barrier_cas(&state_, curr,
                                   kShutdownBit ));
}

void LockfreeEvent::NotifyOn(grpc_closure* closure) {
  while (true) {

    gpr_atm curr = gpr_atm_acq_load(&state_);
    GRPC_TRACE_VLOG(polling, 2) << "LockfreeEvent::NotifyOn: " << this
                                << " curr=" << curr << " closure=" << closure;
    switch (curr) {
      case kClosureNotReady: {

        if (gpr_atm_rel_cas(&state_, kClosureNotReady,
                            reinterpret_cast<gpr_atm>(closure))) {
          return;
        }

        break;
      }

      case kClosureReady: {

        if (gpr_atm_no_barrier_cas(&state_, kClosureReady, kClosureNotReady)) {
          ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
          return;
        }

        break;
      }

      default: {

        if ((curr & kShutdownBit) > 0) {
          grpc_error_handle shutdown_err =
              internal::StatusGetFromHeapPtr(curr & ~kShutdownBit);
          ExecCtx::Run(
              DEBUG_LOCATION, closure,
              GRPC_ERROR_CREATE_REFERENCING("FD Shutdown", &shutdown_err, 1));
          return;
        }

        Crash(
            "LockfreeEvent::NotifyOn: notify_on called with a previous "
            "callback still pending");
      }
    }
  }

  GPR_UNREACHABLE_CODE(return);
}

bool LockfreeEvent::SetShutdown(grpc_error_handle shutdown_error) {
  intptr_t status_ptr = internal::StatusAllocHeapPtr(shutdown_error);
  gpr_atm new_state = status_ptr | kShutdownBit;

  while (true) {
    gpr_atm curr = gpr_atm_no_barrier_load(&state_);
    GRPC_TRACE_VLOG(polling, 2)
        << "LockfreeEvent::SetShutdown: " << &state_ << " curr=" << curr
        << " err=" << StatusToString(shutdown_error);
    switch (curr) {
      case kClosureReady:
      case kClosureNotReady:

        if (gpr_atm_full_cas(&state_, curr, new_state)) {
          return true;
        }
        break;

      default: {

        if ((curr & kShutdownBit) > 0) {
          internal::StatusFreeHeapPtr(status_ptr);
          return false;
        }

        if (gpr_atm_full_cas(&state_, curr, new_state)) {
          ExecCtx::Run(
              DEBUG_LOCATION, reinterpret_cast<grpc_closure*>(curr),
              GRPC_ERROR_CREATE_REFERENCING("FD Shutdown", &shutdown_error, 1));
          return true;
        }

        break;
      }
    }
  }

  GPR_UNREACHABLE_CODE(return false);
}

void LockfreeEvent::SetReady() {
  while (true) {
    gpr_atm curr = gpr_atm_no_barrier_load(&state_);

    GRPC_TRACE_VLOG(polling, 2)
        << "LockfreeEvent::SetReady: " << &state_ << " curr=" << curr;

    switch (curr) {
      case kClosureReady: {

        return;
      }

      case kClosureNotReady: {

        if (gpr_atm_no_barrier_cas(&state_, kClosureNotReady, kClosureReady)) {
          return;
        }
        break;
      }

      default: {

        if ((curr & kShutdownBit) > 0) {

          return;
        }

        else if (gpr_atm_full_cas(&state_, curr, kClosureNotReady)) {
          ExecCtx::Run(DEBUG_LOCATION, reinterpret_cast<grpc_closure*>(curr),
                       absl::OkStatus());
          return;
        }

        return;
      }
    }
  }
}

}
