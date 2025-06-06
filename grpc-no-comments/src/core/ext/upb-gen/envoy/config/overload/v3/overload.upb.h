
#ifndef ENVOY_CONFIG_OVERLOAD_V3_OVERLOAD_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_OVERLOAD_V3_OVERLOAD_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/overload/v3/overload.upb_minitable.h"

#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_overload_v3_ResourceMonitor { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_ResourceMonitor;
typedef struct envoy_config_overload_v3_ThresholdTrigger { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_ThresholdTrigger;
typedef struct envoy_config_overload_v3_ScaledTrigger { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_ScaledTrigger;
typedef struct envoy_config_overload_v3_Trigger { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_Trigger;
typedef struct envoy_config_overload_v3_ScaleTimersOverloadActionConfig { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_ScaleTimersOverloadActionConfig;
typedef struct envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer;
typedef struct envoy_config_overload_v3_OverloadAction { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_OverloadAction;
typedef struct envoy_config_overload_v3_LoadShedPoint { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_LoadShedPoint;
typedef struct envoy_config_overload_v3_BufferFactoryConfig { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_BufferFactoryConfig;
typedef struct envoy_config_overload_v3_OverloadManager { upb_Message UPB_PRIVATE(base); } envoy_config_overload_v3_OverloadManager;
struct envoy_type_v3_Percent;
struct google_protobuf_Any;
struct google_protobuf_Duration;

typedef enum {
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_UNSPECIFIED = 0,
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_HTTP_DOWNSTREAM_CONNECTION_IDLE = 1,
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_HTTP_DOWNSTREAM_STREAM_IDLE = 2,
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_TRANSPORT_SOCKET_CONNECT = 3,
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_HTTP_DOWNSTREAM_CONNECTION_MAX = 4
} envoy_config_overload_v3_ScaleTimersOverloadActionConfig_TimerType;

UPB_INLINE envoy_config_overload_v3_ResourceMonitor* envoy_config_overload_v3_ResourceMonitor_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_ResourceMonitor*)_upb_Message_New(&envoy__config__overload__v3__ResourceMonitor_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_ResourceMonitor* envoy_config_overload_v3_ResourceMonitor_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_ResourceMonitor* ret = envoy_config_overload_v3_ResourceMonitor_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ResourceMonitor_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_ResourceMonitor* envoy_config_overload_v3_ResourceMonitor_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_ResourceMonitor* ret = envoy_config_overload_v3_ResourceMonitor_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ResourceMonitor_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_ResourceMonitor_serialize(const envoy_config_overload_v3_ResourceMonitor* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ResourceMonitor_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_ResourceMonitor_serialize_ex(const envoy_config_overload_v3_ResourceMonitor* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ResourceMonitor_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_overload_v3_ResourceMonitor_config_type_typed_config = 3,
  envoy_config_overload_v3_ResourceMonitor_config_type_NOT_SET = 0
} envoy_config_overload_v3_ResourceMonitor_config_type_oneofcases;
UPB_INLINE envoy_config_overload_v3_ResourceMonitor_config_type_oneofcases envoy_config_overload_v3_ResourceMonitor_config_type_case(const envoy_config_overload_v3_ResourceMonitor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_ResourceMonitor_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_ResourceMonitor_clear_config_type(envoy_config_overload_v3_ResourceMonitor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__overload__v3__ResourceMonitor_msg_init, &field);
}
UPB_INLINE void envoy_config_overload_v3_ResourceMonitor_clear_name(envoy_config_overload_v3_ResourceMonitor* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_overload_v3_ResourceMonitor_name(const envoy_config_overload_v3_ResourceMonitor* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_overload_v3_ResourceMonitor_clear_typed_config(envoy_config_overload_v3_ResourceMonitor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_overload_v3_ResourceMonitor_typed_config(const envoy_config_overload_v3_ResourceMonitor* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_ResourceMonitor_has_typed_config(const envoy_config_overload_v3_ResourceMonitor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_overload_v3_ResourceMonitor_set_name(envoy_config_overload_v3_ResourceMonitor *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_overload_v3_ResourceMonitor_set_typed_config(envoy_config_overload_v3_ResourceMonitor *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_overload_v3_ResourceMonitor_mutable_typed_config(envoy_config_overload_v3_ResourceMonitor* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_overload_v3_ResourceMonitor_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_overload_v3_ResourceMonitor_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_overload_v3_ThresholdTrigger* envoy_config_overload_v3_ThresholdTrigger_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_ThresholdTrigger*)_upb_Message_New(&envoy__config__overload__v3__ThresholdTrigger_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_ThresholdTrigger* envoy_config_overload_v3_ThresholdTrigger_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_ThresholdTrigger* ret = envoy_config_overload_v3_ThresholdTrigger_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ThresholdTrigger_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_ThresholdTrigger* envoy_config_overload_v3_ThresholdTrigger_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_ThresholdTrigger* ret = envoy_config_overload_v3_ThresholdTrigger_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ThresholdTrigger_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_ThresholdTrigger_serialize(const envoy_config_overload_v3_ThresholdTrigger* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ThresholdTrigger_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_ThresholdTrigger_serialize_ex(const envoy_config_overload_v3_ThresholdTrigger* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ThresholdTrigger_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_ThresholdTrigger_clear_value(envoy_config_overload_v3_ThresholdTrigger* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_config_overload_v3_ThresholdTrigger_value(const envoy_config_overload_v3_ThresholdTrigger* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_overload_v3_ThresholdTrigger_set_value(envoy_config_overload_v3_ThresholdTrigger *msg, double value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_overload_v3_ScaledTrigger* envoy_config_overload_v3_ScaledTrigger_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_ScaledTrigger*)_upb_Message_New(&envoy__config__overload__v3__ScaledTrigger_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_ScaledTrigger* envoy_config_overload_v3_ScaledTrigger_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_ScaledTrigger* ret = envoy_config_overload_v3_ScaledTrigger_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ScaledTrigger_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_ScaledTrigger* envoy_config_overload_v3_ScaledTrigger_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_ScaledTrigger* ret = envoy_config_overload_v3_ScaledTrigger_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ScaledTrigger_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_ScaledTrigger_serialize(const envoy_config_overload_v3_ScaledTrigger* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaledTrigger_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_ScaledTrigger_serialize_ex(const envoy_config_overload_v3_ScaledTrigger* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaledTrigger_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_ScaledTrigger_clear_scaling_threshold(envoy_config_overload_v3_ScaledTrigger* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_config_overload_v3_ScaledTrigger_scaling_threshold(const envoy_config_overload_v3_ScaledTrigger* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_overload_v3_ScaledTrigger_clear_saturation_threshold(envoy_config_overload_v3_ScaledTrigger* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_config_overload_v3_ScaledTrigger_saturation_threshold(const envoy_config_overload_v3_ScaledTrigger* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_overload_v3_ScaledTrigger_set_scaling_threshold(envoy_config_overload_v3_ScaledTrigger *msg, double value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_overload_v3_ScaledTrigger_set_saturation_threshold(envoy_config_overload_v3_ScaledTrigger *msg, double value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_overload_v3_Trigger* envoy_config_overload_v3_Trigger_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_Trigger*)_upb_Message_New(&envoy__config__overload__v3__Trigger_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_Trigger* envoy_config_overload_v3_Trigger_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_Trigger* ret = envoy_config_overload_v3_Trigger_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__Trigger_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_Trigger* envoy_config_overload_v3_Trigger_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_Trigger* ret = envoy_config_overload_v3_Trigger_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__Trigger_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_Trigger_serialize(const envoy_config_overload_v3_Trigger* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__Trigger_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_Trigger_serialize_ex(const envoy_config_overload_v3_Trigger* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__Trigger_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_overload_v3_Trigger_trigger_oneof_threshold = 2,
  envoy_config_overload_v3_Trigger_trigger_oneof_scaled = 3,
  envoy_config_overload_v3_Trigger_trigger_oneof_NOT_SET = 0
} envoy_config_overload_v3_Trigger_trigger_oneof_oneofcases;
UPB_INLINE envoy_config_overload_v3_Trigger_trigger_oneof_oneofcases envoy_config_overload_v3_Trigger_trigger_oneof_case(const envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_Trigger_trigger_oneof_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_Trigger_clear_trigger_oneof(envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__overload__v3__Trigger_msg_init, &field);
}
UPB_INLINE void envoy_config_overload_v3_Trigger_clear_name(envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_overload_v3_Trigger_name(const envoy_config_overload_v3_Trigger* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_overload_v3_Trigger_clear_threshold(envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_ThresholdTrigger* envoy_config_overload_v3_Trigger_threshold(const envoy_config_overload_v3_Trigger* msg) {
  const envoy_config_overload_v3_ThresholdTrigger* default_val = NULL;
  const envoy_config_overload_v3_ThresholdTrigger* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ThresholdTrigger_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_Trigger_has_threshold(const envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_Trigger_clear_scaled(envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_ScaledTrigger* envoy_config_overload_v3_Trigger_scaled(const envoy_config_overload_v3_Trigger* msg) {
  const envoy_config_overload_v3_ScaledTrigger* default_val = NULL;
  const envoy_config_overload_v3_ScaledTrigger* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaledTrigger_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_Trigger_has_scaled(const envoy_config_overload_v3_Trigger* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_overload_v3_Trigger_set_name(envoy_config_overload_v3_Trigger *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_overload_v3_Trigger_set_threshold(envoy_config_overload_v3_Trigger *msg, envoy_config_overload_v3_ThresholdTrigger* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ThresholdTrigger_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_overload_v3_ThresholdTrigger* envoy_config_overload_v3_Trigger_mutable_threshold(envoy_config_overload_v3_Trigger* msg, upb_Arena* arena) {
  struct envoy_config_overload_v3_ThresholdTrigger* sub = (struct envoy_config_overload_v3_ThresholdTrigger*)envoy_config_overload_v3_Trigger_threshold(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_overload_v3_ThresholdTrigger*)_upb_Message_New(&envoy__config__overload__v3__ThresholdTrigger_msg_init, arena);
    if (sub) envoy_config_overload_v3_Trigger_set_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_overload_v3_Trigger_set_scaled(envoy_config_overload_v3_Trigger *msg, envoy_config_overload_v3_ScaledTrigger* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaledTrigger_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_overload_v3_ScaledTrigger* envoy_config_overload_v3_Trigger_mutable_scaled(envoy_config_overload_v3_Trigger* msg, upb_Arena* arena) {
  struct envoy_config_overload_v3_ScaledTrigger* sub = (struct envoy_config_overload_v3_ScaledTrigger*)envoy_config_overload_v3_Trigger_scaled(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_overload_v3_ScaledTrigger*)_upb_Message_New(&envoy__config__overload__v3__ScaledTrigger_msg_init, arena);
    if (sub) envoy_config_overload_v3_Trigger_set_scaled(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_ScaleTimersOverloadActionConfig*)_upb_Message_New(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig* ret = envoy_config_overload_v3_ScaleTimersOverloadActionConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig* ret = envoy_config_overload_v3_ScaleTimersOverloadActionConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_serialize(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_serialize_ex(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_clear_timer_scale_factors(envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* const* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_timer_scale_factors(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_overload_v3_ScaleTimersOverloadActionConfig_timer_scale_factors_upb_array(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_overload_v3_ScaleTimersOverloadActionConfig_timer_scale_factors_mutable_upb_array(envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer** envoy_config_overload_v3_ScaleTimersOverloadActionConfig_mutable_timer_scale_factors(envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer** envoy_config_overload_v3_ScaleTimersOverloadActionConfig_resize_timer_scale_factors(envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_add_timer_scale_factors(envoy_config_overload_v3_ScaleTimersOverloadActionConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* sub = (struct envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer*)_upb_Message_New(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer*)_upb_Message_New(&envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* ret = envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* ret = envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_serialize(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_serialize_ex(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_min_timeout = 2,
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_min_scale = 3,
  envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_NOT_SET = 0
} envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_oneofcases;
UPB_INLINE envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_oneofcases envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_case(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_overload_adjust_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_clear_overload_adjust(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__overload__v3__ScaleTimersOverloadActionConfig__ScaleTimer_msg_init, &field);
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_clear_timer(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_timer(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_clear_min_timeout(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_min_timeout(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_has_min_timeout(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_clear_min_scale(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {3, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_min_scale(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {3, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_has_min_scale(const envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg) {
  const upb_MiniTableField field = {3, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_set_timer(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_set_min_timeout(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_mutable_min_timeout(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_min_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_set_min_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_set_min_scale(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {3, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_mutable_min_scale(envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_min_scale(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_overload_v3_ScaleTimersOverloadActionConfig_ScaleTimer_set_min_scale(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_overload_v3_OverloadAction* envoy_config_overload_v3_OverloadAction_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_OverloadAction*)_upb_Message_New(&envoy__config__overload__v3__OverloadAction_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_OverloadAction* envoy_config_overload_v3_OverloadAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_OverloadAction* ret = envoy_config_overload_v3_OverloadAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__OverloadAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_OverloadAction* envoy_config_overload_v3_OverloadAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_OverloadAction* ret = envoy_config_overload_v3_OverloadAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__OverloadAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_OverloadAction_serialize(const envoy_config_overload_v3_OverloadAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__OverloadAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_OverloadAction_serialize_ex(const envoy_config_overload_v3_OverloadAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__OverloadAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_OverloadAction_clear_name(envoy_config_overload_v3_OverloadAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_overload_v3_OverloadAction_name(const envoy_config_overload_v3_OverloadAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_overload_v3_OverloadAction_clear_triggers(envoy_config_overload_v3_OverloadAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_Trigger* const* envoy_config_overload_v3_OverloadAction_triggers(const envoy_config_overload_v3_OverloadAction* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_overload_v3_Trigger* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_overload_v3_OverloadAction_triggers_upb_array(const envoy_config_overload_v3_OverloadAction* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_overload_v3_OverloadAction_triggers_mutable_upb_array(envoy_config_overload_v3_OverloadAction* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_overload_v3_OverloadAction_clear_typed_config(envoy_config_overload_v3_OverloadAction* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_overload_v3_OverloadAction_typed_config(const envoy_config_overload_v3_OverloadAction* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_OverloadAction_has_typed_config(const envoy_config_overload_v3_OverloadAction* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_overload_v3_OverloadAction_set_name(envoy_config_overload_v3_OverloadAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_overload_v3_Trigger** envoy_config_overload_v3_OverloadAction_mutable_triggers(envoy_config_overload_v3_OverloadAction* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_overload_v3_Trigger**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_overload_v3_Trigger** envoy_config_overload_v3_OverloadAction_resize_triggers(envoy_config_overload_v3_OverloadAction* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_Trigger**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_overload_v3_Trigger* envoy_config_overload_v3_OverloadAction_add_triggers(envoy_config_overload_v3_OverloadAction* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_overload_v3_Trigger* sub = (struct envoy_config_overload_v3_Trigger*)_upb_Message_New(&envoy__config__overload__v3__Trigger_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_overload_v3_OverloadAction_set_typed_config(envoy_config_overload_v3_OverloadAction *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_overload_v3_OverloadAction_mutable_typed_config(envoy_config_overload_v3_OverloadAction* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_overload_v3_OverloadAction_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_overload_v3_OverloadAction_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_overload_v3_LoadShedPoint* envoy_config_overload_v3_LoadShedPoint_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_LoadShedPoint*)_upb_Message_New(&envoy__config__overload__v3__LoadShedPoint_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_LoadShedPoint* envoy_config_overload_v3_LoadShedPoint_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_LoadShedPoint* ret = envoy_config_overload_v3_LoadShedPoint_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__LoadShedPoint_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_LoadShedPoint* envoy_config_overload_v3_LoadShedPoint_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_LoadShedPoint* ret = envoy_config_overload_v3_LoadShedPoint_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__LoadShedPoint_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_LoadShedPoint_serialize(const envoy_config_overload_v3_LoadShedPoint* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__LoadShedPoint_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_LoadShedPoint_serialize_ex(const envoy_config_overload_v3_LoadShedPoint* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__LoadShedPoint_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_LoadShedPoint_clear_name(envoy_config_overload_v3_LoadShedPoint* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_overload_v3_LoadShedPoint_name(const envoy_config_overload_v3_LoadShedPoint* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_overload_v3_LoadShedPoint_clear_triggers(envoy_config_overload_v3_LoadShedPoint* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_Trigger* const* envoy_config_overload_v3_LoadShedPoint_triggers(const envoy_config_overload_v3_LoadShedPoint* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_overload_v3_Trigger* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_overload_v3_LoadShedPoint_triggers_upb_array(const envoy_config_overload_v3_LoadShedPoint* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_overload_v3_LoadShedPoint_triggers_mutable_upb_array(envoy_config_overload_v3_LoadShedPoint* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_overload_v3_LoadShedPoint_set_name(envoy_config_overload_v3_LoadShedPoint *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_overload_v3_Trigger** envoy_config_overload_v3_LoadShedPoint_mutable_triggers(envoy_config_overload_v3_LoadShedPoint* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_overload_v3_Trigger**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_overload_v3_Trigger** envoy_config_overload_v3_LoadShedPoint_resize_triggers(envoy_config_overload_v3_LoadShedPoint* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_Trigger**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_overload_v3_Trigger* envoy_config_overload_v3_LoadShedPoint_add_triggers(envoy_config_overload_v3_LoadShedPoint* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__Trigger_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_overload_v3_Trigger* sub = (struct envoy_config_overload_v3_Trigger*)_upb_Message_New(&envoy__config__overload__v3__Trigger_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_overload_v3_BufferFactoryConfig* envoy_config_overload_v3_BufferFactoryConfig_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_BufferFactoryConfig*)_upb_Message_New(&envoy__config__overload__v3__BufferFactoryConfig_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_BufferFactoryConfig* envoy_config_overload_v3_BufferFactoryConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_BufferFactoryConfig* ret = envoy_config_overload_v3_BufferFactoryConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__BufferFactoryConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_BufferFactoryConfig* envoy_config_overload_v3_BufferFactoryConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_BufferFactoryConfig* ret = envoy_config_overload_v3_BufferFactoryConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__BufferFactoryConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_BufferFactoryConfig_serialize(const envoy_config_overload_v3_BufferFactoryConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__BufferFactoryConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_BufferFactoryConfig_serialize_ex(const envoy_config_overload_v3_BufferFactoryConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__BufferFactoryConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_BufferFactoryConfig_clear_minimum_account_to_track_power_of_two(envoy_config_overload_v3_BufferFactoryConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_overload_v3_BufferFactoryConfig_minimum_account_to_track_power_of_two(const envoy_config_overload_v3_BufferFactoryConfig* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_overload_v3_BufferFactoryConfig_set_minimum_account_to_track_power_of_two(envoy_config_overload_v3_BufferFactoryConfig *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_overload_v3_OverloadManager* envoy_config_overload_v3_OverloadManager_new(upb_Arena* arena) {
  return (envoy_config_overload_v3_OverloadManager*)_upb_Message_New(&envoy__config__overload__v3__OverloadManager_msg_init, arena);
}
UPB_INLINE envoy_config_overload_v3_OverloadManager* envoy_config_overload_v3_OverloadManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_overload_v3_OverloadManager* ret = envoy_config_overload_v3_OverloadManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__OverloadManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_overload_v3_OverloadManager* envoy_config_overload_v3_OverloadManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_overload_v3_OverloadManager* ret = envoy_config_overload_v3_OverloadManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__overload__v3__OverloadManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_overload_v3_OverloadManager_serialize(const envoy_config_overload_v3_OverloadManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__OverloadManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_overload_v3_OverloadManager_serialize_ex(const envoy_config_overload_v3_OverloadManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__overload__v3__OverloadManager_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_overload_v3_OverloadManager_clear_refresh_interval(envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_overload_v3_OverloadManager_refresh_interval(const envoy_config_overload_v3_OverloadManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_OverloadManager_has_refresh_interval(const envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_OverloadManager_clear_resource_monitors(envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_ResourceMonitor* const* envoy_config_overload_v3_OverloadManager_resource_monitors(const envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ResourceMonitor_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_overload_v3_ResourceMonitor* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_overload_v3_OverloadManager_resource_monitors_upb_array(const envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ResourceMonitor_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_overload_v3_OverloadManager_resource_monitors_mutable_upb_array(envoy_config_overload_v3_OverloadManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ResourceMonitor_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_overload_v3_OverloadManager_clear_actions(envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_OverloadAction* const* envoy_config_overload_v3_OverloadManager_actions(const envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadAction_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_overload_v3_OverloadAction* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_overload_v3_OverloadManager_actions_upb_array(const envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadAction_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_overload_v3_OverloadManager_actions_mutable_upb_array(envoy_config_overload_v3_OverloadManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadAction_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_overload_v3_OverloadManager_clear_buffer_factory_config(envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_BufferFactoryConfig* envoy_config_overload_v3_OverloadManager_buffer_factory_config(const envoy_config_overload_v3_OverloadManager* msg) {
  const envoy_config_overload_v3_BufferFactoryConfig* default_val = NULL;
  const envoy_config_overload_v3_BufferFactoryConfig* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__BufferFactoryConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_overload_v3_OverloadManager_has_buffer_factory_config(const envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_overload_v3_OverloadManager_clear_loadshed_points(envoy_config_overload_v3_OverloadManager* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_overload_v3_LoadShedPoint* const* envoy_config_overload_v3_OverloadManager_loadshed_points(const envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__LoadShedPoint_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_overload_v3_LoadShedPoint* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_overload_v3_OverloadManager_loadshed_points_upb_array(const envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__LoadShedPoint_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_overload_v3_OverloadManager_loadshed_points_mutable_upb_array(envoy_config_overload_v3_OverloadManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__LoadShedPoint_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_overload_v3_OverloadManager_set_refresh_interval(envoy_config_overload_v3_OverloadManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_overload_v3_OverloadManager_mutable_refresh_interval(envoy_config_overload_v3_OverloadManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_overload_v3_OverloadManager_refresh_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_overload_v3_OverloadManager_set_refresh_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_overload_v3_ResourceMonitor** envoy_config_overload_v3_OverloadManager_mutable_resource_monitors(envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ResourceMonitor_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_overload_v3_ResourceMonitor**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_overload_v3_ResourceMonitor** envoy_config_overload_v3_OverloadManager_resize_resource_monitors(envoy_config_overload_v3_OverloadManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_ResourceMonitor**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_overload_v3_ResourceMonitor* envoy_config_overload_v3_OverloadManager_add_resource_monitors(envoy_config_overload_v3_OverloadManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__ResourceMonitor_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_overload_v3_ResourceMonitor* sub = (struct envoy_config_overload_v3_ResourceMonitor*)_upb_Message_New(&envoy__config__overload__v3__ResourceMonitor_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_config_overload_v3_OverloadAction** envoy_config_overload_v3_OverloadManager_mutable_actions(envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadAction_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_overload_v3_OverloadAction**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_overload_v3_OverloadAction** envoy_config_overload_v3_OverloadManager_resize_actions(envoy_config_overload_v3_OverloadManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_OverloadAction**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_overload_v3_OverloadAction* envoy_config_overload_v3_OverloadManager_add_actions(envoy_config_overload_v3_OverloadManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadAction_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_overload_v3_OverloadAction* sub = (struct envoy_config_overload_v3_OverloadAction*)_upb_Message_New(&envoy__config__overload__v3__OverloadAction_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_overload_v3_OverloadManager_set_buffer_factory_config(envoy_config_overload_v3_OverloadManager *msg, envoy_config_overload_v3_BufferFactoryConfig* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__BufferFactoryConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_overload_v3_BufferFactoryConfig* envoy_config_overload_v3_OverloadManager_mutable_buffer_factory_config(envoy_config_overload_v3_OverloadManager* msg, upb_Arena* arena) {
  struct envoy_config_overload_v3_BufferFactoryConfig* sub = (struct envoy_config_overload_v3_BufferFactoryConfig*)envoy_config_overload_v3_OverloadManager_buffer_factory_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_overload_v3_BufferFactoryConfig*)_upb_Message_New(&envoy__config__overload__v3__BufferFactoryConfig_msg_init, arena);
    if (sub) envoy_config_overload_v3_OverloadManager_set_buffer_factory_config(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_overload_v3_LoadShedPoint** envoy_config_overload_v3_OverloadManager_mutable_loadshed_points(envoy_config_overload_v3_OverloadManager* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__LoadShedPoint_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_overload_v3_LoadShedPoint**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_overload_v3_LoadShedPoint** envoy_config_overload_v3_OverloadManager_resize_loadshed_points(envoy_config_overload_v3_OverloadManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_overload_v3_LoadShedPoint**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_overload_v3_LoadShedPoint* envoy_config_overload_v3_OverloadManager_add_loadshed_points(envoy_config_overload_v3_OverloadManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__LoadShedPoint_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_overload_v3_LoadShedPoint* sub = (struct envoy_config_overload_v3_LoadShedPoint*)_upb_Message_New(&envoy__config__overload__v3__LoadShedPoint_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
