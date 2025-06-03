Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_REFLECTION_ENUM_RESERVED_RANGE_INTERNAL_H_
#define UPB_REFLECTION_ENUM_RESERVED_RANGE_INTERNAL_H_

// Include the public interface for enum reserved ranges
#include "upb/reflection/enum_reserved_range.h"

// Include platform-specific definitions
#include "upb/port/def.inc"

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets a pointer to the i-th reserved range in the array
 * @param r Pointer to the beginning of the enum reserved ranges array
 * @param i Index of the desired reserved range
 * @return Pointer to the i-th upb_EnumReservedRange structure
 */
upb_EnumReservedRange* _upb_EnumReservedRange_At(const upb_EnumReservedRange* r,
                                                 int i);

/**
 * @brief Creates new enum reserved ranges from protocol descriptors
 * @param ctx The definition builder context for memory allocation
 * @param n Number of reserved ranges to create
 * @param protos Array of protocol buffer enum reserved range descriptors
 * @param e The enum definition these ranges belong to
 * @return Pointer to the newly created array of upb_EnumReservedRange structures
 */
upb_EnumReservedRange* _upb_EnumReservedRanges_New(
    upb_DefBuilder* ctx, int n,
    const UPB_DESC(EnumDescriptorProto_EnumReservedRange*) const* protos,
    const upb_EnumDef* e);

// End C++ compatibility
#ifdef __cplusplus
}
#endif

// Undefine platform-specific macros
#include "upb/port/undef.inc"

// End of header guard
#endif  // UPB_REFLECTION_ENUM_RESERVED_RANGE_INTERNAL_H_
```

The comments provide:
1. Explanation of the header guard purpose
2. Documentation for each included file
3. C++ compatibility block explanation
4. Detailed function documentation including parameters and return values
5. Clear indication of the header guard closure

The comments follow standard C++ documentation practices while being concise and informative for maintainers.