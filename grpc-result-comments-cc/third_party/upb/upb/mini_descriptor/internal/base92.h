Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_BASE92_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_BASE92_H_

#include <stdint.h>

#include "upb/base/internal/log2.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Converts a value (0-91) to its corresponding Base92 character.
// ch: Input value between 0 and 91 (inclusive)
// Returns: Corresponding Base92 character
UPB_INLINE char _upb_ToBase92(int8_t ch) {
  extern const char _kUpb_ToBase92[];  // Lookup table for Base92 encoding
  UPB_ASSERT(0 <= ch && ch < 92);     // Validate input range
  return _kUpb_ToBase92[ch];          // Return corresponding character
}

// Converts a Base92 character to its numerical value (0-91).
// ch: Input character (ASCII value)
// Returns: Numerical value (0-91) or -1 if invalid character
UPB_INLINE char _upb_FromBase92(uint8_t ch) {
  extern const int8_t _kUpb_FromBase92[];  // Lookup table for Base92 decoding
  if (' ' > ch || ch > '~') return -1;     // Check if character is in valid ASCII range
  return _kUpb_FromBase92[ch - ' '];       // Return numerical value from lookup table
}

// Decodes a variable-length integer encoded in Base92 format.
// ptr: Pointer to start of encoded string
// end: Pointer to end of encoded string
// first_ch: First character of the encoded value
// min: Minimum valid Base92 character in this encoding
// max: Maximum valid Base92 character in this encoding
// out_val: Output parameter for the decoded value
// Returns: Pointer to next character after the decoded value, or NULL on error
UPB_INLINE const char* _upb_Base92_DecodeVarint(const char* ptr,
                                                const char* end, char first_ch,
                                                uint8_t min, uint8_t max,
                                                uint32_t* out_val) {
  uint32_t val = 0;        // Accumulated decoded value
  uint32_t shift = 0;      // Current bit shift position
  // Calculate bits per character based on the range of valid characters
  const int bits_per_char =
      upb_Log2Ceiling(_upb_FromBase92(max) - _upb_FromBase92(min));
  
  char ch = first_ch;      // Start with the first provided character
  while (1) {
    // Get numerical value of current character and adjust for minimum value
    uint32_t bits = _upb_FromBase92(ch) - _upb_FromBase92(min);
    val |= bits << shift;  // Add bits to the accumulated value
    
    // Check for end of input or invalid character
    if (ptr == end || *ptr < min || max < *ptr) {
      *out_val = val;      // Store decoded value
      UPB_ASSUME(ptr != NULL);
      return ptr;          // Return current position
    }
    
    ch = *ptr++;           // Move to next character
    shift += bits_per_char; // Increase shift for next character
    
    // Prevent overflow (32-bit maximum)
    if (shift >= 32) return NULL;
  }
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MINI_DESCRIPTOR_INTERNAL_BASE92_H_
```

Key improvements made:
1. Added detailed function descriptions explaining purpose, parameters, and return values
2. Added comments for important variables and operations
3. Explained the Base92 encoding/decoding mechanism
4. Documented the variable-length integer decoding algorithm
5. Added clear markers for input validation and error conditions
6. Maintained the original code structure while making it more understandable

The comments now provide a clear understanding of the Base92 encoding/decoding implementation and its usage for variable-length integers.