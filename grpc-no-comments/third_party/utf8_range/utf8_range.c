// Copyright 2023 Google LLC

#include "utf8_range.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#if defined(__GNUC__)
#define FORCE_INLINE_ATTR __attribute__((always_inline))
#elif defined(_MSC_VER)
#define FORCE_INLINE_ATTR __forceinline
#else
#define FORCE_INLINE_ATTR
#endif

static FORCE_INLINE_ATTR inline uint64_t utf8_range_UnalignedLoad64(
    const void* p) {
  uint64_t t;
  memcpy(&t, p, sizeof t);
  return t;
}

static FORCE_INLINE_ATTR inline int utf8_range_AsciiIsAscii(unsigned char c) {
  return c < 128;
}

static FORCE_INLINE_ATTR inline int utf8_range_IsTrailByteOk(const char c) {
  return (int8_t)(c) <= (int8_t)(0xBF);
}

static size_t utf8_range_ValidateUTF8Naive(const char* data, const char* end,
                                           int return_position) {

  size_t err_pos = 0;
  size_t codepoint_bytes = 0;

  while (data + codepoint_bytes < end) {
    if (return_position) {
      err_pos += codepoint_bytes;
    }
    data += codepoint_bytes;
    const size_t len = end - data;
    const unsigned char byte1 = data[0];

    if (utf8_range_AsciiIsAscii(byte1)) {
      codepoint_bytes = 1;
      continue;
    }

    if (len >= 2 && byte1 >= 0xC2 && byte1 <= 0xDF &&
        utf8_range_IsTrailByteOk(data[1])) {
      codepoint_bytes = 2;
      continue;
    }
    if (len >= 3) {
      const unsigned char byte2 = data[1];
      const unsigned char byte3 = data[2];

      if (!utf8_range_IsTrailByteOk(byte2) ||
          !utf8_range_IsTrailByteOk(byte3)) {
        return err_pos;
      }

      if (
          ((byte1 == 0xE0 && byte2 >= 0xA0) ||

           (byte1 >= 0xE1 && byte1 <= 0xEC) ||

           (byte1 == 0xED && byte2 <= 0x9F) ||

           (byte1 >= 0xEE && byte1 <= 0xEF))) {
        codepoint_bytes = 3;
        continue;
      }
      if (len >= 4) {
        const unsigned char byte4 = data[3];

        if (!utf8_range_IsTrailByteOk(byte4)) {
          return err_pos;
        }

        if (
            ((byte1 == 0xF0 && byte2 >= 0x90) ||

             (byte1 >= 0xF1 && byte1 <= 0xF3) ||

             (byte1 == 0xF4 && byte2 <= 0x8F))) {
          codepoint_bytes = 4;
          continue;
        }
      }
    }
    return err_pos;
  }
  if (return_position) {
    err_pos += codepoint_bytes;
  }

  return err_pos + (1 - return_position);
}

#if defined(__SSE4_1__) || (defined(__ARM_NEON) && defined(__ARM_64BIT_STATE))

static inline int utf8_range_CodepointSkipBackwards(int32_t codepoint_word) {
  const int8_t* const codepoint = (const int8_t*)(&codepoint_word);
  if (!utf8_range_IsTrailByteOk(codepoint[3])) {
    return 1;
  } else if (!utf8_range_IsTrailByteOk(codepoint[2])) {
    return 2;
  } else if (!utf8_range_IsTrailByteOk(codepoint[1])) {
    return 3;
  }
  return 0;
}
#endif

static inline const char* utf8_range_SkipAscii(const char* data,
                                               const char* end) {
  while (8 <= end - data &&
         (utf8_range_UnalignedLoad64(data) & 0x8080808080808080) == 0) {
    data += 8;
  }
  while (data < end && utf8_range_AsciiIsAscii(*data)) {
    ++data;
  }
  return data;
}

#if defined(__SSE4_1__)
#include "utf8_range_sse.inc"
#elif defined(__ARM_NEON) && defined(__ARM_64BIT_STATE)
#include "utf8_range_neon.inc"
#endif

static FORCE_INLINE_ATTR inline size_t utf8_range_Validate(
    const char* data, size_t len, int return_position) {
  if (len == 0) return 1 - return_position;

  const char* const data_original = data;
  const char* const end = data + len;
  data = utf8_range_SkipAscii(data, end);

  if (end - data < 16) {
    return (return_position ? (data - data_original) : 0) +
           utf8_range_ValidateUTF8Naive(data, end, return_position);
  }
#if defined(__SSE4_1__) || (defined(__ARM_NEON) && defined(__ARM_64BIT_STATE))
  return utf8_range_ValidateUTF8Simd(
      data_original, data, end, return_position);
#else
  return (return_position ? (data - data_original) : 0) +
         utf8_range_ValidateUTF8Naive(data, end, return_position);
#endif
}

int utf8_range_IsValid(const char* data, size_t len) {
  return utf8_range_Validate(data, len, 0) != 0;
}

size_t utf8_range_ValidPrefix(const char* data, size_t len) {
  return utf8_range_Validate(data, len, 1);
}
