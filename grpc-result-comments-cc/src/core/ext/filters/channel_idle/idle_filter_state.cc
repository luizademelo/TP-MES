Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/ext/filters/channel_idle/idle_filter_state.h"

#include <assert.h>
#include <grpc/support/port_platform.h>

namespace grpc_core {

// Constructor for IdleFilterState
// @param start_timer: Boolean indicating whether to start the timer immediately
IdleFilterState::IdleFilterState(bool start_timer)
    : state_(start_timer ? kTimerStarted : 0) {}

// Increases the call count and marks that calls have started since last timer check
// Uses atomic operations to ensure thread safety
void IdleFilterState::IncreaseCallCount() {
  uintptr_t state = state_.load(std::memory_order_relaxed);
  uintptr_t new_state;
  do {
    // Preserve existing state flags
    new_state = state;
    // Mark that calls have started since last timer check
    new_state |= kCallsStartedSinceLastTimerCheck;
    // Increment the call count
    new_state += kCallIncrement;
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_relaxed));
}

// Decreases the call count and potentially starts idle timer if no calls are in progress
// @return: Boolean indicating whether timer should be started
// Uses atomic operations to ensure thread safety
bool IdleFilterState::DecreaseCallCount() {
  uintptr_t state = state_.load(std::memory_order_relaxed);
  uintptr_t new_state;
  bool start_timer;
  do {
    start_timer = false;
    new_state = state;

    // Ensure we don't underflow the call count
    assert(new_state >= kCallIncrement);
    // Decrement the call count
    new_state -= kCallIncrement;

    // Check if no calls are in progress and timer isn't already started
    if ((new_state >> kCallsInProgressShift) == 0 &&
        (new_state & kTimerStarted) == 0) {
      // Conditions met to start idle timer
      start_timer = true;
      new_state |= kTimerStarted;
      new_state &= ~kCallsInProgressShift;
    }
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_relaxed));
  return start_timer;
}

// Checks timer state and determines if timer should be (re)started
// @return: Boolean indicating whether timer should be started
// Uses atomic operations to ensure thread safety
bool IdleFilterState::CheckTimer() {
  uintptr_t state = state_.load(std::memory_order_relaxed);
  uintptr_t new_state;
  bool start_timer;
  do {
    // If there are calls in progress, timer should continue running
    if ((state >> kCallsInProgressShift) != 0) {
      return true;
    }
    new_state = state;
    bool is_active = false;
    // Check if calls have started since last timer check
    if (new_state & kCallsStartedSinceLastTimerCheck) {
      is_active = true;
      // Clear the flag as we're now checking it
      new_state &= ~kCallsStartedSinceLastTimerCheck;
    }
    if (is_active) {
      // If there was activity, keep timer running
      start_timer = true;
    } else {
      // No activity, stop the timer
      start_timer = false;
      new_state &= ~kTimerStarted;
    }
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_relaxed));
  return start_timer;
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each method
2. The atomic operations and thread safety considerations
3. The state transitions and flag manipulations
4. The conditions for starting/stopping the idle timer
5. The meaning of return values
6. Important assertions and invariants

The comments are placed to provide context without being overly verbose, helping future maintainers understand the code's behavior and threading model.