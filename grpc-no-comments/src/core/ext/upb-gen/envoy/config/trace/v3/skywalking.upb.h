
#ifndef ENVOY_CONFIG_TRACE_V3_SKYWALKING_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_TRACE_V3_SKYWALKING_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/skywalking.upb_minitable.h"

#include "envoy/config/core/v3/grpc_service.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_trace_v3_SkyWalkingConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_SkyWalkingConfig;
typedef struct envoy_config_trace_v3_ClientConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_ClientConfig;
struct envoy_config_core_v3_GrpcService;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_config_trace_v3_SkyWalkingConfig* envoy_config_trace_v3_SkyWalkingConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_SkyWalkingConfig*)_upb_Message_New(&envoy__config__trace__v3__SkyWalkingConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_SkyWalkingConfig* envoy_config_trace_v3_SkyWalkingConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_SkyWalkingConfig* ret = envoy_config_trace_v3_SkyWalkingConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__SkyWalkingConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_SkyWalkingConfig* envoy_config_trace_v3_SkyWalkingConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_SkyWalkingConfig* ret = envoy_config_trace_v3_SkyWalkingConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__SkyWalkingConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_SkyWalkingConfig_serialize(const envoy_config_trace_v3_SkyWalkingConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__SkyWalkingConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_SkyWalkingConfig_serialize_ex(const envoy_config_trace_v3_SkyWalkingConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__SkyWalkingConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_SkyWalkingConfig_clear_grpc_service(envoy_config_trace_v3_SkyWalkingConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_GrpcService* envoy_config_trace_v3_SkyWalkingConfig_grpc_service(const envoy_config_trace_v3_SkyWalkingConfig* msg) {
  const struct envoy_config_core_v3_GrpcService* default_val = NULL;
  const struct envoy_config_core_v3_GrpcService* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_SkyWalkingConfig_has_grpc_service(const envoy_config_trace_v3_SkyWalkingConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_trace_v3_SkyWalkingConfig_clear_client_config(envoy_config_trace_v3_SkyWalkingConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_trace_v3_ClientConfig* envoy_config_trace_v3_SkyWalkingConfig_client_config(const envoy_config_trace_v3_SkyWalkingConfig* msg) {
  const envoy_config_trace_v3_ClientConfig* default_val = NULL;
  const envoy_config_trace_v3_ClientConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__ClientConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_SkyWalkingConfig_has_client_config(const envoy_config_trace_v3_SkyWalkingConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_SkyWalkingConfig_set_grpc_service(envoy_config_trace_v3_SkyWalkingConfig *msg, struct envoy_config_core_v3_GrpcService* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService* envoy_config_trace_v3_SkyWalkingConfig_mutable_grpc_service(envoy_config_trace_v3_SkyWalkingConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService* sub = (struct envoy_config_core_v3_GrpcService*)envoy_config_trace_v3_SkyWalkingConfig_grpc_service(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService*)_upb_Message_New(&envoy__config__core__v3__GrpcService_msg_init, arena);
    if (sub) envoy_config_trace_v3_SkyWalkingConfig_set_grpc_service(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_trace_v3_SkyWalkingConfig_set_client_config(envoy_config_trace_v3_SkyWalkingConfig *msg, envoy_config_trace_v3_ClientConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__ClientConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_trace_v3_ClientConfig* envoy_config_trace_v3_SkyWalkingConfig_mutable_client_config(envoy_config_trace_v3_SkyWalkingConfig* msg, upb_Arena* arena) {
  struct envoy_config_trace_v3_ClientConfig* sub = (struct envoy_config_trace_v3_ClientConfig*)envoy_config_trace_v3_SkyWalkingConfig_client_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_trace_v3_ClientConfig*)_upb_Message_New(&envoy__config__trace__v3__ClientConfig_msg_init, arena);
    if (sub) envoy_config_trace_v3_SkyWalkingConfig_set_client_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_trace_v3_ClientConfig* envoy_config_trace_v3_ClientConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_ClientConfig*)_upb_Message_New(&envoy__config__trace__v3__ClientConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_ClientConfig* envoy_config_trace_v3_ClientConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_ClientConfig* ret = envoy_config_trace_v3_ClientConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__ClientConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_ClientConfig* envoy_config_trace_v3_ClientConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_ClientConfig* ret = envoy_config_trace_v3_ClientConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__ClientConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_ClientConfig_serialize(const envoy_config_trace_v3_ClientConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__ClientConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_ClientConfig_serialize_ex(const envoy_config_trace_v3_ClientConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__ClientConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_trace_v3_ClientConfig_backend_token_specifier_backend_token = 3,
  envoy_config_trace_v3_ClientConfig_backend_token_specifier_NOT_SET = 0
} envoy_config_trace_v3_ClientConfig_backend_token_specifier_oneofcases;
UPB_INLINE envoy_config_trace_v3_ClientConfig_backend_token_specifier_oneofcases envoy_config_trace_v3_ClientConfig_backend_token_specifier_case(const envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_trace_v3_ClientConfig_backend_token_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_clear_backend_token_specifier(envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__trace__v3__ClientConfig_msg_init, &field);
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_clear_service_name(envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_ClientConfig_service_name(const envoy_config_trace_v3_ClientConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_clear_instance_name(envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_ClientConfig_instance_name(const envoy_config_trace_v3_ClientConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_clear_backend_token(envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_ClientConfig_backend_token(const envoy_config_trace_v3_ClientConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_ClientConfig_has_backend_token(const envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_clear_max_cache_size(envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_trace_v3_ClientConfig_max_cache_size(const envoy_config_trace_v3_ClientConfig* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_ClientConfig_has_max_cache_size(const envoy_config_trace_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_ClientConfig_set_service_name(envoy_config_trace_v3_ClientConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_set_instance_name(envoy_config_trace_v3_ClientConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_set_backend_token(envoy_config_trace_v3_ClientConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ClientConfig_set_max_cache_size(envoy_config_trace_v3_ClientConfig *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_trace_v3_ClientConfig_mutable_max_cache_size(envoy_config_trace_v3_ClientConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_trace_v3_ClientConfig_max_cache_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_trace_v3_ClientConfig_set_max_cache_size(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
