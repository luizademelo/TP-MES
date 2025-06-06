
#ifndef ENVOY_CONFIG_METRICS_V3_METRICS_SERVICE_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_METRICS_V3_METRICS_SERVICE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/metrics/v3/metrics_service.upb_minitable.h"

#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/config/core/v3/grpc_service.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_metrics_v3_MetricsServiceConfig { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_MetricsServiceConfig;
struct envoy_config_core_v3_GrpcService;
struct google_protobuf_BoolValue;

typedef enum {
  envoy_config_metrics_v3_SUMMARY_AND_HISTOGRAM = 0,
  envoy_config_metrics_v3_SUMMARY = 1,
  envoy_config_metrics_v3_HISTOGRAM = 2
} envoy_config_metrics_v3_HistogramEmitMode;

UPB_INLINE envoy_config_metrics_v3_MetricsServiceConfig* envoy_config_metrics_v3_MetricsServiceConfig_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_MetricsServiceConfig*)_upb_Message_New(&envoy__config__metrics__v3__MetricsServiceConfig_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_MetricsServiceConfig* envoy_config_metrics_v3_MetricsServiceConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_MetricsServiceConfig* ret = envoy_config_metrics_v3_MetricsServiceConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__MetricsServiceConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_MetricsServiceConfig* envoy_config_metrics_v3_MetricsServiceConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_MetricsServiceConfig* ret = envoy_config_metrics_v3_MetricsServiceConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__MetricsServiceConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_MetricsServiceConfig_serialize(const envoy_config_metrics_v3_MetricsServiceConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__MetricsServiceConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_MetricsServiceConfig_serialize_ex(const envoy_config_metrics_v3_MetricsServiceConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__MetricsServiceConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_clear_grpc_service(envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_GrpcService* envoy_config_metrics_v3_MetricsServiceConfig_grpc_service(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const struct envoy_config_core_v3_GrpcService* default_val = NULL;
  const struct envoy_config_core_v3_GrpcService* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_MetricsServiceConfig_has_grpc_service(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_clear_report_counters_as_deltas(envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_metrics_v3_MetricsServiceConfig_report_counters_as_deltas(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_MetricsServiceConfig_has_report_counters_as_deltas(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_clear_transport_api_version(envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_metrics_v3_MetricsServiceConfig_transport_api_version(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_clear_emit_tags_as_labels(envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_metrics_v3_MetricsServiceConfig_emit_tags_as_labels(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_clear_histogram_emit_mode(envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_metrics_v3_MetricsServiceConfig_histogram_emit_mode(const envoy_config_metrics_v3_MetricsServiceConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_set_grpc_service(envoy_config_metrics_v3_MetricsServiceConfig *msg, struct envoy_config_core_v3_GrpcService* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__GrpcService_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_GrpcService* envoy_config_metrics_v3_MetricsServiceConfig_mutable_grpc_service(envoy_config_metrics_v3_MetricsServiceConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_GrpcService* sub = (struct envoy_config_core_v3_GrpcService*)envoy_config_metrics_v3_MetricsServiceConfig_grpc_service(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_GrpcService*)_upb_Message_New(&envoy__config__core__v3__GrpcService_msg_init, arena);
    if (sub) envoy_config_metrics_v3_MetricsServiceConfig_set_grpc_service(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_set_report_counters_as_deltas(envoy_config_metrics_v3_MetricsServiceConfig *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 32), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_metrics_v3_MetricsServiceConfig_mutable_report_counters_as_deltas(envoy_config_metrics_v3_MetricsServiceConfig* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_metrics_v3_MetricsServiceConfig_report_counters_as_deltas(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_metrics_v3_MetricsServiceConfig_set_report_counters_as_deltas(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_set_transport_api_version(envoy_config_metrics_v3_MetricsServiceConfig *msg, int32_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_set_emit_tags_as_labels(envoy_config_metrics_v3_MetricsServiceConfig *msg, bool value) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_MetricsServiceConfig_set_histogram_emit_mode(envoy_config_metrics_v3_MetricsServiceConfig *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
