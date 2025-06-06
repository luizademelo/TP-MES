
#ifndef ENVOY_CONFIG_ENDPOINT_V3_LOAD_REPORT_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_ENDPOINT_V3_LOAD_REPORT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/endpoint/v3/load_report.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_endpoint_v3_UpstreamLocalityStats { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_UpstreamLocalityStats;
typedef struct envoy_config_endpoint_v3_UpstreamEndpointStats { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_UpstreamEndpointStats;
typedef struct envoy_config_endpoint_v3_EndpointLoadMetricStats { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_EndpointLoadMetricStats;
typedef struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats;
typedef struct envoy_config_endpoint_v3_ClusterStats { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_ClusterStats;
typedef struct envoy_config_endpoint_v3_ClusterStats_DroppedRequests { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_ClusterStats_DroppedRequests;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_Locality;
struct google_protobuf_Duration;
struct google_protobuf_Struct;

UPB_INLINE envoy_config_endpoint_v3_UpstreamLocalityStats* envoy_config_endpoint_v3_UpstreamLocalityStats_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_UpstreamLocalityStats*)_upb_Message_New(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamLocalityStats* envoy_config_endpoint_v3_UpstreamLocalityStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_UpstreamLocalityStats* ret = envoy_config_endpoint_v3_UpstreamLocalityStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamLocalityStats* envoy_config_endpoint_v3_UpstreamLocalityStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_UpstreamLocalityStats* ret = envoy_config_endpoint_v3_UpstreamLocalityStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_UpstreamLocalityStats_serialize(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_UpstreamLocalityStats_serialize_ex(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_locality(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Locality* envoy_config_endpoint_v3_UpstreamLocalityStats_locality(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const struct envoy_config_core_v3_Locality* default_val = NULL;
  const struct envoy_config_core_v3_Locality* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Locality_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_UpstreamLocalityStats_has_locality(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_successful_requests(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_successful_requests(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_requests_in_progress(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_requests_in_progress(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_error_requests(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(56, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_error_requests(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(56, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_load_metric_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_EndpointLoadMetricStats* const* envoy_config_endpoint_v3_UpstreamLocalityStats_load_metric_stats(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_endpoint_v3_EndpointLoadMetricStats* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_UpstreamLocalityStats_load_metric_stats_upb_array(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_UpstreamLocalityStats_load_metric_stats_mutable_upb_array(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_priority(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_endpoint_v3_UpstreamLocalityStats_priority(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_upstream_endpoint_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_UpstreamEndpointStats* const* envoy_config_endpoint_v3_UpstreamLocalityStats_upstream_endpoint_stats(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_endpoint_v3_UpstreamEndpointStats* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_UpstreamLocalityStats_upstream_endpoint_stats_upb_array(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_UpstreamLocalityStats_upstream_endpoint_stats_mutable_upb_array(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_issued_requests(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {8, 64, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_issued_requests(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {8, 64, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_active_connections(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {9, 72, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_active_connections(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {9, 72, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_new_connections(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {10, 80, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_new_connections(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {10, 80, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_total_fail_connections(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {11, 88, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamLocalityStats_total_fail_connections(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {11, 88, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_cpu_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(28, 96), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_cpu_utilization(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* default_val = NULL;
  const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(28, 96), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_UpstreamLocalityStats_has_cpu_utilization(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(28, 96), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_mem_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(32, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_mem_utilization(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* default_val = NULL;
  const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(32, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_UpstreamLocalityStats_has_mem_utilization(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(32, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_clear_application_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(36, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_application_utilization(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* default_val = NULL;
  const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(36, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_UpstreamLocalityStats_has_application_utilization(const envoy_config_endpoint_v3_UpstreamLocalityStats* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(36, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_locality(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, struct envoy_config_core_v3_Locality* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Locality_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Locality* envoy_config_endpoint_v3_UpstreamLocalityStats_mutable_locality(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Locality* sub = (struct envoy_config_core_v3_Locality*)envoy_config_endpoint_v3_UpstreamLocalityStats_locality(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Locality*)_upb_Message_New(&envoy__config__core__v3__Locality_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_UpstreamLocalityStats_set_locality(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_successful_requests(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_requests_in_progress(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_error_requests(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(56, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats** envoy_config_endpoint_v3_UpstreamLocalityStats_mutable_load_metric_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_endpoint_v3_EndpointLoadMetricStats**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats** envoy_config_endpoint_v3_UpstreamLocalityStats_resize_load_metric_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_endpoint_v3_EndpointLoadMetricStats**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_EndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_add_load_metric_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_EndpointLoadMetricStats* sub = (struct envoy_config_endpoint_v3_EndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_priority(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamEndpointStats** envoy_config_endpoint_v3_UpstreamLocalityStats_mutable_upstream_endpoint_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_endpoint_v3_UpstreamEndpointStats**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamEndpointStats** envoy_config_endpoint_v3_UpstreamLocalityStats_resize_upstream_endpoint_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_endpoint_v3_UpstreamEndpointStats**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_UpstreamEndpointStats* envoy_config_endpoint_v3_UpstreamLocalityStats_add_upstream_endpoint_stats(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(24, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_UpstreamEndpointStats* sub = (struct envoy_config_endpoint_v3_UpstreamEndpointStats*)_upb_Message_New(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_issued_requests(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {8, 64, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_active_connections(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {9, 72, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_new_connections(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {10, 80, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_total_fail_connections(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, uint64_t value) {
  const upb_MiniTableField field = {11, 88, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_cpu_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(28, 96), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_mutable_cpu_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena) {
  struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* sub = (struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)envoy_config_endpoint_v3_UpstreamLocalityStats_cpu_utilization(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_UpstreamLocalityStats_set_cpu_utilization(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_mem_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(32, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_mutable_mem_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena) {
  struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* sub = (struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)envoy_config_endpoint_v3_UpstreamLocalityStats_mem_utilization(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_UpstreamLocalityStats_set_mem_utilization(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamLocalityStats_set_application_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats *msg, envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(36, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamLocalityStats_mutable_application_utilization(envoy_config_endpoint_v3_UpstreamLocalityStats* msg, upb_Arena* arena) {
  struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* sub = (struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)envoy_config_endpoint_v3_UpstreamLocalityStats_application_utilization(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_UpstreamLocalityStats_set_application_utilization(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_endpoint_v3_UpstreamEndpointStats* envoy_config_endpoint_v3_UpstreamEndpointStats_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_UpstreamEndpointStats*)_upb_Message_New(&envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamEndpointStats* envoy_config_endpoint_v3_UpstreamEndpointStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_UpstreamEndpointStats* ret = envoy_config_endpoint_v3_UpstreamEndpointStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamEndpointStats* envoy_config_endpoint_v3_UpstreamEndpointStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_UpstreamEndpointStats* ret = envoy_config_endpoint_v3_UpstreamEndpointStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_UpstreamEndpointStats_serialize(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_UpstreamEndpointStats_serialize_ex(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__UpstreamEndpointStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_address(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_config_endpoint_v3_UpstreamEndpointStats_address(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_UpstreamEndpointStats_has_address(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_total_successful_requests(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamEndpointStats_total_successful_requests(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_total_requests_in_progress(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamEndpointStats_total_requests_in_progress(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_total_error_requests(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {4, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamEndpointStats_total_error_requests(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_load_metric_stats(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_EndpointLoadMetricStats* const* envoy_config_endpoint_v3_UpstreamEndpointStats_load_metric_stats(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_endpoint_v3_EndpointLoadMetricStats* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_UpstreamEndpointStats_load_metric_stats_upb_array(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_UpstreamEndpointStats_load_metric_stats_mutable_upb_array(envoy_config_endpoint_v3_UpstreamEndpointStats* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_metadata(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_endpoint_v3_UpstreamEndpointStats_metadata(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_UpstreamEndpointStats_has_metadata(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_clear_total_issued_requests(envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(48, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UpstreamEndpointStats_total_issued_requests(const envoy_config_endpoint_v3_UpstreamEndpointStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {7, UPB_SIZE(48, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_set_address(envoy_config_endpoint_v3_UpstreamEndpointStats *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_endpoint_v3_UpstreamEndpointStats_mutable_address(envoy_config_endpoint_v3_UpstreamEndpointStats* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_config_endpoint_v3_UpstreamEndpointStats_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_UpstreamEndpointStats_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_set_total_successful_requests(envoy_config_endpoint_v3_UpstreamEndpointStats *msg, uint64_t value) {
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_set_total_requests_in_progress(envoy_config_endpoint_v3_UpstreamEndpointStats *msg, uint64_t value) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_set_total_error_requests(envoy_config_endpoint_v3_UpstreamEndpointStats *msg, uint64_t value) {
  const upb_MiniTableField field = {4, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats** envoy_config_endpoint_v3_UpstreamEndpointStats_mutable_load_metric_stats(envoy_config_endpoint_v3_UpstreamEndpointStats* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_endpoint_v3_EndpointLoadMetricStats**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats** envoy_config_endpoint_v3_UpstreamEndpointStats_resize_load_metric_stats(envoy_config_endpoint_v3_UpstreamEndpointStats* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_endpoint_v3_EndpointLoadMetricStats**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_EndpointLoadMetricStats* envoy_config_endpoint_v3_UpstreamEndpointStats_add_load_metric_stats(envoy_config_endpoint_v3_UpstreamEndpointStats* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_EndpointLoadMetricStats* sub = (struct envoy_config_endpoint_v3_EndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_set_metadata(envoy_config_endpoint_v3_UpstreamEndpointStats *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_endpoint_v3_UpstreamEndpointStats_mutable_metadata(envoy_config_endpoint_v3_UpstreamEndpointStats* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_endpoint_v3_UpstreamEndpointStats_metadata(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_UpstreamEndpointStats_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_UpstreamEndpointStats_set_total_issued_requests(envoy_config_endpoint_v3_UpstreamEndpointStats *msg, uint64_t value) {
  const upb_MiniTableField field = {7, UPB_SIZE(48, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats* envoy_config_endpoint_v3_EndpointLoadMetricStats_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_EndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats* envoy_config_endpoint_v3_EndpointLoadMetricStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_EndpointLoadMetricStats* ret = envoy_config_endpoint_v3_EndpointLoadMetricStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_EndpointLoadMetricStats* envoy_config_endpoint_v3_EndpointLoadMetricStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_EndpointLoadMetricStats* ret = envoy_config_endpoint_v3_EndpointLoadMetricStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_EndpointLoadMetricStats_serialize(const envoy_config_endpoint_v3_EndpointLoadMetricStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_EndpointLoadMetricStats_serialize_ex(const envoy_config_endpoint_v3_EndpointLoadMetricStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__EndpointLoadMetricStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_EndpointLoadMetricStats_clear_metric_name(envoy_config_endpoint_v3_EndpointLoadMetricStats* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_endpoint_v3_EndpointLoadMetricStats_metric_name(const envoy_config_endpoint_v3_EndpointLoadMetricStats* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_EndpointLoadMetricStats_clear_num_requests_finished_with_metric(envoy_config_endpoint_v3_EndpointLoadMetricStats* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_EndpointLoadMetricStats_num_requests_finished_with_metric(const envoy_config_endpoint_v3_EndpointLoadMetricStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_EndpointLoadMetricStats_clear_total_metric_value(envoy_config_endpoint_v3_EndpointLoadMetricStats* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_config_endpoint_v3_EndpointLoadMetricStats_total_metric_value(const envoy_config_endpoint_v3_EndpointLoadMetricStats* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_endpoint_v3_EndpointLoadMetricStats_set_metric_name(envoy_config_endpoint_v3_EndpointLoadMetricStats *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_EndpointLoadMetricStats_set_num_requests_finished_with_metric(envoy_config_endpoint_v3_EndpointLoadMetricStats *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_EndpointLoadMetricStats_set_total_metric_value(envoy_config_endpoint_v3_EndpointLoadMetricStats *msg, double value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats*)_upb_Message_New(&envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* ret = envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* ret = envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_serialize(const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_serialize_ex(const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__UnnamedEndpointLoadMetricStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_clear_num_requests_finished_with_metric(envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_num_requests_finished_with_metric(const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_clear_total_metric_value(envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_total_metric_value(const envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_set_num_requests_finished_with_metric(envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats_set_total_metric_value(envoy_config_endpoint_v3_UnnamedEndpointLoadMetricStats *msg, double value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_endpoint_v3_ClusterStats* envoy_config_endpoint_v3_ClusterStats_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_ClusterStats*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterStats_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_ClusterStats* envoy_config_endpoint_v3_ClusterStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterStats* ret = envoy_config_endpoint_v3_ClusterStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_ClusterStats* envoy_config_endpoint_v3_ClusterStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterStats* ret = envoy_config_endpoint_v3_ClusterStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterStats_serialize(const envoy_config_endpoint_v3_ClusterStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterStats_serialize_ex(const envoy_config_endpoint_v3_ClusterStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_clear_cluster_name(envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_endpoint_v3_ClusterStats_cluster_name(const envoy_config_endpoint_v3_ClusterStats* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_clear_upstream_locality_stats(envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_UpstreamLocalityStats* const* envoy_config_endpoint_v3_ClusterStats_upstream_locality_stats(const envoy_config_endpoint_v3_ClusterStats* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_endpoint_v3_UpstreamLocalityStats* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_ClusterStats_upstream_locality_stats_upb_array(const envoy_config_endpoint_v3_ClusterStats* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_ClusterStats_upstream_locality_stats_mutable_upb_array(envoy_config_endpoint_v3_ClusterStats* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_clear_total_dropped_requests(envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_ClusterStats_total_dropped_requests(const envoy_config_endpoint_v3_ClusterStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_clear_load_report_interval(envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_endpoint_v3_ClusterStats_load_report_interval(const envoy_config_endpoint_v3_ClusterStats* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterStats_has_load_report_interval(const envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_clear_dropped_requests(envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_ClusterStats_DroppedRequests* const* envoy_config_endpoint_v3_ClusterStats_dropped_requests(const envoy_config_endpoint_v3_ClusterStats* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_endpoint_v3_ClusterStats_DroppedRequests* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_ClusterStats_dropped_requests_upb_array(const envoy_config_endpoint_v3_ClusterStats* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_ClusterStats_dropped_requests_mutable_upb_array(envoy_config_endpoint_v3_ClusterStats* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_clear_cluster_service_name(envoy_config_endpoint_v3_ClusterStats* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_endpoint_v3_ClusterStats_cluster_service_name(const envoy_config_endpoint_v3_ClusterStats* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_set_cluster_name(envoy_config_endpoint_v3_ClusterStats *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamLocalityStats** envoy_config_endpoint_v3_ClusterStats_mutable_upstream_locality_stats(envoy_config_endpoint_v3_ClusterStats* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_endpoint_v3_UpstreamLocalityStats**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_endpoint_v3_UpstreamLocalityStats** envoy_config_endpoint_v3_ClusterStats_resize_upstream_locality_stats(envoy_config_endpoint_v3_ClusterStats* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_endpoint_v3_UpstreamLocalityStats**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_UpstreamLocalityStats* envoy_config_endpoint_v3_ClusterStats_add_upstream_locality_stats(envoy_config_endpoint_v3_ClusterStats* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_UpstreamLocalityStats* sub = (struct envoy_config_endpoint_v3_UpstreamLocalityStats*)_upb_Message_New(&envoy__config__endpoint__v3__UpstreamLocalityStats_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_set_total_dropped_requests(envoy_config_endpoint_v3_ClusterStats *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_set_load_report_interval(envoy_config_endpoint_v3_ClusterStats *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_endpoint_v3_ClusterStats_mutable_load_report_interval(envoy_config_endpoint_v3_ClusterStats* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_endpoint_v3_ClusterStats_load_report_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_ClusterStats_set_load_report_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_endpoint_v3_ClusterStats_DroppedRequests** envoy_config_endpoint_v3_ClusterStats_mutable_dropped_requests(envoy_config_endpoint_v3_ClusterStats* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_endpoint_v3_ClusterStats_DroppedRequests**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_endpoint_v3_ClusterStats_DroppedRequests** envoy_config_endpoint_v3_ClusterStats_resize_dropped_requests(envoy_config_endpoint_v3_ClusterStats* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_endpoint_v3_ClusterStats_DroppedRequests**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_ClusterStats_DroppedRequests* envoy_config_endpoint_v3_ClusterStats_add_dropped_requests(envoy_config_endpoint_v3_ClusterStats* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(20, 72), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_ClusterStats_DroppedRequests* sub = (struct envoy_config_endpoint_v3_ClusterStats_DroppedRequests*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_set_cluster_service_name(envoy_config_endpoint_v3_ClusterStats *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_endpoint_v3_ClusterStats_DroppedRequests* envoy_config_endpoint_v3_ClusterStats_DroppedRequests_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_ClusterStats_DroppedRequests*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_ClusterStats_DroppedRequests* envoy_config_endpoint_v3_ClusterStats_DroppedRequests_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterStats_DroppedRequests* ret = envoy_config_endpoint_v3_ClusterStats_DroppedRequests_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_ClusterStats_DroppedRequests* envoy_config_endpoint_v3_ClusterStats_DroppedRequests_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterStats_DroppedRequests* ret = envoy_config_endpoint_v3_ClusterStats_DroppedRequests_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterStats_DroppedRequests_serialize(const envoy_config_endpoint_v3_ClusterStats_DroppedRequests* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterStats_DroppedRequests_serialize_ex(const envoy_config_endpoint_v3_ClusterStats_DroppedRequests* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterStats__DroppedRequests_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_DroppedRequests_clear_category(envoy_config_endpoint_v3_ClusterStats_DroppedRequests* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_endpoint_v3_ClusterStats_DroppedRequests_category(const envoy_config_endpoint_v3_ClusterStats_DroppedRequests* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_DroppedRequests_clear_dropped_count(envoy_config_endpoint_v3_ClusterStats_DroppedRequests* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_endpoint_v3_ClusterStats_DroppedRequests_dropped_count(const envoy_config_endpoint_v3_ClusterStats_DroppedRequests* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_DroppedRequests_set_category(envoy_config_endpoint_v3_ClusterStats_DroppedRequests *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterStats_DroppedRequests_set_dropped_count(envoy_config_endpoint_v3_ClusterStats_DroppedRequests *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
