
#ifndef ENVOY_CONFIG_CORE_V3_HEALTH_CHECK_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_HEALTH_CHECK_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/health_check.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/event_service_config.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/proxy_protocol.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/v3/http.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_HealthStatusSet { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthStatusSet;
typedef struct envoy_config_core_v3_HealthCheck { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck;
typedef struct envoy_config_core_v3_HealthCheck_Payload { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_Payload;
typedef struct envoy_config_core_v3_HealthCheck_HttpHealthCheck { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_HttpHealthCheck;
typedef struct envoy_config_core_v3_HealthCheck_TcpHealthCheck { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_TcpHealthCheck;
typedef struct envoy_config_core_v3_HealthCheck_RedisHealthCheck { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_RedisHealthCheck;
typedef struct envoy_config_core_v3_HealthCheck_GrpcHealthCheck { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_GrpcHealthCheck;
typedef struct envoy_config_core_v3_HealthCheck_CustomHealthCheck { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_CustomHealthCheck;
typedef struct envoy_config_core_v3_HealthCheck_TlsOptions { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HealthCheck_TlsOptions;
struct envoy_config_core_v3_EventServiceConfig;
struct envoy_config_core_v3_HeaderValueOption;
struct envoy_config_core_v3_ProxyProtocolConfig;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_type_matcher_v3_StringMatcher;
struct envoy_type_v3_Int64Range;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_Struct;
struct google_protobuf_UInt32Value;
struct google_protobuf_UInt64Value;

typedef enum {
  envoy_config_core_v3_UNKNOWN = 0,
  envoy_config_core_v3_HEALTHY = 1,
  envoy_config_core_v3_UNHEALTHY = 2,
  envoy_config_core_v3_DRAINING = 3,
  envoy_config_core_v3_TIMEOUT = 4,
  envoy_config_core_v3_DEGRADED = 5
} envoy_config_core_v3_HealthStatus;

UPB_INLINE envoy_config_core_v3_HealthStatusSet* envoy_config_core_v3_HealthStatusSet_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthStatusSet*)_upb_Message_New(&envoy__config__core__v3__HealthStatusSet_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthStatusSet* envoy_config_core_v3_HealthStatusSet_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthStatusSet* ret = envoy_config_core_v3_HealthStatusSet_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthStatusSet_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthStatusSet* envoy_config_core_v3_HealthStatusSet_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthStatusSet* ret = envoy_config_core_v3_HealthStatusSet_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthStatusSet_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthStatusSet_serialize(const envoy_config_core_v3_HealthStatusSet* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthStatusSet_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthStatusSet_serialize_ex(const envoy_config_core_v3_HealthStatusSet* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthStatusSet_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HealthStatusSet_clear_statuses(envoy_config_core_v3_HealthStatusSet* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* envoy_config_core_v3_HealthStatusSet_statuses(const envoy_config_core_v3_HealthStatusSet* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthStatusSet_statuses_upb_array(const envoy_config_core_v3_HealthStatusSet* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthStatusSet_statuses_mutable_upb_array(envoy_config_core_v3_HealthStatusSet* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE int32_t* envoy_config_core_v3_HealthStatusSet_mutable_statuses(envoy_config_core_v3_HealthStatusSet* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* envoy_config_core_v3_HealthStatusSet_resize_statuses(envoy_config_core_v3_HealthStatusSet* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_core_v3_HealthStatusSet_add_statuses(envoy_config_core_v3_HealthStatusSet* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_config_core_v3_HealthCheck* envoy_config_core_v3_HealthCheck_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck* envoy_config_core_v3_HealthCheck_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck* ret = envoy_config_core_v3_HealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck* envoy_config_core_v3_HealthCheck_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck* ret = envoy_config_core_v3_HealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_serialize(const envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_serialize_ex(const envoy_config_core_v3_HealthCheck* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_HealthCheck_health_checker_http_health_check = 8,
  envoy_config_core_v3_HealthCheck_health_checker_tcp_health_check = 9,
  envoy_config_core_v3_HealthCheck_health_checker_grpc_health_check = 11,
  envoy_config_core_v3_HealthCheck_health_checker_custom_health_check = 13,
  envoy_config_core_v3_HealthCheck_health_checker_NOT_SET = 0
} envoy_config_core_v3_HealthCheck_health_checker_oneofcases;
UPB_INLINE envoy_config_core_v3_HealthCheck_health_checker_oneofcases envoy_config_core_v3_HealthCheck_health_checker_case(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HealthCheck_health_checker_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_health_checker(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_timeout(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_timeout(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_timeout(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_interval(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_interval_jitter(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_interval_jitter(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_interval_jitter(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_unhealthy_threshold(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_HealthCheck_unhealthy_threshold(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_unhealthy_threshold(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_healthy_threshold(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 72), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_HealthCheck_healthy_threshold(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 72), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_healthy_threshold(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 72), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_alt_port(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 80), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_HealthCheck_alt_port(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 80), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_alt_port(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 80), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_reuse_connection(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 88), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_core_v3_HealthCheck_reuse_connection(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 88), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_reuse_connection(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 88), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_http_health_check(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_HttpHealthCheck* envoy_config_core_v3_HealthCheck_http_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_HttpHealthCheck* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_HttpHealthCheck* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_http_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_tcp_health_check(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_TcpHealthCheck* envoy_config_core_v3_HealthCheck_tcp_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_TcpHealthCheck* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_TcpHealthCheck* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_tcp_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_grpc_health_check(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* envoy_config_core_v3_HealthCheck_grpc_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_grpc_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_no_traffic_interval(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 96), 71, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_no_traffic_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(40, 96), 71, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_no_traffic_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 96), 71, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_custom_health_check(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_CustomHealthCheck* envoy_config_core_v3_HealthCheck_custom_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_CustomHealthCheck* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_CustomHealthCheck* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_custom_health_check(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_unhealthy_interval(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(44, 104), 72, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_unhealthy_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(44, 104), 72, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_unhealthy_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(44, 104), 72, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_unhealthy_edge_interval(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(48, 112), 73, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_unhealthy_edge_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(48, 112), 73, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_unhealthy_edge_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(48, 112), 73, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_healthy_edge_interval(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(52, 120), 74, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_healthy_edge_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(52, 120), 74, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_healthy_edge_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(52, 120), 74, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_event_log_path(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(92, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_event_log_path(const envoy_config_core_v3_HealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {17, UPB_SIZE(92, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_interval_jitter_percent(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(56, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_core_v3_HealthCheck_interval_jitter_percent(const envoy_config_core_v3_HealthCheck* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {18, UPB_SIZE(56, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_always_log_health_check_failures(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_always_log_health_check_failures(const envoy_config_core_v3_HealthCheck* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_initial_jitter(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(60, 128), 75, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_initial_jitter(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(60, 128), 75, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_initial_jitter(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(60, 128), 75, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_tls_options(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(64, 136), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_TlsOptions* envoy_config_core_v3_HealthCheck_tls_options(const envoy_config_core_v3_HealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_TlsOptions* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_TlsOptions* ret;
  const upb_MiniTableField field = {21, UPB_SIZE(64, 136), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__TlsOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_tls_options(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(64, 136), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_event_service(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(68, 144), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_EventServiceConfig* envoy_config_core_v3_HealthCheck_event_service(const envoy_config_core_v3_HealthCheck* msg) {
  const struct envoy_config_core_v3_EventServiceConfig* default_val = NULL;
  const struct envoy_config_core_v3_EventServiceConfig* ret;
  const upb_MiniTableField field = {22, UPB_SIZE(68, 144), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__EventServiceConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_event_service(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(68, 144), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_transport_socket_match_criteria(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(72, 152), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_core_v3_HealthCheck_transport_socket_match_criteria(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {23, UPB_SIZE(72, 152), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_transport_socket_match_criteria(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(72, 152), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_no_traffic_healthy_interval(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(76, 160), 79, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_no_traffic_healthy_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {24, UPB_SIZE(76, 160), 79, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_has_no_traffic_healthy_interval(const envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(76, 160), 79, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_event_logger(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_config_core_v3_HealthCheck_event_logger(const envoy_config_core_v3_HealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_TypedExtensionConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_event_logger_upb_array(const envoy_config_core_v3_HealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_event_logger_mutable_upb_array(envoy_config_core_v3_HealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_clear_always_log_health_check_success(envoy_config_core_v3_HealthCheck* msg) {
  const upb_MiniTableField field = {26, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_always_log_health_check_success(const envoy_config_core_v3_HealthCheck* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {26, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_set_timeout(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_timeout(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_interval(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_interval(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_interval_jitter(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_interval_jitter(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_interval_jitter(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_interval_jitter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_unhealthy_threshold(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_HealthCheck_mutable_unhealthy_threshold(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_HealthCheck_unhealthy_threshold(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_unhealthy_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_healthy_threshold(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 72), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_HealthCheck_mutable_healthy_threshold(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_HealthCheck_healthy_threshold(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_healthy_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_alt_port(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 80), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_HealthCheck_mutable_alt_port(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_HealthCheck_alt_port(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_alt_port(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_reuse_connection(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 88), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_core_v3_HealthCheck_mutable_reuse_connection(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_core_v3_HealthCheck_reuse_connection(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_reuse_connection(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_http_health_check(envoy_config_core_v3_HealthCheck *msg, envoy_config_core_v3_HealthCheck_HttpHealthCheck* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_HttpHealthCheck* envoy_config_core_v3_HealthCheck_mutable_http_health_check(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_HttpHealthCheck* sub = (struct envoy_config_core_v3_HealthCheck_HttpHealthCheck*)envoy_config_core_v3_HealthCheck_http_health_check(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_HttpHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_http_health_check(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_tcp_health_check(envoy_config_core_v3_HealthCheck *msg, envoy_config_core_v3_HealthCheck_TcpHealthCheck* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_TcpHealthCheck* envoy_config_core_v3_HealthCheck_mutable_tcp_health_check(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_TcpHealthCheck* sub = (struct envoy_config_core_v3_HealthCheck_TcpHealthCheck*)envoy_config_core_v3_HealthCheck_tcp_health_check(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_TcpHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_tcp_health_check(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_grpc_health_check(envoy_config_core_v3_HealthCheck *msg, envoy_config_core_v3_HealthCheck_GrpcHealthCheck* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_GrpcHealthCheck* envoy_config_core_v3_HealthCheck_mutable_grpc_health_check(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_GrpcHealthCheck* sub = (struct envoy_config_core_v3_HealthCheck_GrpcHealthCheck*)envoy_config_core_v3_HealthCheck_grpc_health_check(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_GrpcHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_grpc_health_check(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_no_traffic_interval(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 96), 71, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_no_traffic_interval(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_no_traffic_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_no_traffic_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_custom_health_check(envoy_config_core_v3_HealthCheck *msg, envoy_config_core_v3_HealthCheck_CustomHealthCheck* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(88, 176), UPB_SIZE(-85, -17), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_CustomHealthCheck* envoy_config_core_v3_HealthCheck_mutable_custom_health_check(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_CustomHealthCheck* sub = (struct envoy_config_core_v3_HealthCheck_CustomHealthCheck*)envoy_config_core_v3_HealthCheck_custom_health_check(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_CustomHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_custom_health_check(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_unhealthy_interval(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(44, 104), 72, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_unhealthy_interval(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_unhealthy_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_unhealthy_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_unhealthy_edge_interval(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(48, 112), 73, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_unhealthy_edge_interval(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_unhealthy_edge_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_unhealthy_edge_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_healthy_edge_interval(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(52, 120), 74, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_healthy_edge_interval(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_healthy_edge_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_healthy_edge_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_event_log_path(envoy_config_core_v3_HealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {17, UPB_SIZE(92, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_interval_jitter_percent(envoy_config_core_v3_HealthCheck *msg, uint32_t value) {
  const upb_MiniTableField field = {18, UPB_SIZE(56, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_always_log_health_check_failures(envoy_config_core_v3_HealthCheck *msg, bool value) {
  const upb_MiniTableField field = {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_initial_jitter(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(60, 128), 75, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_initial_jitter(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_initial_jitter(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_initial_jitter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_tls_options(envoy_config_core_v3_HealthCheck *msg, envoy_config_core_v3_HealthCheck_TlsOptions* value) {
  const upb_MiniTableField field = {21, UPB_SIZE(64, 136), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__TlsOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_TlsOptions* envoy_config_core_v3_HealthCheck_mutable_tls_options(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_TlsOptions* sub = (struct envoy_config_core_v3_HealthCheck_TlsOptions*)envoy_config_core_v3_HealthCheck_tls_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_TlsOptions*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__TlsOptions_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_tls_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_event_service(envoy_config_core_v3_HealthCheck *msg, struct envoy_config_core_v3_EventServiceConfig* value) {
  const upb_MiniTableField field = {22, UPB_SIZE(68, 144), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__EventServiceConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_EventServiceConfig* envoy_config_core_v3_HealthCheck_mutable_event_service(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_EventServiceConfig* sub = (struct envoy_config_core_v3_EventServiceConfig*)envoy_config_core_v3_HealthCheck_event_service(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_EventServiceConfig*)_upb_Message_New(&envoy__config__core__v3__EventServiceConfig_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_event_service(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_transport_socket_match_criteria(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {23, UPB_SIZE(72, 152), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_core_v3_HealthCheck_mutable_transport_socket_match_criteria(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_core_v3_HealthCheck_transport_socket_match_criteria(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_transport_socket_match_criteria(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_no_traffic_healthy_interval(envoy_config_core_v3_HealthCheck *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {24, UPB_SIZE(76, 160), 79, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HealthCheck_mutable_no_traffic_healthy_interval(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HealthCheck_no_traffic_healthy_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_set_no_traffic_healthy_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_core_v3_HealthCheck_mutable_event_logger(envoy_config_core_v3_HealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_core_v3_HealthCheck_resize_event_logger(envoy_config_core_v3_HealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_core_v3_HealthCheck_add_event_logger(envoy_config_core_v3_HealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {25, UPB_SIZE(80, 168), 0, 20, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_set_always_log_health_check_success(envoy_config_core_v3_HealthCheck *msg, bool value) {
  const upb_MiniTableField field = {26, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_Payload_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_Payload*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__Payload_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_Payload_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_Payload* ret = envoy_config_core_v3_HealthCheck_Payload_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__Payload_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_Payload_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_Payload* ret = envoy_config_core_v3_HealthCheck_Payload_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__Payload_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_Payload_serialize(const envoy_config_core_v3_HealthCheck_Payload* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__Payload_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_Payload_serialize_ex(const envoy_config_core_v3_HealthCheck_Payload* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__Payload_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_HealthCheck_Payload_payload_text = 1,
  envoy_config_core_v3_HealthCheck_Payload_payload_binary = 2,
  envoy_config_core_v3_HealthCheck_Payload_payload_NOT_SET = 0
} envoy_config_core_v3_HealthCheck_Payload_payload_oneofcases;
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload_payload_oneofcases envoy_config_core_v3_HealthCheck_Payload_payload_case(const envoy_config_core_v3_HealthCheck_Payload* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HealthCheck_Payload_payload_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_Payload_clear_payload(envoy_config_core_v3_HealthCheck_Payload* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__Payload_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_Payload_clear_text(envoy_config_core_v3_HealthCheck_Payload* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_Payload_text(const envoy_config_core_v3_HealthCheck_Payload* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_Payload_has_text(const envoy_config_core_v3_HealthCheck_Payload* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_Payload_clear_binary(envoy_config_core_v3_HealthCheck_Payload* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_Payload_binary(const envoy_config_core_v3_HealthCheck_Payload* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_Payload_has_binary(const envoy_config_core_v3_HealthCheck_Payload* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_Payload_set_text(envoy_config_core_v3_HealthCheck_Payload *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_Payload_set_binary(envoy_config_core_v3_HealthCheck_Payload *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_HealthCheck_HttpHealthCheck* envoy_config_core_v3_HealthCheck_HttpHealthCheck_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_HttpHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_HttpHealthCheck* envoy_config_core_v3_HealthCheck_HttpHealthCheck_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_HttpHealthCheck* ret = envoy_config_core_v3_HealthCheck_HttpHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_HttpHealthCheck* envoy_config_core_v3_HealthCheck_HttpHealthCheck_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_HttpHealthCheck* ret = envoy_config_core_v3_HealthCheck_HttpHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_HttpHealthCheck_serialize(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_HttpHealthCheck_serialize_ex(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__HttpHealthCheck_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_host(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_HttpHealthCheck_host(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_path(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(60, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_HttpHealthCheck_path(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(60, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_send(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_HttpHealthCheck_send(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_Payload* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_Payload* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_HttpHealthCheck_has_send(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_receive(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_Payload* const* envoy_config_core_v3_HealthCheck_HttpHealthCheck_receive(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_HealthCheck_Payload* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_receive_upb_array(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_receive_mutable_upb_array(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_request_headers_to_add(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_core_v3_HealthCheck_HttpHealthCheck_request_headers_to_add(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_HeaderValueOption* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_request_headers_to_add_upb_array(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_request_headers_to_add_mutable_upb_array(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_request_headers_to_remove(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_core_v3_HealthCheck_HttpHealthCheck_request_headers_to_remove(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_request_headers_to_remove_upb_array(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_request_headers_to_remove_mutable_upb_array(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_expected_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Int64Range* const* envoy_config_core_v3_HealthCheck_HttpHealthCheck_expected_statuses(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_v3_Int64Range* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_expected_statuses_upb_array(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_expected_statuses_mutable_upb_array(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_codec_client_type(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(32, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_HealthCheck_HttpHealthCheck_codec_client_type(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {10, UPB_SIZE(32, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_service_name_matcher(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_core_v3_HealthCheck_HttpHealthCheck_service_name_matcher(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_HttpHealthCheck_has_service_name_matcher(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_retriable_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Int64Range* const* envoy_config_core_v3_HealthCheck_HttpHealthCheck_retriable_statuses(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_v3_Int64Range* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_retriable_statuses_upb_array(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_HttpHealthCheck_retriable_statuses_mutable_upb_array(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_method(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_HealthCheck_HttpHealthCheck_method(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {13, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_clear_response_buffer_size(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(48, 112), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_core_v3_HealthCheck_HttpHealthCheck_response_buffer_size(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(48, 112), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_HttpHealthCheck_has_response_buffer_size(const envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(48, 112), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_host(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_path(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(60, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_send(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, envoy_config_core_v3_HealthCheck_Payload* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_send(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_Payload* sub = (struct envoy_config_core_v3_HealthCheck_Payload*)envoy_config_core_v3_HealthCheck_HttpHealthCheck_send(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_Payload*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__Payload_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_send(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload** envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_receive(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_HealthCheck_Payload**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload** envoy_config_core_v3_HealthCheck_HttpHealthCheck_resize_receive(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HealthCheck_Payload**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_HttpHealthCheck_add_receive(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HealthCheck_Payload* sub = (struct envoy_config_core_v3_HealthCheck_Payload*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__Payload_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_request_headers_to_add(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_HeaderValueOption**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_core_v3_HealthCheck_HttpHealthCheck_resize_request_headers_to_add(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_core_v3_HealthCheck_HttpHealthCheck_add_request_headers_to_add(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HeaderValueOption* sub = (struct envoy_config_core_v3_HeaderValueOption*)_upb_Message_New(&envoy__config__core__v3__HeaderValueOption_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE upb_StringView* envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_request_headers_to_remove(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_core_v3_HealthCheck_HttpHealthCheck_resize_request_headers_to_remove(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_HttpHealthCheck_add_request_headers_to_remove(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(24, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_type_v3_Int64Range** envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_expected_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_v3_Int64Range**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_v3_Int64Range** envoy_config_core_v3_HealthCheck_HttpHealthCheck_resize_expected_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_v3_Int64Range**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_v3_Int64Range* envoy_config_core_v3_HealthCheck_HttpHealthCheck_add_expected_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(28, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_v3_Int64Range* sub = (struct envoy_type_v3_Int64Range*)_upb_Message_New(&envoy__type__v3__Int64Range_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_codec_client_type(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, int32_t value) {
  const upb_MiniTableField field = {10, UPB_SIZE(32, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_service_name_matcher(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_service_name_matcher(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_core_v3_HealthCheck_HttpHealthCheck_service_name_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_service_name_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_type_v3_Int64Range** envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_retriable_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_v3_Int64Range**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_v3_Int64Range** envoy_config_core_v3_HealthCheck_HttpHealthCheck_resize_retriable_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_v3_Int64Range**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_v3_Int64Range* envoy_config_core_v3_HealthCheck_HttpHealthCheck_add_retriable_statuses(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {12, UPB_SIZE(40, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_v3_Int64Range* sub = (struct envoy_type_v3_Int64Range*)_upb_Message_New(&envoy__type__v3__Int64Range_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_method(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, int32_t value) {
  const upb_MiniTableField field = {13, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_response_buffer_size(envoy_config_core_v3_HealthCheck_HttpHealthCheck *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(48, 112), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_core_v3_HealthCheck_HttpHealthCheck_mutable_response_buffer_size(envoy_config_core_v3_HealthCheck_HttpHealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_core_v3_HealthCheck_HttpHealthCheck_response_buffer_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_HttpHealthCheck_set_response_buffer_size(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_HealthCheck_TcpHealthCheck* envoy_config_core_v3_HealthCheck_TcpHealthCheck_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_TcpHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_TcpHealthCheck* envoy_config_core_v3_HealthCheck_TcpHealthCheck_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_TcpHealthCheck* ret = envoy_config_core_v3_HealthCheck_TcpHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_TcpHealthCheck* envoy_config_core_v3_HealthCheck_TcpHealthCheck_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_TcpHealthCheck* ret = envoy_config_core_v3_HealthCheck_TcpHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_TcpHealthCheck_serialize(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_TcpHealthCheck_serialize_ex(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__TcpHealthCheck_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_TcpHealthCheck_clear_send(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_TcpHealthCheck_send(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const envoy_config_core_v3_HealthCheck_Payload* default_val = NULL;
  const envoy_config_core_v3_HealthCheck_Payload* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_TcpHealthCheck_has_send(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_TcpHealthCheck_clear_receive(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HealthCheck_Payload* const* envoy_config_core_v3_HealthCheck_TcpHealthCheck_receive(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_HealthCheck_Payload* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_TcpHealthCheck_receive_upb_array(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_TcpHealthCheck_receive_mutable_upb_array(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_TcpHealthCheck_clear_proxy_protocol_config(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ProxyProtocolConfig* envoy_config_core_v3_HealthCheck_TcpHealthCheck_proxy_protocol_config(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const struct envoy_config_core_v3_ProxyProtocolConfig* default_val = NULL;
  const struct envoy_config_core_v3_ProxyProtocolConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ProxyProtocolConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_TcpHealthCheck_has_proxy_protocol_config(const envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_TcpHealthCheck_set_send(envoy_config_core_v3_HealthCheck_TcpHealthCheck *msg, envoy_config_core_v3_HealthCheck_Payload* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_TcpHealthCheck_mutable_send(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthCheck_Payload* sub = (struct envoy_config_core_v3_HealthCheck_Payload*)envoy_config_core_v3_HealthCheck_TcpHealthCheck_send(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthCheck_Payload*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__Payload_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_TcpHealthCheck_set_send(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload** envoy_config_core_v3_HealthCheck_TcpHealthCheck_mutable_receive(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_HealthCheck_Payload**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_HealthCheck_Payload** envoy_config_core_v3_HealthCheck_TcpHealthCheck_resize_receive(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HealthCheck_Payload**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck_Payload* envoy_config_core_v3_HealthCheck_TcpHealthCheck_add_receive(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck__Payload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HealthCheck_Payload* sub = (struct envoy_config_core_v3_HealthCheck_Payload*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__Payload_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_TcpHealthCheck_set_proxy_protocol_config(envoy_config_core_v3_HealthCheck_TcpHealthCheck *msg, struct envoy_config_core_v3_ProxyProtocolConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ProxyProtocolConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ProxyProtocolConfig* envoy_config_core_v3_HealthCheck_TcpHealthCheck_mutable_proxy_protocol_config(envoy_config_core_v3_HealthCheck_TcpHealthCheck* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ProxyProtocolConfig* sub = (struct envoy_config_core_v3_ProxyProtocolConfig*)envoy_config_core_v3_HealthCheck_TcpHealthCheck_proxy_protocol_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ProxyProtocolConfig*)_upb_Message_New(&envoy__config__core__v3__ProxyProtocolConfig_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_TcpHealthCheck_set_proxy_protocol_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_HealthCheck_RedisHealthCheck* envoy_config_core_v3_HealthCheck_RedisHealthCheck_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_RedisHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__RedisHealthCheck_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_RedisHealthCheck* envoy_config_core_v3_HealthCheck_RedisHealthCheck_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_RedisHealthCheck* ret = envoy_config_core_v3_HealthCheck_RedisHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__RedisHealthCheck_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_RedisHealthCheck* envoy_config_core_v3_HealthCheck_RedisHealthCheck_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_RedisHealthCheck* ret = envoy_config_core_v3_HealthCheck_RedisHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__RedisHealthCheck_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_RedisHealthCheck_serialize(const envoy_config_core_v3_HealthCheck_RedisHealthCheck* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__RedisHealthCheck_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_RedisHealthCheck_serialize_ex(const envoy_config_core_v3_HealthCheck_RedisHealthCheck* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__RedisHealthCheck_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_RedisHealthCheck_clear_key(envoy_config_core_v3_HealthCheck_RedisHealthCheck* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_RedisHealthCheck_key(const envoy_config_core_v3_HealthCheck_RedisHealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_RedisHealthCheck_set_key(envoy_config_core_v3_HealthCheck_RedisHealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_HealthCheck_GrpcHealthCheck* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_GrpcHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_GrpcHealthCheck* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_GrpcHealthCheck* ret = envoy_config_core_v3_HealthCheck_GrpcHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_GrpcHealthCheck* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_GrpcHealthCheck* ret = envoy_config_core_v3_HealthCheck_GrpcHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_serialize(const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_serialize_ex(const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__GrpcHealthCheck_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_GrpcHealthCheck_clear_service_name(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_GrpcHealthCheck_service_name(const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_GrpcHealthCheck_clear_authority(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_GrpcHealthCheck_authority(const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_GrpcHealthCheck_clear_initial_metadata(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_initial_metadata(const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_HeaderValueOption* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_GrpcHealthCheck_initial_metadata_upb_array(const envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_GrpcHealthCheck_initial_metadata_mutable_upb_array(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_GrpcHealthCheck_set_service_name(envoy_config_core_v3_HealthCheck_GrpcHealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_GrpcHealthCheck_set_authority(envoy_config_core_v3_HealthCheck_GrpcHealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_core_v3_HealthCheck_GrpcHealthCheck_mutable_initial_metadata(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_HeaderValueOption**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_core_v3_HealthCheck_GrpcHealthCheck_resize_initial_metadata(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_core_v3_HealthCheck_GrpcHealthCheck_add_initial_metadata(envoy_config_core_v3_HealthCheck_GrpcHealthCheck* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HeaderValueOption* sub = (struct envoy_config_core_v3_HeaderValueOption*)_upb_Message_New(&envoy__config__core__v3__HeaderValueOption_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_core_v3_HealthCheck_CustomHealthCheck* envoy_config_core_v3_HealthCheck_CustomHealthCheck_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_CustomHealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_CustomHealthCheck* envoy_config_core_v3_HealthCheck_CustomHealthCheck_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_CustomHealthCheck* ret = envoy_config_core_v3_HealthCheck_CustomHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_CustomHealthCheck* envoy_config_core_v3_HealthCheck_CustomHealthCheck_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_CustomHealthCheck* ret = envoy_config_core_v3_HealthCheck_CustomHealthCheck_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_CustomHealthCheck_serialize(const envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_CustomHealthCheck_serialize_ex(const envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_HealthCheck_CustomHealthCheck_config_type_typed_config = 3,
  envoy_config_core_v3_HealthCheck_CustomHealthCheck_config_type_NOT_SET = 0
} envoy_config_core_v3_HealthCheck_CustomHealthCheck_config_type_oneofcases;
UPB_INLINE envoy_config_core_v3_HealthCheck_CustomHealthCheck_config_type_oneofcases envoy_config_core_v3_HealthCheck_CustomHealthCheck_config_type_case(const envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HealthCheck_CustomHealthCheck_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_CustomHealthCheck_clear_config_type(envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__CustomHealthCheck_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_CustomHealthCheck_clear_name(envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HealthCheck_CustomHealthCheck_name(const envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_CustomHealthCheck_clear_typed_config(envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_core_v3_HealthCheck_CustomHealthCheck_typed_config(const envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_CustomHealthCheck_has_typed_config(const envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_HealthCheck_CustomHealthCheck_set_name(envoy_config_core_v3_HealthCheck_CustomHealthCheck *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_CustomHealthCheck_set_typed_config(envoy_config_core_v3_HealthCheck_CustomHealthCheck *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_core_v3_HealthCheck_CustomHealthCheck_mutable_typed_config(envoy_config_core_v3_HealthCheck_CustomHealthCheck* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_core_v3_HealthCheck_CustomHealthCheck_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_core_v3_HealthCheck_CustomHealthCheck_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_HealthCheck_TlsOptions* envoy_config_core_v3_HealthCheck_TlsOptions_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HealthCheck_TlsOptions*)_upb_Message_New(&envoy__config__core__v3__HealthCheck__TlsOptions_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HealthCheck_TlsOptions* envoy_config_core_v3_HealthCheck_TlsOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_TlsOptions* ret = envoy_config_core_v3_HealthCheck_TlsOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__TlsOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HealthCheck_TlsOptions* envoy_config_core_v3_HealthCheck_TlsOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HealthCheck_TlsOptions* ret = envoy_config_core_v3_HealthCheck_TlsOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HealthCheck__TlsOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_TlsOptions_serialize(const envoy_config_core_v3_HealthCheck_TlsOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__TlsOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HealthCheck_TlsOptions_serialize_ex(const envoy_config_core_v3_HealthCheck_TlsOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HealthCheck__TlsOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HealthCheck_TlsOptions_clear_alpn_protocols(envoy_config_core_v3_HealthCheck_TlsOptions* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_core_v3_HealthCheck_TlsOptions_alpn_protocols(const envoy_config_core_v3_HealthCheck_TlsOptions* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HealthCheck_TlsOptions_alpn_protocols_upb_array(const envoy_config_core_v3_HealthCheck_TlsOptions* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HealthCheck_TlsOptions_alpn_protocols_mutable_upb_array(envoy_config_core_v3_HealthCheck_TlsOptions* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE upb_StringView* envoy_config_core_v3_HealthCheck_TlsOptions_mutable_alpn_protocols(envoy_config_core_v3_HealthCheck_TlsOptions* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_core_v3_HealthCheck_TlsOptions_resize_alpn_protocols(envoy_config_core_v3_HealthCheck_TlsOptions* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_core_v3_HealthCheck_TlsOptions_add_alpn_protocols(envoy_config_core_v3_HealthCheck_TlsOptions* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
