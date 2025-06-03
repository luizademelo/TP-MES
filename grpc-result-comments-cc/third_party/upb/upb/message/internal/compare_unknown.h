Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_MESSAGE_INTERNAL_COMPARE_UNKNOWN_H_
#define UPB_MESSAGE_INTERNAL_COMPARE_UNKNOWN_H_

#include <stddef.h>  // For size_t type

// Include necessary headers for message handling and platform definitions
#include "upb/message/message.h"
#include "upb/port/def.inc"

// C++ compatibility: ensure the contents are compiled as C code if included in C++
#ifdef __cplusplus
extern "C" {
#endif

// Enumeration defining possible results when comparing unknown fields between messages
typedef enum {
  kUpb_UnknownCompareResult_Equal = 0,            // Unknown fields are identical
  kUpb_UnknownCompareResult_NotEqual = 1,         // Unknown fields differ
  kUpb_UnknownCompareResult_OutOfMemory = 2,      // Memory allocation failed during comparison
  kUpb_UnknownCompareResult_MaxDepthExceeded = 3, // Message nesting depth exceeded max_depth
} upb_UnknownCompareResult;

// Function declaration for comparing unknown fields between two messages
// Parameters:
//   msg1: First message to compare
//   msg2: Second message to compare
//   max_depth: Maximum recursion depth allowed when comparing nested messages
// Returns: upb_UnknownCompareResult indicating comparison outcome
upb_UnknownCompareResult UPB_PRIVATE(_upb_Message_UnknownFieldsAreEqual)(
    const upb_Message* msg1, const upb_Message* msg2, int max_depth);

// End C++ compatibility block
#ifdef __cplusplus
}
#endif

// Undefine any macros that might have been defined by the included port definitions
#include "upb/port/undef.inc"

#endif  // UPB_MESSAGE_INTERNAL_COMPARE_UNKNOWN_H_
```

The comments explain:
1. The purpose of each section of the header file
2. The meaning of each enum value in upb_UnknownCompareResult
3. The parameters and return value of the comparison function
4. The role of the C++ compatibility blocks
5. The purpose of the include guards and port definitions

The comments are designed to help future developers understand:
- What the code does at a high level
- How to use the provided functionality
- The possible outcomes of the comparison operation
- The structure and organization of the header file