
#ifndef ENVOY_CONFIG_CORE_V3_SUBSTITUTION_FORMAT_STRING_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_SUBSTITUTION_FORMAT_STRING_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/substitution_format_string.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_JsonFormatOptions { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_JsonFormatOptions;
typedef struct envoy_config_core_v3_SubstitutionFormatString { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_SubstitutionFormatString;
struct envoy_config_core_v3_DataSource;
struct envoy_config_core_v3_TypedExtensionConfig;
struct google_protobuf_Struct;

UPB_INLINE envoy_config_core_v3_JsonFormatOptions* envoy_config_core_v3_JsonFormatOptions_new(upb_Arena* arena) {
  return (envoy_config_core_v3_JsonFormatOptions*)_upb_Message_New(&envoy__config__core__v3__JsonFormatOptions_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_JsonFormatOptions* envoy_config_core_v3_JsonFormatOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_JsonFormatOptions* ret = envoy_config_core_v3_JsonFormatOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__JsonFormatOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_JsonFormatOptions* envoy_config_core_v3_JsonFormatOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_JsonFormatOptions* ret = envoy_config_core_v3_JsonFormatOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__JsonFormatOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_JsonFormatOptions_serialize(const envoy_config_core_v3_JsonFormatOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__JsonFormatOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_JsonFormatOptions_serialize_ex(const envoy_config_core_v3_JsonFormatOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__JsonFormatOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_JsonFormatOptions_clear_sort_properties(envoy_config_core_v3_JsonFormatOptions* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_JsonFormatOptions_sort_properties(const envoy_config_core_v3_JsonFormatOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_JsonFormatOptions_set_sort_properties(envoy_config_core_v3_JsonFormatOptions *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_SubstitutionFormatString* envoy_config_core_v3_SubstitutionFormatString_new(upb_Arena* arena) {
  return (envoy_config_core_v3_SubstitutionFormatString*)_upb_Message_New(&envoy__config__core__v3__SubstitutionFormatString_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_SubstitutionFormatString* envoy_config_core_v3_SubstitutionFormatString_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_SubstitutionFormatString* ret = envoy_config_core_v3_SubstitutionFormatString_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SubstitutionFormatString_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_SubstitutionFormatString* envoy_config_core_v3_SubstitutionFormatString_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_SubstitutionFormatString* ret = envoy_config_core_v3_SubstitutionFormatString_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SubstitutionFormatString_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_SubstitutionFormatString_serialize(const envoy_config_core_v3_SubstitutionFormatString* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SubstitutionFormatString_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_SubstitutionFormatString_serialize_ex(const envoy_config_core_v3_SubstitutionFormatString* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SubstitutionFormatString_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_SubstitutionFormatString_format_text_format = 1,
  envoy_config_core_v3_SubstitutionFormatString_format_json_format = 2,
  envoy_config_core_v3_SubstitutionFormatString_format_text_format_source = 5,
  envoy_config_core_v3_SubstitutionFormatString_format_NOT_SET = 0
} envoy_config_core_v3_SubstitutionFormatString_format_oneofcases;
UPB_INLINE envoy_config_core_v3_SubstitutionFormatString_format_oneofcases envoy_config_core_v3_SubstitutionFormatString_format_case(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_SubstitutionFormatString_format_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_format(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__SubstitutionFormatString_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_text_format(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_SubstitutionFormatString_text_format(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SubstitutionFormatString_has_text_format(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_json_format(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {2, 32, UPB_SIZE(-21, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_core_v3_SubstitutionFormatString_json_format(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, 32, UPB_SIZE(-21, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SubstitutionFormatString_has_json_format(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {2, 32, UPB_SIZE(-21, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_omit_empty_values(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_SubstitutionFormatString_omit_empty_values(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_content_type(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_SubstitutionFormatString_content_type(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_text_format_source(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {5, 32, UPB_SIZE(-21, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_core_v3_SubstitutionFormatString_text_format_source(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {5, 32, UPB_SIZE(-21, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SubstitutionFormatString_has_text_format_source(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {5, 32, UPB_SIZE(-21, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_formatters(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_config_core_v3_SubstitutionFormatString_formatters(const envoy_config_core_v3_SubstitutionFormatString* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_TypedExtensionConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_SubstitutionFormatString_formatters_upb_array(const envoy_config_core_v3_SubstitutionFormatString* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_SubstitutionFormatString_formatters_mutable_upb_array(envoy_config_core_v3_SubstitutionFormatString* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_clear_json_format_options(envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 56), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_JsonFormatOptions* envoy_config_core_v3_SubstitutionFormatString_json_format_options(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const envoy_config_core_v3_JsonFormatOptions* default_val = NULL;
  const envoy_config_core_v3_JsonFormatOptions* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(16, 56), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__JsonFormatOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SubstitutionFormatString_has_json_format_options(const envoy_config_core_v3_SubstitutionFormatString* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 56), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_set_text_format(envoy_config_core_v3_SubstitutionFormatString *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_set_json_format(envoy_config_core_v3_SubstitutionFormatString *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, 32, UPB_SIZE(-21, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_core_v3_SubstitutionFormatString_mutable_json_format(envoy_config_core_v3_SubstitutionFormatString* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_core_v3_SubstitutionFormatString_json_format(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_core_v3_SubstitutionFormatString_set_json_format(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_set_omit_empty_values(envoy_config_core_v3_SubstitutionFormatString *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_set_content_type(envoy_config_core_v3_SubstitutionFormatString *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_set_text_format_source(envoy_config_core_v3_SubstitutionFormatString *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {5, 32, UPB_SIZE(-21, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_core_v3_SubstitutionFormatString_mutable_text_format_source(envoy_config_core_v3_SubstitutionFormatString* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_core_v3_SubstitutionFormatString_text_format_source(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_core_v3_SubstitutionFormatString_set_text_format_source(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_core_v3_SubstitutionFormatString_mutable_formatters(envoy_config_core_v3_SubstitutionFormatString* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_core_v3_SubstitutionFormatString_resize_formatters(envoy_config_core_v3_SubstitutionFormatString* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_core_v3_SubstitutionFormatString_add_formatters(envoy_config_core_v3_SubstitutionFormatString* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_SubstitutionFormatString_set_json_format_options(envoy_config_core_v3_SubstitutionFormatString *msg, envoy_config_core_v3_JsonFormatOptions* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 56), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__JsonFormatOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_JsonFormatOptions* envoy_config_core_v3_SubstitutionFormatString_mutable_json_format_options(envoy_config_core_v3_SubstitutionFormatString* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_JsonFormatOptions* sub = (struct envoy_config_core_v3_JsonFormatOptions*)envoy_config_core_v3_SubstitutionFormatString_json_format_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_JsonFormatOptions*)_upb_Message_New(&envoy__config__core__v3__JsonFormatOptions_msg_init, arena);
    if (sub) envoy_config_core_v3_SubstitutionFormatString_set_json_format_options(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
