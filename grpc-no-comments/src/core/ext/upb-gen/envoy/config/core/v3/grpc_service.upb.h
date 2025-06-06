
#ifndef ENVOY_CONFIG_CORE_V3_GRPC_SERVICE_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_GRPC_SERVICE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/grpc_service.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/empty.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_GrpcService { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService;
typedef struct envoy_config_core_v3_GrpcService_EnvoyGrpc { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_EnvoyGrpc;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs;
typedef struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value;
struct envoy_config_core_v3_DataSource;
struct envoy_config_core_v3_HeaderValue;
struct envoy_config_core_v3_RetryPolicy;
struct google_protobuf_Any;
struct google_protobuf_Duration;
struct google_protobuf_Empty;
struct google_protobuf_Struct;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_config_core_v3_GrpcService* envoy_config_core_v3_GrpcService_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService*)_upb_Message_New(&envoy__config__core__v3__GrpcService_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService* envoy_config_core_v3_GrpcService_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService* ret = envoy_config_core_v3_GrpcService_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService* envoy_config_core_v3_GrpcService_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService* ret = envoy_config_core_v3_GrpcService_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_serialize(const envoy_config_core_v3_GrpcService* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_serialize_ex(const envoy_config_core_v3_GrpcService* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_GrpcService_target_specifier_envoy_grpc = 1,
  envoy_config_core_v3_GrpcService_target_specifier_google_grpc = 2,
  envoy_config_core_v3_GrpcService_target_specifier_NOT_SET = 0
} envoy_config_core_v3_GrpcService_target_specifier_oneofcases;
UPB_INLINE envoy_config_core_v3_GrpcService_target_specifier_oneofcases envoy_config_core_v3_GrpcService_target_specifier_case(const envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_GrpcService_target_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_clear_target_specifier(envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_clear_envoy_grpc(envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_EnvoyGrpc* envoy_config_core_v3_GrpcService_envoy_grpc(const envoy_config_core_v3_GrpcService* msg) {
  const envoy_config_core_v3_GrpcService_EnvoyGrpc* default_val = NULL;
  const envoy_config_core_v3_GrpcService_EnvoyGrpc* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_has_envoy_grpc(const envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_clear_google_grpc(envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc* envoy_config_core_v3_GrpcService_google_grpc(const envoy_config_core_v3_GrpcService* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_has_google_grpc(const envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_clear_timeout(envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_GrpcService_timeout(const envoy_config_core_v3_GrpcService* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_has_timeout(const envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_clear_initial_metadata(envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValue* const* envoy_config_core_v3_GrpcService_initial_metadata(const envoy_config_core_v3_GrpcService* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_HeaderValue* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_GrpcService_initial_metadata_upb_array(const envoy_config_core_v3_GrpcService* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_GrpcService_initial_metadata_mutable_upb_array(envoy_config_core_v3_GrpcService* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_clear_retry_policy(envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_GrpcService_retry_policy(const envoy_config_core_v3_GrpcService* msg) {
  const struct envoy_config_core_v3_RetryPolicy* default_val = NULL;
  const struct envoy_config_core_v3_RetryPolicy* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_has_retry_policy(const envoy_config_core_v3_GrpcService* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_set_envoy_grpc(envoy_config_core_v3_GrpcService *msg, envoy_config_core_v3_GrpcService_EnvoyGrpc* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_EnvoyGrpc* envoy_config_core_v3_GrpcService_mutable_envoy_grpc(envoy_config_core_v3_GrpcService* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_EnvoyGrpc* sub = (struct envoy_config_core_v3_GrpcService_EnvoyGrpc*)envoy_config_core_v3_GrpcService_envoy_grpc(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_EnvoyGrpc*)_upb_Message_New(&envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_set_envoy_grpc(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_set_google_grpc(envoy_config_core_v3_GrpcService *msg, envoy_config_core_v3_GrpcService_GoogleGrpc* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 40), UPB_SIZE(-25, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc* envoy_config_core_v3_GrpcService_mutable_google_grpc(envoy_config_core_v3_GrpcService* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc*)envoy_config_core_v3_GrpcService_google_grpc(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_set_google_grpc(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_set_timeout(envoy_config_core_v3_GrpcService *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_GrpcService_mutable_timeout(envoy_config_core_v3_GrpcService* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_GrpcService_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_set_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValue** envoy_config_core_v3_GrpcService_mutable_initial_metadata(envoy_config_core_v3_GrpcService* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_HeaderValue**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_HeaderValue** envoy_config_core_v3_GrpcService_resize_initial_metadata(envoy_config_core_v3_GrpcService* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValue**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValue* envoy_config_core_v3_GrpcService_add_initial_metadata(envoy_config_core_v3_GrpcService* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 24), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HeaderValue* sub = (struct envoy_config_core_v3_HeaderValue*)_upb_Message_New(&envoy__config__core__v3__HeaderValue_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_set_retry_policy(envoy_config_core_v3_GrpcService *msg, struct envoy_config_core_v3_RetryPolicy* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_GrpcService_mutable_retry_policy(envoy_config_core_v3_GrpcService* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RetryPolicy* sub = (struct envoy_config_core_v3_RetryPolicy*)envoy_config_core_v3_GrpcService_retry_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RetryPolicy*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_set_retry_policy(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_GrpcService_EnvoyGrpc* envoy_config_core_v3_GrpcService_EnvoyGrpc_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_EnvoyGrpc*)_upb_Message_New(&envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_EnvoyGrpc* envoy_config_core_v3_GrpcService_EnvoyGrpc_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_EnvoyGrpc* ret = envoy_config_core_v3_GrpcService_EnvoyGrpc_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_EnvoyGrpc* envoy_config_core_v3_GrpcService_EnvoyGrpc_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_EnvoyGrpc* ret = envoy_config_core_v3_GrpcService_EnvoyGrpc_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_EnvoyGrpc_serialize(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_EnvoyGrpc_serialize_ex(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__EnvoyGrpc_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_clear_cluster_name(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_EnvoyGrpc_cluster_name(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_clear_authority(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_EnvoyGrpc_authority(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_clear_retry_policy(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_GrpcService_EnvoyGrpc_retry_policy(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const struct envoy_config_core_v3_RetryPolicy* default_val = NULL;
  const struct envoy_config_core_v3_RetryPolicy* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_EnvoyGrpc_has_retry_policy(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_clear_max_receive_message_length(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_GrpcService_EnvoyGrpc_max_receive_message_length(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_EnvoyGrpc_has_max_receive_message_length(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_clear_skip_envoy_headers(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_EnvoyGrpc_skip_envoy_headers(const envoy_config_core_v3_GrpcService_EnvoyGrpc* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_set_cluster_name(envoy_config_core_v3_GrpcService_EnvoyGrpc *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_set_authority(envoy_config_core_v3_GrpcService_EnvoyGrpc *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_set_retry_policy(envoy_config_core_v3_GrpcService_EnvoyGrpc *msg, struct envoy_config_core_v3_RetryPolicy* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_GrpcService_EnvoyGrpc_mutable_retry_policy(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RetryPolicy* sub = (struct envoy_config_core_v3_RetryPolicy*)envoy_config_core_v3_GrpcService_EnvoyGrpc_retry_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RetryPolicy*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_EnvoyGrpc_set_retry_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_set_max_receive_message_length(envoy_config_core_v3_GrpcService_EnvoyGrpc *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_GrpcService_EnvoyGrpc_mutable_max_receive_message_length(envoy_config_core_v3_GrpcService_EnvoyGrpc* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_GrpcService_EnvoyGrpc_max_receive_message_length(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_EnvoyGrpc_set_max_receive_message_length(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_EnvoyGrpc_set_skip_envoy_headers(envoy_config_core_v3_GrpcService_EnvoyGrpc *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc* envoy_config_core_v3_GrpcService_GoogleGrpc_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc* envoy_config_core_v3_GrpcService_GoogleGrpc_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc* envoy_config_core_v3_GrpcService_GoogleGrpc_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_target_uri(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_target_uri(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_channel_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_channel_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_has_channel_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_call_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* const* envoy_config_core_v3_GrpcService_GoogleGrpc_call_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_GrpcService_GoogleGrpc_call_credentials_upb_array(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_GrpcService_GoogleGrpc_call_credentials_mutable_upb_array(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_stat_prefix(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_stat_prefix(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_credentials_factory_name(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {5, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_credentials_factory_name(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_config(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_core_v3_GrpcService_GoogleGrpc_config(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_has_config(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_per_stream_buffer_limit_bytes(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_GrpcService_GoogleGrpc_per_stream_buffer_limit_bytes(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_has_per_stream_buffer_limit_bytes(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_clear_channel_args(envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* envoy_config_core_v3_GrpcService_GoogleGrpc_channel_args(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(28, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_has_channel_args(const envoy_config_core_v3_GrpcService_GoogleGrpc* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_target_uri(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_channel_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_mutable_channel_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials*)envoy_config_core_v3_GrpcService_GoogleGrpc_channel_credentials(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_set_channel_credentials(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials** envoy_config_core_v3_GrpcService_GoogleGrpc_mutable_call_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials** envoy_config_core_v3_GrpcService_GoogleGrpc_resize_call_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_add_call_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_stat_prefix(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_credentials_factory_name(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_config(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_core_v3_GrpcService_GoogleGrpc_mutable_config(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_core_v3_GrpcService_GoogleGrpc_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_set_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_per_stream_buffer_limit_bytes(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_GrpcService_GoogleGrpc_mutable_per_stream_buffer_limit_bytes(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_GrpcService_GoogleGrpc_per_stream_buffer_limit_bytes(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_set_per_stream_buffer_limit_bytes(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_set_channel_args(envoy_config_core_v3_GrpcService_GoogleGrpc *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* envoy_config_core_v3_GrpcService_GoogleGrpc_mutable_channel_args(envoy_config_core_v3_GrpcService_GoogleGrpc* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs*)envoy_config_core_v3_GrpcService_GoogleGrpc_channel_args(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_set_channel_args(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_clear_root_certs(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_root_certs(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_has_root_certs(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_clear_private_key(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_private_key(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_has_private_key(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_clear_cert_chain(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_cert_chain(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_has_cert_chain(const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_set_root_certs(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_mutable_root_certs(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_root_certs(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_set_root_certs(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_set_private_key(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_mutable_private_key(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_private_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_set_private_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_set_cert_chain(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_mutable_cert_chain(envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_cert_chain(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_set_cert_chain(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_ssl_credentials = 1,
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_google_default = 2,
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_local_credentials = 3,
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_NOT_SET = 0
} envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_oneofcases;
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_oneofcases envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_case(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_credential_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_clear_credential_specifier(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelCredentials_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_clear_ssl_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_ssl_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_has_ssl_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_clear_google_default(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Empty* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_google_default(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const struct google_protobuf_Empty* default_val = NULL;
  const struct google_protobuf_Empty* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_has_google_default(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_clear_local_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_local_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_has_local_credentials(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_set_ssl_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_mutable_ssl_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials*)envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_ssl_credentials(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__SslCredentials_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_set_ssl_credentials(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_set_google_default(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials *msg, struct google_protobuf_Empty* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Empty* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_mutable_google_default(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg, upb_Arena* arena) {
  struct google_protobuf_Empty* sub = (struct google_protobuf_Empty*)envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_google_default(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Empty*)_upb_Message_New(&google__protobuf__Empty_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_set_google_default(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_set_local_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_mutable_local_credentials(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials*)envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_local_credentials(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__GoogleLocalCredentials_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_set_local_credentials(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_access_token = 1,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_google_compute_engine = 2,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_google_refresh_token = 3,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_service_account_jwt_access = 4,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_google_iam = 5,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_from_plugin = 6,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_sts_service = 7,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_NOT_SET = 0
} envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_oneofcases;
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_oneofcases envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_case(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_credential_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_credential_specifier(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_access_token(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_access_token(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_access_token(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_google_compute_engine(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Empty* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_google_compute_engine(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const struct google_protobuf_Empty* default_val = NULL;
  const struct google_protobuf_Empty* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_google_compute_engine(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_google_refresh_token(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_google_refresh_token(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_google_refresh_token(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_service_account_jwt_access(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_service_account_jwt_access(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_service_account_jwt_access(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_google_iam(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_google_iam(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_google_iam(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_from_plugin(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_from_plugin(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_from_plugin(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_clear_sts_service(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_sts_service(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* default_val = NULL;
  const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_has_sts_service(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_access_token(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_google_compute_engine(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, struct google_protobuf_Empty* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Empty* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_mutable_google_compute_engine(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, upb_Arena* arena) {
  struct google_protobuf_Empty* sub = (struct google_protobuf_Empty*)envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_google_compute_engine(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Empty*)_upb_Message_New(&google__protobuf__Empty_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_google_compute_engine(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_google_refresh_token(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_service_account_jwt_access(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_mutable_service_account_jwt_access(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials*)envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_service_account_jwt_access(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_service_account_jwt_access(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_google_iam(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_mutable_google_iam(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials*)envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_google_iam(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_google_iam(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_from_plugin(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_mutable_from_plugin(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin*)envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_from_plugin(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_from_plugin(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_sts_service(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials *msg, envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_mutable_sts_service(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService*)envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_sts_service(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_set_sts_service(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__ServiceAccountJWTAccessCredentials_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_clear_json_key(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_json_key(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_clear_token_lifetime_seconds(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_token_lifetime_seconds(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_set_json_key(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_set_token_lifetime_seconds(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__GoogleIAMCredentials_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_clear_authorization_token(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_authorization_token(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_clear_authority_selector(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_authority_selector(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_set_authorization_token(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_set_authority_selector(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_config_type_typed_config = 3,
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_config_type_NOT_SET = 0
} envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_config_type_oneofcases;
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_config_type_oneofcases envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_config_type_case(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_clear_config_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__MetadataCredentialsFromPlugin_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_clear_name(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_name(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_clear_typed_config(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_typed_config(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_has_typed_config(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_set_name(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_set_typed_config(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_mutable_typed_config(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__CallCredentials__StsService_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_token_exchange_service_uri(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_token_exchange_service_uri(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_resource(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_resource(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_audience(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_audience(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_scope(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(32, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_scope(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(32, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_requested_token_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_requested_token_type(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_subject_token_path(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_subject_token_path(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(48, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_subject_token_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_subject_token_type(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(56, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_actor_token_path(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(64, 120), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_actor_token_path(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(64, 120), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_clear_actor_token_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(72, 136), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_actor_token_type(const envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(72, 136), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_token_exchange_service_uri(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_resource(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_audience(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_scope(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(32, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_requested_token_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_subject_token_path(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_subject_token_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_actor_token_path(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(64, 120), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_set_actor_token_type(envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(72, 136), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_clear_args(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_size(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_get(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, upb_StringView key, envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value** val) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__ArgsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_next(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, upb_StringView* key, const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value** val,
                           size_t* iter) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__ArgsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_upb_map(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__ArgsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_mutable_upb_map(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__ArgsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value*), a);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_clear(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_set(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, upb_StringView key, envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* val, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__ArgsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_args_delete(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs* msg, upb_StringView key) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_new(upb_Arena* arena) {
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value*)_upb_Message_New(&envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* ret = envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_serialize(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_serialize_ex(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_string_value = 1,
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_int_value = 2,
  envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_NOT_SET = 0
} envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_oneofcases;
UPB_INLINE envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_oneofcases envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_case(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_value_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_clear_value_specifier(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__GrpcService__GoogleGrpc__ChannelArgs__Value_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_clear_string_value(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_string_value(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_has_string_value(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_clear_int_value(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_int_value(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_has_int_value(const envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value* msg) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_set_string_value(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_set_int_value(envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value *msg, int64_t value) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
