
#ifndef ENVOY_CONFIG_RBAC_V3_RBAC_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_RBAC_V3_RBAC_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/rbac/v3/rbac.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/type/matcher/v3/filter_state.upb_minitable.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"
#include "envoy/type/matcher/v3/path.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "google/api/expr/v1alpha1/checked.upb_minitable.h"
#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_rbac_v3_RBAC { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_RBAC;
typedef struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_RBAC_AuditLoggingOptions;
typedef struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig;
typedef struct envoy_config_rbac_v3_Policy { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Policy;
typedef struct envoy_config_rbac_v3_SourcedMetadata { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_SourcedMetadata;
typedef struct envoy_config_rbac_v3_Permission { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Permission;
typedef struct envoy_config_rbac_v3_Permission_Set { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Permission_Set;
typedef struct envoy_config_rbac_v3_Principal { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Principal;
typedef struct envoy_config_rbac_v3_Principal_Set { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Principal_Set;
typedef struct envoy_config_rbac_v3_Principal_Authenticated { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Principal_Authenticated;
typedef struct envoy_config_rbac_v3_Action { upb_Message UPB_PRIVATE(base); } envoy_config_rbac_v3_Action;
struct envoy_config_core_v3_CidrRange;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_route_v3_HeaderMatcher;
struct envoy_type_matcher_v3_FilterStateMatcher;
struct envoy_type_matcher_v3_MetadataMatcher;
struct envoy_type_matcher_v3_PathMatcher;
struct envoy_type_matcher_v3_StringMatcher;
struct envoy_type_v3_Int32Range;
struct google_api_expr_v1alpha1_CheckedExpr;
struct google_api_expr_v1alpha1_Expr;

typedef enum {
  envoy_config_rbac_v3_DYNAMIC = 0,
  envoy_config_rbac_v3_ROUTE = 1
} envoy_config_rbac_v3_MetadataSource;

typedef enum {
  envoy_config_rbac_v3_RBAC_ALLOW = 0,
  envoy_config_rbac_v3_RBAC_DENY = 1,
  envoy_config_rbac_v3_RBAC_LOG = 2
} envoy_config_rbac_v3_RBAC_Action;

typedef enum {
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions_NONE = 0,
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions_ON_DENY = 1,
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions_ON_ALLOW = 2,
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions_ON_DENY_AND_ALLOW = 3
} envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditCondition;

UPB_INLINE envoy_config_rbac_v3_RBAC* envoy_config_rbac_v3_RBAC_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_RBAC*)_upb_Message_New(&envoy__config__rbac__v3__RBAC_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_RBAC* envoy_config_rbac_v3_RBAC_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_RBAC* ret = envoy_config_rbac_v3_RBAC_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__RBAC_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_RBAC* envoy_config_rbac_v3_RBAC_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_RBAC* ret = envoy_config_rbac_v3_RBAC_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__RBAC_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_RBAC_serialize(const envoy_config_rbac_v3_RBAC* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__RBAC_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_RBAC_serialize_ex(const envoy_config_rbac_v3_RBAC* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__RBAC_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_clear_action(envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_rbac_v3_RBAC_action(const envoy_config_rbac_v3_RBAC* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_clear_policies(envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_rbac_v3_RBAC_policies_size(const envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_policies_get(const envoy_config_rbac_v3_RBAC* msg, upb_StringView key, envoy_config_rbac_v3_Policy** val) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Policy_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_policies_next(const envoy_config_rbac_v3_RBAC* msg, upb_StringView* key, const envoy_config_rbac_v3_Policy** val,
                           size_t* iter) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Policy_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_rbac_v3_RBAC_policies_upb_map(envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Policy_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_rbac_v3_RBAC_policies_mutable_upb_map(envoy_config_rbac_v3_RBAC* msg, upb_Arena* a) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Policy_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(envoy_config_rbac_v3_Policy*), a);
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_clear_audit_logging_options(envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* envoy_config_rbac_v3_RBAC_audit_logging_options(const envoy_config_rbac_v3_RBAC* msg) {
  const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* default_val = NULL;
  const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_has_audit_logging_options(const envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_rbac_v3_RBAC_set_action(envoy_config_rbac_v3_RBAC *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_policies_clear(envoy_config_rbac_v3_RBAC* msg) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_policies_set(envoy_config_rbac_v3_RBAC* msg, upb_StringView key, envoy_config_rbac_v3_Policy* val, upb_Arena* a) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Policy_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_policies_delete(envoy_config_rbac_v3_RBAC* msg, upb_StringView key) {
  const upb_MiniTableField field = {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_set_audit_logging_options(envoy_config_rbac_v3_RBAC *msg, envoy_config_rbac_v3_RBAC_AuditLoggingOptions* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions* envoy_config_rbac_v3_RBAC_mutable_audit_logging_options(envoy_config_rbac_v3_RBAC* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions* sub = (struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions*)envoy_config_rbac_v3_RBAC_audit_logging_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions*)_upb_Message_New(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init, arena);
    if (sub) envoy_config_rbac_v3_RBAC_set_audit_logging_options(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_RBAC_AuditLoggingOptions*)_upb_Message_New(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions* ret = envoy_config_rbac_v3_RBAC_AuditLoggingOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions* ret = envoy_config_rbac_v3_RBAC_AuditLoggingOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_serialize(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_serialize_ex(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_clear_audit_condition(envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_rbac_v3_RBAC_AuditLoggingOptions_audit_condition(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_clear_logger_configs(envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* const* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_logger_configs(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_rbac_v3_RBAC_AuditLoggingOptions_logger_configs_upb_array(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_rbac_v3_RBAC_AuditLoggingOptions_logger_configs_mutable_upb_array(envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_set_audit_condition(envoy_config_rbac_v3_RBAC_AuditLoggingOptions *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig** envoy_config_rbac_v3_RBAC_AuditLoggingOptions_mutable_logger_configs(envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig** envoy_config_rbac_v3_RBAC_AuditLoggingOptions_resize_logger_configs(envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_add_logger_configs(envoy_config_rbac_v3_RBAC_AuditLoggingOptions* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* sub = (struct envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig*)_upb_Message_New(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig*)_upb_Message_New(&envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* ret = envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* ret = envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_serialize(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_serialize_ex(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_clear_audit_logger(envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_audit_logger(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_has_audit_logger(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_clear_is_optional(envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_is_optional(const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_set_audit_logger(envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_mutable_audit_logger(envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_audit_logger(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_set_audit_logger(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_set_is_optional(envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_rbac_v3_Policy* envoy_config_rbac_v3_Policy_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Policy*)_upb_Message_New(&envoy__config__rbac__v3__Policy_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Policy* envoy_config_rbac_v3_Policy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Policy* ret = envoy_config_rbac_v3_Policy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Policy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Policy* envoy_config_rbac_v3_Policy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Policy* ret = envoy_config_rbac_v3_Policy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Policy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Policy_serialize(const envoy_config_rbac_v3_Policy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Policy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Policy_serialize_ex(const envoy_config_rbac_v3_Policy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Policy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_Policy_clear_permissions(envoy_config_rbac_v3_Policy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Permission* const* envoy_config_rbac_v3_Policy_permissions(const envoy_config_rbac_v3_Policy* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_rbac_v3_Permission* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_rbac_v3_Policy_permissions_upb_array(const envoy_config_rbac_v3_Policy* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_rbac_v3_Policy_permissions_mutable_upb_array(envoy_config_rbac_v3_Policy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_rbac_v3_Policy_clear_principals(envoy_config_rbac_v3_Policy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Principal* const* envoy_config_rbac_v3_Policy_principals(const envoy_config_rbac_v3_Policy* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_rbac_v3_Principal* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_rbac_v3_Policy_principals_upb_array(const envoy_config_rbac_v3_Policy* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_rbac_v3_Policy_principals_mutable_upb_array(envoy_config_rbac_v3_Policy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_rbac_v3_Policy_clear_condition(envoy_config_rbac_v3_Policy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_Expr* envoy_config_rbac_v3_Policy_condition(const envoy_config_rbac_v3_Policy* msg) {
  const struct google_api_expr_v1alpha1_Expr* default_val = NULL;
  const struct google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Policy_has_condition(const envoy_config_rbac_v3_Policy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Policy_clear_checked_condition(envoy_config_rbac_v3_Policy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_CheckedExpr* envoy_config_rbac_v3_Policy_checked_condition(const envoy_config_rbac_v3_Policy* msg) {
  const struct google_api_expr_v1alpha1_CheckedExpr* default_val = NULL;
  const struct google_api_expr_v1alpha1_CheckedExpr* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Policy_has_checked_condition(const envoy_config_rbac_v3_Policy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE envoy_config_rbac_v3_Permission** envoy_config_rbac_v3_Policy_mutable_permissions(envoy_config_rbac_v3_Policy* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_rbac_v3_Permission**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_rbac_v3_Permission** envoy_config_rbac_v3_Policy_resize_permissions(envoy_config_rbac_v3_Policy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_Permission**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Policy_add_permissions(envoy_config_rbac_v3_Policy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_rbac_v3_Permission* sub = (struct envoy_config_rbac_v3_Permission*)_upb_Message_New(&envoy__config__rbac__v3__Permission_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_config_rbac_v3_Principal** envoy_config_rbac_v3_Policy_mutable_principals(envoy_config_rbac_v3_Policy* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_rbac_v3_Principal**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_rbac_v3_Principal** envoy_config_rbac_v3_Policy_resize_principals(envoy_config_rbac_v3_Policy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_Principal**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Policy_add_principals(envoy_config_rbac_v3_Policy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_rbac_v3_Principal* sub = (struct envoy_config_rbac_v3_Principal*)_upb_Message_New(&envoy__config__rbac__v3__Principal_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Policy_set_condition(envoy_config_rbac_v3_Policy *msg, struct google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* envoy_config_rbac_v3_Policy_mutable_condition(envoy_config_rbac_v3_Policy* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)envoy_config_rbac_v3_Policy_condition(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Policy_set_condition(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Policy_set_checked_condition(envoy_config_rbac_v3_Policy *msg, struct google_api_expr_v1alpha1_CheckedExpr* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_CheckedExpr* envoy_config_rbac_v3_Policy_mutable_checked_condition(envoy_config_rbac_v3_Policy* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_CheckedExpr* sub = (struct google_api_expr_v1alpha1_CheckedExpr*)envoy_config_rbac_v3_Policy_checked_condition(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_CheckedExpr*)_upb_Message_New(&google__api__expr__v1alpha1__CheckedExpr_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Policy_set_checked_condition(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_SourcedMetadata_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_SourcedMetadata*)_upb_Message_New(&envoy__config__rbac__v3__SourcedMetadata_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_SourcedMetadata_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_SourcedMetadata* ret = envoy_config_rbac_v3_SourcedMetadata_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__SourcedMetadata_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_SourcedMetadata_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_SourcedMetadata* ret = envoy_config_rbac_v3_SourcedMetadata_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__SourcedMetadata_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_SourcedMetadata_serialize(const envoy_config_rbac_v3_SourcedMetadata* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__SourcedMetadata_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_SourcedMetadata_serialize_ex(const envoy_config_rbac_v3_SourcedMetadata* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__SourcedMetadata_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_SourcedMetadata_clear_metadata_matcher(envoy_config_rbac_v3_SourcedMetadata* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_rbac_v3_SourcedMetadata_metadata_matcher(const envoy_config_rbac_v3_SourcedMetadata* msg) {
  const struct envoy_type_matcher_v3_MetadataMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_MetadataMatcher* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_SourcedMetadata_has_metadata_matcher(const envoy_config_rbac_v3_SourcedMetadata* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_SourcedMetadata_clear_metadata_source(envoy_config_rbac_v3_SourcedMetadata* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_rbac_v3_SourcedMetadata_metadata_source(const envoy_config_rbac_v3_SourcedMetadata* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_rbac_v3_SourcedMetadata_set_metadata_matcher(envoy_config_rbac_v3_SourcedMetadata *msg, struct envoy_type_matcher_v3_MetadataMatcher* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_rbac_v3_SourcedMetadata_mutable_metadata_matcher(envoy_config_rbac_v3_SourcedMetadata* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_MetadataMatcher* sub = (struct envoy_type_matcher_v3_MetadataMatcher*)envoy_config_rbac_v3_SourcedMetadata_metadata_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_MetadataMatcher*)_upb_Message_New(&envoy__type__matcher__v3__MetadataMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_SourcedMetadata_set_metadata_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_SourcedMetadata_set_metadata_source(envoy_config_rbac_v3_SourcedMetadata *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

/* envoy.config.rbac.v3.Permission */

UPB_INLINE envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Permission_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Permission*)_upb_Message_New(&envoy__config__rbac__v3__Permission_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Permission_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Permission* ret = envoy_config_rbac_v3_Permission_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Permission_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Permission_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Permission* ret = envoy_config_rbac_v3_Permission_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Permission_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Permission_serialize(const envoy_config_rbac_v3_Permission* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Permission_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Permission_serialize_ex(const envoy_config_rbac_v3_Permission* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Permission_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_rbac_v3_Permission_rule_and_rules = 1,
  envoy_config_rbac_v3_Permission_rule_or_rules = 2,
  envoy_config_rbac_v3_Permission_rule_any = 3,
  envoy_config_rbac_v3_Permission_rule_header = 4,
  envoy_config_rbac_v3_Permission_rule_url_path = 10,
  envoy_config_rbac_v3_Permission_rule_destination_ip = 5,
  envoy_config_rbac_v3_Permission_rule_destination_port = 6,
  envoy_config_rbac_v3_Permission_rule_destination_port_range = 11,
  envoy_config_rbac_v3_Permission_rule_metadata = 7,
  envoy_config_rbac_v3_Permission_rule_not_rule = 8,
  envoy_config_rbac_v3_Permission_rule_requested_server_name = 9,
  envoy_config_rbac_v3_Permission_rule_matcher = 12,
  envoy_config_rbac_v3_Permission_rule_uri_template = 13,
  envoy_config_rbac_v3_Permission_rule_sourced_metadata = 14,
  envoy_config_rbac_v3_Permission_rule_NOT_SET = 0
} envoy_config_rbac_v3_Permission_rule_oneofcases;
UPB_INLINE envoy_config_rbac_v3_Permission_rule_oneofcases envoy_config_rbac_v3_Permission_rule_case(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_Permission_rule_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_rule(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__rbac__v3__Permission_msg_init, &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_and_rules(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_and_rules(const envoy_config_rbac_v3_Permission* msg) {
  const envoy_config_rbac_v3_Permission_Set* default_val = NULL;
  const envoy_config_rbac_v3_Permission_Set* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission__Set_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_and_rules(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_or_rules(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_or_rules(const envoy_config_rbac_v3_Permission* msg) {
  const envoy_config_rbac_v3_Permission_Set* default_val = NULL;
  const envoy_config_rbac_v3_Permission_Set* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission__Set_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_or_rules(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_any(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_any(const envoy_config_rbac_v3_Permission* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_any(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_header(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_HeaderMatcher* envoy_config_rbac_v3_Permission_header(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_config_route_v3_HeaderMatcher* default_val = NULL;
  const struct envoy_config_route_v3_HeaderMatcher* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_header(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_destination_ip(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Permission_destination_ip(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_config_core_v3_CidrRange* default_val = NULL;
  const struct envoy_config_core_v3_CidrRange* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_destination_ip(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_destination_port(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_rbac_v3_Permission_destination_port(const envoy_config_rbac_v3_Permission* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_destination_port(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_metadata(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_rbac_v3_Permission_metadata(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_type_matcher_v3_MetadataMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_MetadataMatcher* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_metadata(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_not_rule(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Permission_not_rule(const envoy_config_rbac_v3_Permission* msg) {
  const envoy_config_rbac_v3_Permission* default_val = NULL;
  const envoy_config_rbac_v3_Permission* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_not_rule(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_requested_server_name(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_rbac_v3_Permission_requested_server_name(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_requested_server_name(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_url_path(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_PathMatcher* envoy_config_rbac_v3_Permission_url_path(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_type_matcher_v3_PathMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_PathMatcher* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__PathMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_url_path(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_destination_port_range(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Int32Range* envoy_config_rbac_v3_Permission_destination_port_range(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_type_v3_Int32Range* default_val = NULL;
  const struct envoy_type_v3_Int32Range* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int32Range_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_destination_port_range(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_matcher(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_rbac_v3_Permission_matcher(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_matcher(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_uri_template(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_rbac_v3_Permission_uri_template(const envoy_config_rbac_v3_Permission* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_uri_template(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_clear_sourced_metadata(envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_Permission_sourced_metadata(const envoy_config_rbac_v3_Permission* msg) {
  const envoy_config_rbac_v3_SourcedMetadata* default_val = NULL;
  const envoy_config_rbac_v3_SourcedMetadata* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__SourcedMetadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Permission_has_sourced_metadata(const envoy_config_rbac_v3_Permission* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_rbac_v3_Permission_set_and_rules(envoy_config_rbac_v3_Permission *msg, envoy_config_rbac_v3_Permission_Set* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission__Set_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_mutable_and_rules(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Permission_Set* sub = (struct envoy_config_rbac_v3_Permission_Set*)envoy_config_rbac_v3_Permission_and_rules(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Permission_Set*)_upb_Message_New(&envoy__config__rbac__v3__Permission__Set_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_and_rules(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_or_rules(envoy_config_rbac_v3_Permission *msg, envoy_config_rbac_v3_Permission_Set* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission__Set_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_mutable_or_rules(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Permission_Set* sub = (struct envoy_config_rbac_v3_Permission_Set*)envoy_config_rbac_v3_Permission_or_rules(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Permission_Set*)_upb_Message_New(&envoy__config__rbac__v3__Permission__Set_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_or_rules(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_any(envoy_config_rbac_v3_Permission *msg, bool value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_header(envoy_config_rbac_v3_Permission *msg, struct envoy_config_route_v3_HeaderMatcher* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_rbac_v3_Permission_mutable_header(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)envoy_config_rbac_v3_Permission_header(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_header(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_destination_ip(envoy_config_rbac_v3_Permission *msg, struct envoy_config_core_v3_CidrRange* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Permission_mutable_destination_ip(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)envoy_config_rbac_v3_Permission_destination_ip(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_destination_ip(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_destination_port(envoy_config_rbac_v3_Permission *msg, uint32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_metadata(envoy_config_rbac_v3_Permission *msg, struct envoy_type_matcher_v3_MetadataMatcher* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_rbac_v3_Permission_mutable_metadata(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_MetadataMatcher* sub = (struct envoy_type_matcher_v3_MetadataMatcher*)envoy_config_rbac_v3_Permission_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_MetadataMatcher*)_upb_Message_New(&envoy__type__matcher__v3__MetadataMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_not_rule(envoy_config_rbac_v3_Permission *msg, envoy_config_rbac_v3_Permission* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Permission_mutable_not_rule(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Permission* sub = (struct envoy_config_rbac_v3_Permission*)envoy_config_rbac_v3_Permission_not_rule(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Permission*)_upb_Message_New(&envoy__config__rbac__v3__Permission_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_not_rule(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_requested_server_name(envoy_config_rbac_v3_Permission *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_rbac_v3_Permission_mutable_requested_server_name(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_rbac_v3_Permission_requested_server_name(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_requested_server_name(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_url_path(envoy_config_rbac_v3_Permission *msg, struct envoy_type_matcher_v3_PathMatcher* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__PathMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_PathMatcher* envoy_config_rbac_v3_Permission_mutable_url_path(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_PathMatcher* sub = (struct envoy_type_matcher_v3_PathMatcher*)envoy_config_rbac_v3_Permission_url_path(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_PathMatcher*)_upb_Message_New(&envoy__type__matcher__v3__PathMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_url_path(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_destination_port_range(envoy_config_rbac_v3_Permission *msg, struct envoy_type_v3_Int32Range* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int32Range_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Int32Range* envoy_config_rbac_v3_Permission_mutable_destination_port_range(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_type_v3_Int32Range* sub = (struct envoy_type_v3_Int32Range*)envoy_config_rbac_v3_Permission_destination_port_range(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Int32Range*)_upb_Message_New(&envoy__type__v3__Int32Range_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_destination_port_range(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_matcher(envoy_config_rbac_v3_Permission *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_rbac_v3_Permission_mutable_matcher(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_rbac_v3_Permission_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_uri_template(envoy_config_rbac_v3_Permission *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_rbac_v3_Permission_mutable_uri_template(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_rbac_v3_Permission_uri_template(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_uri_template(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_set_sourced_metadata(envoy_config_rbac_v3_Permission *msg, envoy_config_rbac_v3_SourcedMetadata* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__SourcedMetadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_Permission_mutable_sourced_metadata(envoy_config_rbac_v3_Permission* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_SourcedMetadata* sub = (struct envoy_config_rbac_v3_SourcedMetadata*)envoy_config_rbac_v3_Permission_sourced_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_SourcedMetadata*)_upb_Message_New(&envoy__config__rbac__v3__SourcedMetadata_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Permission_set_sourced_metadata(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_Set_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Permission_Set*)_upb_Message_New(&envoy__config__rbac__v3__Permission__Set_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_Set_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Permission_Set* ret = envoy_config_rbac_v3_Permission_Set_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Permission__Set_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Permission_Set* envoy_config_rbac_v3_Permission_Set_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Permission_Set* ret = envoy_config_rbac_v3_Permission_Set_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Permission__Set_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Permission_Set_serialize(const envoy_config_rbac_v3_Permission_Set* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Permission__Set_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Permission_Set_serialize_ex(const envoy_config_rbac_v3_Permission_Set* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Permission__Set_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_Permission_Set_clear_rules(envoy_config_rbac_v3_Permission_Set* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Permission* const* envoy_config_rbac_v3_Permission_Set_rules(const envoy_config_rbac_v3_Permission_Set* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_rbac_v3_Permission* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_rbac_v3_Permission_Set_rules_upb_array(const envoy_config_rbac_v3_Permission_Set* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_rbac_v3_Permission_Set_rules_mutable_upb_array(envoy_config_rbac_v3_Permission_Set* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_rbac_v3_Permission** envoy_config_rbac_v3_Permission_Set_mutable_rules(envoy_config_rbac_v3_Permission_Set* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_rbac_v3_Permission**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_rbac_v3_Permission** envoy_config_rbac_v3_Permission_Set_resize_rules(envoy_config_rbac_v3_Permission_Set* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_Permission**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_rbac_v3_Permission* envoy_config_rbac_v3_Permission_Set_add_rules(envoy_config_rbac_v3_Permission_Set* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Permission_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_rbac_v3_Permission* sub = (struct envoy_config_rbac_v3_Permission*)_upb_Message_New(&envoy__config__rbac__v3__Permission_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Principal_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Principal*)_upb_Message_New(&envoy__config__rbac__v3__Principal_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Principal_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Principal* ret = envoy_config_rbac_v3_Principal_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Principal_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Principal_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Principal* ret = envoy_config_rbac_v3_Principal_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Principal_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Principal_serialize(const envoy_config_rbac_v3_Principal* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Principal_serialize_ex(const envoy_config_rbac_v3_Principal* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_rbac_v3_Principal_identifier_and_ids = 1,
  envoy_config_rbac_v3_Principal_identifier_or_ids = 2,
  envoy_config_rbac_v3_Principal_identifier_any = 3,
  envoy_config_rbac_v3_Principal_identifier_authenticated = 4,
  envoy_config_rbac_v3_Principal_identifier_source_ip = 5,
  envoy_config_rbac_v3_Principal_identifier_direct_remote_ip = 10,
  envoy_config_rbac_v3_Principal_identifier_remote_ip = 11,
  envoy_config_rbac_v3_Principal_identifier_header = 6,
  envoy_config_rbac_v3_Principal_identifier_url_path = 9,
  envoy_config_rbac_v3_Principal_identifier_metadata = 7,
  envoy_config_rbac_v3_Principal_identifier_filter_state = 12,
  envoy_config_rbac_v3_Principal_identifier_not_id = 8,
  envoy_config_rbac_v3_Principal_identifier_sourced_metadata = 13,
  envoy_config_rbac_v3_Principal_identifier_NOT_SET = 0
} envoy_config_rbac_v3_Principal_identifier_oneofcases;
UPB_INLINE envoy_config_rbac_v3_Principal_identifier_oneofcases envoy_config_rbac_v3_Principal_identifier_case(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_Principal_identifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_identifier(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal_msg_init, &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_and_ids(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_and_ids(const envoy_config_rbac_v3_Principal* msg) {
  const envoy_config_rbac_v3_Principal_Set* default_val = NULL;
  const envoy_config_rbac_v3_Principal_Set* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal__Set_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_and_ids(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_or_ids(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_or_ids(const envoy_config_rbac_v3_Principal* msg) {
  const envoy_config_rbac_v3_Principal_Set* default_val = NULL;
  const envoy_config_rbac_v3_Principal_Set* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal__Set_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_or_ids(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_any(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_any(const envoy_config_rbac_v3_Principal* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_any(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_authenticated(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Principal_Authenticated* envoy_config_rbac_v3_Principal_authenticated(const envoy_config_rbac_v3_Principal* msg) {
  const envoy_config_rbac_v3_Principal_Authenticated* default_val = NULL;
  const envoy_config_rbac_v3_Principal_Authenticated* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal__Authenticated_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_authenticated(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_source_ip(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Principal_source_ip(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_config_core_v3_CidrRange* default_val = NULL;
  const struct envoy_config_core_v3_CidrRange* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_source_ip(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_header(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_HeaderMatcher* envoy_config_rbac_v3_Principal_header(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_config_route_v3_HeaderMatcher* default_val = NULL;
  const struct envoy_config_route_v3_HeaderMatcher* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_header(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_metadata(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_rbac_v3_Principal_metadata(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_type_matcher_v3_MetadataMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_MetadataMatcher* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_metadata(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_not_id(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Principal_not_id(const envoy_config_rbac_v3_Principal* msg) {
  const envoy_config_rbac_v3_Principal* default_val = NULL;
  const envoy_config_rbac_v3_Principal* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_not_id(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_url_path(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_PathMatcher* envoy_config_rbac_v3_Principal_url_path(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_type_matcher_v3_PathMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_PathMatcher* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__PathMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_url_path(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_direct_remote_ip(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Principal_direct_remote_ip(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_config_core_v3_CidrRange* default_val = NULL;
  const struct envoy_config_core_v3_CidrRange* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_direct_remote_ip(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_remote_ip(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Principal_remote_ip(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_config_core_v3_CidrRange* default_val = NULL;
  const struct envoy_config_core_v3_CidrRange* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_remote_ip(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_filter_state(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_FilterStateMatcher* envoy_config_rbac_v3_Principal_filter_state(const envoy_config_rbac_v3_Principal* msg) {
  const struct envoy_type_matcher_v3_FilterStateMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_FilterStateMatcher* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__FilterStateMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_filter_state(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_clear_sourced_metadata(envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_Principal_sourced_metadata(const envoy_config_rbac_v3_Principal* msg) {
  const envoy_config_rbac_v3_SourcedMetadata* default_val = NULL;
  const envoy_config_rbac_v3_SourcedMetadata* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__SourcedMetadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_has_sourced_metadata(const envoy_config_rbac_v3_Principal* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_rbac_v3_Principal_set_and_ids(envoy_config_rbac_v3_Principal *msg, envoy_config_rbac_v3_Principal_Set* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal__Set_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_mutable_and_ids(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Principal_Set* sub = (struct envoy_config_rbac_v3_Principal_Set*)envoy_config_rbac_v3_Principal_and_ids(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Principal_Set*)_upb_Message_New(&envoy__config__rbac__v3__Principal__Set_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_and_ids(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_or_ids(envoy_config_rbac_v3_Principal *msg, envoy_config_rbac_v3_Principal_Set* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal__Set_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_mutable_or_ids(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Principal_Set* sub = (struct envoy_config_rbac_v3_Principal_Set*)envoy_config_rbac_v3_Principal_or_ids(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Principal_Set*)_upb_Message_New(&envoy__config__rbac__v3__Principal__Set_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_or_ids(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_any(envoy_config_rbac_v3_Principal *msg, bool value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_authenticated(envoy_config_rbac_v3_Principal *msg, envoy_config_rbac_v3_Principal_Authenticated* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal__Authenticated_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Principal_Authenticated* envoy_config_rbac_v3_Principal_mutable_authenticated(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Principal_Authenticated* sub = (struct envoy_config_rbac_v3_Principal_Authenticated*)envoy_config_rbac_v3_Principal_authenticated(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Principal_Authenticated*)_upb_Message_New(&envoy__config__rbac__v3__Principal__Authenticated_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_authenticated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_source_ip(envoy_config_rbac_v3_Principal *msg, struct envoy_config_core_v3_CidrRange* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Principal_mutable_source_ip(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)envoy_config_rbac_v3_Principal_source_ip(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_source_ip(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_header(envoy_config_rbac_v3_Principal *msg, struct envoy_config_route_v3_HeaderMatcher* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_rbac_v3_Principal_mutable_header(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)envoy_config_rbac_v3_Principal_header(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_header(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_metadata(envoy_config_rbac_v3_Principal *msg, struct envoy_type_matcher_v3_MetadataMatcher* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_rbac_v3_Principal_mutable_metadata(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_MetadataMatcher* sub = (struct envoy_type_matcher_v3_MetadataMatcher*)envoy_config_rbac_v3_Principal_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_MetadataMatcher*)_upb_Message_New(&envoy__type__matcher__v3__MetadataMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_not_id(envoy_config_rbac_v3_Principal *msg, envoy_config_rbac_v3_Principal* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Principal_mutable_not_id(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_Principal* sub = (struct envoy_config_rbac_v3_Principal*)envoy_config_rbac_v3_Principal_not_id(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_Principal*)_upb_Message_New(&envoy__config__rbac__v3__Principal_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_not_id(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_url_path(envoy_config_rbac_v3_Principal *msg, struct envoy_type_matcher_v3_PathMatcher* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__PathMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_PathMatcher* envoy_config_rbac_v3_Principal_mutable_url_path(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_PathMatcher* sub = (struct envoy_type_matcher_v3_PathMatcher*)envoy_config_rbac_v3_Principal_url_path(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_PathMatcher*)_upb_Message_New(&envoy__type__matcher__v3__PathMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_url_path(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_direct_remote_ip(envoy_config_rbac_v3_Principal *msg, struct envoy_config_core_v3_CidrRange* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Principal_mutable_direct_remote_ip(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)envoy_config_rbac_v3_Principal_direct_remote_ip(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_direct_remote_ip(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_remote_ip(envoy_config_rbac_v3_Principal *msg, struct envoy_config_core_v3_CidrRange* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_rbac_v3_Principal_mutable_remote_ip(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)envoy_config_rbac_v3_Principal_remote_ip(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_remote_ip(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_filter_state(envoy_config_rbac_v3_Principal *msg, struct envoy_type_matcher_v3_FilterStateMatcher* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__FilterStateMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_FilterStateMatcher* envoy_config_rbac_v3_Principal_mutable_filter_state(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_FilterStateMatcher* sub = (struct envoy_type_matcher_v3_FilterStateMatcher*)envoy_config_rbac_v3_Principal_filter_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_FilterStateMatcher*)_upb_Message_New(&envoy__type__matcher__v3__FilterStateMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_filter_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_set_sourced_metadata(envoy_config_rbac_v3_Principal *msg, envoy_config_rbac_v3_SourcedMetadata* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__SourcedMetadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_rbac_v3_SourcedMetadata* envoy_config_rbac_v3_Principal_mutable_sourced_metadata(envoy_config_rbac_v3_Principal* msg, upb_Arena* arena) {
  struct envoy_config_rbac_v3_SourcedMetadata* sub = (struct envoy_config_rbac_v3_SourcedMetadata*)envoy_config_rbac_v3_Principal_sourced_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_rbac_v3_SourcedMetadata*)_upb_Message_New(&envoy__config__rbac__v3__SourcedMetadata_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_set_sourced_metadata(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_Set_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Principal_Set*)_upb_Message_New(&envoy__config__rbac__v3__Principal__Set_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_Set_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Principal_Set* ret = envoy_config_rbac_v3_Principal_Set_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Principal__Set_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Principal_Set* envoy_config_rbac_v3_Principal_Set_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Principal_Set* ret = envoy_config_rbac_v3_Principal_Set_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Principal__Set_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Principal_Set_serialize(const envoy_config_rbac_v3_Principal_Set* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal__Set_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Principal_Set_serialize_ex(const envoy_config_rbac_v3_Principal_Set* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal__Set_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_Set_clear_ids(envoy_config_rbac_v3_Principal_Set* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_rbac_v3_Principal* const* envoy_config_rbac_v3_Principal_Set_ids(const envoy_config_rbac_v3_Principal_Set* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_rbac_v3_Principal* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_rbac_v3_Principal_Set_ids_upb_array(const envoy_config_rbac_v3_Principal_Set* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_rbac_v3_Principal_Set_ids_mutable_upb_array(envoy_config_rbac_v3_Principal_Set* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_rbac_v3_Principal** envoy_config_rbac_v3_Principal_Set_mutable_ids(envoy_config_rbac_v3_Principal_Set* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_rbac_v3_Principal**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_rbac_v3_Principal** envoy_config_rbac_v3_Principal_Set_resize_ids(envoy_config_rbac_v3_Principal_Set* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_rbac_v3_Principal**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_rbac_v3_Principal* envoy_config_rbac_v3_Principal_Set_add_ids(envoy_config_rbac_v3_Principal_Set* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__rbac__v3__Principal_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_rbac_v3_Principal* sub = (struct envoy_config_rbac_v3_Principal*)_upb_Message_New(&envoy__config__rbac__v3__Principal_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_Principal_Authenticated* envoy_config_rbac_v3_Principal_Authenticated_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Principal_Authenticated*)_upb_Message_New(&envoy__config__rbac__v3__Principal__Authenticated_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Principal_Authenticated* envoy_config_rbac_v3_Principal_Authenticated_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Principal_Authenticated* ret = envoy_config_rbac_v3_Principal_Authenticated_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Principal__Authenticated_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Principal_Authenticated* envoy_config_rbac_v3_Principal_Authenticated_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Principal_Authenticated* ret = envoy_config_rbac_v3_Principal_Authenticated_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Principal__Authenticated_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Principal_Authenticated_serialize(const envoy_config_rbac_v3_Principal_Authenticated* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal__Authenticated_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Principal_Authenticated_serialize_ex(const envoy_config_rbac_v3_Principal_Authenticated* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Principal__Authenticated_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_Principal_Authenticated_clear_principal_name(envoy_config_rbac_v3_Principal_Authenticated* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_rbac_v3_Principal_Authenticated_principal_name(const envoy_config_rbac_v3_Principal_Authenticated* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_rbac_v3_Principal_Authenticated_has_principal_name(const envoy_config_rbac_v3_Principal_Authenticated* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_rbac_v3_Principal_Authenticated_set_principal_name(envoy_config_rbac_v3_Principal_Authenticated *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_rbac_v3_Principal_Authenticated_mutable_principal_name(envoy_config_rbac_v3_Principal_Authenticated* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_rbac_v3_Principal_Authenticated_principal_name(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_rbac_v3_Principal_Authenticated_set_principal_name(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_rbac_v3_Action* envoy_config_rbac_v3_Action_new(upb_Arena* arena) {
  return (envoy_config_rbac_v3_Action*)_upb_Message_New(&envoy__config__rbac__v3__Action_msg_init, arena);
}
UPB_INLINE envoy_config_rbac_v3_Action* envoy_config_rbac_v3_Action_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_rbac_v3_Action* ret = envoy_config_rbac_v3_Action_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Action_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_rbac_v3_Action* envoy_config_rbac_v3_Action_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_rbac_v3_Action* ret = envoy_config_rbac_v3_Action_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__rbac__v3__Action_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_rbac_v3_Action_serialize(const envoy_config_rbac_v3_Action* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Action_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_rbac_v3_Action_serialize_ex(const envoy_config_rbac_v3_Action* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__rbac__v3__Action_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_rbac_v3_Action_clear_name(envoy_config_rbac_v3_Action* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_rbac_v3_Action_name(const envoy_config_rbac_v3_Action* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_rbac_v3_Action_clear_action(envoy_config_rbac_v3_Action* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_rbac_v3_Action_action(const envoy_config_rbac_v3_Action* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_rbac_v3_Action_set_name(envoy_config_rbac_v3_Action *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_rbac_v3_Action_set_action(envoy_config_rbac_v3_Action *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
