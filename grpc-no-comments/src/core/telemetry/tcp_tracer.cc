
// Copyright 2025 gRPC authors.

#include "src/core/telemetry/tcp_tracer.h"

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"

namespace grpc_core {

std::string TcpCallTracer::TcpEventMetric::ToString() {
  return absl::StrCat(key, "=", value);
}

std::string TcpCallTracer::TcpEventMetricsToString(
    const std::vector<TcpEventMetric>& metrics) {
  return absl::StrJoin(metrics, ", ",
                       [](std::string* out, TcpEventMetric metric) {
                         absl::StrAppend(out, metric.ToString());
                       });
}

}
