// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_CHANNEL_IDLE_IDLE_FILTER_STATE_H
#define GRPC_SRC_CORE_EXT_FILTERS_CHANNEL_IDLE_IDLE_FILTER_STATE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <atomic>

namespace grpc_core {

class IdleFilterState {
 public:
  explicit IdleFilterState(bool start_timer);
  ~IdleFilterState() = default;

  IdleFilterState(const IdleFilterState&) = delete;
  IdleFilterState& operator=(const IdleFilterState&) = delete;

  void IncreaseCallCount();

  GRPC_MUST_USE_RESULT bool DecreaseCallCount();

  GRPC_MUST_USE_RESULT bool CheckTimer();

 private:

  static constexpr uintptr_t kTimerStarted = 1;

  static constexpr uintptr_t kCallsStartedSinceLastTimerCheck = 2;

  static constexpr uintptr_t kCallsInProgressShift = 2;

  static constexpr uintptr_t kCallIncrement = uintptr_t{1}
                                              << kCallsInProgressShift;
  std::atomic<uintptr_t> state_;
};

}

#endif
