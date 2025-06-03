Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_ENUM_H_
#define UPB_MINI_TABLE_INTERNAL_ENUM_H_

#include <stdint.h>

#include "upb/port/def.inc"

// Structure representing a mini table enum for protocol buffers.
// This compact representation is used for efficient enum value validation.
struct upb_MiniTableEnum {
  uint32_t UPB_PRIVATE(mask_limit);  // Threshold value where we switch from bitmask to linear search
  uint32_t UPB_PRIVATE(value_count); // Number of enum values stored beyond mask_limit
  uint32_t UPB_PRIVATE(data)[];      // Flexible array member containing:
                                     // 1) Bitmask for values < mask_limit
                                     // 2) Sorted enum values for values >= mask_limit
};

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Checks if a value is valid for the given enum.
/// @param e Pointer to the mini table enum structure
/// @param val Value to check
/// @return true if the value is valid for this enum, false otherwise
///
/// The function uses a three-tiered approach for efficiency:
/// 1. For values < 64: uses a 64-bit bitmask for O(1) lookup
/// 2. For values < mask_limit: uses 32-bit chunks of a bitmask
/// 3. For values >= mask_limit: performs linear search in a sorted array
UPB_API_INLINE bool upb_MiniTableEnum_CheckValue(
    const struct upb_MiniTableEnum* e, uint32_t val) {
  // Fast path for small values (most common case)
  if (UPB_LIKELY(val < 64)) {
    const uint64_t mask =
        e->UPB_PRIVATE(data)[0] | ((uint64_t)e->UPB_PRIVATE(data)[1] << 32);
    const uint64_t bit = 1ULL << val;
    return (mask & bit) != 0;
  }
  // Medium path for values within bitmask range
  if (UPB_LIKELY(val < e->UPB_PRIVATE(mask_limit))) {
    const uint32_t mask = e->UPB_PRIVATE(data)[val / 32];
    const uint32_t bit = 1U << (val % 32);
    return (mask & bit) != 0;
  }

  // Slow path for large values - linear search in sorted array
  const uint32_t* start =
      &e->UPB_PRIVATE(data)[e->UPB_PRIVATE(mask_limit) / 32];
  const uint32_t* limit = &e->UPB_PRIVATE(
      data)[e->UPB_PRIVATE(mask_limit) / 32 + e->UPB_PRIVATE(value_count)];
  for (const uint32_t* p = start; p < limit; p++) {
    if (*p == val) return true;
  }
  return false;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_INTERNAL_ENUM_H_
```

Key points about the comments:
1. Added documentation for the struct and its fields
2. Added detailed function documentation explaining the three-tiered approach
3. Added inline comments explaining each section of the value checking logic
4. Maintained all existing compiler directives and guards
5. Kept the original copyright notice
6. Added clear section markers for the different value checking paths

The comments explain both the high-level design (why the structure is organized this way) and the implementation details (how the value checking works at each level).