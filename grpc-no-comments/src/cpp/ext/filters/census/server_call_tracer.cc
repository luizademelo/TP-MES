
// Copyright 2018 gRPC authors.

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

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/span_context.h"
#include "opencensus/trace/span_id.h"
#include "opencensus/trace/trace_id.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/surface/call.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/tcp_tracer.h"
#include "src/cpp/ext/filters/census/context.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"
#include "src/cpp/ext/filters/census/measures.h"

namespace grpc {
namespace internal {

namespace {

struct ServerMetadataElements {
  grpc_core::Slice path;
  grpc_core::Slice tracing_slice;
  grpc_core::Slice census_proto;
};

void FilterInitialMetadata(grpc_metadata_batch* b,
                           ServerMetadataElements* sml) {
  const auto* path = b->get_pointer(grpc_core::HttpPathMetadata());
  if (path != nullptr) {
    sml->path = path->Ref();
  }
  if (OpenCensusTracingEnabled()) {
    auto grpc_trace_bin = b->Take(grpc_core::GrpcTraceBinMetadata());
    if (grpc_trace_bin.has_value()) {
      sml->tracing_slice = std::move(*grpc_trace_bin);
    }
  }
  if (OpenCensusStatsEnabled()) {
    auto grpc_tags_bin = b->Take(grpc_core::GrpcTagsBinMetadata());
    if (grpc_tags_bin.has_value()) {
      sml->census_proto = std::move(*grpc_tags_bin);
    }
  }
}

}

class OpenCensusServerCallTracer : public grpc_core::ServerCallTracer {
 public:

  static constexpr uint32_t kMaxServerStatsLen = 16;

  OpenCensusServerCallTracer()
      : start_time_(absl::Now()),
        recv_message_count_(0),
        sent_message_count_(0) {}

  std::string TraceId() override {
    return context_.Context().trace_id().ToHex();
  }

  std::string SpanId() override { return context_.Context().span_id().ToHex(); }

  bool IsSampled() override { return context_.Span().IsSampled(); }

  void RecordSendInitialMetadata(
      grpc_metadata_batch* ) override {}

  void RecordSendTrailingMetadata(
      grpc_metadata_batch* send_trailing_metadata) override;

  void RecordSendMessage(const grpc_core::Message& send_message) override {
    RecordAnnotation(absl::StrFormat("Send message: %ld bytes",
                                     send_message.payload()->Length()));
    ++sent_message_count_;
  }
  void RecordSendCompressedMessage(
      const grpc_core::Message& send_compressed_message) override {
    RecordAnnotation(
        absl::StrFormat("Send compressed message: %ld bytes",
                        send_compressed_message.payload()->Length()));
  }

  void RecordReceivedInitialMetadata(
      grpc_metadata_batch* recv_initial_metadata) override;

  void RecordReceivedMessage(const grpc_core::Message& recv_message) override {
    RecordAnnotation(absl::StrFormat("Received message: %ld bytes",
                                     recv_message.payload()->Length()));
    ++recv_message_count_;
  }
  void RecordReceivedDecompressedMessage(
      const grpc_core::Message& recv_decompressed_message) override {
    RecordAnnotation(
        absl::StrFormat("Received decompressed message: %ld bytes",
                        recv_decompressed_message.payload()->Length()));
  }

  void RecordReceivedTrailingMetadata(
      grpc_metadata_batch* ) override {}

  void RecordCancel(grpc_error_handle ) override {
    elapsed_time_ = absl::Now() - start_time_;
  }

  void RecordEnd(const grpc_call_final_info* final_info) override;

  void RecordIncomingBytes(
      const TransportByteSize& transport_byte_size) override;
  void RecordOutgoingBytes(
      const TransportByteSize& transport_byte_size) override;

  void RecordAnnotation(absl::string_view annotation) override {
    if (!context_.Span().IsRecording()) {
      return;
    }
    context_.AddSpanAnnotation(annotation, {});
  }

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
  std::shared_ptr<grpc_core::TcpCallTracer> StartNewTcpTrace() override {
    return nullptr;
  }

 private:
  experimental::CensusContext context_;

  grpc_core::Slice path_;
  absl::string_view method_;

  absl::Time start_time_;
  absl::Duration elapsed_time_;
  uint64_t recv_message_count_;
  uint64_t sent_message_count_;

  char stats_buf_[kMaxServerStatsLen];

  std::atomic<uint64_t> incoming_bytes_{0};
  std::atomic<uint64_t> outgoing_bytes_{0};
};

void OpenCensusServerCallTracer::RecordReceivedInitialMetadata(
    grpc_metadata_batch* recv_initial_metadata) {
  ServerMetadataElements sml;
  FilterInitialMetadata(recv_initial_metadata, &sml);
  path_ = std::move(sml.path);
  method_ = GetMethod(path_);
  auto tracing_enabled = OpenCensusTracingEnabled();
  GenerateServerContext(
      tracing_enabled ? sml.tracing_slice.as_string_view() : "",
      absl::StrCat("Recv.", method_), &context_);
  if (tracing_enabled) {
    grpc_core::SetContext<census_context>(
        reinterpret_cast<census_context*>(&context_));
  }
  if (OpenCensusStatsEnabled()) {
    std::vector<std::pair<opencensus::tags::TagKey, std::string>> tags =
        context_.tags().tags();
    tags.emplace_back(ServerMethodTagKey(), std::string(method_));
    ::opencensus::stats::Record({{RpcServerStartedRpcs(), 1}}, tags);
  }
}

void OpenCensusServerCallTracer::RecordSendTrailingMetadata(
    grpc_metadata_batch* send_trailing_metadata) {

  elapsed_time_ = absl::Now() - start_time_;
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

void OpenCensusServerCallTracer::RecordEnd(
    const grpc_call_final_info* final_info) {
  if (OpenCensusStatsEnabled()) {
    uint64_t outgoing_bytes;
    uint64_t incoming_bytes;
    if (grpc_core::IsCallTracerInTransportEnabled()) {
      outgoing_bytes = outgoing_bytes_.load();
      incoming_bytes = incoming_bytes_.load();
    } else {
      // Note: We are incorrectly swapping the two values here, which is

      outgoing_bytes = GetIncomingDataSize(final_info);
      incoming_bytes = GetOutgoingDataSize(final_info);
    }
    double elapsed_time_ms = absl::ToDoubleMilliseconds(elapsed_time_);
    std::vector<std::pair<opencensus::tags::TagKey, std::string>> tags =
        context_.tags().tags();
    tags.emplace_back(ServerMethodTagKey(), std::string(method_));
    tags.emplace_back(
        ServerStatusTagKey(),
        std::string(StatusCodeToString(final_info->final_status)));
    ::opencensus::stats::Record(
        {{RpcServerSentBytesPerRpc(), static_cast<double>(outgoing_bytes)},
         {RpcServerReceivedBytesPerRpc(), static_cast<double>(incoming_bytes)},
         {RpcServerServerLatency(), elapsed_time_ms},
         {RpcServerSentMessagesPerRpc(), sent_message_count_},
         {RpcServerReceivedMessagesPerRpc(), recv_message_count_}},
        tags);
  }
  if (OpenCensusTracingEnabled()) {
    context_.EndSpan();
  }
}

void OpenCensusServerCallTracer::RecordIncomingBytes(
    const TransportByteSize& transport_byte_size) {
  incoming_bytes_.fetch_add(transport_byte_size.data_bytes);
}

void OpenCensusServerCallTracer::RecordOutgoingBytes(
    const TransportByteSize& transport_byte_size) {
  outgoing_bytes_.fetch_add(transport_byte_size.data_bytes);
}

grpc_core::ServerCallTracer*
OpenCensusServerCallTracerFactory::CreateNewServerCallTracer(
    grpc_core::Arena* arena, const grpc_core::ChannelArgs& ) {
  return arena->ManagedNew<OpenCensusServerCallTracer>();
}

}
}
