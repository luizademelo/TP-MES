// Copyright 2021 gRPC authors.

#include "src/core/ext/filters/channel_idle/idle_filter_state.h"

#include <assert.h>
#include <grpc/support/port_platform.h>

namespace grpc_core {

IdleFilterState::IdleFilterState(bool start_timer)
    : state_(start_timer ? kTimerStarted : 0) {}

void IdleFilterState::IncreaseCallCount() {
  uintptr_t state = state_.load(std::memory_order_relaxed);
  uintptr_t new_state;
  do {

    new_state = state;
    new_state |= kCallsStartedSinceLastTimerCheck;
    new_state += kCallIncrement;
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_relaxed));
}

bool IdleFilterState::DecreaseCallCount() {
  uintptr_t state = state_.load(std::memory_order_relaxed);
  uintptr_t new_state;
  bool start_timer;
  do {
    start_timer = false;
    new_state = state;

    assert(new_state >= kCallIncrement);
    new_state -= kCallIncrement;

    if ((new_state >> kCallsInProgressShift) == 0 &&
        (new_state & kTimerStarted) == 0) {

      start_timer = true;
      new_state |= kTimerStarted;
      new_state &= ~kCallsInProgressShift;
    }
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_relaxed));
  return start_timer;
}

bool IdleFilterState::CheckTimer() {
  uintptr_t state = state_.load(std::memory_order_relaxed);
  uintptr_t new_state;
  bool start_timer;
  do {
    if ((state >> kCallsInProgressShift) != 0) {

      return true;
    }
    new_state = state;
    bool is_active = false;
    if (new_state & kCallsStartedSinceLastTimerCheck) {

      is_active = true;
      new_state &= ~kCallsStartedSinceLastTimerCheck;
    }
    if (is_active) {

      start_timer = true;
    } else {

      start_timer = false;
      new_state &= ~kTimerStarted;
    }
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_relaxed));
  return start_timer;
}

}
