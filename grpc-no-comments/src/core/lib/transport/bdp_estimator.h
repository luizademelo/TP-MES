
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

class BdpEstimator {
 public:
  explicit BdpEstimator(absl::string_view name);
  ~BdpEstimator() {}

  int64_t EstimateBdp() const { return estimate_; }
  double EstimateBandwidth() const { return bw_est_; }

  void AddIncomingBytes(int64_t num_bytes) { accumulator_ += num_bytes; }

  void SchedulePing() {
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]:sched acc=" << accumulator_
        << " est=" << estimate_;
    CHECK(ping_state_ == PingState::UNSCHEDULED);
    ping_state_ = PingState::SCHEDULED;
    accumulator_ = 0;
  }

  void StartPing() {
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]:start acc=" << accumulator_
        << " est=" << estimate_;
    CHECK(ping_state_ == PingState::SCHEDULED);
    ping_state_ = PingState::STARTED;
    ping_start_time_ = gpr_now(GPR_CLOCK_MONOTONIC);
  }

  Timestamp CompletePing();

  int64_t accumulator() const { return accumulator_; }

 private:
  enum class PingState { UNSCHEDULED, SCHEDULED, STARTED };

  int64_t accumulator_;
  int64_t estimate_;

  gpr_timespec ping_start_time_;
  Duration inter_ping_delay_;
  int stable_estimate_count_;
  PingState ping_state_;
  double bw_est_;
  absl::string_view name_;
};

}

#endif
