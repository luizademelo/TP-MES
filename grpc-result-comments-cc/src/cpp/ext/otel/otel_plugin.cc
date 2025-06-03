Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/otel/otel_plugin.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/ext/otel_plugin.h>
#include <grpcpp/version_info.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/escaping.h"
#include "opentelemetry/metrics/meter.h"
#include "opentelemetry/metrics/meter_provider.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "opentelemetry/nostd/string_view.h"
#include "opentelemetry/nostd/variant.h"
#include "opentelemetry/trace/context.h"
#include "opentelemetry/trace/span_context.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/match.h"
#include "src/cpp/ext/otel/key_value_iterable.h"
#include "src/cpp/ext/otel/otel_client_call_tracer.h"
#include "src/cpp/ext/otel/otel_server_call_tracer.h"

using opentelemetry::context::propagation::TextMapPropagator;
using opentelemetry::trace::SpanContext;
using opentelemetry::trace::SpanId;
using opentelemetry::trace::TraceId;

namespace grpc {
namespace internal {

// Returns the OpenTelemetry method key
absl::string_view OpenTelemetryMethodKey() { return "grpc.method"; }

// Returns the OpenTelemetry status key
absl::string_view OpenTelemetryStatusKey() { return "grpc.status"; }

// Returns the OpenTelemetry target key
absl::string_view OpenTelemetryTargetKey() { return "grpc.target"; }

namespace {
// Returns a set of base metrics that are enabled by default
absl::flat_hash_set<std::string> BaseMetrics() {
  absl::flat_hash_set<std::string> base_metrics{
      std::string(grpc::OpenTelemetryPluginBuilder::
                      kClientAttemptStartedInstrumentName),
      std::string(grpc::OpenTelemetryPluginBuilder::
                      kClientAttemptDurationInstrumentName),
      std::string(
          grpc::OpenTelemetryPluginBuilder::
              kClientAttemptSentTotalCompressedMessageSizeInstrumentName),
      std::string(
          grpc::OpenTelemetryPluginBuilder::
              kClientAttemptRcvdTotalCompressedMessageSizeInstrumentName),
      std::string(
          grpc::OpenTelemetryPluginBuilder::kServerCallStartedInstrumentName),
      std::string(
          grpc::OpenTelemetryPluginBuilder::kServerCallDurationInstrumentName),
      std::string(grpc::OpenTelemetryPluginBuilder::
                      kServerCallSentTotalCompressedMessageSizeInstrumentName),
      std::string(grpc::OpenTelemetryPluginBuilder::
                      kServerCallRcvdTotalCompressedMessageSizeInstrumentName)};
  // Add any global instruments that are enabled by default
  grpc_core::GlobalInstrumentsRegistry::ForEach(
      [&](const grpc_core::GlobalInstrumentsRegistry::
              GlobalInstrumentDescriptor& descriptor) {
        if (descriptor.enable_by_default) {
          base_metrics.emplace(descriptor.name);
        }
      });
  return base_metrics;
}
}  // namespace

// Implementation of KeyValueIterable for OpenTelemetry metrics
class OpenTelemetryPluginImpl::NPCMetricsKeyValueIterable
    : public opentelemetry::common::KeyValueIterable {
 public:
  NPCMetricsKeyValueIterable(
      absl::Span<const absl::string_view> label_keys,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_label_keys,
      absl::Span<const absl::string_view> optional_label_values,
      const OptionalLabelsBitSet& optional_labels_bits)
      : label_keys_(label_keys),
        label_values_(label_values),
        optional_label_keys_(optional_label_keys),
        optional_label_values_(optional_label_values),
        optional_labels_bits_(optional_labels_bits) {}

  // Iterates through key-value pairs and applies the callback function
  bool ForEachKeyValue(opentelemetry::nostd::function_ref<
                       bool(opentelemetry::nostd::string_view,
                            opentelemetry::common::AttributeValue)>
                           callback) const noexcept override {
    // Process required labels first
    for (size_t i = 0; i < label_keys_.size(); ++i) {
      if (!callback(AbslStrViewToOpenTelemetryStrView(label_keys_[i]),
                    AbslStrViewToOpenTelemetryStrView(label_values_[i]))) {
        return false;
      }
    }

    // Process optional labels based on the bitset
    bool filtered = optional_label_values_.size() < optional_label_keys_.size();
    for (size_t i = 0, j = 0; i < optional_label_keys_.size(); ++i) {
      if (!optional_labels_bits_.test(i)) {
        if (!filtered) ++j;
        continue;
      }
      if (!callback(
              AbslStrViewToOpenTelemetryStrView(optional_label_keys_[i]),
              AbslStrViewToOpenTelemetryStrView(optional_label_values_[j++]))) {
        return false;
      }
    }
    return true;
  }

  // Returns total number of labels (required + enabled optional)
  size_t size() const noexcept override {
    return label_keys_.size() + optional_labels_bits_.count();
  }

 private:
  absl::Span<const absl::string_view> label_keys_;
  absl::Span<const absl::string_view> label_values_;
  absl::Span<const absl::string_view> optional_label_keys_;
  absl::Span<const absl::string_view> optional_label_values_;
  const OptionalLabelsBitSet& optional_labels_bits_;
};

// Initialize OpenTelemetryPluginBuilder with base metrics
OpenTelemetryPluginBuilderImpl::OpenTelemetryPluginBuilderImpl()
    : metrics_(BaseMetrics()) {}

OpenTelemetryPluginBuilderImpl::~OpenTelemetryPluginBuilderImpl() = default;

// Set the meter provider for metrics collection
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetMeterProvider(
    std::shared_ptr<opentelemetry::metrics::MeterProvider> meter_provider) {
  meter_provider_ = std::move(meter_provider);
  return *this;
}

// Enable specific metrics by name
OpenTelemetryPluginBuilderImpl& OpenTelemetryPluginBuilderImpl::EnableMetrics(
    absl::Span<const absl::string_view> metric_names) {
  for (const auto& metric_name : metric_names) {
    metrics_.emplace(metric_name);
  }
  return *this;
}

// Disable specific metrics by name
OpenTelemetryPluginBuilderImpl& OpenTelemetryPluginBuilderImpl::DisableMetrics(
    absl::Span<const absl::string_view> metric_names) {
  for (const auto& metric_name : metric_names) {
    metrics_.erase(metric_name);
  }
  return *this;
}

// Disable all metrics
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::DisableAllMetrics() {
  metrics_.clear();
  return *this;
}

// Set filter for target attributes
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetTargetAttributeFilter(
    absl::AnyInvocable<bool(absl::string_view ) const>
        target_attribute_filter) {
  target_attribute_filter_ = std::move(target_attribute_filter);
  return *this;
}

// Set filter for generic method attributes
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetGenericMethodAttributeFilter(
    absl::AnyInvocable<bool(absl::string_view ) const>
        generic_method_attribute_filter) {
  generic_method_attribute_filter_ = std::move(generic_method_attribute_filter);
  return *this;
}

// Set server selector for determining which servers to instrument
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetServerSelector(
    absl::AnyInvocable<bool(const grpc_core::ChannelArgs& ) const>
        server_selector) {
  server_selector_ = std::move(server_selector);
  return *this;
}

// Add a plugin option
OpenTelemetryPluginBuilderImpl& OpenTelemetryPluginBuilderImpl::AddPluginOption(
    std::unique_ptr<InternalOpenTelemetryPluginOption> option) {
  CHECK_LT(plugin_options_.size(), 64u);
  plugin_options_.push_back(std::move(option));
  return *this;
}

// Add an optional label key
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::AddOptionalLabel(
    absl::string_view optional_label_key) {
  optional_label_keys_.emplace(optional_label_key);
  return *this;
}

// Set the tracer provider for tracing
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetTracerProvider(
    std::shared_ptr<opentelemetry::trace::TracerProvider> tracer_provider) {
  tracer_provider_ = std::move(tracer_provider);
  return *this;
}

// Set the text map propagator for trace context propagation
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetTextMapPropagator(
    std::unique_ptr<TextMapPropagator> text_map_propagator) {
  text_map_propagator_ = std::move(text_map_propagator);
  return *this;
}

// Set filter for channel scope
OpenTelemetryPluginBuilderImpl&
OpenTelemetryPluginBuilderImpl::SetChannelScopeFilter(
    absl::AnyInvocable<
        bool(const OpenTelemetryPluginBuilder::ChannelScope& ) const>
        channel_scope_filter) {
  channel_scope_filter_ = std::move(channel_scope_filter);
  return *this;
}

// Build and register the plugin globally
absl::Status OpenTelemetryPluginBuilderImpl::BuildAndRegisterGlobal() {
  if (meter_provider_ == nullptr && tracer_provider_ == nullptr) {
    return absl::InvalidArgumentError(
        "Need to configure a valid meter provider or tracer provider.");
  }
  grpc_core::GlobalStatsPluginRegistry::RegisterStatsPlugin(
      std::make_shared<OpenTelemetryPluginImpl>(
          metrics_, meter_provider_, std::move(target_attribute_filter_),
          std::move(generic_method_attribute_filter_),
          std::move(server_selector_), std::move(plugin_options_),
          std::move(optional_label_keys_), std::move(tracer_provider_),
          std::move(text_map_propagator_), std::move(channel_scope_filter_)));
  return absl::OkStatus();
}

// Build the plugin without registering it globally
absl::StatusOr<std::shared_ptr<grpc::experimental::OpenTelemetryPlugin>>
OpenTelemetryPluginBuilderImpl::Build() {
  if (meter_provider_ == nullptr) {
    return absl::InvalidArgumentError(
        "Need to configure a valid meter provider.");
  }
  return std::make_shared<OpenTelemetryPluginImpl>(
      metrics_, meter_provider_, std::move(target_attribute_filter_),
      std::move(generic_method_attribute_filter_), std::move(server_selector_),
      std::move(plugin_options_), std::move(optional_label_keys_),
      std::move(tracer_provider_), std::move(text_map_propagator_),
      std::move(channel_scope_filter_));
}

// CallbackMetricReporter implementation for reporting metrics
OpenTelemetryPluginImpl::CallbackMetricReporter::CallbackMetricReporter(
    OpenTelemetryPluginImpl* ot_plugin,
    grpc_core::RegisteredMetricCallback* key)
    : ot_plugin_(ot_plugin), key_(key) {
  // Initialize caches for all metrics in the callback
  for (const auto& handle : key->metrics()) {
    const auto& descriptor =
        grpc_core::GlobalInstrumentsRegistry::GetInstrumentDescriptor(handle);
    CHECK(descriptor.instrument_type ==
          grpc_core::GlobalInstrumentsRegistry::InstrumentType::kCallbackGauge);
    switch (descriptor.value_type) {
      case grpc_core::GlobalInstrumentsRegistry::ValueType::kInt64: {
        auto& callback_gauge_state =
            std::get<std::unique_ptr<CallbackGaugeState<int64_t>>>(
                ot_plugin_->instruments_data_.at(handle.index).instrument);
        callback_gauge_state->caches[key].clear();
        break;
      }
      case grpc_core::GlobalInstrumentsRegistry::ValueType::kDouble: {
        auto& callback_gauge_state =
            std::get<std::unique_ptr<CallbackGaugeState<double>>>(
                ot_plugin_->instruments_data_.at(handle.index).instrument);
        callback_gauge_state->caches[key].clear();
        break;
      }
      default:
        grpc_core::Crash(absl::StrFormat(
            "Unknown or unsupported value type: %d", descriptor.value_type));
    }
  }
}

// Report an int64 value for a metric
void OpenTelemetryPluginImpl::CallbackMetricReporter::ReportInt64(
    grpc_core::GlobalInstrumentsRegistry::GlobalInstrumentHandle handle,
    int64_t value, absl::Span<const absl::string_view> label_values,
    absl::Span<const absl::string_view> optional_values) {
  const auto& instrument_data = ot_plugin_->instruments_data_.at(handle.index);
  auto* callback_gauge_state =
      std::get_if<std::unique_ptr<CallbackGaugeState<int64_t>>>(
          &instrument_data.instrument);
  CHECK_NE(callback_gauge_state, nullptr);
  const auto& descriptor =
      grpc_core::GlobalInstrumentsRegistry::GetInstrumentDescriptor(handle);
  CHECK(descriptor.label_keys.size() == label_values.size());
  CHECK(descriptor.optional_label_keys.size() == optional_values.size());
  
  // Check if this callback is registered for the gauge
  if ((*callback_gauge_state)->caches.find(key_) ==
      (*callback_gauge_state)->caches.end()) {
    LOG(ERROR) << "This may occur when the gauge used in AddCallback is "
                  "different from the gauge used in Report. This indicates a "
                  "misuse of the API. The value "
               << value << " will not be recorded for instrument "
               << handle.index;
    return;
  }
  
  // Build the cache key from label values
  auto& cell = (*callback_gauge_state)->caches.at(key_);
  std::vector<std::string> key;
  key.reserve(label_values.size() +
              instrument_data.optional_labels_bits.count());
  for (const absl::string_view value : label_values) {
    key.emplace_back(value);
  }
  for (size_t i = 0; i < optional_values.size(); ++i) {
    if (instrument_data.optional_labels_bits.test(i)) {
      key.emplace_back(optional_values[i]);
    }
  }
  cell.insert_or_assign(std::move(key), value);
}

// Report a double value for a metric
void OpenTelemetryPluginImpl::CallbackMetricReporter::ReportDouble(
    grpc_core::GlobalInstrumentsRegistry::GlobalInstrumentHandle handle,
    double value, absl::Span<const absl::string_view> label_values,
    absl::Span<const absl::string_view> optional_values) {
  const auto& instrument_data = ot_plugin_->instruments_data_.at(handle.index);
  auto* callback_gauge_state =
      std::get_if<std::unique_ptr<CallbackGaugeState<double>>>(
          &instrument_data.instrument);
  CHECK_NE(callback_gauge_state, nullptr);
  const auto& descriptor =
      grpc_core::GlobalInstrumentsRegistry::GetInstrumentDescriptor(handle);
  CHECK(descriptor.label_keys.size() == label_values.size());
  CHECK(descriptor.optional_label_keys.size() == optional_values.size());
  
  // Check if this callback is registered for the gauge
  if ((*callback_gauge_state)->caches.find(key_) ==
      (*callback_gauge_state)->caches.end()) {
    LOG(ERROR) << "This may occur when the gauge used in AddCallback is "
                  "different from the gauge used in Report. This indicates a "
                  "misuse of the API. The value "
               << value << " will not be recorded for instrument "
               << handle.index;
    return;
  }
  
  // Build the cache key from label values
  auto& cell = (*callback_gauge_state)->caches.at(key_);
  std::vector<std::string> key;
  key.reserve(label_values.size() +
              instrument_data.optional_labels_bits.count());
  for (const absl::string_view value : label_values) {
    key.emplace_back(value);
  }
  for (size_t i = 0; i < optional_values.size(); ++i) {
    if (instrument_data.optional_labels_bits.test(i)) {
      key.emplace_back(optional_values[i]);
    }
  }
  cell.insert_or_assign(std::move(key), value);
}

// Update channel arguments with the plugin configuration
void OpenTelemetryPluginImpl::ServerBuilderOption::UpdateArguments(
    grpc::ChannelArguments* args) {
  plugin_->AddToChannelArguments(args);
}

namespace {
// Helper function to create a tracer if provider is available
opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> MaybeMakeTracer(
    opentelemetry::trace::TracerProvider* tracer_provider) {
  if (tracer_provider == nullptr) {
    return opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer>();
  }
  return tracer_provider->GetTracer("grpc-c++", GRPC_CPP_VERSION_STRING);
}
}  // namespace

// Main implementation of OpenTelemetry plugin
OpenTelemetryPluginImpl::OpenTelemetryPluginImpl(
    const absl::flat_hash_set<std::string>& metrics,
    opentelemetry::nostd::shared_ptr<opentelemetry::metrics::MeterProvider>
        meter_provider,
    absl::AnyInvocable<bool(absl::string_view ) const>
        target_attribute_filter,
    absl::AnyInvocable