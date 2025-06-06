
#ifndef ENVOY_ADMIN_V3_CLUSTERS_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_CLUSTERS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/clusters.upb_minitable.h"

#include "envoy/admin/v3/metrics.upb_minitable.h"
#include "envoy/config/cluster/v3/circuit_breaker.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/health_check.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_Clusters { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_Clusters;
typedef struct envoy_admin_v3_ClusterStatus { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ClusterStatus;
typedef struct envoy_admin_v3_HostStatus { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_HostStatus;
typedef struct envoy_admin_v3_HostHealthStatus { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_HostHealthStatus;
struct envoy_admin_v3_SimpleMetric;
struct envoy_config_cluster_v3_CircuitBreakers;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_Locality;
struct envoy_type_v3_Percent;

UPB_INLINE envoy_admin_v3_Clusters* envoy_admin_v3_Clusters_new(upb_Arena* arena) {
  return (envoy_admin_v3_Clusters*)_upb_Message_New(&envoy__admin__v3__Clusters_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_Clusters* envoy_admin_v3_Clusters_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_Clusters* ret = envoy_admin_v3_Clusters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Clusters_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_Clusters* envoy_admin_v3_Clusters_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_Clusters* ret = envoy_admin_v3_Clusters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Clusters_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_Clusters_serialize(const envoy_admin_v3_Clusters* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Clusters_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_Clusters_serialize_ex(const envoy_admin_v3_Clusters* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Clusters_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_Clusters_clear_cluster_statuses(envoy_admin_v3_Clusters* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ClusterStatus* const* envoy_admin_v3_Clusters_cluster_statuses(const envoy_admin_v3_Clusters* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClusterStatus_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ClusterStatus* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_Clusters_cluster_statuses_upb_array(const envoy_admin_v3_Clusters* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClusterStatus_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_Clusters_cluster_statuses_mutable_upb_array(envoy_admin_v3_Clusters* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClusterStatus_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_ClusterStatus** envoy_admin_v3_Clusters_mutable_cluster_statuses(envoy_admin_v3_Clusters* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClusterStatus_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ClusterStatus**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ClusterStatus** envoy_admin_v3_Clusters_resize_cluster_statuses(envoy_admin_v3_Clusters* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ClusterStatus**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ClusterStatus* envoy_admin_v3_Clusters_add_cluster_statuses(envoy_admin_v3_Clusters* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClusterStatus_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ClusterStatus* sub = (struct envoy_admin_v3_ClusterStatus*)_upb_Message_New(&envoy__admin__v3__ClusterStatus_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_ClusterStatus* envoy_admin_v3_ClusterStatus_new(upb_Arena* arena) {
  return (envoy_admin_v3_ClusterStatus*)_upb_Message_New(&envoy__admin__v3__ClusterStatus_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ClusterStatus* envoy_admin_v3_ClusterStatus_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ClusterStatus* ret = envoy_admin_v3_ClusterStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClusterStatus_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ClusterStatus* envoy_admin_v3_ClusterStatus_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ClusterStatus* ret = envoy_admin_v3_ClusterStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClusterStatus_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ClusterStatus_serialize(const envoy_admin_v3_ClusterStatus* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClusterStatus_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ClusterStatus_serialize_ex(const envoy_admin_v3_ClusterStatus* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClusterStatus_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_name(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ClusterStatus_name(const envoy_admin_v3_ClusterStatus* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_added_via_api(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_ClusterStatus_added_via_api(const envoy_admin_v3_ClusterStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_success_rate_ejection_threshold(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_admin_v3_ClusterStatus_success_rate_ejection_threshold(const envoy_admin_v3_ClusterStatus* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClusterStatus_has_success_rate_ejection_threshold(const envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_host_statuses(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_HostStatus* const* envoy_admin_v3_ClusterStatus_host_statuses(const envoy_admin_v3_ClusterStatus* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostStatus_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_HostStatus* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ClusterStatus_host_statuses_upb_array(const envoy_admin_v3_ClusterStatus* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostStatus_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ClusterStatus_host_statuses_mutable_upb_array(envoy_admin_v3_ClusterStatus* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostStatus_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_local_origin_success_rate_ejection_threshold(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_admin_v3_ClusterStatus_local_origin_success_rate_ejection_threshold(const envoy_admin_v3_ClusterStatus* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClusterStatus_has_local_origin_success_rate_ejection_threshold(const envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_circuit_breakers(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_cluster_v3_CircuitBreakers* envoy_admin_v3_ClusterStatus_circuit_breakers(const envoy_admin_v3_ClusterStatus* msg) {
  const struct envoy_config_cluster_v3_CircuitBreakers* default_val = NULL;
  const struct envoy_config_cluster_v3_CircuitBreakers* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClusterStatus_has_circuit_breakers(const envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_observability_name(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ClusterStatus_observability_name(const envoy_admin_v3_ClusterStatus* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_clear_eds_service_name(envoy_admin_v3_ClusterStatus* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ClusterStatus_eds_service_name(const envoy_admin_v3_ClusterStatus* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_ClusterStatus_set_name(envoy_admin_v3_ClusterStatus *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_set_added_via_api(envoy_admin_v3_ClusterStatus *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_set_success_rate_ejection_threshold(envoy_admin_v3_ClusterStatus *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_admin_v3_ClusterStatus_mutable_success_rate_ejection_threshold(envoy_admin_v3_ClusterStatus* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_admin_v3_ClusterStatus_success_rate_ejection_threshold(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_admin_v3_ClusterStatus_set_success_rate_ejection_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_admin_v3_HostStatus** envoy_admin_v3_ClusterStatus_mutable_host_statuses(envoy_admin_v3_ClusterStatus* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostStatus_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_HostStatus**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_HostStatus** envoy_admin_v3_ClusterStatus_resize_host_statuses(envoy_admin_v3_ClusterStatus* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_HostStatus**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_HostStatus* envoy_admin_v3_ClusterStatus_add_host_statuses(envoy_admin_v3_ClusterStatus* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostStatus_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_HostStatus* sub = (struct envoy_admin_v3_HostStatus*)_upb_Message_New(&envoy__admin__v3__HostStatus_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_set_local_origin_success_rate_ejection_threshold(envoy_admin_v3_ClusterStatus *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_admin_v3_ClusterStatus_mutable_local_origin_success_rate_ejection_threshold(envoy_admin_v3_ClusterStatus* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_admin_v3_ClusterStatus_local_origin_success_rate_ejection_threshold(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_admin_v3_ClusterStatus_set_local_origin_success_rate_ejection_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_set_circuit_breakers(envoy_admin_v3_ClusterStatus *msg, struct envoy_config_cluster_v3_CircuitBreakers* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_CircuitBreakers* envoy_admin_v3_ClusterStatus_mutable_circuit_breakers(envoy_admin_v3_ClusterStatus* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_CircuitBreakers* sub = (struct envoy_config_cluster_v3_CircuitBreakers*)envoy_admin_v3_ClusterStatus_circuit_breakers(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_CircuitBreakers*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers_msg_init, arena);
    if (sub) envoy_admin_v3_ClusterStatus_set_circuit_breakers(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_set_observability_name(envoy_admin_v3_ClusterStatus *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ClusterStatus_set_eds_service_name(envoy_admin_v3_ClusterStatus *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_HostStatus* envoy_admin_v3_HostStatus_new(upb_Arena* arena) {
  return (envoy_admin_v3_HostStatus*)_upb_Message_New(&envoy__admin__v3__HostStatus_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_HostStatus* envoy_admin_v3_HostStatus_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_HostStatus* ret = envoy_admin_v3_HostStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__HostStatus_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_HostStatus* envoy_admin_v3_HostStatus_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_HostStatus* ret = envoy_admin_v3_HostStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__HostStatus_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_HostStatus_serialize(const envoy_admin_v3_HostStatus* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__HostStatus_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_HostStatus_serialize_ex(const envoy_admin_v3_HostStatus* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__HostStatus_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_address(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_admin_v3_HostStatus_address(const envoy_admin_v3_HostStatus* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_HostStatus_has_address(const envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_stats(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_SimpleMetric* const* envoy_admin_v3_HostStatus_stats(const envoy_admin_v3_HostStatus* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SimpleMetric_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_admin_v3_SimpleMetric* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_HostStatus_stats_upb_array(const envoy_admin_v3_HostStatus* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SimpleMetric_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_HostStatus_stats_mutable_upb_array(envoy_admin_v3_HostStatus* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SimpleMetric_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_health_status(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_HostHealthStatus* envoy_admin_v3_HostStatus_health_status(const envoy_admin_v3_HostStatus* msg) {
  const envoy_admin_v3_HostHealthStatus* default_val = NULL;
  const envoy_admin_v3_HostHealthStatus* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostHealthStatus_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_HostStatus_has_health_status(const envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_success_rate(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_admin_v3_HostStatus_success_rate(const envoy_admin_v3_HostStatus* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_HostStatus_has_success_rate(const envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_weight(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_admin_v3_HostStatus_weight(const envoy_admin_v3_HostStatus* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_hostname(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(44, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_HostStatus_hostname(const envoy_admin_v3_HostStatus* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(44, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_priority(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_admin_v3_HostStatus_priority(const envoy_admin_v3_HostStatus* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {7, UPB_SIZE(32, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_local_origin_success_rate(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_admin_v3_HostStatus_local_origin_success_rate(const envoy_admin_v3_HostStatus* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_HostStatus_has_local_origin_success_rate(const envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_HostStatus_clear_locality(envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 80), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Locality* envoy_admin_v3_HostStatus_locality(const envoy_admin_v3_HostStatus* msg) {
  const struct envoy_config_core_v3_Locality* default_val = NULL;
  const struct envoy_config_core_v3_Locality* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(40, 80), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Locality_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_HostStatus_has_locality(const envoy_admin_v3_HostStatus* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 80), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_HostStatus_set_address(envoy_admin_v3_HostStatus *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_admin_v3_HostStatus_mutable_address(envoy_admin_v3_HostStatus* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_admin_v3_HostStatus_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_admin_v3_HostStatus_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_admin_v3_SimpleMetric** envoy_admin_v3_HostStatus_mutable_stats(envoy_admin_v3_HostStatus* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SimpleMetric_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_admin_v3_SimpleMetric**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_admin_v3_SimpleMetric** envoy_admin_v3_HostStatus_resize_stats(envoy_admin_v3_HostStatus* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_admin_v3_SimpleMetric**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_SimpleMetric* envoy_admin_v3_HostStatus_add_stats(envoy_admin_v3_HostStatus* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SimpleMetric_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_SimpleMetric* sub = (struct envoy_admin_v3_SimpleMetric*)_upb_Message_New(&envoy__admin__v3__SimpleMetric_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_health_status(envoy_admin_v3_HostStatus *msg, envoy_admin_v3_HostHealthStatus* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__HostHealthStatus_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_HostHealthStatus* envoy_admin_v3_HostStatus_mutable_health_status(envoy_admin_v3_HostStatus* msg, upb_Arena* arena) {
  struct envoy_admin_v3_HostHealthStatus* sub = (struct envoy_admin_v3_HostHealthStatus*)envoy_admin_v3_HostStatus_health_status(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_HostHealthStatus*)_upb_Message_New(&envoy__admin__v3__HostHealthStatus_msg_init, arena);
    if (sub) envoy_admin_v3_HostStatus_set_health_status(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_success_rate(envoy_admin_v3_HostStatus *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_admin_v3_HostStatus_mutable_success_rate(envoy_admin_v3_HostStatus* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_admin_v3_HostStatus_success_rate(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_admin_v3_HostStatus_set_success_rate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_weight(envoy_admin_v3_HostStatus *msg, uint32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_hostname(envoy_admin_v3_HostStatus *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(44, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_priority(envoy_admin_v3_HostStatus *msg, uint32_t value) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_local_origin_success_rate(envoy_admin_v3_HostStatus *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_admin_v3_HostStatus_mutable_local_origin_success_rate(envoy_admin_v3_HostStatus* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_admin_v3_HostStatus_local_origin_success_rate(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_admin_v3_HostStatus_set_local_origin_success_rate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_HostStatus_set_locality(envoy_admin_v3_HostStatus *msg, struct envoy_config_core_v3_Locality* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 80), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Locality_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Locality* envoy_admin_v3_HostStatus_mutable_locality(envoy_admin_v3_HostStatus* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Locality* sub = (struct envoy_config_core_v3_Locality*)envoy_admin_v3_HostStatus_locality(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Locality*)_upb_Message_New(&envoy__config__core__v3__Locality_msg_init, arena);
    if (sub) envoy_admin_v3_HostStatus_set_locality(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_HostHealthStatus* envoy_admin_v3_HostHealthStatus_new(upb_Arena* arena) {
  return (envoy_admin_v3_HostHealthStatus*)_upb_Message_New(&envoy__admin__v3__HostHealthStatus_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_HostHealthStatus* envoy_admin_v3_HostHealthStatus_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_HostHealthStatus* ret = envoy_admin_v3_HostHealthStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__HostHealthStatus_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_HostHealthStatus* envoy_admin_v3_HostHealthStatus_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_HostHealthStatus* ret = envoy_admin_v3_HostHealthStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__HostHealthStatus_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_HostHealthStatus_serialize(const envoy_admin_v3_HostHealthStatus* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__HostHealthStatus_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_HostHealthStatus_serialize_ex(const envoy_admin_v3_HostHealthStatus* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__HostHealthStatus_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_failed_active_health_check(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_failed_active_health_check(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_failed_outlier_check(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_failed_outlier_check(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_eds_health_status(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_HostHealthStatus_eds_health_status(const envoy_admin_v3_HostHealthStatus* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_failed_active_degraded_check(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_failed_active_degraded_check(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_pending_dynamic_removal(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_pending_dynamic_removal(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_pending_active_hc(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_pending_active_hc(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_excluded_via_immediate_hc_fail(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {7, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_excluded_via_immediate_hc_fail(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_clear_active_hc_timeout(envoy_admin_v3_HostHealthStatus* msg) {
  const upb_MiniTableField field = {8, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_admin_v3_HostHealthStatus_active_hc_timeout(const envoy_admin_v3_HostHealthStatus* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_failed_active_health_check(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_failed_outlier_check(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_eds_health_status(envoy_admin_v3_HostHealthStatus *msg, int32_t value) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_failed_active_degraded_check(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_pending_dynamic_removal(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_pending_active_hc(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_excluded_via_immediate_hc_fail(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {7, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_HostHealthStatus_set_active_hc_timeout(envoy_admin_v3_HostHealthStatus *msg, bool value) {
  const upb_MiniTableField field = {8, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
