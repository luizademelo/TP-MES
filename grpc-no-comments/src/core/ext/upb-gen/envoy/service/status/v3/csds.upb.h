
#ifndef ENVOY_SERVICE_STATUS_V3_CSDS_PROTO_UPB_H__UPB_H_
#define ENVOY_SERVICE_STATUS_V3_CSDS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/service/status/v3/csds.upb_minitable.h"

#include "envoy/admin/v3/config_dump_shared.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/type/matcher/v3/node.upb_minitable.h"
#include "google/api/annotations.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_service_status_v3_ClientStatusRequest { upb_Message UPB_PRIVATE(base); } envoy_service_status_v3_ClientStatusRequest;
typedef struct envoy_service_status_v3_PerXdsConfig { upb_Message UPB_PRIVATE(base); } envoy_service_status_v3_PerXdsConfig;
typedef struct envoy_service_status_v3_ClientConfig { upb_Message UPB_PRIVATE(base); } envoy_service_status_v3_ClientConfig;
typedef struct envoy_service_status_v3_ClientConfig_GenericXdsConfig { upb_Message UPB_PRIVATE(base); } envoy_service_status_v3_ClientConfig_GenericXdsConfig;
typedef struct envoy_service_status_v3_ClientStatusResponse { upb_Message UPB_PRIVATE(base); } envoy_service_status_v3_ClientStatusResponse;
struct envoy_admin_v3_ClustersConfigDump;
struct envoy_admin_v3_EndpointsConfigDump;
struct envoy_admin_v3_ListenersConfigDump;
struct envoy_admin_v3_RoutesConfigDump;
struct envoy_admin_v3_ScopedRoutesConfigDump;
struct envoy_admin_v3_UpdateFailureState;
struct envoy_config_core_v3_Node;
struct envoy_type_matcher_v3_NodeMatcher;
struct google_protobuf_Any;
struct google_protobuf_Timestamp;

typedef enum {
  envoy_service_status_v3_CLIENT_UNKNOWN = 0,
  envoy_service_status_v3_CLIENT_REQUESTED = 1,
  envoy_service_status_v3_CLIENT_ACKED = 2,
  envoy_service_status_v3_CLIENT_NACKED = 3,
  envoy_service_status_v3_CLIENT_RECEIVED_ERROR = 4
} envoy_service_status_v3_ClientConfigStatus;

typedef enum {
  envoy_service_status_v3_UNKNOWN = 0,
  envoy_service_status_v3_SYNCED = 1,
  envoy_service_status_v3_NOT_SENT = 2,
  envoy_service_status_v3_STALE = 3,
  envoy_service_status_v3_ERROR = 4
} envoy_service_status_v3_ConfigStatus;

UPB_INLINE envoy_service_status_v3_ClientStatusRequest* envoy_service_status_v3_ClientStatusRequest_new(upb_Arena* arena) {
  return (envoy_service_status_v3_ClientStatusRequest*)_upb_Message_New(&envoy__service__status__v3__ClientStatusRequest_msg_init, arena);
}
UPB_INLINE envoy_service_status_v3_ClientStatusRequest* envoy_service_status_v3_ClientStatusRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_service_status_v3_ClientStatusRequest* ret = envoy_service_status_v3_ClientStatusRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientStatusRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_service_status_v3_ClientStatusRequest* envoy_service_status_v3_ClientStatusRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_service_status_v3_ClientStatusRequest* ret = envoy_service_status_v3_ClientStatusRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientStatusRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_service_status_v3_ClientStatusRequest_serialize(const envoy_service_status_v3_ClientStatusRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientStatusRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_service_status_v3_ClientStatusRequest_serialize_ex(const envoy_service_status_v3_ClientStatusRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientStatusRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_service_status_v3_ClientStatusRequest_clear_node_matchers(envoy_service_status_v3_ClientStatusRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_NodeMatcher* const* envoy_service_status_v3_ClientStatusRequest_node_matchers(const envoy_service_status_v3_ClientStatusRequest* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__NodeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_matcher_v3_NodeMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_service_status_v3_ClientStatusRequest_node_matchers_upb_array(const envoy_service_status_v3_ClientStatusRequest* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__NodeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_service_status_v3_ClientStatusRequest_node_matchers_mutable_upb_array(envoy_service_status_v3_ClientStatusRequest* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__NodeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_service_status_v3_ClientStatusRequest_clear_node(envoy_service_status_v3_ClientStatusRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Node* envoy_service_status_v3_ClientStatusRequest_node(const envoy_service_status_v3_ClientStatusRequest* msg) {
  const struct envoy_config_core_v3_Node* default_val = NULL;
  const struct envoy_config_core_v3_Node* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_ClientStatusRequest_has_node(const envoy_service_status_v3_ClientStatusRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_ClientStatusRequest_clear_exclude_resource_contents(envoy_service_status_v3_ClientStatusRequest* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_service_status_v3_ClientStatusRequest_exclude_resource_contents(const envoy_service_status_v3_ClientStatusRequest* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE struct envoy_type_matcher_v3_NodeMatcher** envoy_service_status_v3_ClientStatusRequest_mutable_node_matchers(envoy_service_status_v3_ClientStatusRequest* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__NodeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_matcher_v3_NodeMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_matcher_v3_NodeMatcher** envoy_service_status_v3_ClientStatusRequest_resize_node_matchers(envoy_service_status_v3_ClientStatusRequest* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_matcher_v3_NodeMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_NodeMatcher* envoy_service_status_v3_ClientStatusRequest_add_node_matchers(envoy_service_status_v3_ClientStatusRequest* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__NodeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_matcher_v3_NodeMatcher* sub = (struct envoy_type_matcher_v3_NodeMatcher*)_upb_Message_New(&envoy__type__matcher__v3__NodeMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_service_status_v3_ClientStatusRequest_set_node(envoy_service_status_v3_ClientStatusRequest *msg, struct envoy_config_core_v3_Node* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Node* envoy_service_status_v3_ClientStatusRequest_mutable_node(envoy_service_status_v3_ClientStatusRequest* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Node* sub = (struct envoy_config_core_v3_Node*)envoy_service_status_v3_ClientStatusRequest_node(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Node*)_upb_Message_New(&envoy__config__core__v3__Node_msg_init, arena);
    if (sub) envoy_service_status_v3_ClientStatusRequest_set_node(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_ClientStatusRequest_set_exclude_resource_contents(envoy_service_status_v3_ClientStatusRequest *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_service_status_v3_PerXdsConfig* envoy_service_status_v3_PerXdsConfig_new(upb_Arena* arena) {
  return (envoy_service_status_v3_PerXdsConfig*)_upb_Message_New(&envoy__service__status__v3__PerXdsConfig_msg_init, arena);
}
UPB_INLINE envoy_service_status_v3_PerXdsConfig* envoy_service_status_v3_PerXdsConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_service_status_v3_PerXdsConfig* ret = envoy_service_status_v3_PerXdsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__PerXdsConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_service_status_v3_PerXdsConfig* envoy_service_status_v3_PerXdsConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_service_status_v3_PerXdsConfig* ret = envoy_service_status_v3_PerXdsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__PerXdsConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_service_status_v3_PerXdsConfig_serialize(const envoy_service_status_v3_PerXdsConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__PerXdsConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_service_status_v3_PerXdsConfig_serialize_ex(const envoy_service_status_v3_PerXdsConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__PerXdsConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_service_status_v3_PerXdsConfig_per_xds_config_listener_config = 2,
  envoy_service_status_v3_PerXdsConfig_per_xds_config_cluster_config = 3,
  envoy_service_status_v3_PerXdsConfig_per_xds_config_route_config = 4,
  envoy_service_status_v3_PerXdsConfig_per_xds_config_scoped_route_config = 5,
  envoy_service_status_v3_PerXdsConfig_per_xds_config_endpoint_config = 6,
  envoy_service_status_v3_PerXdsConfig_per_xds_config_NOT_SET = 0
} envoy_service_status_v3_PerXdsConfig_per_xds_config_oneofcases;
UPB_INLINE envoy_service_status_v3_PerXdsConfig_per_xds_config_oneofcases envoy_service_status_v3_PerXdsConfig_per_xds_config_case(const envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_service_status_v3_PerXdsConfig_per_xds_config_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_per_xds_config(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__service__status__v3__PerXdsConfig_msg_init, &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_status(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_service_status_v3_PerXdsConfig_status(const envoy_service_status_v3_PerXdsConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_listener_config(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_ListenersConfigDump* envoy_service_status_v3_PerXdsConfig_listener_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const struct envoy_admin_v3_ListenersConfigDump* default_val = NULL;
  const struct envoy_admin_v3_ListenersConfigDump* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_PerXdsConfig_has_listener_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_cluster_config(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), -17, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_ClustersConfigDump* envoy_service_status_v3_PerXdsConfig_cluster_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const struct envoy_admin_v3_ClustersConfigDump* default_val = NULL;
  const struct envoy_admin_v3_ClustersConfigDump* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), -17, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_PerXdsConfig_has_cluster_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), -17, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_route_config(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), -17, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_RoutesConfigDump* envoy_service_status_v3_PerXdsConfig_route_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const struct envoy_admin_v3_RoutesConfigDump* default_val = NULL;
  const struct envoy_admin_v3_RoutesConfigDump* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), -17, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_PerXdsConfig_has_route_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), -17, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_scoped_route_config(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), -17, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_ScopedRoutesConfigDump* envoy_service_status_v3_PerXdsConfig_scoped_route_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const struct envoy_admin_v3_ScopedRoutesConfigDump* default_val = NULL;
  const struct envoy_admin_v3_ScopedRoutesConfigDump* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), -17, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_PerXdsConfig_has_scoped_route_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), -17, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_endpoint_config(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), -17, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_EndpointsConfigDump* envoy_service_status_v3_PerXdsConfig_endpoint_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const struct envoy_admin_v3_EndpointsConfigDump* default_val = NULL;
  const struct envoy_admin_v3_EndpointsConfigDump* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), -17, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_PerXdsConfig_has_endpoint_config(const envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), -17, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_clear_client_status(envoy_service_status_v3_PerXdsConfig* msg) {
  const upb_MiniTableField field = {7, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_service_status_v3_PerXdsConfig_client_status(const envoy_service_status_v3_PerXdsConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {7, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_status(envoy_service_status_v3_PerXdsConfig *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_listener_config(envoy_service_status_v3_PerXdsConfig *msg, struct envoy_admin_v3_ListenersConfigDump* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_ListenersConfigDump* envoy_service_status_v3_PerXdsConfig_mutable_listener_config(envoy_service_status_v3_PerXdsConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_ListenersConfigDump* sub = (struct envoy_admin_v3_ListenersConfigDump*)envoy_service_status_v3_PerXdsConfig_listener_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_ListenersConfigDump*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump_msg_init, arena);
    if (sub) envoy_service_status_v3_PerXdsConfig_set_listener_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_cluster_config(envoy_service_status_v3_PerXdsConfig *msg, struct envoy_admin_v3_ClustersConfigDump* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), -17, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_ClustersConfigDump* envoy_service_status_v3_PerXdsConfig_mutable_cluster_config(envoy_service_status_v3_PerXdsConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_ClustersConfigDump* sub = (struct envoy_admin_v3_ClustersConfigDump*)envoy_service_status_v3_PerXdsConfig_cluster_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_ClustersConfigDump*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump_msg_init, arena);
    if (sub) envoy_service_status_v3_PerXdsConfig_set_cluster_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_route_config(envoy_service_status_v3_PerXdsConfig *msg, struct envoy_admin_v3_RoutesConfigDump* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), -17, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_RoutesConfigDump* envoy_service_status_v3_PerXdsConfig_mutable_route_config(envoy_service_status_v3_PerXdsConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_RoutesConfigDump* sub = (struct envoy_admin_v3_RoutesConfigDump*)envoy_service_status_v3_PerXdsConfig_route_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_RoutesConfigDump*)_upb_Message_New(&envoy__admin__v3__RoutesConfigDump_msg_init, arena);
    if (sub) envoy_service_status_v3_PerXdsConfig_set_route_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_scoped_route_config(envoy_service_status_v3_PerXdsConfig *msg, struct envoy_admin_v3_ScopedRoutesConfigDump* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), -17, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_ScopedRoutesConfigDump* envoy_service_status_v3_PerXdsConfig_mutable_scoped_route_config(envoy_service_status_v3_PerXdsConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_ScopedRoutesConfigDump* sub = (struct envoy_admin_v3_ScopedRoutesConfigDump*)envoy_service_status_v3_PerXdsConfig_scoped_route_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_ScopedRoutesConfigDump*)_upb_Message_New(&envoy__admin__v3__ScopedRoutesConfigDump_msg_init, arena);
    if (sub) envoy_service_status_v3_PerXdsConfig_set_scoped_route_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_endpoint_config(envoy_service_status_v3_PerXdsConfig *msg, struct envoy_admin_v3_EndpointsConfigDump* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 24), -17, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_EndpointsConfigDump* envoy_service_status_v3_PerXdsConfig_mutable_endpoint_config(envoy_service_status_v3_PerXdsConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_EndpointsConfigDump* sub = (struct envoy_admin_v3_EndpointsConfigDump*)envoy_service_status_v3_PerXdsConfig_endpoint_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_EndpointsConfigDump*)_upb_Message_New(&envoy__admin__v3__EndpointsConfigDump_msg_init, arena);
    if (sub) envoy_service_status_v3_PerXdsConfig_set_endpoint_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_PerXdsConfig_set_client_status(envoy_service_status_v3_PerXdsConfig *msg, int32_t value) {
  const upb_MiniTableField field = {7, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_service_status_v3_ClientConfig* envoy_service_status_v3_ClientConfig_new(upb_Arena* arena) {
  return (envoy_service_status_v3_ClientConfig*)_upb_Message_New(&envoy__service__status__v3__ClientConfig_msg_init, arena);
}
UPB_INLINE envoy_service_status_v3_ClientConfig* envoy_service_status_v3_ClientConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_service_status_v3_ClientConfig* ret = envoy_service_status_v3_ClientConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_service_status_v3_ClientConfig* envoy_service_status_v3_ClientConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_service_status_v3_ClientConfig* ret = envoy_service_status_v3_ClientConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_service_status_v3_ClientConfig_serialize(const envoy_service_status_v3_ClientConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_service_status_v3_ClientConfig_serialize_ex(const envoy_service_status_v3_ClientConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_clear_node(envoy_service_status_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Node* envoy_service_status_v3_ClientConfig_node(const envoy_service_status_v3_ClientConfig* msg) {
  const struct envoy_config_core_v3_Node* default_val = NULL;
  const struct envoy_config_core_v3_Node* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_ClientConfig_has_node(const envoy_service_status_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_clear_xds_config(envoy_service_status_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_service_status_v3_PerXdsConfig* const* envoy_service_status_v3_ClientConfig_xds_config(const envoy_service_status_v3_ClientConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__PerXdsConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_service_status_v3_PerXdsConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_service_status_v3_ClientConfig_xds_config_upb_array(const envoy_service_status_v3_ClientConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__PerXdsConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_service_status_v3_ClientConfig_xds_config_mutable_upb_array(envoy_service_status_v3_ClientConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__PerXdsConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_clear_generic_xds_configs(envoy_service_status_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_service_status_v3_ClientConfig_GenericXdsConfig* const* envoy_service_status_v3_ClientConfig_generic_xds_configs(const envoy_service_status_v3_ClientConfig* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_service_status_v3_ClientConfig_GenericXdsConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_service_status_v3_ClientConfig_generic_xds_configs_upb_array(const envoy_service_status_v3_ClientConfig* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_service_status_v3_ClientConfig_generic_xds_configs_mutable_upb_array(envoy_service_status_v3_ClientConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_clear_client_scope(envoy_service_status_v3_ClientConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_service_status_v3_ClientConfig_client_scope(const envoy_service_status_v3_ClientConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_service_status_v3_ClientConfig_set_node(envoy_service_status_v3_ClientConfig *msg, struct envoy_config_core_v3_Node* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Node* envoy_service_status_v3_ClientConfig_mutable_node(envoy_service_status_v3_ClientConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Node* sub = (struct envoy_config_core_v3_Node*)envoy_service_status_v3_ClientConfig_node(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Node*)_upb_Message_New(&envoy__config__core__v3__Node_msg_init, arena);
    if (sub) envoy_service_status_v3_ClientConfig_set_node(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_service_status_v3_PerXdsConfig** envoy_service_status_v3_ClientConfig_mutable_xds_config(envoy_service_status_v3_ClientConfig* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__PerXdsConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_service_status_v3_PerXdsConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_service_status_v3_PerXdsConfig** envoy_service_status_v3_ClientConfig_resize_xds_config(envoy_service_status_v3_ClientConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_service_status_v3_PerXdsConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_service_status_v3_PerXdsConfig* envoy_service_status_v3_ClientConfig_add_xds_config(envoy_service_status_v3_ClientConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__PerXdsConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_service_status_v3_PerXdsConfig* sub = (struct envoy_service_status_v3_PerXdsConfig*)_upb_Message_New(&envoy__service__status__v3__PerXdsConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_service_status_v3_ClientConfig_GenericXdsConfig** envoy_service_status_v3_ClientConfig_mutable_generic_xds_configs(envoy_service_status_v3_ClientConfig* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_service_status_v3_ClientConfig_GenericXdsConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_service_status_v3_ClientConfig_GenericXdsConfig** envoy_service_status_v3_ClientConfig_resize_generic_xds_configs(envoy_service_status_v3_ClientConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_service_status_v3_ClientConfig_GenericXdsConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_service_status_v3_ClientConfig_GenericXdsConfig* envoy_service_status_v3_ClientConfig_add_generic_xds_configs(envoy_service_status_v3_ClientConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_service_status_v3_ClientConfig_GenericXdsConfig* sub = (struct envoy_service_status_v3_ClientConfig_GenericXdsConfig*)_upb_Message_New(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_set_client_scope(envoy_service_status_v3_ClientConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_service_status_v3_ClientConfig_GenericXdsConfig* envoy_service_status_v3_ClientConfig_GenericXdsConfig_new(upb_Arena* arena) {
  return (envoy_service_status_v3_ClientConfig_GenericXdsConfig*)_upb_Message_New(&envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init, arena);
}
UPB_INLINE envoy_service_status_v3_ClientConfig_GenericXdsConfig* envoy_service_status_v3_ClientConfig_GenericXdsConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_service_status_v3_ClientConfig_GenericXdsConfig* ret = envoy_service_status_v3_ClientConfig_GenericXdsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_service_status_v3_ClientConfig_GenericXdsConfig* envoy_service_status_v3_ClientConfig_GenericXdsConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_service_status_v3_ClientConfig_GenericXdsConfig* ret = envoy_service_status_v3_ClientConfig_GenericXdsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_service_status_v3_ClientConfig_GenericXdsConfig_serialize(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_service_status_v3_ClientConfig_GenericXdsConfig_serialize_ex(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_type_url(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_service_status_v3_ClientConfig_GenericXdsConfig_type_url(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_name(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {2, 40, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_service_status_v3_ClientConfig_GenericXdsConfig_name(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 40, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_version_info(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(48, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_service_status_v3_ClientConfig_GenericXdsConfig_version_info(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(48, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_xds_config(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_service_status_v3_ClientConfig_GenericXdsConfig_xds_config(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_ClientConfig_GenericXdsConfig_has_xds_config(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_last_updated(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_service_status_v3_ClientConfig_GenericXdsConfig_last_updated(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_ClientConfig_GenericXdsConfig_has_last_updated(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_config_status(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_service_status_v3_ClientConfig_GenericXdsConfig_config_status(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_client_status(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_service_status_v3_ClientConfig_GenericXdsConfig_client_status(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_error_state(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_UpdateFailureState* envoy_service_status_v3_ClientConfig_GenericXdsConfig_error_state(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const struct envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const struct envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_service_status_v3_ClientConfig_GenericXdsConfig_has_error_state(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_clear_is_static_resource(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  const upb_MiniTableField field = {9, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_service_status_v3_ClientConfig_GenericXdsConfig_is_static_resource(const envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {9, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_type_url(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_name(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 40, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_version_info(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(48, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_xds_config(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_service_status_v3_ClientConfig_GenericXdsConfig_mutable_xds_config(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_service_status_v3_ClientConfig_GenericXdsConfig_xds_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_xds_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_last_updated(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_service_status_v3_ClientConfig_GenericXdsConfig_mutable_last_updated(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_service_status_v3_ClientConfig_GenericXdsConfig_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_config_status(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, int32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_client_status(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, int32_t value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_error_state(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, struct envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_service_status_v3_ClientConfig_GenericXdsConfig_mutable_error_state(envoy_service_status_v3_ClientConfig_GenericXdsConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_service_status_v3_ClientConfig_GenericXdsConfig_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_service_status_v3_ClientConfig_GenericXdsConfig_set_is_static_resource(envoy_service_status_v3_ClientConfig_GenericXdsConfig *msg, bool value) {
  const upb_MiniTableField field = {9, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_service_status_v3_ClientStatusResponse* envoy_service_status_v3_ClientStatusResponse_new(upb_Arena* arena) {
  return (envoy_service_status_v3_ClientStatusResponse*)_upb_Message_New(&envoy__service__status__v3__ClientStatusResponse_msg_init, arena);
}
UPB_INLINE envoy_service_status_v3_ClientStatusResponse* envoy_service_status_v3_ClientStatusResponse_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_service_status_v3_ClientStatusResponse* ret = envoy_service_status_v3_ClientStatusResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientStatusResponse_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_service_status_v3_ClientStatusResponse* envoy_service_status_v3_ClientStatusResponse_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_service_status_v3_ClientStatusResponse* ret = envoy_service_status_v3_ClientStatusResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__service__status__v3__ClientStatusResponse_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_service_status_v3_ClientStatusResponse_serialize(const envoy_service_status_v3_ClientStatusResponse* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientStatusResponse_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_service_status_v3_ClientStatusResponse_serialize_ex(const envoy_service_status_v3_ClientStatusResponse* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__service__status__v3__ClientStatusResponse_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_service_status_v3_ClientStatusResponse_clear_config(envoy_service_status_v3_ClientStatusResponse* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_service_status_v3_ClientConfig* const* envoy_service_status_v3_ClientStatusResponse_config(const envoy_service_status_v3_ClientStatusResponse* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_service_status_v3_ClientConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_service_status_v3_ClientStatusResponse_config_upb_array(const envoy_service_status_v3_ClientStatusResponse* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_service_status_v3_ClientStatusResponse_config_mutable_upb_array(envoy_service_status_v3_ClientStatusResponse* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_service_status_v3_ClientConfig** envoy_service_status_v3_ClientStatusResponse_mutable_config(envoy_service_status_v3_ClientStatusResponse* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_service_status_v3_ClientConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_service_status_v3_ClientConfig** envoy_service_status_v3_ClientStatusResponse_resize_config(envoy_service_status_v3_ClientStatusResponse* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_service_status_v3_ClientConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_service_status_v3_ClientConfig* envoy_service_status_v3_ClientStatusResponse_add_config(envoy_service_status_v3_ClientStatusResponse* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__service__status__v3__ClientConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_service_status_v3_ClientConfig* sub = (struct envoy_service_status_v3_ClientConfig*)_upb_Message_New(&envoy__service__status__v3__ClientConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
