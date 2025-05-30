
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_BIN_ENCODER_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_BIN_ENCODER_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

grpc_slice grpc_chttp2_base64_encode(const grpc_slice& input);

grpc_slice grpc_chttp2_huffman_compress(const grpc_slice& input);

grpc_slice grpc_chttp2_base64_encode_and_huffman_compress(
    const grpc_slice& input, uint32_t* wire_size);

#endif
