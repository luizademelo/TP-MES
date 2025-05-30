
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_BACKEND_METRIC_DATA_H
#define GRPC_SRC_CORE_LOAD_BALANCING_BACKEND_METRIC_DATA_H

#include <grpc/support/port_platform.h>

#include <map>

#include "absl/strings/string_view.h"

namespace grpc_core {

struct BackendMetricData {

  double cpu_utilization = -1;

  double mem_utilization = -1;

  double application_utilization = -1;

  double qps = -1;

  double eps = -1;

  std::map<absl::string_view, double> request_cost;

  std::map<absl::string_view, double> utilization;

  std::map<absl::string_view, double> named_metrics;
};

}

#endif
