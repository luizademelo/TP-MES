
// Copyright 2024 gRPC authors.

#include "src/core/xds/xds_client/xds_backend_metric_propagation.h"

#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "src/core/util/useful.h"

namespace grpc_core {

std::string BackendMetricPropagation::AsString() const {
  std::vector<std::string> parts;
  if (propagation_bits & kCpuUtilization) parts.push_back("cpu_utilization");
  if (propagation_bits & kMemUtilization) parts.push_back("mem_utilization");
  if (propagation_bits & kApplicationUtilization) {
    parts.push_back("application_utilization");
  }
  if (propagation_bits & kNamedMetricsAll) {
    parts.push_back("named_metrics.*");
  } else {

    std::vector<absl::string_view> keys(named_metric_keys.begin(),
                                        named_metric_keys.end());
    std::sort(keys.begin(), keys.end());
    for (const auto& key : keys) {
      parts.push_back(absl::StrCat("named_metrics.", key));
    }
  }
  return absl::StrCat("{", absl::StrJoin(parts, ","), "}");
}

bool BackendMetricPropagation::operator<(
    const BackendMetricPropagation& other) const {
  int c = QsortCompare(propagation_bits, other.propagation_bits);
  if (c != 0) return c == -1;
  auto other_it = other.named_metric_keys.begin();
  for (auto it = named_metric_keys.begin(); it != named_metric_keys.end();
       ++it) {
    if (other_it == other.named_metric_keys.end()) return false;
    c = QsortCompare(*it, *other_it);
    if (c != 0) return c == -1;
    ++other_it;
  }
  return false;
}

}
