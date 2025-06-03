Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/lib/compression/message_compress.h"

#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>
#include <zconf.h>
#include <zlib.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/slice/slice.h"

// Define the block size for output buffer allocation
#define OUTPUT_BLOCK_SIZE 1024

// Core zlib processing function that handles both compression and decompression
// Parameters:
//   zs - z_stream object for zlib operations
//   input - buffer containing data to process
//   output - buffer to store processed data
//   flate - function pointer to either deflate (compress) or inflate (decompress)
// Returns:
//   1 on success, 0 on failure
static int zlib_body(z_stream* zs, grpc_slice_buffer* input,
                     grpc_slice_buffer* output,
                     int (*flate)(z_stream* zs, int flush)) {
  int r = Z_STREAM_END;  // Return code from zlib operations
  int flush;             // Flush mode for zlib
  size_t i;              // Loop counter
  // Allocate output buffer slice
  grpc_slice outbuf = GRPC_SLICE_MALLOC(OUTPUT_BLOCK_SIZE);
  const uInt uint_max = ~uInt{0};  // Maximum unsigned int value

  // Verify output buffer size doesn't exceed zlib's maximum
  CHECK(GRPC_SLICE_LENGTH(outbuf) <= uint_max);
  zs->avail_out = static_cast<uInt> GRPC_SLICE_LENGTH(outbuf);
  zs->next_out = GRPC_SLICE_START_PTR(outbuf);
  flush = Z_NO_FLUSH;  // Initial flush mode

  // Process each slice in the input buffer
  for (i = 0; i < input->count; i++) {
    // Set Z_FINISH flush mode for last input slice
    if (i == input->count - 1) flush = Z_FINISH;
    
    CHECK(GRPC_SLICE_LENGTH(input->slices[i]) <= uint_max);
    zs->avail_in = static_cast<uInt> GRPC_SLICE_LENGTH(input->slices[i]);
    zs->next_in = GRPC_SLICE_START_PTR(input->slices[i]);
    
    // Process current input slice
    do {
      // If output buffer is full, add it to output and allocate new buffer
      if (zs->avail_out == 0) {
        grpc_slice_buffer_add_indexed(output, outbuf);
        outbuf = GRPC_SLICE_MALLOC(OUTPUT_BLOCK_SIZE);
        CHECK(GRPC_SLICE_LENGTH(outbuf) <= uint_max);
        zs->avail_out = static_cast<uInt> GRPC_SLICE_LENGTH(outbuf);
        zs->next_out = GRPC_SLICE_START_PTR(outbuf);
      }
      // Perform compression/decompression
      r = flate(zs, flush);
      if (r < 0 && r != Z_BUF_ERROR ) {
        VLOG(2) << "zlib error (" << r << ")";
        goto error;
      }
    } while (zs->avail_out == 0);  // Continue while output buffer is full
    
    // Check if all input was consumed
    if (zs->avail_in) {
      VLOG(2) << "zlib: not all input consumed";
      goto error;
    }
  }
  
  // Verify stream was properly completed
  if (r != Z_STREAM_END) {
    VLOG(2) << "zlib: Data error";
    goto error;
  }

  // Add remaining output to buffer
  CHECK(outbuf.refcount);
  outbuf.data.refcounted.length -= zs->avail_out;
  grpc_slice_buffer_add_indexed(output, outbuf);

  return 1;  // Success

error:
  // Cleanup on error
  grpc_core::CSliceUnref(outbuf);
  return 0;  // Failure
}

// Custom zlib memory allocation function using gRPC's allocator
static void* zalloc_gpr(void* , unsigned int items,
                        unsigned int size) {
  return gpr_malloc(items * size);
}

// Custom zlib memory deallocation function using gRPC's allocator
static void zfree_gpr(void* , void* address) { gpr_free(address); }

// Compress input buffer using zlib
// Parameters:
//   input - buffer to compress
//   output - buffer to store compressed data
//   gzip - if true, use gzip format; otherwise use deflate
// Returns:
//   1 if compression succeeded and output is smaller than input, 0 otherwise
static int zlib_compress(grpc_slice_buffer* input, grpc_slice_buffer* output,
                         int gzip) {
  z_stream zs;
  int r;
  size_t i;
  // Remember initial output state for rollback on failure
  size_t count_before = output->count;
  size_t length_before = output->length;
  
  memset(&zs, 0, sizeof(zs));
  zs.zalloc = zalloc_gpr;  // Set custom allocators
  zs.zfree = zfree_gpr;
  
  // Initialize zlib with appropriate parameters
  r = deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 | (gzip ? 16 : 0),
                   8, Z_DEFAULT_STRATEGY);
  CHECK(r == Z_OK);
  
  // Perform compression and verify output is smaller than input
  r = zlib_body(&zs, input, output, deflate) && output->length < input->length;
  
  // Rollback output buffer if compression failed
  if (!r) {
    for (i = count_before; i < output->count; i++) {
      grpc_core::CSliceUnref(output->slices[i]);
    }
    output->count = count_before;
    output->length = length_before;
  }
  
  deflateEnd(&zs);  // Clean up zlib
  return r;
}

// Decompress input buffer using zlib
// Parameters:
//   input - buffer to decompress
//   output - buffer to store decompressed data
//   gzip - if true, expect gzip format; otherwise expect deflate
// Returns:
//   1 on success, 0 on failure
static int zlib_decompress(grpc_slice_buffer* input, grpc_slice_buffer* output,
                           int gzip) {
  z_stream zs;
  int r;
  size_t i;
  // Remember initial output state for rollback on failure
  size_t count_before = output->count;
  size_t length_before = output->length;
  
  memset(&zs, 0, sizeof(zs));
  zs.zalloc = zalloc_gpr;  // Set custom allocators
  zs.zfree = zfree_gpr;
  
  // Initialize zlib with appropriate parameters
  r = inflateInit2(&zs, 15 | (gzip ? 16 : 0));
  CHECK(r == Z_OK);
  
  // Perform decompression
  r = zlib_body(&zs, input, output, inflate);
  
  // Rollback output buffer if decompression failed
  if (!r) {
    for (i = count_before; i < output->count; i++) {
      grpc_core::CSliceUnref(output->slices[i]);
    }
    output->count = count_before;
    output->length = length_before;
  }
  
  inflateEnd(&zs);  // Clean up zlib
  return r;
}

// Copy input buffer to output buffer without modification
// Parameters:
//   input - source buffer
//   output - destination buffer
// Returns:
//   1 (always succeeds)
static int copy(grpc_slice_buffer* input, grpc_slice_buffer* output) {
  size_t i;
  for (i = 0; i < input->count; i++) {
    grpc_slice_buffer_add(output, grpc_core::CSliceRef(input->slices[i]));
  }
  return 1;
}

// Internal compression function that selects algorithm implementation
// Parameters:
//   algorithm - compression algorithm to use
//   input - buffer to compress
//   output - buffer to store compressed data
// Returns:
//   1 on success, 0 on failure
static int compress_inner(grpc_compression_algorithm algorithm,
                          grpc_slice_buffer* input, grpc_slice_buffer* output) {
  switch (algorithm) {
    case GRPC_COMPRESS_NONE:
      // No compression requested
      return 0;
    case GRPC_COMPRESS_DEFLATE:
      // Use deflate format
      return zlib_compress(input, output, 0);
    case GRPC_COMPRESS_GZIP:
      // Use gzip format
      return zlib_compress(input, output, 1);
    case GRPC_COMPRESS_ALGORITHMS_COUNT:
      break;
  }
  LOG(ERROR) << "invalid compression algorithm " << algorithm;
  return 0;
}

// Public interface for message compression
// Parameters:
//   algorithm - compression algorithm to use
//   input - buffer to compress
//   output - buffer to store compressed data
// Returns:
//   1 if compression succeeded, 0 otherwise (falls back to copying input)
int grpc_msg_compress(grpc_compression_algorithm algorithm,
                      grpc_slice_buffer* input, grpc_slice_buffer* output) {
  if (!compress_inner(algorithm, input, output)) {
    // If compression fails, copy input to output
    copy(input, output);
    return 0;
  }
  return 1;
}

// Public interface for message decompression
// Parameters:
//   algorithm - compression algorithm used
//   input - buffer to decompress
//   output - buffer to store decompressed data
// Returns:
//   1 on success, 0 on failure
int grpc_msg_decompress(grpc_compression_algorithm algorithm,
                        grpc_slice_buffer* input, grpc_slice_buffer* output) {
  switch (algorithm) {
    case GRPC_COMPRESS_NONE:
      // No compression was used, just copy
      return copy(input, output);
    case GRPC_COMPRESS_DEFLATE:
      // Decompress deflate format
      return zlib_decompress(input, output, 0);
    case GRPC_COMPRESS_GZIP:
      // Decompress gzip format
      return zlib_decompress(input, output, 1);
    case GRPC_COMPRESS_ALGORITHMS_COUNT:
      break;
  }
  LOG(ERROR) << "invalid compression algorithm " << algorithm;
  return 0;
}
```