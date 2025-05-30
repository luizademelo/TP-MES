
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_BIN_DECODER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_BIN_DECODER_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

struct grpc_base64_decode_context {

  const uint8_t* input_cur;
  const uint8_t* input_end;
  uint8_t* output_cur;
  uint8_t* output_end;

  bool contains_tail;
};

bool grpc_base64_decode_partial(struct grpc_base64_decode_context* ctx);

grpc_slice grpc_chttp2_base64_decode(const grpc_slice& input);

grpc_slice grpc_chttp2_base64_decode_with_length(const grpc_slice& input,
                                                 size_t output_length);

size_t grpc_chttp2_base64_infer_length_after_decode(const grpc_slice& slice);

#endif
