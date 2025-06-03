Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame_window_update.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"
#include "src/core/ext/transport/chttp2/transport/flow_control.h"
#include "src/core/ext/transport/chttp2/transport/http2_ztrace_collector.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/stream_lists.h"
#include "src/core/telemetry/stats.h"
#include "src/core/util/time.h"

// Creates a WINDOW_UPDATE frame for HTTP/2 protocol
// Parameters:
//   id: The stream ID (0 for connection-level window updates)
//   window_delta: The amount to increment the window size
//   call_tracer: Optional tracer for tracking outgoing bytes
// Returns:
//   A grpc_slice containing the constructed WINDOW_UPDATE frame
grpc_slice grpc_chttp2_window_update_create(
    uint32_t id, uint32_t window_delta,
    grpc_core::CallTracerInterface* call_tracer) {
  // Fixed size for WINDOW_UPDATE frame (9 bytes header + 4 bytes payload)
  static const size_t frame_size = 13;
  grpc_slice slice = GRPC_SLICE_MALLOC(frame_size);
  
  // Record outgoing bytes if call tracer is provided
  if (call_tracer != nullptr) {
    call_tracer->RecordOutgoingBytes({frame_size, 0, 0});
  }
  uint8_t* p = GRPC_SLICE_START_PTR(slice);

  // Ensure window_delta is non-zero (required by HTTP/2 spec)
  CHECK(window_delta);

  // Construct frame header:
  // First 3 bytes: payload length (4 bytes for WINDOW_UPDATE)
  *p++ = 0;
  *p++ = 0;
  *p++ = 4;
  // Frame type (WINDOW_UPDATE)
  *p++ = GRPC_CHTTP2_FRAME_WINDOW_UPDATE;
  // Flags (none for WINDOW_UPDATE)
  *p++ = 0;
  // Stream ID (4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(id >> 24);
  *p++ = static_cast<uint8_t>(id >> 16);
  *p++ = static_cast<uint8_t>(id >> 8);
  *p++ = static_cast<uint8_t>(id);
  // Window size increment (4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(window_delta >> 24);
  *p++ = static_cast<uint8_t>(window_delta >> 16);
  *p++ = static_cast<uint8_t>(window_delta >> 8);
  *p++ = static_cast<uint8_t>(window_delta);

  return slice;
}

// Initializes a window update parser and validates frame header
// Parameters:
//   parser: The parser to initialize
//   length: The payload length from frame header
//   flags: The flags from frame header
// Returns:
//   OK status if valid, error if frame is malformed
grpc_error_handle grpc_chttp2_window_update_parser_begin_frame(
    grpc_chttp2_window_update_parser* parser, uint32_t length, uint8_t flags) {
  // WINDOW_UPDATE must have no flags and exactly 4 bytes payload
  if (flags || length != 4) {
    return GRPC_ERROR_CREATE(absl::StrFormat(
        "invalid window update: length=%d, flags=%02x", length, flags));
  }
  // Initialize parser state
  parser->byte = 0;
  parser->amount = 0;
  return absl::OkStatus();
}

// Parses a WINDOW_UPDATE frame and updates flow control windows
// Parameters:
//   parser: The parser state
//   t: The HTTP/2 transport
//   s: The stream (nullptr for connection-level updates)
//   slice: The frame payload data
//   is_last: Flag indicating if this is the last frame in the sequence
// Returns:
//   OK status if successful, error if parsing failed
grpc_error_handle grpc_chttp2_window_update_parser_parse(
    void* parser, grpc_chttp2_transport* t, grpc_chttp2_stream* s,
    const grpc_slice& slice, int is_last) {
  const uint8_t* const beg = GRPC_SLICE_START_PTR(slice);
  const uint8_t* const end = GRPC_SLICE_END_PTR(slice);
  const uint8_t* cur = beg;
  grpc_chttp2_window_update_parser* p =
      static_cast<grpc_chttp2_window_update_parser*>(parser);

  // Parse the 4-byte window update amount (big-endian)
  while (p->byte != 4 && cur != end) {
    p->amount |= (static_cast<uint32_t>(*cur)) << (8 * (3 - p->byte));
    cur++;
    p->byte++;
  }

  // Record incoming framing bytes if stream exists
  if (s != nullptr) {
    uint64_t framing_bytes = static_cast<uint32_t>(end - cur);
    s->call_tracer_wrapper.RecordIncomingBytes({framing_bytes, 0, 0});
  }

  // Once we have all 4 bytes, process the window update
  if (p->byte == 4) {
    // Mask out the reserved high bit (per HTTP/2 spec)
    uint32_t received_update = p->amount & 0x7fffffffu;
    // Window update must be non-zero (per HTTP/2 spec)
    if (received_update == 0) {
      return GRPC_ERROR_CREATE(
          absl::StrCat("invalid window update bytes: ", p->amount));
    }
    // WINDOW_UPDATE frames must not be followed by continuation frames
    CHECK(is_last);

    // Record window update in trace collector
    t->http2_ztrace_collector.Append(grpc_core::H2WindowUpdateTrace<true>{
        t->incoming_stream_id, received_update});

    // Stream-level window update
    if (t->incoming_stream_id != 0) {
      if (s != nullptr) {
        grpc_core::Timestamp now = grpc_core::Timestamp::Now();
        // Update window update statistics if previous update exists
        if (s->last_window_update_time != grpc_core::Timestamp::InfPast()) {
          grpc_core::global_stats().IncrementHttp2StreamWindowUpdatePeriod(
              (now - s->last_window_update_time).millis());
        }
        s->last_window_update_time = now;
        // Update stream flow control window
        grpc_core::chttp2::StreamFlowControl::OutgoingUpdateContext(
            &s->flow_control)
            .RecvUpdate(received_update);
        grpc_core::global_stats().IncrementHttp2StreamRemoteWindowUpdate(
            received_update);
        // If stream was stalled, mark it writable again
        if (grpc_chttp2_list_remove_stalled_by_stream(t, s)) {
          grpc_chttp2_mark_stream_writable(t, s);
          grpc_chttp2_initiate_write(
              t, GRPC_CHTTP2_INITIATE_WRITE_FLOW_CONTROL_UNSTALLED_BY_UPDATE);
        }
      }
    } 
    // Connection-level window update
    else {
      grpc_core::chttp2::TransportFlowControl::OutgoingUpdateContext upd(
          &t->flow_control);
      grpc_core::Timestamp now = grpc_core::Timestamp::Now();
      // Update window update statistics if previous update exists
      if (t->last_window_update_time != grpc_core::Timestamp::InfPast()) {
        grpc_core::global_stats().IncrementHttp2TransportWindowUpdatePeriod(
            (now - t->last_window_update_time).millis());
      }
      t->last_window_update_time = now;
      grpc_core::global_stats().IncrementHttp2TransportRemoteWindowUpdate(
          received_update);
      // Update transport flow control window
      upd.RecvUpdate(received_update);
      // If transport was stalled, initiate write to resume
      if (upd.Finish() == grpc_core::chttp2::StallEdge::kUnstalled) {
        grpc_chttp2_initiate_write(
            t, GRPC_CHTTP2_INITIATE_WRITE_TRANSPORT_FLOW_CONTROL_UNSTALLED);
      }
    }
  }

  return absl::OkStatus();
}
```