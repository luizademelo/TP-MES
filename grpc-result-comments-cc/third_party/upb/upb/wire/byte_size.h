Here's the commented version of the code:

```c++
// Copyright 2024 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_WIRE_BYTE_SIZE_H_
#define UPB_WIRE_BYTE_SIZE_H_

#include <stddef.h>  // For size_t type

// Include necessary headers for upb (universal protobuf) message handling
#include "upb/message/message.h"      // For upb_Message type
#include "upb/mini_table/message.h"   // For upb_MiniTable type

// Include platform-specific definitions
#include "upb/port/def.inc"

// C++ compatibility: if compiled as C++, ensure the function has C linkage
#ifdef __cplusplus
extern "C" {
#endif

// Function declaration for calculating the byte size of a protobuf message
// Parameters:
//   msg: Pointer to the message object whose size should be calculated
//   mt: Pointer to the mini-table containing message metadata
// Returns:
//   The size in bytes of the serialized message
UPB_API size_t upb_ByteSize(const upb_Message* msg, const upb_MiniTable* mt);

// End of C linkage section for C++
#ifdef __cplusplus
}
#endif

// Undefine any platform-specific macros that were defined earlier
#include "upb/port/undef.inc"

#endif  // UPB_WIRE_BYTE_SIZE_H_
```

The comments explain:
1. The purpose of the header guard
2. The included headers and their purposes
3. The C++ compatibility section
4. The function declaration and its parameters
5. The platform-specific macro handling
6. The closing of the header guard

The comments are designed to help future developers understand:
- The overall structure of the header file
- The dependencies and why they're included
- The purpose and usage of the declared function
- The cross-platform and cross-language considerations