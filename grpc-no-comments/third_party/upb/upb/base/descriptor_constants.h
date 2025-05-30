
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_BASE_DESCRIPTOR_CONSTANTS_H_
#define UPB_BASE_DESCRIPTOR_CONSTANTS_H_

#include "upb/port/def.inc"

typedef enum {
  kUpb_CType_Bool = 1,
  kUpb_CType_Float = 2,
  kUpb_CType_Int32 = 3,
  kUpb_CType_UInt32 = 4,
  kUpb_CType_Enum = 5,
  kUpb_CType_Message = 6,
  kUpb_CType_Double = 7,
  kUpb_CType_Int64 = 8,
  kUpb_CType_UInt64 = 9,
  kUpb_CType_String = 10,
  kUpb_CType_Bytes = 11
} upb_CType;

typedef enum {
  kUpb_Label_Optional = 1,
  kUpb_Label_Required = 2,
  kUpb_Label_Repeated = 3
} upb_Label;

typedef enum {
  kUpb_FieldType_Double = 1,
  kUpb_FieldType_Float = 2,
  kUpb_FieldType_Int64 = 3,
  kUpb_FieldType_UInt64 = 4,
  kUpb_FieldType_Int32 = 5,
  kUpb_FieldType_Fixed64 = 6,
  kUpb_FieldType_Fixed32 = 7,
  kUpb_FieldType_Bool = 8,
  kUpb_FieldType_String = 9,
  kUpb_FieldType_Group = 10,
  kUpb_FieldType_Message = 11,
  kUpb_FieldType_Bytes = 12,
  kUpb_FieldType_UInt32 = 13,
  kUpb_FieldType_Enum = 14,
  kUpb_FieldType_SFixed32 = 15,
  kUpb_FieldType_SFixed64 = 16,
  kUpb_FieldType_SInt32 = 17,
  kUpb_FieldType_SInt64 = 18,
} upb_FieldType;

#define kUpb_FieldType_SizeOf 19

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE upb_CType upb_FieldType_CType(upb_FieldType field_type) {
  static const upb_CType c_type[] = {
      kUpb_CType_Double,
      kUpb_CType_Float,
      kUpb_CType_Int64,
      kUpb_CType_UInt64,
      kUpb_CType_Int32,
      kUpb_CType_UInt64,
      kUpb_CType_UInt32,
      kUpb_CType_Bool,
      kUpb_CType_String,
      kUpb_CType_Message,
      kUpb_CType_Message,
      kUpb_CType_Bytes,
      kUpb_CType_UInt32,
      kUpb_CType_Enum,
      kUpb_CType_Int32,
      kUpb_CType_Int64,
      kUpb_CType_Int32,
      kUpb_CType_Int64,
  };

  return c_type[field_type - 1];
}

UPB_INLINE bool upb_FieldType_IsPackable(upb_FieldType field_type) {

  const unsigned kUnpackableTypes =
      (1 << kUpb_FieldType_String) |
      (1 << kUpb_FieldType_Bytes) |
      (1 << kUpb_FieldType_Message) |
      (1 << kUpb_FieldType_Group);

  return (1 << field_type) & ~kUnpackableTypes;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
