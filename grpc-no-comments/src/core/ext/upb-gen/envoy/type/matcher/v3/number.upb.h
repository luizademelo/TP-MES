
#ifndef ENVOY_TYPE_MATCHER_V3_NUMBER_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_MATCHER_V3_NUMBER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/matcher/v3/number.upb_minitable.h"

#include "envoy/type/v3/range.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_matcher_v3_DoubleMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_DoubleMatcher;
struct envoy_type_v3_DoubleRange;

UPB_INLINE envoy_type_matcher_v3_DoubleMatcher* envoy_type_matcher_v3_DoubleMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_DoubleMatcher*)_upb_Message_New(&envoy__type__matcher__v3__DoubleMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_DoubleMatcher* envoy_type_matcher_v3_DoubleMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_DoubleMatcher* ret = envoy_type_matcher_v3_DoubleMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__DoubleMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_DoubleMatcher* envoy_type_matcher_v3_DoubleMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_DoubleMatcher* ret = envoy_type_matcher_v3_DoubleMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__DoubleMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_DoubleMatcher_serialize(const envoy_type_matcher_v3_DoubleMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__DoubleMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_DoubleMatcher_serialize_ex(const envoy_type_matcher_v3_DoubleMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__DoubleMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_matcher_v3_DoubleMatcher_match_pattern_range = 1,
  envoy_type_matcher_v3_DoubleMatcher_match_pattern_exact = 2,
  envoy_type_matcher_v3_DoubleMatcher_match_pattern_NOT_SET = 0
} envoy_type_matcher_v3_DoubleMatcher_match_pattern_oneofcases;
UPB_INLINE envoy_type_matcher_v3_DoubleMatcher_match_pattern_oneofcases envoy_type_matcher_v3_DoubleMatcher_match_pattern_case(const envoy_type_matcher_v3_DoubleMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_DoubleMatcher_match_pattern_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_DoubleMatcher_clear_match_pattern(envoy_type_matcher_v3_DoubleMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__matcher__v3__DoubleMatcher_msg_init, &field);
}
UPB_INLINE void envoy_type_matcher_v3_DoubleMatcher_clear_range(envoy_type_matcher_v3_DoubleMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_DoubleRange* envoy_type_matcher_v3_DoubleMatcher_range(const envoy_type_matcher_v3_DoubleMatcher* msg) {
  const struct envoy_type_v3_DoubleRange* default_val = NULL;
  const struct envoy_type_v3_DoubleRange* ret;
  const upb_MiniTableField field = {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__DoubleRange_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_DoubleMatcher_has_range(const envoy_type_matcher_v3_DoubleMatcher* msg) {
  const upb_MiniTableField field = {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_DoubleMatcher_clear_exact(envoy_type_matcher_v3_DoubleMatcher* msg) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_type_matcher_v3_DoubleMatcher_exact(const envoy_type_matcher_v3_DoubleMatcher* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_DoubleMatcher_has_exact(const envoy_type_matcher_v3_DoubleMatcher* msg) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_matcher_v3_DoubleMatcher_set_range(envoy_type_matcher_v3_DoubleMatcher *msg, struct envoy_type_v3_DoubleRange* value) {
  const upb_MiniTableField field = {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__DoubleRange_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_DoubleRange* envoy_type_matcher_v3_DoubleMatcher_mutable_range(envoy_type_matcher_v3_DoubleMatcher* msg, upb_Arena* arena) {
  struct envoy_type_v3_DoubleRange* sub = (struct envoy_type_v3_DoubleRange*)envoy_type_matcher_v3_DoubleMatcher_range(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_DoubleRange*)_upb_Message_New(&envoy__type__v3__DoubleRange_msg_init, arena);
    if (sub) envoy_type_matcher_v3_DoubleMatcher_set_range(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_DoubleMatcher_set_exact(envoy_type_matcher_v3_DoubleMatcher *msg, double value) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
