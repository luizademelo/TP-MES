Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/xds/grpc/xds_health_status.h"

#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "envoy/config/core/v3/health_check.upb.h"

namespace grpc_core {

// Converts a health status from UPB (Universal Protocol Buffers) format to XdsHealthStatus.
// Returns std::nullopt if the input status is not recognized.
std::optional<XdsHealthStatus> XdsHealthStatus::FromUpb(uint32_t status) {
  switch (status) {
    case envoy_config_core_v3_UNKNOWN:
      return XdsHealthStatus(kUnknown);
    case envoy_config_core_v3_HEALTHY:
      return XdsHealthStatus(kHealthy);
    case envoy_config_core_v3_DRAINING:
      return XdsHealthStatus(kDraining);
    default:
      return std::nullopt;
  }
}

// Converts a string representation of health status to XdsHealthStatus.
// Returns std::nullopt if the input string doesn't match any known status.
std::optional<XdsHealthStatus> XdsHealthStatus::FromString(
    absl::string_view status) {
  if (status == "UNKNOWN") return XdsHealthStatus(kUnknown);
  if (status == "HEALTHY") return XdsHealthStatus(kHealthy);
  if (status == "DRAINING") return XdsHealthStatus(kDraining);
  return std::nullopt;
}

// Returns a string representation of the current health status.
// Returns "<INVALID>" if the status is not recognized.
const char* XdsHealthStatus::ToString() const {
  switch (status_) {
    case kUnknown:
      return "UNKNOWN";
    case kHealthy:
      return "HEALTHY";
    case kDraining:
      return "DRAINING";
    default:
      return "<INVALID>";
  }
}

// Returns a string representation of the health status set in the format "{STATUS1, STATUS2}".
// Only includes statuses that are present in the set.
std::string XdsHealthStatusSet::ToString() const {
  std::vector<const char*> set;
  set.reserve(3);  // Reserve space for all possible statuses (unknown, healthy, draining)
  
  // Iterate through all possible health statuses
  for (const auto& status :
       {XdsHealthStatus::kUnknown, XdsHealthStatus::kHealthy,
        XdsHealthStatus::kDraining}) {
    const XdsHealthStatus health_status(status);
    if (Contains(health_status)) set.push_back(health_status.ToString());
  }
  
  // Join the status strings with commas and enclose in curly braces
  return absl::StrCat("{", absl::StrJoin(set, ", "), "}");
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each function
2. The input/output behavior
3. Special cases (like unrecognized inputs)
4. The logic flow in more complex functions
5. Important implementation details (like the reserve() call)
6. The string formatting in ToString() methods

The comments are kept concise while providing all the essential information a developer would need to understand and maintain this code.