
#ifndef ENVOY_CONFIG_TRACE_V3_ZIPKIN_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_TRACE_V3_ZIPKIN_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/zipkin.upb_minitable.h"

#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_trace_v3_ZipkinConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_ZipkinConfig;
struct google_protobuf_BoolValue;

typedef enum {
  envoy_config_trace_v3_ZipkinConfig_DEPRECATED_AND_UNAVAILABLE_DO_NOT_USE = 0,
  envoy_config_trace_v3_ZipkinConfig_HTTP_JSON = 1,
  envoy_config_trace_v3_ZipkinConfig_HTTP_PROTO = 2,
  envoy_config_trace_v3_ZipkinConfig_GRPC = 3
} envoy_config_trace_v3_ZipkinConfig_CollectorEndpointVersion;

UPB_INLINE envoy_config_trace_v3_ZipkinConfig* envoy_config_trace_v3_ZipkinConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_ZipkinConfig*)_upb_Message_New(&envoy__config__trace__v3__ZipkinConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_ZipkinConfig* envoy_config_trace_v3_ZipkinConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_ZipkinConfig* ret = envoy_config_trace_v3_ZipkinConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__ZipkinConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_ZipkinConfig* envoy_config_trace_v3_ZipkinConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_ZipkinConfig* ret = envoy_config_trace_v3_ZipkinConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__ZipkinConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_ZipkinConfig_serialize(const envoy_config_trace_v3_ZipkinConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__ZipkinConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_ZipkinConfig_serialize_ex(const envoy_config_trace_v3_ZipkinConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__ZipkinConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_collector_cluster(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_ZipkinConfig_collector_cluster(const envoy_config_trace_v3_ZipkinConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_collector_endpoint(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_ZipkinConfig_collector_endpoint(const envoy_config_trace_v3_ZipkinConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_trace_id_128bit(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_trace_v3_ZipkinConfig_trace_id_128bit(const envoy_config_trace_v3_ZipkinConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_shared_span_context(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_trace_v3_ZipkinConfig_shared_span_context(const envoy_config_trace_v3_ZipkinConfig* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_ZipkinConfig_has_shared_span_context(const envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_collector_endpoint_version(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_trace_v3_ZipkinConfig_collector_endpoint_version(const envoy_config_trace_v3_ZipkinConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_collector_hostname(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_ZipkinConfig_collector_hostname(const envoy_config_trace_v3_ZipkinConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_clear_split_spans_for_request(envoy_config_trace_v3_ZipkinConfig* msg) {
  const upb_MiniTableField field = {7, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_trace_v3_ZipkinConfig_split_spans_for_request(const envoy_config_trace_v3_ZipkinConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_collector_cluster(envoy_config_trace_v3_ZipkinConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_collector_endpoint(envoy_config_trace_v3_ZipkinConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_trace_id_128bit(envoy_config_trace_v3_ZipkinConfig *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_shared_span_context(envoy_config_trace_v3_ZipkinConfig *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_trace_v3_ZipkinConfig_mutable_shared_span_context(envoy_config_trace_v3_ZipkinConfig* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_trace_v3_ZipkinConfig_shared_span_context(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_trace_v3_ZipkinConfig_set_shared_span_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_collector_endpoint_version(envoy_config_trace_v3_ZipkinConfig *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_collector_hostname(envoy_config_trace_v3_ZipkinConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_ZipkinConfig_set_split_spans_for_request(envoy_config_trace_v3_ZipkinConfig *msg, bool value) {
  const upb_MiniTableField field = {7, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
