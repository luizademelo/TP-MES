Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_REFLECTION_ENUM_RESERVED_RANGE_H_
#define UPB_REFLECTION_ENUM_RESERVED_RANGE_H_

// Include necessary headers for the functionality
#include "upb/reflection/common.h"  // Common definitions for upb reflection
#include "upb/port/def.inc"        // Platform-specific definitions

// C++ compatibility: if compiled as C++, use C linkage
#ifdef __cplusplus
extern "C" {
#endif

// Function declarations for working with enum reserved ranges:

// Returns the start value of an enum reserved range
// @param r Pointer to the EnumReservedRange object
// @return The starting value of the reserved range as a 32-bit integer
int32_t upb_EnumReservedRange_Start(const upb_EnumReservedRange* r);

// Returns the end value of an enum reserved range
// @param r Pointer to the EnumReservedRange object
// @return The ending value of the reserved range as a 32-bit integer
int32_t upb_EnumReservedRange_End(const upb_EnumReservedRange* r);

// End of C linkage section for C++ compatibility
#ifdef __cplusplus
}
#endif

// Undefine any platform-specific macros that were defined earlier
#include "upb/port/undef.inc"

// End of header guard
#endif  // UPB_REFLECTION_ENUM_RESERVED_RANGE_H_
```

The comments explain:
1. The purpose of header guards
2. The included files and their roles
3. The C++ compatibility section
4. Each function's purpose, parameters, and return values
5. The purpose of the undef include
7. The closing of the header guard

The comments are concise but provide all the necessary information for a developer to understand and use this header file correctly.