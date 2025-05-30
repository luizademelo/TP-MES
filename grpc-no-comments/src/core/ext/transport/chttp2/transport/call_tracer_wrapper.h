
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_CALL_TRACER_WRAPPER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_CALL_TRACER_WRAPPER_H

#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/call_tracer.h"

struct grpc_chttp2_stream;

namespace grpc_core {

class Chttp2CallTracerWrapper final : public CallTracerInterface {
 public:
  explicit Chttp2CallTracerWrapper(grpc_chttp2_stream* stream)
      : stream_(stream) {}

  void RecordIncomingBytes(
      const TransportByteSize& transport_byte_size) override;
  void RecordOutgoingBytes(
      const TransportByteSize& transport_byte_size) override;

  void RecordSendInitialMetadata(
      grpc_metadata_batch* ) override {}
  void RecordSendTrailingMetadata(
      grpc_metadata_batch* ) override {}
  void RecordSendMessage(const Message& ) override {}
  void RecordSendCompressedMessage(
      const Message& ) override {}
  void RecordReceivedInitialMetadata(
      grpc_metadata_batch* ) override {}
  void RecordReceivedMessage(const Message& ) override {}
  void RecordReceivedDecompressedMessage(
      const Message& ) override {}
  void RecordCancel(grpc_error_handle ) override {}
  std::shared_ptr<TcpCallTracer> StartNewTcpTrace() override { return nullptr; }
  void RecordAnnotation(absl::string_view ) override {}
  void RecordAnnotation(const Annotation& ) override {}
  std::string TraceId() override { return ""; }
  std::string SpanId() override { return ""; }
  bool IsSampled() override { return false; }

 private:
  grpc_chttp2_stream* stream_;
};

}

#endif
