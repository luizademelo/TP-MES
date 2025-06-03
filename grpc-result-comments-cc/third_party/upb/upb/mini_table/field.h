Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_MINI_TABLE_FIELD_H_
#define UPB_MINI_TABLE_FIELD_H_

#include <stdint.h>  // For uint32_t type

// Include necessary headers for descriptor constants and internal field representation
#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/internal/field.h"

// Include platform-specific definitions
#include "upb/port/def.inc"

// Forward declaration of upb_MiniTableField structure
typedef struct upb_MiniTableField upb_MiniTableField;

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

// API functions for querying field properties:

// Returns the C-type of the field (as defined in upb's type system)
UPB_API_INLINE upb_CType upb_MiniTableField_CType(const upb_MiniTableField* f);

// Returns true if the field has presence information (optional fields)
UPB_API_INLINE bool upb_MiniTableField_HasPresence(const upb_MiniTableField* f);

// Returns true if the field is a repeated field (array)
UPB_API_INLINE bool upb_MiniTableField_IsArray(const upb_MiniTableField* f);

// Returns true if the field is a closed enum type
UPB_API_INLINE bool upb_MiniTableField_IsClosedEnum(
    const upb_MiniTableField* f);

// Returns true if the field is an extension field
UPB_API_INLINE bool upb_MiniTableField_IsExtension(const upb_MiniTableField* f);

// Returns true if the field is part of a oneof group
UPB_API_INLINE bool upb_MiniTableField_IsInOneof(const upb_MiniTableField* f);

// Returns true if the field is a map type
UPB_API_INLINE bool upb_MiniTableField_IsMap(const upb_MiniTableField* f);

// Returns true if the field is packed (for repeated primitive fields)
UPB_API_INLINE bool upb_MiniTableField_IsPacked(const upb_MiniTableField* f);

// Returns true if the field is a scalar (non-message, non-array) type
UPB_API_INLINE bool upb_MiniTableField_IsScalar(const upb_MiniTableField* f);

// Returns true if the field is a sub-message type
UPB_API_INLINE bool upb_MiniTableField_IsSubMessage(
    const upb_MiniTableField* f);

// Returns the field number as defined in the .proto file
UPB_API_INLINE uint32_t upb_MiniTableField_Number(const upb_MiniTableField* f);

// Returns the field type (as defined in upb's type system)
UPB_API_INLINE upb_FieldType
upb_MiniTableField_Type(const upb_MiniTableField* f);

#ifdef __cplusplus
}  // extern "C"
#endif

// Undefine platform-specific definitions
#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_FIELD_H_
```

The comments explain:
1. The purpose of each include directive
2. The overall purpose of the header file (providing field property query functions)
3. The behavior and return value of each API function
4. The C++ compatibility section
5. The header guard and platform-specific definition handling

The comments are concise but provide enough information for a developer to understand what each part does without needing to dive into the implementation details.