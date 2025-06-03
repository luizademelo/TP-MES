Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_MESSAGE_INTERNAL_TYPES_H_
#define UPB_MESSAGE_INTERNAL_TYPES_H_

#include <stdint.h>

#include "upb/port/def.inc"

// Macro to create an opaque identifier by appending "_opaque" to the input
#define UPB_OPAQUE(x) x##_opaque

// Main message structure definition
struct upb_Message {
  union {
    // Internal representation that can also be used to store a double
    // The least significant bit is used to track frozen state
    uintptr_t UPB_OPAQUE(internal);
    double d;  // Alternative interpretation of the same memory as a double
  };
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Freezes a message by setting the least significant bit of internal
 * @param msg Pointer to the message to freeze
 * @note This is a private/internal API function
 */
UPB_INLINE void UPB_PRIVATE(_upb_Message_ShallowFreeze)(
    struct upb_Message* msg) {
  msg->UPB_OPAQUE(internal) |= 1ULL;
}

/**
 * @brief Checks if a message is frozen
 * @param msg Pointer to the message to check
 * @return true if the message is frozen (LSB set), false otherwise
 * @note This is a public API function
 */
UPB_API_INLINE bool upb_Message_IsFrozen(const struct upb_Message* msg) {
  return (msg->UPB_OPAQUE(internal) & 1ULL) != 0;
}

/**
 * @brief Gets the internal representation of a message
 * @param msg Pointer to the message
 * @return Pointer to the internal message structure
 * @note This masks off the frozen bit before returning the pointer
 * @note This is a private/internal API function
 */
UPB_INLINE struct upb_Message_Internal* UPB_PRIVATE(_upb_Message_GetInternal)(
    const struct upb_Message* msg) {
  const uintptr_t tmp = msg->UPB_OPAQUE(internal) & ~1ULL;
  return (struct upb_Message_Internal*)tmp;
}

/**
 * @brief Sets the internal representation of a message
 * @param msg Pointer to the message to modify
 * @param internal Pointer to the new internal representation
 * @note Asserts that the message is not frozen before modification
 * @note This is a private/internal API function
 */
UPB_INLINE void UPB_PRIVATE(_upb_Message_SetInternal)(
    struct upb_Message* msg, struct upb_Message_Internal* internal) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  msg->UPB_OPAQUE(internal) = (uintptr_t)internal;
}

#ifdef __cplusplus
}  // extern "C"
#endif

// Clean up the macro definition
#undef UPB_OPAQUE

#include "upb/port/undef.inc"

#endif  // UPB_MESSAGE_INTERNAL_TYPES_H_
```

Key points explained in the comments:
1. Header guards and includes are documented
2. The UPB_OPAQUE macro's purpose is explained
3. The upb_Message structure's dual-purpose union is documented
4. Each function has a clear description of its purpose and behavior
5. The freezing mechanism (using LSB of the pointer) is explained
6. Public vs private API functions are noted
7. Important implementation details (like pointer masking) are called out
8. Assertion conditions are documented

The comments maintain a consistent style and provide enough information for future maintainers to understand the code's purpose and behavior without being overly verbose.