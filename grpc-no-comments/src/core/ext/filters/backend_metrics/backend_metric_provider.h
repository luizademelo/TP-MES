// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_BACKEND_METRICS_BACKEND_METRIC_PROVIDER_H
#define GRPC_SRC_CORE_EXT_FILTERS_BACKEND_METRICS_BACKEND_METRIC_PROVIDER_H

#include "src/core/lib/resource_quota/arena.h"

namespace grpc_core {

struct BackendMetricData;
class BackendMetricProvider {
 public:
  virtual ~BackendMetricProvider() = default;
  virtual BackendMetricData GetBackendMetricData() = 0;
};

template <>
struct ArenaContextType<BackendMetricProvider> {
  static void Destroy(BackendMetricProvider*) {}
};

}

#endif
