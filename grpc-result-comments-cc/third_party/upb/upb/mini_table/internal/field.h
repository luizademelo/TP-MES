Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_FIELD_H_
#define UPB_MINI_TABLE_INTERNAL_FIELD_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/internal/size_log2.h"

#include "upb/port/def.inc"

// Structure representing a field in a mini table (compact protocol buffer representation)
struct upb_MiniTableField {
  uint32_t UPB_ONLYBITS(number);      // Field number in the protocol buffer
  uint16_t UPB_ONLYBITS(offset);      // Offset of the field within the message
  int16_t presence;                   // Presence indicator (positive for hasbit, negative for oneof, 0 for no presence)
  
  uint16_t UPB_PRIVATE(submsg_index); // Index of submessage type if this is a message/group field
  
  uint8_t UPB_PRIVATE(descriptortype); // Field type descriptor
  
  uint8_t UPB_ONLYBITS(mode);         // Bitfield containing mode and representation info
};

// Constant indicating no submessage
#define kUpb_NoSub ((uint16_t)-1)

// Enum defining different field modes (how the field is stored)
typedef enum {
  kUpb_FieldMode_Map = 0,    // Field is a map
  kUpb_FieldMode_Array = 1,  // Field is a repeated field (array)
  kUpb_FieldMode_Scalar = 2, // Field is a single value
} upb_FieldMode;

// Mask to extract field mode bits from the mode byte
#define kUpb_FieldMode_Mask 3

// Enum defining various label flags for fields
typedef enum {
  kUpb_LabelFlags_IsPacked = 4,      // Field is packed (for repeated numeric fields)
  kUpb_LabelFlags_IsExtension = 8,   // Field is an extension
  kUpb_LabelFlags_IsAlternate = 16,  // Field has an alternate type representation
} upb_LabelFlags;

// Enum defining different field representation types (how the field data is stored)
// Note: we sort by this number when calculating layout order.
typedef enum {
  kUpb_FieldRep_1Byte = 0,       // 1-byte representation
  kUpb_FieldRep_4Byte = 1,       // 4-byte representation
  kUpb_FieldRep_StringView = 2,  // String view representation
  kUpb_FieldRep_8Byte = 3,       // 8-byte representation

  // Platform-dependent pointer size representation
  kUpb_FieldRep_NativePointer = UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte),
  kUpb_FieldRep_Max = kUpb_FieldRep_8Byte, // Maximum representation value
} upb_FieldRep;

// Shift amount to get to representation bits in mode byte
#define kUpb_FieldRep_Shift 6

#ifdef __cplusplus
extern "C" {
#endif

// Returns the field mode (map, array, or scalar)
UPB_INLINE upb_FieldMode
UPB_PRIVATE(_upb_MiniTableField_Mode)(const struct upb_MiniTableField* f) {
  return (upb_FieldMode)(f->UPB_ONLYBITS(mode) & kUpb_FieldMode_Mask);
}

// Returns the field representation type
UPB_INLINE upb_FieldRep
UPB_PRIVATE(_upb_MiniTableField_GetRep)(const struct upb_MiniTableField* f) {
  return (upb_FieldRep)(f->UPB_ONLYBITS(mode) >> kUpb_FieldRep_Shift);
}

// Returns true if the field is an array (repeated field)
UPB_API_INLINE bool upb_MiniTableField_IsArray(
    const struct upb_MiniTableField* f) {
  return UPB_PRIVATE(_upb_MiniTableField_Mode)(f) == kUpb_FieldMode_Array;
}

// Returns true if the field is a map
UPB_API_INLINE bool upb_MiniTableField_IsMap(
    const struct upb_MiniTableField* f) {
  return UPB_PRIVATE(_upb_MiniTableField_Mode)(f) == kUpb_FieldMode_Map;
}

// Returns true if the field is a scalar (single value)
UPB_API_INLINE bool upb_MiniTableField_IsScalar(
    const struct upb_MiniTableField* f) {
  return UPB_PRIVATE(_upb_MiniTableField_Mode)(f) == kUpb_FieldMode_Scalar;
}

// Returns true if the field has an alternate type representation
UPB_INLINE bool UPB_PRIVATE(_upb_MiniTableField_IsAlternate)(
    const struct upb_MiniTableField* f) {
  return (f->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsAlternate) != 0;
}

// Returns true if the field is an extension
UPB_API_INLINE bool upb_MiniTableField_IsExtension(
    const struct upb_MiniTableField* f) {
  return (f->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsExtension) != 0;
}

// Returns true if the field is packed (for repeated numeric fields)
UPB_API_INLINE bool upb_MiniTableField_IsPacked(
    const struct upb_MiniTableField* f) {
  return (f->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsPacked) != 0;
}

// Returns the field type, handling alternate representations
UPB_API_INLINE upb_FieldType
upb_MiniTableField_Type(const struct upb_MiniTableField* f) {
  const upb_FieldType type = (upb_FieldType)f->UPB_PRIVATE(descriptortype);
  if (UPB_PRIVATE(_upb_MiniTableField_IsAlternate)(f)) {
    if (type == kUpb_FieldType_Int32) return kUpb_FieldType_Enum;
    if (type == kUpb_FieldType_Bytes) return kUpb_FieldType_String;
    UPB_ASSERT(false);
  }
  return type;
}

// Returns the C type corresponding to the field type
UPB_API_INLINE
upb_CType upb_MiniTableField_CType(const struct upb_MiniTableField* f) {
  return upb_FieldType_CType(upb_MiniTableField_Type(f));
}

// Returns true if the field uses a hasbit for presence tracking
UPB_INLINE bool UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(
    const struct upb_MiniTableField* f) {
  return f->presence > 0;
}

// Returns the bitmask for the hasbit in the hasbit array
UPB_INLINE char UPB_PRIVATE(_upb_MiniTableField_HasbitMask)(
    const struct upb_MiniTableField* f) {
  UPB_ASSERT(UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f));
  const uint16_t index = f->presence;
  return 1 << (index % 8);
}

// Returns the byte offset of the hasbit in the hasbit array
UPB_INLINE uint16_t UPB_PRIVATE(_upb_MiniTableField_HasbitOffset)(
    const struct upb_MiniTableField* f) {
  UPB_ASSERT(UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f));
  const uint16_t index = f->presence;
  return index / 8;
}

// Returns true if the field is a closed enum type
UPB_API_INLINE bool upb_MiniTableField_IsClosedEnum(
    const struct upb_MiniTableField* f) {
  return f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Enum;
}

// Returns true if the field is part of a oneof
UPB_API_INLINE bool upb_MiniTableField_IsInOneof(
    const struct upb_MiniTableField* f) {
  return f->presence < 0;
}

// Returns true if the field is a submessage (message or group)
UPB_API_INLINE bool upb_MiniTableField_IsSubMessage(
    const struct upb_MiniTableField* f) {
  return f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Message ||
         f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Group;
}

// Returns true if the field has presence information
UPB_API_INLINE bool upb_MiniTableField_HasPresence(
    const struct upb_MiniTableField* f) {
  if (upb_MiniTableField_IsExtension(f)) {
    return upb_MiniTableField_IsScalar(f);
  } else {
    return f->presence != 0;
  }
}

// Returns the field number
UPB_API_INLINE uint32_t
upb_MiniTableField_Number(const struct upb_MiniTableField* f) {
  return f->UPB_ONLYBITS(number);
}

// Returns the field's offset within the message
UPB_INLINE uint16_t
UPB_PRIVATE(_upb_MiniTableField_Offset)(const struct upb_MiniTableField* f) {
  return f->UPB_ONLYBITS(offset);
}

// Returns the oneof case offset for fields in a oneof
UPB_INLINE size_t UPB_PRIVATE(_upb_MiniTableField_OneofOffset)(
    const struct upb_MiniTableField* f) {
  UPB_ASSERT(upb_MiniTableField_IsInOneof(f));
  return ~(ptrdiff_t)f->presence;
}

// Debug/assert helper to verify a field is an array
UPB_INLINE void UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(
    const struct upb_MiniTableField* f) {
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             kUpb_FieldRep_NativePointer);
  UPB_ASSUME(upb_MiniTableField_IsArray(f));
  UPB_ASSUME(f->presence == 0);
}

// Debug/assert helper to verify a field is a map
UPB_INLINE void UPB_PRIVATE(_upb_MiniTableField_CheckIsMap)(
    const struct upb_MiniTableField* f) {
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             kUpb_FieldRep_NativePointer);
  UPB_ASSUME(upb_MiniTableField_IsMap(f));
  UPB_ASSUME(f->presence == 0);
}

// Returns the log2 size of the field's element type
UPB_INLINE size_t UPB_PRIVATE(_upb_MiniTableField_ElemSizeLg2)(
    const struct upb_MiniTableField* f) {
  const upb_FieldType field_type = upb_MiniTableField_Type(f);
  return UPB_PRIVATE(_upb_FieldType_SizeLg2)(field_type);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_INTERNAL_FIELD_H_
```