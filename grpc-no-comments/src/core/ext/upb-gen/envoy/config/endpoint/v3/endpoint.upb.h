
#ifndef ENVOY_CONFIG_ENDPOINT_V3_ENDPOINT_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_ENDPOINT_V3_ENDPOINT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/endpoint/v3/endpoint.upb_minitable.h"

#include "envoy/config/endpoint/v3/endpoint_components.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_endpoint_v3_ClusterLoadAssignment { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_ClusterLoadAssignment;
typedef struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_ClusterLoadAssignment_Policy;
typedef struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload { upb_Message UPB_PRIVATE(base); } envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload;
struct envoy_config_endpoint_v3_LocalityLbEndpoints;
struct envoy_type_v3_FractionalPercent;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment* envoy_config_endpoint_v3_ClusterLoadAssignment_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_ClusterLoadAssignment*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment* envoy_config_endpoint_v3_ClusterLoadAssignment_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterLoadAssignment* ret = envoy_config_endpoint_v3_ClusterLoadAssignment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment* envoy_config_endpoint_v3_ClusterLoadAssignment_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterLoadAssignment* ret = envoy_config_endpoint_v3_ClusterLoadAssignment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterLoadAssignment_serialize(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterLoadAssignment_serialize_ex(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_clear_cluster_name(envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_endpoint_v3_ClusterLoadAssignment_cluster_name(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_clear_endpoints(envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_endpoint_v3_LocalityLbEndpoints* const* envoy_config_endpoint_v3_ClusterLoadAssignment_endpoints(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_endpoint_v3_LocalityLbEndpoints* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_ClusterLoadAssignment_endpoints_upb_array(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_ClusterLoadAssignment_endpoints_mutable_upb_array(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_clear_policy(envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* envoy_config_endpoint_v3_ClusterLoadAssignment_policy(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* default_val = NULL;
  const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_has_policy(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_clear_named_endpoints(envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_size(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_get(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_StringView key, struct envoy_config_endpoint_v3_Endpoint** val) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__Endpoint_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_next(const envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_StringView* key, const struct envoy_config_endpoint_v3_Endpoint** val,
                           size_t* iter) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__Endpoint_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_upb_map(envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__Endpoint_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_mutable_upb_map(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__Endpoint_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct envoy_config_endpoint_v3_Endpoint*), a);
}

UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_set_cluster_name(envoy_config_endpoint_v3_ClusterLoadAssignment *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_endpoint_v3_LocalityLbEndpoints** envoy_config_endpoint_v3_ClusterLoadAssignment_mutable_endpoints(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_endpoint_v3_LocalityLbEndpoints**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_endpoint_v3_LocalityLbEndpoints** envoy_config_endpoint_v3_ClusterLoadAssignment_resize_endpoints(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_endpoint_v3_LocalityLbEndpoints**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_LocalityLbEndpoints* envoy_config_endpoint_v3_ClusterLoadAssignment_add_endpoints(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_LocalityLbEndpoints* sub = (struct envoy_config_endpoint_v3_LocalityLbEndpoints*)_upb_Message_New(&envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_set_policy(envoy_config_endpoint_v3_ClusterLoadAssignment *msg, envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* envoy_config_endpoint_v3_ClusterLoadAssignment_mutable_policy(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_Arena* arena) {
  struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* sub = (struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy*)envoy_config_endpoint_v3_ClusterLoadAssignment_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_ClusterLoadAssignment_set_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_clear(envoy_config_endpoint_v3_ClusterLoadAssignment* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_set(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_StringView key, struct envoy_config_endpoint_v3_Endpoint* val, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__Endpoint_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_named_endpoints_delete(envoy_config_endpoint_v3_ClusterLoadAssignment* msg, upb_StringView key) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_ClusterLoadAssignment_Policy*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* ret = envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* ret = envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_serialize(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_serialize_ex(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_clear_drop_overloads(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* const* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_drop_overloads(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_drop_overloads_upb_array(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_drop_overloads_mutable_upb_array(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_clear_overprovisioning_factor(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_overprovisioning_factor(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_has_overprovisioning_factor(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_clear_endpoint_stale_after(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_endpoint_stale_after(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_has_endpoint_stale_after(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_clear_weighted_priority_health(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_weighted_priority_health(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload** envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_mutable_drop_overloads(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload** envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_resize_drop_overloads(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_add_drop_overloads(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* sub = (struct envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_set_overprovisioning_factor(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_mutable_overprovisioning_factor(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_overprovisioning_factor(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_set_overprovisioning_factor(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_set_endpoint_stale_after(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_mutable_endpoint_stale_after(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_endpoint_stale_after(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_set_endpoint_stale_after(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_set_weighted_priority_health(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_new(upb_Arena* arena) {
  return (envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init, arena);
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* ret = envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* ret = envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_serialize(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_serialize_ex(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_clear_category(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_category(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_clear_drop_percentage(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_drop_percentage(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_has_drop_percentage(const envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_set_category(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_set_drop_percentage(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_mutable_drop_percentage(envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_drop_percentage(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload_set_drop_percentage(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
