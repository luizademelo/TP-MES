Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_REFLECTION_MESSAGE_RESERVED_RANGE_H_
#define UPB_REFLECTION_MESSAGE_RESERVED_RANGE_H_

// Include common definitions for upb reflection
#include "upb/reflection/common.h"

// Include platform-specific definitions
#include "upb/port/def.inc"

// C++ compatibility: if compiled as C++, use C linkage
#ifdef __cplusplus
extern "C" {
#endif

// Function to get the start index of a reserved range in a protobuf message
// @param r Pointer to the MessageReservedRange structure
// @return The starting index of the reserved range
int32_t upb_MessageReservedRange_Start(const upb_MessageReservedRange* r);

// Function to get the end index of a reserved range in a protobuf message
// @param r Pointer to the MessageReservedRange structure
// @return The ending index of the reserved range
int32_t upb_MessageReservedRange_End(const upb_MessageReservedRange* r);

// End C++ linkage scope if compiled as C++
#ifdef __cplusplus
}
#endif

// Undefine platform-specific macros to avoid pollution
#include "upb/port/undef.inc"

// End of header guard
#endif  // UPB_REFLECTION_MESSAGE_RESERVED_RANGE_H_
```

The comments explain:
1. The purpose of header guards
2. The included files and their roles
3. The C++ compatibility mechanism
4. Each function's purpose, parameters, and return values
5. The cleanup of platform-specific definitions
6. The closing of the header guard

The comments are concise yet informative, following common C++ documentation practices while being helpful for maintenance.