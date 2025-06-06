
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/transport_sockets/tls/v3/tls.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/common.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/secret.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext;
typedef struct envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext;
typedef struct envoy_extensions_transport_sockets_tls_v3_TlsKeyLog { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_TlsKeyLog;
typedef struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CommonTlsContext;
typedef struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider;
typedef struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance;
typedef struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext;
struct envoy_config_core_v3_CidrRange;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance;
struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext;
struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig;
struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate;
struct envoy_extensions_transport_sockets_tls_v3_TlsParameters;
struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;

typedef enum {
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_LENIENT_STAPLING = 0,
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_STRICT_STAPLING = 1,
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_MUST_STAPLE = 2
} envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_OcspStaplePolicy;

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* ret = envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* ret = envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_serialize(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__UpstreamTlsContext_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_common_tls_context(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_common_tls_context(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_has_common_tls_context(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_sni(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_sni(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_allow_renegotiation(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_allow_renegotiation(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_max_session_keys(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_max_session_keys(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_has_max_session_keys(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_enforce_rsa_key_usage(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_enforce_rsa_key_usage(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_has_enforce_rsa_key_usage(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_auto_host_sni(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_auto_host_sni(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_clear_auto_sni_san_validation(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  const upb_MiniTableField field = {7, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_auto_sni_san_validation(const envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_common_tls_context(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_mutable_common_tls_context(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*)envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_common_tls_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_common_tls_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_sni(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_allow_renegotiation(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_max_session_keys(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_mutable_max_session_keys(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_max_session_keys(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_max_session_keys(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_enforce_rsa_key_usage(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_mutable_enforce_rsa_key_usage(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_enforce_rsa_key_usage(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_enforce_rsa_key_usage(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_auto_host_sni(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, bool value) {
  const upb_MiniTableField field = {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_set_auto_sni_san_validation(envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext *msg, bool value) {
  const upb_MiniTableField field = {7, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* ret = envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* ret = envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_serialize(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_session_ticket_keys = 4,
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_session_ticket_keys_sds_secret_config = 5,
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_disable_stateless_session_resumption = 7,
  envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_NOT_SET = 0
} envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_oneofcases;
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_oneofcases envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_case(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_session_ticket_keys_type(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__DownstreamTlsContext_msg_init, &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_common_tls_context(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_common_tls_context(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_common_tls_context(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_require_client_certificate(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_require_client_certificate(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_require_client_certificate(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_require_sni(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_require_sni(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_require_sni(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_session_ticket_keys(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_session_ticket_keys(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_session_ticket_keys_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_sds_secret_config(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_session_ticket_keys_sds_secret_config(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_session_timeout(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 48), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_timeout(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 48), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_session_timeout(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 48), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_disable_stateless_session_resumption(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_disable_stateless_session_resumption(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_disable_stateless_session_resumption(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_ocsp_staple_policy(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_ocsp_staple_policy(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {8, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_full_scan_certs_on_sni_mismatch(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_full_scan_certs_on_sni_mismatch(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_has_full_scan_certs_on_sni_mismatch(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_disable_stateful_session_resumption(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {10, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_disable_stateful_session_resumption(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {10, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_clear_prefer_client_ciphers(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  const upb_MiniTableField field = {11, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_prefer_client_ciphers(const envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {11, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_common_tls_context(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_common_tls_context(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_common_tls_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_common_tls_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_require_client_certificate(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_require_client_certificate(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_require_client_certificate(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_require_client_certificate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_require_sni(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_require_sni(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_require_sni(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_require_sni(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_session_ticket_keys(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_session_ticket_keys(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_session_ticket_keys(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_session_ticket_keys_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_session_ticket_keys_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_ticket_keys_sds_secret_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_session_ticket_keys_sds_secret_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_session_timeout(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 48), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_session_timeout(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_session_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_session_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_disable_stateless_session_resumption(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, bool value) {
  const upb_MiniTableField field = {7, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_ocsp_staple_policy(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, int32_t value) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_full_scan_certs_on_sni_mismatch(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_mutable_full_scan_certs_on_sni_mismatch(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_full_scan_certs_on_sni_mismatch(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_full_scan_certs_on_sni_mismatch(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_disable_stateful_session_resumption(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, bool value) {
  const upb_MiniTableField field = {10, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_set_prefer_client_ciphers(envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext *msg, bool value) {
  const upb_MiniTableField field = {11, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_TlsKeyLog*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* ret = envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* ret = envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_serialize(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_clear_path(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_path(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_clear_local_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* const* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_local_address_range(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_CidrRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_local_address_range_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_local_address_range_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_clear_remote_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* const* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_remote_address_range(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_CidrRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_remote_address_range_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_remote_address_range_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_set_path(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_mutable_local_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_CidrRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_resize_local_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_CidrRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_add_local_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_mutable_remote_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_CidrRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_resize_remote_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_CidrRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_add_remote_address_range(envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_serialize(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_validation_context = 3,
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_validation_context_sds_secret_config = 7,
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_combined_validation_context = 8,
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_validation_context_certificate_provider = 10,
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_validation_context_certificate_provider_instance = 12,
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_NOT_SET = 0
} envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_oneofcases;
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_oneofcases envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_case(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_validation_context_type(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext_msg_init, &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_tls_params(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_TlsParameters* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_params(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_TlsParameters* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_TlsParameters* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_tls_params(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_tls_certificates(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* const* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificates(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificates_upb_array(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificates_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_validation_context(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_alpn_protocols(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_alpn_protocols(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_alpn_protocols_upb_array(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_alpn_protocols_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_tls_certificate_sds_secret_configs(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* const* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_sds_secret_configs(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_sds_secret_configs_upb_array(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_sds_secret_configs_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_validation_context_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_sds_secret_config(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_validation_context_sds_secret_config(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_combined_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_combined_validation_context(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_combined_validation_context(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_tls_certificate_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 48), 65, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_certificate_provider(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(28, 48), 65, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_tls_certificate_certificate_provider(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 48), 65, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_validation_context_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_certificate_provider(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_validation_context_certificate_provider(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_tls_certificate_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 56), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(32, 56), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_tls_certificate_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 56), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_validation_context_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_validation_context_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_custom_handshaker(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 64), 67, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_custom_handshaker(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(36, 64), 67, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_custom_handshaker(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 64), 67, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_tls_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(40, 72), 68, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(40, 72), 68, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_tls_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(40, 72), 68, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_key_log(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 80), 69, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_key_log(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(44, 80), 69, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_key_log(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 80), 69, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_clear_custom_tls_certificate_selector(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(48, 88), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_custom_tls_certificate_selector(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(48, 88), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_custom_tls_certificate_selector(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(48, 88), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_params(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, struct envoy_extensions_transport_sockets_tls_v3_TlsParameters* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsParameters* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_tls_params(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_TlsParameters* sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsParameters*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_params(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsParameters*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_params(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate** envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_tls_certificates(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate** envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_resize_tls_certificates(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_add_tls_certificates(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context(msg, sub);
  }
  return sub;
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_alpn_protocols(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_resize_alpn_protocols(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_add_alpn_protocols(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig** envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_tls_certificate_sds_secret_configs(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig** envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_resize_tls_certificate_sds_secret_configs(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_add_tls_certificate_sds_secret_configs(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_validation_context_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_sds_secret_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context_sds_secret_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_combined_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_combined_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_combined_validation_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_combined_validation_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_certificate_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 48), 65, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_tls_certificate_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_certificate_provider(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_certificate_certificate_provider(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_validation_context_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_certificate_provider(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context_certificate_provider(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_certificate_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 56), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_tls_certificate_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_certificate_provider_instance(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_certificate_certificate_provider_instance(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(56, 96), UPB_SIZE(-53, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_validation_context_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context_certificate_provider_instance(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_validation_context_certificate_provider_instance(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_custom_handshaker(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 64), 67, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_custom_handshaker(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_custom_handshaker(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_custom_handshaker(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(40, 72), 68, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_tls_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_provider_instance(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_tls_certificate_provider_instance(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_key_log(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 80), 69, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_key_log(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_TlsKeyLog* sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsKeyLog*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_key_log(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsKeyLog*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsKeyLog_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_key_log(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_custom_tls_certificate_selector(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(48, 88), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_mutable_custom_tls_certificate_selector(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_custom_tls_certificate_selector(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_set_custom_tls_certificate_selector(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_serialize(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_config_typed_config = 2,
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_config_NOT_SET = 0
} envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_config_oneofcases;
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_config_oneofcases envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_config_case(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_config_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_clear_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_clear_name(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_name(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_clear_typed_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_typed_config(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_has_typed_config(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_set_name(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_set_typed_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_mutable_typed_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_typed_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_serialize(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_clear_instance_name(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_instance_name(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_clear_certificate_name(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_certificate_name(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_set_instance_name(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_set_certificate_name(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* ret = envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_serialize(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CombinedCertificateValidationContext_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_clear_default_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_default_validation_context(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_has_default_validation_context(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_clear_validation_context_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_sds_secret_config(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_has_validation_context_sds_secret_config(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_clear_validation_context_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_certificate_provider(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_has_validation_context_certificate_provider(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_clear_validation_context_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_has_validation_context_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_default_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext *msg, struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_mutable_default_validation_context(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_default_validation_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_default_validation_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_validation_context_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext *msg, struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_mutable_validation_context_sds_secret_config(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_sds_secret_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_validation_context_sds_secret_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_validation_context_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_mutable_validation_context_certificate_provider(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_certificate_provider(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProvider_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_validation_context_certificate_provider(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_validation_context_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext *msg, envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_mutable_validation_context_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance* sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_certificate_provider_instance(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CommonTlsContext__CertificateProviderInstance_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_set_validation_context_certificate_provider_instance(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
