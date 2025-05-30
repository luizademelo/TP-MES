
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BACKEND_METRIC_PROPAGATION_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BACKEND_METRIC_PROPAGATION_H

#include <string>

#include "absl/container/flat_hash_set.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

struct BackendMetricPropagation : public RefCounted<BackendMetricPropagation> {
  static constexpr uint8_t kCpuUtilization = 1;
  static constexpr uint8_t kMemUtilization = 2;
  static constexpr uint8_t kApplicationUtilization = 4;
  static constexpr uint8_t kNamedMetricsAll = 8;

  uint8_t propagation_bits = 0;
  absl::flat_hash_set<std::string> named_metric_keys;

  std::string AsString() const;

  bool operator==(const BackendMetricPropagation& other) const {
    return propagation_bits == other.propagation_bits &&
           named_metric_keys == other.named_metric_keys;
  }

  bool operator<(const BackendMetricPropagation& other) const;

  struct Less {
    bool operator()(
        const RefCountedPtr<const BackendMetricPropagation>& p1,
        const RefCountedPtr<const BackendMetricPropagation>& p2) const {
      if (p1 == nullptr || p2 == nullptr) return p1.get() < p2.get();
      return *p1 < *p2;
    }
  };
};

}

#endif
