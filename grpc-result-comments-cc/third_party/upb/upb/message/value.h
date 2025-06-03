Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_VALUE_H_
#define UPB_MESSAGE_VALUE_H_

// Include necessary headers
#include <stdint.h>   // Standard integer types
#include <string.h>   // For memset()

#include "upb/base/string_view.h"       // For string view functionality
#include "upb/message/internal/types.h" // Internal message types

#include "upb/port/def.inc"             // Platform-specific definitions

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

// Union representing all possible types that can be stored in a protobuf message field.
// This allows type-safe storage and access to different field types.
typedef union {
  bool bool_val;                        // Boolean value
  float float_val;                      // 32-bit floating point value
  double double_val;                    // 64-bit floating point value
  int32_t int32_val;                    // 32-bit signed integer
  int64_t int64_val;                    // 64-bit signed integer
  uint32_t uint32_val;                  // 32-bit unsigned integer
  uint64_t uint64_val;                  // 64-bit unsigned integer
  const struct upb_Array* array_val;    // Pointer to array data
  const struct upb_Map* map_val;        // Pointer to map data
  const struct upb_Message* msg_val;    // Pointer to message data
  upb_StringView str_val;               // String view (pointer + length)

  uintptr_t tagged_msg_val;             // Tagged pointer for message values

  // Extension message value (using platform-specific macro for private access)
  struct upb_Message UPB_PRIVATE(ext_msg_val);
} upb_MessageValue;

// Returns a zero-initialized upb_MessageValue.
// This is useful for initializing fields to default/empty values.
UPB_API_INLINE upb_MessageValue upb_MessageValue_Zero(void) {
  upb_MessageValue zero;
  memset(&zero, 0, sizeof(zero));
  return zero;
}

// Union representing mutable variants of message value types.
// Used when we need to modify the contents rather than just read them.
typedef union {
  struct upb_Array* array;  // Mutable array pointer
  struct upb_Map* map;      // Mutable map pointer
  struct upb_Message* msg;  // Mutable message pointer
} upb_MutableMessageValue;

// Returns a zero-initialized upb_MutableMessageValue.
// Similar to upb_MessageValue_Zero but for mutable values.
UPB_API_INLINE upb_MutableMessageValue upb_MutableMessageValue_Zero(void) {
  upb_MutableMessageValue zero;
  memset(&zero, 0, sizeof(zero));
  return zero;
}

#ifdef __cplusplus
}  // extern "C"
#endif

#include "upb/port/undef.inc"  // Undo platform-specific definitions

#endif  // UPB_MESSAGE_VALUE_H_
```

Key points about the comments:
1. Added explanations for the purpose of each union and its fields
2. Documented the zero-initialization functions and their use cases
3. Explained the difference between upb_MessageValue and upb_MutableMessageValue
4. Added context for platform-specific macros and C++ compatibility
5. Maintained the original copyright notice and include guards
6. Kept the existing comments about C++ extern block
7. Added closing comments for #endif directives to show what they're closing

The comments aim to help future developers understand:
- What each type represents
- When to use which type
- The purpose of the zero-initialization functions
- The overall structure of the header file