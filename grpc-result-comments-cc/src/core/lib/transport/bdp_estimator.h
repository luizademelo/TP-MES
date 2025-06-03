Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_BDP_ESTIMATOR_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_BDP_ESTIMATOR_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <inttypes.h>

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/time.h"

namespace grpc_core {

// Bandwidth-Delay Product (BDP) Estimator class
// Used to estimate network bandwidth and round-trip time (RTT) characteristics
// by measuring data transfer during specially timed ping operations.
class BdpEstimator {
 public:
  // Constructor that takes a name for identification in logs
  explicit BdpEstimator(absl::string_view name);
  ~BdpEstimator() {}

  // Returns the current BDP estimate in bytes
  int64_t EstimateBdp() const { return estimate_; }
  
  // Returns the current bandwidth estimate in bytes per second
  double EstimateBandwidth() const { return bw_est_; }

  // Accumulates incoming bytes for BDP measurement
  void AddIncomingBytes(int64_t num_bytes) { accumulator_ += num_bytes; }

  // Prepares for a new ping measurement by resetting the accumulator
  // and marking the ping as scheduled
  void SchedulePing() {
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]:sched acc=" << accumulator_
        << " est=" << estimate_;
    CHECK(ping_state_ == PingState::UNSCHEDULED);
    ping_state_ = PingState::SCHEDULED;
    accumulator_ = 0;
  }

  // Starts a ping measurement by recording the start time
  void StartPing() {
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]:start acc=" << accumulator_
        << " est=" << estimate_;
    CHECK(ping_state_ == PingState::SCHEDULED);
    ping_state_ = PingState::STARTED;
    ping_start_time_ = gpr_now(GPR_CLOCK_MONOTONIC);
  }

  // Completes a ping measurement and updates BDP/bandwidth estimates
  // Returns the next time when a ping should be scheduled
  Timestamp CompletePing();

  // Returns the current accumulator value (bytes received since last reset)
  int64_t accumulator() const { return accumulator_; }

 private:
  // Represents the state of ping measurement
  enum class PingState { 
    UNSCHEDULED,  // No ping in progress
    SCHEDULED,    // Ping is scheduled but not started
    STARTED       // Ping is in progress
  };

  // Member variables:
  int64_t accumulator_;        // Bytes received since last ping start
  int64_t estimate_;           // Current BDP estimate in bytes

  gpr_timespec ping_start_time_;  // When the current ping was started
  Duration inter_ping_delay_;     // Current delay between pings
  int stable_estimate_count_;     // Count of consecutive stable estimates
  PingState ping_state_;          // Current state of ping measurement
  double bw_est_;                // Current bandwidth estimate (bytes/sec)
  absl::string_view name_;       // Identifier for logging purposes
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_TRANSPORT_BDP_ESTIMATOR_H
```

The comments explain:
1. The overall purpose of the BDP estimator class
2. Each public method's functionality and purpose
3. The meaning of private member variables
4. The different ping states in the enum
5. The logging and verification being performed
6. The units of measurement for various values

The comments are concise yet informative, providing enough context for future maintainers to understand the code's operation without being overly verbose.