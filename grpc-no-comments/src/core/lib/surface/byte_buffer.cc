
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"

grpc_byte_buffer* grpc_raw_byte_buffer_create(grpc_slice* slices,
                                              size_t nslices) {
  return grpc_raw_compressed_byte_buffer_create(slices, nslices,
                                                GRPC_COMPRESS_NONE);
}

grpc_byte_buffer* grpc_raw_compressed_byte_buffer_create(
    grpc_slice* slices, size_t nslices,
    grpc_compression_algorithm compression) {
  size_t i;
  grpc_byte_buffer* bb =
      static_cast<grpc_byte_buffer*>(gpr_malloc(sizeof(grpc_byte_buffer)));
  bb->type = GRPC_BB_RAW;
  bb->data.raw.compression = compression;
  grpc_slice_buffer_init(&bb->data.raw.slice_buffer);
  for (i = 0; i < nslices; i++) {
    grpc_core::CSliceRef(slices[i]);
    grpc_slice_buffer_add(&bb->data.raw.slice_buffer, slices[i]);
  }
  return bb;
}

grpc_byte_buffer* grpc_raw_byte_buffer_from_reader(
    grpc_byte_buffer_reader* reader) {
  grpc_byte_buffer* bb =
      static_cast<grpc_byte_buffer*>(gpr_malloc(sizeof(grpc_byte_buffer)));
  grpc_slice slice;
  bb->type = GRPC_BB_RAW;
  bb->data.raw.compression = GRPC_COMPRESS_NONE;
  grpc_slice_buffer_init(&bb->data.raw.slice_buffer);

  while (grpc_byte_buffer_reader_next(reader, &slice)) {
    grpc_slice_buffer_add(&bb->data.raw.slice_buffer, slice);
  }
  return bb;
}

grpc_byte_buffer* grpc_byte_buffer_copy(grpc_byte_buffer* bb) {
  switch (bb->type) {
    case GRPC_BB_RAW:
      return grpc_raw_compressed_byte_buffer_create(
          bb->data.raw.slice_buffer.slices, bb->data.raw.slice_buffer.count,
          bb->data.raw.compression);
  }
  GPR_UNREACHABLE_CODE(return nullptr);
}

void grpc_byte_buffer_destroy(grpc_byte_buffer* bb) {
  if (!bb) return;
  grpc_core::ExecCtx exec_ctx;
  switch (bb->type) {
    case GRPC_BB_RAW:
      grpc_slice_buffer_destroy(&bb->data.raw.slice_buffer);
      break;
  }
  gpr_free(bb);
}

size_t grpc_byte_buffer_length(grpc_byte_buffer* bb) {
  switch (bb->type) {
    case GRPC_BB_RAW:
      return bb->data.raw.slice_buffer.length;
  }
  GPR_UNREACHABLE_CODE(return 0);
}
