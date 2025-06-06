
#ifndef ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_CLIENT_SIDE_WEIGHTED_ROUND_ROBIN_V3_CLIENT_SIDE_WEIGHTED_ROUND_ROBIN_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_CLIENT_SIDE_WEIGHTED_ROUND_ROBIN_V3_CLIENT_SIDE_WEIGHTED_ROUND_ROBIN_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/load_balancing_policies/client_side_weighted_round_robin/v3/client_side_weighted_round_robin.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_FloatValue;

UPB_INLINE envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__client_0side_0weighted_0round_0robin__v3__ClientSideWeightedRoundRobin_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* ret = envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__client_0side_0weighted_0round_0robin__v3__ClientSideWeightedRoundRobin_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* ret = envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__client_0side_0weighted_0round_0robin__v3__ClientSideWeightedRoundRobin_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_serialize(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__client_0side_0weighted_0round_0robin__v3__ClientSideWeightedRoundRobin_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_serialize_ex(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__client_0side_0weighted_0round_0robin__v3__ClientSideWeightedRoundRobin_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_enable_oob_load_report(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_enable_oob_load_report(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_has_enable_oob_load_report(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_oob_reporting_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_oob_reporting_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_has_oob_reporting_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_blackout_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_blackout_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_has_blackout_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_weight_expiration_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_weight_expiration_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_has_weight_expiration_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_weight_update_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_weight_update_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_has_weight_update_period(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_error_utilization_penalty(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_FloatValue* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_error_utilization_penalty(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const struct google_protobuf_FloatValue* default_val = NULL;
  const struct google_protobuf_FloatValue* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__FloatValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_has_error_utilization_penalty(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_clear_metric_names_for_computing_utilization(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_metric_names_for_computing_utilization(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_metric_names_for_computing_utilization_upb_array(const envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_metric_names_for_computing_utilization_mutable_upb_array(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_enable_oob_load_report(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_enable_oob_load_report(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_enable_oob_load_report(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_enable_oob_load_report(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_oob_reporting_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_oob_reporting_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_oob_reporting_period(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_oob_reporting_period(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_blackout_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_blackout_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_blackout_period(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_blackout_period(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_weight_expiration_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_weight_expiration_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_weight_expiration_period(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_weight_expiration_period(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_weight_update_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_weight_update_period(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_weight_update_period(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_weight_update_period(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_error_utilization_penalty(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin *msg, struct google_protobuf_FloatValue* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__FloatValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_FloatValue* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_error_utilization_penalty(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_Arena* arena) {
  struct google_protobuf_FloatValue* sub = (struct google_protobuf_FloatValue*)envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_error_utilization_penalty(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_FloatValue*)_upb_Message_New(&google__protobuf__FloatValue_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_set_error_utilization_penalty(msg, sub);
  }
  return sub;
}
UPB_INLINE upb_StringView* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_mutable_metric_names_for_computing_utilization(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_resize_metric_names_for_computing_utilization(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin_add_metric_names_for_computing_utilization(envoy_extensions_load_balancing_policies_client_side_weighted_round_robin_v3_ClientSideWeightedRoundRobin* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
