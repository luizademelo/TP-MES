
#ifndef ENVOY_CONFIG_CLUSTER_V3_OUTLIER_DETECTION_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CLUSTER_V3_OUTLIER_DETECTION_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/cluster/v3/outlier_detection.upb_minitable.h"

#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_cluster_v3_OutlierDetection { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_OutlierDetection;
struct envoy_config_core_v3_TypedExtensionConfig;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_config_cluster_v3_OutlierDetection* envoy_config_cluster_v3_OutlierDetection_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_OutlierDetection*)_upb_Message_New(&envoy__config__cluster__v3__OutlierDetection_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_OutlierDetection* envoy_config_cluster_v3_OutlierDetection_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_OutlierDetection* ret = envoy_config_cluster_v3_OutlierDetection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__OutlierDetection_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_OutlierDetection* envoy_config_cluster_v3_OutlierDetection_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_OutlierDetection* ret = envoy_config_cluster_v3_OutlierDetection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__OutlierDetection_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_OutlierDetection_serialize(const envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__OutlierDetection_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_OutlierDetection_serialize_ex(const envoy_config_cluster_v3_OutlierDetection* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__OutlierDetection_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_consecutive_5xx(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_consecutive_5xx(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_consecutive_5xx(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_interval(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_interval(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_interval(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_base_ejection_time(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_base_ejection_time(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_base_ejection_time(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_max_ejection_percent(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_max_ejection_percent(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_max_ejection_percent(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_consecutive_5xx(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_consecutive_5xx(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_consecutive_5xx(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_success_rate(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_success_rate(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_success_rate(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_success_rate_minimum_hosts(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_success_rate_minimum_hosts(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_success_rate_minimum_hosts(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_success_rate_request_volume(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_success_rate_request_volume(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_success_rate_request_volume(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_success_rate_stdev_factor(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 80), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_success_rate_stdev_factor(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(44, 80), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_success_rate_stdev_factor(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 80), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_consecutive_gateway_failure(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(48, 88), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_consecutive_gateway_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(48, 88), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_consecutive_gateway_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(48, 88), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_consecutive_gateway_failure(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(52, 96), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_consecutive_gateway_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(52, 96), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_consecutive_gateway_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(52, 96), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_split_external_local_origin_errors(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {12, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_split_external_local_origin_errors(const envoy_config_cluster_v3_OutlierDetection* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {12, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_consecutive_local_origin_failure(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(56, 104), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_consecutive_local_origin_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(56, 104), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_consecutive_local_origin_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(56, 104), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_consecutive_local_origin_failure(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 112), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_consecutive_local_origin_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(60, 112), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_consecutive_local_origin_failure(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 112), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_local_origin_success_rate(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(64, 120), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_local_origin_success_rate(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(64, 120), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_local_origin_success_rate(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(64, 120), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_failure_percentage_threshold(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(68, 128), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_failure_percentage_threshold(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(68, 128), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_failure_percentage_threshold(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(68, 128), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_failure_percentage(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(72, 136), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_failure_percentage(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(72, 136), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_failure_percentage(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(72, 136), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_enforcing_failure_percentage_local_origin(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(76, 144), 80, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_enforcing_failure_percentage_local_origin(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {18, UPB_SIZE(76, 144), 80, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_enforcing_failure_percentage_local_origin(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(76, 144), 80, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_failure_percentage_minimum_hosts(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(80, 152), 81, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_failure_percentage_minimum_hosts(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {19, UPB_SIZE(80, 152), 81, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_failure_percentage_minimum_hosts(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(80, 152), 81, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_failure_percentage_request_volume(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(84, 160), 82, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_failure_percentage_request_volume(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(84, 160), 82, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_failure_percentage_request_volume(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(84, 160), 82, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_max_ejection_time(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(88, 168), 83, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_max_ejection_time(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {21, UPB_SIZE(88, 168), 83, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_max_ejection_time(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(88, 168), 83, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_max_ejection_time_jitter(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(92, 176), 84, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_max_ejection_time_jitter(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {22, UPB_SIZE(92, 176), 84, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_max_ejection_time_jitter(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(92, 176), 84, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_successful_active_health_check_uneject_host(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(96, 184), 85, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_cluster_v3_OutlierDetection_successful_active_health_check_uneject_host(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {23, UPB_SIZE(96, 184), 85, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_successful_active_health_check_uneject_host(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(96, 184), 85, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_monitors(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_config_cluster_v3_OutlierDetection_monitors(const envoy_config_cluster_v3_OutlierDetection* msg, size_t* size) {
  const upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_OutlierDetection_monitors_upb_array(const envoy_config_cluster_v3_OutlierDetection* msg, size_t* size) {
  const upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_OutlierDetection_monitors_mutable_upb_array(envoy_config_cluster_v3_OutlierDetection* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_clear_always_eject_one_host(envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(104, 200), 86, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_cluster_v3_OutlierDetection_always_eject_one_host(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {25, UPB_SIZE(104, 200), 86, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_OutlierDetection_has_always_eject_one_host(const envoy_config_cluster_v3_OutlierDetection* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(104, 200), 86, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_consecutive_5xx(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_consecutive_5xx(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_consecutive_5xx(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_consecutive_5xx(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_interval(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_mutable_interval(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_OutlierDetection_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_base_ejection_time(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_mutable_base_ejection_time(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_OutlierDetection_base_ejection_time(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_base_ejection_time(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_max_ejection_percent(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_max_ejection_percent(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_max_ejection_percent(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_max_ejection_percent(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_consecutive_5xx(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_consecutive_5xx(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_consecutive_5xx(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_consecutive_5xx(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_success_rate(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_success_rate(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_success_rate(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_success_rate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_success_rate_minimum_hosts(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_success_rate_minimum_hosts(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_success_rate_minimum_hosts(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_success_rate_minimum_hosts(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_success_rate_request_volume(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 72), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_success_rate_request_volume(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_success_rate_request_volume(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_success_rate_request_volume(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_success_rate_stdev_factor(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 80), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_success_rate_stdev_factor(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_success_rate_stdev_factor(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_success_rate_stdev_factor(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_consecutive_gateway_failure(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(48, 88), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_consecutive_gateway_failure(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_consecutive_gateway_failure(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_consecutive_gateway_failure(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_consecutive_gateway_failure(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(52, 96), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_consecutive_gateway_failure(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_consecutive_gateway_failure(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_consecutive_gateway_failure(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_split_external_local_origin_errors(envoy_config_cluster_v3_OutlierDetection *msg, bool value) {
  const upb_MiniTableField field = {12, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_consecutive_local_origin_failure(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(56, 104), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_consecutive_local_origin_failure(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_consecutive_local_origin_failure(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_consecutive_local_origin_failure(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_consecutive_local_origin_failure(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 112), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_consecutive_local_origin_failure(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_consecutive_local_origin_failure(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_consecutive_local_origin_failure(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_local_origin_success_rate(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(64, 120), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_local_origin_success_rate(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_local_origin_success_rate(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_local_origin_success_rate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_failure_percentage_threshold(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(68, 128), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_failure_percentage_threshold(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_failure_percentage_threshold(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_failure_percentage_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_failure_percentage(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(72, 136), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_failure_percentage(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_failure_percentage(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_failure_percentage(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_enforcing_failure_percentage_local_origin(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {18, UPB_SIZE(76, 144), 80, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_enforcing_failure_percentage_local_origin(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_enforcing_failure_percentage_local_origin(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_enforcing_failure_percentage_local_origin(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_failure_percentage_minimum_hosts(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {19, UPB_SIZE(80, 152), 81, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_failure_percentage_minimum_hosts(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_failure_percentage_minimum_hosts(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_failure_percentage_minimum_hosts(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_failure_percentage_request_volume(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(84, 160), 82, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_OutlierDetection_mutable_failure_percentage_request_volume(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_OutlierDetection_failure_percentage_request_volume(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_failure_percentage_request_volume(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_max_ejection_time(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {21, UPB_SIZE(88, 168), 83, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_mutable_max_ejection_time(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_OutlierDetection_max_ejection_time(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_max_ejection_time(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_max_ejection_time_jitter(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {22, UPB_SIZE(92, 176), 84, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_OutlierDetection_mutable_max_ejection_time_jitter(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_OutlierDetection_max_ejection_time_jitter(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_max_ejection_time_jitter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_successful_active_health_check_uneject_host(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {23, UPB_SIZE(96, 184), 85, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_cluster_v3_OutlierDetection_mutable_successful_active_health_check_uneject_host(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_cluster_v3_OutlierDetection_successful_active_health_check_uneject_host(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_successful_active_health_check_uneject_host(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_cluster_v3_OutlierDetection_mutable_monitors(envoy_config_cluster_v3_OutlierDetection* msg, size_t* size) {
  upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_cluster_v3_OutlierDetection_resize_monitors(envoy_config_cluster_v3_OutlierDetection* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_OutlierDetection_add_monitors(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  upb_MiniTableField field = {24, UPB_SIZE(100, 192), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_cluster_v3_OutlierDetection_set_always_eject_one_host(envoy_config_cluster_v3_OutlierDetection *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {25, UPB_SIZE(104, 200), 86, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_cluster_v3_OutlierDetection_mutable_always_eject_one_host(envoy_config_cluster_v3_OutlierDetection* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_cluster_v3_OutlierDetection_always_eject_one_host(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_cluster_v3_OutlierDetection_set_always_eject_one_host(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
