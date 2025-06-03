Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_BASE_INTERNAL_LOG2_H_
#define UPB_BASE_INTERNAL_LOG2_H_

// Include platform-specific definitions
#include "upb/port/def.inc"

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Calculates the ceiling of base-2 logarithm of an integer.
 * 
 * @param x The input value (must be positive)
 * @return The smallest power of 2 that is >= x, or 0 if x <= 1
 * 
 * Note: Uses compiler intrinsics when available (GCC/Clang) for better performance,
 * otherwise falls back to a loop-based implementation.
 */
UPB_INLINE int upb_Log2Ceiling(int x) {
  if (x <= 1) return 0;  // Handle edge cases
#ifdef __GNUC__
  // Use GCC/Clang builtin function for counting leading zeros
  return 32 - __builtin_clz(x - 1);
#else
  // Portable implementation using a loop
  int lg2 = 0;
  while ((1 << lg2) < x) lg2++;
  return lg2;
#endif
}

/**
 * Rounds up an integer to the nearest power of two.
 * 
 * @param x The input value to round up
 * @return The smallest power of 2 that is >= x
 * 
 * Note: Returns 1 for x <= 1 (since 2^0 = 1)
 */
UPB_INLINE int upb_RoundUpToPowerOfTwo(int x) {
  return 1 << upb_Log2Ceiling(x);
}

// End C++ compatibility
#ifdef __cplusplus
}
#endif

// Undefine any platform-specific macros
#include "upb/port/undef.inc"

#endif  // UPB_BASE_INTERNAL_LOG2_H_
```

Key improvements in the comments:
1. Added detailed function documentation explaining purpose, parameters, and return values
2. Explained the platform-specific optimizations (GCC builtins vs portable implementation)
3. Clarified edge case behavior
4. Added comments for the header guard and include sections
5. Documented the C++ compatibility section
6. Added note about the power-of-two rounding behavior for small values

The comments now provide a clear understanding of what the code does, why certain implementation choices were made, and how to use the functions correctly.