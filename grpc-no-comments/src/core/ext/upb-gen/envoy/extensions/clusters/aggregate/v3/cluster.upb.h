
#ifndef ENVOY_EXTENSIONS_CLUSTERS_AGGREGATE_V3_CLUSTER_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_CLUSTERS_AGGREGATE_V3_CLUSTER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/clusters/aggregate/v3/cluster.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_clusters_aggregate_v3_ClusterConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_clusters_aggregate_v3_ClusterConfig;

UPB_INLINE envoy_extensions_clusters_aggregate_v3_ClusterConfig* envoy_extensions_clusters_aggregate_v3_ClusterConfig_new(upb_Arena* arena) {
  return (envoy_extensions_clusters_aggregate_v3_ClusterConfig*)_upb_Message_New(&envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_clusters_aggregate_v3_ClusterConfig* envoy_extensions_clusters_aggregate_v3_ClusterConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_clusters_aggregate_v3_ClusterConfig* ret = envoy_extensions_clusters_aggregate_v3_ClusterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_clusters_aggregate_v3_ClusterConfig* envoy_extensions_clusters_aggregate_v3_ClusterConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_clusters_aggregate_v3_ClusterConfig* ret = envoy_extensions_clusters_aggregate_v3_ClusterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_clusters_aggregate_v3_ClusterConfig_serialize(const envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_clusters_aggregate_v3_ClusterConfig_serialize_ex(const envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__clusters__aggregate__v3__ClusterConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_clusters_aggregate_v3_ClusterConfig_clear_clusters(envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_clusters_aggregate_v3_ClusterConfig_clusters(const envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_clusters_aggregate_v3_ClusterConfig_clusters_upb_array(const envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_clusters_aggregate_v3_ClusterConfig_clusters_mutable_upb_array(envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE upb_StringView* envoy_extensions_clusters_aggregate_v3_ClusterConfig_mutable_clusters(envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_clusters_aggregate_v3_ClusterConfig_resize_clusters(envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_clusters_aggregate_v3_ClusterConfig_add_clusters(envoy_extensions_clusters_aggregate_v3_ClusterConfig* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
