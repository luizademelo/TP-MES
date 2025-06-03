Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_HEALTH_STATUS_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_HEALTH_STATUS_H

#include <stdint.h>

#include <optional>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/resolver/endpoint_addresses.h"

// gRPC channel argument key for XDS health status
#define GRPC_ARG_XDS_HEALTH_STATUS \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "xds_health_status"

namespace grpc_core {

// Represents the health status of an XDS endpoint.
// Can be Unknown, Healthy, or Draining.
class XdsHealthStatus final {
 public:
  // Enumeration of possible health status values:
  // - kUnknown: Initial state or status not reported
  // - kHealthy: Endpoint is healthy and can serve requests
  // - kDraining: Endpoint is draining and should not receive new requests
  enum HealthStatus { kUnknown, kHealthy, kDraining };

  // Creates an XdsHealthStatus from a protobuf-encoded status value.
  // Returns empty optional if the status value is invalid.
  static std::optional<XdsHealthStatus> FromUpb(uint32_t status);

  // Creates an XdsHealthStatus from a string representation.
  // Returns empty optional if the string doesn't match any known status.
  static std::optional<XdsHealthStatus> FromString(absl::string_view status);

  // Constructs an XdsHealthStatus with the specified status
  explicit XdsHealthStatus(HealthStatus status) : status_(status) {}

  // Returns the current health status
  HealthStatus status() const { return status_; }

  // Equality comparison operator
  bool operator==(const XdsHealthStatus& other) const {
    return status_ == other.status_;
  }

  // Returns a string representation of the health status
  const char* ToString() const;

 private:
  HealthStatus status_;  // The current health status
};

// Represents a set of XdsHealthStatus values, used to track multiple
// possible statuses for load balancing purposes.
class XdsHealthStatusSet final {
 public:
  // Constructs an empty status set
  XdsHealthStatusSet() = default;

  // Constructs a status set from a span of XdsHealthStatus values
  explicit XdsHealthStatusSet(absl::Span<const XdsHealthStatus> statuses) {
    for (XdsHealthStatus status : statuses) {
      Add(status);
    }
  }

  // Equality comparison operator
  bool operator==(const XdsHealthStatusSet& other) const {
    return status_mask_ == other.status_mask_;
  }

  // Returns true if the set contains no statuses
  bool Empty() const { return status_mask_ == 0; }

  // Clears all statuses from the set
  void Clear() { status_mask_ = 0; }

  // Adds a status to the set
  void Add(XdsHealthStatus status) { status_mask_ |= (0x1 << status.status()); }

  // Checks if the set contains a specific status
  bool Contains(XdsHealthStatus status) const {
    return status_mask_ & (0x1 << status.status());
  }

  // Returns a string representation of all statuses in the set
  std::string ToString() const;

 private:
  // Bitmask representing the set of statuses
  // Each bit corresponds to a HealthStatus enum value
  int status_mask_ = 0;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_HEALTH_STATUS_H
```

Key aspects covered in the comments:
1. Overall purpose of each class (XdsHealthStatus and XdsHealthStatusSet)
2. Meaning of each enum value
3. Purpose and behavior of each method
4. Internal representation details (like the bitmask in XdsHealthStatusSet)
5. Parameters and return values where relevant
6. Special operations like equality comparison
7. File-level documentation (copyright and header guard)

The comments aim to provide enough context for future maintainers to understand both the interface and implementation details without being overly verbose.