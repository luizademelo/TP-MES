Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_MINI_TABLE_INTERNAL_EXTENSION_H_
#define UPB_MINI_TABLE_INTERNAL_EXTENSION_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/internal/field.h"
#include "upb/mini_table/internal/sub.h"

#include "upb/port/def.inc"

// Structure representing a mini table extension in upb (micro protobuf)
// Contains information about an extension field in protobuf
struct upb_MiniTableExtension {
  // The field information (type, number, etc)
  struct upb_MiniTableField UPB_PRIVATE(field);

  // The message type being extended
  const struct upb_MiniTable* UPB_PRIVATE(extendee);
  
  // Sub-information (either a submessage or enum)
  union upb_MiniTableSub UPB_PRIVATE(sub);
};

#ifdef __cplusplus
extern "C" {
#endif

// Returns the C-type of the extension field
UPB_API_INLINE upb_CType
upb_MiniTableExtension_CType(const struct upb_MiniTableExtension* e) {
  return upb_MiniTableField_CType(&e->UPB_PRIVATE(field));
}

// Returns the field number of the extension
UPB_API_INLINE uint32_t
upb_MiniTableExtension_Number(const struct upb_MiniTableExtension* e) {
  return e->UPB_PRIVATE(field).UPB_ONLYBITS(number);
}

// Returns the submessage type for this extension if it's a message type,
// otherwise returns NULL
UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableExtension_GetSubMessage(
    const struct upb_MiniTableExtension* e) {
  if (upb_MiniTableExtension_CType(e) != kUpb_CType_Message) {
    return NULL;
  }
  return upb_MiniTableSub_Message(e->UPB_PRIVATE(sub));
}

// Returns the enum type for this extension if it's an enum type,
// otherwise returns NULL
UPB_API_INLINE const struct upb_MiniTableEnum*
upb_MiniTableExtension_GetSubEnum(const struct upb_MiniTableExtension* e) {
  if (upb_MiniTableExtension_CType(e) != kUpb_CType_Enum) {
    return NULL;
  }
  return upb_MiniTableSub_Enum(e->UPB_PRIVATE(sub));
}

// Sets the submessage type for this extension.
// Returns true if successful (field is a message type), false otherwise
UPB_API_INLINE bool upb_MiniTableExtension_SetSubMessage(
    struct upb_MiniTableExtension* e, const struct upb_MiniTable* m) {
  if (e->UPB_PRIVATE(field).UPB_PRIVATE(descriptortype) !=
      kUpb_FieldType_Message) {
    return false;
  }
  e->UPB_PRIVATE(sub).UPB_PRIVATE(submsg) = m;
  return true;
}

// Sets the enum type for this extension.
// Returns true if successful (field is an enum type), false otherwise
UPB_API_INLINE bool upb_MiniTableExtension_SetSubEnum(
    struct upb_MiniTableExtension* e, const struct upb_MiniTableEnum* en) {
  if (e->UPB_PRIVATE(field).UPB_PRIVATE(descriptortype) !=
      kUpb_FieldType_Enum) {
    return false;
  }
  e->UPB_PRIVATE(sub).UPB_PRIVATE(subenum) = en;
  return true;
}

// Internal function to get the field representation
UPB_INLINE upb_FieldRep UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(
    const struct upb_MiniTableExtension* e) {
  return UPB_PRIVATE(_upb_MiniTableField_GetRep)(&e->UPB_PRIVATE(field));
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_INTERNAL_EXTENSION_H_
```

Key aspects covered in the comments:
1. Header guard explanation
2. Structure of the upb_MiniTableExtension and its components
3. Purpose of each inline function
4. Return value explanations
5. Conditions under which functions return NULL or false
6. Internal function documentation

The comments maintain a balance between explaining the what and the why while avoiding over-commenting obvious things. They focus on the contract and behavior of each component rather than implementation details that are clear from the code itself.