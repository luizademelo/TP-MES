
#ifndef ENVOY_TYPE_MATCHER_V3_VALUE_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_MATCHER_V3_VALUE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/matcher/v3/value.upb_minitable.h"

#include "envoy/type/matcher/v3/number.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_matcher_v3_ValueMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_ValueMatcher;
typedef struct envoy_type_matcher_v3_ValueMatcher_NullMatch { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_ValueMatcher_NullMatch;
typedef struct envoy_type_matcher_v3_ListMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_ListMatcher;
typedef struct envoy_type_matcher_v3_OrMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_OrMatcher;
struct envoy_type_matcher_v3_DoubleMatcher;
struct envoy_type_matcher_v3_StringMatcher;

UPB_INLINE envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_ValueMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_ValueMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ValueMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_ValueMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_ValueMatcher* ret = envoy_type_matcher_v3_ValueMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ValueMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_ValueMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_ValueMatcher* ret = envoy_type_matcher_v3_ValueMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ValueMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_ValueMatcher_serialize(const envoy_type_matcher_v3_ValueMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ValueMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_ValueMatcher_serialize_ex(const envoy_type_matcher_v3_ValueMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ValueMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_matcher_v3_ValueMatcher_match_pattern_null_match = 1,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_double_match = 2,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_string_match = 3,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_bool_match = 4,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_present_match = 5,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_list_match = 6,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_or_match = 7,
  envoy_type_matcher_v3_ValueMatcher_match_pattern_NOT_SET = 0
} envoy_type_matcher_v3_ValueMatcher_match_pattern_oneofcases;
UPB_INLINE envoy_type_matcher_v3_ValueMatcher_match_pattern_oneofcases envoy_type_matcher_v3_ValueMatcher_match_pattern_case(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_ValueMatcher_match_pattern_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_match_pattern(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__matcher__v3__ValueMatcher_msg_init, &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_null_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_ValueMatcher_NullMatch* envoy_type_matcher_v3_ValueMatcher_null_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const envoy_type_matcher_v3_ValueMatcher_NullMatch* default_val = NULL;
  const envoy_type_matcher_v3_ValueMatcher_NullMatch* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_null_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_double_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_DoubleMatcher* envoy_type_matcher_v3_ValueMatcher_double_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const struct envoy_type_matcher_v3_DoubleMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_DoubleMatcher* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__DoubleMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_double_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_string_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_type_matcher_v3_ValueMatcher_string_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_string_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_bool_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_bool_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_bool_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_present_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_present_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_present_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_list_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_ListMatcher* envoy_type_matcher_v3_ValueMatcher_list_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const envoy_type_matcher_v3_ListMatcher* default_val = NULL;
  const envoy_type_matcher_v3_ListMatcher* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ListMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_list_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_clear_or_match(envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_OrMatcher* envoy_type_matcher_v3_ValueMatcher_or_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const envoy_type_matcher_v3_OrMatcher* default_val = NULL;
  const envoy_type_matcher_v3_OrMatcher* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__OrMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ValueMatcher_has_or_match(const envoy_type_matcher_v3_ValueMatcher* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_null_match(envoy_type_matcher_v3_ValueMatcher *msg, envoy_type_matcher_v3_ValueMatcher_NullMatch* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_ValueMatcher_NullMatch* envoy_type_matcher_v3_ValueMatcher_mutable_null_match(envoy_type_matcher_v3_ValueMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_ValueMatcher_NullMatch* sub = (struct envoy_type_matcher_v3_ValueMatcher_NullMatch*)envoy_type_matcher_v3_ValueMatcher_null_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_ValueMatcher_NullMatch*)_upb_Message_New(&envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init, arena);
    if (sub) envoy_type_matcher_v3_ValueMatcher_set_null_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_double_match(envoy_type_matcher_v3_ValueMatcher *msg, struct envoy_type_matcher_v3_DoubleMatcher* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__DoubleMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_DoubleMatcher* envoy_type_matcher_v3_ValueMatcher_mutable_double_match(envoy_type_matcher_v3_ValueMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_DoubleMatcher* sub = (struct envoy_type_matcher_v3_DoubleMatcher*)envoy_type_matcher_v3_ValueMatcher_double_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_DoubleMatcher*)_upb_Message_New(&envoy__type__matcher__v3__DoubleMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_ValueMatcher_set_double_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_string_match(envoy_type_matcher_v3_ValueMatcher *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_type_matcher_v3_ValueMatcher_mutable_string_match(envoy_type_matcher_v3_ValueMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_type_matcher_v3_ValueMatcher_string_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_ValueMatcher_set_string_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_bool_match(envoy_type_matcher_v3_ValueMatcher *msg, bool value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_present_match(envoy_type_matcher_v3_ValueMatcher *msg, bool value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_list_match(envoy_type_matcher_v3_ValueMatcher *msg, envoy_type_matcher_v3_ListMatcher* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ListMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_ListMatcher* envoy_type_matcher_v3_ValueMatcher_mutable_list_match(envoy_type_matcher_v3_ValueMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_ListMatcher* sub = (struct envoy_type_matcher_v3_ListMatcher*)envoy_type_matcher_v3_ValueMatcher_list_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_ListMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ListMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_ValueMatcher_set_list_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_ValueMatcher_set_or_match(envoy_type_matcher_v3_ValueMatcher *msg, envoy_type_matcher_v3_OrMatcher* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__OrMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_OrMatcher* envoy_type_matcher_v3_ValueMatcher_mutable_or_match(envoy_type_matcher_v3_ValueMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_OrMatcher* sub = (struct envoy_type_matcher_v3_OrMatcher*)envoy_type_matcher_v3_ValueMatcher_or_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_OrMatcher*)_upb_Message_New(&envoy__type__matcher__v3__OrMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_ValueMatcher_set_or_match(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_matcher_v3_ValueMatcher_NullMatch* envoy_type_matcher_v3_ValueMatcher_NullMatch_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_ValueMatcher_NullMatch*)_upb_Message_New(&envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_ValueMatcher_NullMatch* envoy_type_matcher_v3_ValueMatcher_NullMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_ValueMatcher_NullMatch* ret = envoy_type_matcher_v3_ValueMatcher_NullMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_ValueMatcher_NullMatch* envoy_type_matcher_v3_ValueMatcher_NullMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_ValueMatcher_NullMatch* ret = envoy_type_matcher_v3_ValueMatcher_NullMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_ValueMatcher_NullMatch_serialize(const envoy_type_matcher_v3_ValueMatcher_NullMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_ValueMatcher_NullMatch_serialize_ex(const envoy_type_matcher_v3_ValueMatcher_NullMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_type_matcher_v3_ListMatcher* envoy_type_matcher_v3_ListMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_ListMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ListMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_ListMatcher* envoy_type_matcher_v3_ListMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_ListMatcher* ret = envoy_type_matcher_v3_ListMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ListMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_ListMatcher* envoy_type_matcher_v3_ListMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_ListMatcher* ret = envoy_type_matcher_v3_ListMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__ListMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_ListMatcher_serialize(const envoy_type_matcher_v3_ListMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ListMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_ListMatcher_serialize_ex(const envoy_type_matcher_v3_ListMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__ListMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_matcher_v3_ListMatcher_match_pattern_one_of = 1,
  envoy_type_matcher_v3_ListMatcher_match_pattern_NOT_SET = 0
} envoy_type_matcher_v3_ListMatcher_match_pattern_oneofcases;
UPB_INLINE envoy_type_matcher_v3_ListMatcher_match_pattern_oneofcases envoy_type_matcher_v3_ListMatcher_match_pattern_case(const envoy_type_matcher_v3_ListMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_ListMatcher_match_pattern_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_ListMatcher_clear_match_pattern(envoy_type_matcher_v3_ListMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__matcher__v3__ListMatcher_msg_init, &field);
}
UPB_INLINE void envoy_type_matcher_v3_ListMatcher_clear_one_of(envoy_type_matcher_v3_ListMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_ListMatcher_one_of(const envoy_type_matcher_v3_ListMatcher* msg) {
  const envoy_type_matcher_v3_ValueMatcher* default_val = NULL;
  const envoy_type_matcher_v3_ValueMatcher* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_ListMatcher_has_one_of(const envoy_type_matcher_v3_ListMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_matcher_v3_ListMatcher_set_one_of(envoy_type_matcher_v3_ListMatcher *msg, envoy_type_matcher_v3_ValueMatcher* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_ListMatcher_mutable_one_of(envoy_type_matcher_v3_ListMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_ValueMatcher* sub = (struct envoy_type_matcher_v3_ValueMatcher*)envoy_type_matcher_v3_ListMatcher_one_of(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_ValueMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ValueMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_ListMatcher_set_one_of(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_matcher_v3_OrMatcher* envoy_type_matcher_v3_OrMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_OrMatcher*)_upb_Message_New(&envoy__type__matcher__v3__OrMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_OrMatcher* envoy_type_matcher_v3_OrMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_OrMatcher* ret = envoy_type_matcher_v3_OrMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__OrMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_OrMatcher* envoy_type_matcher_v3_OrMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_OrMatcher* ret = envoy_type_matcher_v3_OrMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__OrMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_OrMatcher_serialize(const envoy_type_matcher_v3_OrMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__OrMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_OrMatcher_serialize_ex(const envoy_type_matcher_v3_OrMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__OrMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_OrMatcher_clear_value_matchers(envoy_type_matcher_v3_OrMatcher* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_ValueMatcher* const* envoy_type_matcher_v3_OrMatcher_value_matchers(const envoy_type_matcher_v3_OrMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_type_matcher_v3_ValueMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_type_matcher_v3_OrMatcher_value_matchers_upb_array(const envoy_type_matcher_v3_OrMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_type_matcher_v3_OrMatcher_value_matchers_mutable_upb_array(envoy_type_matcher_v3_OrMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_type_matcher_v3_ValueMatcher** envoy_type_matcher_v3_OrMatcher_mutable_value_matchers(envoy_type_matcher_v3_OrMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_type_matcher_v3_ValueMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_type_matcher_v3_ValueMatcher** envoy_type_matcher_v3_OrMatcher_resize_value_matchers(envoy_type_matcher_v3_OrMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_ValueMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_OrMatcher_add_value_matchers(envoy_type_matcher_v3_OrMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_matcher_v3_ValueMatcher* sub = (struct envoy_type_matcher_v3_ValueMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ValueMatcher_msg_init, arena);
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
