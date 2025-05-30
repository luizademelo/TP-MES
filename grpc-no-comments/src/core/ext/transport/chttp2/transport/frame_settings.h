
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_SETTINGS_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FRAME_SETTINGS_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/manual_constructor.h"

typedef enum {
  GRPC_CHTTP2_SPS_ID0,
  GRPC_CHTTP2_SPS_ID1,
  GRPC_CHTTP2_SPS_VAL0,
  GRPC_CHTTP2_SPS_VAL1,
  GRPC_CHTTP2_SPS_VAL2,
  GRPC_CHTTP2_SPS_VAL3
} grpc_chttp2_settings_parse_state;

struct grpc_chttp2_settings_parser {
  grpc_chttp2_settings_parse_state state;
  grpc_core::Http2Settings* target_settings;
  grpc_core::ManualConstructor<grpc_core::Http2Settings> incoming_settings;
  uint8_t is_ack;
  uint16_t id;
  uint32_t value;
};

grpc_slice grpc_chttp2_settings_ack_create(void);

grpc_error_handle grpc_chttp2_settings_parser_begin_frame(
    grpc_chttp2_settings_parser* parser, uint32_t length, uint8_t flags,
    grpc_core::Http2Settings& settings);
grpc_error_handle grpc_chttp2_settings_parser_parse(void* parser,
                                                    grpc_chttp2_transport* t,
                                                    grpc_chttp2_stream* s,
                                                    const grpc_slice& slice,
                                                    int is_last);

#endif
