
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_WEIGHTED_ROUND_ROBIN_STATIC_STRIDE_SCHEDULER_H
#define GRPC_SRC_CORE_LOAD_BALANCING_WEIGHTED_ROUND_ROBIN_STATIC_STRIDE_SCHEDULER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <optional>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/types/span.h"

namespace grpc_core {

class StaticStrideScheduler final {
 public:

  static std::optional<StaticStrideScheduler> Make(
      absl::Span<const float> float_weights,
      absl::AnyInvocable<uint32_t()> next_sequence_func);

  size_t Pick() const;

 private:
  StaticStrideScheduler(std::vector<uint16_t> weights,
                        absl::AnyInvocable<uint32_t()> next_sequence_func);

  mutable absl::AnyInvocable<uint32_t()> next_sequence_func_;

  std::vector<uint16_t> weights_;
};

}

#endif
