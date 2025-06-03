Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/csm/csm_observability.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/ext/csm_observability.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "google/cloud/opentelemetry/resource_detector.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk/resource/resource_detector.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/uri.h"
#include "src/core/xds/grpc/xds_enabled_server.h"
#include "src/cpp/ext/csm/metadata_exchange.h"
#include "src/cpp/ext/otel/otel_plugin.h"

namespace grpc {

namespace internal {

namespace {
// Atomic flag to track if CSM (Cloud Service Mesh) plugin is enabled
std::atomic<bool> g_csm_plugin_enabled(false);
}

// Determines if CSM should be active on a server based on channel args
// Currently just checks if the CSM plugin is globally enabled
bool CsmServerSelector(const grpc_core::ChannelArgs& ) {
  return g_csm_plugin_enabled;
}

// Determines if CSM should be active for a client channel based on target URI
// Returns true if:
// - CSM plugin is enabled
// - Target URI scheme is "xds"
// - Target URI authority is empty or matches traffic director global endpoint
bool CsmChannelTargetSelector(absl::string_view target) {
  if (!g_csm_plugin_enabled) return false;
  auto uri = grpc_core::URI::Parse(target);
  if (!uri.ok()) {
    LOG(ERROR) << "Failed to parse URI: " << target;
    return false;
  }

  if (uri->scheme() != "xds") {
    return false;
  }

  if (!uri->authority().empty() &&
      uri->authority() != "traffic-director-global.xds.googleapis.com") {
    return false;
  }
  return true;
}

// Implementation of OpenTelemetry plugin option specific to CSM
class CsmOpenTelemetryPluginOption
    : public grpc::internal::InternalOpenTelemetryPluginOption {
 public:
  // Constructor initializes the labels injector with attributes from
  // the detected cloud resource
  CsmOpenTelemetryPluginOption()
      : labels_injector_(std::make_unique<internal::ServiceMeshLabelsInjector>(
            google::cloud::otel::MakeResourceDetector()
                ->Detect()
                .GetAttributes())) {}

  // Checks if plugin should be active for client channel based on target
  bool IsActiveOnClientChannel(absl::string_view target) const override {
    return CsmChannelTargetSelector(target);
  }

  // Checks if plugin should be active for server based on channel args
  bool IsActiveOnServer(const grpc_core::ChannelArgs& args) const override {
    return CsmServerSelector(args);
  }

  // Returns the labels injector for adding CSM-specific labels to metrics
  const grpc::internal::LabelsInjector* labels_injector() const override {
    return labels_injector_.get();
  }

 private:
  std::unique_ptr<internal::ServiceMeshLabelsInjector> labels_injector_;
};

}  // namespace internal

// Destructor - disables CSM plugin if this instance was valid
CsmObservability::~CsmObservability() {
  if (valid_) {
    internal::g_csm_plugin_enabled = false;
  }
}

// Move constructor - marks source as invalid
CsmObservability::CsmObservability(CsmObservability&& other) noexcept {
  other.valid_ = false;
}

// Move assignment operator - marks source as invalid
CsmObservability& CsmObservability::operator=(
    CsmObservability&& other) noexcept {
  other.valid_ = false;
  return *this;
}

// Builder for CsmObservability
CsmObservabilityBuilder::CsmObservabilityBuilder()
    : builder_(
          std::make_unique<grpc::internal::OpenTelemetryPluginBuilderImpl>()) {}

CsmObservabilityBuilder::~CsmObservabilityBuilder() = default;

// Sets the meter provider for CSM observability
CsmObservabilityBuilder& CsmObservabilityBuilder::SetMeterProvider(
    std::shared_ptr<opentelemetry::metrics::MeterProvider> meter_provider) {
  builder_->SetMeterProvider(meter_provider);
  return *this;
}

// Sets the filter for target attributes in CSM observability
CsmObservabilityBuilder& CsmObservabilityBuilder::SetTargetAttributeFilter(
    absl::AnyInvocable<bool(absl::string_view ) const>
        target_attribute_filter) {
  builder_->SetTargetAttributeFilter(std::move(target_attribute_filter));
  return *this;
}

// Sets the filter for generic method attributes in CSM observability
CsmObservabilityBuilder&
CsmObservabilityBuilder::SetGenericMethodAttributeFilter(
    absl::AnyInvocable<bool(absl::string_view ) const>
        generic_method_attribute_filter) {
  builder_->SetGenericMethodAttributeFilter(
      std::move(generic_method_attribute_filter));
  return *this;
}

// Builds and registers the CSM observability plugin
// Returns:
// - StatusOr containing CsmObservability instance on success
// - Error status if registration fails
absl::StatusOr<CsmObservability> CsmObservabilityBuilder::BuildAndRegister() {
  builder_->AddPluginOption(
      std::make_unique<grpc::internal::CsmOpenTelemetryPluginOption>());
  auto status = builder_->BuildAndRegisterGlobal();
  internal::g_csm_plugin_enabled = true;
  if (!status.ok()) {
    return status;
  }
  return CsmObservability();
}

}  // namespace grpc
```