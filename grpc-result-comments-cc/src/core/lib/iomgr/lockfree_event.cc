Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/lib/iomgr/lockfree_event.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/crash.h"

namespace grpc_core {

// Constructor initializes the event to a "not ready" state
LockfreeEvent::LockfreeEvent() { InitEvent(); }

// Initialize the event state to kClosureNotReady
// Uses a no-barrier atomic store for initialization
void LockfreeEvent::InitEvent() {
  gpr_atm_no_barrier_store(&state_, kClosureNotReady);
}

// Clean up the event state, handling any pending shutdown status
// This is a thread-safe operation that ensures proper cleanup of resources
void LockfreeEvent::DestroyEvent() {
  gpr_atm curr;
  do {
    // Load current state without memory barriers
    curr = gpr_atm_no_barrier_load(&state_);
    if (curr & kShutdownBit) {
      // If shutdown bit is set, free the associated status
      internal::StatusFreeHeapPtr(curr & ~kShutdownBit);
    } else {
      // Otherwise verify state is either not ready or ready
      CHECK(curr == kClosureNotReady || curr == kClosureReady);
    }
    // Attempt to set shutdown bit using compare-and-swap
  } while (!gpr_atm_no_barrier_cas(&state_, curr,
                                   kShutdownBit ));
}

// Register a closure to be notified when the event becomes ready
// This is a thread-safe operation that handles various event states
void LockfreeEvent::NotifyOn(grpc_closure* closure) {
  while (true) {
    // Load current state with acquire semantics
    gpr_atm curr = gpr_atm_acq_load(&state_);
    GRPC_TRACE_VLOG(polling, 2) << "LockfreeEvent::NotifyOn: " << this
                                << " curr=" << curr << " closure=" << closure;
    switch (curr) {
      case kClosureNotReady: {
        // Try to set the closure as pending notification
        if (gpr_atm_rel_cas(&state_, kClosureNotReady,
                            reinterpret_cast<gpr_atm>(closure))) {
          return;  // Successfully registered the closure
        }
        break;  // CAS failed, retry
      }

      case kClosureReady: {
        // Event is already ready - execute closure immediately
        if (gpr_atm_no_barrier_cas(&state_, kClosureReady, kClosureNotReady)) {
          ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
          return;
        }
        break;  // CAS failed, retry
      }

      default: {
        if ((curr & kShutdownBit) > 0) {
          // Event is shutdown - execute closure with error
          grpc_error_handle shutdown_err =
              internal::StatusGetFromHeapPtr(curr & ~kShutdownBit);
          ExecCtx::Run(
              DEBUG_LOCATION, closure,
              GRPC_ERROR_CREATE_REFERENCING("FD Shutdown", &shutdown_err, 1));
          return;
        }
        // Invalid state - crash with error message
        Crash(
            "LockfreeEvent::NotifyOn: notify_on called with a previous "
            "callback still pending");
      }
    }
  }

  GPR_UNREACHABLE_CODE(return);
}

// Set the event to shutdown state with the given error
// Returns true if shutdown was successfully set, false if already shutdown
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
        // Try to transition to shutdown state
        if (gpr_atm_full_cas(&state_, curr, new_state)) {
          return true;
        }
        break;

      default: {
        if ((curr & kShutdownBit) > 0) {
          // Already shutdown - free the new status and return false
          internal::StatusFreeHeapPtr(status_ptr);
          return false;
        }

        // There's a pending closure - transition to shutdown and execute it
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

// Set the event to ready state and execute any pending closure
// This is a thread-safe operation that handles various event states
void LockfreeEvent::SetReady() {
  while (true) {
    gpr_atm curr = gpr_atm_no_barrier_load(&state_);

    GRPC_TRACE_VLOG(polling, 2)
        << "LockfreeEvent::SetReady: " << &state_ << " curr=" << curr;

    switch (curr) {
      case kClosureReady: {
        // Already ready - nothing to do
        return;
      }

      case kClosureNotReady: {
        // Transition to ready state
        if (gpr_atm_no_barrier_cas(&state_, kClosureNotReady, kClosureReady)) {
          return;
        }
        break;  // CAS failed, retry
      }

      default: {
        if ((curr & kShutdownBit) > 0) {
          // Shutdown - nothing to do
          return;
        }
        else if (gpr_atm_full_cas(&state_, curr, kClosureNotReady)) {
          // There's a pending closure - execute it
          ExecCtx::Run(DEBUG_LOCATION, reinterpret_cast<grpc_closure*>(curr),
                       absl::OkStatus());
          return;
        }

        return;
      }
    }
  }
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each method
2. The thread-safety mechanisms used (atomic operations, memory barriers)
3. The state transitions and their implications
4. Error handling and edge cases
5. The flow of execution in each method

The comments are designed to help future developers understand:
- The lock-free synchronization patterns used
- The state machine of the event
- Memory management considerations
- Error handling paths
- The purpose of each atomic operation