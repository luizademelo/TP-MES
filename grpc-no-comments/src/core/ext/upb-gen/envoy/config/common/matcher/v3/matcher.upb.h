
#ifndef ENVOY_CONFIG_COMMON_MATCHER_V3_MATCHER_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_COMMON_MATCHER_V3_MATCHER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/common/matcher/v3/matcher.upb_minitable.h"

#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_common_matcher_v3_Matcher { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher;
typedef struct envoy_config_common_matcher_v3_Matcher_OnMatch { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_OnMatch;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherList { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherList;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherTree { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherTree;
typedef struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap;
typedef struct envoy_config_common_matcher_v3_MatchPredicate { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_MatchPredicate;
typedef struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_MatchPredicate_MatchSet;
typedef struct envoy_config_common_matcher_v3_HttpHeadersMatch { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_HttpHeadersMatch;
typedef struct envoy_config_common_matcher_v3_HttpGenericBodyMatch { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_HttpGenericBodyMatch;
typedef struct envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch { upb_Message UPB_PRIVATE(base); } envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_route_v3_HeaderMatcher;
struct envoy_type_matcher_v3_StringMatcher;

UPB_INLINE envoy_config_common_matcher_v3_Matcher* envoy_config_common_matcher_v3_Matcher_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher* envoy_config_common_matcher_v3_Matcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher* ret = envoy_config_common_matcher_v3_Matcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher* envoy_config_common_matcher_v3_Matcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher* ret = envoy_config_common_matcher_v3_Matcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_serialize(const envoy_config_common_matcher_v3_Matcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_serialize_ex(const envoy_config_common_matcher_v3_Matcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_Matcher_matcher_type_matcher_list = 1,
  envoy_config_common_matcher_v3_Matcher_matcher_type_matcher_tree = 2,
  envoy_config_common_matcher_v3_Matcher_matcher_type_NOT_SET = 0
} envoy_config_common_matcher_v3_Matcher_matcher_type_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_Matcher_matcher_type_oneofcases envoy_config_common_matcher_v3_Matcher_matcher_type_case(const envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_matcher_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_clear_matcher_type(envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_clear_matcher_list(envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList* envoy_config_common_matcher_v3_Matcher_matcher_list(const envoy_config_common_matcher_v3_Matcher* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherList* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherList* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_has_matcher_list(const envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_clear_matcher_tree(envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherTree* envoy_config_common_matcher_v3_Matcher_matcher_tree(const envoy_config_common_matcher_v3_Matcher* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherTree* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherTree* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_has_matcher_tree(const envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_clear_on_no_match(envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_on_no_match(const envoy_config_common_matcher_v3_Matcher* msg) {
  const envoy_config_common_matcher_v3_Matcher_OnMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_OnMatch* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_has_on_no_match(const envoy_config_common_matcher_v3_Matcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_set_matcher_list(envoy_config_common_matcher_v3_Matcher *msg, envoy_config_common_matcher_v3_Matcher_MatcherList* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList* envoy_config_common_matcher_v3_Matcher_mutable_matcher_list(envoy_config_common_matcher_v3_Matcher* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherList* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList*)envoy_config_common_matcher_v3_Matcher_matcher_list(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_set_matcher_list(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_set_matcher_tree(envoy_config_common_matcher_v3_Matcher *msg, envoy_config_common_matcher_v3_Matcher_MatcherTree* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherTree* envoy_config_common_matcher_v3_Matcher_mutable_matcher_tree(envoy_config_common_matcher_v3_Matcher* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherTree* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherTree*)envoy_config_common_matcher_v3_Matcher_matcher_tree(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherTree*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_set_matcher_tree(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_set_on_no_match(envoy_config_common_matcher_v3_Matcher *msg, envoy_config_common_matcher_v3_Matcher_OnMatch* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_mutable_on_no_match(envoy_config_common_matcher_v3_Matcher* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_OnMatch* sub = (struct envoy_config_common_matcher_v3_Matcher_OnMatch*)envoy_config_common_matcher_v3_Matcher_on_no_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_set_on_no_match(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_OnMatch_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_OnMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_OnMatch* ret = envoy_config_common_matcher_v3_Matcher_OnMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_OnMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_OnMatch* ret = envoy_config_common_matcher_v3_Matcher_OnMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_OnMatch_serialize(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_OnMatch_serialize_ex(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_matcher = 1,
  envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_action = 2,
  envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_NOT_SET = 0
} envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_oneofcases envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_case(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_OnMatch_on_match_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_OnMatch_clear_on_match(envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_OnMatch_clear_matcher(envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher* envoy_config_common_matcher_v3_Matcher_OnMatch_matcher(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const envoy_config_common_matcher_v3_Matcher* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_OnMatch_has_matcher(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_OnMatch_clear_action(envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_OnMatch_action(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_OnMatch_has_action(const envoy_config_common_matcher_v3_Matcher_OnMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_OnMatch_set_matcher(envoy_config_common_matcher_v3_Matcher_OnMatch *msg, envoy_config_common_matcher_v3_Matcher* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher* envoy_config_common_matcher_v3_Matcher_OnMatch_mutable_matcher(envoy_config_common_matcher_v3_Matcher_OnMatch* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher* sub = (struct envoy_config_common_matcher_v3_Matcher*)envoy_config_common_matcher_v3_Matcher_OnMatch_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_OnMatch_set_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_OnMatch_set_action(envoy_config_common_matcher_v3_Matcher_OnMatch *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_OnMatch_mutable_action(envoy_config_common_matcher_v3_Matcher_OnMatch* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_common_matcher_v3_Matcher_OnMatch_action(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_OnMatch_set_action(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList* envoy_config_common_matcher_v3_Matcher_MatcherList_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherList*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList* envoy_config_common_matcher_v3_Matcher_MatcherList_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList* envoy_config_common_matcher_v3_Matcher_MatcherList_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherList* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherList* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_clear_matchers(envoy_config_common_matcher_v3_Matcher_MatcherList* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* const* envoy_config_common_matcher_v3_Matcher_MatcherList_matchers(const envoy_config_common_matcher_v3_Matcher_MatcherList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_common_matcher_v3_Matcher_MatcherList_matchers_upb_array(const envoy_config_common_matcher_v3_Matcher_MatcherList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_common_matcher_v3_Matcher_MatcherList_matchers_mutable_upb_array(envoy_config_common_matcher_v3_Matcher_MatcherList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher** envoy_config_common_matcher_v3_Matcher_MatcherList_mutable_matchers(envoy_config_common_matcher_v3_Matcher_MatcherList* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher** envoy_config_common_matcher_v3_Matcher_MatcherList_resize_matchers(envoy_config_common_matcher_v3_Matcher_MatcherList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* envoy_config_common_matcher_v3_Matcher_MatcherList_add_matchers(envoy_config_common_matcher_v3_Matcher_MatcherList* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_single_predicate = 1,
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_or_matcher = 2,
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_and_matcher = 3,
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_not_matcher = 4,
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_NOT_SET = 0
} envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_oneofcases envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_case(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_match_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_clear_match_type(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_clear_single_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_single_predicate(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_has_single_predicate(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_clear_or_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_or_matcher(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_has_or_matcher(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_clear_and_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_and_matcher(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_has_and_matcher(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_clear_not_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_not_matcher(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_has_not_matcher(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_single_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate *msg, envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_mutable_single_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_single_predicate(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_single_predicate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_or_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate *msg, envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_mutable_or_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_or_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_or_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_and_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate *msg, envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_mutable_and_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_and_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_and_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_not_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate *msg, envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_mutable_not_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_not_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_set_not_matcher(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_value_match = 2,
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_custom_match = 3,
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_NOT_SET = 0
} envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_oneofcases envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_case(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_matcher_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_clear_matcher(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__SinglePredicate_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_clear_input(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_input(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_has_input(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_clear_value_match(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_value_match(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_has_value_match(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_clear_custom_match(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_custom_match(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_has_custom_match(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_set_input(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_mutable_input(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_input(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_set_input(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_set_value_match(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_mutable_value_match(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_value_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_set_value_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_set_custom_match(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_mutable_custom_match(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_custom_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_SinglePredicate_set_custom_match(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate__PredicateList_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_clear_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* const* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_predicate(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_predicate_upb_array(const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_predicate_mutable_upb_array(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate** envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_mutable_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate** envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_resize_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList_add_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate_PredicateList* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* ret = envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherList__FieldMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_clear_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_predicate(const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_has_predicate(const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_clear_on_match(envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_on_match(const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg) {
  const envoy_config_common_matcher_v3_Matcher_OnMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_OnMatch* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_has_on_match(const envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_set_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher *msg, envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_mutable_predicate(envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate*)envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_predicate(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherList_Predicate*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherList__Predicate_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_set_predicate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_set_on_match(envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher *msg, envoy_config_common_matcher_v3_Matcher_OnMatch* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_OnMatch* envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_mutable_on_match(envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_OnMatch* sub = (struct envoy_config_common_matcher_v3_Matcher_OnMatch*)envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_on_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherList_FieldMatcher_set_on_match(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree* envoy_config_common_matcher_v3_Matcher_MatcherTree_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherTree*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree* envoy_config_common_matcher_v3_Matcher_MatcherTree_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherTree* ret = envoy_config_common_matcher_v3_Matcher_MatcherTree_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree* envoy_config_common_matcher_v3_Matcher_MatcherTree_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherTree* ret = envoy_config_common_matcher_v3_Matcher_MatcherTree_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherTree_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherTree_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_exact_match_map = 2,
  envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_prefix_match_map = 3,
  envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_custom_match = 4,
  envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_NOT_SET = 0
} envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_oneofcases envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_case(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_Matcher_MatcherTree_tree_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_clear_tree_type(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherTree_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_clear_input(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherTree_input(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_has_input(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_clear_exact_match_map(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_exact_match_map(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_has_exact_match_map(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_clear_prefix_match_map(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_prefix_match_map(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* default_val = NULL;
  const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_has_prefix_match_map(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_clear_custom_match(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherTree_custom_match(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_has_custom_match(const envoy_config_common_matcher_v3_Matcher_MatcherTree* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_set_input(envoy_config_common_matcher_v3_Matcher_MatcherTree *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherTree_mutable_input(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_common_matcher_v3_Matcher_MatcherTree_input(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherTree_set_input(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_set_exact_match_map(envoy_config_common_matcher_v3_Matcher_MatcherTree *msg, envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_mutable_exact_match_map(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap*)envoy_config_common_matcher_v3_Matcher_MatcherTree_exact_match_map(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherTree_set_exact_match_map(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_set_prefix_match_map(envoy_config_common_matcher_v3_Matcher_MatcherTree *msg, envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_mutable_prefix_match_map(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap*)envoy_config_common_matcher_v3_Matcher_MatcherTree_prefix_match_map(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherTree_set_prefix_match_map(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_set_custom_match(envoy_config_common_matcher_v3_Matcher_MatcherTree *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_common_matcher_v3_Matcher_MatcherTree_mutable_custom_match(envoy_config_common_matcher_v3_Matcher_MatcherTree* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_common_matcher_v3_Matcher_MatcherTree_custom_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_Matcher_MatcherTree_set_custom_match(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap*)_upb_Message_New(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* ret = envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* ret = envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_serialize(const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_serialize_ex(const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_clear_map(envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_size(const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_get(const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, upb_StringView key, envoy_config_common_matcher_v3_Matcher_OnMatch** val) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap__MapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_next(const envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, upb_StringView* key, const envoy_config_common_matcher_v3_Matcher_OnMatch** val,
                           size_t* iter) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap__MapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_upb_map(envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap__MapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_mutable_upb_map(envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap__MapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(envoy_config_common_matcher_v3_Matcher_OnMatch*), a);
}

UPB_INLINE void envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_clear(envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_set(envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, upb_StringView key, envoy_config_common_matcher_v3_Matcher_OnMatch* val, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__MatcherTree__MatchMap__MapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap_map_delete(envoy_config_common_matcher_v3_Matcher_MatcherTree_MatchMap* msg, upb_StringView key) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate* envoy_config_common_matcher_v3_MatchPredicate_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_MatchPredicate*)_upb_Message_New(&envoy__config__common__matcher__v3__MatchPredicate_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate* envoy_config_common_matcher_v3_MatchPredicate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_MatchPredicate* ret = envoy_config_common_matcher_v3_MatchPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__MatchPredicate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate* envoy_config_common_matcher_v3_MatchPredicate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_MatchPredicate* ret = envoy_config_common_matcher_v3_MatchPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__MatchPredicate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_MatchPredicate_serialize(const envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__MatchPredicate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_MatchPredicate_serialize_ex(const envoy_config_common_matcher_v3_MatchPredicate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__MatchPredicate_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_MatchPredicate_rule_or_match = 1,
  envoy_config_common_matcher_v3_MatchPredicate_rule_and_match = 2,
  envoy_config_common_matcher_v3_MatchPredicate_rule_not_match = 3,
  envoy_config_common_matcher_v3_MatchPredicate_rule_any_match = 4,
  envoy_config_common_matcher_v3_MatchPredicate_rule_http_request_headers_match = 5,
  envoy_config_common_matcher_v3_MatchPredicate_rule_http_request_trailers_match = 6,
  envoy_config_common_matcher_v3_MatchPredicate_rule_http_response_headers_match = 7,
  envoy_config_common_matcher_v3_MatchPredicate_rule_http_response_trailers_match = 8,
  envoy_config_common_matcher_v3_MatchPredicate_rule_http_request_generic_body_match = 9,
  envoy_config_common_matcher_v3_MatchPredicate_rule_http_response_generic_body_match = 10,
  envoy_config_common_matcher_v3_MatchPredicate_rule_NOT_SET = 0
} envoy_config_common_matcher_v3_MatchPredicate_rule_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate_rule_oneofcases envoy_config_common_matcher_v3_MatchPredicate_rule_case(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_MatchPredicate_rule_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_rule(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__MatchPredicate_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_or_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_or_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* default_val = NULL;
  const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_or_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_and_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_and_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* default_val = NULL;
  const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_and_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_not_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_MatchPredicate* envoy_config_common_matcher_v3_MatchPredicate_not_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_MatchPredicate* default_val = NULL;
  const envoy_config_common_matcher_v3_MatchPredicate* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_not_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_any_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_any_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_any_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_http_request_headers_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_http_request_headers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_HttpHeadersMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_HttpHeadersMatch* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_http_request_headers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_http_request_trailers_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_http_request_trailers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_HttpHeadersMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_HttpHeadersMatch* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_http_request_trailers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_http_response_headers_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_http_response_headers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_HttpHeadersMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_HttpHeadersMatch* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_http_response_headers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_http_response_trailers_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_http_response_trailers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_HttpHeadersMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_HttpHeadersMatch* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_http_response_trailers_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_http_request_generic_body_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_MatchPredicate_http_request_generic_body_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_HttpGenericBodyMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_HttpGenericBodyMatch* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_http_request_generic_body_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_clear_http_response_generic_body_match(envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_MatchPredicate_http_response_generic_body_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const envoy_config_common_matcher_v3_HttpGenericBodyMatch* default_val = NULL;
  const envoy_config_common_matcher_v3_HttpGenericBodyMatch* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_MatchPredicate_has_http_response_generic_body_match(const envoy_config_common_matcher_v3_MatchPredicate* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_or_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_MatchPredicate_MatchSet* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_mutable_or_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet* sub = (struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet*)envoy_config_common_matcher_v3_MatchPredicate_or_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet*)_upb_Message_New(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_or_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_and_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_MatchPredicate_MatchSet* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_mutable_and_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet* sub = (struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet*)envoy_config_common_matcher_v3_MatchPredicate_and_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_MatchPredicate_MatchSet*)_upb_Message_New(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_and_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_not_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_MatchPredicate* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_MatchPredicate* envoy_config_common_matcher_v3_MatchPredicate_mutable_not_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_MatchPredicate* sub = (struct envoy_config_common_matcher_v3_MatchPredicate*)envoy_config_common_matcher_v3_MatchPredicate_not_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_MatchPredicate*)_upb_Message_New(&envoy__config__common__matcher__v3__MatchPredicate_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_not_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_any_match(envoy_config_common_matcher_v3_MatchPredicate *msg, bool value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_http_request_headers_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_HttpHeadersMatch* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_mutable_http_request_headers_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_HttpHeadersMatch* sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)envoy_config_common_matcher_v3_MatchPredicate_http_request_headers_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_http_request_headers_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_http_request_trailers_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_HttpHeadersMatch* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_mutable_http_request_trailers_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_HttpHeadersMatch* sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)envoy_config_common_matcher_v3_MatchPredicate_http_request_trailers_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_http_request_trailers_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_http_response_headers_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_HttpHeadersMatch* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_mutable_http_response_headers_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_HttpHeadersMatch* sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)envoy_config_common_matcher_v3_MatchPredicate_http_response_headers_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_http_response_headers_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_http_response_trailers_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_HttpHeadersMatch* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_MatchPredicate_mutable_http_response_trailers_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_HttpHeadersMatch* sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)envoy_config_common_matcher_v3_MatchPredicate_http_response_trailers_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_HttpHeadersMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_http_response_trailers_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_http_request_generic_body_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_HttpGenericBodyMatch* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_MatchPredicate_mutable_http_request_generic_body_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_HttpGenericBodyMatch* sub = (struct envoy_config_common_matcher_v3_HttpGenericBodyMatch*)envoy_config_common_matcher_v3_MatchPredicate_http_request_generic_body_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_HttpGenericBodyMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_http_request_generic_body_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_set_http_response_generic_body_match(envoy_config_common_matcher_v3_MatchPredicate *msg, envoy_config_common_matcher_v3_HttpGenericBodyMatch* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_MatchPredicate_mutable_http_response_generic_body_match(envoy_config_common_matcher_v3_MatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_common_matcher_v3_HttpGenericBodyMatch* sub = (struct envoy_config_common_matcher_v3_HttpGenericBodyMatch*)envoy_config_common_matcher_v3_MatchPredicate_http_response_generic_body_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_common_matcher_v3_HttpGenericBodyMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, arena);
    if (sub) envoy_config_common_matcher_v3_MatchPredicate_set_http_response_generic_body_match(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_MatchPredicate_MatchSet*)_upb_Message_New(&envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_MatchPredicate_MatchSet* ret = envoy_config_common_matcher_v3_MatchPredicate_MatchSet_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate_MatchSet* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_MatchPredicate_MatchSet* ret = envoy_config_common_matcher_v3_MatchPredicate_MatchSet_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_serialize(const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_serialize_ex(const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__MatchPredicate__MatchSet_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_MatchPredicate_MatchSet_clear_rules(envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_MatchPredicate* const* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_rules(const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_common_matcher_v3_MatchPredicate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_common_matcher_v3_MatchPredicate_MatchSet_rules_upb_array(const envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_common_matcher_v3_MatchPredicate_MatchSet_rules_mutable_upb_array(envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate** envoy_config_common_matcher_v3_MatchPredicate_MatchSet_mutable_rules(envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_common_matcher_v3_MatchPredicate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_common_matcher_v3_MatchPredicate** envoy_config_common_matcher_v3_MatchPredicate_MatchSet_resize_rules(envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_MatchPredicate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_common_matcher_v3_MatchPredicate* envoy_config_common_matcher_v3_MatchPredicate_MatchSet_add_rules(envoy_config_common_matcher_v3_MatchPredicate_MatchSet* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__MatchPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_common_matcher_v3_MatchPredicate* sub = (struct envoy_config_common_matcher_v3_MatchPredicate*)_upb_Message_New(&envoy__config__common__matcher__v3__MatchPredicate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_HttpHeadersMatch_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_HttpHeadersMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_HttpHeadersMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_HttpHeadersMatch* ret = envoy_config_common_matcher_v3_HttpHeadersMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_HttpHeadersMatch* envoy_config_common_matcher_v3_HttpHeadersMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_HttpHeadersMatch* ret = envoy_config_common_matcher_v3_HttpHeadersMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_HttpHeadersMatch_serialize(const envoy_config_common_matcher_v3_HttpHeadersMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_HttpHeadersMatch_serialize_ex(const envoy_config_common_matcher_v3_HttpHeadersMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpHeadersMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpHeadersMatch_clear_headers(envoy_config_common_matcher_v3_HttpHeadersMatch* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_HeaderMatcher* const* envoy_config_common_matcher_v3_HttpHeadersMatch_headers(const envoy_config_common_matcher_v3_HttpHeadersMatch* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_common_matcher_v3_HttpHeadersMatch_headers_upb_array(const envoy_config_common_matcher_v3_HttpHeadersMatch* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_common_matcher_v3_HttpHeadersMatch_headers_mutable_upb_array(envoy_config_common_matcher_v3_HttpHeadersMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct envoy_config_route_v3_HeaderMatcher** envoy_config_common_matcher_v3_HttpHeadersMatch_mutable_headers(envoy_config_common_matcher_v3_HttpHeadersMatch* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher** envoy_config_common_matcher_v3_HttpHeadersMatch_resize_headers(envoy_config_common_matcher_v3_HttpHeadersMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_common_matcher_v3_HttpHeadersMatch_add_headers(envoy_config_common_matcher_v3_HttpHeadersMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_HttpGenericBodyMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_HttpGenericBodyMatch* ret = envoy_config_common_matcher_v3_HttpGenericBodyMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_HttpGenericBodyMatch* ret = envoy_config_common_matcher_v3_HttpGenericBodyMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_HttpGenericBodyMatch_serialize(const envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_HttpGenericBodyMatch_serialize_ex(const envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpGenericBodyMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_clear_bytes_limit(envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_common_matcher_v3_HttpGenericBodyMatch_bytes_limit(const envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_clear_patterns(envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* const* envoy_config_common_matcher_v3_HttpGenericBodyMatch_patterns(const envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_common_matcher_v3_HttpGenericBodyMatch_patterns_upb_array(const envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_common_matcher_v3_HttpGenericBodyMatch_patterns_mutable_upb_array(envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_set_bytes_limit(envoy_config_common_matcher_v3_HttpGenericBodyMatch *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch** envoy_config_common_matcher_v3_HttpGenericBodyMatch_mutable_patterns(envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch** envoy_config_common_matcher_v3_HttpGenericBodyMatch_resize_patterns(envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_add_patterns(envoy_config_common_matcher_v3_HttpGenericBodyMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* sub = (struct envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_new(upb_Arena* arena) {
  return (envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch*)_upb_Message_New(&envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, arena);
}
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* ret = envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* ret = envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_serialize(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_serialize_ex(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_string_match = 1,
  envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_binary_match = 2,
  envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_NOT_SET = 0
} envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_oneofcases;
UPB_INLINE envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_oneofcases envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_case(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_rule_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_clear_rule(envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__common__matcher__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init, &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_clear_string_match(envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_string_match(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_has_string_match(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_clear_binary_match(envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_binary_match(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_has_binary_match(const envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_set_string_match(envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch_set_binary_match(envoy_config_common_matcher_v3_HttpGenericBodyMatch_GenericTextMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
