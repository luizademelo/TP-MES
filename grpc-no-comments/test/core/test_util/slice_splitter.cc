
// Copyright 2015 gRPC authors.

#include "test/core/test_util/slice_splitter.h"

#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>

const char* grpc_slice_split_mode_name(grpc_slice_split_mode mode) {
  switch (mode) {
    case GRPC_SLICE_SPLIT_IDENTITY:
      return "identity";
    case GRPC_SLICE_SPLIT_MERGE_ALL:
      return "merge_all";
    case GRPC_SLICE_SPLIT_ONE_BYTE:
      return "one_byte";
  }
  return "error";
}

void grpc_split_slices(grpc_slice_split_mode mode, grpc_slice* src_slices,
                       size_t src_slice_count, grpc_slice** dst_slices,
                       size_t* dst_slice_count) {
  size_t i, j;
  size_t length;

  switch (mode) {
    case GRPC_SLICE_SPLIT_IDENTITY:
      *dst_slice_count = src_slice_count;
      *dst_slices = static_cast<grpc_slice*>(
          gpr_malloc(sizeof(grpc_slice) * src_slice_count));
      for (i = 0; i < src_slice_count; i++) {
        (*dst_slices)[i] = src_slices[i];
        grpc_slice_ref((*dst_slices)[i]);
      }
      break;
    case GRPC_SLICE_SPLIT_MERGE_ALL:
      *dst_slice_count = 1;
      length = 0;
      for (i = 0; i < src_slice_count; i++) {
        length += GRPC_SLICE_LENGTH(src_slices[i]);
      }
      *dst_slices = static_cast<grpc_slice*>(gpr_malloc(sizeof(grpc_slice)));
      **dst_slices = grpc_slice_malloc(length);
      length = 0;
      for (i = 0; i < src_slice_count; i++) {
        memcpy(GRPC_SLICE_START_PTR(**dst_slices) + length,
               GRPC_SLICE_START_PTR(src_slices[i]),
               GRPC_SLICE_LENGTH(src_slices[i]));
        length += GRPC_SLICE_LENGTH(src_slices[i]);
      }
      break;
    case GRPC_SLICE_SPLIT_ONE_BYTE:
      length = 0;
      for (i = 0; i < src_slice_count; i++) {
        length += GRPC_SLICE_LENGTH(src_slices[i]);
      }
      *dst_slice_count = length;
      *dst_slices =
          static_cast<grpc_slice*>(gpr_malloc(sizeof(grpc_slice) * length));
      length = 0;
      for (i = 0; i < src_slice_count; i++) {
        for (j = 0; j < GRPC_SLICE_LENGTH(src_slices[i]); j++) {
          (*dst_slices)[length] = grpc_slice_sub(src_slices[i], j, j + 1);
          length++;
        }
      }
      break;
  }
}

void grpc_split_slices_to_buffer(grpc_slice_split_mode mode,
                                 grpc_slice* src_slices, size_t src_slice_count,
                                 grpc_slice_buffer* dst) {
  grpc_slice* slices;
  size_t nslices;
  size_t i;
  grpc_split_slices(mode, src_slices, src_slice_count, &slices, &nslices);
  for (i = 0; i < nslices; i++) {

    grpc_slice_buffer_add_indexed(dst, slices[i]);
  }
  gpr_free(slices);
}

void grpc_split_slice_buffer(grpc_slice_split_mode mode, grpc_slice_buffer* src,
                             grpc_slice_buffer* dst) {
  grpc_split_slices_to_buffer(mode, src->slices, src->count, dst);
}

grpc_slice grpc_slice_merge(grpc_slice* slices, size_t nslices) {
  uint8_t* out = nullptr;
  size_t length = 0;
  size_t capacity = 0;
  size_t i;

  for (i = 0; i < nslices; i++) {
    if (GRPC_SLICE_LENGTH(slices[i]) + length > capacity) {
      capacity = std::max(capacity * 2, GRPC_SLICE_LENGTH(slices[i]) + length);
      out = static_cast<uint8_t*>(gpr_realloc(out, capacity));
    }
    memcpy(out + length, GRPC_SLICE_START_PTR(slices[i]),
           GRPC_SLICE_LENGTH(slices[i]));
    length += GRPC_SLICE_LENGTH(slices[i]);
  }

  return grpc_slice_new(out, length, gpr_free);
}
