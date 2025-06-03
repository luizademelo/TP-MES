Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_MINI_TABLE_SUB_H_
#define UPB_MINI_TABLE_SUB_H_

// Include necessary headers for enum, internal sub implementation, and message functionality
#include "upb/mini_table/enum.h"
#include "upb/mini_table/internal/sub.h"
#include "upb/mini_table/message.h"

// Include platform-specific definitions
#include "upb/port/def.inc"

// Forward declaration of upb_MiniTableSub union type
typedef union upb_MiniTableSub upb_MiniTableSub;

// C++ compatibility block
#ifdef __cplusplus
extern "C" {
#endif

// API function to create a MiniTableSub from an enum descriptor
// @param subenum Pointer to the enum descriptor
// @return MiniTableSub union containing the enum descriptor
UPB_API_INLINE upb_MiniTableSub
upb_MiniTableSub_FromEnum(const upb_MiniTableEnum* subenum);

// API function to create a MiniTableSub from a message descriptor
// @param submsg Pointer to the message descriptor
// @return MiniTableSub union containing the message descriptor
UPB_API_INLINE upb_MiniTableSub
upb_MiniTableSub_FromMessage(const upb_MiniTable* submsg);

// API function to extract enum descriptor from MiniTableSub
// @param sub MiniTableSub union to inspect
// @return Pointer to the contained enum descriptor (or NULL if not an enum)
UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTableSub_Enum(
    upb_MiniTableSub sub);

// API function to extract message descriptor from MiniTableSub
// @param sub MiniTableSub union to inspect
// @return Pointer to the contained message descriptor (or NULL if not a message)
UPB_API_INLINE const upb_MiniTable* upb_MiniTableSub_Message(
    upb_MiniTableSub sub);

// End of C++ compatibility block
#ifdef __cplusplus
}
#endif

// Undefine platform-specific macros
#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_SUB_H_
```

The comments explain:
1. The purpose of each section and include
2. The functionality of each API function
3. Parameters and return values for each function
4. The C++ compatibility block
5. The header guard pattern
6. Platform-specific macro handling

The comments are designed to help future developers understand:
- What this header file provides
- How to use the API functions
- The underlying structure (union type)
- The cross-platform and cross-language considerations