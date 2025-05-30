// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/lockfree_event.h"

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstdint>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/util/crash.h"
#include "src/core/util/status_helper.h"

namespace grpc_event_engine::experimental {

void LockfreeEvent::InitEvent() {

  state_.store(kClosureNotReady, std::memory_order_relaxed);
}

void LockfreeEvent::DestroyEvent() {
  intptr_t curr;
  do {
    curr = state_.load(std::memory_order_relaxed);
    if (curr & kShutdownBit) {
      grpc_core::internal::StatusFreeHeapPtr(curr & ~kShutdownBit);
    } else {
      CHECK(curr == kClosureNotReady || curr == kClosureReady);
    }

  } while (!state_.compare_exchange_strong(curr, kShutdownBit,
                                           std::memory_order_acq_rel,
                                           std::memory_order_acquire));
}

void LockfreeEvent::NotifyOn(PosixEngineClosure* closure) {

  intptr_t curr = state_.load(std::memory_order_acquire);
  while (true) {
    switch (curr) {
      case kClosureNotReady: {

        if (state_.compare_exchange_strong(
                curr, reinterpret_cast<intptr_t>(closure),
                std::memory_order_acq_rel, std::memory_order_acquire)) {
          return;
        }

        break;
      }

      case kClosureReady: {

        if (state_.compare_exchange_strong(curr, kClosureNotReady,
                                           std::memory_order_acq_rel,
                                           std::memory_order_acquire)) {
          scheduler_->Run(closure);
          return;
        }
        break;
      }

      default: {

        if ((curr & kShutdownBit) > 0) {
          absl::Status shutdown_err =
              grpc_core::internal::StatusGetFromHeapPtr(curr & ~kShutdownBit);
          closure->SetStatus(shutdown_err);
          scheduler_->Run(closure);
          return;
        }

        grpc_core::Crash(
            "LockfreeEvent::NotifyOn: notify_on called with a previous "
            "callback still pending");
      }
    }
  }

  GPR_UNREACHABLE_CODE(return);
}

bool LockfreeEvent::SetShutdown(absl::Status shutdown_error) {
  intptr_t status_ptr = grpc_core::internal::StatusAllocHeapPtr(shutdown_error);
  gpr_atm new_state = status_ptr | kShutdownBit;

  intptr_t curr = state_.load(std::memory_order_acquire);

  while (true) {
    switch (curr) {
      case kClosureReady:
      case kClosureNotReady:

        if (state_.compare_exchange_strong(curr, new_state,
                                           std::memory_order_acq_rel,
                                           std::memory_order_acquire)) {
          return true;
        }
        break;

      default: {

        if ((curr & kShutdownBit) > 0) {
          grpc_core::internal::StatusFreeHeapPtr(status_ptr);
          return false;
        }

        if (state_.compare_exchange_strong(curr, new_state,
                                           std::memory_order_acq_rel,
                                           std::memory_order_acquire)) {
          auto closure = reinterpret_cast<PosixEngineClosure*>(curr);
          closure->SetStatus(shutdown_error);
          scheduler_->Run(closure);
          return true;
        }

        break;
      }
    }
  }
  GPR_UNREACHABLE_CODE(return false);
}

void LockfreeEvent::SetReady() {

  intptr_t curr = state_.load(std::memory_order_acquire);
  while (true) {
    switch (curr) {
      case kClosureReady: {

        return;
      }

      case kClosureNotReady: {
        if (state_.compare_exchange_strong(curr, kClosureReady,
                                           std::memory_order_acq_rel,
                                           std::memory_order_acquire)) {
          return;
        }
        break;
      }

      default: {

        if ((curr & kShutdownBit) > 0) {

          return;
        } else if (state_.compare_exchange_strong(curr, kClosureNotReady,
                                                  std::memory_order_acq_rel,
                                                  std::memory_order_acquire)) {

          auto closure = reinterpret_cast<PosixEngineClosure*>(curr);
          closure->SetStatus(absl::OkStatus());
          scheduler_->Run(closure);
          return;
        }

        return;
      }
    }
  }
}

}
