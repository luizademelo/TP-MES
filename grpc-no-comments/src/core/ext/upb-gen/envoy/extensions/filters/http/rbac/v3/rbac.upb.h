
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_RBAC_V3_RBAC_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_RBAC_V3_RBAC_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/filters/http/rbac/v3/rbac.upb_minitable.h"

#include "envoy/config/rbac/v3/rbac.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_filters_http_rbac_v3_RBAC { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_rbac_v3_RBAC;
typedef struct envoy_extensions_filters_http_rbac_v3_RBACPerRoute { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_rbac_v3_RBACPerRoute;
struct envoy_config_rbac_v3_RBAC;
struct xds_type_matcher_v3_Matcher;

UPB_INLINE envoy_extensions_filters_http_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_rbac_v3_RBAC*)_upb_Message_New(&envoy__extensions__filters__http__rbac__v3__RBAC_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_rbac_v3_RBAC* ret = envoy_extensions_filters_http_rbac_v3_RBAC_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_rbac_v3_RBAC* ret = envoy_extensions_filters_http_rbac_v3_RBAC_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_rbac_v3_RBAC_serialize(const envoy_extensions_filters_http_rbac_v3_RBAC* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_rbac_v3_RBAC_serialize_ex(const envoy_extensions_filters_http_rbac_v3_RBAC* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__rbac__v3__RBAC_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_rules(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_rules(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const struct envoy_config_rbac_v3_RBAC* default_val = NULL;
  const struct envoy_config_rbac_v3_RBAC* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_rbac_v3_RBAC_has_rules(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_shadow_rules(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_shadow_rules(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const struct envoy_config_rbac_v3_RBAC* default_val = NULL;
  const struct envoy_config_rbac_v3_RBAC* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_rbac_v3_RBAC_has_shadow_rules(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_shadow_rules_stat_prefix(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_rbac_v3_RBAC_shadow_rules_stat_prefix(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_matcher(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher* envoy_extensions_filters_http_rbac_v3_RBAC_matcher(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const struct xds_type_matcher_v3_Matcher* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_rbac_v3_RBAC_has_matcher(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_shadow_matcher(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher* envoy_extensions_filters_http_rbac_v3_RBAC_shadow_matcher(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const struct xds_type_matcher_v3_Matcher* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_rbac_v3_RBAC_has_shadow_matcher(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_rules_stat_prefix(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_rbac_v3_RBAC_rules_stat_prefix(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_clear_track_per_rule_stats(envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_http_rbac_v3_RBAC_track_per_rule_stats(const envoy_extensions_filters_http_rbac_v3_RBAC* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_rules(envoy_extensions_filters_http_rbac_v3_RBAC *msg, struct envoy_config_rbac_v3_RBAC* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_mutable_rules(envoy_extensions_filters_http_rbac_v3_RBAC* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_RBAC* sub = (struct envoy_config_rbac_v3_RBAC*)envoy_extensions_filters_http_rbac_v3_RBAC_rules(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_RBAC*)_upb_Message_New(&envoy__config__rbac__v3__RBAC_msg_init, arena);
    if (sub) envoy_extensions_filters_http_rbac_v3_RBAC_set_rules(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_shadow_rules(envoy_extensions_filters_http_rbac_v3_RBAC *msg, struct envoy_config_rbac_v3_RBAC* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBAC_mutable_shadow_rules(envoy_extensions_filters_http_rbac_v3_RBAC* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_RBAC* sub = (struct envoy_config_rbac_v3_RBAC*)envoy_extensions_filters_http_rbac_v3_RBAC_shadow_rules(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_RBAC*)_upb_Message_New(&envoy__config__rbac__v3__RBAC_msg_init, arena);
    if (sub) envoy_extensions_filters_http_rbac_v3_RBAC_set_shadow_rules(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_shadow_rules_stat_prefix(envoy_extensions_filters_http_rbac_v3_RBAC *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_matcher(envoy_extensions_filters_http_rbac_v3_RBAC *msg, struct xds_type_matcher_v3_Matcher* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher* envoy_extensions_filters_http_rbac_v3_RBAC_mutable_matcher(envoy_extensions_filters_http_rbac_v3_RBAC* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher* sub = (struct xds_type_matcher_v3_Matcher*)envoy_extensions_filters_http_rbac_v3_RBAC_matcher(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher*)_upb_Message_New(&xds__type__matcher__v3__Matcher_msg_init, arena);
    if (sub) envoy_extensions_filters_http_rbac_v3_RBAC_set_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_shadow_matcher(envoy_extensions_filters_http_rbac_v3_RBAC *msg, struct xds_type_matcher_v3_Matcher* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher* envoy_extensions_filters_http_rbac_v3_RBAC_mutable_shadow_matcher(envoy_extensions_filters_http_rbac_v3_RBAC* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher* sub = (struct xds_type_matcher_v3_Matcher*)envoy_extensions_filters_http_rbac_v3_RBAC_shadow_matcher(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher*)_upb_Message_New(&xds__type__matcher__v3__Matcher_msg_init, arena);
    if (sub) envoy_extensions_filters_http_rbac_v3_RBAC_set_shadow_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_rules_stat_prefix(envoy_extensions_filters_http_rbac_v3_RBAC *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBAC_set_track_per_rule_stats(envoy_extensions_filters_http_rbac_v3_RBAC *msg, bool value) {
  const upb_MiniTableField field = {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_http_rbac_v3_RBACPerRoute* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_rbac_v3_RBACPerRoute*)_upb_Message_New(&envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_rbac_v3_RBACPerRoute* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_rbac_v3_RBACPerRoute* ret = envoy_extensions_filters_http_rbac_v3_RBACPerRoute_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_rbac_v3_RBACPerRoute* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_rbac_v3_RBACPerRoute* ret = envoy_extensions_filters_http_rbac_v3_RBACPerRoute_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_serialize(const envoy_extensions_filters_http_rbac_v3_RBACPerRoute* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_serialize_ex(const envoy_extensions_filters_http_rbac_v3_RBACPerRoute* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__rbac__v3__RBACPerRoute_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBACPerRoute_clear_rbac(envoy_extensions_filters_http_rbac_v3_RBACPerRoute* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_http_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_rbac(const envoy_extensions_filters_http_rbac_v3_RBACPerRoute* msg) {
  const envoy_extensions_filters_http_rbac_v3_RBAC* default_val = NULL;
  const envoy_extensions_filters_http_rbac_v3_RBAC* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__rbac__v3__RBAC_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_rbac_v3_RBACPerRoute_has_rbac(const envoy_extensions_filters_http_rbac_v3_RBACPerRoute* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_http_rbac_v3_RBACPerRoute_set_rbac(envoy_extensions_filters_http_rbac_v3_RBACPerRoute *msg, envoy_extensions_filters_http_rbac_v3_RBAC* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__rbac__v3__RBAC_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_http_rbac_v3_RBAC* envoy_extensions_filters_http_rbac_v3_RBACPerRoute_mutable_rbac(envoy_extensions_filters_http_rbac_v3_RBACPerRoute* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_http_rbac_v3_RBAC* sub = (struct envoy_extensions_filters_http_rbac_v3_RBAC*)envoy_extensions_filters_http_rbac_v3_RBACPerRoute_rbac(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_http_rbac_v3_RBAC*)_upb_Message_New(&envoy__extensions__filters__http__rbac__v3__RBAC_msg_init, arena);
    if (sub) envoy_extensions_filters_http_rbac_v3_RBACPerRoute_set_rbac(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
