
// Copyright 2022 gRPC authors.

#include "src/core/load_balancing/weighted_round_robin/static_stride_scheduler.h"

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"

namespace grpc_core {

namespace {

constexpr uint16_t kMaxWeight = std::numeric_limits<uint16_t>::max();

constexpr double kMaxRatio = 10;

constexpr double kMinRatio = 0.01;

}

std::optional<StaticStrideScheduler> StaticStrideScheduler::Make(
    absl::Span<const float> float_weights,
    absl::AnyInvocable<uint32_t()> next_sequence_func) {
  if (float_weights.empty()) return std::nullopt;
  if (float_weights.size() == 1) return std::nullopt;

  const size_t n = float_weights.size();
  size_t num_zero_weight_channels = 0;
  double sum = 0;
  float unscaled_max = 0;
  for (const float weight : float_weights) {
    sum += weight;
    unscaled_max = std::max(unscaled_max, weight);
    if (weight == 0) {
      ++num_zero_weight_channels;
    }
  }

  if (num_zero_weight_channels == n) return std::nullopt;

  const double unscaled_mean =
      sum / static_cast<double>(n - num_zero_weight_channels);
  const double ratio = unscaled_max / unscaled_mean;

  if (ratio > kMaxRatio) {
    unscaled_max = kMaxRatio * unscaled_mean;
  }

  const double scaling_factor = kMaxWeight / unscaled_max;

  const uint16_t mean = std::lround(scaling_factor * unscaled_mean);

  const uint16_t weight_lower_bound =
      std::max(static_cast<uint16_t>(1),
               static_cast<uint16_t>(std::lround(mean * kMinRatio)));

  std::vector<uint16_t> weights;
  weights.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    if (float_weights[i] == 0) {
      weights.push_back(mean);
    } else {
      const double float_weight_capped_from_above =
          std::min(float_weights[i], unscaled_max);
      const uint16_t weight =
          std::lround(float_weight_capped_from_above * scaling_factor);
      weights.push_back(std::max(weight, weight_lower_bound));
    }
  }

  CHECK(weights.size() == float_weights.size());
  return StaticStrideScheduler{std::move(weights),
                               std::move(next_sequence_func)};
}

StaticStrideScheduler::StaticStrideScheduler(
    std::vector<uint16_t> weights,
    absl::AnyInvocable<uint32_t()> next_sequence_func)
    : next_sequence_func_(std::move(next_sequence_func)),
      weights_(std::move(weights)) {
  CHECK(next_sequence_func_ != nullptr);
}

size_t StaticStrideScheduler::Pick() const {
  while (true) {
    const uint32_t sequence = next_sequence_func_();

    const uint64_t backend_index = sequence % weights_.size();
    const uint64_t generation = sequence / weights_.size();
    const uint64_t weight = weights_[backend_index];

    const uint16_t kOffset = kMaxWeight / 2;
    const uint16_t mod =
        (weight * generation + backend_index * kOffset) % kMaxWeight;

    if (mod < kMaxWeight - weight) {

      continue;
    }
    return backend_index;
  }
}

}
