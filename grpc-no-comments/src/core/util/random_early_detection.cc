// Copyright 2023 gRPC authors.

#include "src/core/util/random_early_detection.h"

#include <grpc/support/port_platform.h>

#include "absl/random/distributions.h"

namespace grpc_core {

bool RandomEarlyDetection::Reject(uint64_t size, absl::BitGenRef bitsrc) const {
  if (size <= soft_limit_) return false;
  if (size < hard_limit_) {
    return absl::Bernoulli(bitsrc,
                           static_cast<double>(size - soft_limit_) /
                               static_cast<double>(hard_limit_ - soft_limit_));
  }
  return true;
}

}
