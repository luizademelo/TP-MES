
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_SLICE_SPLITTER_H
#define GRPC_TEST_CORE_TEST_UTIL_SLICE_SPLITTER_H

#include <grpc/slice.h>
#include <stddef.h>

typedef enum {

  GRPC_SLICE_SPLIT_MERGE_ALL,

  GRPC_SLICE_SPLIT_IDENTITY,

  GRPC_SLICE_SPLIT_ONE_BYTE
} grpc_slice_split_mode;

void grpc_split_slices(grpc_slice_split_mode mode, grpc_slice* src_slices,
                       size_t src_slice_count, grpc_slice** dst_slices,
                       size_t* dst_slice_count);

void grpc_split_slices_to_buffer(grpc_slice_split_mode mode,
                                 grpc_slice* src_slices, size_t src_slice_count,
                                 grpc_slice_buffer* dst);
void grpc_split_slice_buffer(grpc_slice_split_mode mode, grpc_slice_buffer* src,
                             grpc_slice_buffer* dst);

grpc_slice grpc_slice_merge(grpc_slice* slices, size_t nslices);

const char* grpc_slice_split_mode_name(grpc_slice_split_mode mode);

#endif
