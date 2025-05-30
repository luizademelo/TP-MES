// Copyright 2022 gRPC authors.

#include "src/core/lib/resource_quota/periodic_update.h"

#include <grpc/support/port_platform.h>

#include <atomic>

#include "src/core/util/useful.h"

namespace grpc_core {

bool PeriodicUpdate::MaybeEndPeriod(absl::FunctionRef<void(Duration)> f) {
  if (period_start_ == Timestamp::ProcessEpoch()) {
    period_start_ = Timestamp::Now();
    updates_remaining_.store(1, std::memory_order_release);
    return false;
  }

  auto now = Timestamp::Now();
  Duration time_so_far = now - period_start_;
  if (time_so_far < period_) {

    int64_t better_guess;
    if (time_so_far.millis() == 0) {
      better_guess = expected_updates_per_period_ * 2;
    } else {

      const double scale =
          Clamp(period_.seconds() / time_so_far.seconds(), 1.01, 2.0);
      better_guess = expected_updates_per_period_ * scale;
      if (better_guess <= expected_updates_per_period_) {
        better_guess = expected_updates_per_period_ + 1;
      }
    }

    updates_remaining_.store(better_guess - expected_updates_per_period_,
                             std::memory_order_release);

    return false;
  }

  expected_updates_per_period_ =
      period_.seconds() * expected_updates_per_period_ / time_so_far.seconds();
  if (expected_updates_per_period_ < 1) expected_updates_per_period_ = 1;
  f(time_so_far);
  period_start_ = Timestamp::Now();
  updates_remaining_.store(expected_updates_per_period_,
                           std::memory_order_release);
  return true;
}

}
