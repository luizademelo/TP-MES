
#ifndef ENVOY_CONFIG_CORE_V3_PROXY_PROTOCOL_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_PROXY_PROTOCOL_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/proxy_protocol.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_ProxyProtocolPassThroughTLVs { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_ProxyProtocolPassThroughTLVs;
typedef struct envoy_config_core_v3_ProxyProtocolConfig { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_ProxyProtocolConfig;

typedef enum {
  envoy_config_core_v3_ProxyProtocolConfig_V1 = 0,
  envoy_config_core_v3_ProxyProtocolConfig_V2 = 1
} envoy_config_core_v3_ProxyProtocolConfig_Version;

typedef enum {
  envoy_config_core_v3_ProxyProtocolPassThroughTLVs_INCLUDE_ALL = 0,
  envoy_config_core_v3_ProxyProtocolPassThroughTLVs_INCLUDE = 1
} envoy_config_core_v3_ProxyProtocolPassThroughTLVs_PassTLVsMatchType;

UPB_INLINE envoy_config_core_v3_ProxyProtocolPassThroughTLVs* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_new(upb_Arena* arena) {
  return (envoy_config_core_v3_ProxyProtocolPassThroughTLVs*)_upb_Message_New(&envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_ProxyProtocolPassThroughTLVs* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_ProxyProtocolPassThroughTLVs* ret = envoy_config_core_v3_ProxyProtocolPassThroughTLVs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_ProxyProtocolPassThroughTLVs* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_ProxyProtocolPassThroughTLVs* ret = envoy_config_core_v3_ProxyProtocolPassThroughTLVs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_serialize(const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_serialize_ex(const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_ProxyProtocolPassThroughTLVs_clear_match_type(envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_ProxyProtocolPassThroughTLVs_match_type(const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_ProxyProtocolPassThroughTLVs_clear_tlv_type(envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_tlv_type(const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_ProxyProtocolPassThroughTLVs_tlv_type_upb_array(const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_ProxyProtocolPassThroughTLVs_tlv_type_mutable_upb_array(envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_core_v3_ProxyProtocolPassThroughTLVs_set_match_type(envoy_config_core_v3_ProxyProtocolPassThroughTLVs *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE uint32_t* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_mutable_tlv_type(envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* envoy_config_core_v3_ProxyProtocolPassThroughTLVs_resize_tlv_type(envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_core_v3_ProxyProtocolPassThroughTLVs_add_tlv_type(envoy_config_core_v3_ProxyProtocolPassThroughTLVs* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_config_core_v3_ProxyProtocolConfig* envoy_config_core_v3_ProxyProtocolConfig_new(upb_Arena* arena) {
  return (envoy_config_core_v3_ProxyProtocolConfig*)_upb_Message_New(&envoy__config__core__v3__ProxyProtocolConfig_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_ProxyProtocolConfig* envoy_config_core_v3_ProxyProtocolConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_ProxyProtocolConfig* ret = envoy_config_core_v3_ProxyProtocolConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__ProxyProtocolConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_ProxyProtocolConfig* envoy_config_core_v3_ProxyProtocolConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_ProxyProtocolConfig* ret = envoy_config_core_v3_ProxyProtocolConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__ProxyProtocolConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_ProxyProtocolConfig_serialize(const envoy_config_core_v3_ProxyProtocolConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__ProxyProtocolConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_ProxyProtocolConfig_serialize_ex(const envoy_config_core_v3_ProxyProtocolConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__ProxyProtocolConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_ProxyProtocolConfig_clear_version(envoy_config_core_v3_ProxyProtocolConfig* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_ProxyProtocolConfig_version(const envoy_config_core_v3_ProxyProtocolConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_ProxyProtocolConfig_clear_pass_through_tlvs(envoy_config_core_v3_ProxyProtocolConfig* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* envoy_config_core_v3_ProxyProtocolConfig_pass_through_tlvs(const envoy_config_core_v3_ProxyProtocolConfig* msg) {
  const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* default_val = NULL;
  const envoy_config_core_v3_ProxyProtocolPassThroughTLVs* ret;
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_ProxyProtocolConfig_has_pass_through_tlvs(const envoy_config_core_v3_ProxyProtocolConfig* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_ProxyProtocolConfig_set_version(envoy_config_core_v3_ProxyProtocolConfig *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_ProxyProtocolConfig_set_pass_through_tlvs(envoy_config_core_v3_ProxyProtocolConfig *msg, envoy_config_core_v3_ProxyProtocolPassThroughTLVs* value) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ProxyProtocolPassThroughTLVs* envoy_config_core_v3_ProxyProtocolConfig_mutable_pass_through_tlvs(envoy_config_core_v3_ProxyProtocolConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ProxyProtocolPassThroughTLVs* sub = (struct envoy_config_core_v3_ProxyProtocolPassThroughTLVs*)envoy_config_core_v3_ProxyProtocolConfig_pass_through_tlvs(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ProxyProtocolPassThroughTLVs*)_upb_Message_New(&envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init, arena);
    if (sub) envoy_config_core_v3_ProxyProtocolConfig_set_pass_through_tlvs(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
