
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_SECURITY_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_SECURITY_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport_framing_endpoint_extension.h"

struct grpc_chttp2_security_frame_parser {
  grpc_core::SliceBuffer payload;
};

void grpc_chttp2_security_frame_create(grpc_slice_buffer* payload,
                                       uint32_t length,
                                       grpc_slice_buffer* frame);

absl::Status grpc_chttp2_security_frame_parser_begin_frame(
    grpc_chttp2_security_frame_parser* parser);

grpc_error_handle grpc_chttp2_security_frame_parser_parse(
    void* parser, grpc_chttp2_transport* t, grpc_chttp2_stream* s,
    const grpc_slice& slice, int is_last);

#endif
