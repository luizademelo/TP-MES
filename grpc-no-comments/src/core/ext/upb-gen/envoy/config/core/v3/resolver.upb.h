
#ifndef ENVOY_CONFIG_CORE_V3_RESOLVER_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_RESOLVER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/resolver.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_DnsResolverOptions { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_DnsResolverOptions;
typedef struct envoy_config_core_v3_DnsResolutionConfig { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_DnsResolutionConfig;
struct envoy_config_core_v3_Address;

UPB_INLINE envoy_config_core_v3_DnsResolverOptions* envoy_config_core_v3_DnsResolverOptions_new(upb_Arena* arena) {
  return (envoy_config_core_v3_DnsResolverOptions*)_upb_Message_New(&envoy__config__core__v3__DnsResolverOptions_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_DnsResolverOptions* envoy_config_core_v3_DnsResolverOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_DnsResolverOptions* ret = envoy_config_core_v3_DnsResolverOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__DnsResolverOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_DnsResolverOptions* envoy_config_core_v3_DnsResolverOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_DnsResolverOptions* ret = envoy_config_core_v3_DnsResolverOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__DnsResolverOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_DnsResolverOptions_serialize(const envoy_config_core_v3_DnsResolverOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__DnsResolverOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_DnsResolverOptions_serialize_ex(const envoy_config_core_v3_DnsResolverOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__DnsResolverOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_DnsResolverOptions_clear_use_tcp_for_dns_lookups(envoy_config_core_v3_DnsResolverOptions* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_DnsResolverOptions_use_tcp_for_dns_lookups(const envoy_config_core_v3_DnsResolverOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_DnsResolverOptions_clear_no_default_search_domain(envoy_config_core_v3_DnsResolverOptions* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_DnsResolverOptions_no_default_search_domain(const envoy_config_core_v3_DnsResolverOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_DnsResolverOptions_set_use_tcp_for_dns_lookups(envoy_config_core_v3_DnsResolverOptions *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_DnsResolverOptions_set_no_default_search_domain(envoy_config_core_v3_DnsResolverOptions *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_DnsResolutionConfig* envoy_config_core_v3_DnsResolutionConfig_new(upb_Arena* arena) {
  return (envoy_config_core_v3_DnsResolutionConfig*)_upb_Message_New(&envoy__config__core__v3__DnsResolutionConfig_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_DnsResolutionConfig* envoy_config_core_v3_DnsResolutionConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_DnsResolutionConfig* ret = envoy_config_core_v3_DnsResolutionConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__DnsResolutionConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_DnsResolutionConfig* envoy_config_core_v3_DnsResolutionConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_DnsResolutionConfig* ret = envoy_config_core_v3_DnsResolutionConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__DnsResolutionConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_DnsResolutionConfig_serialize(const envoy_config_core_v3_DnsResolutionConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__DnsResolutionConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_DnsResolutionConfig_serialize_ex(const envoy_config_core_v3_DnsResolutionConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__DnsResolutionConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_DnsResolutionConfig_clear_resolvers(envoy_config_core_v3_DnsResolutionConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* const* envoy_config_core_v3_DnsResolutionConfig_resolvers(const envoy_config_core_v3_DnsResolutionConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_Address* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_DnsResolutionConfig_resolvers_upb_array(const envoy_config_core_v3_DnsResolutionConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_DnsResolutionConfig_resolvers_mutable_upb_array(envoy_config_core_v3_DnsResolutionConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_DnsResolutionConfig_clear_dns_resolver_options(envoy_config_core_v3_DnsResolutionConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_DnsResolverOptions* envoy_config_core_v3_DnsResolutionConfig_dns_resolver_options(const envoy_config_core_v3_DnsResolutionConfig* msg) {
  const envoy_config_core_v3_DnsResolverOptions* default_val = NULL;
  const envoy_config_core_v3_DnsResolverOptions* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DnsResolverOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_DnsResolutionConfig_has_dns_resolver_options(const envoy_config_core_v3_DnsResolutionConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE struct envoy_config_core_v3_Address** envoy_config_core_v3_DnsResolutionConfig_mutable_resolvers(envoy_config_core_v3_DnsResolutionConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_Address**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_Address** envoy_config_core_v3_DnsResolutionConfig_resize_resolvers(envoy_config_core_v3_DnsResolutionConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_Address**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_core_v3_DnsResolutionConfig_add_resolvers(envoy_config_core_v3_DnsResolutionConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_DnsResolutionConfig_set_dns_resolver_options(envoy_config_core_v3_DnsResolutionConfig *msg, envoy_config_core_v3_DnsResolverOptions* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DnsResolverOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DnsResolverOptions* envoy_config_core_v3_DnsResolutionConfig_mutable_dns_resolver_options(envoy_config_core_v3_DnsResolutionConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DnsResolverOptions* sub = (struct envoy_config_core_v3_DnsResolverOptions*)envoy_config_core_v3_DnsResolutionConfig_dns_resolver_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DnsResolverOptions*)_upb_Message_New(&envoy__config__core__v3__DnsResolverOptions_msg_init, arena);
    if (sub) envoy_config_core_v3_DnsResolutionConfig_set_dns_resolver_options(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
