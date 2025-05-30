
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_OPEN_CENSUS_CALL_TRACER_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_OPEN_CENSUS_CALL_TRACER_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <grpcpp/opencensus.h>
#include <stdint.h>

#include <atomic>
#include <memory>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/span_context.h"
#include "opencensus/trace/span_id.h"
#include "opencensus/trace/trace_id.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/tcp_tracer.h"
#include "src/core/util/sync.h"

#define GRPC_ARG_ENABLE_OBSERVABILITY "grpc.experimental.enable_observability"

namespace grpc {
namespace internal {

class OpenCensusCallTracer : public grpc_core::ClientCallTracer {
 public:
  class OpenCensusCallAttemptTracer : public CallAttemptTracer {
   public:
    OpenCensusCallAttemptTracer(OpenCensusCallTracer* parent,
                                uint64_t attempt_num, bool is_transparent_retry,
                                bool arena_allocated);

    std::string TraceId() override {
      return context_.Context().trace_id().ToHex();
    }

    std::string SpanId() override {
      return context_.Context().span_id().ToHex();
    }

    bool IsSampled() override { return context_.Span().IsSampled(); }

    void RecordSendInitialMetadata(
        grpc_metadata_batch* send_initial_metadata) override;
    void RecordSendTrailingMetadata(
        grpc_metadata_batch* ) override {}
    void RecordSendMessage(const grpc_core::Message& send_message) override;
    void RecordSendCompressedMessage(
        const grpc_core::Message& send_compressed_message) override;
    void RecordReceivedInitialMetadata(
        grpc_metadata_batch* ) override {}
    void RecordReceivedMessage(const grpc_core::Message& recv_message) override;
    void RecordReceivedDecompressedMessage(
        const grpc_core::Message& recv_decompressed_message) override;
    void RecordReceivedTrailingMetadata(
        absl::Status status, grpc_metadata_batch* recv_trailing_metadata,
        const grpc_transport_stream_stats* transport_stream_stats) override;
    void RecordIncomingBytes(
        const TransportByteSize& transport_byte_size) override;
    void RecordOutgoingBytes(
        const TransportByteSize& transport_byte_size) override;
    void RecordCancel(grpc_error_handle cancel_error) override;
    void RecordEnd() override;
    void RecordAnnotation(absl::string_view annotation) override;
    void RecordAnnotation(const Annotation& annotation) override;
    std::shared_ptr<grpc_core::TcpCallTracer> StartNewTcpTrace() override;
    void SetOptionalLabel(OptionalLabelKey,
                          grpc_core::RefCountedStringValue) override {}

    experimental::CensusContext* context() { return &context_; }

   private:

    static constexpr uint32_t kMaxTraceContextLen = 64;

    static constexpr uint32_t kMaxTagsLen = 2048;
    OpenCensusCallTracer* parent_;
    const bool arena_allocated_;
    experimental::CensusContext context_;

    absl::Time start_time_;

    uint64_t recv_message_count_ = 0;
    uint64_t sent_message_count_ = 0;

    absl::StatusCode status_code_;

    std::atomic<uint64_t> incoming_bytes_{0};
    std::atomic<uint64_t> outgoing_bytes_{0};
  };

  explicit OpenCensusCallTracer(grpc_core::Slice path, grpc_core::Arena* arena,
                                bool tracing_enabled);
  ~OpenCensusCallTracer() override;

  std::string TraceId() override {
    return context_.Context().trace_id().ToHex();
  }

  std::string SpanId() override { return context_.Context().span_id().ToHex(); }

  bool IsSampled() override { return context_.Span().IsSampled(); }

  void GenerateContext();
  OpenCensusCallAttemptTracer* StartNewAttempt(
      bool is_transparent_retry) override;
  void RecordAnnotation(absl::string_view annotation) override;
  void RecordAnnotation(const Annotation& annotation) override;

  void RecordApiLatency(absl::Duration api_latency,
                        absl::StatusCode status_code_);

 private:
  experimental::CensusContext CreateCensusContextForCallAttempt();

  grpc_core::Slice path_;
  absl::string_view method_;
  experimental::CensusContext context_;
  grpc_core::Arena* arena_;
  const bool tracing_enabled_;
  grpc_core::Mutex mu_;

  uint64_t retries_ ABSL_GUARDED_BY(&mu_) = 0;

  uint64_t transparent_retries_ ABSL_GUARDED_BY(&mu_) = 0;

  absl::Duration retry_delay_ ABSL_GUARDED_BY(&mu_);
  absl::Time time_at_last_attempt_end_ ABSL_GUARDED_BY(&mu_);
  uint64_t num_active_rpcs_ ABSL_GUARDED_BY(&mu_) = 0;
};

}
}

#endif
