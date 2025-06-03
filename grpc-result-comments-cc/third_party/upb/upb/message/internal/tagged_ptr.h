Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_
#define UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_

#include <stdint.h>

#include "upb/message/internal/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Packs a message pointer and an empty flag into a single tagged pointer.
// The least significant bit is used to store the empty flag (1 = empty).
// The pointer must be aligned (LSB = 0) to ensure the tag bit can be stored.
UPB_INLINE uintptr_t
UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(struct upb_Message* ptr, bool empty) {
  UPB_ASSERT(((uintptr_t)ptr & 1) == 0);  // Ensure pointer is properly aligned
  return (uintptr_t)ptr | (empty ? 1 : 0);  // Set LSB if empty
}

// Checks if the tagged pointer represents an empty message by examining LSB.
UPB_API_INLINE bool upb_TaggedMessagePtr_IsEmpty(uintptr_t ptr) {
  return ptr & 1;
}

// Extracts the message pointer from a tagged pointer by clearing the LSB.
UPB_INLINE struct upb_Message* UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(
    uintptr_t ptr) {
  return (struct upb_Message*)(ptr & ~(uintptr_t)1);
}

// Gets the message pointer from a tagged pointer that is known to be non-empty.
// Asserts if the pointer is actually empty.
UPB_API_INLINE struct upb_Message* upb_TaggedMessagePtr_GetNonEmptyMessage(
    uintptr_t ptr) {
  UPB_ASSERT(!upb_TaggedMessagePtr_IsEmpty(ptr));
  return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(ptr);
}

// Gets the message pointer from a tagged pointer that is known to be empty.
// Asserts if the pointer is actually non-empty.
UPB_INLINE struct upb_Message* UPB_PRIVATE(
    _upb_TaggedMessagePtr_GetEmptyMessage)(uintptr_t ptr) {
  UPB_ASSERT(upb_TaggedMessagePtr_IsEmpty(ptr));
  return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(ptr);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
```

The comments explain:
1. The purpose of each function
2. The tagged pointer technique being used (LSB as a flag)
3. The assertions and their purposes
4. The bit manipulation operations
5. The distinction between public and private APIs

The comments maintain a consistent style and provide enough detail to understand the code's purpose and implementation without being overly verbose.