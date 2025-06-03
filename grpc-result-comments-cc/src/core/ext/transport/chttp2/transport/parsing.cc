I'll provide a commented version of the code. The comments explain the functionality and logic of each major section.

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for gRPC HTTP/2 transport implementation
#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <string.h>

// Standard C++ headers
#include <atomic>
#include <initializer_list>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <variant>

// Abseil headers for utilities and logging
#include "absl/base/attributes.h"
#include "absl/container/flat_hash_map.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/bit_gen_ref.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"

// gRPC core headers for HTTP/2 transport implementation
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"
#include "src/core/ext/transport/chttp2/transport/flow_control.h"
#include "src/core/ext/transport/chttp2/transport/frame_data.h"
#include "src/core/ext/transport/chttp2/transport/frame_goaway.h"
#include "src/core/ext/transport/chttp2/transport/frame_ping.h"
#include "src/core/ext/transport/chttp2/transport/frame_rst_stream.h"
#include "src/core/ext/transport/chttp2/transport/frame_security.h"
#include "src/core/ext/transport/chttp2/transport/frame_settings.h"
#include "src/core/ext/transport/chttp2/transport/frame_window_update.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser_table.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/ext/transport/chttp2/transport/http2_ztrace_collector.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"

// Other gRPC core utilities
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/combiner.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/bdp_estimator.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/random_early_detection.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/status_helper.h"

// Using declarations for commonly used types
using grpc_core::HPackParser;
using grpc_core::http2::Http2ErrorCode;

// Forward declarations for frame parser initialization functions
static grpc_error_handle init_frame_parser(grpc_chttp2_transport* t,
                                           size_t& requests_started);
static grpc_error_handle init_header_frame_parser(grpc_chttp2_transport* t,
                                                  int is_continuation,
                                                  size_t& requests_started);
static grpc_error_handle init_data_frame_parser(grpc_chttp2_transport* t);
static grpc_error_handle init_rst_stream_parser(grpc_chttp2_transport* t);
static grpc_error_handle init_settings_frame_parser(grpc_chttp2_transport* t);
static grpc_error_handle init_window_update_frame_parser(
    grpc_chttp2_transport* t);
static grpc_error_handle init_ping_parser(grpc_chttp2_transport* t);
static grpc_error_handle init_goaway_parser(grpc_chttp2_transport* t);
static grpc_error_handle init_security_frame_parser(grpc_chttp2_transport* t);
static grpc_error_handle init_non_header_skip_frame_parser(
    grpc_chttp2_transport* t);

// Forward declaration for frame slice parsing function
static grpc_error_handle parse_frame_slice(grpc_chttp2_transport* t,
                                           const grpc_slice& slice,
                                           int is_last);

// Helper function to get a safe UTF-8 character (replaces non-ASCII with space)
static char get_utf8_safe_char(char c) {
  return static_cast<unsigned char>(c) < 128 ? c : 32;
}

// Returns the minimum read progress size based on current deframe state
uint32_t grpc_chttp2_min_read_progress_size(grpc_chttp2_transport* t) {
  switch (t->deframe_state) {
    case GRPC_DTS_CLIENT_PREFIX_0:
    case GRPC_DTS_CLIENT_PREFIX_1:
    case GRPC_DTS_CLIENT_PREFIX_2:
    case GRPC_DTS_CLIENT_PREFIX_3:
    case GRPC_DTS_CLIENT_PREFIX_4:
    case GRPC_DTS_CLIENT_PREFIX_5:
    case GRPC_DTS_CLIENT_PREFIX_6:
    case GRPC_DTS_CLIENT_PREFIX_7:
    case GRPC_DTS_CLIENT_PREFIX_8:
    case GRPC_DTS_CLIENT_PREFIX_9:
    case GRPC_DTS_CLIENT_PREFIX_10:
    case GRPC_DTS_CLIENT_PREFIX_11:
    case GRPC_DTS_CLIENT_PREFIX_12:
    case GRPC_DTS_CLIENT_PREFIX_13:
    case GRPC_DTS_CLIENT_PREFIX_14:
    case GRPC_DTS_CLIENT_PREFIX_15:
    case GRPC_DTS_CLIENT_PREFIX_16:
    case GRPC_DTS_CLIENT_PREFIX_17:
    case GRPC_DTS_CLIENT_PREFIX_18:
    case GRPC_DTS_CLIENT_PREFIX_19:
    case GRPC_DTS_CLIENT_PREFIX_20:
    case GRPC_DTS_CLIENT_PREFIX_21:
    case GRPC_DTS_CLIENT_PREFIX_22:
    case GRPC_DTS_CLIENT_PREFIX_23:
      // Calculate remaining bytes in client prefix
      return 9 + 24 - (t->deframe_state - GRPC_DTS_CLIENT_PREFIX_0);
    case GRPC_DTS_FH_0:
    case GRPC_DTS_FH_1:
    case GRPC_DTS_FH_2:
    case GRPC_DTS_FH_3:
    case GRPC_DTS_FH_4:
    case GRPC_DTS_FH_5:
    case GRPC_DTS_FH_6:
    case GRPC_DTS_FH_7:
    case GRPC_DTS_FH_8:
      // Calculate remaining bytes in frame header
      return 9 - (t->deframe_state - GRPC_DTS_FH_0);
    case GRPC_DTS_FRAME:
      // For frame body, return the remaining frame size
      return t->incoming_frame_size;
  }
  GPR_UNREACHABLE_CODE(return 1);
}

namespace {
// Structure to represent known frame flags and their names
struct KnownFlag {
  uint8_t flag;
  absl::string_view name;
};

// Creates a string representation of a frame type with its flags
std::string MakeFrameTypeString(absl::string_view frame_type, uint8_t flags,
                                std::initializer_list<KnownFlag> known_flags) {
  std::string result(frame_type);
  // Append known flags to the string
  for (const KnownFlag& known_flag : known_flags) {
    if (flags & known_flag.flag) {
      absl::StrAppend(&result, ":", known_flag.name);
      flags &= ~known_flag.flag;
    }
  }
  // Append any remaining unknown flags in hex format
  if (flags != 0) {
    absl::StrAppend(&result, ":UNKNOWN_FLAGS=0x",
                    absl::Hex(flags, absl::kZeroPad2));
  }
  return result;
}

// Returns a string representation of the frame type and flags
std::string FrameTypeString(uint8_t frame_type, uint8_t flags) {
  switch (frame_type) {
    case GRPC_CHTTP2_FRAME_DATA:
      return MakeFrameTypeString(
          "DATA", flags, {{GRPC_CHTTP2_DATA_FLAG_END_STREAM, "END_STREAM"}});
    case GRPC_CHTTP2_FRAME_HEADER:
      return MakeFrameTypeString(
          "HEADERS", flags,
          {{GRPC_CHTTP2_DATA_FLAG_END_STREAM, "END_STREAM"},
           {GRPC_CHTTP2_DATA_FLAG_END_HEADERS, "END_HEADERS"},
           {GRPC_CHTTP2_FLAG_HAS_PRIORITY, "PRIORITY"}});
    case GRPC_CHTTP2_FRAME_CONTINUATION:
      return MakeFrameTypeString(
          "HEADERS", flags,
          {{GRPC_CHTTP2_DATA_FLAG_END_STREAM, "END_STREAM"},
           {GRPC_CHTTP2_DATA_FLAG_END_HEADERS, "END_HEADERS"},
           {GRPC_CHTTP2_FLAG_HAS_PRIORITY, "PRIORITY"}});
    case GRPC_CHTTP2_FRAME_RST_STREAM:
      return MakeFrameTypeString("RST_STREAM", flags, {});
    case GRPC_CHTTP2_FRAME_SETTINGS:
      return MakeFrameTypeString("SETTINGS", flags,
                                 {{GRPC_CHTTP2_FLAG_ACK, "ACK"}});
    case GRPC_CHTTP2_FRAME_PING:
      return MakeFrameTypeString("PING", flags,
                                 {{GRPC_CHTTP2_FLAG_ACK, "ACK"}});
    case GRPC_CHTTP2_FRAME_GOAWAY:
      return MakeFrameTypeString("GOAWAY", flags, {});
    case GRPC_CHTTP2_FRAME_WINDOW_UPDATE:
      return MakeFrameTypeString("WINDOW_UPDATE", flags, {});
    case GRPC_CHTTP2_FRAME_SECURITY:
      return MakeFrameTypeString("SECURITY", flags, {});
    default:
      return MakeFrameTypeString(
          absl::StrCat("UNKNOWN_FRAME_TYPE_", static_cast<int>(frame_type)),
          flags, {});
  }
}
}

// Main function to perform HTTP/2 frame parsing
std::variant<size_t, absl::Status> grpc_chttp2_perform_read(
    grpc_chttp2_transport* t, const grpc_slice& slice,
    size_t& requests_started) {
  GRPC_LATENT_SEE_INNER_SCOPE("grpc_chttp2_perform_read");

  // Get slice boundaries
  const uint8_t* beg = GRPC_SLICE_START_PTR(slice);
  const uint8_t* end = GRPC_SLICE_END_PTR(slice);
  const uint8_t* cur = beg;
  grpc_error_handle err;

  // Early return if slice is empty
  if (cur == end) return absl::OkStatus();

  // State machine for parsing HTTP/2 frames
  switch (t->deframe_state) {
    // Handle client connection prefix (24 bytes)
    case GRPC_DTS_CLIENT_PREFIX_0:
    case GRPC_DTS_CLIENT_PREFIX_1:
    case GRPC_DTS_CLIENT_PREFIX_2:
    case GRPC_DTS_CLIENT_PREFIX_3:
    case GRPC_DTS_CLIENT_PREFIX_4:
    case GRPC_DTS_CLIENT_PREFIX_5:
    case GRPC_DTS_CLIENT_PREFIX_6:
    case GRPC_DTS_CLIENT_PREFIX_7:
    case GRPC_DTS_CLIENT_PREFIX_8:
    case GRPC_DTS_CLIENT_PREFIX_9:
    case GRPC_DTS_CLIENT_PREFIX_10:
    case GRPC_DTS_CLIENT_PREFIX_11:
    case GRPC_DTS_CLIENT_PREFIX_12:
    case GRPC_DTS_CLIENT_PREFIX_13:
    case GRPC_DTS_CLIENT_PREFIX_14:
    case GRPC_DTS_CLIENT_PREFIX_15:
    case GRPC_DTS_CLIENT_PREFIX_16:
    case GRPC_DTS_CLIENT_PREFIX_17:
    case GRPC_DTS_CLIENT_PREFIX_18:
    case GRPC_DTS_CLIENT_PREFIX_19:
    case GRPC_DTS_CLIENT_PREFIX_20:
    case GRPC_DTS_CLIENT_PREFIX_21:
    case GRPC_DTS_CLIENT_PREFIX_22:
    case GRPC_DTS_CLIENT_PREFIX_23:
      // Verify client connection prefix bytes
      while (cur != end && t->deframe_state != GRPC_DTS_FH_0) {
        if (*cur != GRPC_CHTTP2_CLIENT_CONNECT_STRING[t->deframe_state]) {
          return GRPC_ERROR_CREATE(absl::StrFormat(
              "Connect string mismatch: expected '%c' (%d) got '%c' (%d) "
              "at byte %d",
              get_utf8_safe_char(
                  GRPC_CHTTP2_CLIENT_CONNECT_STRING[t->deframe_state]),
              static_cast<int>(static_cast<uint8_t>(
                  GRPC_CHTTP2_CLIENT_CONNECT_STRING[t->deframe_state])),
              get_utf8_safe_char(*cur), static_cast<int>(*cur),
              t->deframe_state));
        }
        ++cur;
        // Move to next state
        t->deframe_state = static_cast<grpc_chttp2_deframe_transport_state>(
            1 + static_cast<int>(t->deframe_state));
      }
      if (cur == end) {
        return absl::OkStatus();
      }
    // Fall through to frame header parsing
    dts_fh_0:
      // Check if we've reached the maximum requests per read
      if (requests_started >= t->max_requests_per_read) {
        t->deframe_state = GRPC_DTS_FH_0;
        return static_cast<size_t>(cur - beg);
      }
      [[fallthrough]];
    // Parse frame header fields (9 bytes total)
    case GRPC_DTS_FH_0:  // Frame length byte 1 (16 bits)
      DCHECK_LT(cur, end);
      t->incoming_frame_size = (static_cast<uint32_t>(*cur)) << 16;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_1;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_1:  // Frame length byte 2
      DCHECK_LT(cur, end);
      t->incoming_frame_size |= (static_cast<uint32_t>(*cur)) << 8;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_2;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_2:  // Frame length byte 3
      DCHECK_LT(cur, end);
      t->incoming_frame_size |= *cur;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_3;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_3:  // Frame type
      DCHECK_LT(cur, end);
      t->incoming_frame_type = *cur;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_4;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_4:  // Frame flags
      DCHECK_LT(cur, end);
      t->incoming_frame_flags = *cur;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_5;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_5:  // Stream ID byte 1 (31 bits)
      DCHECK_LT(cur, end);
      t->incoming_stream_id = ((static_cast<uint32_t>(*cur)) & 0x7f) << 24;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_6;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_6:  // Stream ID byte 2
      DCHECK_LT(cur, end);
      t->incoming_stream_id |= (static_cast<uint32_t>(*cur)) << 16;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_7;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_7:  // Stream ID byte 3
      DCHECK_LT(cur, end);
      t->incoming_stream_id |= (static_cast<uint32_t>(*cur)) << 8;
      if (++cur == end) {
        t->deframe_state = GRPC_DTS_FH_8;
        return absl::OkStatus();
      }
      [[fallthrough]];
    case GRPC_DTS_FH_8:  // Stream ID byte 4
      DCHECK_LT(cur, end);
      t