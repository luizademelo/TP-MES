Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC and system headers
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

// Initializes a byte buffer reader for reading data from the given buffer
// Parameters:
//   reader: Pointer to the reader structure to initialize
//   buffer: Byte buffer to read from
// Returns:
//   1 on success (always returns 1 in current implementation)
int grpc_byte_buffer_reader_init(grpc_byte_buffer_reader* reader,
                                 grpc_byte_buffer* buffer) {
  // Store the input buffer reference
  reader->buffer_in = buffer;
  
  // Handle different buffer types (currently only RAW is implemented)
  switch (reader->buffer_in->type) {
    case GRPC_BB_RAW:
      // For RAW buffers, output buffer is same as input
      reader->buffer_out = reader->buffer_in;
      // Initialize index to start reading from beginning
      reader->current.index = 0;
      break;
  }
  return 1;
}

// Destroys a byte buffer reader, cleaning up resources
// Parameters:
//   reader: Pointer to the reader structure to destroy
void grpc_byte_buffer_reader_destroy(grpc_byte_buffer_reader* reader) {
  // Null out the output buffer reference
  reader->buffer_out = nullptr;
}

// Peeks at the next slice in the buffer without consuming it
// Parameters:
//   reader: Initialized reader structure
//   slice: Output parameter for the peeked slice
// Returns:
//   1 if a slice was available, 0 otherwise
int grpc_byte_buffer_reader_peek(grpc_byte_buffer_reader* reader,
                                 grpc_slice** slice) {
  switch (reader->buffer_in->type) {
    case GRPC_BB_RAW: {
      // Get the slice buffer from the raw buffer
      grpc_slice_buffer* slice_buffer;
      slice_buffer = &reader->buffer_out->data.raw.slice_buffer;
      
      // Check if there are more slices available
      if (reader->current.index < slice_buffer->count) {
        // Return the current slice and advance the index
        *slice = &slice_buffer->slices[reader->current.index];
        reader->current.index += 1;
        return 1;
      }
      break;
    }
  }
  return 0;
}

// Reads the next slice from the buffer
// Parameters:
//   reader: Initialized reader structure
//   slice: Output parameter for the read slice
// Returns:
//   1 if a slice was read, 0 otherwise
int grpc_byte_buffer_reader_next(grpc_byte_buffer_reader* reader,
                                 grpc_slice* slice) {
  switch (reader->buffer_in->type) {
    case GRPC_BB_RAW: {
      // Get the slice buffer from the raw buffer
      grpc_slice_buffer* slice_buffer;
      slice_buffer = &reader->buffer_out->data.raw.slice_buffer;
      
      // Check if there are more slices available
      if (reader->current.index < slice_buffer->count) {
        // Copy and reference the current slice, then advance the index
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

// Reads all remaining data from the buffer and concatenates it into a single slice
// Parameters:
//   reader: Initialized reader structure
// Returns:
//   A new slice containing all remaining data
grpc_slice grpc_byte_buffer_reader_readall(grpc_byte_buffer_reader* reader) {
  grpc_slice in_slice;
  size_t bytes_read = 0;
  
  // Get total size of remaining data
  const size_t input_size = grpc_byte_buffer_length(reader->buffer_out);
  
  // Allocate output slice of appropriate size
  grpc_slice out_slice = GRPC_SLICE_MALLOC(input_size);
  uint8_t* const outbuf = GRPC_SLICE_START_PTR(out_slice);

  // Create execution context for reference counting
  grpc_core::ExecCtx exec_ctx;
  
  // Read all slices sequentially
  while (grpc_byte_buffer_reader_next(reader, &in_slice) != 0) {
    const size_t slice_length = GRPC_SLICE_LENGTH(in_slice);
    // Copy slice data to output buffer
    memcpy(&(outbuf[bytes_read]), GRPC_SLICE_START_PTR(in_slice), slice_length);
    bytes_read += slice_length;
    // Release the input slice reference
    grpc_core::CSliceUnref(in_slice);
    // Safety check to ensure we don't overflow the output buffer
    CHECK(bytes_read <= input_size);
  }

  return out_slice;
}
```