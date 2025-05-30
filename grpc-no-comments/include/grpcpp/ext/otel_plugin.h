
// Copyright 2023 gRPC authors.

#ifndef GRPCPP_EXT_OTEL_PLUGIN_H
#define GRPCPP_EXT_OTEL_PLUGIN_H

#include <grpc/support/metrics.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/channel_arguments.h>
#include <stddef.h>
#include <stdint.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/metrics/meter_provider.h"
#include "opentelemetry/trace/tracer_provider.h"

namespace grpc {
namespace internal {
class OpenTelemetryPluginBuilderImpl;
}

class OpenTelemetryPluginOption {
 public:
  virtual ~OpenTelemetryPluginOption() = default;
};

namespace experimental {

class OpenTelemetryPlugin {
 public:
  virtual ~OpenTelemetryPlugin() = default;

  virtual void AddToChannelArguments(grpc::ChannelArguments* args) = 0;

  virtual void AddToServerBuilder(grpc::ServerBuilder* builder) = 0;
};
}

class OpenTelemetryPluginBuilder {
 public:
  using ChannelScope = grpc_core::experimental::StatsPluginChannelScope;

  static constexpr absl::string_view kClientAttemptStartedInstrumentName =
      "grpc.client.attempt.started";
  static constexpr absl::string_view kClientAttemptDurationInstrumentName =
      "grpc.client.attempt.duration";
  static constexpr absl::string_view
      kClientAttemptSentTotalCompressedMessageSizeInstrumentName =
          "grpc.client.attempt.sent_total_compressed_message_size";
  static constexpr absl::string_view
      kClientAttemptRcvdTotalCompressedMessageSizeInstrumentName =
          "grpc.client.attempt.rcvd_total_compressed_message_size";
  static constexpr absl::string_view kServerCallStartedInstrumentName =
      "grpc.server.call.started";
  static constexpr absl::string_view kServerCallDurationInstrumentName =
      "grpc.server.call.duration";
  static constexpr absl::string_view
      kServerCallSentTotalCompressedMessageSizeInstrumentName =
          "grpc.server.call.sent_total_compressed_message_size";
  static constexpr absl::string_view
      kServerCallRcvdTotalCompressedMessageSizeInstrumentName =
          "grpc.server.call.rcvd_total_compressed_message_size";

  OpenTelemetryPluginBuilder();
  ~OpenTelemetryPluginBuilder();

  OpenTelemetryPluginBuilder& SetMeterProvider(
      std::shared_ptr<opentelemetry::metrics::MeterProvider> meter_provider);

  GRPC_DEPRECATED(
      "Does not work as expected. Please raise an issue on "
      "https://github.com/grpc/grpc if this would be of use to you.")
  OpenTelemetryPluginBuilder& SetTargetAttributeFilter(
      absl::AnyInvocable<bool(absl::string_view ) const>
          target_attribute_filter);

  OpenTelemetryPluginBuilder& SetGenericMethodAttributeFilter(
      absl::AnyInvocable<bool(absl::string_view ) const>
          generic_method_attribute_filter);

  OpenTelemetryPluginBuilder& EnableMetrics(
      absl::Span<const absl::string_view> metric_names);
  OpenTelemetryPluginBuilder& DisableMetrics(
      absl::Span<const absl::string_view> metric_names);
  OpenTelemetryPluginBuilder& DisableAllMetrics();

  OpenTelemetryPluginBuilder& AddPluginOption(
      std::unique_ptr<OpenTelemetryPluginOption> option);

  OpenTelemetryPluginBuilder& AddOptionalLabel(
      absl::string_view optional_label_key);

  OpenTelemetryPluginBuilder& SetTracerProvider(
      std::shared_ptr<opentelemetry::trace::TracerProvider> tracer_provider);

  OpenTelemetryPluginBuilder& SetTextMapPropagator(
      std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>
          text_map_propagator);

  static std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>
  MakeGrpcTraceBinTextMapPropagator();

  OpenTelemetryPluginBuilder& SetChannelScopeFilter(
      absl::AnyInvocable<bool(const ChannelScope& ) const>
          channel_scope_filter);

  absl::Status BuildAndRegisterGlobal();

  GRPC_MUST_USE_RESULT
  absl::StatusOr<std::shared_ptr<experimental::OpenTelemetryPlugin>> Build();

 private:
  std::unique_ptr<internal::OpenTelemetryPluginBuilderImpl> impl_;
};

namespace experimental {

GRPC_DEPRECATED(
    "Use grpc::OpenTelemetryPluginBuilder instead. The experimental version "
    "will be deleted after the 1.62 release.")
typedef grpc::OpenTelemetryPluginBuilder OpenTelemetryPluginBuilder;
}

}

#endif
