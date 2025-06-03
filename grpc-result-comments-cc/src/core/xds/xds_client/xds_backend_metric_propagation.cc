Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "src/core/xds/xds_client/xds_backend_metric_propagation.h"

#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "src/core/util/useful.h"

namespace grpc_core {

// Converts the BackendMetricPropagation object to a string representation
// The output format is a comma-separated list of metrics enclosed in curly braces
// Example: "{cpu_utilization,mem_utilization,named_metrics.metric1}"
std::string BackendMetricPropagation::AsString() const {
  std::vector<std::string> parts;
  
  // Check each metric flag and add corresponding string if set
  if (propagation_bits & kCpuUtilization) parts.push_back("cpu_utilization");
  if (propagation_bits & kMemUtilization) parts.push_back("mem_utilization");
  if (propagation_bits & kApplicationUtilization) {
    parts.push_back("application_utilization");
  }
  
  // Handle named metrics - either all metrics or specific ones
  if (propagation_bits & kNamedMetricsAll) {
    // If all named metrics are selected, use wildcard notation
    parts.push_back("named_metrics.*");
  } else {
    // For specific named metrics, sort them alphabetically and format each one
    std::vector<absl::string_view> keys(named_metric_keys.begin(),
                                      named_metric_keys.end());
    std::sort(keys.begin(), keys.end());
    for (const auto& key : keys) {
      parts.push_back(absl::StrCat("named_metrics.", key));
    }
  }
  
  // Combine all parts into a single string with comma separators
  return absl::StrCat("{", absl::StrJoin(parts, ","), "}");
}

// Comparison operator for BackendMetricPropagation objects
// Provides strict weak ordering required for use in ordered containers
bool BackendMetricPropagation::operator<(
    const BackendMetricPropagation& other) const {
  // First compare the propagation bits (bitmask of enabled metrics)
  int c = QsortCompare(propagation_bits, other.propagation_bits);
  if (c != 0) return c == -1;
  
  // If bits are equal, compare named metrics lexicographically
  auto other_it = other.named_metric_keys.begin();
  for (auto it = named_metric_keys.begin(); it != named_metric_keys.end();
       ++it) {
    // If other has fewer named metrics, we're greater
    if (other_it == other.named_metric_keys.end()) return false;
    // Compare current metric names
    c = QsortCompare(*it, *other_it);
    if (c != 0) return c == -1;
    ++other_it;
  }
  
  // If we get here, either all named metrics are equal or we have fewer metrics
  // than the other object (in which case we're less than)
  return other_it != other.named_metric_keys.end();
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each method
2. The logic flow within each method
3. The significance of key operations
4. The expected output formats
5. The comparison semantics for the operator<

The comments are designed to help future maintainers understand:
- What the code does
- Why it does it that way
- How the different components interact
- The expected behavior in different scenarios