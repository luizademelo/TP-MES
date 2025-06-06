
#ifndef ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_WRR_LOCALITY_V3_WRR_LOCALITY_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_WRR_LOCALITY_V3_WRR_LOCALITY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/load_balancing_policies/wrr_locality/v3/wrr_locality.upb_minitable.h"

#include "envoy/config/cluster/v3/cluster.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality;
struct envoy_config_cluster_v3_LoadBalancingPolicy;

UPB_INLINE envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* ret = envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* ret = envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_serialize(const envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_serialize_ex(const envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__wrr_0locality__v3__WrrLocality_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_clear_endpoint_picking_policy(envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_cluster_v3_LoadBalancingPolicy* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_endpoint_picking_policy(const envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* msg) {
  const struct envoy_config_cluster_v3_LoadBalancingPolicy* default_val = NULL;
  const struct envoy_config_cluster_v3_LoadBalancingPolicy* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_has_endpoint_picking_policy(const envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_set_endpoint_picking_policy(envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality *msg, struct envoy_config_cluster_v3_LoadBalancingPolicy* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_LoadBalancingPolicy* envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_mutable_endpoint_picking_policy(envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_LoadBalancingPolicy* sub = (struct envoy_config_cluster_v3_LoadBalancingPolicy*)envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_endpoint_picking_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_LoadBalancingPolicy*)_upb_Message_New(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_wrr_locality_v3_WrrLocality_set_endpoint_picking_policy(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
