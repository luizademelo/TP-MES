
// Copyright 2015 gRPC authors.

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"

int grpc_byte_buffer_reader_init(grpc_byte_buffer_reader* reader,
                                 grpc_byte_buffer* buffer) {
  reader->buffer_in = buffer;
  switch (reader->buffer_in->type) {
    case GRPC_BB_RAW:
      reader->buffer_out = reader->buffer_in;
      reader->current.index = 0;
      break;
  }
  return 1;
}

void grpc_byte_buffer_reader_destroy(grpc_byte_buffer_reader* reader) {
  reader->buffer_out = nullptr;
}

int grpc_byte_buffer_reader_peek(grpc_byte_buffer_reader* reader,
                                 grpc_slice** slice) {
  switch (reader->buffer_in->type) {
    case GRPC_BB_RAW: {
      grpc_slice_buffer* slice_buffer;
      slice_buffer = &reader->buffer_out->data.raw.slice_buffer;
      if (reader->current.index < slice_buffer->count) {
        *slice = &slice_buffer->slices[reader->current.index];
        reader->current.index += 1;
        return 1;
      }
      break;
    }
  }
  return 0;
}

int grpc_byte_buffer_reader_next(grpc_byte_buffer_reader* reader,
                                 grpc_slice* slice) {
  switch (reader->buffer_in->type) {
    case GRPC_BB_RAW: {
      grpc_slice_buffer* slice_buffer;
      slice_buffer = &reader->buffer_out->data.raw.slice_buffer;
      if (reader->current.index < slice_buffer->count) {
        *slice =
            grpc_core::CSliceRef(slice_buffer->slices[reader->current.index]);
        reader->current.index += 1;
        return 1;
      }
      break;
    }
  }
  return 0;
}

grpc_slice grpc_byte_buffer_reader_readall(grpc_byte_buffer_reader* reader) {
  grpc_slice in_slice;
  size_t bytes_read = 0;
  const size_t input_size = grpc_byte_buffer_length(reader->buffer_out);
  grpc_slice out_slice = GRPC_SLICE_MALLOC(input_size);
  uint8_t* const outbuf = GRPC_SLICE_START_PTR(out_slice);

  grpc_core::ExecCtx exec_ctx;
  while (grpc_byte_buffer_reader_next(reader, &in_slice) != 0) {
    const size_t slice_length = GRPC_SLICE_LENGTH(in_slice);
    memcpy(&(outbuf[bytes_read]), GRPC_SLICE_START_PTR(in_slice), slice_length);
    bytes_read += slice_length;
    grpc_core::CSliceUnref(in_slice);
    CHECK(bytes_read <= input_size);
  }

  return out_slice;
}
