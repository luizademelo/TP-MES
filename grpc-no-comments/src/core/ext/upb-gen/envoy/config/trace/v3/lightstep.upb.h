
#ifndef ENVOY_CONFIG_TRACE_V3_LIGHTSTEP_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_TRACE_V3_LIGHTSTEP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/lightstep.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_trace_v3_LightstepConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_LightstepConfig;
struct envoy_config_core_v3_DataSource;

typedef enum {
  envoy_config_trace_v3_LightstepConfig_ENVOY = 0,
  envoy_config_trace_v3_LightstepConfig_LIGHTSTEP = 1,
  envoy_config_trace_v3_LightstepConfig_B3 = 2,
  envoy_config_trace_v3_LightstepConfig_TRACE_CONTEXT = 3
} envoy_config_trace_v3_LightstepConfig_PropagationMode;

UPB_INLINE envoy_config_trace_v3_LightstepConfig* envoy_config_trace_v3_LightstepConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_LightstepConfig*)_upb_Message_New(&envoy__config__trace__v3__LightstepConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_LightstepConfig* envoy_config_trace_v3_LightstepConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_LightstepConfig* ret = envoy_config_trace_v3_LightstepConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__LightstepConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_LightstepConfig* envoy_config_trace_v3_LightstepConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_LightstepConfig* ret = envoy_config_trace_v3_LightstepConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__LightstepConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_LightstepConfig_serialize(const envoy_config_trace_v3_LightstepConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__LightstepConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_LightstepConfig_serialize_ex(const envoy_config_trace_v3_LightstepConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__LightstepConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_LightstepConfig_clear_collector_cluster(envoy_config_trace_v3_LightstepConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_LightstepConfig_collector_cluster(const envoy_config_trace_v3_LightstepConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_LightstepConfig_clear_access_token_file(envoy_config_trace_v3_LightstepConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_LightstepConfig_access_token_file(const envoy_config_trace_v3_LightstepConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_LightstepConfig_clear_propagation_modes(envoy_config_trace_v3_LightstepConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* envoy_config_trace_v3_LightstepConfig_propagation_modes(const envoy_config_trace_v3_LightstepConfig* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_trace_v3_LightstepConfig_propagation_modes_upb_array(const envoy_config_trace_v3_LightstepConfig* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_trace_v3_LightstepConfig_propagation_modes_mutable_upb_array(envoy_config_trace_v3_LightstepConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_trace_v3_LightstepConfig_clear_access_token(envoy_config_trace_v3_LightstepConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_trace_v3_LightstepConfig_access_token(const envoy_config_trace_v3_LightstepConfig* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_LightstepConfig_has_access_token(const envoy_config_trace_v3_LightstepConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_LightstepConfig_set_collector_cluster(envoy_config_trace_v3_LightstepConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_LightstepConfig_set_access_token_file(envoy_config_trace_v3_LightstepConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* envoy_config_trace_v3_LightstepConfig_mutable_propagation_modes(envoy_config_trace_v3_LightstepConfig* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* envoy_config_trace_v3_LightstepConfig_resize_propagation_modes(envoy_config_trace_v3_LightstepConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_trace_v3_LightstepConfig_add_propagation_modes(envoy_config_trace_v3_LightstepConfig* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_trace_v3_LightstepConfig_set_access_token(envoy_config_trace_v3_LightstepConfig *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_trace_v3_LightstepConfig_mutable_access_token(envoy_config_trace_v3_LightstepConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_trace_v3_LightstepConfig_access_token(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_trace_v3_LightstepConfig_set_access_token(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
