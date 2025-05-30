// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_PERIODIC_UPDATE_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_PERIODIC_UPDATE_H

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <atomic>

#include "absl/functional/function_ref.h"
#include "src/core/util/time.h"

namespace grpc_core {

class PeriodicUpdate {
 public:
  explicit PeriodicUpdate(Duration period) : period_(period) {}

  bool Tick(absl::FunctionRef<void(Duration)> f) {

    if (updates_remaining_.fetch_sub(1, std::memory_order_acquire) == 1) {
      return MaybeEndPeriod(f);
    }
    return false;
  }

 private:
  bool MaybeEndPeriod(absl::FunctionRef<void(Duration)> f);

  std::atomic<int64_t> updates_remaining_{1};
  const Duration period_;
  Timestamp period_start_ = Timestamp::ProcessEpoch();
  int64_t expected_updates_per_period_ = 1;
};

}

#endif
