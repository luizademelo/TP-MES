Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for data frame handling in HTTP/2 transport
#include "src/core/ext/transport/chttp2/transport/frame_data.h"

#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/stats.h"
#include "src/core/util/status_helper.h"

// Function to begin processing a DATA frame
// Validates flags and sets stream state accordingly
// Args:
//   flags: Frame flags from the incoming DATA frame
//   stream_id: The stream identifier this frame belongs to
//   s: Pointer to the stream object
// Returns:
//   OkStatus if flags are valid, InternalError otherwise
absl::Status grpc_chttp2_data_parser_begin_frame(uint8_t flags,
                                                 uint32_t stream_id,
                                                 grpc_chttp2_stream* s) {
  // Only END_STREAM flag is supported for DATA frames
  if (flags & ~GRPC_CHTTP2_DATA_FLAG_END_STREAM) {
    return absl::InternalError(absl::StrFormat(
        "unsupported data flags: 0x%02x stream: %d", flags, stream_id));
  }

  // Update stream state based on END_STREAM flag
  if (flags & GRPC_CHTTP2_DATA_FLAG_END_STREAM) {
    s->received_last_frame = true;
    s->eos_received = true;
  } else {
    s->received_last_frame = false;
  }

  return absl::OkStatus();
}

// Encodes data into HTTP/2 DATA frames
// Args:
//   id: Stream ID for the frame
//   inbuf: Buffer containing data to be sent
//   write_bytes: Number of bytes to write
//   is_eof: Flag indicating if this is the last frame
//   call_tracer: For tracing call data
//   ztrace_collector: For collecting ztrace data
//   outbuf: Buffer where encoded frame will be stored
void grpc_chttp2_encode_data(uint32_t id, grpc_slice_buffer* inbuf,
                             uint32_t write_bytes, int is_eof,
                             grpc_core::CallTracerInterface* call_tracer,
                             grpc_core::Http2ZTraceCollector* ztrace_collector,
                             grpc_slice_buffer* outbuf) {
  grpc_slice hdr;
  uint8_t* p;
  static const size_t header_size = 9;  // Standard HTTP/2 frame header size

  // Allocate and prepare frame header
  hdr = GRPC_SLICE_MALLOC(header_size);
  p = GRPC_SLICE_START_PTR(hdr);
  CHECK(write_bytes < (1 << 24));  // Ensure write_bytes fits in 24 bits
  
  // Write frame length (24 bits in 3 bytes)
  *p++ = static_cast<uint8_t>(write_bytes >> 16);
  *p++ = static_cast<uint8_t>(write_bytes >> 8);
  *p++ = static_cast<uint8_t>(write_bytes);
  
  // Write frame type (DATA) and flags
  *p++ = GRPC_CHTTP2_FRAME_DATA;
  *p++ = is_eof ? GRPC_CHTTP2_DATA_FLAG_END_STREAM : 0;
  
  // Write stream ID (32 bits in 4 bytes, big-endian)
  *p++ = static_cast<uint8_t>(id >> 24);
  *p++ = static_cast<uint8_t>(id >> 16);
  *p++ = static_cast<uint8_t>(id >> 8);
  *p++ = static_cast<uint8_t>(id);
  
  // Add header to output buffer
  grpc_slice_buffer_add(outbuf, hdr);

  // Record data frame in ztrace collector
  ztrace_collector->Append(
      grpc_core::H2DataTrace<false>{id, is_eof != 0, write_bytes});

  // Move data from input to output buffer
  grpc_slice_buffer_move_first_no_ref(inbuf, write_bytes, outbuf);

  // Update statistics and tracing
  grpc_core::global_stats().IncrementHttp2WriteDataFrameSize(write_bytes);
  call_tracer->RecordOutgoingBytes({header_size, 0, 0});
}

// Processes incoming frames from a stream and deframes them
// Args:
//   s: The stream to process
//   min_progress_size: Output parameter for minimum bytes needed to progress
//   stream_out: Buffer for deframed data
//   message_flags: Output parameter for message flags
// Returns:
//   Pending if more data is needed, OkStatus if processing completed,
//   or error status if there was a problem
grpc_core::Poll<grpc_error_handle> grpc_deframe_unprocessed_incoming_frames(
    grpc_chttp2_stream* s, int64_t* min_progress_size,
    grpc_core::SliceBuffer* stream_out, uint32_t* message_flags) {
  grpc_slice_buffer* slices = &s->frame_storage;
  grpc_error_handle error;

  // Check if we have enough data for at least a header
  if (slices->length < GRPC_HEADER_SIZE_IN_BYTES) {
    if (min_progress_size != nullptr) {
      *min_progress_size = GRPC_HEADER_SIZE_IN_BYTES - slices->length;
    }
    return grpc_core::Pending{};
  }

  // Extract header bytes
  uint8_t header[GRPC_HEADER_SIZE_IN_BYTES];
  grpc_slice_buffer_copy_first_into_buffer(slices, GRPC_HEADER_SIZE_IN_BYTES,
                                           header);

  // Process frame type (compression flag)
  switch (header[0]) {
    case 0:  // No compression
      if (message_flags != nullptr) *message_flags = 0;
      break;
    case 1:  // Compressed frame
      if (message_flags != nullptr) {
        *message_flags = GRPC_WRITE_INTERNAL_COMPRESS;
      }
      break;
    default:  // Invalid frame type
      error = GRPC_ERROR_CREATE(
          absl::StrFormat("Bad GRPC frame type 0x%02x", header[0]));
      error = grpc_error_set_int(error, grpc_core::StatusIntProperty::kStreamId,
                                 static_cast<intptr_t>(s->id));
      return error;
  }

  // Calculate frame length from header
  size_t length = (static_cast<uint32_t>(header[1]) << 24) |
                  (static_cast<uint32_t>(header[2]) << 16) |
                  (static_cast<uint32_t>(header[3]) << 8) |
                  static_cast<uint32_t>(header[4]);

  // Check if we have the complete frame
  if (slices->length < length + GRPC_HEADER_SIZE_IN_BYTES) {
    if (min_progress_size != nullptr) {
      *min_progress_size = length + GRPC_HEADER_SIZE_IN_BYTES - slices->length;
    }
    return grpc_core::Pending{};
  }

  if (min_progress_size != nullptr) *min_progress_size = 0;

  // If output buffer provided, move data to it
  if (stream_out != nullptr) {
    s->call_tracer_wrapper.RecordIncomingBytes(
        {GRPC_HEADER_SIZE_IN_BYTES, length, 0});
    grpc_slice_buffer_move_first_into_buffer(slices, GRPC_HEADER_SIZE_IN_BYTES,
                                             header);
    grpc_slice_buffer_move_first(slices, length, stream_out->c_slice_buffer());
  }

  return absl::OkStatus();
}

// Parses incoming DATA frames and processes them
// Args:
//   (unused) parser: Parser object (unused in this implementation)
//   t: The transport object
//   s: The stream object
//   slice: The incoming data slice
//   is_last: Flag indicating if this is the last frame
// Returns:
//   OkStatus on success, or error status if there was a problem
grpc_error_handle grpc_chttp2_data_parser_parse(void* /*parser*/,
                                                grpc_chttp2_transport* t,
                                                grpc_chttp2_stream* s,
                                                const grpc_slice& slice,
                                                int is_last) {
  // Add incoming slice to frame storage
  grpc_core::CSliceRef(slice);
  grpc_slice_buffer_add(&s->frame_storage, slice);
  
  // Attempt to complete message reception
  grpc_chttp2_maybe_complete_recv_message(t, s);

  // If this is the last frame, record it in ztrace collector
  if (is_last) {
    t->http2_ztrace_collector.Append(grpc_core::H2DataTrace<true>{
        t->incoming_stream_id,
        (t->incoming_frame_flags & GRPC_CHTTP2_DATA_FLAG_END_STREAM) != 0,
        t->incoming_frame_size});
  }
  
  // If we've received the last frame, mark stream as closed
  if (is_last && s->received_last_frame) {
    grpc_chttp2_mark_stream_closed(
        t, s, true, false,
        t->is_client
            ? GRPC_ERROR_CREATE("Data frame with END_STREAM flag received")
            : absl::OkStatus());
  }

  return absl::OkStatus();
}
```