
#ifndef ENVOY_CONFIG_TRACE_V3_DYNAMIC_OT_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_TRACE_V3_DYNAMIC_OT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/dynamic_ot.upb_minitable.h"

#include "google/protobuf/struct.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_trace_v3_DynamicOtConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_DynamicOtConfig;
struct google_protobuf_Struct;

UPB_INLINE envoy_config_trace_v3_DynamicOtConfig* envoy_config_trace_v3_DynamicOtConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_DynamicOtConfig*)_upb_Message_New(&envoy__config__trace__v3__DynamicOtConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_DynamicOtConfig* envoy_config_trace_v3_DynamicOtConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_DynamicOtConfig* ret = envoy_config_trace_v3_DynamicOtConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__DynamicOtConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_DynamicOtConfig* envoy_config_trace_v3_DynamicOtConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_DynamicOtConfig* ret = envoy_config_trace_v3_DynamicOtConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__DynamicOtConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_DynamicOtConfig_serialize(const envoy_config_trace_v3_DynamicOtConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__DynamicOtConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_DynamicOtConfig_serialize_ex(const envoy_config_trace_v3_DynamicOtConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__DynamicOtConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_DynamicOtConfig_clear_library(envoy_config_trace_v3_DynamicOtConfig* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_DynamicOtConfig_library(const envoy_config_trace_v3_DynamicOtConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_DynamicOtConfig_clear_config(envoy_config_trace_v3_DynamicOtConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_trace_v3_DynamicOtConfig_config(const envoy_config_trace_v3_DynamicOtConfig* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_DynamicOtConfig_has_config(const envoy_config_trace_v3_DynamicOtConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_DynamicOtConfig_set_library(envoy_config_trace_v3_DynamicOtConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_DynamicOtConfig_set_config(envoy_config_trace_v3_DynamicOtConfig *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_trace_v3_DynamicOtConfig_mutable_config(envoy_config_trace_v3_DynamicOtConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_trace_v3_DynamicOtConfig_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_trace_v3_DynamicOtConfig_set_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
