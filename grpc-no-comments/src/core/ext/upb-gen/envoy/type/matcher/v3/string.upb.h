
#ifndef ENVOY_TYPE_MATCHER_V3_STRING_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_MATCHER_V3_STRING_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/matcher/v3/string.upb_minitable.h"

#include "envoy/type/matcher/v3/regex.upb_minitable.h"
#include "xds/core/v3/extension.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_matcher_v3_StringMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_StringMatcher;
typedef struct envoy_type_matcher_v3_ListStringMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_ListStringMatcher;
struct envoy_type_matcher_v3_RegexMatcher;
struct xds_core_v3_TypedExtensionConfig;

UPB_INLINE envoy_type_matcher_v3_StringMatcher* envoy_type_matcher_v3_StringMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_StringMatcher* envoy_type_matcher_v3_StringMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_StringMatcher* ret = envoy_type_matcher_v3_StringMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__StringMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_StringMatcher* envoy_type_matcher_v3_StringMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_StringMatcher* ret = envoy_type_matcher_v3_StringMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__StringMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_StringMatcher_serialize(const envoy_type_matcher_v3_StringMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__StringMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_StringMatcher_serialize_ex(const envoy_type_matcher_v3_StringMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__StringMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_matcher_v3_StringMatcher_match_pattern_exact = 1,
  envoy_type_matcher_v3_StringMatcher_match_pattern_prefix = 2,
  envoy_type_matcher_v3_StringMatcher_match_pattern_suffix = 3,
  envoy_type_matcher_v3_StringMatcher_match_pattern_safe_regex = 5,
  envoy_type_matcher_v3_StringMatcher_match_pattern_contains = 7,
  envoy_type_matcher_v3_StringMatcher_match_pattern_custom = 8,
  envoy_type_matcher_v3_StringMatcher_match_pattern_NOT_SET = 0
} envoy_type_matcher_v3_StringMatcher_match_pattern_oneofcases;
UPB_INLINE envoy_type_matcher_v3_StringMatcher_match_pattern_oneofcases envoy_type_matcher_v3_StringMatcher_match_pattern_case(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_StringMatcher_match_pattern_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_match_pattern(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__matcher__v3__StringMatcher_msg_init, &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_exact(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_StringMatcher_exact(const envoy_type_matcher_v3_StringMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_has_exact(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_prefix(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {2, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_StringMatcher_prefix(const envoy_type_matcher_v3_StringMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_has_prefix(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {2, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_suffix(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {3, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_StringMatcher_suffix(const envoy_type_matcher_v3_StringMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_has_suffix(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {3, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_safe_regex(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {5, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatcher* envoy_type_matcher_v3_StringMatcher_safe_regex(const envoy_type_matcher_v3_StringMatcher* msg) {
  const struct envoy_type_matcher_v3_RegexMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatcher* ret;
  const upb_MiniTableField field = {5, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_has_safe_regex(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {5, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_ignore_case(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_ignore_case(const envoy_type_matcher_v3_StringMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_contains(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {7, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_StringMatcher_contains(const envoy_type_matcher_v3_StringMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_has_contains(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {7, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_clear_custom(envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {8, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_core_v3_TypedExtensionConfig* envoy_type_matcher_v3_StringMatcher_custom(const envoy_type_matcher_v3_StringMatcher* msg) {
  const struct xds_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct xds_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {8, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StringMatcher_has_custom(const envoy_type_matcher_v3_StringMatcher* msg) {
  const upb_MiniTableField field = {8, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_exact(envoy_type_matcher_v3_StringMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_prefix(envoy_type_matcher_v3_StringMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_suffix(envoy_type_matcher_v3_StringMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_safe_regex(envoy_type_matcher_v3_StringMatcher *msg, struct envoy_type_matcher_v3_RegexMatcher* value) {
  const upb_MiniTableField field = {5, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatcher* envoy_type_matcher_v3_StringMatcher_mutable_safe_regex(envoy_type_matcher_v3_StringMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatcher* sub = (struct envoy_type_matcher_v3_RegexMatcher*)envoy_type_matcher_v3_StringMatcher_safe_regex(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatcher*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_StringMatcher_set_safe_regex(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_ignore_case(envoy_type_matcher_v3_StringMatcher *msg, bool value) {
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_contains(envoy_type_matcher_v3_StringMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_StringMatcher_set_custom(envoy_type_matcher_v3_StringMatcher *msg, struct xds_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {8, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_TypedExtensionConfig* envoy_type_matcher_v3_StringMatcher_mutable_custom(envoy_type_matcher_v3_StringMatcher* msg, upb_Arena* arena) {
  struct xds_core_v3_TypedExtensionConfig* sub = (struct xds_core_v3_TypedExtensionConfig*)envoy_type_matcher_v3_StringMatcher_custom(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_TypedExtensionConfig*)_upb_Message_New(&xds__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_type_matcher_v3_StringMatcher_set_custom(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_matcher_v3_ListStringMatcher* envoy_type_matcher_v3_ListStringMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_ListStringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ListStringMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_ListStringMatcher* envoy_type_matcher_v3_ListStringMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_ListStringMatcher* ret = envoy_type_matcher_v3_ListStringMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ListStringMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_ListStringMatcher* envoy_type_matcher_v3_ListStringMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_ListStringMatcher* ret = envoy_type_matcher_v3_ListStringMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ListStringMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_ListStringMatcher_serialize(const envoy_type_matcher_v3_ListStringMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ListStringMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_ListStringMatcher_serialize_ex(const envoy_type_matcher_v3_ListStringMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ListStringMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_ListStringMatcher_clear_patterns(envoy_type_matcher_v3_ListStringMatcher* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_StringMatcher* const* envoy_type_matcher_v3_ListStringMatcher_patterns(const envoy_type_matcher_v3_ListStringMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_type_matcher_v3_StringMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_type_matcher_v3_ListStringMatcher_patterns_upb_array(const envoy_type_matcher_v3_ListStringMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_type_matcher_v3_ListStringMatcher_patterns_mutable_upb_array(envoy_type_matcher_v3_ListStringMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_type_matcher_v3_StringMatcher** envoy_type_matcher_v3_ListStringMatcher_mutable_patterns(envoy_type_matcher_v3_ListStringMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_type_matcher_v3_StringMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_type_matcher_v3_StringMatcher** envoy_type_matcher_v3_ListStringMatcher_resize_patterns(envoy_type_matcher_v3_ListStringMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_StringMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_type_matcher_v3_ListStringMatcher_add_patterns(envoy_type_matcher_v3_ListStringMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
