
#ifndef ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_RING_HASH_V3_RING_HASH_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_LOAD_BALANCING_POLICIES_RING_HASH_V3_RING_HASH_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/load_balancing_policies/ring_hash/v3/ring_hash.upb_minitable.h"

#include "envoy/extensions/load_balancing_policies/common/v3/common.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash { upb_Message UPB_PRIVATE(base); } envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash;
struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig;
struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig;
struct google_protobuf_UInt32Value;
struct google_protobuf_UInt64Value;

typedef enum {
  envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_DEFAULT_HASH = 0,
  envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_XX_HASH = 1,
  envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_MURMUR_HASH_2 = 2
} envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_HashFunction;

UPB_INLINE envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_new(upb_Arena* arena) {
  return (envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__ring_0hash__v3__RingHash_msg_init, arena);
}
UPB_INLINE envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* ret = envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__ring_0hash__v3__RingHash_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* ret = envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__load_0balancing_0policies__ring_0hash__v3__RingHash_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_serialize(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__ring_0hash__v3__RingHash_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_serialize_ex(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__load_0balancing_0policies__ring_0hash__v3__RingHash_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_hash_function(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_hash_function(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_minimum_ring_size(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_minimum_ring_size(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_has_minimum_ring_size(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_maximum_ring_size(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_maximum_ring_size(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_has_maximum_ring_size(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_use_hostname_for_hashing(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_use_hostname_for_hashing(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_hash_balance_factor(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_hash_balance_factor(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_has_hash_balance_factor(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_consistent_hashing_lb_config(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_consistent_hashing_lb_config(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* default_val = NULL;
  const struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_has_consistent_hashing_lb_config(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_clear_locality_weighted_lb_config(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_locality_weighted_lb_config(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* default_val = NULL;
  const struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_has_locality_weighted_lb_config(const envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_hash_function(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_minimum_ring_size(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_mutable_minimum_ring_size(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_minimum_ring_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_minimum_ring_size(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_maximum_ring_size(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_mutable_maximum_ring_size(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_maximum_ring_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_maximum_ring_size(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_use_hostname_for_hashing(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, bool value) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_hash_balance_factor(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_mutable_hash_balance_factor(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_hash_balance_factor(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_hash_balance_factor(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_consistent_hashing_lb_config(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_mutable_consistent_hashing_lb_config(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, upb_Arena* arena) {
  struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig* sub = (struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig*)envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_consistent_hashing_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_consistent_hashing_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_locality_weighted_lb_config(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash *msg, struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_mutable_locality_weighted_lb_config(envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash* msg, upb_Arena* arena) {
  struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig* sub = (struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig*)envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_locality_weighted_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_LocalityWeightedLbConfig*)_upb_Message_New(&envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init, arena);
    if (sub) envoy_extensions_load_balancing_policies_ring_hash_v3_RingHash_set_locality_weighted_lb_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
