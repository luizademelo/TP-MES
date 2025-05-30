
// Copyright 2023 gRPC authors.

#ifndef GRPCPP_EXT_CSM_OBSERVABILITY_H
#define GRPCPP_EXT_CSM_OBSERVABILITY_H

#include <grpc/support/port_platform.h>
#include <grpcpp/ext/otel_plugin.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "opentelemetry/metrics/meter_provider.h"

namespace grpc {

namespace internal {
class OpenTelemetryPluginBuilderImpl;
}

class CsmObservability {
 public:
  CsmObservability() = default;
  ~CsmObservability();

  CsmObservability(const CsmObservability&) = delete;
  CsmObservability& operator=(const CsmObservability&) = delete;
  CsmObservability(CsmObservability&&) noexcept;
  CsmObservability& operator=(CsmObservability&&) noexcept;

 private:
  bool valid_ = true;
};

class CsmObservabilityBuilder {
 public:
  CsmObservabilityBuilder();
  ~CsmObservabilityBuilder();
  CsmObservabilityBuilder& SetMeterProvider(
      std::shared_ptr<opentelemetry::metrics::MeterProvider> meter_provider);

  CsmObservabilityBuilder& SetTargetAttributeFilter(
      absl::AnyInvocable<bool(absl::string_view ) const>
          target_attribute_filter);

  CsmObservabilityBuilder& SetGenericMethodAttributeFilter(
      absl::AnyInvocable<bool(absl::string_view ) const>
          generic_method_attribute_filter);

  absl::StatusOr<CsmObservability> BuildAndRegister();

 private:
  std::unique_ptr<grpc::internal::OpenTelemetryPluginBuilderImpl> builder_;
};

namespace experimental {

using CsmObservability GRPC_DEPRECATED("Use grpc::CsmObservability instead.") =
    grpc::CsmObservability;
using CsmObservabilityBuilder GRPC_DEPRECATED(
    "Use grpc::CsmObservabilityBuilder instead.") =
    grpc::CsmObservabilityBuilder;
}

}

#endif
