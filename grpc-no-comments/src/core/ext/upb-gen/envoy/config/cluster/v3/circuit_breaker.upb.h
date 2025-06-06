
#ifndef ENVOY_CONFIG_CLUSTER_V3_CIRCUIT_BREAKER_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CLUSTER_V3_CIRCUIT_BREAKER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/cluster/v3/circuit_breaker.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_cluster_v3_CircuitBreakers { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_CircuitBreakers;
typedef struct envoy_config_cluster_v3_CircuitBreakers_Thresholds { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_CircuitBreakers_Thresholds;
typedef struct envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget;
struct envoy_type_v3_Percent;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_config_cluster_v3_CircuitBreakers* envoy_config_cluster_v3_CircuitBreakers_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_CircuitBreakers*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers* envoy_config_cluster_v3_CircuitBreakers_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_CircuitBreakers* ret = envoy_config_cluster_v3_CircuitBreakers_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__CircuitBreakers_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers* envoy_config_cluster_v3_CircuitBreakers_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_CircuitBreakers* ret = envoy_config_cluster_v3_CircuitBreakers_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__CircuitBreakers_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_CircuitBreakers_serialize(const envoy_config_cluster_v3_CircuitBreakers* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__CircuitBreakers_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_CircuitBreakers_serialize_ex(const envoy_config_cluster_v3_CircuitBreakers* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__CircuitBreakers_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_clear_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_CircuitBreakers_Thresholds* const* envoy_config_cluster_v3_CircuitBreakers_thresholds(const envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_cluster_v3_CircuitBreakers_Thresholds* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_CircuitBreakers_thresholds_upb_array(const envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_CircuitBreakers_thresholds_mutable_upb_array(envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_clear_per_host_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_CircuitBreakers_Thresholds* const* envoy_config_cluster_v3_CircuitBreakers_per_host_thresholds(const envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_cluster_v3_CircuitBreakers_Thresholds* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_CircuitBreakers_per_host_thresholds_upb_array(const envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_CircuitBreakers_per_host_thresholds_mutable_upb_array(envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds** envoy_config_cluster_v3_CircuitBreakers_mutable_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_cluster_v3_CircuitBreakers_Thresholds**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds** envoy_config_cluster_v3_CircuitBreakers_resize_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_CircuitBreakers_Thresholds**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_CircuitBreakers_Thresholds* envoy_config_cluster_v3_CircuitBreakers_add_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_CircuitBreakers_Thresholds* sub = (struct envoy_config_cluster_v3_CircuitBreakers_Thresholds*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds** envoy_config_cluster_v3_CircuitBreakers_mutable_per_host_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_cluster_v3_CircuitBreakers_Thresholds**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds** envoy_config_cluster_v3_CircuitBreakers_resize_per_host_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_CircuitBreakers_Thresholds**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_CircuitBreakers_Thresholds* envoy_config_cluster_v3_CircuitBreakers_add_per_host_thresholds(envoy_config_cluster_v3_CircuitBreakers* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_CircuitBreakers_Thresholds* sub = (struct envoy_config_cluster_v3_CircuitBreakers_Thresholds*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds* envoy_config_cluster_v3_CircuitBreakers_Thresholds_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_CircuitBreakers_Thresholds*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds* envoy_config_cluster_v3_CircuitBreakers_Thresholds_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_CircuitBreakers_Thresholds* ret = envoy_config_cluster_v3_CircuitBreakers_Thresholds_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds* envoy_config_cluster_v3_CircuitBreakers_Thresholds_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_CircuitBreakers_Thresholds* ret = envoy_config_cluster_v3_CircuitBreakers_Thresholds_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_CircuitBreakers_Thresholds_serialize(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_CircuitBreakers_Thresholds_serialize_ex(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__CircuitBreakers__Thresholds_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_priority(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_CircuitBreakers_Thresholds_priority(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_max_connections(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_connections(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_has_max_connections(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_max_pending_requests(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_pending_requests(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_has_max_pending_requests(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_max_requests(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_requests(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_has_max_requests(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_max_retries(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_retries(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_has_max_retries(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_track_remaining(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_track_remaining(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_max_connection_pools(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_connection_pools(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_has_max_connection_pools(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_clear_retry_budget(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* envoy_config_cluster_v3_CircuitBreakers_Thresholds_retry_budget(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* default_val = NULL;
  const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(36, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_has_retry_budget(const envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_priority(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_connections(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_mutable_max_connections(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_connections(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_connections(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_pending_requests(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_mutable_max_pending_requests(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_pending_requests(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_pending_requests(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_requests(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_mutable_max_requests(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_requests(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_requests(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_retries(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_mutable_max_retries(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_retries(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_retries(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_track_remaining(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_connection_pools(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_mutable_max_connection_pools(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_max_connection_pools(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_max_connection_pools(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_retry_budget(envoy_config_cluster_v3_CircuitBreakers_Thresholds *msg, envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* envoy_config_cluster_v3_CircuitBreakers_Thresholds_mutable_retry_budget(envoy_config_cluster_v3_CircuitBreakers_Thresholds* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* sub = (struct envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_retry_budget(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_set_retry_budget(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* ret = envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* ret = envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_serialize(const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_serialize_ex(const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__CircuitBreakers__Thresholds__RetryBudget_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_clear_budget_percent(envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_budget_percent(const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_has_budget_percent(const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_clear_min_retry_concurrency(envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_min_retry_concurrency(const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_has_min_retry_concurrency(const envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_set_budget_percent(envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_mutable_budget_percent(envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_budget_percent(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_set_budget_percent(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_set_min_retry_concurrency(envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_mutable_min_retry_concurrency(envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_min_retry_concurrency(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_CircuitBreakers_Thresholds_RetryBudget_set_min_retry_concurrency(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
