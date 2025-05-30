
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_COMPRESSION_MESSAGE_COMPRESS_H
#define GRPC_SRC_CORE_LIB_COMPRESSION_MESSAGE_COMPRESS_H

#include <grpc/impl/compression_types.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

int grpc_msg_compress(grpc_compression_algorithm algorithm,
                      grpc_slice_buffer* input, grpc_slice_buffer* output);

int grpc_msg_decompress(grpc_compression_algorithm algorithm,
                        grpc_slice_buffer* input, grpc_slice_buffer* output);

#endif
