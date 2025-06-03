Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for RST_STREAM frame functionality
#include "src/core/ext/transport/chttp2/transport/frame_rst_stream.h"

#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/distributions.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/ext/transport/chttp2/transport/ping_callbacks.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/status_helper.h"

using grpc_core::http2::Http2ErrorCode;

// Creates a RST_STREAM frame with the given stream ID and error code
// Parameters:
//   id: The stream ID to reset
//   code: The HTTP/2 error code for the reset
//   call_tracer: Optional call tracer for monitoring
//   ztrace_collector: Collector for tracing information
// Returns:
//   A grpc_slice containing the RST_STREAM frame
grpc_slice grpc_chttp2_rst_stream_create(
    uint32_t id, uint32_t code, grpc_core::CallTracerInterface* call_tracer,
    grpc_core::Http2ZTraceCollector* ztrace_collector) {
  static const size_t frame_size = 13;  // Fixed size for RST_STREAM frame
  grpc_slice slice = GRPC_SLICE_MALLOC(frame_size);
  
  // Record outgoing bytes if call tracer is present
  if (call_tracer != nullptr) {
    call_tracer->RecordOutgoingBytes({frame_size, 0, 0});
  }
  
  // Append RST_STREAM event to trace collector
  ztrace_collector->Append(grpc_core::H2RstStreamTrace<false>{id, code});
  
  // Build the RST_STREAM frame
  uint8_t* p = GRPC_SLICE_START_PTR(slice);

  // Frame header (9 bytes)
  *p++ = 0;  // Length byte 1 (upper 8 bits of 0x000004)
  *p++ = 0;  // Length byte 2 (middle 8 bits of 0x000004)
  *p++ = 4;  // Length byte 3 (lower 8 bits of 0x000004)
  
  *p++ = GRPC_CHTTP2_FRAME_RST_STREAM;  // Frame type
  *p++ = 0;  // Flags (none set for RST_STREAM)
  
  // Stream ID (4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(id >> 24);
  *p++ = static_cast<uint8_t>(id >> 16);
  *p++ = static_cast<uint8_t>(id >> 8);
  *p++ = static_cast<uint8_t>(id);
  
  // Error code (4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(code >> 24);
  *p++ = static_cast<uint8_t>(code >> 16);
  *p++ = static_cast<uint8_t>(code >> 8);
  *p++ = static_cast<uint8_t>(code);

  return slice;
}

// Adds a RST_STREAM frame to the transport's next write queue
// Parameters:
//   t: The HTTP/2 transport
//   id: The stream ID to reset
//   code: The HTTP/2 error code for the reset
//   call_tracer: Optional call tracer for monitoring
void grpc_chttp2_add_rst_stream_to_next_write(
    grpc_chttp2_transport* t, uint32_t id, uint32_t code,
    grpc_core::CallTracerInterface* call_tracer) {
  t->num_pending_induced_frames++;
  grpc_slice_buffer_add(
      &t->qbuf, grpc_chttp2_rst_stream_create(id, code, call_tracer,
                                              &t->http2_ztrace_collector));
}

// Begins parsing a RST_STREAM frame
// Parameters:
//   parser: The RST_STREAM parser state
//   length: The frame length from the header
//   flags: The frame flags from the header
// Returns:
//   OK if valid, error if frame is malformed
grpc_error_handle grpc_chttp2_rst_stream_parser_begin_frame(
    grpc_chttp2_rst_stream_parser* parser, uint32_t length, uint8_t flags) {
  // RST_STREAM frames must have exactly 4 bytes of payload (error code)
  if (length != 4) {
    return GRPC_ERROR_CREATE(absl::StrFormat(
        "invalid rst_stream: length=%d, flags=%02x", length, flags));
  }
  parser->byte = 0;  // Reset parser state
  return absl::OkStatus();
}

// Parses a RST_STREAM frame payload
// Parameters:
//   parser: The parser state
//   t: The HTTP/2 transport
//   s: The affected stream
//   slice: The frame payload data
//   is_last: Flag indicating if this is the last frame in the sequence
// Returns:
//   OK if parsing succeeded, error otherwise
grpc_error_handle grpc_chttp2_rst_stream_parser_parse(void* parser,
                                                      grpc_chttp2_transport* t,
                                                      grpc_chttp2_stream* s,
                                                      const grpc_slice& slice,
                                                      int is_last) {
  const uint8_t* const beg = GRPC_SLICE_START_PTR(slice);
  const uint8_t* const end = GRPC_SLICE_END_PTR(slice);
  const uint8_t* cur = beg;
  grpc_chttp2_rst_stream_parser* p =
      static_cast<grpc_chttp2_rst_stream_parser*>(parser);

  // Collect the 4-byte error code
  while (p->byte != 4 && cur != end) {
    p->reason_bytes[p->byte] = *cur;
    cur++;
    p->byte++;
  }
  
  // Record any remaining bytes as framing overhead
  uint64_t framing_bytes = static_cast<uint64_t>(end - cur);
  s->call_tracer_wrapper.RecordIncomingBytes({framing_bytes, 0, 0});

  // When we have all 4 bytes of the error code
  if (p->byte == 4) {
    CHECK(is_last);  // RST_STREAM must be the last frame in the sequence
    
    // Combine the 4 bytes into a 32-bit error code (big-endian)
    uint32_t reason = ((static_cast<uint32_t>(p->reason_bytes[0])) << 24) |
                      ((static_cast<uint32_t>(p->reason_bytes[1])) << 16) |
                      ((static_cast<uint32_t>(p->reason_bytes[2])) << 8) |
                      ((static_cast<uint32_t>(p->reason_bytes[3])));
    
    // Record the RST_STREAM event in the trace collector
    t->http2_ztrace_collector.Append(
        grpc_core::H2RstStreamTrace<true>{t->incoming_stream_id, reason});
    
    // Log the RST_STREAM event
    GRPC_TRACE_LOG(http, INFO)
        << "[chttp2 transport=" << t << " stream=" << s
        << "] received RST_STREAM(reason=" << reason << ")";
    
    grpc_error_handle error;
    // Create an error unless it's a NO_ERROR and we have trailing metadata
    if (reason != static_cast<uint32_t>(Http2ErrorCode::kNoError) ||
        s->trailing_metadata_buffer.empty()) {
      error = grpc_error_set_int(
          grpc_error_set_str(
              GRPC_ERROR_CREATE("RST_STREAM"),
              grpc_core::StatusStrProperty::kGrpcMessage,
              absl::StrCat("Received RST_STREAM with error code ", reason)),
          grpc_core::StatusIntProperty::kHttp2Error,
          static_cast<intptr_t>(reason));
    }
    
    // For servers: optionally send a PING in response to RST_STREAM
    grpc_core::SharedBitGen g;
    if (!t->is_client &&
        absl::Bernoulli(g, t->ping_on_rst_stream_percent / 100.0)) {
      ++t->num_pending_induced_frames;
      t->ping_callbacks.RequestPing();
      grpc_chttp2_initiate_write(t, GRPC_CHTTP2_INITIATE_WRITE_KEEPALIVE_PING);
    }
    
    // Mark the stream as closed with the error
    grpc_chttp2_mark_stream_closed(t, s, true, true, error);
  }

  return absl::OkStatus();
}
```