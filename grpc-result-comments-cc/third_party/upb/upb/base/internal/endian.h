Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_BASE_INTERNAL_ENDIAN_H_
#define UPB_BASE_INTERNAL_ENDIAN_H_

#include <stdint.h>

#include "upb/port/def.inc"

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determines if the system is little-endian.
 * @return true if the system is little-endian, false otherwise.
 * 
 * This works by checking the byte representation of the integer 1.
 * On little-endian systems, the least significant byte comes first (0x01).
 * On big-endian systems, the most significant byte comes first (0x00).
 */
UPB_INLINE bool upb_IsLittleEndian(void) {
  const int x = 1;
  return *(char*)&x == 1;
}

/**
 * Converts a 32-bit value to big-endian (network) byte order.
 * @param val The 32-bit value to convert
 * @return The value in big-endian byte order
 * 
 * If the system is already big-endian, returns the value unchanged.
 * For little-endian systems, reverses the byte order.
 */
UPB_INLINE uint32_t upb_BigEndian32(uint32_t val) {
  if (upb_IsLittleEndian()) return val;

  // Byte swapping:
  // Move byte 0 to position 3, byte 1 to position 2,
  // byte 2 to position 1, and byte 3 to position 0
  return ((val & 0xff) << 24) | ((val & 0xff00) << 8) |
         ((val & 0xff0000) >> 8) | ((val & 0xff000000) >> 24);
}

/**
 * Converts a 64-bit value to big-endian (network) byte order.
 * @param val The 64-bit value to convert
 * @return The value in big-endian byte order
 * 
 * If the system is already big-endian, returns the value unchanged.
 * For little-endian systems, reverses the byte order by treating
 * the value as two 32-bit halves and swapping each half.
 */
UPB_INLINE uint64_t upb_BigEndian64(uint64_t val) {
  if (upb_IsLittleEndian()) return val;

  // Convert upper and lower 32-bit halves separately
  const uint64_t hi = ((uint64_t)upb_BigEndian32((uint32_t)val)) << 32;
  const uint64_t lo = upb_BigEndian32((uint32_t)(val >> 32));
  return hi | lo;
}

// End C++ compatibility
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_BASE_INTERNAL_ENDIAN_H_
```

The comments explain:
1. The purpose of each function
2. The endianness detection mechanism
3. The byte-swapping logic for both 32-bit and 64-bit values
4. The handling of both little-endian and big-endian systems
5. The structure of the header file (guards, includes, C++ compatibility)

The comments are designed to help future developers understand:
- Why these functions are needed
- How they work
- What assumptions they make
- How to use them correctly