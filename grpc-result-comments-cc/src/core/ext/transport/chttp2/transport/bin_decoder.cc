Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/bin_decoder.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "absl/base/attributes.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/slice/slice.h"

// Base64 decoding table that maps ASCII characters to their 6-bit values
// 0x40 is used as an invalid marker for characters not in the Base64 alphabet
static uint8_t decode_table[] = {
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 62,   0x40, 0x40, 0x40, 63,
    52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0,    1,    2,    3,    4,    5,    6,
    7,    8,    9,    10,   11,   12,   13,   14,   15,   16,   17,   18,
    19,   20,   21,   22,   23,   24,   25,   0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 26,   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
    37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
    49,   50,   51,   0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40};

// Table for handling the tail end of Base64 input (non-multiple of 4 bytes)
// Maps remaining bytes (1-3) to output bytes needed (0-2)
static const uint8_t tail_xtra[4] = {0, 0, 1, 2};

// Validates that all characters in the input are valid Base64 characters
// Returns false if any invalid character is found
static bool input_is_valid(const uint8_t* input_ptr, size_t length) {
  size_t i;

  for (i = 0; i < length; ++i) {
    // Check if character is invalid (marked by 0xC0 in decode table)
    if (GPR_UNLIKELY((decode_table[input_ptr[i]] & 0xC0) != 0)) {
      LOG(ERROR) << "Base64 decoding failed, invalid character '"
                 << static_cast<char>(*input_ptr) << "' in base64 input.\n";
      return false;
    }
  }
  return true;
}

// Macros to compose output bytes from 4 input bytes (Base64 decoding)
#define COMPOSE_OUTPUT_BYTE_0(input_ptr)          \
  (uint8_t)((decode_table[(input_ptr)[0]] << 2) | \
            (decode_table[(input_ptr)[1]] >> 4))

#define COMPOSE_OUTPUT_BYTE_1(input_ptr)          \
  (uint8_t)((decode_table[(input_ptr)[1]] << 4) | \
            (decode_table[(input_ptr)[2]] >> 2))

#define COMPOSE_OUTPUT_BYTE_2(input_ptr) \
  (uint8_t)((decode_table[(input_ptr)[2]] << 6) | decode_table[(input_ptr)[3]])

// Calculates the length of decoded data from Base64 input
// Handles padding characters ('=') and validates input length
size_t grpc_chttp2_base64_infer_length_after_decode(const grpc_slice& slice) {
  size_t len = GRPC_SLICE_LENGTH(slice);
  const uint8_t* bytes = GRPC_SLICE_START_PTR(slice);
  
  // Skip padding characters at the end
  while (len > 0 && bytes[len - 1] == '=') {
    len--;
  }
  
  // Validate padding length (max 2 '=' characters allowed)
  if (GPR_UNLIKELY(GRPC_SLICE_LENGTH(slice) - len > 2)) {
    LOG(ERROR) << "Base64 decoding failed. Input has more than 2 paddings.";
    return 0;
  }
  
  size_t tuples = len / 4;  // Number of 4-byte groups
  size_t tail_case = len % 4;  // Remaining bytes (0-3)
  
  // Validate tail case (1 remaining byte is invalid in Base64)
  if (GPR_UNLIKELY(tail_case == 1)) {
    LOG(ERROR) << "Base64 decoding failed. Input has a length of " << len
               << " (without padding), which is invalid.\n";
    return 0;
  }
  
  // Calculate output length: 3 bytes per 4-byte group plus tail bytes
  return (tuples * 3) + tail_xtra[tail_case];
}

// Performs partial Base64 decoding of a context structure
// Handles both complete 4-byte groups and tail cases
bool grpc_base64_decode_partial(struct grpc_base64_decode_context* ctx) {
  size_t input_tail;

  // Validate input/output buffer boundaries
  if (ctx->input_cur > ctx->input_end || ctx->output_cur > ctx->output_end) {
    return false;
  }

  // Process complete 4-byte groups while we have space
  while (ctx->input_end >= ctx->input_cur + 4 &&
         ctx->output_end >= ctx->output_cur + 3) {
    if (!input_is_valid(ctx->input_cur, 4)) return false;
    ctx->output_cur[0] = COMPOSE_OUTPUT_BYTE_0(ctx->input_cur);
    ctx->output_cur[1] = COMPOSE_OUTPUT_BYTE_1(ctx->input_cur);
    ctx->output_cur[2] = COMPOSE_OUTPUT_BYTE_2(ctx->input_cur);
    ctx->output_cur += 3;
    ctx->input_cur += 4;
  }

  // Handle remaining bytes (tail case)
  input_tail = static_cast<size_t>(ctx->input_end - ctx->input_cur);
  
  // Special case: exactly 4 bytes with padding
  if (input_tail == 4) {
    if (ctx->input_cur[3] == '=') {
      if (ctx->input_cur[2] == '=' && ctx->output_end >= ctx->output_cur + 1) {
        // Case: 2 padding characters (output 1 byte)
        if (!input_is_valid(ctx->input_cur, 2)) return false;
        *(ctx->output_cur++) = COMPOSE_OUTPUT_BYTE_0(ctx->input_cur);
        ctx->input_cur += 4;
      } else if (ctx->output_end >= ctx->output_cur + 2) {
        // Case: 1 padding character (output 2 bytes)
        if (!input_is_valid(ctx->input_cur, 3)) return false;
        *(ctx->output_cur++) = COMPOSE_OUTPUT_BYTE_0(ctx->input_cur);
        *(ctx->output_cur++) = COMPOSE_OUTPUT_BYTE_1(ctx->input_cur);
        ctx->input_cur += 4;
      }
    }
  } 
  // Handle other tail cases (when contains_tail is true)
  else if (ctx->contains_tail && input_tail > 1) {
    if (ctx->output_end >= ctx->output_cur + tail_xtra[input_tail]) {
      if (!input_is_valid(ctx->input_cur, input_tail)) return false;
      switch (input_tail) {
        case 3:
          ctx->output_cur[1] = COMPOSE_OUTPUT_BYTE_1(ctx->input_cur);
          [[fallthrough]];
        case 2:
          ctx->output_cur[0] = COMPOSE_OUTPUT_BYTE_0(ctx->input_cur);
      }
      ctx->output_cur += tail_xtra[input_tail];
      ctx->input_cur += input_tail;
    }
  }

  return true;
}

// Decodes a Base64-encoded grpc_slice into binary data
// Allocates and returns a new slice with decoded data
grpc_slice grpc_chttp2_base64_decode(const grpc_slice& input) {
  size_t input_length = GRPC_SLICE_LENGTH(input);
  size_t output_length = input_length / 4 * 3;  // Initial estimate
  struct grpc_base64_decode_context ctx;
  grpc_slice output;

  // Input length must be a multiple of 4
  if (GPR_UNLIKELY(input_length % 4 != 0)) {
    LOG(ERROR) << "Base64 decoding failed, input of "
                  "grpc_chttp2_base64_decode has a length of "
               << input_length << ", which is not a multiple of 4.\n";
    return grpc_empty_slice();
  }

  // Adjust output length for padding
  if (input_length > 0) {
    const uint8_t* input_end = GRPC_SLICE_END_PTR(input);
    if (*(--input_end) == '=') {
      output_length--;
      if (*(--input_end) == '=') {
        output_length--;
      }
    }
  }
  
  // Allocate output slice
  output = GRPC_SLICE_MALLOC(output_length);

  // Set up decoding context
  ctx.input_cur = GRPC_SLICE_START_PTR(input);
  ctx.input_end = GRPC_SLICE_END_PTR(input);
  ctx.output_cur = GRPC_SLICE_START_PTR(output);
  ctx.output_end = GRPC_SLICE_END_PTR(output);
  ctx.contains_tail = false;

  // Perform decoding
  if (GPR_UNLIKELY(!grpc_base64_decode_partial(&ctx))) {
    char* s = grpc_slice_to_c_string(input);
    LOG(ERROR) << "Base64 decoding failed, input string:\n" << s << "\n";
    gpr_free(s);
    grpc_core::CSliceUnref(output);
    return grpc_empty_slice();
  }
  
  // Verify we processed all input and filled all output
  CHECK(ctx.output_cur == GRPC_SLICE_END_PTR(output));
  CHECK(ctx.input_cur == GRPC_SLICE_END_PTR(input));
  return output;
}

// Decodes a Base64-encoded grpc_slice with known output length
// Useful when output length is known in advance
grpc_slice grpc_chttp2_base64_decode_with_length(const grpc_slice& input,
                                                 size_t output_length) {
  size_t input_length = GRPC_SLICE_LENGTH(input);
  grpc_slice output = GRPC_SLICE_MALLOC(output_length);
  struct grpc_base64_decode_context ctx;

  // Validate input length (tail of 1 byte is invalid)
  if (GPR_UNLIKELY(input_length % 4 == 1)) {
    LOG(ERROR) << "Base64 decoding failed, input of "
                  "grpc_chttp2_base64_decode_with_length has a length of "
               << input_length << ", which has a tail of 1 byte.\n";
    grpc_core::CSliceUnref(output);
    return grpc_empty_slice();
  }

  // Validate output length doesn't exceed maximum possible
  if (GPR_UNLIKELY(output_length >
                   input_length / 4 * 3 + tail_xtra[input_length % 4])) {
    LOG(ERROR) << "Base64 decoding failed, output_length " << output_length
               << " is longer than the max possible output length "
               << ((input_length / 4 * 3) + tail_xtra[input_length % 4])
               << ".\n";
    grpc_core::CSliceUnref(output);
    return grpc_empty_slice();
  }

  // Set up decoding context
  ctx.input_cur = GRPC_SLICE_START_PTR(input);
  ctx.input_end = GRPC_SLICE_END_PTR(input);
  ctx.output_cur = GRPC_SLICE_START_PTR(output);
  ctx.output_end = GRPC_SLICE_END_PTR(output);
  ctx.contains_tail = true;  // Enable tail processing

  // Perform decoding
  if (GPR_UNLIKELY(!grpc_base64_decode_partial(&ctx))) {
    char* s = grpc_slice_to_c_string(input);
    LOG(ERROR) << "Base64 decoding failed, input string:\n" << s << "\n";
    gpr_free(s);
    grpc_core::CSliceUnref(output);
    return grpc_empty_slice();
  }
  
  // Verify we produced exactly the expected output
  CHECK(ctx.output_cur == GRPC_SLICE_END_PTR(output));
  // Input may not be fully consumed in contains_tail mode
  CHECK(ctx.input_cur <= GRPC_SLICE_END_PTR(input));
  return output;
}
```