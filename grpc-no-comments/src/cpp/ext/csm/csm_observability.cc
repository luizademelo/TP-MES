
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
std::atomic<bool> g_csm_plugin_enabled(false);
}

bool CsmServerSelector(const grpc_core::ChannelArgs& ) {
  return g_csm_plugin_enabled;
}

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

class CsmOpenTelemetryPluginOption
    : public grpc::internal::InternalOpenTelemetryPluginOption {
 public:
  CsmOpenTelemetryPluginOption()
      : labels_injector_(std::make_unique<internal::ServiceMeshLabelsInjector>(
            google::cloud::otel::MakeResourceDetector()
                ->Detect()
                .GetAttributes())) {}

  bool IsActiveOnClientChannel(absl::string_view target) const override {
    return CsmChannelTargetSelector(target);
  }

  bool IsActiveOnServer(const grpc_core::ChannelArgs& args) const override {
    return CsmServerSelector(args);
  }

  const grpc::internal::LabelsInjector* labels_injector() const override {
    return labels_injector_.get();
  }

 private:
  std::unique_ptr<internal::ServiceMeshLabelsInjector> labels_injector_;
};

}

CsmObservability::~CsmObservability() {
  if (valid_) {
    internal::g_csm_plugin_enabled = false;
  }
}

CsmObservability::CsmObservability(CsmObservability&& other) noexcept {
  other.valid_ = false;
}
CsmObservability& CsmObservability::operator=(
    CsmObservability&& other) noexcept {
  other.valid_ = false;
  return *this;
}

CsmObservabilityBuilder::CsmObservabilityBuilder()
    : builder_(
          std::make_unique<grpc::internal::OpenTelemetryPluginBuilderImpl>()) {}

CsmObservabilityBuilder::~CsmObservabilityBuilder() = default;

CsmObservabilityBuilder& CsmObservabilityBuilder::SetMeterProvider(
    std::shared_ptr<opentelemetry::metrics::MeterProvider> meter_provider) {
  builder_->SetMeterProvider(meter_provider);
  return *this;
}

CsmObservabilityBuilder& CsmObservabilityBuilder::SetTargetAttributeFilter(
    absl::AnyInvocable<bool(absl::string_view ) const>
        target_attribute_filter) {
  builder_->SetTargetAttributeFilter(std::move(target_attribute_filter));
  return *this;
}

CsmObservabilityBuilder&
CsmObservabilityBuilder::SetGenericMethodAttributeFilter(
    absl::AnyInvocable<bool(absl::string_view ) const>
        generic_method_attribute_filter) {
  builder_->SetGenericMethodAttributeFilter(
      std::move(generic_method_attribute_filter));
  return *this;
}

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

}
