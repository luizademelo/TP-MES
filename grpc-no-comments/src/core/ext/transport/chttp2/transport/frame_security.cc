
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame_security.h"

#include <cstddef>
#include <cstdint>

#include "absl/status/status.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport_framing_endpoint_extension.h"

absl::Status grpc_chttp2_security_frame_parser_parse(void* parser,
                                                     grpc_chttp2_transport* t,
                                                     grpc_chttp2_stream* ,
                                                     const grpc_slice& slice,
                                                     int is_last) {

  if (t->transport_framing_endpoint_extension == nullptr) {
    return absl::OkStatus();
  }

  grpc_chttp2_security_frame_parser* p =
      static_cast<grpc_chttp2_security_frame_parser*>(parser);
  p->payload.Append(grpc_core::Slice(grpc_core::CSliceRef(slice)));

  if (is_last) {

    t->transport_framing_endpoint_extension->ReceiveFrame(
        std::move(p->payload));
  }

  return absl::OkStatus();
}

absl::Status grpc_chttp2_security_frame_parser_begin_frame(
    grpc_chttp2_security_frame_parser* parser) {
  parser->payload.Clear();
  return absl::OkStatus();
}

void grpc_chttp2_security_frame_create(grpc_slice_buffer* payload,
                                       uint32_t length,
                                       grpc_slice_buffer* frame) {
  grpc_slice hdr;
  uint8_t* p;
  static const size_t header_size = 9;

  hdr = GRPC_SLICE_MALLOC(header_size);
  p = GRPC_SLICE_START_PTR(hdr);
  *p++ = static_cast<uint8_t>(length >> 16);
  *p++ = static_cast<uint8_t>(length >> 8);
  *p++ = static_cast<uint8_t>(length);
  *p++ = GRPC_CHTTP2_FRAME_SECURITY;
  *p++ = 0;
  *p++ = 0;
  *p++ = 0;
  *p++ = 0;
  *p++ = 0;

  grpc_slice_buffer_add(frame, hdr);
  grpc_slice_buffer_move_first_no_ref(payload, payload->length, frame);
}
