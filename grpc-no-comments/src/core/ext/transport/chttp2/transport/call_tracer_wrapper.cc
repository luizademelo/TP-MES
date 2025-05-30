
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"

#include "src/core/ext/transport/chttp2/transport/internal.h"

namespace grpc_core {

void Chttp2CallTracerWrapper::RecordIncomingBytes(
    const CallTracerInterface::TransportByteSize& transport_byte_size) {

  stream_->stats.incoming.framing_bytes += transport_byte_size.framing_bytes;
  stream_->stats.incoming.data_bytes += transport_byte_size.data_bytes;
  stream_->stats.incoming.header_bytes += transport_byte_size.header_bytes;

  if (!IsCallTracerInTransportEnabled()) return;
  auto* call_tracer = stream_->call_tracer;
  if (call_tracer != nullptr) {
    call_tracer->RecordIncomingBytes(transport_byte_size);
  }
}

void Chttp2CallTracerWrapper::RecordOutgoingBytes(
    const CallTracerInterface::TransportByteSize& transport_byte_size) {

  stream_->stats.outgoing.framing_bytes += transport_byte_size.framing_bytes;
  stream_->stats.outgoing.data_bytes += transport_byte_size.data_bytes;
  stream_->stats.outgoing.header_bytes +=
      transport_byte_size.header_bytes;
  if (!IsCallTracerInTransportEnabled()) return;
  auto* call_tracer = stream_->call_tracer;
  if (call_tracer != nullptr) {
    call_tracer->RecordOutgoingBytes(transport_byte_size);
  }
}

}