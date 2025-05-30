
// Copyright 2016 gRPC authors.

#include "src/core/lib/transport/bdp_estimator.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stdlib.h>

#include <algorithm>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc_core {

BdpEstimator::BdpEstimator(absl::string_view name)
    : accumulator_(0),
      estimate_(65536),
      ping_start_time_(gpr_time_0(GPR_CLOCK_MONOTONIC)),
      inter_ping_delay_(Duration::Milliseconds(100)),
      stable_estimate_count_(0),
      ping_state_(PingState::UNSCHEDULED),
      bw_est_(0),
      name_(name) {}

Timestamp BdpEstimator::CompletePing() {
  gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
  gpr_timespec dt_ts = gpr_time_sub(now, ping_start_time_);
  double dt = static_cast<double>(dt_ts.tv_sec) +
              (1e-9 * static_cast<double>(dt_ts.tv_nsec));
  double bw = dt > 0 ? (static_cast<double>(accumulator_) / dt) : 0;
  Duration start_inter_ping_delay = inter_ping_delay_;
  GRPC_TRACE_LOG(bdp_estimator, INFO)
      << "bdp[" << name_ << "]:complete acc=" << accumulator_
      << " est=" << estimate_ << " dt=" << dt << " bw=" << bw / 125000.0
      << "Mbs bw_est=" << bw_est_ / 125000.0 << "Mbs";
  CHECK(ping_state_ == PingState::STARTED);
  if (accumulator_ > 2 * estimate_ / 3 && bw > bw_est_) {
    estimate_ = std::max(accumulator_, estimate_ * 2);
    bw_est_ = bw;
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]: estimate increased to " << estimate_;
    inter_ping_delay_ /= 2;

  } else if (inter_ping_delay_ < Duration::Seconds(10)) {
    stable_estimate_count_++;
    if (stable_estimate_count_ >= 2) {

      inter_ping_delay_ += Duration::Milliseconds(
          100 + static_cast<int>(rand() * 100.0 / RAND_MAX));
    }
  }
  if (start_inter_ping_delay != inter_ping_delay_) {
    stable_estimate_count_ = 0;
    GRPC_TRACE_LOG(bdp_estimator, INFO)
        << "bdp[" << name_ << "]:update_inter_time to "
        << inter_ping_delay_.millis() << "ms";
  }
  ping_state_ = PingState::UNSCHEDULED;
  accumulator_ = 0;
  return Timestamp::Now() + inter_ping_delay_;
}

}
