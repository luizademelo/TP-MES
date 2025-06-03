Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame_goaway.h"

#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/base/attributes.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"

// Initializes a GOAWAY frame parser
void grpc_chttp2_goaway_parser_init(grpc_chttp2_goaway_parser* p) {
  p->debug_data = nullptr;
}

// Destroys a GOAWAY frame parser and frees allocated debug data
void grpc_chttp2_goaway_parser_destroy(grpc_chttp2_goaway_parser* p) {
  gpr_free(p->debug_data);
}

// Begins parsing a GOAWAY frame by validating length and initializing parser state
// Returns error if frame is too short (<8 bytes)
grpc_error_handle grpc_chttp2_goaway_parser_begin_frame(
    grpc_chttp2_goaway_parser* p, uint32_t length, uint8_t ) {
  if (length < 8) {
    return GRPC_ERROR_CREATE(
        absl::StrFormat("goaway frame too short (%d bytes)", length));
  }

  // Free any existing debug data and allocate space for new debug data
  gpr_free(p->debug_data);
  p->debug_length = length - 8;
  p->debug_data = static_cast<char*>(gpr_malloc(p->debug_length));
  p->debug_pos = 0;
  p->state = GRPC_CHTTP2_GOAWAY_LSI0;  // Start with parsing last stream ID (first byte)
  return absl::OkStatus();
}

// Parses a GOAWAY frame chunk by chunk using a state machine
// Handles partial frames and continues parsing where it left off
grpc_error_handle grpc_chttp2_goaway_parser_parse(void* parser,
                                                  grpc_chttp2_transport* t,
                                                  grpc_chttp2_stream* ,
                                                  const grpc_slice& slice,
                                                  int is_last) {
  const uint8_t* const beg = GRPC_SLICE_START_PTR(slice);
  const uint8_t* const end = GRPC_SLICE_END_PTR(slice);
  const uint8_t* cur = beg;
  grpc_chttp2_goaway_parser* p =
      static_cast<grpc_chttp2_goaway_parser*>(parser);

  // State machine for parsing GOAWAY frame components
  switch (p->state) {
    // Parse last stream ID (4 bytes, big-endian)
    case GRPC_CHTTP2_GOAWAY_LSI0:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_LSI0;
        return absl::OkStatus();
      }
      p->last_stream_id = (static_cast<uint32_t>(*cur)) << 24;
      ++cur;
      [[fallthrough]];
    case GRPC_CHTTP2_GOAWAY_LSI1:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_LSI1;
        return absl::OkStatus();
      }
      p->last_stream_id |= (static_cast<uint32_t>(*cur)) << 16;
      ++cur;
      [[fallthrough]];
    case GRPC_CHTTP2_GOAWAY_LSI2:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_LSI2;
        return absl::OkStatus();
      }
      p->last_stream_id |= (static_cast<uint32_t>(*cur)) << 8;
      ++cur;
      [[fallthrough]];
    case GRPC_CHTTP2_GOAWAY_LSI3:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_LSI3;
        return absl::OkStatus();
      }
      p->last_stream_id |= (static_cast<uint32_t>(*cur));
      ++cur;
      [[fallthrough]];

    // Parse error code (4 bytes, big-endian)
    case GRPC_CHTTP2_GOAWAY_ERR0:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_ERR0;
        return absl::OkStatus();
      }
      p->error_code = (static_cast<uint32_t>(*cur)) << 24;
      ++cur;
      [[fallthrough]];
    case GRPC_CHTTP2_GOAWAY_ERR1:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_ERR1;
        return absl::OkStatus();
      }
      p->error_code |= (static_cast<uint32_t>(*cur)) << 16;
      ++cur;
      [[fallthrough]];
    case GRPC_CHTTP2_GOAWAY_ERR2:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_ERR2;
        return absl::OkStatus();
      }
      p->error_code |= (static_cast<uint32_t>(*cur)) << 8;
      ++cur;
      [[fallthrough]];
    case GRPC_CHTTP2_GOAWAY_ERR3:
      if (cur == end) {
        p->state = GRPC_CHTTP2_GOAWAY_ERR3;
        return absl::OkStatus();
      }
      p->error_code |= (static_cast<uint32_t>(*cur));
      ++cur;
      [[fallthrough]];

    // Parse debug data (remaining bytes)
    case GRPC_CHTTP2_GOAWAY_DEBUG:
      if (end != cur) {
        memcpy(p->debug_data + p->debug_pos, cur,
               static_cast<size_t>(end - cur));
      }
      CHECK((size_t)(end - cur) < UINT32_MAX - p->debug_pos);
      p->debug_pos += static_cast<uint32_t>(end - cur);
      p->state = GRPC_CHTTP2_GOAWAY_DEBUG;
      if (is_last) {
        // Add trace event for the complete GOAWAY frame
        t->http2_ztrace_collector.Append([p]() {
          return grpc_core::H2GoAwayTrace<true>{
              p->last_stream_id, p->error_code,
              std::string(absl::string_view(p->debug_data, p->debug_length))};
        });
        // Process the complete GOAWAY frame
        grpc_chttp2_add_incoming_goaway(
            t, p->error_code, p->last_stream_id,
            absl::string_view(p->debug_data, p->debug_length));
        gpr_free(p->debug_data);
        p->debug_data = nullptr;
      }
      return absl::OkStatus();
  }
  GPR_UNREACHABLE_CODE(return GRPC_ERROR_CREATE("Should never reach here"));
}

// Constructs and appends a GOAWAY frame to the slice buffer
void grpc_chttp2_goaway_append(
    uint32_t last_stream_id, uint32_t error_code, const grpc_slice& debug_data,
    grpc_slice_buffer* slice_buffer,
    grpc_core::Http2ZTraceCollector* ztrace_collector) {
  // Allocate header slice (9 bytes for frame header + 4 for last_stream_id + 4 for error_code)
  grpc_slice header = GRPC_SLICE_MALLOC(9 + 4 + 4);
  uint8_t* p = GRPC_SLICE_START_PTR(header);
  uint32_t frame_length;
  CHECK(GRPC_SLICE_LENGTH(debug_data) < UINT32_MAX - 4 - 4);
  frame_length = 4 + 4 + static_cast<uint32_t> GRPC_SLICE_LENGTH(debug_data);

  // Add trace event for the outgoing GOAWAY frame
  ztrace_collector->Append([last_stream_id, error_code, debug_data]() {
    return grpc_core::H2GoAwayTrace<false>{
        last_stream_id, error_code,
        std::string(grpc_core::StringViewFromSlice(debug_data))};
  });

  // Write frame header (length and type)
  *p++ = static_cast<uint8_t>(frame_length >> 16);
  *p++ = static_cast<uint8_t>(frame_length >> 8);
  *p++ = static_cast<uint8_t>(frame_length);

  *p++ = GRPC_CHTTP2_FRAME_GOAWAY;

  // Write flags (none for GOAWAY)
  *p++ = 0;

  // Write reserved bytes (4 bytes, must be 0)
  *p++ = 0;
  *p++ = 0;
  *p++ = 0;
  *p++ = 0;

  // Write last stream ID (4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(last_stream_id >> 24);
  *p++ = static_cast<uint8_t>(last_stream_id >> 16);
  *p++ = static_cast<uint8_t>(last_stream_id >> 8);
  *p++ = static_cast<uint8_t>(last_stream_id);

  // Write error code (4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(error_code >> 24);
  *p++ = static_cast<uint8_t>(error_code >> 16);
  *p++ = static_cast<uint8_t>(error_code >> 8);
  *p++ = static_cast<uint8_t>(error_code);
  
  // Verify we wrote exactly the expected number of bytes
  CHECK(p == GRPC_SLICE_END_PTR(header));
  
  // Add header and debug data to the slice buffer
  grpc_slice_buffer_add(slice_buffer, header);
  grpc_slice_buffer_add(slice_buffer, debug_data);
}
```