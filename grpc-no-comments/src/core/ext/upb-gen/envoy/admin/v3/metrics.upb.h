
#ifndef ENVOY_ADMIN_V3_METRICS_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_METRICS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/metrics.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_SimpleMetric { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_SimpleMetric;

typedef enum {
  envoy_admin_v3_SimpleMetric_COUNTER = 0,
  envoy_admin_v3_SimpleMetric_GAUGE = 1
} envoy_admin_v3_SimpleMetric_Type;

UPB_INLINE envoy_admin_v3_SimpleMetric* envoy_admin_v3_SimpleMetric_new(upb_Arena* arena) {
  return (envoy_admin_v3_SimpleMetric*)_upb_Message_New(&envoy__admin__v3__SimpleMetric_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_SimpleMetric* envoy_admin_v3_SimpleMetric_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_SimpleMetric* ret = envoy_admin_v3_SimpleMetric_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SimpleMetric_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_SimpleMetric* envoy_admin_v3_SimpleMetric_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_SimpleMetric* ret = envoy_admin_v3_SimpleMetric_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SimpleMetric_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_SimpleMetric_serialize(const envoy_admin_v3_SimpleMetric* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SimpleMetric_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_SimpleMetric_serialize_ex(const envoy_admin_v3_SimpleMetric* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SimpleMetric_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_SimpleMetric_clear_type(envoy_admin_v3_SimpleMetric* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_SimpleMetric_type(const envoy_admin_v3_SimpleMetric* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_SimpleMetric_clear_value(envoy_admin_v3_SimpleMetric* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_SimpleMetric_value(const envoy_admin_v3_SimpleMetric* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_SimpleMetric_clear_name(envoy_admin_v3_SimpleMetric* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SimpleMetric_name(const envoy_admin_v3_SimpleMetric* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_SimpleMetric_set_type(envoy_admin_v3_SimpleMetric *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SimpleMetric_set_value(envoy_admin_v3_SimpleMetric *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SimpleMetric_set_name(envoy_admin_v3_SimpleMetric *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
