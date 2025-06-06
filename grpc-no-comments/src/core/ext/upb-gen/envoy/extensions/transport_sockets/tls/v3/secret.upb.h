
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_SECRET_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_SECRET_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/transport_sockets/tls/v3/secret.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/common.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_transport_sockets_tls_v3_GenericSecret { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_GenericSecret;
typedef struct envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig;
typedef struct envoy_extensions_transport_sockets_tls_v3_Secret { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_Secret;
struct envoy_config_core_v3_ConfigSource;
struct envoy_config_core_v3_DataSource;
struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext;
struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate;
struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys;

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_GenericSecret* envoy_extensions_transport_sockets_tls_v3_GenericSecret_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_GenericSecret*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_GenericSecret* envoy_extensions_transport_sockets_tls_v3_GenericSecret_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_GenericSecret* ret = envoy_extensions_transport_sockets_tls_v3_GenericSecret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_GenericSecret* envoy_extensions_transport_sockets_tls_v3_GenericSecret_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_GenericSecret* ret = envoy_extensions_transport_sockets_tls_v3_GenericSecret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_GenericSecret_serialize(const envoy_extensions_transport_sockets_tls_v3_GenericSecret* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_GenericSecret_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_GenericSecret* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_GenericSecret_clear_secret(envoy_extensions_transport_sockets_tls_v3_GenericSecret* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_GenericSecret_secret(const envoy_extensions_transport_sockets_tls_v3_GenericSecret* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_GenericSecret_has_secret(const envoy_extensions_transport_sockets_tls_v3_GenericSecret* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_GenericSecret_set_secret(envoy_extensions_transport_sockets_tls_v3_GenericSecret *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_GenericSecret_mutable_secret(envoy_extensions_transport_sockets_tls_v3_GenericSecret* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_GenericSecret_secret(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_GenericSecret_set_secret(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* ret = envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* ret = envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_serialize(const envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SdsSecretConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_clear_name(envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_name(const envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_clear_sds_config(envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_sds_config(const envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_has_sds_config(const envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_set_name(envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_set_sds_config(envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_mutable_sds_config(envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_sds_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_SdsSecretConfig_set_sds_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_Secret* envoy_extensions_transport_sockets_tls_v3_Secret_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_Secret*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_Secret* envoy_extensions_transport_sockets_tls_v3_Secret_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_Secret* ret = envoy_extensions_transport_sockets_tls_v3_Secret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_Secret* envoy_extensions_transport_sockets_tls_v3_Secret_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_Secret* ret = envoy_extensions_transport_sockets_tls_v3_Secret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_Secret_serialize(const envoy_extensions_transport_sockets_tls_v3_Secret* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_Secret_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_Secret* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_transport_sockets_tls_v3_Secret_type_tls_certificate = 2,
  envoy_extensions_transport_sockets_tls_v3_Secret_type_session_ticket_keys = 3,
  envoy_extensions_transport_sockets_tls_v3_Secret_type_validation_context = 4,
  envoy_extensions_transport_sockets_tls_v3_Secret_type_generic_secret = 5,
  envoy_extensions_transport_sockets_tls_v3_Secret_type_NOT_SET = 0
} envoy_extensions_transport_sockets_tls_v3_Secret_type_oneofcases;
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_Secret_type_oneofcases envoy_extensions_transport_sockets_tls_v3_Secret_type_case(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_Secret_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_clear_type(envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_clear_name(envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_Secret_name(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_clear_tls_certificate(envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* envoy_extensions_transport_sockets_tls_v3_Secret_tls_certificate(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_Secret_has_tls_certificate(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_clear_session_ticket_keys(envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_Secret_session_ticket_keys(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_Secret_has_session_ticket_keys(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_clear_validation_context(envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_Secret_validation_context(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* default_val = NULL;
  const struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_Secret_has_validation_context(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_clear_generic_secret(envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_GenericSecret* envoy_extensions_transport_sockets_tls_v3_Secret_generic_secret(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const envoy_extensions_transport_sockets_tls_v3_GenericSecret* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_GenericSecret* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_Secret_has_generic_secret(const envoy_extensions_transport_sockets_tls_v3_Secret* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_set_name(envoy_extensions_transport_sockets_tls_v3_Secret *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_set_tls_certificate(envoy_extensions_transport_sockets_tls_v3_Secret *msg, struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* envoy_extensions_transport_sockets_tls_v3_Secret_mutable_tls_certificate(envoy_extensions_transport_sockets_tls_v3_Secret* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate* sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate*)envoy_extensions_transport_sockets_tls_v3_Secret_tls_certificate(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_Secret_set_tls_certificate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_set_session_ticket_keys(envoy_extensions_transport_sockets_tls_v3_Secret *msg, struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_Secret_mutable_session_ticket_keys(envoy_extensions_transport_sockets_tls_v3_Secret* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys*)envoy_extensions_transport_sockets_tls_v3_Secret_session_ticket_keys(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_Secret_set_session_ticket_keys(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_set_validation_context(envoy_extensions_transport_sockets_tls_v3_Secret *msg, struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_Secret_mutable_validation_context(envoy_extensions_transport_sockets_tls_v3_Secret* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)envoy_extensions_transport_sockets_tls_v3_Secret_validation_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_Secret_set_validation_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_Secret_set_generic_secret(envoy_extensions_transport_sockets_tls_v3_Secret *msg, envoy_extensions_transport_sockets_tls_v3_GenericSecret* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_GenericSecret* envoy_extensions_transport_sockets_tls_v3_Secret_mutable_generic_secret(envoy_extensions_transport_sockets_tls_v3_Secret* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_GenericSecret* sub = (struct envoy_extensions_transport_sockets_tls_v3_GenericSecret*)envoy_extensions_transport_sockets_tls_v3_Secret_generic_secret(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_GenericSecret*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__GenericSecret_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_Secret_set_generic_secret(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
