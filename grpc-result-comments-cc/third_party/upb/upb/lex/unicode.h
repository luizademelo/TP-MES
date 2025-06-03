Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_LEX_UNICODE_H_
#define UPB_LEX_UNICODE_H_

#include <stdint.h>

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Checks if the given Unicode code point is a high surrogate (lead surrogate).
// High surrogates are in the range 0xD800-0xDBFF.
UPB_INLINE bool upb_Unicode_IsHigh(uint32_t cp) {
  return (cp >= 0xd800 && cp <= 0xdbff);
}

// Checks if the given Unicode code point is a low surrogate (trail surrogate).
// Low surrogates are in the range 0xDC00-0xDFFF.
UPB_INLINE bool upb_Unicode_IsLow(uint32_t cp) {
  return (cp >= 0xdc00 && cp <= 0xdfff);
}

// Converts a Unicode code point to a high surrogate (lead surrogate).
// This is used for UTF-16 encoding of supplementary characters (those beyond BMP).
UPB_INLINE uint16_t upb_Unicode_ToHigh(uint32_t cp) {
  return (cp >> 10) + 0xd7c0;
}

// Converts a Unicode code point to a low surrogate (trail surrogate).
// This is used for UTF-16 encoding of supplementary characters (those beyond BMP).
UPB_INLINE uint16_t upb_Unicode_ToLow(uint32_t cp) {
  return (cp & 0x3ff) | 0xdc00;
}

// Combines a high and low surrogate pair into a single Unicode code point.
// This reconstructs supplementary characters from their UTF-16 surrogate pairs.
UPB_INLINE uint32_t upb_Unicode_FromPair(uint32_t high, uint32_t low) {
  return ((high & 0x3ff) << 10) + (low & 0x3ff) + 0x10000;
}

// Converts a Unicode code point to its UTF-8 encoding.
// Returns the number of bytes written to 'out' (1-4).
// 'out' must have enough space for the UTF-8 encoding (at least 4 bytes).
int upb_Unicode_ToUTF8(uint32_t cp, char* out);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_LEX_UNICODE_H_
```

The comments explain:
1. The purpose of each function
2. The range of valid inputs for surrogate checks
3. The transformation being performed in each conversion function
4. The behavior and requirements of the UTF-8 conversion function
5. Maintained the existing header guards and C++ compatibility markers

The comments are concise but provide enough information for a developer to understand:
- What each function does
- The expected input ranges
- The purpose of the operations
- Any important preconditions or requirements