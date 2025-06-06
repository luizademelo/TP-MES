
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_COMMON_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_COMMON_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/transport_sockets/tls/v3/common.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_transport_sockets_tls_v3_TlsParameters { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_TlsParameters;
typedef struct envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider;
typedef struct envoy_extensions_transport_sockets_tls_v3_TlsCertificate { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_TlsCertificate;
typedef struct envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys;
typedef struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance;
typedef struct envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher;
typedef struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext;
typedef struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts;
struct envoy_config_core_v3_DataSource;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_core_v3_WatchedDirectory;
struct envoy_type_matcher_v3_StringMatcher;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_UInt32Value;

typedef enum {
  envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_VERIFY_TRUST_CHAIN = 0,
  envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_ACCEPT_UNTRUSTED = 1
} envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_TrustChainVerification;

typedef enum {
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_SAN_TYPE_UNSPECIFIED = 0,
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_EMAIL = 1,
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_DNS = 2,
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_URI = 3,
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_IP_ADDRESS = 4,
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_OTHER_NAME = 5
} envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_SanType;

typedef enum {
  envoy_extensions_transport_sockets_tls_v3_TlsParameters_TLS_AUTO = 0,
  envoy_extensions_transport_sockets_tls_v3_TlsParameters_TLSv1_0 = 1,
  envoy_extensions_transport_sockets_tls_v3_TlsParameters_TLSv1_1 = 2,
  envoy_extensions_transport_sockets_tls_v3_TlsParameters_TLSv1_2 = 3,
  envoy_extensions_transport_sockets_tls_v3_TlsParameters_TLSv1_3 = 4
} envoy_extensions_transport_sockets_tls_v3_TlsParameters_TlsProtocol;

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsParameters* envoy_extensions_transport_sockets_tls_v3_TlsParameters_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_TlsParameters*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsParameters* envoy_extensions_transport_sockets_tls_v3_TlsParameters_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsParameters* ret = envoy_extensions_transport_sockets_tls_v3_TlsParameters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsParameters* envoy_extensions_transport_sockets_tls_v3_TlsParameters_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsParameters* ret = envoy_extensions_transport_sockets_tls_v3_TlsParameters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsParameters_serialize(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsParameters_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsParameters_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_clear_tls_minimum_protocol_version(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_transport_sockets_tls_v3_TlsParameters_tls_minimum_protocol_version(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_clear_tls_maximum_protocol_version(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_transport_sockets_tls_v3_TlsParameters_tls_maximum_protocol_version(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_clear_cipher_suites(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_transport_sockets_tls_v3_TlsParameters_cipher_suites(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsParameters_cipher_suites_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsParameters_cipher_suites_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_clear_ecdh_curves(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_transport_sockets_tls_v3_TlsParameters_ecdh_curves(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsParameters_ecdh_curves_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsParameters_ecdh_curves_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_clear_signature_algorithms(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_transport_sockets_tls_v3_TlsParameters_signature_algorithms(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsParameters_signature_algorithms_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsParameters_signature_algorithms_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_set_tls_minimum_protocol_version(envoy_extensions_transport_sockets_tls_v3_TlsParameters *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsParameters_set_tls_maximum_protocol_version(envoy_extensions_transport_sockets_tls_v3_TlsParameters *msg, int32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_TlsParameters_mutable_cipher_suites(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_TlsParameters_resize_cipher_suites(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsParameters_add_cipher_suites(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_TlsParameters_mutable_ecdh_curves(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_TlsParameters_resize_ecdh_curves(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsParameters_add_ecdh_curves(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_TlsParameters_mutable_signature_algorithms(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_TlsParameters_resize_signature_algorithms(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsParameters_add_signature_algorithms(envoy_extensions_transport_sockets_tls_v3_TlsParameters* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* ret = envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* ret = envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_serialize(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_config_type_typed_config = 3,
  envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_config_type_NOT_SET = 0
} envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_config_type_oneofcases;
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_config_type_oneofcases envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_config_type_case(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_clear_config_type(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_clear_provider_name(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_provider_name(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_clear_typed_config(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_typed_config(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_has_typed_config(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_clear_fallback(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_fallback(const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_set_provider_name(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_set_typed_config(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_mutable_typed_config(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_set_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_set_fallback(envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider *msg, bool value) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsCertificate* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_TlsCertificate*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsCertificate* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsCertificate* ret = envoy_extensions_transport_sockets_tls_v3_TlsCertificate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsCertificate* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsCertificate* ret = envoy_extensions_transport_sockets_tls_v3_TlsCertificate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_serialize(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsCertificate_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_certificate_chain(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_certificate_chain(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_certificate_chain(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_private_key(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_private_key(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_private_key(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_password(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_password(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_password(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_ocsp_staple(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_ocsp_staple(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_ocsp_staple(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* const* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_signed_certificate_timestamp(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_DataSource* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsCertificate_signed_certificate_timestamp_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsCertificate_signed_certificate_timestamp_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_private_key_provider(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_private_key_provider(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_private_key_provider(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_watched_directory(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_WatchedDirectory* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_watched_directory(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const struct envoy_config_core_v3_WatchedDirectory* default_val = NULL;
  const struct envoy_config_core_v3_WatchedDirectory* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__WatchedDirectory_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_watched_directory(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_clear_pkcs12(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_pkcs12(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_TlsCertificate_has_pkcs12(const envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_certificate_chain(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_certificate_chain(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_certificate_chain(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_certificate_chain(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_private_key(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_private_key(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_private_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_private_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_password(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_password(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_password(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_password(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_ocsp_staple(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_ocsp_staple(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_ocsp_staple(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_ocsp_staple(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_DataSource** envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_DataSource**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_DataSource** envoy_extensions_transport_sockets_tls_v3_TlsCertificate_resize_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_DataSource**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_add_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_private_key_provider(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_private_key_provider(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider* sub = (struct envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_private_key_provider(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__PrivateKeyProvider_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_private_key_provider(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_watched_directory(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, struct envoy_config_core_v3_WatchedDirectory* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__WatchedDirectory_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_WatchedDirectory* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_watched_directory(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_WatchedDirectory* sub = (struct envoy_config_core_v3_WatchedDirectory*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_watched_directory(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_WatchedDirectory*)_upb_Message_New(&envoy__config__core__v3__WatchedDirectory_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_watched_directory(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_pkcs12(envoy_extensions_transport_sockets_tls_v3_TlsCertificate *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsCertificate_mutable_pkcs12(envoy_extensions_transport_sockets_tls_v3_TlsCertificate* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_TlsCertificate_pkcs12(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_TlsCertificate_set_pkcs12(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* ret = envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* ret = envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_serialize(const envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__TlsSessionTicketKeys_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_clear_keys(envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* const* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_keys(const envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_DataSource* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_keys_upb_array(const envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_keys_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct envoy_config_core_v3_DataSource** envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_mutable_keys(envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_DataSource**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_DataSource** envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_resize_keys(envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_DataSource**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_add_keys(envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* ret = envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* ret = envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_serialize(const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_clear_instance_name(envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_instance_name(const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_clear_certificate_name(envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_certificate_name(const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_set_instance_name(envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_set_certificate_name(envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* ret = envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* ret = envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_serialize(const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_clear_san_type(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_san_type(const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_clear_matcher(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_matcher(const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_has_matcher(const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_clear_oid(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_oid(const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_set_san_type(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_set_matcher(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_mutable_matcher(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_set_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_set_oid(envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* ret = envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* ret = envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_serialize(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_trusted_ca(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_trusted_ca(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_trusted_ca(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_verify_certificate_hash(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_hash(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_hash_upb_array(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_hash_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_verify_certificate_spki(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_spki(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_spki_upb_array(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_spki_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_require_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_require_signed_certificate_timestamp(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_require_signed_certificate_timestamp(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_crl(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_crl(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(28, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_crl(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_allow_expired_certificate(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {8, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_allow_expired_certificate(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_match_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* const* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_subject_alt_names(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_matcher_v3_StringMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_subject_alt_names_upb_array(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_subject_alt_names_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_trust_chain_verification(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_trust_chain_verification(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {10, UPB_SIZE(36, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_watched_directory(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(40, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_WatchedDirectory* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_watched_directory(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const struct envoy_config_core_v3_WatchedDirectory* default_val = NULL;
  const struct envoy_config_core_v3_WatchedDirectory* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(40, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__WatchedDirectory_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_watched_directory(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(40, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_custom_validator_config(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(44, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_custom_validator_config(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(44, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_custom_validator_config(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(44, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_ca_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 80), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_ca_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(48, 80), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_ca_certificate_provider_instance(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 80), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_only_verify_leaf_cert_crl(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {14, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_only_verify_leaf_cert_crl(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {14, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_match_typed_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* const* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_typed_subject_alt_names(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_typed_subject_alt_names_upb_array(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_typed_subject_alt_names_mutable_upb_array(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_max_verify_depth(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 96), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_max_verify_depth(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(56, 96), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_max_verify_depth(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 96), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_clear_system_root_certs(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 104), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_system_root_certs(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* default_val = NULL;
  const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(60, 104), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_system_root_certs(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 104), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_trusted_ca(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_trusted_ca(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_trusted_ca(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_trusted_ca(msg, sub);
  }
  return sub;
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_verify_certificate_hash(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_resize_verify_certificate_hash(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_add_verify_certificate_hash(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_verify_certificate_spki(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_resize_verify_certificate_spki(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_add_verify_certificate_spki(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_require_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_require_signed_certificate_timestamp(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_require_signed_certificate_timestamp(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_require_signed_certificate_timestamp(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_crl(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_crl(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_crl(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_crl(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_allow_expired_certificate(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, bool value) {
  const upb_MiniTableField field = {8, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher** envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_match_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_matcher_v3_StringMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher** envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_resize_match_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_matcher_v3_StringMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_add_match_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(32, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_trust_chain_verification(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, int32_t value) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_watched_directory(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, struct envoy_config_core_v3_WatchedDirectory* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(40, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__WatchedDirectory_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_WatchedDirectory* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_watched_directory(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_WatchedDirectory* sub = (struct envoy_config_core_v3_WatchedDirectory*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_watched_directory(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_WatchedDirectory*)_upb_Message_New(&envoy__config__core__v3__WatchedDirectory_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_watched_directory(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_custom_validator_config(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(44, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_custom_validator_config(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_custom_validator_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_custom_validator_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_ca_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 80), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_ca_certificate_provider_instance(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance* sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_ca_certificate_provider_instance(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateProviderPluginInstance_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_ca_certificate_provider_instance(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_only_verify_leaf_cert_crl(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, bool value) {
  const upb_MiniTableField field = {14, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher** envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_match_typed_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t* size) {
  upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher** envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_resize_match_typed_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_add_match_typed_subject_alt_names(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  upb_MiniTableField field = {15, UPB_SIZE(52, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher* sub = (struct envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__SubjectAltNameMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_max_verify_depth(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 96), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_max_verify_depth(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_max_verify_depth(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_max_verify_depth(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_system_root_certs(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext *msg, envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 104), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_mutable_system_root_certs(envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext* msg, upb_Arena* arena) {
  struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts*)envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_system_root_certs(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_set_system_root_certs(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* ret = envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* ret = envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_serialize(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_serialize_ex(const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__tls__v3__CertificateValidationContext__SystemRootCerts_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
