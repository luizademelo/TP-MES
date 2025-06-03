Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/lib/transport/bdp_estimator.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stdlib.h>

#include <algorithm>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc_core {

// Constructor for BdpEstimator class
// Initializes bandwidth-delay product (BDP) estimator with default values:
// - accumulator_: tracks bytes accumulated during measurement (starts at 0)
// - estimate_: initial BDP estimate (64KB)
// - ping_start_time_: initialized to 0 (monotonic clock)
// - inter_ping_delay_: initial delay between pings (100ms)
// - stable_estimate_count_: counter for stable estimates (starts at 0)
// - ping_state_: initial state is UNSCHEDULED
// - bw_est_: initial bandwidth estimate (0)
// - name_: identifier for this estimator
BdpEstimator::BdpEstimator(absl::string_view name)
    : accumulator_(0),
      estimate_(65536),
      ping_start_time_(gpr_time_0(GPR_CLOCK_MONOTONIC)),
      inter_ping_delay_(Duration::Milliseconds(100)),
      stable_estimate_count_(0),
      ping_state_(PingState::UNSCHEDULED),
      bw_est_(0),
      name_(name) {}

// Completes a ping operation and calculates new bandwidth and BDP estimates
// Returns: Timestamp for when the next ping should be scheduled
Timestamp BdpEstimator::CompletePing() {
  // Calculate time elapsed since ping started
  gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
  gpr_timespec dt_ts = gpr_time_sub(now, ping_start_time_);
  double dt = static_cast<double>(dt_ts.tv_sec) +
              (1e-9 * static_cast<double>(dt_ts.tv_nsec));
  
  // Calculate current bandwidth (bytes/sec)
  double bw = dt > 0 ? (static_cast<double>(accumulator_) / dt) : 0;
  
  // Store initial inter-ping delay before potential modification
  Duration start_inter_ping_delay = inter_ping_delay_;
  
  // Log current estimation state
  GRPC_TRACE_LOG(bdp_estimator, INFO)
      << "bdp[" << name_ << "]:complete acc=" << accumulator_
      << " est=" << estimate_ << " dt=" << dt << " bw=" << bw / 125000.0
      << "Mbs bw_est=" << bw_est_ / 125000.0 << "Mbs";
  
  // Verify we're in the correct state
  CHECK(ping_state_ == PingState::STARTED);
  
  // If we've accumulated more than 2/3 of current estimate and bandwidth is increasing
  if (accumulator_ > 2 * estimate_ / 3 && bw > bw_est_) {
    // Increase estimate to max between current accumulation or double previous estimate
    estimate_ = std::max(accumulator_, estimate_ * 2);
    bw_est_ = bw;
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]: estimate increased to " << estimate_;
    // Halve ping interval to get measurements more frequently
    inter_ping_delay_ /= 2;
  } 
  // If network conditions appear stable (ping interval < 10s)
  else if (inter_ping_delay_ < Duration::Seconds(10)) {
    stable_estimate_count_++;
    // After 2 stable measurements, increase ping interval with some randomness
    if (stable_estimate_count_ >= 2) {
      inter_ping_delay_ += Duration::Milliseconds(
          100 + static_cast<int>(rand() * 100.0 / RAND_MAX));
    }
  }
  
  // If ping interval changed, reset stability counter and log the change
  if (start_inter_ping_delay != inter_ping_delay_) {
    stable_estimate_count_ = 0;
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]:update_inter_time to "
        << inter_ping_delay_.millis() << "ms";
  }
  
  // Reset state and accumulator for next measurement
  ping_state_ = PingState::UNSCHEDULED;
  accumulator_ = 0;
  
  // Return when next ping should be scheduled
  return Timestamp::Now() + inter_ping_delay_;
}

}  // namespace grpc_core
```

The comments explain:
1. The class constructor and its initialization parameters
2. The CompletePing() method's purpose and return value
3. The bandwidth and delay calculations
4. The logic for adjusting the BDP estimate and ping intervals
5. The stability detection mechanism
6. State management and reset operations
7. The logging and debugging information

The comments are designed to help future developers understand:
- The algorithm's adaptive behavior
- The conditions that trigger estimate changes
- The purpose of each member variable
- The control flow of the estimation process