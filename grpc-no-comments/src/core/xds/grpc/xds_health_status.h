
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_HEALTH_STATUS_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_HEALTH_STATUS_H

#include <stdint.h>

#include <optional>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/resolver/endpoint_addresses.h"

#define GRPC_ARG_XDS_HEALTH_STATUS \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "xds_health_status"

namespace grpc_core {

class XdsHealthStatus final {
 public:
  enum HealthStatus { kUnknown, kHealthy, kDraining };

  static std::optional<XdsHealthStatus> FromUpb(uint32_t status);
  static std::optional<XdsHealthStatus> FromString(absl::string_view status);

  explicit XdsHealthStatus(HealthStatus status) : status_(status) {}

  HealthStatus status() const { return status_; }

  bool operator==(const XdsHealthStatus& other) const {
    return status_ == other.status_;
  }

  const char* ToString() const;

 private:
  HealthStatus status_;
};

class XdsHealthStatusSet final {
 public:
  XdsHealthStatusSet() = default;

  explicit XdsHealthStatusSet(absl::Span<const XdsHealthStatus> statuses) {
    for (XdsHealthStatus status : statuses) {
      Add(status);
    }
  }

  bool operator==(const XdsHealthStatusSet& other) const {
    return status_mask_ == other.status_mask_;
  }

  bool Empty() const { return status_mask_ == 0; }

  void Clear() { status_mask_ = 0; }

  void Add(XdsHealthStatus status) { status_mask_ |= (0x1 << status.status()); }

  bool Contains(XdsHealthStatus status) const {
    return status_mask_ & (0x1 << status.status());
  }

  std::string ToString() const;

 private:
  int status_mask_ = 0;
};

}

#endif
