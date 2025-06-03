Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame_ping.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <string.h>

#include <algorithm>

#include "absl/container/flat_hash_map.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/ping_abuse_policy.h"
#include "src/core/ext/transport/chttp2/transport/ping_callbacks.h"
#include "src/core/lib/debug/trace.h"

// Creates a PING frame for HTTP/2 protocol
// Parameters:
//   ack: Flag indicating whether this is a PING ACK (1) or regular PING (0)
//   opaque_8bytes: 8-byte opaque data to include in the PING frame
// Returns:
//   grpc_slice containing the constructed PING frame
grpc_slice grpc_chttp2_ping_create(uint8_t ack, uint64_t opaque_8bytes) {
  // Allocate 17 bytes: 9 for header + 8 for opaque data
  grpc_slice slice = GRPC_SLICE_MALLOC(9 + 8);
  uint8_t* p = GRPC_SLICE_START_PTR(slice);

  // Construct HTTP/2 frame header:
  *p++ = 0;  // 24-bit length (upper 8 bits)
  *p++ = 0;  // 24-bit length (middle 8 bits)
  *p++ = 8;  // 24-bit length (lower 8 bits) - payload is 8 bytes
  *p++ = GRPC_CHTTP2_FRAME_PING;  // Frame type (PING)
  *p++ = ack ? 1 : 0;  // Flags (ACK bit)
  *p++ = 0;  // Reserved bit + 31-bit stream identifier (upper 8 bits)
  *p++ = 0;  // 31-bit stream identifier (next 8 bits)
  *p++ = 0;  // 31-bit stream identifier (next 8 bits)
  *p++ = 0;  // 31-bit stream identifier (lower 8 bits)

  // Add the 8-byte opaque data (big-endian)
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 56);
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 48);
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 40);
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 32);
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 24);
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 16);
  *p++ = static_cast<uint8_t>(opaque_8bytes >> 8);
  *p++ = static_cast<uint8_t>(opaque_8bytes);

  return slice;
}

// Initializes a PING frame parser
// Parameters:
//   parser: The parser to initialize
//   length: The length of the PING frame payload
//   flags: The flags field from the frame header
// Returns:
//   grpc_error_handle indicating success or failure
// Notes:
//   - Valid PING frames must have exactly 8 bytes of payload
//   - Only the ACK flag (0x01) is allowed
grpc_error_handle grpc_chttp2_ping_parser_begin_frame(
    grpc_chttp2_ping_parser* parser, uint32_t length, uint8_t flags) {
  if (flags & 0xfe || length != 8) {
    return GRPC_ERROR_CREATE(
        absl::StrFormat("invalid ping: length=%d, flags=%02x", length, flags));
  }
  parser->byte = 0;  // Reset byte counter
  parser->is_ack = flags;  // Store ACK flag
  parser->opaque_8bytes = 0;  // Initialize opaque data storage
  return absl::OkStatus();
}

// Parses a PING frame
// Parameters:
//   parser: The parser state
//   t: The HTTP/2 transport
//   [unused]: The stream (unused for PING frames)
//   slice: The data to parse
//   is_last: Flag indicating if this is the last slice of the frame
// Returns:
//   grpc_error_handle indicating success or failure
// Notes:
//   - For ACK PINGs, notifies the transport
//   - For regular PINGs from server, checks ping abuse policy
//   - May initiate a PING ACK response if configured
grpc_error_handle grpc_chttp2_ping_parser_parse(void* parser,
                                                grpc_chttp2_transport* t,
                                                grpc_chttp2_stream* ,
                                                const grpc_slice& slice,
                                                int is_last) {
  const uint8_t* const beg = GRPC_SLICE_START_PTR(slice);
  const uint8_t* const end = GRPC_SLICE_END_PTR(slice);
  const uint8_t* cur = beg;
  grpc_chttp2_ping_parser* p = static_cast<grpc_chttp2_ping_parser*>(parser);

  // Parse the 8-byte opaque data (big-endian)
  while (p->byte != 8 && cur != end) {
    p->opaque_8bytes |= ((static_cast<uint64_t>(*cur)) << (56 - 8 * p->byte));
    cur++;
    p->byte++;
  }

  // When we've received all 8 bytes
  if (p->byte == 8) {
    CHECK(is_last);  // PING frames should never be fragmented
    t->http2_ztrace_collector.Append(
        grpc_core::H2PingTrace<true>{p->is_ack != 0, p->opaque_8bytes});
    
    if (p->is_ack) {
      // Handle PING ACK
      GRPC_TRACE_LOG(http2_ping, INFO)
          << (t->is_client ? "CLIENT" : "SERVER") << "[" << t
          << "]: received ping ack " << p->opaque_8bytes;
      grpc_chttp2_ack_ping(t, p->opaque_8bytes);
    } else {
      // Handle regular PING
      if (!t->is_client) {
        // Server-side PING handling
        const bool transport_idle =
            t->keepalive_permit_without_calls == 0 && t->stream_map.empty();
        if (GRPC_TRACE_FLAG_ENABLED(http_keepalive) ||
            GRPC_TRACE_FLAG_ENABLED(http)) {
          LOG(INFO) << "SERVER[" << t << "]: received ping " << p->opaque_8bytes
                    << ": "
                    << t->ping_abuse_policy.GetDebugString(transport_idle);
        }
        // Check ping abuse policy
        if (t->ping_abuse_policy.ReceivedOnePing(transport_idle)) {
          grpc_chttp2_exceeded_ping_strikes(t);
        }
      } else {
        // Client-side PING handling
        GRPC_TRACE_LOG(http2_ping, INFO)
            << "CLIENT[" << t << "]: received ping " << p->opaque_8bytes;
      }
      
      // Send ACK if configured
      if (t->ack_pings) {
        // Grow ping ACK buffer if needed
        if (t->ping_ack_count == t->ping_ack_capacity) {
          t->ping_ack_capacity =
              std::max(t->ping_ack_capacity * 3 / 2, size_t{3});
          t->ping_acks = static_cast<uint64_t*>(gpr_realloc(
              t->ping_acks, t->ping_ack_capacity * sizeof(*t->ping_acks)));
        }
        // Queue the ACK
        t->num_pending_induced_frames++;
        t->ping_acks[t->ping_ack_count++] = p->opaque_8bytes;
        grpc_chttp2_initiate_write(t, GRPC_CHTTP2_INITIATE_WRITE_PING_RESPONSE);
      }
    }
  }

  return absl::OkStatus();
}
```