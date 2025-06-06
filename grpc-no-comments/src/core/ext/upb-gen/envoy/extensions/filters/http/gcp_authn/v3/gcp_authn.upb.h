
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_GCP_AUTHN_V3_GCP_AUTHN_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_GCP_AUTHN_V3_GCP_AUTHN_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/filters/http/gcp_authn/v3/gcp_authn.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/http_uri.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig;
typedef struct envoy_extensions_filters_http_gcp_authn_v3_Audience { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_gcp_authn_v3_Audience;
typedef struct envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig;
typedef struct envoy_extensions_filters_http_gcp_authn_v3_TokenHeader { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_gcp_authn_v3_TokenHeader;
struct envoy_config_core_v3_HttpUri;
struct envoy_config_core_v3_RetryPolicy;
struct google_protobuf_Duration;
struct google_protobuf_UInt64Value;

UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig*)_upb_Message_New(&envoy__extensions__filters__http__gcp_0authn__v3__GcpAuthnFilterConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* ret = envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__GcpAuthnFilterConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* ret = envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__GcpAuthnFilterConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_serialize(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__GcpAuthnFilterConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_serialize_ex(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__GcpAuthnFilterConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_clear_http_uri(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HttpUri* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_http_uri(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const struct envoy_config_core_v3_HttpUri* default_val = NULL;
  const struct envoy_config_core_v3_HttpUri* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpUri_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_has_http_uri(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_clear_retry_policy(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RetryPolicy* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_retry_policy(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const struct envoy_config_core_v3_RetryPolicy* default_val = NULL;
  const struct envoy_config_core_v3_RetryPolicy* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_has_retry_policy(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_clear_cache_config(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_cache_config(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* default_val = NULL;
  const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_has_cache_config(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_clear_token_header(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_token_header(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* default_val = NULL;
  const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_has_token_header(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_clear_cluster(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_cluster(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_clear_timeout(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_timeout(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_has_timeout(const envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_http_uri(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig *msg, struct envoy_config_core_v3_HttpUri* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpUri_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HttpUri* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_mutable_http_uri(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HttpUri* sub = (struct envoy_config_core_v3_HttpUri*)envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_http_uri(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HttpUri*)_upb_Message_New(&envoy__config__core__v3__HttpUri_msg_init, arena);
    if (sub) envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_http_uri(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_retry_policy(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig *msg, struct envoy_config_core_v3_RetryPolicy* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RetryPolicy* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_mutable_retry_policy(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RetryPolicy* sub = (struct envoy_config_core_v3_RetryPolicy*)envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_retry_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RetryPolicy*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy_msg_init, arena);
    if (sub) envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_retry_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_cache_config(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig *msg, envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_mutable_cache_config(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* sub = (struct envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig*)envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_cache_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig*)_upb_Message_New(&envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init, arena);
    if (sub) envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_cache_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_token_header(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig *msg, envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_mutable_token_header(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* sub = (struct envoy_extensions_filters_http_gcp_authn_v3_TokenHeader*)envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_token_header(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_http_gcp_authn_v3_TokenHeader*)_upb_Message_New(&envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init, arena);
    if (sub) envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_token_header(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_cluster(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_timeout(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_mutable_timeout(envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_set_timeout(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_Audience* envoy_extensions_filters_http_gcp_authn_v3_Audience_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_gcp_authn_v3_Audience*)_upb_Message_New(&envoy__extensions__filters__http__gcp_0authn__v3__Audience_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_Audience* envoy_extensions_filters_http_gcp_authn_v3_Audience_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_Audience* ret = envoy_extensions_filters_http_gcp_authn_v3_Audience_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__Audience_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_Audience* envoy_extensions_filters_http_gcp_authn_v3_Audience_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_Audience* ret = envoy_extensions_filters_http_gcp_authn_v3_Audience_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__Audience_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_Audience_serialize(const envoy_extensions_filters_http_gcp_authn_v3_Audience* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__Audience_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_Audience_serialize_ex(const envoy_extensions_filters_http_gcp_authn_v3_Audience* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__Audience_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_Audience_clear_url(envoy_extensions_filters_http_gcp_authn_v3_Audience* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_gcp_authn_v3_Audience_url(const envoy_extensions_filters_http_gcp_authn_v3_Audience* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_Audience_set_url(envoy_extensions_filters_http_gcp_authn_v3_Audience *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig*)_upb_Message_New(&envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* ret = envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* ret = envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_serialize(const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_serialize_ex(const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__TokenCacheConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_clear_cache_size(envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_cache_size(const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_has_cache_size(const envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_set_cache_size(envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_mutable_cache_size(envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_cache_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_set_cache_size(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_gcp_authn_v3_TokenHeader*)_upb_Message_New(&envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* ret = envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* ret = envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_serialize(const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_serialize_ex(const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__gcp_0authn__v3__TokenHeader_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_clear_name(envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_name(const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_clear_value_prefix(envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_value_prefix(const envoy_extensions_filters_http_gcp_authn_v3_TokenHeader* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_set_name(envoy_extensions_filters_http_gcp_authn_v3_TokenHeader *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_set_value_prefix(envoy_extensions_filters_http_gcp_authn_v3_TokenHeader *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
