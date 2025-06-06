
#ifndef ENVOY_ADMIN_V3_CONFIG_DUMP_SHARED_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_CONFIG_DUMP_SHARED_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/config_dump_shared.upb_minitable.h"

#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_UpdateFailureState { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_UpdateFailureState;
typedef struct envoy_admin_v3_ListenersConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ListenersConfigDump;
typedef struct envoy_admin_v3_ListenersConfigDump_StaticListener { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ListenersConfigDump_StaticListener;
typedef struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ListenersConfigDump_DynamicListenerState;
typedef struct envoy_admin_v3_ListenersConfigDump_DynamicListener { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ListenersConfigDump_DynamicListener;
typedef struct envoy_admin_v3_ClustersConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ClustersConfigDump;
typedef struct envoy_admin_v3_ClustersConfigDump_StaticCluster { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ClustersConfigDump_StaticCluster;
typedef struct envoy_admin_v3_ClustersConfigDump_DynamicCluster { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ClustersConfigDump_DynamicCluster;
typedef struct envoy_admin_v3_RoutesConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_RoutesConfigDump;
typedef struct envoy_admin_v3_RoutesConfigDump_StaticRouteConfig { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_RoutesConfigDump_StaticRouteConfig;
typedef struct envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig;
typedef struct envoy_admin_v3_ScopedRoutesConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ScopedRoutesConfigDump;
typedef struct envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs;
typedef struct envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs;
typedef struct envoy_admin_v3_EndpointsConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_EndpointsConfigDump;
typedef struct envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig;
typedef struct envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig;
typedef struct envoy_admin_v3_EcdsConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_EcdsConfigDump;
typedef struct envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig;
struct google_protobuf_Any;
struct google_protobuf_Timestamp;

typedef enum {
  envoy_admin_v3_UNKNOWN = 0,
  envoy_admin_v3_REQUESTED = 1,
  envoy_admin_v3_DOES_NOT_EXIST = 2,
  envoy_admin_v3_ACKED = 3,
  envoy_admin_v3_NACKED = 4,
  envoy_admin_v3_RECEIVED_ERROR = 5,
  envoy_admin_v3_TIMEOUT = 6
} envoy_admin_v3_ClientResourceStatus;

UPB_INLINE envoy_admin_v3_UpdateFailureState* envoy_admin_v3_UpdateFailureState_new(upb_Arena* arena) {
  return (envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_UpdateFailureState* envoy_admin_v3_UpdateFailureState_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_UpdateFailureState* ret = envoy_admin_v3_UpdateFailureState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__UpdateFailureState_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_UpdateFailureState* envoy_admin_v3_UpdateFailureState_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_UpdateFailureState* ret = envoy_admin_v3_UpdateFailureState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__UpdateFailureState_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_UpdateFailureState_serialize(const envoy_admin_v3_UpdateFailureState* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__UpdateFailureState_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_UpdateFailureState_serialize_ex(const envoy_admin_v3_UpdateFailureState* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__UpdateFailureState_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_clear_failed_configuration(envoy_admin_v3_UpdateFailureState* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_UpdateFailureState_failed_configuration(const envoy_admin_v3_UpdateFailureState* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_UpdateFailureState_has_failed_configuration(const envoy_admin_v3_UpdateFailureState* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_clear_last_update_attempt(envoy_admin_v3_UpdateFailureState* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_UpdateFailureState_last_update_attempt(const envoy_admin_v3_UpdateFailureState* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_UpdateFailureState_has_last_update_attempt(const envoy_admin_v3_UpdateFailureState* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_clear_details(envoy_admin_v3_UpdateFailureState* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_UpdateFailureState_details(const envoy_admin_v3_UpdateFailureState* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_clear_version_info(envoy_admin_v3_UpdateFailureState* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_UpdateFailureState_version_info(const envoy_admin_v3_UpdateFailureState* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_UpdateFailureState_set_failed_configuration(envoy_admin_v3_UpdateFailureState *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_UpdateFailureState_mutable_failed_configuration(envoy_admin_v3_UpdateFailureState* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_UpdateFailureState_failed_configuration(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_UpdateFailureState_set_failed_configuration(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_set_last_update_attempt(envoy_admin_v3_UpdateFailureState *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_UpdateFailureState_mutable_last_update_attempt(envoy_admin_v3_UpdateFailureState* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_UpdateFailureState_last_update_attempt(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_UpdateFailureState_set_last_update_attempt(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_set_details(envoy_admin_v3_UpdateFailureState *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_UpdateFailureState_set_version_info(envoy_admin_v3_UpdateFailureState *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_ListenersConfigDump* envoy_admin_v3_ListenersConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_ListenersConfigDump*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump* envoy_admin_v3_ListenersConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump* ret = envoy_admin_v3_ListenersConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump* envoy_admin_v3_ListenersConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump* ret = envoy_admin_v3_ListenersConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_serialize(const envoy_admin_v3_ListenersConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_serialize_ex(const envoy_admin_v3_ListenersConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_clear_version_info(envoy_admin_v3_ListenersConfigDump* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ListenersConfigDump_version_info(const envoy_admin_v3_ListenersConfigDump* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_clear_static_listeners(envoy_admin_v3_ListenersConfigDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ListenersConfigDump_StaticListener* const* envoy_admin_v3_ListenersConfigDump_static_listeners(const envoy_admin_v3_ListenersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ListenersConfigDump_StaticListener* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ListenersConfigDump_static_listeners_upb_array(const envoy_admin_v3_ListenersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ListenersConfigDump_static_listeners_mutable_upb_array(envoy_admin_v3_ListenersConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_clear_dynamic_listeners(envoy_admin_v3_ListenersConfigDump* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ListenersConfigDump_DynamicListener* const* envoy_admin_v3_ListenersConfigDump_dynamic_listeners(const envoy_admin_v3_ListenersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ListenersConfigDump_DynamicListener* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ListenersConfigDump_dynamic_listeners_upb_array(const envoy_admin_v3_ListenersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ListenersConfigDump_dynamic_listeners_mutable_upb_array(envoy_admin_v3_ListenersConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_admin_v3_ListenersConfigDump_set_version_info(envoy_admin_v3_ListenersConfigDump *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_StaticListener** envoy_admin_v3_ListenersConfigDump_mutable_static_listeners(envoy_admin_v3_ListenersConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ListenersConfigDump_StaticListener**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_StaticListener** envoy_admin_v3_ListenersConfigDump_resize_static_listeners(envoy_admin_v3_ListenersConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ListenersConfigDump_StaticListener**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ListenersConfigDump_StaticListener* envoy_admin_v3_ListenersConfigDump_add_static_listeners(envoy_admin_v3_ListenersConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ListenersConfigDump_StaticListener* sub = (struct envoy_admin_v3_ListenersConfigDump_StaticListener*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListener** envoy_admin_v3_ListenersConfigDump_mutable_dynamic_listeners(envoy_admin_v3_ListenersConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ListenersConfigDump_DynamicListener**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListener** envoy_admin_v3_ListenersConfigDump_resize_dynamic_listeners(envoy_admin_v3_ListenersConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ListenersConfigDump_DynamicListener**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ListenersConfigDump_DynamicListener* envoy_admin_v3_ListenersConfigDump_add_dynamic_listeners(envoy_admin_v3_ListenersConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ListenersConfigDump_DynamicListener* sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListener*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_ListenersConfigDump_StaticListener* envoy_admin_v3_ListenersConfigDump_StaticListener_new(upb_Arena* arena) {
  return (envoy_admin_v3_ListenersConfigDump_StaticListener*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_StaticListener* envoy_admin_v3_ListenersConfigDump_StaticListener_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump_StaticListener* ret = envoy_admin_v3_ListenersConfigDump_StaticListener_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_StaticListener* envoy_admin_v3_ListenersConfigDump_StaticListener_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump_StaticListener* ret = envoy_admin_v3_ListenersConfigDump_StaticListener_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_StaticListener_serialize(const envoy_admin_v3_ListenersConfigDump_StaticListener* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_StaticListener_serialize_ex(const envoy_admin_v3_ListenersConfigDump_StaticListener* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_StaticListener_clear_listener(envoy_admin_v3_ListenersConfigDump_StaticListener* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_ListenersConfigDump_StaticListener_listener(const envoy_admin_v3_ListenersConfigDump_StaticListener* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_StaticListener_has_listener(const envoy_admin_v3_ListenersConfigDump_StaticListener* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_StaticListener_clear_last_updated(envoy_admin_v3_ListenersConfigDump_StaticListener* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_ListenersConfigDump_StaticListener_last_updated(const envoy_admin_v3_ListenersConfigDump_StaticListener* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_StaticListener_has_last_updated(const envoy_admin_v3_ListenersConfigDump_StaticListener* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_ListenersConfigDump_StaticListener_set_listener(envoy_admin_v3_ListenersConfigDump_StaticListener *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ListenersConfigDump_StaticListener_mutable_listener(envoy_admin_v3_ListenersConfigDump_StaticListener* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_ListenersConfigDump_StaticListener_listener(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_StaticListener_set_listener(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_StaticListener_set_last_updated(envoy_admin_v3_ListenersConfigDump_StaticListener *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_ListenersConfigDump_StaticListener_mutable_last_updated(envoy_admin_v3_ListenersConfigDump_StaticListener* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_ListenersConfigDump_StaticListener_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_StaticListener_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_new(upb_Arena* arena) {
  return (envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump_DynamicListenerState* ret = envoy_admin_v3_ListenersConfigDump_DynamicListenerState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump_DynamicListenerState* ret = envoy_admin_v3_ListenersConfigDump_DynamicListenerState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_serialize(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_serialize_ex(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListenerState_clear_version_info(envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ListenersConfigDump_DynamicListenerState_version_info(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListenerState_clear_listener(envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_listener(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_DynamicListenerState_has_listener(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListenerState_clear_last_updated(envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_last_updated(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_DynamicListenerState_has_last_updated(const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListenerState_set_version_info(envoy_admin_v3_ListenersConfigDump_DynamicListenerState *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListenerState_set_listener(envoy_admin_v3_ListenersConfigDump_DynamicListenerState *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_mutable_listener(envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_ListenersConfigDump_DynamicListenerState_listener(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_DynamicListenerState_set_listener(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListenerState_set_last_updated(envoy_admin_v3_ListenersConfigDump_DynamicListenerState *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_ListenersConfigDump_DynamicListenerState_mutable_last_updated(envoy_admin_v3_ListenersConfigDump_DynamicListenerState* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_ListenersConfigDump_DynamicListenerState_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_DynamicListenerState_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListener* envoy_admin_v3_ListenersConfigDump_DynamicListener_new(upb_Arena* arena) {
  return (envoy_admin_v3_ListenersConfigDump_DynamicListener*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListener* envoy_admin_v3_ListenersConfigDump_DynamicListener_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump_DynamicListener* ret = envoy_admin_v3_ListenersConfigDump_DynamicListener_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ListenersConfigDump_DynamicListener* envoy_admin_v3_ListenersConfigDump_DynamicListener_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ListenersConfigDump_DynamicListener* ret = envoy_admin_v3_ListenersConfigDump_DynamicListener_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_DynamicListener_serialize(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ListenersConfigDump_DynamicListener_serialize_ex(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_clear_name(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ListenersConfigDump_DynamicListener_name(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_clear_active_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListener_active_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* default_val = NULL;
  const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_DynamicListener_has_active_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_clear_warming_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListener_warming_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* default_val = NULL;
  const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_DynamicListener_has_warming_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_clear_draining_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListener_draining_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* default_val = NULL;
  const envoy_admin_v3_ListenersConfigDump_DynamicListenerState* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_DynamicListener_has_draining_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_clear_error_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UpdateFailureState* envoy_admin_v3_ListenersConfigDump_DynamicListener_error_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ListenersConfigDump_DynamicListener_has_error_state(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_clear_client_status(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_ListenersConfigDump_DynamicListener_client_status(const envoy_admin_v3_ListenersConfigDump_DynamicListener* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_set_name(envoy_admin_v3_ListenersConfigDump_DynamicListener *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_set_active_state(envoy_admin_v3_ListenersConfigDump_DynamicListener *msg, envoy_admin_v3_ListenersConfigDump_DynamicListenerState* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListener_mutable_active_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg, upb_Arena* arena) {
  struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState* sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)envoy_admin_v3_ListenersConfigDump_DynamicListener_active_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_DynamicListener_set_active_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_set_warming_state(envoy_admin_v3_ListenersConfigDump_DynamicListener *msg, envoy_admin_v3_ListenersConfigDump_DynamicListenerState* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListener_mutable_warming_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg, upb_Arena* arena) {
  struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState* sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)envoy_admin_v3_ListenersConfigDump_DynamicListener_warming_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_DynamicListener_set_warming_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_set_draining_state(envoy_admin_v3_ListenersConfigDump_DynamicListener *msg, envoy_admin_v3_ListenersConfigDump_DynamicListenerState* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState* envoy_admin_v3_ListenersConfigDump_DynamicListener_mutable_draining_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg, upb_Arena* arena) {
  struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState* sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)envoy_admin_v3_ListenersConfigDump_DynamicListener_draining_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_ListenersConfigDump_DynamicListenerState*)_upb_Message_New(&envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_DynamicListener_set_draining_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_set_error_state(envoy_admin_v3_ListenersConfigDump_DynamicListener *msg, envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_ListenersConfigDump_DynamicListener_mutable_error_state(envoy_admin_v3_ListenersConfigDump_DynamicListener* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_ListenersConfigDump_DynamicListener_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_ListenersConfigDump_DynamicListener_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ListenersConfigDump_DynamicListener_set_client_status(envoy_admin_v3_ListenersConfigDump_DynamicListener *msg, int32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_ClustersConfigDump* envoy_admin_v3_ClustersConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_ClustersConfigDump*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump* envoy_admin_v3_ClustersConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ClustersConfigDump* ret = envoy_admin_v3_ClustersConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClustersConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump* envoy_admin_v3_ClustersConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ClustersConfigDump* ret = envoy_admin_v3_ClustersConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClustersConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ClustersConfigDump_serialize(const envoy_admin_v3_ClustersConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClustersConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ClustersConfigDump_serialize_ex(const envoy_admin_v3_ClustersConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClustersConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_clear_version_info(envoy_admin_v3_ClustersConfigDump* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ClustersConfigDump_version_info(const envoy_admin_v3_ClustersConfigDump* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_clear_static_clusters(envoy_admin_v3_ClustersConfigDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ClustersConfigDump_StaticCluster* const* envoy_admin_v3_ClustersConfigDump_static_clusters(const envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ClustersConfigDump_StaticCluster* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ClustersConfigDump_static_clusters_upb_array(const envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ClustersConfigDump_static_clusters_mutable_upb_array(envoy_admin_v3_ClustersConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_clear_dynamic_active_clusters(envoy_admin_v3_ClustersConfigDump* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ClustersConfigDump_DynamicCluster* const* envoy_admin_v3_ClustersConfigDump_dynamic_active_clusters(const envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ClustersConfigDump_DynamicCluster* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ClustersConfigDump_dynamic_active_clusters_upb_array(const envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ClustersConfigDump_dynamic_active_clusters_mutable_upb_array(envoy_admin_v3_ClustersConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_clear_dynamic_warming_clusters(envoy_admin_v3_ClustersConfigDump* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ClustersConfigDump_DynamicCluster* const* envoy_admin_v3_ClustersConfigDump_dynamic_warming_clusters(const envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ClustersConfigDump_DynamicCluster* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ClustersConfigDump_dynamic_warming_clusters_upb_array(const envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ClustersConfigDump_dynamic_warming_clusters_mutable_upb_array(envoy_admin_v3_ClustersConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_admin_v3_ClustersConfigDump_set_version_info(envoy_admin_v3_ClustersConfigDump *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_StaticCluster** envoy_admin_v3_ClustersConfigDump_mutable_static_clusters(envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ClustersConfigDump_StaticCluster**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_StaticCluster** envoy_admin_v3_ClustersConfigDump_resize_static_clusters(envoy_admin_v3_ClustersConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ClustersConfigDump_StaticCluster**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ClustersConfigDump_StaticCluster* envoy_admin_v3_ClustersConfigDump_add_static_clusters(envoy_admin_v3_ClustersConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ClustersConfigDump_StaticCluster* sub = (struct envoy_admin_v3_ClustersConfigDump_StaticCluster*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster** envoy_admin_v3_ClustersConfigDump_mutable_dynamic_active_clusters(envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ClustersConfigDump_DynamicCluster**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster** envoy_admin_v3_ClustersConfigDump_resize_dynamic_active_clusters(envoy_admin_v3_ClustersConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ClustersConfigDump_DynamicCluster**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ClustersConfigDump_DynamicCluster* envoy_admin_v3_ClustersConfigDump_add_dynamic_active_clusters(envoy_admin_v3_ClustersConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ClustersConfigDump_DynamicCluster* sub = (struct envoy_admin_v3_ClustersConfigDump_DynamicCluster*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster** envoy_admin_v3_ClustersConfigDump_mutable_dynamic_warming_clusters(envoy_admin_v3_ClustersConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ClustersConfigDump_DynamicCluster**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster** envoy_admin_v3_ClustersConfigDump_resize_dynamic_warming_clusters(envoy_admin_v3_ClustersConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ClustersConfigDump_DynamicCluster**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ClustersConfigDump_DynamicCluster* envoy_admin_v3_ClustersConfigDump_add_dynamic_warming_clusters(envoy_admin_v3_ClustersConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ClustersConfigDump_DynamicCluster* sub = (struct envoy_admin_v3_ClustersConfigDump_DynamicCluster*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_ClustersConfigDump_StaticCluster* envoy_admin_v3_ClustersConfigDump_StaticCluster_new(upb_Arena* arena) {
  return (envoy_admin_v3_ClustersConfigDump_StaticCluster*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_StaticCluster* envoy_admin_v3_ClustersConfigDump_StaticCluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ClustersConfigDump_StaticCluster* ret = envoy_admin_v3_ClustersConfigDump_StaticCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_StaticCluster* envoy_admin_v3_ClustersConfigDump_StaticCluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ClustersConfigDump_StaticCluster* ret = envoy_admin_v3_ClustersConfigDump_StaticCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ClustersConfigDump_StaticCluster_serialize(const envoy_admin_v3_ClustersConfigDump_StaticCluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ClustersConfigDump_StaticCluster_serialize_ex(const envoy_admin_v3_ClustersConfigDump_StaticCluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_StaticCluster_clear_cluster(envoy_admin_v3_ClustersConfigDump_StaticCluster* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_ClustersConfigDump_StaticCluster_cluster(const envoy_admin_v3_ClustersConfigDump_StaticCluster* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClustersConfigDump_StaticCluster_has_cluster(const envoy_admin_v3_ClustersConfigDump_StaticCluster* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_StaticCluster_clear_last_updated(envoy_admin_v3_ClustersConfigDump_StaticCluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_ClustersConfigDump_StaticCluster_last_updated(const envoy_admin_v3_ClustersConfigDump_StaticCluster* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClustersConfigDump_StaticCluster_has_last_updated(const envoy_admin_v3_ClustersConfigDump_StaticCluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_ClustersConfigDump_StaticCluster_set_cluster(envoy_admin_v3_ClustersConfigDump_StaticCluster *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ClustersConfigDump_StaticCluster_mutable_cluster(envoy_admin_v3_ClustersConfigDump_StaticCluster* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_ClustersConfigDump_StaticCluster_cluster(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_ClustersConfigDump_StaticCluster_set_cluster(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_StaticCluster_set_last_updated(envoy_admin_v3_ClustersConfigDump_StaticCluster *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_ClustersConfigDump_StaticCluster_mutable_last_updated(envoy_admin_v3_ClustersConfigDump_StaticCluster* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_ClustersConfigDump_StaticCluster_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_ClustersConfigDump_StaticCluster_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster* envoy_admin_v3_ClustersConfigDump_DynamicCluster_new(upb_Arena* arena) {
  return (envoy_admin_v3_ClustersConfigDump_DynamicCluster*)_upb_Message_New(&envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster* envoy_admin_v3_ClustersConfigDump_DynamicCluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ClustersConfigDump_DynamicCluster* ret = envoy_admin_v3_ClustersConfigDump_DynamicCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ClustersConfigDump_DynamicCluster* envoy_admin_v3_ClustersConfigDump_DynamicCluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ClustersConfigDump_DynamicCluster* ret = envoy_admin_v3_ClustersConfigDump_DynamicCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ClustersConfigDump_DynamicCluster_serialize(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ClustersConfigDump_DynamicCluster_serialize_ex(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_clear_version_info(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ClustersConfigDump_DynamicCluster_version_info(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_clear_cluster(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_ClustersConfigDump_DynamicCluster_cluster(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClustersConfigDump_DynamicCluster_has_cluster(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_clear_last_updated(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_ClustersConfigDump_DynamicCluster_last_updated(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClustersConfigDump_DynamicCluster_has_last_updated(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_clear_error_state(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UpdateFailureState* envoy_admin_v3_ClustersConfigDump_DynamicCluster_error_state(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ClustersConfigDump_DynamicCluster_has_error_state(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_clear_client_status(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_ClustersConfigDump_DynamicCluster_client_status(const envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_version_info(envoy_admin_v3_ClustersConfigDump_DynamicCluster *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_cluster(envoy_admin_v3_ClustersConfigDump_DynamicCluster *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ClustersConfigDump_DynamicCluster_mutable_cluster(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_ClustersConfigDump_DynamicCluster_cluster(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_cluster(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_last_updated(envoy_admin_v3_ClustersConfigDump_DynamicCluster *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_ClustersConfigDump_DynamicCluster_mutable_last_updated(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_ClustersConfigDump_DynamicCluster_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_error_state(envoy_admin_v3_ClustersConfigDump_DynamicCluster *msg, envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_ClustersConfigDump_DynamicCluster_mutable_error_state(envoy_admin_v3_ClustersConfigDump_DynamicCluster* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_ClustersConfigDump_DynamicCluster_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ClustersConfigDump_DynamicCluster_set_client_status(envoy_admin_v3_ClustersConfigDump_DynamicCluster *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_RoutesConfigDump* envoy_admin_v3_RoutesConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_RoutesConfigDump*)_upb_Message_New(&envoy__admin__v3__RoutesConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump* envoy_admin_v3_RoutesConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_RoutesConfigDump* ret = envoy_admin_v3_RoutesConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__RoutesConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump* envoy_admin_v3_RoutesConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_RoutesConfigDump* ret = envoy_admin_v3_RoutesConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__RoutesConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_RoutesConfigDump_serialize(const envoy_admin_v3_RoutesConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__RoutesConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_RoutesConfigDump_serialize_ex(const envoy_admin_v3_RoutesConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__RoutesConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_clear_static_route_configs(envoy_admin_v3_RoutesConfigDump* msg) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* const* envoy_admin_v3_RoutesConfigDump_static_route_configs(const envoy_admin_v3_RoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_RoutesConfigDump_static_route_configs_upb_array(const envoy_admin_v3_RoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_RoutesConfigDump_static_route_configs_mutable_upb_array(envoy_admin_v3_RoutesConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_clear_dynamic_route_configs(envoy_admin_v3_RoutesConfigDump* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* const* envoy_admin_v3_RoutesConfigDump_dynamic_route_configs(const envoy_admin_v3_RoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_RoutesConfigDump_dynamic_route_configs_upb_array(const envoy_admin_v3_RoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_RoutesConfigDump_dynamic_route_configs_mutable_upb_array(envoy_admin_v3_RoutesConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_RoutesConfigDump_StaticRouteConfig** envoy_admin_v3_RoutesConfigDump_mutable_static_route_configs(envoy_admin_v3_RoutesConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_RoutesConfigDump_StaticRouteConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_StaticRouteConfig** envoy_admin_v3_RoutesConfigDump_resize_static_route_configs(envoy_admin_v3_RoutesConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_RoutesConfigDump_StaticRouteConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* envoy_admin_v3_RoutesConfigDump_add_static_route_configs(envoy_admin_v3_RoutesConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* sub = (struct envoy_admin_v3_RoutesConfigDump_StaticRouteConfig*)_upb_Message_New(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig** envoy_admin_v3_RoutesConfigDump_mutable_dynamic_route_configs(envoy_admin_v3_RoutesConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig** envoy_admin_v3_RoutesConfigDump_resize_dynamic_route_configs(envoy_admin_v3_RoutesConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* envoy_admin_v3_RoutesConfigDump_add_dynamic_route_configs(envoy_admin_v3_RoutesConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* sub = (struct envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig*)_upb_Message_New(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_new(upb_Arena* arena) {
  return (envoy_admin_v3_RoutesConfigDump_StaticRouteConfig*)_upb_Message_New(&envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* ret = envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* ret = envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_serialize(const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_serialize_ex(const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_clear_route_config(envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_route_config(const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_has_route_config(const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_clear_last_updated(envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_last_updated(const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_has_last_updated(const envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_set_route_config(envoy_admin_v3_RoutesConfigDump_StaticRouteConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_mutable_route_config(envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_route_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_set_route_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_set_last_updated(envoy_admin_v3_RoutesConfigDump_StaticRouteConfig *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_mutable_last_updated(envoy_admin_v3_RoutesConfigDump_StaticRouteConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_new(upb_Arena* arena) {
  return (envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig*)_upb_Message_New(&envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* ret = envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* ret = envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_serialize(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_serialize_ex(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_clear_version_info(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_version_info(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_clear_route_config(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_route_config(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_has_route_config(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_clear_last_updated(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_last_updated(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_has_last_updated(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_clear_error_state(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UpdateFailureState* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_error_state(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_has_error_state(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_clear_client_status(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_client_status(const envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_version_info(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_route_config(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_mutable_route_config(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_route_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_route_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_last_updated(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_mutable_last_updated(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_error_state(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig *msg, envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_mutable_error_state(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_set_client_status(envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump* envoy_admin_v3_ScopedRoutesConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_ScopedRoutesConfigDump*)_upb_Message_New(&envoy__admin__v3__ScopedRoutesConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump* envoy_admin_v3_ScopedRoutesConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ScopedRoutesConfigDump* ret = envoy_admin_v3_ScopedRoutesConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ScopedRoutesConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump* envoy_admin_v3_ScopedRoutesConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ScopedRoutesConfigDump* ret = envoy_admin_v3_ScopedRoutesConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ScopedRoutesConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ScopedRoutesConfigDump_serialize(const envoy_admin_v3_ScopedRoutesConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ScopedRoutesConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ScopedRoutesConfigDump_serialize_ex(const envoy_admin_v3_ScopedRoutesConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ScopedRoutesConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_clear_inline_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* const* envoy_admin_v3_ScopedRoutesConfigDump_inline_scoped_route_configs(const envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_inline_scoped_route_configs_upb_array(const envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_inline_scoped_route_configs_mutable_upb_array(envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_clear_dynamic_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* const* envoy_admin_v3_ScopedRoutesConfigDump_dynamic_scoped_route_configs(const envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_dynamic_scoped_route_configs_upb_array(const envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_dynamic_scoped_route_configs_mutable_upb_array(envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs** envoy_admin_v3_ScopedRoutesConfigDump_mutable_inline_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs** envoy_admin_v3_ScopedRoutesConfigDump_resize_inline_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_add_inline_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* sub = (struct envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs*)_upb_Message_New(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs** envoy_admin_v3_ScopedRoutesConfigDump_mutable_dynamic_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs** envoy_admin_v3_ScopedRoutesConfigDump_resize_dynamic_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_add_dynamic_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* sub = (struct envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs*)_upb_Message_New(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_new(upb_Arena* arena) {
  return (envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs*)_upb_Message_New(&envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* ret = envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* ret = envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_serialize(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_serialize_ex(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_clear_name(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_name(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_clear_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* const* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_scoped_route_configs(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct google_protobuf_Any* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_scoped_route_configs_upb_array(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_scoped_route_configs_mutable_upb_array(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_clear_last_updated(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_last_updated(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_has_last_updated(const envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_set_name(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any** envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_mutable_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct google_protobuf_Any**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct google_protobuf_Any** envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_resize_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct google_protobuf_Any**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_add_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_set_last_updated(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_mutable_last_updated(envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_new(upb_Arena* arena) {
  return (envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs*)_upb_Message_New(&envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* ret = envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* ret = envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_serialize(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_serialize_ex(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_clear_name(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_name(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_clear_version_info(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_version_info(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_clear_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* const* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_scoped_route_configs(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct google_protobuf_Any* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_scoped_route_configs_upb_array(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_scoped_route_configs_mutable_upb_array(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_clear_last_updated(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_last_updated(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_has_last_updated(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_clear_error_state(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UpdateFailureState* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_error_state(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_has_error_state(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_clear_client_status(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_client_status(const envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_name(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_version_info(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any** envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_mutable_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct google_protobuf_Any**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct google_protobuf_Any** envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_resize_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct google_protobuf_Any**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_add_scoped_route_configs(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_last_updated(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_mutable_last_updated(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_error_state(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs *msg, envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_mutable_error_state(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_set_client_status(envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs *msg, int32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_EndpointsConfigDump* envoy_admin_v3_EndpointsConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_EndpointsConfigDump*)_upb_Message_New(&envoy__admin__v3__EndpointsConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump* envoy_admin_v3_EndpointsConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_EndpointsConfigDump* ret = envoy_admin_v3_EndpointsConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EndpointsConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump* envoy_admin_v3_EndpointsConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_EndpointsConfigDump* ret = envoy_admin_v3_EndpointsConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EndpointsConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_EndpointsConfigDump_serialize(const envoy_admin_v3_EndpointsConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EndpointsConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_EndpointsConfigDump_serialize_ex(const envoy_admin_v3_EndpointsConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EndpointsConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_clear_static_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* const* envoy_admin_v3_EndpointsConfigDump_static_endpoint_configs(const envoy_admin_v3_EndpointsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_EndpointsConfigDump_static_endpoint_configs_upb_array(const envoy_admin_v3_EndpointsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_EndpointsConfigDump_static_endpoint_configs_mutable_upb_array(envoy_admin_v3_EndpointsConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_clear_dynamic_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* const* envoy_admin_v3_EndpointsConfigDump_dynamic_endpoint_configs(const envoy_admin_v3_EndpointsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_EndpointsConfigDump_dynamic_endpoint_configs_upb_array(const envoy_admin_v3_EndpointsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_EndpointsConfigDump_dynamic_endpoint_configs_mutable_upb_array(envoy_admin_v3_EndpointsConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig** envoy_admin_v3_EndpointsConfigDump_mutable_static_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig** envoy_admin_v3_EndpointsConfigDump_resize_static_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* envoy_admin_v3_EndpointsConfigDump_add_static_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* sub = (struct envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig*)_upb_Message_New(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig** envoy_admin_v3_EndpointsConfigDump_mutable_dynamic_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig** envoy_admin_v3_EndpointsConfigDump_resize_dynamic_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* envoy_admin_v3_EndpointsConfigDump_add_dynamic_endpoint_configs(envoy_admin_v3_EndpointsConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* sub = (struct envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig*)_upb_Message_New(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_new(upb_Arena* arena) {
  return (envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig*)_upb_Message_New(&envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* ret = envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* ret = envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_serialize(const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_serialize_ex(const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_clear_endpoint_config(envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_endpoint_config(const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_has_endpoint_config(const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_clear_last_updated(envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_last_updated(const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_has_last_updated(const envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_set_endpoint_config(envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_mutable_endpoint_config(envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_endpoint_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_set_endpoint_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_set_last_updated(envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_mutable_last_updated(envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_new(upb_Arena* arena) {
  return (envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig*)_upb_Message_New(&envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* ret = envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* ret = envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_serialize(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_serialize_ex(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_clear_version_info(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_version_info(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_clear_endpoint_config(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_endpoint_config(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_has_endpoint_config(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_clear_last_updated(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_last_updated(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_has_last_updated(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_clear_error_state(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UpdateFailureState* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_error_state(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_has_error_state(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_clear_client_status(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_client_status(const envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_version_info(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_endpoint_config(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_mutable_endpoint_config(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_endpoint_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_endpoint_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_last_updated(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_mutable_last_updated(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_error_state(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig *msg, envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_mutable_error_state(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_set_client_status(envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_EcdsConfigDump* envoy_admin_v3_EcdsConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_EcdsConfigDump*)_upb_Message_New(&envoy__admin__v3__EcdsConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_EcdsConfigDump* envoy_admin_v3_EcdsConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_EcdsConfigDump* ret = envoy_admin_v3_EcdsConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EcdsConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_EcdsConfigDump* envoy_admin_v3_EcdsConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_EcdsConfigDump* ret = envoy_admin_v3_EcdsConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EcdsConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_EcdsConfigDump_serialize(const envoy_admin_v3_EcdsConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EcdsConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_EcdsConfigDump_serialize_ex(const envoy_admin_v3_EcdsConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EcdsConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_clear_ecds_filters(envoy_admin_v3_EcdsConfigDump* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* const* envoy_admin_v3_EcdsConfigDump_ecds_filters(const envoy_admin_v3_EcdsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_EcdsConfigDump_ecds_filters_upb_array(const envoy_admin_v3_EcdsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_EcdsConfigDump_ecds_filters_mutable_upb_array(envoy_admin_v3_EcdsConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig** envoy_admin_v3_EcdsConfigDump_mutable_ecds_filters(envoy_admin_v3_EcdsConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig** envoy_admin_v3_EcdsConfigDump_resize_ecds_filters(envoy_admin_v3_EcdsConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* envoy_admin_v3_EcdsConfigDump_add_ecds_filters(envoy_admin_v3_EcdsConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* sub = (struct envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig*)_upb_Message_New(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_new(upb_Arena* arena) {
  return (envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig*)_upb_Message_New(&envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* ret = envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* ret = envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_serialize(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_serialize_ex(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_clear_version_info(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_version_info(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_clear_ecds_filter(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_ecds_filter(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_has_ecds_filter(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_clear_last_updated(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_last_updated(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_has_last_updated(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_clear_error_state(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UpdateFailureState* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_error_state(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_has_error_state(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_clear_client_status(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_client_status(const envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_version_info(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_ecds_filter(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_mutable_ecds_filter(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_ecds_filter(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_ecds_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_last_updated(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_mutable_last_updated(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_error_state(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig *msg, envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_mutable_error_state(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_set_client_status(envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
