Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/otel/otel_server_call_tracer.h"

#include <grpc/support/port_platform.h>

#include <array>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "absl/types/span.h"
#include "opentelemetry/context/context.h"
#include "opentelemetry/metrics/sync_instruments.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/status_util.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/event_engine/utils.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/tcp_tracer.h"
#include "src/cpp/ext/otel/key_value_iterable.h"
#include "src/cpp/ext/otel/otel_plugin.h"

namespace grpc {
namespace internal {

// TcpCallTracer is a wrapper around ServerCallTracer that implements TCP-level
// tracing functionality
class OpenTelemetryPluginImpl::ServerCallTracer::TcpCallTracer
    : public grpc_core::TcpCallTracer {
 public:
  // Constructor takes a reference to the parent ServerCallTracer
  explicit TcpCallTracer(
      grpc_core::RefCountedPtr<OpenTelemetryPluginImpl::ServerCallTracer>
          server_call_tracer)
      : server_call_tracer_(server_call_tracer) {
    // Take an internal reference to the call object in the arena
    server_call_tracer_->arena_->GetContext<grpc_core::Call>()->InternalRef(
        "OpenTelemetryPluginImpl::ServerCallTracer::TcpCallTracer");
  }

  // Destructor releases the internal reference to the call object
  ~TcpCallTracer() override {
    server_call_tracer_->arena_->GetContext<grpc_core::Call>()->InternalUnref(
        "OpenTelemetryPluginImpl::ServerCallTracer::TcpCallTracer");
  }

  // Records TCP events and forwards them to the parent ServerCallTracer as annotations
  void RecordEvent(grpc_event_engine::experimental::internal::WriteEvent type,
                   absl::Time time, size_t byte_offset,
                   std::vector<TcpEventMetric> metrics) override {
    server_call_tracer_->RecordAnnotation(
        absl::StrCat(
            "TCP: ", grpc_event_engine::experimental::WriteEventToString(type),
            " byte_offset=", byte_offset, " ",
            grpc_core::TcpCallTracer::TcpEventMetricsToString(metrics)),
        time);
  }

 private:
  // Reference to the parent ServerCallTracer
  grpc_core::RefCountedPtr<OpenTelemetryPluginImpl::ServerCallTracer>
      server_call_tracer_;
};

// ServerCallTracer constructor initializes OpenTelemetry tracing for server calls
OpenTelemetryPluginImpl::ServerCallTracer::ServerCallTracer(
    OpenTelemetryPluginImpl* otel_plugin, grpc_core::Arena* arena,
    std::shared_ptr<OpenTelemetryPluginImpl::ServerScopeConfig> scope_config)
    : start_time_(absl::Now()),  // Record start time of the call
      injected_labels_from_plugin_options_(
          otel_plugin->plugin_options().size()),  // Initialize label storage
      otel_plugin_(otel_plugin),  // Store reference to OpenTelemetry plugin
      arena_(arena),  // Store reference to call arena
      scope_config_(std::move(scope_config)) {}  // Store scope configuration

// ServerCallTracer destructor ensures the span is properly ended
OpenTelemetryPluginImpl::ServerCallTracer::~ServerCallTracer() {
  if (span_ != nullptr) {
    span_->End();  // End the OpenTelemetry span if it exists
  }
}

// Records received initial metadata and starts tracing if configured
void OpenTelemetryPluginImpl::ServerCallTracer::RecordReceivedInitialMetadata(
    grpc_metadata_batch* recv_initial_metadata) {
  // Extract and store the HTTP path from metadata
  path_ =
      recv_initial_metadata->get_pointer(grpc_core::HttpPathMetadata())->Ref();
  
  // Process plugin options to extract and store labels from metadata
  scope_config_->active_plugin_options_view().ForEach(
      [&](const InternalOpenTelemetryPluginOption& plugin_option,
          size_t index) {
        auto* labels_injector = plugin_option.labels_injector();
        if (labels_injector != nullptr) {
          injected_labels_from_plugin_options_[index] =
              labels_injector->GetLabels(recv_initial_metadata);
        }
        return true;
      },
      otel_plugin_);
  
  // Check if this is a registered method
  registered_method_ =
      recv_initial_metadata->get(grpc_core::GrpcRegisteredMethod())
          .value_or(nullptr) != nullptr;
  
  // Prepare labels for metrics
  std::array<std::pair<absl::string_view, absl::string_view>, 1>
      additional_labels = {{{OpenTelemetryMethodKey(), MethodForStats()}}};
  
  // Record call started metric if configured
  if (otel_plugin_->server_.call.started != nullptr) {
    otel_plugin_->server_.call.started->Add(
        1, KeyValueIterable({},
                            additional_labels,
                            nullptr, {},
                            false, otel_plugin_));
  }
  
  // Start OpenTelemetry span if tracing is enabled
  if (otel_plugin_->tracer_ != nullptr) {
    GrpcTextMapCarrier carrier(recv_initial_metadata);
    opentelemetry::context::Context context;
    // Extract context from incoming metadata
    context = otel_plugin_->text_map_propagator_->Extract(carrier, context);
    opentelemetry::trace::StartSpanOptions options;
    options.parent = context;
    // Create span with method name from path
    span_ = otel_plugin_->tracer_->StartSpan(
        absl::StrCat("Recv.", GetMethodFromPath(path_)), options);

    // Store span in census context
    grpc_core::SetContext<census_context>(
        reinterpret_cast<census_context*>(span_.get()));
  }
}

// Records a received message event in the span
void OpenTelemetryPluginImpl::ServerCallTracer::RecordReceivedMessage(
    const grpc_core::Message& recv_message) {
  if (span_ != nullptr) {
    // Prepare attributes for the event
    std::array<std::pair<opentelemetry::nostd::string_view,
                         opentelemetry::common::AttributeValue>,
               2>
        attributes = {
            std::pair("sequence-number",
                      opentelemetry::common::AttributeValue(recv_seq_num_++)),
            std::pair(recv_message.flags() & GRPC_WRITE_INTERNAL_COMPRESS
                          ? "message-size-compressed"
                          : "message-size",
                      opentelemetry::common::AttributeValue(
                          recv_message.payload()->Length()))};
    // Add event to span with appropriate type based on compression
    span_->AddEvent(recv_message.flags() & GRPC_WRITE_INTERNAL_COMPRESS
                        ? "Inbound compressed message"
                        : "Inbound message",
                    attributes);
  }
}

// Records a received decompressed message event in the span
void OpenTelemetryPluginImpl::ServerCallTracer::
    RecordReceivedDecompressedMessage(
        const grpc_core::Message& recv_decompressed_message) {
  if (span_ != nullptr) {
    // Prepare attributes for the event
    std::array<std::pair<opentelemetry::nostd::string_view,
                         opentelemetry::common::AttributeValue>,
               2>
        attributes = {
            std::pair("sequence-number",
                      opentelemetry::common::AttributeValue(recv_seq_num_ - 1)),
            std::pair("message-size",
                      opentelemetry::common::AttributeValue(
                          recv_decompressed_message.payload()->Length()))};
    // Add event to span
    span_->AddEvent("Inbound message", attributes);
  }
}

// Processes and injects labels into outgoing initial metadata
void OpenTelemetryPluginImpl::ServerCallTracer::RecordSendInitialMetadata(
    grpc_metadata_batch* send_initial_metadata) {
  scope_config_->active_plugin_options_view().ForEach(
      [&](const InternalOpenTelemetryPluginOption& plugin_option,
          size_t index) {
        auto* labels_injector = plugin_option.labels_injector();
        if (labels_injector != nullptr) {
          labels_injector->AddLabels(
              send_initial_metadata,
              injected_labels_from_plugin_options_[index].get());
        }
        return true;
      },
      otel_plugin_);
}

// Records a sent message event in the span
void OpenTelemetryPluginImpl::ServerCallTracer::RecordSendMessage(
    const grpc_core::Message& send_message) {
  if (span_ != nullptr) {
    // Prepare attributes for the event
    std::array<std::pair<opentelemetry::nostd::string_view,
                         opentelemetry::common::AttributeValue>,
               2>
        attributes = {
            std::pair("sequence-number", send_seq_num_++),
            std::pair("message-size", send_message.payload()->Length())};
    // Add event to span
    span_->AddEvent("Outbound message", attributes);
  }
}

// Records a sent compressed message event in the span
void OpenTelemetryPluginImpl::ServerCallTracer::RecordSendCompressedMessage(
    const grpc_core::Message& send_compressed_message) {
  if (span_ != nullptr) {
    // Prepare attributes for the event
    std::array<std::pair<opentelemetry::nostd::string_view,
                         opentelemetry::common::AttributeValue>,
               2>
        attributes = {
            std::pair("sequence-number",
                      opentelemetry::common::AttributeValue(send_seq_num_ - 1)),
            std::pair("message-size-compressed",
                      opentelemetry::common::AttributeValue(
                          send_compressed_message.payload()->Length()))};
    // Add event to span
    span_->AddEvent("Outbound message compressed", attributes);
  }
}

// Records the sending of trailing metadata and calculates elapsed time
void OpenTelemetryPluginImpl::ServerCallTracer::RecordSendTrailingMetadata(
    grpc_metadata_batch* ) {
  elapsed_time_ = absl::Now() - start_time_;  // Calculate total call duration
}

// Records call completion with final status and metrics
void OpenTelemetryPluginImpl::ServerCallTracer::RecordEnd(
    const grpc_call_final_info* final_info) {
  // Prepare labels for metrics including method and status
  std::array<std::pair<absl::string_view, absl::string_view>, 2>
      additional_labels = {
          {{OpenTelemetryMethodKey(), MethodForStats()},
           {OpenTelemetryStatusKey(),
            grpc_status_code_to_string(final_info->final_status)}}};

  KeyValueIterable labels(
      injected_labels_from_plugin_options_, additional_labels,
      nullptr, {},
      false, otel_plugin_);
  
  // Record call duration metric if configured
  if (otel_plugin_->server_.call.duration != nullptr) {
    otel_plugin_->server_.call.duration->Record(
        absl::ToDoubleSeconds(elapsed_time_), labels,
        opentelemetry::context::Context{});
  }
  
  // Record total sent compressed message size metric if configured
  if (otel_plugin_->server_.call.sent_total_compressed_message_size !=
      nullptr) {
    otel_plugin_->server_.call.sent_total_compressed_message_size->Record(
        grpc_core::IsCallTracerInTransportEnabled()
            ? outgoing_bytes_.load()
            : final_info->stats.transport_stream_stats.outgoing.data_bytes,
        labels, opentelemetry::context::Context{});
  }
  
  // Record total received compressed message size metric if configured
  if (otel_plugin_->server_.call.rcvd_total_compressed_message_size !=
      nullptr) {
    otel_plugin_->server_.call.rcvd_total_compressed_message_size->Record(
        grpc_core::IsCallTracerInTransportEnabled()
            ? incoming_bytes_.load()
            : final_info->stats.transport_stream_stats.incoming.data_bytes,
        labels, opentelemetry::context::Context{});
  }
  
  // Finalize the span with appropriate status
  if (span_ != nullptr) {
    if (final_info->final_status == GRPC_STATUS_OK) {
      span_->SetStatus(opentelemetry::trace::StatusCode::kOk);
    } else {
      span_->SetStatus(
          opentelemetry::trace::StatusCode::kError,
          absl::Status(static_cast<absl::StatusCode>(final_info->final_status),
                       final_info->error_string)
              .ToString());
    }
  }
  Unref(DEBUG_LOCATION, "RecordEnd");
}

// Records incoming bytes for transport-level metrics
void OpenTelemetryPluginImpl::ServerCallTracer::RecordIncomingBytes(
    const TransportByteSize& transport_byte_size) {
  incoming_bytes_.fetch_add(transport_byte_size.data_bytes);
}

// Records outgoing bytes for transport-level metrics
void OpenTelemetryPluginImpl::ServerCallTracer::RecordOutgoingBytes(
    const TransportByteSize& transport_byte_size) {
  outgoing_bytes_.fetch_add(transport_byte_size.data_bytes);
}

// Records a generic annotation in the span
void OpenTelemetryPluginImpl::ServerCallTracer::RecordAnnotation(
    absl::string_view annotation) {
  if (span_ != nullptr) {
    span_->AddEvent(AbslStringViewToNoStdStringView(annotation));
  }
}

// Records a timestamped annotation in the span
void OpenTelemetryPluginImpl::ServerCallTracer::RecordAnnotation(
    absl::string_view annotation, absl::Time time) {
  if (span_ != nullptr) {
    span_->AddEvent(AbslStringViewToNoStdStringView(annotation),
                    absl::ToChronoTime(time));
  }
}

// Creates a new TCP tracer instance if tracing is enabled
std::shared_ptr<grpc_core::TcpCallTracer>
OpenTelemetryPluginImpl::ServerCallTracer::StartNewTcpTrace() {
  if (span_ != nullptr) {
    return std::make_shared<TcpCallTracer>(
        Ref(DEBUG_LOCATION, "StartNewTcpTrace"));
  }
  return nullptr;
}

}
}
```