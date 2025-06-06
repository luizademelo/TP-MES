
#ifndef ENVOY_ADMIN_V3_MUTEX_STATS_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_MUTEX_STATS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/mutex_stats.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_MutexStats { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_MutexStats;

UPB_INLINE envoy_admin_v3_MutexStats* envoy_admin_v3_MutexStats_new(upb_Arena* arena) {
  return (envoy_admin_v3_MutexStats*)_upb_Message_New(&envoy__admin__v3__MutexStats_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_MutexStats* envoy_admin_v3_MutexStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_MutexStats* ret = envoy_admin_v3_MutexStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__MutexStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_MutexStats* envoy_admin_v3_MutexStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_MutexStats* ret = envoy_admin_v3_MutexStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__MutexStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_MutexStats_serialize(const envoy_admin_v3_MutexStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__MutexStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_MutexStats_serialize_ex(const envoy_admin_v3_MutexStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__MutexStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_MutexStats_clear_num_contentions(envoy_admin_v3_MutexStats* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_MutexStats_num_contentions(const envoy_admin_v3_MutexStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_MutexStats_clear_current_wait_cycles(envoy_admin_v3_MutexStats* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_MutexStats_current_wait_cycles(const envoy_admin_v3_MutexStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_MutexStats_clear_lifetime_wait_cycles(envoy_admin_v3_MutexStats* msg) {
  const upb_MiniTableField field = {3, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_MutexStats_lifetime_wait_cycles(const envoy_admin_v3_MutexStats* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_MutexStats_set_num_contentions(envoy_admin_v3_MutexStats *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_MutexStats_set_current_wait_cycles(envoy_admin_v3_MutexStats *msg, uint64_t value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_MutexStats_set_lifetime_wait_cycles(envoy_admin_v3_MutexStats *msg, uint64_t value) {
  const upb_MiniTableField field = {3, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
