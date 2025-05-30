// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/write_size_policy.h"

#include <grpc/support/port_platform.h>

#include <algorithm>

#include "absl/log/check.h"

namespace grpc_core {

size_t Chttp2WriteSizePolicy::WriteTargetSize() { return current_target_; }

void Chttp2WriteSizePolicy::BeginWrite(size_t size) {
  CHECK(experiment_start_time_ == Timestamp::InfFuture());
  if (size < current_target_ * 7 / 10) {

    if (state_ < 0) state_ = 0;
    return;
  }
  experiment_start_time_ = Timestamp::Now();
}

void Chttp2WriteSizePolicy::EndWrite(bool success) {
  if (experiment_start_time_ == Timestamp::InfFuture()) return;
  const auto elapsed = Timestamp::Now() - experiment_start_time_;
  experiment_start_time_ = Timestamp::InfFuture();
  if (!success) return;
  if (elapsed < FastWrite()) {
    --state_;
    if (state_ == -2) {
      state_ = 0;
      current_target_ = std::min(current_target_ * 3 / 2, MaxTarget());
    }
  } else if (elapsed > SlowWrite()) {
    ++state_;
    if (state_ == 2) {
      state_ = 0;
      current_target_ = std::max(current_target_ / 3, MinTarget());
    }
  } else {
    state_ = 0;
  }
}

}
