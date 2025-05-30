
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_BACKEND_METRIC_PARSER_H
#define GRPC_SRC_CORE_LOAD_BALANCING_BACKEND_METRIC_PARSER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/strings/string_view.h"
#include "src/core/load_balancing/backend_metric_data.h"

namespace grpc_core {

class BackendMetricAllocatorInterface {
 public:
  virtual ~BackendMetricAllocatorInterface() = default;

  virtual BackendMetricData* AllocateBackendMetricData() = 0;

  virtual char* AllocateString(size_t size) = 0;
};

const BackendMetricData* ParseBackendMetricData(
    absl::string_view serialized_load_report,
    BackendMetricAllocatorInterface* allocator);

}

#endif
