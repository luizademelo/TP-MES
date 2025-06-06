
#ifndef ENVOY_TYPE_V3_HASH_POLICY_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_V3_HASH_POLICY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/v3/hash_policy.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_v3_HashPolicy { upb_Message UPB_PRIVATE(base); } envoy_type_v3_HashPolicy;
typedef struct envoy_type_v3_HashPolicy_SourceIp { upb_Message UPB_PRIVATE(base); } envoy_type_v3_HashPolicy_SourceIp;
typedef struct envoy_type_v3_HashPolicy_FilterState { upb_Message UPB_PRIVATE(base); } envoy_type_v3_HashPolicy_FilterState;

UPB_INLINE envoy_type_v3_HashPolicy* envoy_type_v3_HashPolicy_new(upb_Arena* arena) {
  return (envoy_type_v3_HashPolicy*)_upb_Message_New(&envoy__type__v3__HashPolicy_msg_init, arena);
}
UPB_INLINE envoy_type_v3_HashPolicy* envoy_type_v3_HashPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_v3_HashPolicy* ret = envoy_type_v3_HashPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HashPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_v3_HashPolicy* envoy_type_v3_HashPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_v3_HashPolicy* ret = envoy_type_v3_HashPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HashPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_v3_HashPolicy_serialize(const envoy_type_v3_HashPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_v3_HashPolicy_serialize_ex(const envoy_type_v3_HashPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_v3_HashPolicy_policy_specifier_source_ip = 1,
  envoy_type_v3_HashPolicy_policy_specifier_filter_state = 2,
  envoy_type_v3_HashPolicy_policy_specifier_NOT_SET = 0
} envoy_type_v3_HashPolicy_policy_specifier_oneofcases;
UPB_INLINE envoy_type_v3_HashPolicy_policy_specifier_oneofcases envoy_type_v3_HashPolicy_policy_specifier_case(const envoy_type_v3_HashPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_v3_HashPolicy_policy_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_v3_HashPolicy_clear_policy_specifier(envoy_type_v3_HashPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy_msg_init, &field);
}
UPB_INLINE void envoy_type_v3_HashPolicy_clear_source_ip(envoy_type_v3_HashPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_v3_HashPolicy_SourceIp* envoy_type_v3_HashPolicy_source_ip(const envoy_type_v3_HashPolicy* msg) {
  const envoy_type_v3_HashPolicy_SourceIp* default_val = NULL;
  const envoy_type_v3_HashPolicy_SourceIp* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__HashPolicy__SourceIp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_v3_HashPolicy_has_source_ip(const envoy_type_v3_HashPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_v3_HashPolicy_clear_filter_state(envoy_type_v3_HashPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_v3_HashPolicy_FilterState* envoy_type_v3_HashPolicy_filter_state(const envoy_type_v3_HashPolicy* msg) {
  const envoy_type_v3_HashPolicy_FilterState* default_val = NULL;
  const envoy_type_v3_HashPolicy_FilterState* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__HashPolicy__FilterState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_v3_HashPolicy_has_filter_state(const envoy_type_v3_HashPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_v3_HashPolicy_set_source_ip(envoy_type_v3_HashPolicy *msg, envoy_type_v3_HashPolicy_SourceIp* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__HashPolicy__SourceIp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_HashPolicy_SourceIp* envoy_type_v3_HashPolicy_mutable_source_ip(envoy_type_v3_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_type_v3_HashPolicy_SourceIp* sub = (struct envoy_type_v3_HashPolicy_SourceIp*)envoy_type_v3_HashPolicy_source_ip(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_HashPolicy_SourceIp*)_upb_Message_New(&envoy__type__v3__HashPolicy__SourceIp_msg_init, arena);
    if (sub) envoy_type_v3_HashPolicy_set_source_ip(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_v3_HashPolicy_set_filter_state(envoy_type_v3_HashPolicy *msg, envoy_type_v3_HashPolicy_FilterState* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__HashPolicy__FilterState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_HashPolicy_FilterState* envoy_type_v3_HashPolicy_mutable_filter_state(envoy_type_v3_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_type_v3_HashPolicy_FilterState* sub = (struct envoy_type_v3_HashPolicy_FilterState*)envoy_type_v3_HashPolicy_filter_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_HashPolicy_FilterState*)_upb_Message_New(&envoy__type__v3__HashPolicy__FilterState_msg_init, arena);
    if (sub) envoy_type_v3_HashPolicy_set_filter_state(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_v3_HashPolicy_SourceIp* envoy_type_v3_HashPolicy_SourceIp_new(upb_Arena* arena) {
  return (envoy_type_v3_HashPolicy_SourceIp*)_upb_Message_New(&envoy__type__v3__HashPolicy__SourceIp_msg_init, arena);
}
UPB_INLINE envoy_type_v3_HashPolicy_SourceIp* envoy_type_v3_HashPolicy_SourceIp_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_v3_HashPolicy_SourceIp* ret = envoy_type_v3_HashPolicy_SourceIp_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HashPolicy__SourceIp_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_v3_HashPolicy_SourceIp* envoy_type_v3_HashPolicy_SourceIp_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_v3_HashPolicy_SourceIp* ret = envoy_type_v3_HashPolicy_SourceIp_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HashPolicy__SourceIp_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_v3_HashPolicy_SourceIp_serialize(const envoy_type_v3_HashPolicy_SourceIp* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy__SourceIp_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_v3_HashPolicy_SourceIp_serialize_ex(const envoy_type_v3_HashPolicy_SourceIp* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy__SourceIp_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_type_v3_HashPolicy_FilterState* envoy_type_v3_HashPolicy_FilterState_new(upb_Arena* arena) {
  return (envoy_type_v3_HashPolicy_FilterState*)_upb_Message_New(&envoy__type__v3__HashPolicy__FilterState_msg_init, arena);
}
UPB_INLINE envoy_type_v3_HashPolicy_FilterState* envoy_type_v3_HashPolicy_FilterState_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_v3_HashPolicy_FilterState* ret = envoy_type_v3_HashPolicy_FilterState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HashPolicy__FilterState_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_v3_HashPolicy_FilterState* envoy_type_v3_HashPolicy_FilterState_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_v3_HashPolicy_FilterState* ret = envoy_type_v3_HashPolicy_FilterState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HashPolicy__FilterState_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_v3_HashPolicy_FilterState_serialize(const envoy_type_v3_HashPolicy_FilterState* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy__FilterState_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_v3_HashPolicy_FilterState_serialize_ex(const envoy_type_v3_HashPolicy_FilterState* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HashPolicy__FilterState_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_v3_HashPolicy_FilterState_clear_key(envoy_type_v3_HashPolicy_FilterState* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_v3_HashPolicy_FilterState_key(const envoy_type_v3_HashPolicy_FilterState* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_v3_HashPolicy_FilterState_set_key(envoy_type_v3_HashPolicy_FilterState *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
