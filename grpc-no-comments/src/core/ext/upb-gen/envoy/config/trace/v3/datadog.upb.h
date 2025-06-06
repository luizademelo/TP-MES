
#ifndef ENVOY_CONFIG_TRACE_V3_DATADOG_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_TRACE_V3_DATADOG_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/datadog.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_trace_v3_DatadogRemoteConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_DatadogRemoteConfig;
typedef struct envoy_config_trace_v3_DatadogConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_DatadogConfig;
struct google_protobuf_Duration;

UPB_INLINE envoy_config_trace_v3_DatadogRemoteConfig* envoy_config_trace_v3_DatadogRemoteConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_DatadogRemoteConfig*)_upb_Message_New(&envoy__config__trace__v3__DatadogRemoteConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_DatadogRemoteConfig* envoy_config_trace_v3_DatadogRemoteConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_DatadogRemoteConfig* ret = envoy_config_trace_v3_DatadogRemoteConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__DatadogRemoteConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_DatadogRemoteConfig* envoy_config_trace_v3_DatadogRemoteConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_DatadogRemoteConfig* ret = envoy_config_trace_v3_DatadogRemoteConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__DatadogRemoteConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_DatadogRemoteConfig_serialize(const envoy_config_trace_v3_DatadogRemoteConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__DatadogRemoteConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_DatadogRemoteConfig_serialize_ex(const envoy_config_trace_v3_DatadogRemoteConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__DatadogRemoteConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_DatadogRemoteConfig_clear_polling_interval(envoy_config_trace_v3_DatadogRemoteConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_trace_v3_DatadogRemoteConfig_polling_interval(const envoy_config_trace_v3_DatadogRemoteConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_DatadogRemoteConfig_has_polling_interval(const envoy_config_trace_v3_DatadogRemoteConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_DatadogRemoteConfig_set_polling_interval(envoy_config_trace_v3_DatadogRemoteConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_trace_v3_DatadogRemoteConfig_mutable_polling_interval(envoy_config_trace_v3_DatadogRemoteConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_trace_v3_DatadogRemoteConfig_polling_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_trace_v3_DatadogRemoteConfig_set_polling_interval(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_trace_v3_DatadogConfig* envoy_config_trace_v3_DatadogConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_DatadogConfig*)_upb_Message_New(&envoy__config__trace__v3__DatadogConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_DatadogConfig* envoy_config_trace_v3_DatadogConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_DatadogConfig* ret = envoy_config_trace_v3_DatadogConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__DatadogConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_DatadogConfig* envoy_config_trace_v3_DatadogConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_DatadogConfig* ret = envoy_config_trace_v3_DatadogConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__DatadogConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_DatadogConfig_serialize(const envoy_config_trace_v3_DatadogConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__DatadogConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_DatadogConfig_serialize_ex(const envoy_config_trace_v3_DatadogConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__DatadogConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_clear_collector_cluster(envoy_config_trace_v3_DatadogConfig* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_DatadogConfig_collector_cluster(const envoy_config_trace_v3_DatadogConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_clear_service_name(envoy_config_trace_v3_DatadogConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_DatadogConfig_service_name(const envoy_config_trace_v3_DatadogConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_clear_collector_hostname(envoy_config_trace_v3_DatadogConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_DatadogConfig_collector_hostname(const envoy_config_trace_v3_DatadogConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_clear_remote_config(envoy_config_trace_v3_DatadogConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_trace_v3_DatadogRemoteConfig* envoy_config_trace_v3_DatadogConfig_remote_config(const envoy_config_trace_v3_DatadogConfig* msg) {
  const envoy_config_trace_v3_DatadogRemoteConfig* default_val = NULL;
  const envoy_config_trace_v3_DatadogRemoteConfig* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__DatadogRemoteConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_DatadogConfig_has_remote_config(const envoy_config_trace_v3_DatadogConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_DatadogConfig_set_collector_cluster(envoy_config_trace_v3_DatadogConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_set_service_name(envoy_config_trace_v3_DatadogConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_set_collector_hostname(envoy_config_trace_v3_DatadogConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_DatadogConfig_set_remote_config(envoy_config_trace_v3_DatadogConfig *msg, envoy_config_trace_v3_DatadogRemoteConfig* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__DatadogRemoteConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_trace_v3_DatadogRemoteConfig* envoy_config_trace_v3_DatadogConfig_mutable_remote_config(envoy_config_trace_v3_DatadogConfig* msg, upb_Arena* arena) {
  struct envoy_config_trace_v3_DatadogRemoteConfig* sub = (struct envoy_config_trace_v3_DatadogRemoteConfig*)envoy_config_trace_v3_DatadogConfig_remote_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_trace_v3_DatadogRemoteConfig*)_upb_Message_New(&envoy__config__trace__v3__DatadogRemoteConfig_msg_init, arena);
    if (sub) envoy_config_trace_v3_DatadogConfig_set_remote_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
