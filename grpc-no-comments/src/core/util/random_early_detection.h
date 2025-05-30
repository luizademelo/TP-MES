// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_RANDOM_EARLY_DETECTION_H
#define GRPC_SRC_CORE_UTIL_RANDOM_EARLY_DETECTION_H

#include <grpc/support/port_platform.h>
#include <limits.h>

#include <cstdint>

#include "absl/random/bit_gen_ref.h"

namespace grpc_core {

class RandomEarlyDetection {
 public:
  RandomEarlyDetection() : soft_limit_(INT_MAX), hard_limit_(INT_MAX) {}
  RandomEarlyDetection(uint64_t soft_limit, uint64_t hard_limit)
      : soft_limit_(soft_limit), hard_limit_(hard_limit) {}

  bool MustReject(uint64_t size) { return size >= hard_limit_; }

  bool Reject(uint64_t size, absl::BitGenRef bitsrc) const;

  uint64_t soft_limit() const { return soft_limit_; }
  uint64_t hard_limit() const { return hard_limit_; }

  void SetLimits(uint64_t soft_limit, uint64_t hard_limit) {
    soft_limit_ = soft_limit;
    hard_limit_ = hard_limit;
  }

 private:

  uint64_t soft_limit_;

  uint64_t hard_limit_;
};

}

#endif
