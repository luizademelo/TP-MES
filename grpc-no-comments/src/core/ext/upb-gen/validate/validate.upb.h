
#ifndef VALIDATE_VALIDATE_PROTO_UPB_H__UPB_H_
#define VALIDATE_VALIDATE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "validate/validate.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct validate_FieldRules { upb_Message UPB_PRIVATE(base); } validate_FieldRules;
typedef struct validate_FloatRules { upb_Message UPB_PRIVATE(base); } validate_FloatRules;
typedef struct validate_DoubleRules { upb_Message UPB_PRIVATE(base); } validate_DoubleRules;
typedef struct validate_Int32Rules { upb_Message UPB_PRIVATE(base); } validate_Int32Rules;
typedef struct validate_Int64Rules { upb_Message UPB_PRIVATE(base); } validate_Int64Rules;
typedef struct validate_UInt32Rules { upb_Message UPB_PRIVATE(base); } validate_UInt32Rules;
typedef struct validate_UInt64Rules { upb_Message UPB_PRIVATE(base); } validate_UInt64Rules;
typedef struct validate_SInt32Rules { upb_Message UPB_PRIVATE(base); } validate_SInt32Rules;
typedef struct validate_SInt64Rules { upb_Message UPB_PRIVATE(base); } validate_SInt64Rules;
typedef struct validate_Fixed32Rules { upb_Message UPB_PRIVATE(base); } validate_Fixed32Rules;
typedef struct validate_Fixed64Rules { upb_Message UPB_PRIVATE(base); } validate_Fixed64Rules;
typedef struct validate_SFixed32Rules { upb_Message UPB_PRIVATE(base); } validate_SFixed32Rules;
typedef struct validate_SFixed64Rules { upb_Message UPB_PRIVATE(base); } validate_SFixed64Rules;
typedef struct validate_BoolRules { upb_Message UPB_PRIVATE(base); } validate_BoolRules;
typedef struct validate_StringRules { upb_Message UPB_PRIVATE(base); } validate_StringRules;
typedef struct validate_BytesRules { upb_Message UPB_PRIVATE(base); } validate_BytesRules;
typedef struct validate_EnumRules { upb_Message UPB_PRIVATE(base); } validate_EnumRules;
typedef struct validate_MessageRules { upb_Message UPB_PRIVATE(base); } validate_MessageRules;
typedef struct validate_RepeatedRules { upb_Message UPB_PRIVATE(base); } validate_RepeatedRules;
typedef struct validate_MapRules { upb_Message UPB_PRIVATE(base); } validate_MapRules;
typedef struct validate_AnyRules { upb_Message UPB_PRIVATE(base); } validate_AnyRules;
typedef struct validate_DurationRules { upb_Message UPB_PRIVATE(base); } validate_DurationRules;
typedef struct validate_TimestampRules { upb_Message UPB_PRIVATE(base); } validate_TimestampRules;
struct google_protobuf_Duration;
struct google_protobuf_FieldOptions;
struct google_protobuf_MessageOptions;
struct google_protobuf_OneofOptions;
struct google_protobuf_Timestamp;

typedef enum {
  validate_UNKNOWN = 0,
  validate_HTTP_HEADER_NAME = 1,
  validate_HTTP_HEADER_VALUE = 2
} validate_KnownRegex;

UPB_INLINE validate_FieldRules* validate_FieldRules_new(upb_Arena* arena) {
  return (validate_FieldRules*)_upb_Message_New(&validate__FieldRules_msg_init, arena);
}
UPB_INLINE validate_FieldRules* validate_FieldRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_FieldRules* ret = validate_FieldRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__FieldRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_FieldRules* validate_FieldRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_FieldRules* ret = validate_FieldRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__FieldRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_FieldRules_serialize(const validate_FieldRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__FieldRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_FieldRules_serialize_ex(const validate_FieldRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__FieldRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  validate_FieldRules_type_float = 1,
  validate_FieldRules_type_double = 2,
  validate_FieldRules_type_int32 = 3,
  validate_FieldRules_type_int64 = 4,
  validate_FieldRules_type_uint32 = 5,
  validate_FieldRules_type_uint64 = 6,
  validate_FieldRules_type_sint32 = 7,
  validate_FieldRules_type_sint64 = 8,
  validate_FieldRules_type_fixed32 = 9,
  validate_FieldRules_type_fixed64 = 10,
  validate_FieldRules_type_sfixed32 = 11,
  validate_FieldRules_type_sfixed64 = 12,
  validate_FieldRules_type_bool = 13,
  validate_FieldRules_type_string = 14,
  validate_FieldRules_type_bytes = 15,
  validate_FieldRules_type_enum = 16,
  validate_FieldRules_type_repeated = 18,
  validate_FieldRules_type_map = 19,
  validate_FieldRules_type_any = 20,
  validate_FieldRules_type_duration = 21,
  validate_FieldRules_type_timestamp = 22,
  validate_FieldRules_type_NOT_SET = 0
} validate_FieldRules_type_oneofcases;
UPB_INLINE validate_FieldRules_type_oneofcases validate_FieldRules_type_case(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (validate_FieldRules_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_type(validate_FieldRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &validate__FieldRules_msg_init, &field);
}
UPB_INLINE void validate_FieldRules_clear_float(validate_FieldRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_FloatRules* validate_FieldRules_float(const validate_FieldRules* msg) {
  const validate_FloatRules* default_val = NULL;
  const validate_FloatRules* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FloatRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_float(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_double(validate_FieldRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_DoubleRules* validate_FieldRules_double(const validate_FieldRules* msg) {
  const validate_DoubleRules* default_val = NULL;
  const validate_DoubleRules* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__DoubleRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_double(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_int32(validate_FieldRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_Int32Rules* validate_FieldRules_int32(const validate_FieldRules* msg) {
  const validate_Int32Rules* default_val = NULL;
  const validate_Int32Rules* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Int32Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_int32(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_int64(validate_FieldRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_Int64Rules* validate_FieldRules_int64(const validate_FieldRules* msg) {
  const validate_Int64Rules* default_val = NULL;
  const validate_Int64Rules* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Int64Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_int64(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_uint32(validate_FieldRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_UInt32Rules* validate_FieldRules_uint32(const validate_FieldRules* msg) {
  const validate_UInt32Rules* default_val = NULL;
  const validate_UInt32Rules* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__UInt32Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_uint32(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_uint64(validate_FieldRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_UInt64Rules* validate_FieldRules_uint64(const validate_FieldRules* msg) {
  const validate_UInt64Rules* default_val = NULL;
  const validate_UInt64Rules* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__UInt64Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_uint64(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_sint32(validate_FieldRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_SInt32Rules* validate_FieldRules_sint32(const validate_FieldRules* msg) {
  const validate_SInt32Rules* default_val = NULL;
  const validate_SInt32Rules* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SInt32Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_sint32(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_sint64(validate_FieldRules* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_SInt64Rules* validate_FieldRules_sint64(const validate_FieldRules* msg) {
  const validate_SInt64Rules* default_val = NULL;
  const validate_SInt64Rules* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SInt64Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_sint64(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_fixed32(validate_FieldRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_Fixed32Rules* validate_FieldRules_fixed32(const validate_FieldRules* msg) {
  const validate_Fixed32Rules* default_val = NULL;
  const validate_Fixed32Rules* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Fixed32Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_fixed32(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_fixed64(validate_FieldRules* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_Fixed64Rules* validate_FieldRules_fixed64(const validate_FieldRules* msg) {
  const validate_Fixed64Rules* default_val = NULL;
  const validate_Fixed64Rules* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Fixed64Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_fixed64(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_sfixed32(validate_FieldRules* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_SFixed32Rules* validate_FieldRules_sfixed32(const validate_FieldRules* msg) {
  const validate_SFixed32Rules* default_val = NULL;
  const validate_SFixed32Rules* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SFixed32Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_sfixed32(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_sfixed64(validate_FieldRules* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_SFixed64Rules* validate_FieldRules_sfixed64(const validate_FieldRules* msg) {
  const validate_SFixed64Rules* default_val = NULL;
  const validate_SFixed64Rules* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SFixed64Rules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_sfixed64(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_bool(validate_FieldRules* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_BoolRules* validate_FieldRules_bool(const validate_FieldRules* msg) {
  const validate_BoolRules* default_val = NULL;
  const validate_BoolRules* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__BoolRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_bool(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_string(validate_FieldRules* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_StringRules* validate_FieldRules_string(const validate_FieldRules* msg) {
  const validate_StringRules* default_val = NULL;
  const validate_StringRules* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__StringRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_string(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_bytes(validate_FieldRules* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_BytesRules* validate_FieldRules_bytes(const validate_FieldRules* msg) {
  const validate_BytesRules* default_val = NULL;
  const validate_BytesRules* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__BytesRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_bytes(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_enum(validate_FieldRules* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_EnumRules* validate_FieldRules_enum(const validate_FieldRules* msg) {
  const validate_EnumRules* default_val = NULL;
  const validate_EnumRules* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__EnumRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_enum(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_message(validate_FieldRules* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(12, 16), 64, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_MessageRules* validate_FieldRules_message(const validate_FieldRules* msg) {
  const validate_MessageRules* default_val = NULL;
  const validate_MessageRules* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(12, 16), 64, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__MessageRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_message(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(12, 16), 64, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_repeated(validate_FieldRules* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_RepeatedRules* validate_FieldRules_repeated(const validate_FieldRules* msg) {
  const validate_RepeatedRules* default_val = NULL;
  const validate_RepeatedRules* ret;
  const upb_MiniTableField field = {18, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__RepeatedRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_repeated(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_map(validate_FieldRules* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_MapRules* validate_FieldRules_map(const validate_FieldRules* msg) {
  const validate_MapRules* default_val = NULL;
  const validate_MapRules* ret;
  const upb_MiniTableField field = {19, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__MapRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_map(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_any(validate_FieldRules* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_AnyRules* validate_FieldRules_any(const validate_FieldRules* msg) {
  const validate_AnyRules* default_val = NULL;
  const validate_AnyRules* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__AnyRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_any(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_duration(validate_FieldRules* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_DurationRules* validate_FieldRules_duration(const validate_FieldRules* msg) {
  const validate_DurationRules* default_val = NULL;
  const validate_DurationRules* ret;
  const upb_MiniTableField field = {21, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__DurationRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_duration(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FieldRules_clear_timestamp(validate_FieldRules* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_TimestampRules* validate_FieldRules_timestamp(const validate_FieldRules* msg) {
  const validate_TimestampRules* default_val = NULL;
  const validate_TimestampRules* ret;
  const upb_MiniTableField field = {22, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__TimestampRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FieldRules_has_timestamp(const validate_FieldRules* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_FieldRules_set_float(validate_FieldRules *msg, validate_FloatRules* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FloatRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_FloatRules* validate_FieldRules_mutable_float(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_FloatRules* sub = (struct validate_FloatRules*)validate_FieldRules_float(msg);
  if (sub == NULL) {
    sub = (struct validate_FloatRules*)_upb_Message_New(&validate__FloatRules_msg_init, arena);
    if (sub) validate_FieldRules_set_float(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_double(validate_FieldRules *msg, validate_DoubleRules* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__DoubleRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_DoubleRules* validate_FieldRules_mutable_double(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_DoubleRules* sub = (struct validate_DoubleRules*)validate_FieldRules_double(msg);
  if (sub == NULL) {
    sub = (struct validate_DoubleRules*)_upb_Message_New(&validate__DoubleRules_msg_init, arena);
    if (sub) validate_FieldRules_set_double(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_int32(validate_FieldRules *msg, validate_Int32Rules* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Int32Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_Int32Rules* validate_FieldRules_mutable_int32(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_Int32Rules* sub = (struct validate_Int32Rules*)validate_FieldRules_int32(msg);
  if (sub == NULL) {
    sub = (struct validate_Int32Rules*)_upb_Message_New(&validate__Int32Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_int32(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_int64(validate_FieldRules *msg, validate_Int64Rules* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Int64Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_Int64Rules* validate_FieldRules_mutable_int64(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_Int64Rules* sub = (struct validate_Int64Rules*)validate_FieldRules_int64(msg);
  if (sub == NULL) {
    sub = (struct validate_Int64Rules*)_upb_Message_New(&validate__Int64Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_int64(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_uint32(validate_FieldRules *msg, validate_UInt32Rules* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__UInt32Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_UInt32Rules* validate_FieldRules_mutable_uint32(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_UInt32Rules* sub = (struct validate_UInt32Rules*)validate_FieldRules_uint32(msg);
  if (sub == NULL) {
    sub = (struct validate_UInt32Rules*)_upb_Message_New(&validate__UInt32Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_uint32(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_uint64(validate_FieldRules *msg, validate_UInt64Rules* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__UInt64Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_UInt64Rules* validate_FieldRules_mutable_uint64(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_UInt64Rules* sub = (struct validate_UInt64Rules*)validate_FieldRules_uint64(msg);
  if (sub == NULL) {
    sub = (struct validate_UInt64Rules*)_upb_Message_New(&validate__UInt64Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_uint64(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_sint32(validate_FieldRules *msg, validate_SInt32Rules* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SInt32Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_SInt32Rules* validate_FieldRules_mutable_sint32(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_SInt32Rules* sub = (struct validate_SInt32Rules*)validate_FieldRules_sint32(msg);
  if (sub == NULL) {
    sub = (struct validate_SInt32Rules*)_upb_Message_New(&validate__SInt32Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_sint32(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_sint64(validate_FieldRules *msg, validate_SInt64Rules* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SInt64Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_SInt64Rules* validate_FieldRules_mutable_sint64(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_SInt64Rules* sub = (struct validate_SInt64Rules*)validate_FieldRules_sint64(msg);
  if (sub == NULL) {
    sub = (struct validate_SInt64Rules*)_upb_Message_New(&validate__SInt64Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_sint64(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_fixed32(validate_FieldRules *msg, validate_Fixed32Rules* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Fixed32Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_Fixed32Rules* validate_FieldRules_mutable_fixed32(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_Fixed32Rules* sub = (struct validate_Fixed32Rules*)validate_FieldRules_fixed32(msg);
  if (sub == NULL) {
    sub = (struct validate_Fixed32Rules*)_upb_Message_New(&validate__Fixed32Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_fixed32(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_fixed64(validate_FieldRules *msg, validate_Fixed64Rules* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__Fixed64Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_Fixed64Rules* validate_FieldRules_mutable_fixed64(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_Fixed64Rules* sub = (struct validate_Fixed64Rules*)validate_FieldRules_fixed64(msg);
  if (sub == NULL) {
    sub = (struct validate_Fixed64Rules*)_upb_Message_New(&validate__Fixed64Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_fixed64(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_sfixed32(validate_FieldRules *msg, validate_SFixed32Rules* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SFixed32Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_SFixed32Rules* validate_FieldRules_mutable_sfixed32(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_SFixed32Rules* sub = (struct validate_SFixed32Rules*)validate_FieldRules_sfixed32(msg);
  if (sub == NULL) {
    sub = (struct validate_SFixed32Rules*)_upb_Message_New(&validate__SFixed32Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_sfixed32(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_sfixed64(validate_FieldRules *msg, validate_SFixed64Rules* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__SFixed64Rules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_SFixed64Rules* validate_FieldRules_mutable_sfixed64(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_SFixed64Rules* sub = (struct validate_SFixed64Rules*)validate_FieldRules_sfixed64(msg);
  if (sub == NULL) {
    sub = (struct validate_SFixed64Rules*)_upb_Message_New(&validate__SFixed64Rules_msg_init, arena);
    if (sub) validate_FieldRules_set_sfixed64(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_bool(validate_FieldRules *msg, validate_BoolRules* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__BoolRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_BoolRules* validate_FieldRules_mutable_bool(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_BoolRules* sub = (struct validate_BoolRules*)validate_FieldRules_bool(msg);
  if (sub == NULL) {
    sub = (struct validate_BoolRules*)_upb_Message_New(&validate__BoolRules_msg_init, arena);
    if (sub) validate_FieldRules_set_bool(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_string(validate_FieldRules *msg, validate_StringRules* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__StringRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_StringRules* validate_FieldRules_mutable_string(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_StringRules* sub = (struct validate_StringRules*)validate_FieldRules_string(msg);
  if (sub == NULL) {
    sub = (struct validate_StringRules*)_upb_Message_New(&validate__StringRules_msg_init, arena);
    if (sub) validate_FieldRules_set_string(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_bytes(validate_FieldRules *msg, validate_BytesRules* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__BytesRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_BytesRules* validate_FieldRules_mutable_bytes(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_BytesRules* sub = (struct validate_BytesRules*)validate_FieldRules_bytes(msg);
  if (sub == NULL) {
    sub = (struct validate_BytesRules*)_upb_Message_New(&validate__BytesRules_msg_init, arena);
    if (sub) validate_FieldRules_set_bytes(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_enum(validate_FieldRules *msg, validate_EnumRules* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__EnumRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_EnumRules* validate_FieldRules_mutable_enum(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_EnumRules* sub = (struct validate_EnumRules*)validate_FieldRules_enum(msg);
  if (sub == NULL) {
    sub = (struct validate_EnumRules*)_upb_Message_New(&validate__EnumRules_msg_init, arena);
    if (sub) validate_FieldRules_set_enum(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_message(validate_FieldRules *msg, validate_MessageRules* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(12, 16), 64, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__MessageRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_MessageRules* validate_FieldRules_mutable_message(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_MessageRules* sub = (struct validate_MessageRules*)validate_FieldRules_message(msg);
  if (sub == NULL) {
    sub = (struct validate_MessageRules*)_upb_Message_New(&validate__MessageRules_msg_init, arena);
    if (sub) validate_FieldRules_set_message(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_repeated(validate_FieldRules *msg, validate_RepeatedRules* value) {
  const upb_MiniTableField field = {18, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__RepeatedRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_RepeatedRules* validate_FieldRules_mutable_repeated(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_RepeatedRules* sub = (struct validate_RepeatedRules*)validate_FieldRules_repeated(msg);
  if (sub == NULL) {
    sub = (struct validate_RepeatedRules*)_upb_Message_New(&validate__RepeatedRules_msg_init, arena);
    if (sub) validate_FieldRules_set_repeated(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_map(validate_FieldRules *msg, validate_MapRules* value) {
  const upb_MiniTableField field = {19, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__MapRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_MapRules* validate_FieldRules_mutable_map(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_MapRules* sub = (struct validate_MapRules*)validate_FieldRules_map(msg);
  if (sub == NULL) {
    sub = (struct validate_MapRules*)_upb_Message_New(&validate__MapRules_msg_init, arena);
    if (sub) validate_FieldRules_set_map(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_any(validate_FieldRules *msg, validate_AnyRules* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__AnyRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_AnyRules* validate_FieldRules_mutable_any(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_AnyRules* sub = (struct validate_AnyRules*)validate_FieldRules_any(msg);
  if (sub == NULL) {
    sub = (struct validate_AnyRules*)_upb_Message_New(&validate__AnyRules_msg_init, arena);
    if (sub) validate_FieldRules_set_any(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_duration(validate_FieldRules *msg, validate_DurationRules* value) {
  const upb_MiniTableField field = {21, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__DurationRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_DurationRules* validate_FieldRules_mutable_duration(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_DurationRules* sub = (struct validate_DurationRules*)validate_FieldRules_duration(msg);
  if (sub == NULL) {
    sub = (struct validate_DurationRules*)_upb_Message_New(&validate__DurationRules_msg_init, arena);
    if (sub) validate_FieldRules_set_duration(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_FieldRules_set_timestamp(validate_FieldRules *msg, validate_TimestampRules* value) {
  const upb_MiniTableField field = {22, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__TimestampRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_TimestampRules* validate_FieldRules_mutable_timestamp(validate_FieldRules* msg, upb_Arena* arena) {
  struct validate_TimestampRules* sub = (struct validate_TimestampRules*)validate_FieldRules_timestamp(msg);
  if (sub == NULL) {
    sub = (struct validate_TimestampRules*)_upb_Message_New(&validate__TimestampRules_msg_init, arena);
    if (sub) validate_FieldRules_set_timestamp(msg, sub);
  }
  return sub;
}

UPB_INLINE validate_FloatRules* validate_FloatRules_new(upb_Arena* arena) {
  return (validate_FloatRules*)_upb_Message_New(&validate__FloatRules_msg_init, arena);
}
UPB_INLINE validate_FloatRules* validate_FloatRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_FloatRules* ret = validate_FloatRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__FloatRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_FloatRules* validate_FloatRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_FloatRules* ret = validate_FloatRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__FloatRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_FloatRules_serialize(const validate_FloatRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__FloatRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_FloatRules_serialize_ex(const validate_FloatRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__FloatRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_FloatRules_clear_const(validate_FloatRules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float validate_FloatRules_const(const validate_FloatRules* msg) {
  float default_val = 0;
  float ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FloatRules_has_const(const validate_FloatRules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FloatRules_clear_lt(validate_FloatRules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float validate_FloatRules_lt(const validate_FloatRules* msg) {
  float default_val = 0;
  float ret;
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FloatRules_has_lt(const validate_FloatRules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FloatRules_clear_lte(validate_FloatRules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float validate_FloatRules_lte(const validate_FloatRules* msg) {
  float default_val = 0;
  float ret;
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FloatRules_has_lte(const validate_FloatRules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FloatRules_clear_gt(validate_FloatRules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float validate_FloatRules_gt(const validate_FloatRules* msg) {
  float default_val = 0;
  float ret;
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FloatRules_has_gt(const validate_FloatRules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FloatRules_clear_gte(validate_FloatRules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float validate_FloatRules_gte(const validate_FloatRules* msg) {
  float default_val = 0;
  float ret;
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FloatRules_has_gte(const validate_FloatRules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_FloatRules_clear_in(validate_FloatRules* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float const* validate_FloatRules_in(const validate_FloatRules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (float const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_FloatRules_in_upb_array(const validate_FloatRules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_FloatRules_in_mutable_upb_array(validate_FloatRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_FloatRules_clear_not_in(validate_FloatRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float const* validate_FloatRules_not_in(const validate_FloatRules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (float const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_FloatRules_not_in_upb_array(const validate_FloatRules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_FloatRules_not_in_mutable_upb_array(validate_FloatRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_FloatRules_clear_ignore_empty(validate_FloatRules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_FloatRules_ignore_empty(const validate_FloatRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_FloatRules_has_ignore_empty(const validate_FloatRules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_FloatRules_set_const(validate_FloatRules *msg, float value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_FloatRules_set_lt(validate_FloatRules *msg, float value) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_FloatRules_set_lte(validate_FloatRules *msg, float value) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_FloatRules_set_gt(validate_FloatRules *msg, float value) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_FloatRules_set_gte(validate_FloatRules *msg, float value) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE float* validate_FloatRules_mutable_in(validate_FloatRules* msg, size_t* size) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (float*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE float* validate_FloatRules_resize_in(validate_FloatRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (float*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_FloatRules_add_in(validate_FloatRules* msg, float val, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE float* validate_FloatRules_mutable_not_in(validate_FloatRules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (float*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE float* validate_FloatRules_resize_not_in(validate_FloatRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (float*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_FloatRules_add_not_in(validate_FloatRules* msg, float val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_FloatRules_set_ignore_empty(validate_FloatRules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_DoubleRules* validate_DoubleRules_new(upb_Arena* arena) {
  return (validate_DoubleRules*)_upb_Message_New(&validate__DoubleRules_msg_init, arena);
}
UPB_INLINE validate_DoubleRules* validate_DoubleRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_DoubleRules* ret = validate_DoubleRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__DoubleRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_DoubleRules* validate_DoubleRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_DoubleRules* ret = validate_DoubleRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__DoubleRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_DoubleRules_serialize(const validate_DoubleRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__DoubleRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_DoubleRules_serialize_ex(const validate_DoubleRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__DoubleRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_DoubleRules_clear_const(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double validate_DoubleRules_const(const validate_DoubleRules* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DoubleRules_has_const(const validate_DoubleRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DoubleRules_clear_lt(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double validate_DoubleRules_lt(const validate_DoubleRules* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DoubleRules_has_lt(const validate_DoubleRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DoubleRules_clear_lte(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double validate_DoubleRules_lte(const validate_DoubleRules* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DoubleRules_has_lte(const validate_DoubleRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DoubleRules_clear_gt(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double validate_DoubleRules_gt(const validate_DoubleRules* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DoubleRules_has_gt(const validate_DoubleRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DoubleRules_clear_gte(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double validate_DoubleRules_gte(const validate_DoubleRules* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DoubleRules_has_gte(const validate_DoubleRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DoubleRules_clear_in(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double const* validate_DoubleRules_in(const validate_DoubleRules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (double const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_DoubleRules_in_upb_array(const validate_DoubleRules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_DoubleRules_in_mutable_upb_array(validate_DoubleRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_DoubleRules_clear_not_in(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double const* validate_DoubleRules_not_in(const validate_DoubleRules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (double const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_DoubleRules_not_in_upb_array(const validate_DoubleRules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_DoubleRules_not_in_mutable_upb_array(validate_DoubleRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_DoubleRules_clear_ignore_empty(validate_DoubleRules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_DoubleRules_ignore_empty(const validate_DoubleRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DoubleRules_has_ignore_empty(const validate_DoubleRules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_DoubleRules_set_const(validate_DoubleRules *msg, double value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_DoubleRules_set_lt(validate_DoubleRules *msg, double value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_DoubleRules_set_lte(validate_DoubleRules *msg, double value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_DoubleRules_set_gt(validate_DoubleRules *msg, double value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_DoubleRules_set_gte(validate_DoubleRules *msg, double value) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE double* validate_DoubleRules_mutable_in(validate_DoubleRules* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (double*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE double* validate_DoubleRules_resize_in(validate_DoubleRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (double*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_DoubleRules_add_in(validate_DoubleRules* msg, double val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE double* validate_DoubleRules_mutable_not_in(validate_DoubleRules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (double*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE double* validate_DoubleRules_resize_not_in(validate_DoubleRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (double*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_DoubleRules_add_not_in(validate_DoubleRules* msg, double val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_DoubleRules_set_ignore_empty(validate_DoubleRules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_Int32Rules* validate_Int32Rules_new(upb_Arena* arena) {
  return (validate_Int32Rules*)_upb_Message_New(&validate__Int32Rules_msg_init, arena);
}
UPB_INLINE validate_Int32Rules* validate_Int32Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_Int32Rules* ret = validate_Int32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Int32Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_Int32Rules* validate_Int32Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_Int32Rules* ret = validate_Int32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Int32Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_Int32Rules_serialize(const validate_Int32Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Int32Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_Int32Rules_serialize_ex(const validate_Int32Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Int32Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_Int32Rules_clear_const(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_Int32Rules_const(const validate_Int32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int32Rules_has_const(const validate_Int32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int32Rules_clear_lt(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_Int32Rules_lt(const validate_Int32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int32Rules_has_lt(const validate_Int32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int32Rules_clear_lte(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_Int32Rules_lte(const validate_Int32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int32Rules_has_lte(const validate_Int32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int32Rules_clear_gt(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_Int32Rules_gt(const validate_Int32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int32Rules_has_gt(const validate_Int32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int32Rules_clear_gte(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_Int32Rules_gte(const validate_Int32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int32Rules_has_gte(const validate_Int32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int32Rules_clear_in(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_Int32Rules_in(const validate_Int32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Int32Rules_in_upb_array(const validate_Int32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Int32Rules_in_mutable_upb_array(validate_Int32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Int32Rules_clear_not_in(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_Int32Rules_not_in(const validate_Int32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Int32Rules_not_in_upb_array(const validate_Int32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Int32Rules_not_in_mutable_upb_array(validate_Int32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Int32Rules_clear_ignore_empty(validate_Int32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_Int32Rules_ignore_empty(const validate_Int32Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int32Rules_has_ignore_empty(const validate_Int32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_Int32Rules_set_const(validate_Int32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int32Rules_set_lt(validate_Int32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int32Rules_set_lte(validate_Int32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int32Rules_set_gt(validate_Int32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int32Rules_set_gte(validate_Int32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* validate_Int32Rules_mutable_in(validate_Int32Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_Int32Rules_resize_in(validate_Int32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Int32Rules_add_in(validate_Int32Rules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int32_t* validate_Int32Rules_mutable_not_in(validate_Int32Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_Int32Rules_resize_not_in(validate_Int32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Int32Rules_add_not_in(validate_Int32Rules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_Int32Rules_set_ignore_empty(validate_Int32Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_Int64Rules* validate_Int64Rules_new(upb_Arena* arena) {
  return (validate_Int64Rules*)_upb_Message_New(&validate__Int64Rules_msg_init, arena);
}
UPB_INLINE validate_Int64Rules* validate_Int64Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_Int64Rules* ret = validate_Int64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Int64Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_Int64Rules* validate_Int64Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_Int64Rules* ret = validate_Int64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Int64Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_Int64Rules_serialize(const validate_Int64Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Int64Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_Int64Rules_serialize_ex(const validate_Int64Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Int64Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_Int64Rules_clear_const(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_Int64Rules_const(const validate_Int64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int64Rules_has_const(const validate_Int64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int64Rules_clear_lt(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_Int64Rules_lt(const validate_Int64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int64Rules_has_lt(const validate_Int64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int64Rules_clear_lte(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_Int64Rules_lte(const validate_Int64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int64Rules_has_lte(const validate_Int64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int64Rules_clear_gt(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_Int64Rules_gt(const validate_Int64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int64Rules_has_gt(const validate_Int64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int64Rules_clear_gte(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_Int64Rules_gte(const validate_Int64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int64Rules_has_gte(const validate_Int64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Int64Rules_clear_in(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t const* validate_Int64Rules_in(const validate_Int64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Int64Rules_in_upb_array(const validate_Int64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Int64Rules_in_mutable_upb_array(validate_Int64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Int64Rules_clear_not_in(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t const* validate_Int64Rules_not_in(const validate_Int64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Int64Rules_not_in_upb_array(const validate_Int64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Int64Rules_not_in_mutable_upb_array(validate_Int64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Int64Rules_clear_ignore_empty(validate_Int64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_Int64Rules_ignore_empty(const validate_Int64Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Int64Rules_has_ignore_empty(const validate_Int64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_Int64Rules_set_const(validate_Int64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int64Rules_set_lt(validate_Int64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int64Rules_set_lte(validate_Int64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int64Rules_set_gt(validate_Int64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Int64Rules_set_gte(validate_Int64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int64_t* validate_Int64Rules_mutable_in(validate_Int64Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int64_t* validate_Int64Rules_resize_in(validate_Int64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Int64Rules_add_in(validate_Int64Rules* msg, int64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int64_t* validate_Int64Rules_mutable_not_in(validate_Int64Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int64_t* validate_Int64Rules_resize_not_in(validate_Int64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Int64Rules_add_not_in(validate_Int64Rules* msg, int64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_Int64Rules_set_ignore_empty(validate_Int64Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_UInt32Rules* validate_UInt32Rules_new(upb_Arena* arena) {
  return (validate_UInt32Rules*)_upb_Message_New(&validate__UInt32Rules_msg_init, arena);
}
UPB_INLINE validate_UInt32Rules* validate_UInt32Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_UInt32Rules* ret = validate_UInt32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__UInt32Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_UInt32Rules* validate_UInt32Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_UInt32Rules* ret = validate_UInt32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__UInt32Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_UInt32Rules_serialize(const validate_UInt32Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__UInt32Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_UInt32Rules_serialize_ex(const validate_UInt32Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__UInt32Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_UInt32Rules_clear_const(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_UInt32Rules_const(const validate_UInt32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt32Rules_has_const(const validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt32Rules_clear_lt(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_UInt32Rules_lt(const validate_UInt32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt32Rules_has_lt(const validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt32Rules_clear_lte(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_UInt32Rules_lte(const validate_UInt32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt32Rules_has_lte(const validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt32Rules_clear_gt(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_UInt32Rules_gt(const validate_UInt32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt32Rules_has_gt(const validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt32Rules_clear_gte(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_UInt32Rules_gte(const validate_UInt32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt32Rules_has_gte(const validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt32Rules_clear_in(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* validate_UInt32Rules_in(const validate_UInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_UInt32Rules_in_upb_array(const validate_UInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_UInt32Rules_in_mutable_upb_array(validate_UInt32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_UInt32Rules_clear_not_in(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* validate_UInt32Rules_not_in(const validate_UInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_UInt32Rules_not_in_upb_array(const validate_UInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_UInt32Rules_not_in_mutable_upb_array(validate_UInt32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_UInt32Rules_clear_ignore_empty(validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_UInt32Rules_ignore_empty(const validate_UInt32Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt32Rules_has_ignore_empty(const validate_UInt32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_UInt32Rules_set_const(validate_UInt32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt32Rules_set_lt(validate_UInt32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt32Rules_set_lte(validate_UInt32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt32Rules_set_gt(validate_UInt32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt32Rules_set_gte(validate_UInt32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE uint32_t* validate_UInt32Rules_mutable_in(validate_UInt32Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* validate_UInt32Rules_resize_in(validate_UInt32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_UInt32Rules_add_in(validate_UInt32Rules* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE uint32_t* validate_UInt32Rules_mutable_not_in(validate_UInt32Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* validate_UInt32Rules_resize_not_in(validate_UInt32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_UInt32Rules_add_not_in(validate_UInt32Rules* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_UInt32Rules_set_ignore_empty(validate_UInt32Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_UInt64Rules* validate_UInt64Rules_new(upb_Arena* arena) {
  return (validate_UInt64Rules*)_upb_Message_New(&validate__UInt64Rules_msg_init, arena);
}
UPB_INLINE validate_UInt64Rules* validate_UInt64Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_UInt64Rules* ret = validate_UInt64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__UInt64Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_UInt64Rules* validate_UInt64Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_UInt64Rules* ret = validate_UInt64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__UInt64Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_UInt64Rules_serialize(const validate_UInt64Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__UInt64Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_UInt64Rules_serialize_ex(const validate_UInt64Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__UInt64Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_UInt64Rules_clear_const(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_UInt64Rules_const(const validate_UInt64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt64Rules_has_const(const validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt64Rules_clear_lt(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_UInt64Rules_lt(const validate_UInt64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt64Rules_has_lt(const validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt64Rules_clear_lte(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_UInt64Rules_lte(const validate_UInt64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt64Rules_has_lte(const validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt64Rules_clear_gt(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_UInt64Rules_gt(const validate_UInt64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt64Rules_has_gt(const validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt64Rules_clear_gte(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_UInt64Rules_gte(const validate_UInt64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt64Rules_has_gte(const validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_UInt64Rules_clear_in(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t const* validate_UInt64Rules_in(const validate_UInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_UInt64Rules_in_upb_array(const validate_UInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_UInt64Rules_in_mutable_upb_array(validate_UInt64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_UInt64Rules_clear_not_in(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t const* validate_UInt64Rules_not_in(const validate_UInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_UInt64Rules_not_in_upb_array(const validate_UInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_UInt64Rules_not_in_mutable_upb_array(validate_UInt64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_UInt64Rules_clear_ignore_empty(validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_UInt64Rules_ignore_empty(const validate_UInt64Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_UInt64Rules_has_ignore_empty(const validate_UInt64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_UInt64Rules_set_const(validate_UInt64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt64Rules_set_lt(validate_UInt64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt64Rules_set_lte(validate_UInt64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt64Rules_set_gt(validate_UInt64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_UInt64Rules_set_gte(validate_UInt64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE uint64_t* validate_UInt64Rules_mutable_in(validate_UInt64Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint64_t* validate_UInt64Rules_resize_in(validate_UInt64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_UInt64Rules_add_in(validate_UInt64Rules* msg, uint64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE uint64_t* validate_UInt64Rules_mutable_not_in(validate_UInt64Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint64_t* validate_UInt64Rules_resize_not_in(validate_UInt64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_UInt64Rules_add_not_in(validate_UInt64Rules* msg, uint64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_UInt64Rules_set_ignore_empty(validate_UInt64Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_SInt32Rules* validate_SInt32Rules_new(upb_Arena* arena) {
  return (validate_SInt32Rules*)_upb_Message_New(&validate__SInt32Rules_msg_init, arena);
}
UPB_INLINE validate_SInt32Rules* validate_SInt32Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_SInt32Rules* ret = validate_SInt32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SInt32Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_SInt32Rules* validate_SInt32Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_SInt32Rules* ret = validate_SInt32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SInt32Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_SInt32Rules_serialize(const validate_SInt32Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SInt32Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_SInt32Rules_serialize_ex(const validate_SInt32Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SInt32Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_SInt32Rules_clear_const(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SInt32Rules_const(const validate_SInt32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt32Rules_has_const(const validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt32Rules_clear_lt(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SInt32Rules_lt(const validate_SInt32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt32Rules_has_lt(const validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt32Rules_clear_lte(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SInt32Rules_lte(const validate_SInt32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt32Rules_has_lte(const validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt32Rules_clear_gt(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SInt32Rules_gt(const validate_SInt32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt32Rules_has_gt(const validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt32Rules_clear_gte(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SInt32Rules_gte(const validate_SInt32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt32Rules_has_gte(const validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt32Rules_clear_in(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_SInt32Rules_in(const validate_SInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SInt32Rules_in_upb_array(const validate_SInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SInt32Rules_in_mutable_upb_array(validate_SInt32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SInt32Rules_clear_not_in(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_SInt32Rules_not_in(const validate_SInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SInt32Rules_not_in_upb_array(const validate_SInt32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SInt32Rules_not_in_mutable_upb_array(validate_SInt32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SInt32Rules_clear_ignore_empty(validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_SInt32Rules_ignore_empty(const validate_SInt32Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt32Rules_has_ignore_empty(const validate_SInt32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_SInt32Rules_set_const(validate_SInt32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt32Rules_set_lt(validate_SInt32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt32Rules_set_lte(validate_SInt32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt32Rules_set_gt(validate_SInt32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt32Rules_set_gte(validate_SInt32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* validate_SInt32Rules_mutable_in(validate_SInt32Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_SInt32Rules_resize_in(validate_SInt32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SInt32Rules_add_in(validate_SInt32Rules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int32_t* validate_SInt32Rules_mutable_not_in(validate_SInt32Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_SInt32Rules_resize_not_in(validate_SInt32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SInt32Rules_add_not_in(validate_SInt32Rules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_SInt32Rules_set_ignore_empty(validate_SInt32Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_SInt64Rules* validate_SInt64Rules_new(upb_Arena* arena) {
  return (validate_SInt64Rules*)_upb_Message_New(&validate__SInt64Rules_msg_init, arena);
}
UPB_INLINE validate_SInt64Rules* validate_SInt64Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_SInt64Rules* ret = validate_SInt64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SInt64Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_SInt64Rules* validate_SInt64Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_SInt64Rules* ret = validate_SInt64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SInt64Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_SInt64Rules_serialize(const validate_SInt64Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SInt64Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_SInt64Rules_serialize_ex(const validate_SInt64Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SInt64Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_SInt64Rules_clear_const(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SInt64Rules_const(const validate_SInt64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt64Rules_has_const(const validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt64Rules_clear_lt(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SInt64Rules_lt(const validate_SInt64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt64Rules_has_lt(const validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt64Rules_clear_lte(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SInt64Rules_lte(const validate_SInt64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt64Rules_has_lte(const validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt64Rules_clear_gt(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SInt64Rules_gt(const validate_SInt64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt64Rules_has_gt(const validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt64Rules_clear_gte(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SInt64Rules_gte(const validate_SInt64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt64Rules_has_gte(const validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SInt64Rules_clear_in(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t const* validate_SInt64Rules_in(const validate_SInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SInt64Rules_in_upb_array(const validate_SInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SInt64Rules_in_mutable_upb_array(validate_SInt64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SInt64Rules_clear_not_in(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t const* validate_SInt64Rules_not_in(const validate_SInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SInt64Rules_not_in_upb_array(const validate_SInt64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SInt64Rules_not_in_mutable_upb_array(validate_SInt64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SInt64Rules_clear_ignore_empty(validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_SInt64Rules_ignore_empty(const validate_SInt64Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SInt64Rules_has_ignore_empty(const validate_SInt64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_SInt64Rules_set_const(validate_SInt64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt64Rules_set_lt(validate_SInt64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt64Rules_set_lte(validate_SInt64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt64Rules_set_gt(validate_SInt64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SInt64Rules_set_gte(validate_SInt64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int64_t* validate_SInt64Rules_mutable_in(validate_SInt64Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int64_t* validate_SInt64Rules_resize_in(validate_SInt64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SInt64Rules_add_in(validate_SInt64Rules* msg, int64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int64_t* validate_SInt64Rules_mutable_not_in(validate_SInt64Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int64_t* validate_SInt64Rules_resize_not_in(validate_SInt64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SInt64Rules_add_not_in(validate_SInt64Rules* msg, int64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_SInt64Rules_set_ignore_empty(validate_SInt64Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_Fixed32Rules* validate_Fixed32Rules_new(upb_Arena* arena) {
  return (validate_Fixed32Rules*)_upb_Message_New(&validate__Fixed32Rules_msg_init, arena);
}
UPB_INLINE validate_Fixed32Rules* validate_Fixed32Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_Fixed32Rules* ret = validate_Fixed32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Fixed32Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_Fixed32Rules* validate_Fixed32Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_Fixed32Rules* ret = validate_Fixed32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Fixed32Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_Fixed32Rules_serialize(const validate_Fixed32Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Fixed32Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_Fixed32Rules_serialize_ex(const validate_Fixed32Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Fixed32Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_Fixed32Rules_clear_const(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_Fixed32Rules_const(const validate_Fixed32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed32Rules_has_const(const validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed32Rules_clear_lt(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_Fixed32Rules_lt(const validate_Fixed32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed32Rules_has_lt(const validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed32Rules_clear_lte(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_Fixed32Rules_lte(const validate_Fixed32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed32Rules_has_lte(const validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed32Rules_clear_gt(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_Fixed32Rules_gt(const validate_Fixed32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed32Rules_has_gt(const validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed32Rules_clear_gte(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t validate_Fixed32Rules_gte(const validate_Fixed32Rules* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed32Rules_has_gte(const validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed32Rules_clear_in(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* validate_Fixed32Rules_in(const validate_Fixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Fixed32Rules_in_upb_array(const validate_Fixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Fixed32Rules_in_mutable_upb_array(validate_Fixed32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Fixed32Rules_clear_not_in(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* validate_Fixed32Rules_not_in(const validate_Fixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Fixed32Rules_not_in_upb_array(const validate_Fixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Fixed32Rules_not_in_mutable_upb_array(validate_Fixed32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Fixed32Rules_clear_ignore_empty(validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_Fixed32Rules_ignore_empty(const validate_Fixed32Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed32Rules_has_ignore_empty(const validate_Fixed32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_Fixed32Rules_set_const(validate_Fixed32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed32Rules_set_lt(validate_Fixed32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed32Rules_set_lte(validate_Fixed32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed32Rules_set_gt(validate_Fixed32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed32Rules_set_gte(validate_Fixed32Rules *msg, uint32_t value) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE uint32_t* validate_Fixed32Rules_mutable_in(validate_Fixed32Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* validate_Fixed32Rules_resize_in(validate_Fixed32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Fixed32Rules_add_in(validate_Fixed32Rules* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE uint32_t* validate_Fixed32Rules_mutable_not_in(validate_Fixed32Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* validate_Fixed32Rules_resize_not_in(validate_Fixed32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Fixed32Rules_add_not_in(validate_Fixed32Rules* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_Fixed32Rules_set_ignore_empty(validate_Fixed32Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_Fixed64Rules* validate_Fixed64Rules_new(upb_Arena* arena) {
  return (validate_Fixed64Rules*)_upb_Message_New(&validate__Fixed64Rules_msg_init, arena);
}
UPB_INLINE validate_Fixed64Rules* validate_Fixed64Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_Fixed64Rules* ret = validate_Fixed64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Fixed64Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_Fixed64Rules* validate_Fixed64Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_Fixed64Rules* ret = validate_Fixed64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__Fixed64Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_Fixed64Rules_serialize(const validate_Fixed64Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Fixed64Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_Fixed64Rules_serialize_ex(const validate_Fixed64Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__Fixed64Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_Fixed64Rules_clear_const(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_Fixed64Rules_const(const validate_Fixed64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed64Rules_has_const(const validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed64Rules_clear_lt(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_Fixed64Rules_lt(const validate_Fixed64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed64Rules_has_lt(const validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed64Rules_clear_lte(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_Fixed64Rules_lte(const validate_Fixed64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed64Rules_has_lte(const validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed64Rules_clear_gt(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_Fixed64Rules_gt(const validate_Fixed64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed64Rules_has_gt(const validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed64Rules_clear_gte(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_Fixed64Rules_gte(const validate_Fixed64Rules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed64Rules_has_gte(const validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_Fixed64Rules_clear_in(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t const* validate_Fixed64Rules_in(const validate_Fixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Fixed64Rules_in_upb_array(const validate_Fixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Fixed64Rules_in_mutable_upb_array(validate_Fixed64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Fixed64Rules_clear_not_in(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t const* validate_Fixed64Rules_not_in(const validate_Fixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_Fixed64Rules_not_in_upb_array(const validate_Fixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_Fixed64Rules_not_in_mutable_upb_array(validate_Fixed64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_Fixed64Rules_clear_ignore_empty(validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_Fixed64Rules_ignore_empty(const validate_Fixed64Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_Fixed64Rules_has_ignore_empty(const validate_Fixed64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_Fixed64Rules_set_const(validate_Fixed64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed64Rules_set_lt(validate_Fixed64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed64Rules_set_lte(validate_Fixed64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed64Rules_set_gt(validate_Fixed64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_Fixed64Rules_set_gte(validate_Fixed64Rules *msg, uint64_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE uint64_t* validate_Fixed64Rules_mutable_in(validate_Fixed64Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint64_t* validate_Fixed64Rules_resize_in(validate_Fixed64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Fixed64Rules_add_in(validate_Fixed64Rules* msg, uint64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE uint64_t* validate_Fixed64Rules_mutable_not_in(validate_Fixed64Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint64_t* validate_Fixed64Rules_resize_not_in(validate_Fixed64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_Fixed64Rules_add_not_in(validate_Fixed64Rules* msg, uint64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_Fixed64Rules_set_ignore_empty(validate_Fixed64Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_SFixed32Rules* validate_SFixed32Rules_new(upb_Arena* arena) {
  return (validate_SFixed32Rules*)_upb_Message_New(&validate__SFixed32Rules_msg_init, arena);
}
UPB_INLINE validate_SFixed32Rules* validate_SFixed32Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_SFixed32Rules* ret = validate_SFixed32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SFixed32Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_SFixed32Rules* validate_SFixed32Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_SFixed32Rules* ret = validate_SFixed32Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SFixed32Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_SFixed32Rules_serialize(const validate_SFixed32Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SFixed32Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_SFixed32Rules_serialize_ex(const validate_SFixed32Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SFixed32Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_SFixed32Rules_clear_const(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SFixed32Rules_const(const validate_SFixed32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed32Rules_has_const(const validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed32Rules_clear_lt(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SFixed32Rules_lt(const validate_SFixed32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed32Rules_has_lt(const validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed32Rules_clear_lte(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SFixed32Rules_lte(const validate_SFixed32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed32Rules_has_lte(const validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed32Rules_clear_gt(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SFixed32Rules_gt(const validate_SFixed32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed32Rules_has_gt(const validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed32Rules_clear_gte(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_SFixed32Rules_gte(const validate_SFixed32Rules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed32Rules_has_gte(const validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed32Rules_clear_in(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_SFixed32Rules_in(const validate_SFixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SFixed32Rules_in_upb_array(const validate_SFixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SFixed32Rules_in_mutable_upb_array(validate_SFixed32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SFixed32Rules_clear_not_in(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_SFixed32Rules_not_in(const validate_SFixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SFixed32Rules_not_in_upb_array(const validate_SFixed32Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SFixed32Rules_not_in_mutable_upb_array(validate_SFixed32Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SFixed32Rules_clear_ignore_empty(validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_SFixed32Rules_ignore_empty(const validate_SFixed32Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed32Rules_has_ignore_empty(const validate_SFixed32Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_SFixed32Rules_set_const(validate_SFixed32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed32Rules_set_lt(validate_SFixed32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {2, 16, 65, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed32Rules_set_lte(validate_SFixed32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {3, 20, 66, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed32Rules_set_gt(validate_SFixed32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {4, 24, 67, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed32Rules_set_gte(validate_SFixed32Rules *msg, int32_t value) {
  const upb_MiniTableField field = {5, 28, 68, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* validate_SFixed32Rules_mutable_in(validate_SFixed32Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_SFixed32Rules_resize_in(validate_SFixed32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SFixed32Rules_add_in(validate_SFixed32Rules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int32_t* validate_SFixed32Rules_mutable_not_in(validate_SFixed32Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_SFixed32Rules_resize_not_in(validate_SFixed32Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SFixed32Rules_add_not_in(validate_SFixed32Rules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_SFixed32Rules_set_ignore_empty(validate_SFixed32Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_SFixed64Rules* validate_SFixed64Rules_new(upb_Arena* arena) {
  return (validate_SFixed64Rules*)_upb_Message_New(&validate__SFixed64Rules_msg_init, arena);
}
UPB_INLINE validate_SFixed64Rules* validate_SFixed64Rules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_SFixed64Rules* ret = validate_SFixed64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SFixed64Rules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_SFixed64Rules* validate_SFixed64Rules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_SFixed64Rules* ret = validate_SFixed64Rules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__SFixed64Rules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_SFixed64Rules_serialize(const validate_SFixed64Rules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SFixed64Rules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_SFixed64Rules_serialize_ex(const validate_SFixed64Rules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__SFixed64Rules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_SFixed64Rules_clear_const(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SFixed64Rules_const(const validate_SFixed64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed64Rules_has_const(const validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed64Rules_clear_lt(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SFixed64Rules_lt(const validate_SFixed64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed64Rules_has_lt(const validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed64Rules_clear_lte(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SFixed64Rules_lte(const validate_SFixed64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed64Rules_has_lte(const validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed64Rules_clear_gt(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SFixed64Rules_gt(const validate_SFixed64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed64Rules_has_gt(const validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed64Rules_clear_gte(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t validate_SFixed64Rules_gte(const validate_SFixed64Rules* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed64Rules_has_gte(const validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_SFixed64Rules_clear_in(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t const* validate_SFixed64Rules_in(const validate_SFixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SFixed64Rules_in_upb_array(const validate_SFixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SFixed64Rules_in_mutable_upb_array(validate_SFixed64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SFixed64Rules_clear_not_in(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t const* validate_SFixed64Rules_not_in(const validate_SFixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_SFixed64Rules_not_in_upb_array(const validate_SFixed64Rules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_SFixed64Rules_not_in_mutable_upb_array(validate_SFixed64Rules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_SFixed64Rules_clear_ignore_empty(validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_SFixed64Rules_ignore_empty(const validate_SFixed64Rules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_SFixed64Rules_has_ignore_empty(const validate_SFixed64Rules* msg) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_SFixed64Rules_set_const(validate_SFixed64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed64Rules_set_lt(validate_SFixed64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed64Rules_set_lte(validate_SFixed64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed64Rules_set_gt(validate_SFixed64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_SFixed64Rules_set_gte(validate_SFixed64Rules *msg, int64_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int64_t* validate_SFixed64Rules_mutable_in(validate_SFixed64Rules* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int64_t* validate_SFixed64Rules_resize_in(validate_SFixed64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SFixed64Rules_add_in(validate_SFixed64Rules* msg, int64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int64_t* validate_SFixed64Rules_mutable_not_in(validate_SFixed64Rules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int64_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int64_t* validate_SFixed64Rules_resize_not_in(validate_SFixed64Rules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int64_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_SFixed64Rules_add_not_in(validate_SFixed64Rules* msg, int64_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_SFixed64Rules_set_ignore_empty(validate_SFixed64Rules *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_BoolRules* validate_BoolRules_new(upb_Arena* arena) {
  return (validate_BoolRules*)_upb_Message_New(&validate__BoolRules_msg_init, arena);
}
UPB_INLINE validate_BoolRules* validate_BoolRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_BoolRules* ret = validate_BoolRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__BoolRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_BoolRules* validate_BoolRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_BoolRules* ret = validate_BoolRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__BoolRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_BoolRules_serialize(const validate_BoolRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__BoolRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_BoolRules_serialize_ex(const validate_BoolRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__BoolRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_BoolRules_clear_const(validate_BoolRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_BoolRules_const(const validate_BoolRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BoolRules_has_const(const validate_BoolRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_BoolRules_set_const(validate_BoolRules *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_StringRules* validate_StringRules_new(upb_Arena* arena) {
  return (validate_StringRules*)_upb_Message_New(&validate__StringRules_msg_init, arena);
}
UPB_INLINE validate_StringRules* validate_StringRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_StringRules* ret = validate_StringRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__StringRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_StringRules* validate_StringRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_StringRules* ret = validate_StringRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__StringRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_StringRules_serialize(const validate_StringRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__StringRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_StringRules_serialize_ex(const validate_StringRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__StringRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  validate_StringRules_well_known_email = 12,
  validate_StringRules_well_known_hostname = 13,
  validate_StringRules_well_known_ip = 14,
  validate_StringRules_well_known_ipv4 = 15,
  validate_StringRules_well_known_ipv6 = 16,
  validate_StringRules_well_known_uri = 17,
  validate_StringRules_well_known_uri_ref = 18,
  validate_StringRules_well_known_address = 21,
  validate_StringRules_well_known_uuid = 22,
  validate_StringRules_well_known_well_known_regex = 24,
  validate_StringRules_well_known_NOT_SET = 0
} validate_StringRules_well_known_oneofcases;
UPB_INLINE validate_StringRules_well_known_oneofcases validate_StringRules_well_known_case(const validate_StringRules* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (validate_StringRules_well_known_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_well_known(validate_StringRules* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &validate__StringRules_msg_init, &field);
}
UPB_INLINE void validate_StringRules_clear_const(validate_StringRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_StringRules_const(const validate_StringRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_const(const validate_StringRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_min_len(validate_StringRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(80, 120), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_StringRules_min_len(const validate_StringRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(80, 120), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_min_len(const validate_StringRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(80, 120), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_max_len(validate_StringRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(88, 128), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_StringRules_max_len(const validate_StringRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(88, 128), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_max_len(const validate_StringRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(88, 128), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_min_bytes(validate_StringRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(96, 136), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_StringRules_min_bytes(const validate_StringRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(96, 136), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_min_bytes(const validate_StringRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(96, 136), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_max_bytes(validate_StringRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(104, 144), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_StringRules_max_bytes(const validate_StringRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(104, 144), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_max_bytes(const validate_StringRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(104, 144), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_pattern(validate_StringRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 40), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_StringRules_pattern(const validate_StringRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(36, 40), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_pattern(const validate_StringRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 40), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_prefix(validate_StringRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(44, 56), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_StringRules_prefix(const validate_StringRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(44, 56), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_prefix(const validate_StringRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(44, 56), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_suffix(validate_StringRules* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(52, 72), 71, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_StringRules_suffix(const validate_StringRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(52, 72), 71, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_suffix(const validate_StringRules* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(52, 72), 71, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_contains(validate_StringRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(60, 88), 72, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_StringRules_contains(const validate_StringRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(60, 88), 72, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_contains(const validate_StringRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(60, 88), 72, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_in(validate_StringRules* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* validate_StringRules_in(const validate_StringRules* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_StringRules_in_upb_array(const validate_StringRules* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_StringRules_in_mutable_upb_array(validate_StringRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_StringRules_clear_not_in(validate_StringRules* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* validate_StringRules_not_in(const validate_StringRules* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_StringRules_not_in_upb_array(const validate_StringRules* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_StringRules_not_in_mutable_upb_array(validate_StringRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_StringRules_clear_email(validate_StringRules* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_email(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_email(const validate_StringRules* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_hostname(validate_StringRules* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_hostname(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {13, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_hostname(const validate_StringRules* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_ip(validate_StringRules* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_ip(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {14, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_ip(const validate_StringRules* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_ipv4(validate_StringRules* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_ipv4(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {15, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_ipv4(const validate_StringRules* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_ipv6(validate_StringRules* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_ipv6(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {16, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_ipv6(const validate_StringRules* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_uri(validate_StringRules* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_uri(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {17, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_uri(const validate_StringRules* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_uri_ref(validate_StringRules* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_uri_ref(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {18, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_uri_ref(const validate_StringRules* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_len(validate_StringRules* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(112, 168), 73, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_StringRules_len(const validate_StringRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {19, UPB_SIZE(112, 168), 73, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_len(const validate_StringRules* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(112, 168), 73, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_len_bytes(validate_StringRules* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(120, 176), 74, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_StringRules_len_bytes(const validate_StringRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {20, UPB_SIZE(120, 176), 74, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_len_bytes(const validate_StringRules* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(120, 176), 74, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_address(validate_StringRules* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_address(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {21, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_address(const validate_StringRules* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_uuid(validate_StringRules* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_uuid(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {22, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_uuid(const validate_StringRules* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_not_contains(validate_StringRules* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(68, 104), 75, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_StringRules_not_contains(const validate_StringRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {23, UPB_SIZE(68, 104), 75, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_not_contains(const validate_StringRules* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(68, 104), 75, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_well_known_regex(validate_StringRules* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_StringRules_well_known_regex(const validate_StringRules* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {24, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_well_known_regex(const validate_StringRules* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_strict(validate_StringRules* msg) {
  const upb_MiniTableField field = {25, 10, 76, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_strict(const validate_StringRules* msg) {
  bool default_val = true;
  bool ret;
  const upb_MiniTableField field = {25, 10, 76, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_strict(const validate_StringRules* msg) {
  const upb_MiniTableField field = {25, 10, 76, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_StringRules_clear_ignore_empty(validate_StringRules* msg) {
  const upb_MiniTableField field = {26, 11, 77, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_StringRules_ignore_empty(const validate_StringRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {26, 11, 77, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_StringRules_has_ignore_empty(const validate_StringRules* msg) {
  const upb_MiniTableField field = {26, 11, 77, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_StringRules_set_const(validate_StringRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_min_len(validate_StringRules *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(80, 120), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_max_len(validate_StringRules *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(88, 128), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_min_bytes(validate_StringRules *msg, uint64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(96, 136), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_max_bytes(validate_StringRules *msg, uint64_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(104, 144), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_pattern(validate_StringRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 40), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_prefix(validate_StringRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(44, 56), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_suffix(validate_StringRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(52, 72), 71, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_contains(validate_StringRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(60, 88), 72, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* validate_StringRules_mutable_in(validate_StringRules* msg, size_t* size) {
  upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* validate_StringRules_resize_in(validate_StringRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_StringRules_add_in(validate_StringRules* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE upb_StringView* validate_StringRules_mutable_not_in(validate_StringRules* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* validate_StringRules_resize_not_in(validate_StringRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_StringRules_add_not_in(validate_StringRules* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_StringRules_set_email(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_hostname(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {13, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_ip(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {14, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_ipv4(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {15, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_ipv6(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {16, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_uri(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {17, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_uri_ref(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {18, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_len(validate_StringRules *msg, uint64_t value) {
  const upb_MiniTableField field = {19, UPB_SIZE(112, 168), 73, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_len_bytes(validate_StringRules *msg, uint64_t value) {
  const upb_MiniTableField field = {20, UPB_SIZE(120, 176), 74, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_address(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {21, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_uuid(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {22, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_not_contains(validate_StringRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {23, UPB_SIZE(68, 104), 75, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_well_known_regex(validate_StringRules *msg, int32_t value) {
  const upb_MiniTableField field = {24, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_strict(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {25, 10, 76, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_StringRules_set_ignore_empty(validate_StringRules *msg, bool value) {
  const upb_MiniTableField field = {26, 11, 77, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_BytesRules* validate_BytesRules_new(upb_Arena* arena) {
  return (validate_BytesRules*)_upb_Message_New(&validate__BytesRules_msg_init, arena);
}
UPB_INLINE validate_BytesRules* validate_BytesRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_BytesRules* ret = validate_BytesRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__BytesRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_BytesRules* validate_BytesRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_BytesRules* ret = validate_BytesRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__BytesRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_BytesRules_serialize(const validate_BytesRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__BytesRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_BytesRules_serialize_ex(const validate_BytesRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__BytesRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  validate_BytesRules_well_known_ip = 10,
  validate_BytesRules_well_known_ipv4 = 11,
  validate_BytesRules_well_known_ipv6 = 12,
  validate_BytesRules_well_known_NOT_SET = 0
} validate_BytesRules_well_known_oneofcases;
UPB_INLINE validate_BytesRules_well_known_oneofcases validate_BytesRules_well_known_case(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (validate_BytesRules_well_known_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_well_known(validate_BytesRules* msg) {
  const upb_MiniTableField field = {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &validate__BytesRules_msg_init, &field);
}
UPB_INLINE void validate_BytesRules_clear_const(validate_BytesRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_BytesRules_const(const validate_BytesRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_const(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_min_len(validate_BytesRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(64, 96), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_BytesRules_min_len(const validate_BytesRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(64, 96), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_min_len(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(64, 96), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_max_len(validate_BytesRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(72, 104), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_BytesRules_max_len(const validate_BytesRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(72, 104), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_max_len(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(72, 104), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_pattern(validate_BytesRules* msg) {
  const upb_MiniTableField field = {4, 32, 67, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_BytesRules_pattern(const validate_BytesRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, 32, 67, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_pattern(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {4, 32, 67, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_prefix(validate_BytesRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_BytesRules_prefix(const validate_BytesRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_prefix(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_suffix(validate_BytesRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_BytesRules_suffix(const validate_BytesRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_suffix(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_contains(validate_BytesRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView validate_BytesRules_contains(const validate_BytesRules* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_contains(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_in(validate_BytesRules* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* validate_BytesRules_in(const validate_BytesRules* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_BytesRules_in_upb_array(const validate_BytesRules* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_BytesRules_in_mutable_upb_array(validate_BytesRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_BytesRules_clear_not_in(validate_BytesRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* validate_BytesRules_not_in(const validate_BytesRules* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_BytesRules_not_in_upb_array(const validate_BytesRules* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_BytesRules_not_in_mutable_upb_array(validate_BytesRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_BytesRules_clear_ip(validate_BytesRules* msg) {
  const upb_MiniTableField field = {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_BytesRules_ip(const validate_BytesRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_ip(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_ipv4(validate_BytesRules* msg) {
  const upb_MiniTableField field = {11, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_BytesRules_ipv4(const validate_BytesRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {11, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_ipv4(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {11, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_ipv6(validate_BytesRules* msg) {
  const upb_MiniTableField field = {12, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_BytesRules_ipv6(const validate_BytesRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {12, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_ipv6(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {12, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_len(validate_BytesRules* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(80, 128), 71, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_BytesRules_len(const validate_BytesRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {13, UPB_SIZE(80, 128), 71, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_len(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(80, 128), 71, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_BytesRules_clear_ignore_empty(validate_BytesRules* msg) {
  const upb_MiniTableField field = {14, 10, 72, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_BytesRules_ignore_empty(const validate_BytesRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {14, 10, 72, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_BytesRules_has_ignore_empty(const validate_BytesRules* msg) {
  const upb_MiniTableField field = {14, 10, 72, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_BytesRules_set_const(validate_BytesRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_min_len(validate_BytesRules *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(64, 96), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_max_len(validate_BytesRules *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(72, 104), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_pattern(validate_BytesRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, 32, 67, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_prefix(validate_BytesRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_suffix(validate_BytesRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_contains(validate_BytesRules *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* validate_BytesRules_mutable_in(validate_BytesRules* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* validate_BytesRules_resize_in(validate_BytesRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_BytesRules_add_in(validate_BytesRules* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE upb_StringView* validate_BytesRules_mutable_not_in(validate_BytesRules* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* validate_BytesRules_resize_not_in(validate_BytesRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_BytesRules_add_not_in(validate_BytesRules* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void validate_BytesRules_set_ip(validate_BytesRules *msg, bool value) {
  const upb_MiniTableField field = {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_ipv4(validate_BytesRules *msg, bool value) {
  const upb_MiniTableField field = {11, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_ipv6(validate_BytesRules *msg, bool value) {
  const upb_MiniTableField field = {12, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_len(validate_BytesRules *msg, uint64_t value) {
  const upb_MiniTableField field = {13, UPB_SIZE(80, 128), 71, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_BytesRules_set_ignore_empty(validate_BytesRules *msg, bool value) {
  const upb_MiniTableField field = {14, 10, 72, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_EnumRules* validate_EnumRules_new(upb_Arena* arena) {
  return (validate_EnumRules*)_upb_Message_New(&validate__EnumRules_msg_init, arena);
}
UPB_INLINE validate_EnumRules* validate_EnumRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_EnumRules* ret = validate_EnumRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__EnumRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_EnumRules* validate_EnumRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_EnumRules* ret = validate_EnumRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__EnumRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_EnumRules_serialize(const validate_EnumRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__EnumRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_EnumRules_serialize_ex(const validate_EnumRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__EnumRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_EnumRules_clear_const(validate_EnumRules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t validate_EnumRules_const(const validate_EnumRules* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_EnumRules_has_const(const validate_EnumRules* msg) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_EnumRules_clear_defined_only(validate_EnumRules* msg) {
  const upb_MiniTableField field = {2, 9, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_EnumRules_defined_only(const validate_EnumRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_EnumRules_has_defined_only(const validate_EnumRules* msg) {
  const upb_MiniTableField field = {2, 9, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_EnumRules_clear_in(validate_EnumRules* msg) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_EnumRules_in(const validate_EnumRules* msg, size_t* size) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_EnumRules_in_upb_array(const validate_EnumRules* msg, size_t* size) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_EnumRules_in_mutable_upb_array(validate_EnumRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_EnumRules_clear_not_in(validate_EnumRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* validate_EnumRules_not_in(const validate_EnumRules* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_EnumRules_not_in_upb_array(const validate_EnumRules* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_EnumRules_not_in_mutable_upb_array(validate_EnumRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void validate_EnumRules_set_const(validate_EnumRules *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_EnumRules_set_defined_only(validate_EnumRules *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* validate_EnumRules_mutable_in(validate_EnumRules* msg, size_t* size) {
  upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_EnumRules_resize_in(validate_EnumRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_EnumRules_add_in(validate_EnumRules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE int32_t* validate_EnumRules_mutable_not_in(validate_EnumRules* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* validate_EnumRules_resize_not_in(validate_EnumRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_EnumRules_add_not_in(validate_EnumRules* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}

UPB_INLINE validate_MessageRules* validate_MessageRules_new(upb_Arena* arena) {
  return (validate_MessageRules*)_upb_Message_New(&validate__MessageRules_msg_init, arena);
}
UPB_INLINE validate_MessageRules* validate_MessageRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_MessageRules* ret = validate_MessageRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__MessageRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_MessageRules* validate_MessageRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_MessageRules* ret = validate_MessageRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__MessageRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_MessageRules_serialize(const validate_MessageRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__MessageRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_MessageRules_serialize_ex(const validate_MessageRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__MessageRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_MessageRules_clear_skip(validate_MessageRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_MessageRules_skip(const validate_MessageRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MessageRules_has_skip(const validate_MessageRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_MessageRules_clear_required(validate_MessageRules* msg) {
  const upb_MiniTableField field = {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_MessageRules_required(const validate_MessageRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MessageRules_has_required(const validate_MessageRules* msg) {
  const upb_MiniTableField field = {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_MessageRules_set_skip(validate_MessageRules *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_MessageRules_set_required(validate_MessageRules *msg, bool value) {
  const upb_MiniTableField field = {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_RepeatedRules* validate_RepeatedRules_new(upb_Arena* arena) {
  return (validate_RepeatedRules*)_upb_Message_New(&validate__RepeatedRules_msg_init, arena);
}
UPB_INLINE validate_RepeatedRules* validate_RepeatedRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_RepeatedRules* ret = validate_RepeatedRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__RepeatedRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_RepeatedRules* validate_RepeatedRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_RepeatedRules* ret = validate_RepeatedRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__RepeatedRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_RepeatedRules_serialize(const validate_RepeatedRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__RepeatedRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_RepeatedRules_serialize_ex(const validate_RepeatedRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__RepeatedRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_RepeatedRules_clear_min_items(validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {1, 16, 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_RepeatedRules_min_items(const validate_RepeatedRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 16, 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_RepeatedRules_has_min_items(const validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {1, 16, 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_RepeatedRules_clear_max_items(validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {2, 24, 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_RepeatedRules_max_items(const validate_RepeatedRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, 24, 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_RepeatedRules_has_max_items(const validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {2, 24, 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_RepeatedRules_clear_unique(validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_RepeatedRules_unique(const validate_RepeatedRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_RepeatedRules_has_unique(const validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_RepeatedRules_clear_items(validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_FieldRules* validate_RepeatedRules_items(const validate_RepeatedRules* msg) {
  const validate_FieldRules* default_val = NULL;
  const validate_FieldRules* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FieldRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_RepeatedRules_has_items(const validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_RepeatedRules_clear_ignore_empty(validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {5, 10, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_RepeatedRules_ignore_empty(const validate_RepeatedRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 10, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_RepeatedRules_has_ignore_empty(const validate_RepeatedRules* msg) {
  const upb_MiniTableField field = {5, 10, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_RepeatedRules_set_min_items(validate_RepeatedRules *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 16, 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_RepeatedRules_set_max_items(validate_RepeatedRules *msg, uint64_t value) {
  const upb_MiniTableField field = {2, 24, 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_RepeatedRules_set_unique(validate_RepeatedRules *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_RepeatedRules_set_items(validate_RepeatedRules *msg, validate_FieldRules* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FieldRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_FieldRules* validate_RepeatedRules_mutable_items(validate_RepeatedRules* msg, upb_Arena* arena) {
  struct validate_FieldRules* sub = (struct validate_FieldRules*)validate_RepeatedRules_items(msg);
  if (sub == NULL) {
    sub = (struct validate_FieldRules*)_upb_Message_New(&validate__FieldRules_msg_init, arena);
    if (sub) validate_RepeatedRules_set_items(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_RepeatedRules_set_ignore_empty(validate_RepeatedRules *msg, bool value) {
  const upb_MiniTableField field = {5, 10, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_MapRules* validate_MapRules_new(upb_Arena* arena) {
  return (validate_MapRules*)_upb_Message_New(&validate__MapRules_msg_init, arena);
}
UPB_INLINE validate_MapRules* validate_MapRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_MapRules* ret = validate_MapRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__MapRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_MapRules* validate_MapRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_MapRules* ret = validate_MapRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__MapRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_MapRules_serialize(const validate_MapRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__MapRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_MapRules_serialize_ex(const validate_MapRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__MapRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_MapRules_clear_min_pairs(validate_MapRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_MapRules_min_pairs(const validate_MapRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MapRules_has_min_pairs(const validate_MapRules* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_MapRules_clear_max_pairs(validate_MapRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t validate_MapRules_max_pairs(const validate_MapRules* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MapRules_has_max_pairs(const validate_MapRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_MapRules_clear_no_sparse(validate_MapRules* msg) {
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_MapRules_no_sparse(const validate_MapRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MapRules_has_no_sparse(const validate_MapRules* msg) {
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_MapRules_clear_keys(validate_MapRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_FieldRules* validate_MapRules_keys(const validate_MapRules* msg) {
  const validate_FieldRules* default_val = NULL;
  const validate_FieldRules* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FieldRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MapRules_has_keys(const validate_MapRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_MapRules_clear_values(validate_MapRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 40), 68, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const validate_FieldRules* validate_MapRules_values(const validate_MapRules* msg) {
  const validate_FieldRules* default_val = NULL;
  const validate_FieldRules* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 40), 68, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FieldRules_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MapRules_has_values(const validate_MapRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 40), 68, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_MapRules_clear_ignore_empty(validate_MapRules* msg) {
  const upb_MiniTableField field = {6, 10, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_MapRules_ignore_empty(const validate_MapRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 10, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_MapRules_has_ignore_empty(const validate_MapRules* msg) {
  const upb_MiniTableField field = {6, 10, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_MapRules_set_min_pairs(validate_MapRules *msg, uint64_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_MapRules_set_max_pairs(validate_MapRules *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_MapRules_set_no_sparse(validate_MapRules *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_MapRules_set_keys(validate_MapRules *msg, validate_FieldRules* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FieldRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_FieldRules* validate_MapRules_mutable_keys(validate_MapRules* msg, upb_Arena* arena) {
  struct validate_FieldRules* sub = (struct validate_FieldRules*)validate_MapRules_keys(msg);
  if (sub == NULL) {
    sub = (struct validate_FieldRules*)_upb_Message_New(&validate__FieldRules_msg_init, arena);
    if (sub) validate_MapRules_set_keys(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_MapRules_set_values(validate_MapRules *msg, validate_FieldRules* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 40), 68, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&validate__FieldRules_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct validate_FieldRules* validate_MapRules_mutable_values(validate_MapRules* msg, upb_Arena* arena) {
  struct validate_FieldRules* sub = (struct validate_FieldRules*)validate_MapRules_values(msg);
  if (sub == NULL) {
    sub = (struct validate_FieldRules*)_upb_Message_New(&validate__FieldRules_msg_init, arena);
    if (sub) validate_MapRules_set_values(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_MapRules_set_ignore_empty(validate_MapRules *msg, bool value) {
  const upb_MiniTableField field = {6, 10, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE validate_AnyRules* validate_AnyRules_new(upb_Arena* arena) {
  return (validate_AnyRules*)_upb_Message_New(&validate__AnyRules_msg_init, arena);
}
UPB_INLINE validate_AnyRules* validate_AnyRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_AnyRules* ret = validate_AnyRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__AnyRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_AnyRules* validate_AnyRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_AnyRules* ret = validate_AnyRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__AnyRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_AnyRules_serialize(const validate_AnyRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__AnyRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_AnyRules_serialize_ex(const validate_AnyRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__AnyRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_AnyRules_clear_required(validate_AnyRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_AnyRules_required(const validate_AnyRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_AnyRules_has_required(const validate_AnyRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_AnyRules_clear_in(validate_AnyRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* validate_AnyRules_in(const validate_AnyRules* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_AnyRules_in_upb_array(const validate_AnyRules* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_AnyRules_in_mutable_upb_array(validate_AnyRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_AnyRules_clear_not_in(validate_AnyRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* validate_AnyRules_not_in(const validate_AnyRules* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_AnyRules_not_in_upb_array(const validate_AnyRules* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_AnyRules_not_in_mutable_upb_array(validate_AnyRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void validate_AnyRules_set_required(validate_AnyRules *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* validate_AnyRules_mutable_in(validate_AnyRules* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* validate_AnyRules_resize_in(validate_AnyRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_AnyRules_add_in(validate_AnyRules* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE upb_StringView* validate_AnyRules_mutable_not_in(validate_AnyRules* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* validate_AnyRules_resize_not_in(validate_AnyRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool validate_AnyRules_add_not_in(validate_AnyRules* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}

UPB_INLINE validate_DurationRules* validate_DurationRules_new(upb_Arena* arena) {
  return (validate_DurationRules*)_upb_Message_New(&validate__DurationRules_msg_init, arena);
}
UPB_INLINE validate_DurationRules* validate_DurationRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_DurationRules* ret = validate_DurationRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__DurationRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_DurationRules* validate_DurationRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_DurationRules* ret = validate_DurationRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__DurationRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_DurationRules_serialize(const validate_DurationRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__DurationRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_DurationRules_serialize_ex(const validate_DurationRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__DurationRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_DurationRules_clear_required(validate_DurationRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_DurationRules_required(const validate_DurationRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DurationRules_has_required(const validate_DurationRules* msg) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DurationRules_clear_const(validate_DurationRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* validate_DurationRules_const(const validate_DurationRules* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DurationRules_has_const(const validate_DurationRules* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DurationRules_clear_lt(validate_DurationRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* validate_DurationRules_lt(const validate_DurationRules* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DurationRules_has_lt(const validate_DurationRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DurationRules_clear_lte(validate_DurationRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* validate_DurationRules_lte(const validate_DurationRules* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DurationRules_has_lte(const validate_DurationRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DurationRules_clear_gt(validate_DurationRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* validate_DurationRules_gt(const validate_DurationRules* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DurationRules_has_gt(const validate_DurationRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DurationRules_clear_gte(validate_DurationRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* validate_DurationRules_gte(const validate_DurationRules* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_DurationRules_has_gte(const validate_DurationRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_DurationRules_clear_in(validate_DurationRules* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* const* validate_DurationRules_in(const validate_DurationRules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct google_protobuf_Duration* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_DurationRules_in_upb_array(const validate_DurationRules* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_DurationRules_in_mutable_upb_array(validate_DurationRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void validate_DurationRules_clear_not_in(validate_DurationRules* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* const* validate_DurationRules_not_in(const validate_DurationRules* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct google_protobuf_Duration* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _validate_DurationRules_not_in_upb_array(const validate_DurationRules* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _validate_DurationRules_not_in_mutable_upb_array(validate_DurationRules* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void validate_DurationRules_set_required(validate_DurationRules *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_DurationRules_set_const(validate_DurationRules *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_mutable_const(validate_DurationRules* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)validate_DurationRules_const(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) validate_DurationRules_set_const(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_DurationRules_set_lt(validate_DurationRules *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_mutable_lt(validate_DurationRules* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)validate_DurationRules_lt(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) validate_DurationRules_set_lt(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_DurationRules_set_lte(validate_DurationRules *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_mutable_lte(validate_DurationRules* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)validate_DurationRules_lte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) validate_DurationRules_set_lte(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_DurationRules_set_gt(validate_DurationRules *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_mutable_gt(validate_DurationRules* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)validate_DurationRules_gt(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) validate_DurationRules_set_gt(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_DurationRules_set_gte(validate_DurationRules *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_mutable_gte(validate_DurationRules* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)validate_DurationRules_gte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) validate_DurationRules_set_gte(msg, sub);
  }
  return sub;
}
UPB_INLINE struct google_protobuf_Duration** validate_DurationRules_mutable_in(validate_DurationRules* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct google_protobuf_Duration**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct google_protobuf_Duration** validate_DurationRules_resize_in(validate_DurationRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct google_protobuf_Duration**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_add_in(validate_DurationRules* msg, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct google_protobuf_Duration** validate_DurationRules_mutable_not_in(validate_DurationRules* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct google_protobuf_Duration**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct google_protobuf_Duration** validate_DurationRules_resize_not_in(validate_DurationRules* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct google_protobuf_Duration**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_protobuf_Duration* validate_DurationRules_add_not_in(validate_DurationRules* msg, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE validate_TimestampRules* validate_TimestampRules_new(upb_Arena* arena) {
  return (validate_TimestampRules*)_upb_Message_New(&validate__TimestampRules_msg_init, arena);
}
UPB_INLINE validate_TimestampRules* validate_TimestampRules_parse(const char* buf, size_t size, upb_Arena* arena) {
  validate_TimestampRules* ret = validate_TimestampRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__TimestampRules_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE validate_TimestampRules* validate_TimestampRules_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  validate_TimestampRules* ret = validate_TimestampRules_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &validate__TimestampRules_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* validate_TimestampRules_serialize(const validate_TimestampRules* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__TimestampRules_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* validate_TimestampRules_serialize_ex(const validate_TimestampRules* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &validate__TimestampRules_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void validate_TimestampRules_clear_required(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {1, 10, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_TimestampRules_required(const validate_TimestampRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 10, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_required(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {1, 10, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_const(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {2, 16, 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* validate_TimestampRules_const(const validate_TimestampRules* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, 16, 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_const(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {2, 16, 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_lt(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* validate_TimestampRules_lt(const validate_TimestampRules* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_lt(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_lte(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* validate_TimestampRules_lte(const validate_TimestampRules* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_lte(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_gt(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* validate_TimestampRules_gt(const validate_TimestampRules* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_gt(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_gte(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* validate_TimestampRules_gte(const validate_TimestampRules* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_gte(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_lt_now(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {7, 11, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_TimestampRules_lt_now(const validate_TimestampRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 11, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_lt_now(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {7, 11, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_gt_now(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {8, 12, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool validate_TimestampRules_gt_now(const validate_TimestampRules* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 12, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_gt_now(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {8, 12, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void validate_TimestampRules_clear_within(validate_TimestampRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 56), 72, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* validate_TimestampRules_within(const validate_TimestampRules* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(36, 56), 72, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool validate_TimestampRules_has_within(const validate_TimestampRules* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 56), 72, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void validate_TimestampRules_set_required(validate_TimestampRules *msg, bool value) {
  const upb_MiniTableField field = {1, 10, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_TimestampRules_set_const(validate_TimestampRules *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, 16, 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* validate_TimestampRules_mutable_const(validate_TimestampRules* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)validate_TimestampRules_const(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) validate_TimestampRules_set_const(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_TimestampRules_set_lt(validate_TimestampRules *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* validate_TimestampRules_mutable_lt(validate_TimestampRules* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)validate_TimestampRules_lt(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) validate_TimestampRules_set_lt(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_TimestampRules_set_lte(validate_TimestampRules *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* validate_TimestampRules_mutable_lte(validate_TimestampRules* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)validate_TimestampRules_lte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) validate_TimestampRules_set_lte(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_TimestampRules_set_gt(validate_TimestampRules *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* validate_TimestampRules_mutable_gt(validate_TimestampRules* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)validate_TimestampRules_gt(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) validate_TimestampRules_set_gt(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_TimestampRules_set_gte(validate_TimestampRules *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* validate_TimestampRules_mutable_gte(validate_TimestampRules* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)validate_TimestampRules_gte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) validate_TimestampRules_set_gte(msg, sub);
  }
  return sub;
}
UPB_INLINE void validate_TimestampRules_set_lt_now(validate_TimestampRules *msg, bool value) {
  const upb_MiniTableField field = {7, 11, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_TimestampRules_set_gt_now(validate_TimestampRules *msg, bool value) {
  const upb_MiniTableField field = {8, 12, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void validate_TimestampRules_set_within(validate_TimestampRules *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 56), 72, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* validate_TimestampRules_mutable_within(validate_TimestampRules* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)validate_TimestampRules_within(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) validate_TimestampRules_set_within(msg, sub);
  }
  return sub;
}

UPB_INLINE bool validate_has_disabled(const struct google_protobuf_MessageOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &validate_disabled_ext);
}
UPB_INLINE void validate_clear_disabled(struct google_protobuf_MessageOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &validate_disabled_ext);
}
UPB_INLINE bool validate_disabled(const struct google_protobuf_MessageOptions* msg) {
  const upb_MiniTableExtension* ext = &validate_disabled_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void validate_set_disabled(struct google_protobuf_MessageOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &validate_disabled_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE bool validate_has_ignored(const struct google_protobuf_MessageOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &validate_ignored_ext);
}
UPB_INLINE void validate_clear_ignored(struct google_protobuf_MessageOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &validate_ignored_ext);
}
UPB_INLINE bool validate_ignored(const struct google_protobuf_MessageOptions* msg) {
  const upb_MiniTableExtension* ext = &validate_ignored_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void validate_set_ignored(struct google_protobuf_MessageOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &validate_ignored_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE bool validate_has_required(const struct google_protobuf_OneofOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &validate_required_ext);
}
UPB_INLINE void validate_clear_required(struct google_protobuf_OneofOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &validate_required_ext);
}
UPB_INLINE bool validate_required(const struct google_protobuf_OneofOptions* msg) {
  const upb_MiniTableExtension* ext = &validate_required_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void validate_set_required(struct google_protobuf_OneofOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &validate_required_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE bool validate_has_rules(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &validate_rules_ext);
}
UPB_INLINE void validate_clear_rules(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &validate_rules_ext);
}
UPB_INLINE const validate_FieldRules* validate_rules(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &validate_rules_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const validate_FieldRules* default_val = NULL;
  const validate_FieldRules* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void validate_set_rules(struct google_protobuf_FieldOptions* msg, const validate_FieldRules* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &validate_rules_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct validate_FieldRules* validate_mutable_rules(struct google_protobuf_FieldOptions* msg,
                                    upb_Arena* arena) {
  struct validate_FieldRules* sub = (struct validate_FieldRules*)validate_rules(msg);
  if (sub == NULL) {
    sub = (struct validate_FieldRules*)_upb_Message_New(&validate__FieldRules_msg_init, arena);
    if (sub) validate_set_rules(msg, sub, arena);
  }
  return sub;
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
