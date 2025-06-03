Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header includes for gRPC and OpenCensus functionality
#include "src/cpp/ext/filters/census/server_call_tracer.h"

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>
#include <stdint.h>
#include <string.h>

#include <atomic>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Abseil libraries for string and time operations
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"

// OpenCensus libraries for metrics and tracing
#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/span_context.h"
#include "opencensus/trace/span_id.h"
#include "opencensus/trace/trace_id.h"

// gRPC core libraries
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/surface/call.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/tcp_tracer.h"

// gRPC Census filter specific headers
#include "src/cpp/ext/filters/census/context.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"
#include "src/cpp/ext/filters/census/measures.h"

namespace grpc {
namespace internal {

namespace {

// Structure to hold server metadata elements extracted from incoming requests
struct ServerMetadataElements {
  grpc_core::Slice path;            // Request path
  grpc_core::Slice tracing_slice;   // Tracing information
  grpc_core::Slice census_proto;    // Census tags information
};

// Filters and extracts relevant metadata from incoming initial metadata
void FilterInitialMetadata(grpc_metadata_batch* b,
                           ServerMetadataElements* sml) {
  // Extract path from HTTP metadata if present
  const auto* path = b->get_pointer(grpc_core::HttpPathMetadata());
  if (path != nullptr) {
    sml->path = path->Ref();
  }
  
  // Extract tracing information if tracing is enabled
  if (OpenCensusTracingEnabled()) {
    auto grpc_trace_bin = b->Take(grpc_core::GrpcTraceBinMetadata());
    if (grpc_trace_bin.has_value()) {
      sml->tracing_slice = std::move(*grpc_trace_bin);
    }
  }
  
  // Extract census tags if stats collection is enabled
  if (OpenCensusStatsEnabled()) {
    auto grpc_tags_bin = b->Take(grpc_core::GrpcTagsBinMetadata());
    if (grpc_tags_bin.has_value()) {
      sml->census_proto = std::move(*grpc_tags_bin);
    }
  }
}

}  // namespace

// Implementation of ServerCallTracer for OpenCensus integration
class OpenCensusServerCallTracer : public grpc_core::ServerCallTracer {
 public:
  // Maximum buffer size for serialized server stats
  static constexpr uint32_t kMaxServerStatsLen = 16;

  // Constructor initializes start time and message counters
  OpenCensusServerCallTracer()
      : start_time_(absl::Now()),
        recv_message_count_(0),
        sent_message_count_(0) {}

  // Returns the trace ID as a hex string
  std::string TraceId() override {
    return context_.Context().trace_id().ToHex();
  }

  // Returns the span ID as a hex string
  std::string SpanId() override { return context_.Context().span_id().ToHex(); }

  // Returns whether this span is sampled
  bool IsSampled() override { return context_.Span().IsSampled(); }

  // Placeholder for recording initial metadata (currently no-op)
  void RecordSendInitialMetadata(grpc_metadata_batch* ) override {}

  // Records sending of trailing metadata
  void RecordSendTrailingMetadata(
      grpc_metadata_batch* send_trailing_metadata) override;

  // Records sending a message and increments counter
  void RecordSendMessage(const grpc_core::Message& send_message) override {
    RecordAnnotation(absl::StrFormat("Send message: %ld bytes",
                                     send_message.payload()->Length()));
    ++sent_message_count_;
  }
  
  // Records sending a compressed message
  void RecordSendCompressedMessage(
      const grpc_core::Message& send_compressed_message) override {
    RecordAnnotation(
        absl::StrFormat("Send compressed message: %ld bytes",
                        send_compressed_message.payload()->Length()));
  }

  // Records receiving initial metadata
  void RecordReceivedInitialMetadata(
      grpc_metadata_batch* recv_initial_metadata) override;

  // Records receiving a message and increments counter
  void RecordReceivedMessage(const grpc_core::Message& recv_message) override {
    RecordAnnotation(absl::StrFormat("Received message: %ld bytes",
                                     recv_message.payload()->Length()));
    ++recv_message_count_;
  }
  
  // Records receiving a decompressed message
  void RecordReceivedDecompressedMessage(
      const grpc_core::Message& recv_decompressed_message) override {
    RecordAnnotation(
        absl::StrFormat("Received decompressed message: %ld bytes",
                        recv_decompressed_message.payload()->Length()));
  }

  // Placeholder for recording trailing metadata (currently no-op)
  void RecordReceivedTrailingMetadata(grpc_metadata_batch* ) override {}

  // Records cancellation of the call and updates elapsed time
  void RecordCancel(grpc_error_handle ) override {
    elapsed_time_ = absl::Now() - start_time_;
  }

  // Records call end with final info
  void RecordEnd(const grpc_call_final_info* final_info) override;

  // Records incoming bytes count
  void RecordIncomingBytes(const TransportByteSize& transport_byte_size) override;
  
  // Records outgoing bytes count
  void RecordOutgoingBytes(const TransportByteSize& transport_byte_size) override;

  // Records a text annotation if the span is being recorded
  void RecordAnnotation(absl::string_view annotation) override {
    if (!context_.Span().IsRecording()) {
      return;
    }
    context_.AddSpanAnnotation(annotation, {});
  }

  // Records a structured annotation if the span is being recorded
  void RecordAnnotation(const Annotation& annotation) override {
    if (!context_.Span().IsRecording()) {
      return;
    }

    switch (annotation.type()) {
      default:
        if (IsSampled()) {
          context_.AddSpanAnnotation(annotation.ToString(), {});
        }
        break;
    }
  }
  
  // Placeholder for TCP tracing (returns nullptr as not implemented)
  std::shared_ptr<grpc_core::TcpCallTracer> StartNewTcpTrace() override {
    return nullptr;
  }

 private:
  experimental::CensusContext context_;  // OpenCensus context for this call

  grpc_core::Slice path_;        // Request path
  absl::string_view method_;     // Method name derived from path

  absl::Time start_time_;        // Call start time
  absl::Duration elapsed_time_;  // Time since call started
  uint64_t recv_message_count_;  // Count of received messages
  uint64_t sent_message_count_;  // Count of sent messages

  char stats_buf_[kMaxServerStatsLen];  // Buffer for serialized stats

  // Atomic counters for byte tracking
  std::atomic<uint64_t> incoming_bytes_{0};
  std::atomic<uint64_t> outgoing_bytes_{0};
};

// Implementation of RecordReceivedInitialMetadata
void OpenCensusServerCallTracer::RecordReceivedInitialMetadata(
    grpc_metadata_batch* recv_initial_metadata) {
  ServerMetadataElements sml;
  FilterInitialMetadata(recv_initial_metadata, &sml);
  path_ = std::move(sml.path);
  method_ = GetMethod(path_);
  
  // Generate server context if tracing is enabled
  auto tracing_enabled = OpenCensusTracingEnabled();
  GenerateServerContext(
      tracing_enabled ? sml.tracing_slice.as_string_view() : "",
      absl::StrCat("Recv.", method_), &context_);
  
  // Set context if tracing is enabled
  if (tracing_enabled) {
    grpc_core::SetContext<census_context>(
        reinterpret_cast<census_context*>(&context_));
  }
  
  // Record server started RPC if stats are enabled
  if (OpenCensusStatsEnabled()) {
    std::vector<std::pair<opencensus::tags::TagKey, std::string>> tags =
        context_.tags().tags();
    tags.emplace_back(ServerMethodTagKey(), std::string(method_));
    ::opencensus::stats::Record({{RpcServerStartedRpcs(), 1}}, tags);
  }
}

// Implementation of RecordSendTrailingMetadata
void OpenCensusServerCallTracer::RecordSendTrailingMetadata(
    grpc_metadata_batch* send_trailing_metadata) {
  // Update elapsed time
  elapsed_time_ = absl::Now() - start_time_;
  
  // If stats are enabled, serialize server stats to trailing metadata
  if (OpenCensusStatsEnabled() && send_trailing_metadata != nullptr) {
    size_t len = ServerStatsSerialize(absl::ToInt64Nanoseconds(elapsed_time_),
                                      stats_buf_, kMaxServerStatsLen);
    if (len > 0) {
      send_trailing_metadata->Set(
          grpc_core::GrpcServerStatsBinMetadata(),
          grpc_core::Slice::FromCopiedBuffer(stats_buf_, len));
    }
  }
}

// Implementation of RecordEnd
void OpenCensusServerCallTracer::RecordEnd(
    const grpc_call_final_info* final_info) {
  // Record various metrics if stats are enabled
  if (OpenCensusStatsEnabled()) {
    uint64_t outgoing_bytes;
    uint64_t incoming_bytes;
    
    // Get byte counts based on transport tracing availability
    if (grpc_core::IsCallTracerInTransportEnabled()) {
      outgoing_bytes = outgoing_bytes_.load();
      incoming_bytes = incoming_bytes_.load();
    } else {
      // Note: We are incorrectly swapping the two values here, which is
      // a known issue
      outgoing_bytes = GetIncomingDataSize(final_info);
      incoming_bytes = GetOutgoingDataSize(final_info);
    }
    
    // Calculate elapsed time in milliseconds
    double elapsed_time_ms = absl::ToDoubleMilliseconds(elapsed_time_);
    
    // Prepare tags for metrics recording
    std::vector<std::pair<opencensus::tags::TagKey, std::string>> tags =
        context_.tags().tags();
    tags.emplace_back(ServerMethodTagKey(), std::string(method_));
    tags.emplace_back(
        ServerStatusTagKey(),
        std::string(StatusCodeToString(final_info->final_status)));
        
    // Record all metrics
    ::opencensus::stats::Record(
        {{RpcServerSentBytesPerRpc(), static_cast<double>(outgoing_bytes)},
         {RpcServerReceivedBytesPerRpc(), static_cast<double>(incoming_bytes)},
         {RpcServerServerLatency(), elapsed_time_ms},
         {RpcServerSentMessagesPerRpc(), sent_message_count_},
         {RpcServerReceivedMessagesPerRpc(), recv_message_count_}},
        tags);
  }
  
  // End the span if tracing is enabled
  if (OpenCensusTracingEnabled()) {
    context_.EndSpan();
  }
}

// Implementation of RecordIncomingBytes
void OpenCensusServerCallTracer::RecordIncomingBytes(
    const TransportByteSize& transport_byte_size) {
  incoming_bytes_.fetch_add(transport_byte_size.data_bytes);
}

// Implementation of RecordOutgoingBytes
void OpenCensusServerCallTracer::RecordOutgoingBytes(
    const TransportByteSize& transport_byte_size) {
  outgoing_bytes_.fetch_add(transport_byte_size.data_bytes);
}

// Factory method to create new server call tracers
grpc_core::ServerCallTracer*
OpenCensusServerCallTracerFactory::CreateNewServerCallTracer(
    grpc_core::Arena* arena, const grpc_core::ChannelArgs& ) {
  return arena->ManagedNew<OpenCensusServerCallTracer>();
}

}  // namespace internal
}  // namespace grpc
```