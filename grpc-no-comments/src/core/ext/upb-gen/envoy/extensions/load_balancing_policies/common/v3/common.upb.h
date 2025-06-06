
#ifndef ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_COMMON_V3_COMMON_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_COMMON_V3_COMMON_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/load_balancing_policies/common/v3/common.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig;
typedef struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig;
typedef struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig;
typedef struct envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig;
typedef struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig;
struct envoy_config_core_v3_RuntimeDouble;
struct envoy_type_v3_Percent;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;
struct google_protobuf_UInt64Value;

UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_serialize(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_serialize_ex(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_zone_aware_lb_config = 1,
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_locality_weighted_lb_config = 2,
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_NOT_SET = 0
} envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_oneofcases;
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_oneofcases envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_case(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_config_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_clear_locality_config_specifier(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init, &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_clear_zone_aware_lb_config(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_zone_aware_lb_config(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* default_val = NULL;
  const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_has_zone_aware_lb_config(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_clear_locality_weighted_lb_config(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_weighted_lb_config(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* default_val = NULL;
  const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_has_locality_weighted_lb_config(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_set_zone_aware_lb_config(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig *msg, envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_mutable_zone_aware_lb_config(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg, upb_Arena* arena) {
  struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* sub = (struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig*)envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_zone_aware_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_set_zone_aware_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_set_locality_weighted_lb_config(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig *msg, envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_mutable_locality_weighted_lb_config(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig* msg, upb_Arena* arena) {
  struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* sub = (struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig*)envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_locality_weighted_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_set_locality_weighted_lb_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_serialize(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_serialize_ex(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_clear_routing_enabled(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_routing_enabled(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_has_routing_enabled(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_clear_min_cluster_size(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_min_cluster_size(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_has_min_cluster_size(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_clear_fail_traffic_on_panic(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_fail_traffic_on_panic(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_set_routing_enabled(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_mutable_routing_enabled(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_routing_enabled(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_set_routing_enabled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_set_min_cluster_size(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_mutable_min_cluster_size(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_min_cluster_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_set_min_cluster_size(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig_set_fail_traffic_on_panic(envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_serialize(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig_serialize_ex(const envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* ret = envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* ret = envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_serialize(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_serialize_ex(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_clear_slow_start_window(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_slow_start_window(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_has_slow_start_window(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_clear_aggression(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeDouble* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_aggression(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const struct envoy_config_core_v3_RuntimeDouble* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeDouble* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeDouble_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_has_aggression(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_clear_min_weight_percent(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_min_weight_percent(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_has_min_weight_percent(const envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_set_slow_start_window(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_mutable_slow_start_window(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_slow_start_window(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_set_slow_start_window(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_set_aggression(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig *msg, struct envoy_config_core_v3_RuntimeDouble* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeDouble_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeDouble* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_mutable_aggression(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeDouble* sub = (struct envoy_config_core_v3_RuntimeDouble*)envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_aggression(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeDouble*)_upb_Message_New(&envoy__config__core__v3__RuntimeDouble_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_set_aggression(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_set_min_weight_percent(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_mutable_min_weight_percent(envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_min_weight_percent(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig_set_min_weight_percent(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* ret = envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_serialize(const envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_serialize_ex(const envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_clear_use_hostname_for_hashing(envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_use_hostname_for_hashing(const envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_clear_hash_balance_factor(envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_hash_balance_factor(const envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_has_hash_balance_factor(const envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_set_use_hostname_for_hashing(envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_set_hash_balance_factor(envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_mutable_hash_balance_factor(envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_hash_balance_factor(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig_set_hash_balance_factor(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
