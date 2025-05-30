
// Copyright 2022 gRPC authors.

#ifndef GRPCPP_EXT_GCP_OBSERVABILITY_H
#define GRPCPP_EXT_GCP_OBSERVABILITY_H

#include <grpc/support/port_platform.h>
#include <grpcpp/impl/grpc_library.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

#define GRPC_GCP_OBSERVABILITY_DEPRECATED_REASON                          \
  "OpenCensus has been sunsetted in favor of OpenTelemetry "              \
  "https://opentelemetry.io/blog/2023/sunsetting-opencensus/. Given GCP " \
  "Observability's dependency on OpenCensus, it is deprecated as well."

namespace grpc {

class GRPC_DEPRECATED(GRPC_GCP_OBSERVABILITY_DEPRECATED_REASON)
    GcpObservability {
 public:

  GRPC_DEPRECATED(GRPC_GCP_OBSERVABILITY_DEPRECATED_REASON)
  static absl::StatusOr<GcpObservability> Init();

  GcpObservability() = default;

  GcpObservability(GcpObservability&& other) noexcept;
  GcpObservability& operator=(GcpObservability&& other) noexcept;

  GcpObservability(const GcpObservability&) = delete;
  GcpObservability& operator=(const GcpObservability&) = delete;

 private:

  class GcpObservabilityImpl : private internal::GrpcLibrary {
   public:
    ~GcpObservabilityImpl() override;
  };
  std::unique_ptr<GcpObservabilityImpl> impl_;
};

namespace experimental {

GRPC_DEPRECATED("Use grpc::GcpObservability::Init() instead.")
absl::Status GcpObservabilityInit();
GRPC_DEPRECATED("Use grpc::GcpObservability::Init() instead.")
void GcpObservabilityClose();
}

}

#endif
