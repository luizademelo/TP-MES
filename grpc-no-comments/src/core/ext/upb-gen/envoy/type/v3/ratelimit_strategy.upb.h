
#ifndef ENVOY_TYPE_V3_RATELIMIT_STRATEGY_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_V3_RATELIMIT_STRATEGY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/v3/ratelimit_strategy.upb_minitable.h"

#include "envoy/type/v3/ratelimit_unit.upb_minitable.h"
#include "envoy/type/v3/token_bucket.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_v3_RateLimitStrategy { upb_Message UPB_PRIVATE(base); } envoy_type_v3_RateLimitStrategy;
typedef struct envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit { upb_Message UPB_PRIVATE(base); } envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit;
struct envoy_type_v3_TokenBucket;

typedef enum {
  envoy_type_v3_RateLimitStrategy_ALLOW_ALL = 0,
  envoy_type_v3_RateLimitStrategy_DENY_ALL = 1
} envoy_type_v3_RateLimitStrategy_BlanketRule;

UPB_INLINE envoy_type_v3_RateLimitStrategy* envoy_type_v3_RateLimitStrategy_new(upb_Arena* arena) {
  return (envoy_type_v3_RateLimitStrategy*)_upb_Message_New(&envoy__type__v3__RateLimitStrategy_msg_init, arena);
}
UPB_INLINE envoy_type_v3_RateLimitStrategy* envoy_type_v3_RateLimitStrategy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_v3_RateLimitStrategy* ret = envoy_type_v3_RateLimitStrategy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__RateLimitStrategy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_v3_RateLimitStrategy* envoy_type_v3_RateLimitStrategy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_v3_RateLimitStrategy* ret = envoy_type_v3_RateLimitStrategy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__RateLimitStrategy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_v3_RateLimitStrategy_serialize(const envoy_type_v3_RateLimitStrategy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__RateLimitStrategy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_v3_RateLimitStrategy_serialize_ex(const envoy_type_v3_RateLimitStrategy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__RateLimitStrategy_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_v3_RateLimitStrategy_strategy_blanket_rule = 1,
  envoy_type_v3_RateLimitStrategy_strategy_requests_per_time_unit = 2,
  envoy_type_v3_RateLimitStrategy_strategy_token_bucket = 3,
  envoy_type_v3_RateLimitStrategy_strategy_NOT_SET = 0
} envoy_type_v3_RateLimitStrategy_strategy_oneofcases;
UPB_INLINE envoy_type_v3_RateLimitStrategy_strategy_oneofcases envoy_type_v3_RateLimitStrategy_strategy_case(const envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return (envoy_type_v3_RateLimitStrategy_strategy_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_clear_strategy(envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__v3__RateLimitStrategy_msg_init, &field);
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_clear_blanket_rule(envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_type_v3_RateLimitStrategy_blanket_rule(const envoy_type_v3_RateLimitStrategy* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_v3_RateLimitStrategy_has_blanket_rule(const envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_clear_requests_per_time_unit(envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* envoy_type_v3_RateLimitStrategy_requests_per_time_unit(const envoy_type_v3_RateLimitStrategy* msg) {
  const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* default_val = NULL;
  const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_v3_RateLimitStrategy_has_requests_per_time_unit(const envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_clear_token_bucket(envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_TokenBucket* envoy_type_v3_RateLimitStrategy_token_bucket(const envoy_type_v3_RateLimitStrategy* msg) {
  const struct envoy_type_v3_TokenBucket* default_val = NULL;
  const struct envoy_type_v3_TokenBucket* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__TokenBucket_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_v3_RateLimitStrategy_has_token_bucket(const envoy_type_v3_RateLimitStrategy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_v3_RateLimitStrategy_set_blanket_rule(envoy_type_v3_RateLimitStrategy *msg, int32_t value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_set_requests_per_time_unit(envoy_type_v3_RateLimitStrategy *msg, envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* envoy_type_v3_RateLimitStrategy_mutable_requests_per_time_unit(envoy_type_v3_RateLimitStrategy* msg, upb_Arena* arena) {
  struct envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* sub = (struct envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit*)envoy_type_v3_RateLimitStrategy_requests_per_time_unit(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit*)_upb_Message_New(&envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init, arena);
    if (sub) envoy_type_v3_RateLimitStrategy_set_requests_per_time_unit(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_set_token_bucket(envoy_type_v3_RateLimitStrategy *msg, struct envoy_type_v3_TokenBucket* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__TokenBucket_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_TokenBucket* envoy_type_v3_RateLimitStrategy_mutable_token_bucket(envoy_type_v3_RateLimitStrategy* msg, upb_Arena* arena) {
  struct envoy_type_v3_TokenBucket* sub = (struct envoy_type_v3_TokenBucket*)envoy_type_v3_RateLimitStrategy_token_bucket(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_TokenBucket*)_upb_Message_New(&envoy__type__v3__TokenBucket_msg_init, arena);
    if (sub) envoy_type_v3_RateLimitStrategy_set_token_bucket(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_new(upb_Arena* arena) {
  return (envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit*)_upb_Message_New(&envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init, arena);
}
UPB_INLINE envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* ret = envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* ret = envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_serialize(const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_serialize_ex(const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_clear_requests_per_time_unit(envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_requests_per_time_unit(const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_clear_time_unit(envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_time_unit(const envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_set_requests_per_time_unit(envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit_set_time_unit(envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
