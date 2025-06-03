Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/write_size_policy.h"

#include <grpc/support/port_platform.h>

#include <algorithm>

#include "absl/log/check.h"

namespace grpc_core {

// Returns the current target write size
size_t Chttp2WriteSizePolicy::WriteTargetSize() { return current_target_; }

// Begins tracking a write operation and potentially adjusts state
// Parameters:
//   size - the size of the write being initiated
void Chttp2WriteSizePolicy::BeginWrite(size_t size) {
  // Verify no experiment is currently running
  CHECK(experiment_start_time_ == Timestamp::InfFuture());
  
  // If the write size is less than 70% of current target,
  // reset state if negative and skip experiment
  if (size < current_target_ * 7 / 10) {
    if (state_ < 0) state_ = 0;
    return;
  }
  
  // Start tracking experiment time for this write
  experiment_start_time_ = Timestamp::Now();
}

// Completes tracking of a write operation and adjusts target size based on performance
// Parameters:
//   success - whether the write operation completed successfully
void Chttp2WriteSizePolicy::EndWrite(bool success) {
  // If no experiment was running, return immediately
  if (experiment_start_time_ == Timestamp::InfFuture()) return;
  
  // Calculate elapsed time and reset experiment timer
  const auto elapsed = Timestamp::Now() - experiment_start_time_;
  experiment_start_time_ = Timestamp::InfFuture();
  
  // If write failed, don't adjust anything
  if (!success) return;
  
  // Adjust target size based on write performance:
  if (elapsed < FastWrite()) {
    // Write was faster than threshold - decrease state
    --state_;
    if (state_ == -2) {
      // After two consecutive fast writes, increase target size (capped at MaxTarget)
      state_ = 0;
      current_target_ = std::min(current_target_ * 3 / 2, MaxTarget());
    }
  } else if (elapsed > SlowWrite()) {
    // Write was slower than threshold - increase state
    ++state_;
    if (state_ == 2) {
      // After two consecutive slow writes, decrease target size (floored at MinTarget)
      state_ = 0;
      current_target_ = std::max(current_target_ / 3, MinTarget());
    }
  } else {
    // Write was within normal performance range - reset state
    state_ = 0;
  }
}

}  // namespace grpc_core
```

The comments explain:
1. The overall purpose of each method
2. The state machine logic for adjusting write sizes
3. The conditions for increasing/decreasing the target size
4. The bounds checking (min/max targets)
5. The timing-based performance evaluation
6. The state transition logic

The comments maintain a balance between explaining the high-level algorithm and the specific implementation details while avoiding redundancy with the code itself.