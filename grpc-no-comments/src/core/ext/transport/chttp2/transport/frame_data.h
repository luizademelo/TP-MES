
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_DATA_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_DATA_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "absl/status/status.h"
#include "src/core/ext/transport/chttp2/transport/http2_ztrace_collector.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/call_tracer.h"

absl::Status grpc_chttp2_data_parser_begin_frame(uint8_t flags,
                                                 uint32_t stream_id,
                                                 grpc_chttp2_stream* s);

grpc_error_handle grpc_chttp2_data_parser_parse(void* parser,
                                                grpc_chttp2_transport* t,
                                                grpc_chttp2_stream* s,
                                                const grpc_slice& slice,
                                                int is_last);

void grpc_chttp2_encode_data(uint32_t id, grpc_slice_buffer* inbuf,
                             uint32_t write_bytes, int is_eof,
                             grpc_core::CallTracerInterface* call_tracer,
                             grpc_core::Http2ZTraceCollector* ztrace_collector,
                             grpc_slice_buffer* outbuf);

grpc_core::Poll<grpc_error_handle> grpc_deframe_unprocessed_incoming_frames(
    grpc_chttp2_stream* s, int64_t* min_progress_size,
    grpc_core::SliceBuffer* stream_out, uint32_t* message_flags);

#endif
