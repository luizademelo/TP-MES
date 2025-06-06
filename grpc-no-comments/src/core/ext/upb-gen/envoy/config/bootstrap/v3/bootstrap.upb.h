
#ifndef ENVOY_CONFIG_BOOTSTRAP_V3_BOOTSTRAP_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_BOOTSTRAP_V3_BOOTSTRAP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/bootstrap/v3/bootstrap.upb_minitable.h"

#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/cluster/v3/cluster.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/config/core/v3/event_service_config.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/resolver.upb_minitable.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"
#include "envoy/config/listener/v3/listener.upb_minitable.h"
#include "envoy/config/metrics/v3/stats.upb_minitable.h"
#include "envoy/config/overload/v3/overload.upb_minitable.h"
#include "envoy/config/trace/v3/http_tracer.upb_minitable.h"
#include "envoy/extensions/transport_sockets/tls/v3/secret.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/security.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_bootstrap_v3_Bootstrap { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap;
typedef struct envoy_config_bootstrap_v3_Bootstrap_StaticResources { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap_StaticResources;
typedef struct envoy_config_bootstrap_v3_Bootstrap_DynamicResources { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap_DynamicResources;
typedef struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig;
typedef struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat;
typedef struct envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions;
typedef struct envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig;
typedef struct envoy_config_bootstrap_v3_Admin { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Admin;
typedef struct envoy_config_bootstrap_v3_ClusterManager { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_ClusterManager;
typedef struct envoy_config_bootstrap_v3_ClusterManager_OutlierDetection { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_ClusterManager_OutlierDetection;
typedef struct envoy_config_bootstrap_v3_Watchdogs { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Watchdogs;
typedef struct envoy_config_bootstrap_v3_Watchdog { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Watchdog;
typedef struct envoy_config_bootstrap_v3_Watchdog_WatchdogAction { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Watchdog_WatchdogAction;
typedef struct envoy_config_bootstrap_v3_FatalAction { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_FatalAction;
typedef struct envoy_config_bootstrap_v3_Runtime { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_Runtime;
typedef struct envoy_config_bootstrap_v3_RuntimeLayer { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_RuntimeLayer;
typedef struct envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer;
typedef struct envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer;
typedef struct envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer;
typedef struct envoy_config_bootstrap_v3_LayeredRuntime { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_LayeredRuntime;
typedef struct envoy_config_bootstrap_v3_CustomInlineHeader { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_CustomInlineHeader;
typedef struct envoy_config_bootstrap_v3_MemoryAllocatorManager { upb_Message UPB_PRIVATE(base); } envoy_config_bootstrap_v3_MemoryAllocatorManager;
struct envoy_config_accesslog_v3_AccessLog;
struct envoy_config_cluster_v3_Cluster;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_ApiConfigSource;
struct envoy_config_core_v3_BindConfig;
struct envoy_config_core_v3_ConfigSource;
struct envoy_config_core_v3_DnsResolutionConfig;
struct envoy_config_core_v3_EventServiceConfig;
struct envoy_config_core_v3_Node;
struct envoy_config_core_v3_SocketOption;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_listener_v3_Listener;
struct envoy_config_metrics_v3_StatsConfig;
struct envoy_config_metrics_v3_StatsSink;
struct envoy_config_overload_v3_OverloadManager;
struct envoy_config_trace_v3_Tracing;
struct envoy_extensions_transport_sockets_tls_v3_Secret;
struct envoy_type_v3_Percent;
struct google_protobuf_Duration;
struct google_protobuf_Struct;
struct google_protobuf_UInt64Value;

typedef enum {
  envoy_config_bootstrap_v3_CustomInlineHeader_REQUEST_HEADER = 0,
  envoy_config_bootstrap_v3_CustomInlineHeader_REQUEST_TRAILER = 1,
  envoy_config_bootstrap_v3_CustomInlineHeader_RESPONSE_HEADER = 2,
  envoy_config_bootstrap_v3_CustomInlineHeader_RESPONSE_TRAILER = 3
} envoy_config_bootstrap_v3_CustomInlineHeader_InlineHeaderType;

typedef enum {
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction_UNKNOWN = 0,
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction_KILL = 1,
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction_MULTIKILL = 2,
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction_MEGAMISS = 3,
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction_MISS = 4
} envoy_config_bootstrap_v3_Watchdog_WatchdogAction_WatchdogEvent;

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap* envoy_config_bootstrap_v3_Bootstrap_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap* envoy_config_bootstrap_v3_Bootstrap_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap* ret = envoy_config_bootstrap_v3_Bootstrap_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap* envoy_config_bootstrap_v3_Bootstrap_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap* ret = envoy_config_bootstrap_v3_Bootstrap_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_serialize(const envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_bootstrap_v3_Bootstrap_stats_flush_stats_flush_on_admin = 29,
  envoy_config_bootstrap_v3_Bootstrap_stats_flush_NOT_SET = 0
} envoy_config_bootstrap_v3_Bootstrap_stats_flush_oneofcases;
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_stats_flush_oneofcases envoy_config_bootstrap_v3_Bootstrap_stats_flush_case(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_Bootstrap_stats_flush_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_stats_flush(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap_msg_init, &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_node(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 88), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Node* envoy_config_bootstrap_v3_Bootstrap_node(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_Node* default_val = NULL;
  const struct envoy_config_core_v3_Node* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(16, 88), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_node(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 88), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_static_resources(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 96), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Bootstrap_StaticResources* envoy_config_bootstrap_v3_Bootstrap_static_resources(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Bootstrap_StaticResources* default_val = NULL;
  const envoy_config_bootstrap_v3_Bootstrap_StaticResources* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 96), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_static_resources(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 96), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_dynamic_resources(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 104), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* envoy_config_bootstrap_v3_Bootstrap_dynamic_resources(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* default_val = NULL;
  const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 104), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_dynamic_resources(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 104), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_cluster_manager(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 112), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_ClusterManager* envoy_config_bootstrap_v3_Bootstrap_cluster_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_ClusterManager* default_val = NULL;
  const envoy_config_bootstrap_v3_ClusterManager* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(28, 112), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__ClusterManager_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_cluster_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 112), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_flags_path(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(148, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_flags_path(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(148, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_stats_sinks(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_metrics_v3_StatsSink* const* envoy_config_bootstrap_v3_Bootstrap_stats_sinks(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsSink_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_metrics_v3_StatsSink* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_stats_sinks_upb_array(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsSink_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_stats_sinks_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsSink_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_stats_flush_interval(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 128), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Bootstrap_stats_flush_interval(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 128), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_stats_flush_interval(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 128), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_watchdog(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 136), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Bootstrap_watchdog(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Watchdog* default_val = NULL;
  const envoy_config_bootstrap_v3_Watchdog* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(40, 136), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_watchdog(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 136), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_tracing(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 144), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_trace_v3_Tracing* envoy_config_bootstrap_v3_Bootstrap_tracing(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_trace_v3_Tracing* default_val = NULL;
  const struct envoy_config_trace_v3_Tracing* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(44, 144), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__Tracing_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_tracing(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 144), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_admin(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 152), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Admin* envoy_config_bootstrap_v3_Bootstrap_admin(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Admin* default_val = NULL;
  const envoy_config_bootstrap_v3_Admin* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(48, 152), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Admin_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_admin(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 152), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_stats_config(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 160), 72, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_metrics_v3_StatsConfig* envoy_config_bootstrap_v3_Bootstrap_stats_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_metrics_v3_StatsConfig* default_val = NULL;
  const struct envoy_config_metrics_v3_StatsConfig* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(52, 160), 72, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_stats_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 160), 72, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_hds_config(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(56, 168), 73, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ApiConfigSource* envoy_config_bootstrap_v3_Bootstrap_hds_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_ApiConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ApiConfigSource* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(56, 168), 73, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ApiConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_hds_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(56, 168), 73, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_overload_manager(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(60, 176), 74, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_overload_v3_OverloadManager* envoy_config_bootstrap_v3_Bootstrap_overload_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_overload_v3_OverloadManager* default_val = NULL;
  const struct envoy_config_overload_v3_OverloadManager* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(60, 176), 74, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadManager_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_overload_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(60, 176), 74, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_enable_dispatcher_stats(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {16, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_enable_dispatcher_stats(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {16, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_layered_runtime(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(64, 184), 75, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_LayeredRuntime* envoy_config_bootstrap_v3_Bootstrap_layered_runtime(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_LayeredRuntime* default_val = NULL;
  const envoy_config_bootstrap_v3_LayeredRuntime* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(64, 184), 75, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__LayeredRuntime_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_layered_runtime(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(64, 184), 75, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_header_prefix(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(156, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_header_prefix(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {18, UPB_SIZE(156, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_stats_server_version_override(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 192), 76, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_bootstrap_v3_Bootstrap_stats_server_version_override(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {19, UPB_SIZE(68, 192), 76, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_stats_server_version_override(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 192), 76, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_use_tcp_for_dns_lookups(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_use_tcp_for_dns_lookups(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_bootstrap_extensions(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_config_bootstrap_v3_Bootstrap_bootstrap_extensions(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_TypedExtensionConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_bootstrap_extensions_upb_array(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_bootstrap_extensions_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_config_sources(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* const* envoy_config_bootstrap_v3_Bootstrap_config_sources(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_ConfigSource* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_config_sources_upb_array(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_config_sources_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_default_config_source(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(80, 216), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_default_config_source(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {23, UPB_SIZE(80, 216), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_default_config_source(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(80, 216), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_default_socket_interface(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(164, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_default_socket_interface(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {24, UPB_SIZE(164, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_certificate_provider_instances(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_size(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_get(const envoy_config_bootstrap_v3_Bootstrap* msg, upb_StringView key, struct envoy_config_core_v3_TypedExtensionConfig** val) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_next(const envoy_config_bootstrap_v3_Bootstrap* msg, upb_StringView* key, const struct envoy_config_core_v3_TypedExtensionConfig** val,
                           size_t* iter) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_upb_map(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_mutable_upb_map(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* a) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct envoy_config_core_v3_TypedExtensionConfig*), a);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_node_context_params(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_bootstrap_v3_Bootstrap_node_context_params(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_node_context_params_upb_array(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_node_context_params_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_watchdogs(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(92, 240), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Watchdogs* envoy_config_bootstrap_v3_Bootstrap_watchdogs(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Watchdogs* default_val = NULL;
  const envoy_config_bootstrap_v3_Watchdogs* ret;
  const upb_MiniTableField field = {27, UPB_SIZE(92, 240), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdogs_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_watchdogs(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(92, 240), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_fatal_actions(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_FatalAction* const* envoy_config_bootstrap_v3_Bootstrap_fatal_actions(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__FatalAction_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_bootstrap_v3_FatalAction* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_fatal_actions_upb_array(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__FatalAction_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_fatal_actions_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__FatalAction_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_stats_flush_on_admin(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_stats_flush_on_admin(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_stats_flush_on_admin(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_dns_resolution_config(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(100, 256), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DnsResolutionConfig* envoy_config_bootstrap_v3_Bootstrap_dns_resolution_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_DnsResolutionConfig* default_val = NULL;
  const struct envoy_config_core_v3_DnsResolutionConfig* ret;
  const upb_MiniTableField field = {30, UPB_SIZE(100, 256), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DnsResolutionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_dns_resolution_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(100, 256), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_typed_dns_resolver_config(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(104, 264), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_typed_dns_resolver_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {31, UPB_SIZE(104, 264), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_typed_dns_resolver_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(104, 264), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_inline_headers(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_CustomInlineHeader* const* envoy_config_bootstrap_v3_Bootstrap_inline_headers(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_bootstrap_v3_CustomInlineHeader* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_inline_headers_upb_array(const envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  const upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_inline_headers_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_perf_tracing_file_path(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(172, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_perf_tracing_file_path(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {33, UPB_SIZE(172, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_default_regex_engine(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(112, 280), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_default_regex_engine(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {34, UPB_SIZE(112, 280), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_default_regex_engine(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(112, 280), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_xds_delegate_extension(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(116, 288), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_xds_delegate_extension(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {35, UPB_SIZE(116, 288), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_xds_delegate_extension(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(116, 288), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_xds_config_tracker_extension(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(120, 296), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_xds_config_tracker_extension(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {36, UPB_SIZE(120, 296), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_xds_config_tracker_extension(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(120, 296), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_listener_manager(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {37, UPB_SIZE(124, 304), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_listener_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {37, UPB_SIZE(124, 304), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_listener_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {37, UPB_SIZE(124, 304), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_application_log_config(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(128, 312), 85, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* envoy_config_bootstrap_v3_Bootstrap_application_log_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* default_val = NULL;
  const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* ret;
  const upb_MiniTableField field = {38, UPB_SIZE(128, 312), 85, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_application_log_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(128, 312), 85, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_deferred_stat_options(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {39, UPB_SIZE(132, 320), 86, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* envoy_config_bootstrap_v3_Bootstrap_deferred_stat_options(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* default_val = NULL;
  const envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* ret;
  const upb_MiniTableField field = {39, UPB_SIZE(132, 320), 86, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_deferred_stat_options(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {39, UPB_SIZE(132, 320), 86, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_grpc_async_client_manager_config(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(136, 328), 87, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* envoy_config_bootstrap_v3_Bootstrap_grpc_async_client_manager_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* default_val = NULL;
  const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* ret;
  const upb_MiniTableField field = {40, UPB_SIZE(136, 328), 87, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_grpc_async_client_manager_config(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(136, 328), 87, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_clear_memory_allocator_manager(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(140, 336), 88, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_MemoryAllocatorManager* envoy_config_bootstrap_v3_Bootstrap_memory_allocator_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const envoy_config_bootstrap_v3_MemoryAllocatorManager* default_val = NULL;
  const envoy_config_bootstrap_v3_MemoryAllocatorManager* ret;
  const upb_MiniTableField field = {41, UPB_SIZE(140, 336), 88, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_has_memory_allocator_manager(const envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(140, 336), 88, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_node(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_Node* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 88), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Node* envoy_config_bootstrap_v3_Bootstrap_mutable_node(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Node* sub = (struct envoy_config_core_v3_Node*)envoy_config_bootstrap_v3_Bootstrap_node(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Node*)_upb_Message_New(&envoy__config__core__v3__Node_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_node(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_static_resources(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Bootstrap_StaticResources* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 96), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap_StaticResources* envoy_config_bootstrap_v3_Bootstrap_mutable_static_resources(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap_StaticResources* sub = (struct envoy_config_bootstrap_v3_Bootstrap_StaticResources*)envoy_config_bootstrap_v3_Bootstrap_static_resources(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap_StaticResources*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_static_resources(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_dynamic_resources(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Bootstrap_DynamicResources* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 104), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap_DynamicResources* envoy_config_bootstrap_v3_Bootstrap_mutable_dynamic_resources(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap_DynamicResources* sub = (struct envoy_config_bootstrap_v3_Bootstrap_DynamicResources*)envoy_config_bootstrap_v3_Bootstrap_dynamic_resources(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap_DynamicResources*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_dynamic_resources(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_cluster_manager(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_ClusterManager* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 112), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__ClusterManager_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_ClusterManager* envoy_config_bootstrap_v3_Bootstrap_mutable_cluster_manager(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_ClusterManager* sub = (struct envoy_config_bootstrap_v3_ClusterManager*)envoy_config_bootstrap_v3_Bootstrap_cluster_manager(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_ClusterManager*)_upb_Message_New(&envoy__config__bootstrap__v3__ClusterManager_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_cluster_manager(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_flags_path(envoy_config_bootstrap_v3_Bootstrap *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(148, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_metrics_v3_StatsSink** envoy_config_bootstrap_v3_Bootstrap_mutable_stats_sinks(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsSink_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_metrics_v3_StatsSink**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_metrics_v3_StatsSink** envoy_config_bootstrap_v3_Bootstrap_resize_stats_sinks(envoy_config_bootstrap_v3_Bootstrap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_metrics_v3_StatsSink**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_metrics_v3_StatsSink* envoy_config_bootstrap_v3_Bootstrap_add_stats_sinks(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(32, 120), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsSink_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_metrics_v3_StatsSink* sub = (struct envoy_config_metrics_v3_StatsSink*)_upb_Message_New(&envoy__config__metrics__v3__StatsSink_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_stats_flush_interval(envoy_config_bootstrap_v3_Bootstrap *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 128), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Bootstrap_mutable_stats_flush_interval(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Bootstrap_stats_flush_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_stats_flush_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_watchdog(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Watchdog* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 136), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Bootstrap_mutable_watchdog(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Watchdog* sub = (struct envoy_config_bootstrap_v3_Watchdog*)envoy_config_bootstrap_v3_Bootstrap_watchdog(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Watchdog*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdog_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_watchdog(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_tracing(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_trace_v3_Tracing* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 144), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__Tracing_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_trace_v3_Tracing* envoy_config_bootstrap_v3_Bootstrap_mutable_tracing(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_trace_v3_Tracing* sub = (struct envoy_config_trace_v3_Tracing*)envoy_config_bootstrap_v3_Bootstrap_tracing(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_trace_v3_Tracing*)_upb_Message_New(&envoy__config__trace__v3__Tracing_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_tracing(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_admin(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Admin* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 152), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Admin_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Admin* envoy_config_bootstrap_v3_Bootstrap_mutable_admin(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Admin* sub = (struct envoy_config_bootstrap_v3_Admin*)envoy_config_bootstrap_v3_Bootstrap_admin(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Admin*)_upb_Message_New(&envoy__config__bootstrap__v3__Admin_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_admin(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_stats_config(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_metrics_v3_StatsConfig* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 160), 72, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_metrics_v3_StatsConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_stats_config(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_metrics_v3_StatsConfig* sub = (struct envoy_config_metrics_v3_StatsConfig*)envoy_config_bootstrap_v3_Bootstrap_stats_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_metrics_v3_StatsConfig*)_upb_Message_New(&envoy__config__metrics__v3__StatsConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_stats_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_hds_config(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_ApiConfigSource* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(56, 168), 73, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ApiConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ApiConfigSource* envoy_config_bootstrap_v3_Bootstrap_mutable_hds_config(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ApiConfigSource* sub = (struct envoy_config_core_v3_ApiConfigSource*)envoy_config_bootstrap_v3_Bootstrap_hds_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ApiConfigSource*)_upb_Message_New(&envoy__config__core__v3__ApiConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_hds_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_overload_manager(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_overload_v3_OverloadManager* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(60, 176), 74, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__overload__v3__OverloadManager_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_overload_v3_OverloadManager* envoy_config_bootstrap_v3_Bootstrap_mutable_overload_manager(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_overload_v3_OverloadManager* sub = (struct envoy_config_overload_v3_OverloadManager*)envoy_config_bootstrap_v3_Bootstrap_overload_manager(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_overload_v3_OverloadManager*)_upb_Message_New(&envoy__config__overload__v3__OverloadManager_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_overload_manager(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_enable_dispatcher_stats(envoy_config_bootstrap_v3_Bootstrap *msg, bool value) {
  const upb_MiniTableField field = {16, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_layered_runtime(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_LayeredRuntime* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(64, 184), 75, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__LayeredRuntime_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_LayeredRuntime* envoy_config_bootstrap_v3_Bootstrap_mutable_layered_runtime(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_LayeredRuntime* sub = (struct envoy_config_bootstrap_v3_LayeredRuntime*)envoy_config_bootstrap_v3_Bootstrap_layered_runtime(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_LayeredRuntime*)_upb_Message_New(&envoy__config__bootstrap__v3__LayeredRuntime_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_layered_runtime(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_header_prefix(envoy_config_bootstrap_v3_Bootstrap *msg, upb_StringView value) {
  const upb_MiniTableField field = {18, UPB_SIZE(156, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_stats_server_version_override(envoy_config_bootstrap_v3_Bootstrap *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 192), 76, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_bootstrap_v3_Bootstrap_mutable_stats_server_version_override(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_bootstrap_v3_Bootstrap_stats_server_version_override(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_stats_server_version_override(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_use_tcp_for_dns_lookups(envoy_config_bootstrap_v3_Bootstrap *msg, bool value) {
  const upb_MiniTableField field = {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_bootstrap_v3_Bootstrap_mutable_bootstrap_extensions(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_bootstrap_v3_Bootstrap_resize_bootstrap_extensions(envoy_config_bootstrap_v3_Bootstrap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_add_bootstrap_extensions(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  upb_MiniTableField field = {21, UPB_SIZE(72, 200), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource** envoy_config_bootstrap_v3_Bootstrap_mutable_config_sources(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_ConfigSource**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource** envoy_config_bootstrap_v3_Bootstrap_resize_config_sources(envoy_config_bootstrap_v3_Bootstrap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_ConfigSource**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_add_config_sources(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  upb_MiniTableField field = {22, UPB_SIZE(76, 208), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_default_config_source(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {23, UPB_SIZE(80, 216), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_mutable_default_config_source(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_config_bootstrap_v3_Bootstrap_default_config_source(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_default_config_source(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_default_socket_interface(envoy_config_bootstrap_v3_Bootstrap *msg, upb_StringView value) {
  const upb_MiniTableField field = {24, UPB_SIZE(164, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_clear(envoy_config_bootstrap_v3_Bootstrap* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_set(envoy_config_bootstrap_v3_Bootstrap* msg, upb_StringView key, struct envoy_config_core_v3_TypedExtensionConfig* val, upb_Arena* a) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__CertificateProviderInstancesEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_certificate_provider_instances_delete(envoy_config_bootstrap_v3_Bootstrap* msg, upb_StringView key) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 224), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE upb_StringView* envoy_config_bootstrap_v3_Bootstrap_mutable_node_context_params(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_bootstrap_v3_Bootstrap_resize_node_context_params(envoy_config_bootstrap_v3_Bootstrap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_add_node_context_params(envoy_config_bootstrap_v3_Bootstrap* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {26, UPB_SIZE(88, 232), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_watchdogs(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Watchdogs* value) {
  const upb_MiniTableField field = {27, UPB_SIZE(92, 240), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdogs_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Watchdogs* envoy_config_bootstrap_v3_Bootstrap_mutable_watchdogs(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Watchdogs* sub = (struct envoy_config_bootstrap_v3_Watchdogs*)envoy_config_bootstrap_v3_Bootstrap_watchdogs(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Watchdogs*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdogs_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_watchdogs(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_bootstrap_v3_FatalAction** envoy_config_bootstrap_v3_Bootstrap_mutable_fatal_actions(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__FatalAction_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_bootstrap_v3_FatalAction**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_bootstrap_v3_FatalAction** envoy_config_bootstrap_v3_Bootstrap_resize_fatal_actions(envoy_config_bootstrap_v3_Bootstrap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_FatalAction**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_bootstrap_v3_FatalAction* envoy_config_bootstrap_v3_Bootstrap_add_fatal_actions(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  upb_MiniTableField field = {28, UPB_SIZE(96, 248), 0, 19, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__FatalAction_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_bootstrap_v3_FatalAction* sub = (struct envoy_config_bootstrap_v3_FatalAction*)_upb_Message_New(&envoy__config__bootstrap__v3__FatalAction_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_stats_flush_on_admin(envoy_config_bootstrap_v3_Bootstrap *msg, bool value) {
  const upb_MiniTableField field = {29, 14, UPB_SIZE(-145, -17), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_dns_resolution_config(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_DnsResolutionConfig* value) {
  const upb_MiniTableField field = {30, UPB_SIZE(100, 256), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DnsResolutionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DnsResolutionConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_dns_resolution_config(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DnsResolutionConfig* sub = (struct envoy_config_core_v3_DnsResolutionConfig*)envoy_config_bootstrap_v3_Bootstrap_dns_resolution_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DnsResolutionConfig*)_upb_Message_New(&envoy__config__core__v3__DnsResolutionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_dns_resolution_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_typed_dns_resolver_config(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {31, UPB_SIZE(104, 264), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_typed_dns_resolver_config(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_Bootstrap_typed_dns_resolver_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_typed_dns_resolver_config(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_bootstrap_v3_CustomInlineHeader** envoy_config_bootstrap_v3_Bootstrap_mutable_inline_headers(envoy_config_bootstrap_v3_Bootstrap* msg, size_t* size) {
  upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_bootstrap_v3_CustomInlineHeader**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_bootstrap_v3_CustomInlineHeader** envoy_config_bootstrap_v3_Bootstrap_resize_inline_headers(envoy_config_bootstrap_v3_Bootstrap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_CustomInlineHeader**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_bootstrap_v3_CustomInlineHeader* envoy_config_bootstrap_v3_Bootstrap_add_inline_headers(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  upb_MiniTableField field = {32, UPB_SIZE(108, 272), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_bootstrap_v3_CustomInlineHeader* sub = (struct envoy_config_bootstrap_v3_CustomInlineHeader*)_upb_Message_New(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_perf_tracing_file_path(envoy_config_bootstrap_v3_Bootstrap *msg, upb_StringView value) {
  const upb_MiniTableField field = {33, UPB_SIZE(172, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_default_regex_engine(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {34, UPB_SIZE(112, 280), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_default_regex_engine(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_Bootstrap_default_regex_engine(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_default_regex_engine(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_xds_delegate_extension(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {35, UPB_SIZE(116, 288), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_xds_delegate_extension(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_Bootstrap_xds_delegate_extension(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_xds_delegate_extension(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_xds_config_tracker_extension(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {36, UPB_SIZE(120, 296), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_xds_config_tracker_extension(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_Bootstrap_xds_config_tracker_extension(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_xds_config_tracker_extension(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_listener_manager(envoy_config_bootstrap_v3_Bootstrap *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {37, UPB_SIZE(124, 304), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_listener_manager(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_Bootstrap_listener_manager(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_listener_manager(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_application_log_config(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* value) {
  const upb_MiniTableField field = {38, UPB_SIZE(128, 312), 85, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_application_log_config(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* sub = (struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig*)envoy_config_bootstrap_v3_Bootstrap_application_log_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_application_log_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_deferred_stat_options(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* value) {
  const upb_MiniTableField field = {39, UPB_SIZE(132, 320), 86, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* envoy_config_bootstrap_v3_Bootstrap_mutable_deferred_stat_options(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* sub = (struct envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions*)envoy_config_bootstrap_v3_Bootstrap_deferred_stat_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_deferred_stat_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_grpc_async_client_manager_config(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* value) {
  const upb_MiniTableField field = {40, UPB_SIZE(136, 328), 87, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* envoy_config_bootstrap_v3_Bootstrap_mutable_grpc_async_client_manager_config(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* sub = (struct envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig*)envoy_config_bootstrap_v3_Bootstrap_grpc_async_client_manager_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_grpc_async_client_manager_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_set_memory_allocator_manager(envoy_config_bootstrap_v3_Bootstrap *msg, envoy_config_bootstrap_v3_MemoryAllocatorManager* value) {
  const upb_MiniTableField field = {41, UPB_SIZE(140, 336), 88, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_MemoryAllocatorManager* envoy_config_bootstrap_v3_Bootstrap_mutable_memory_allocator_manager(envoy_config_bootstrap_v3_Bootstrap* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_MemoryAllocatorManager* sub = (struct envoy_config_bootstrap_v3_MemoryAllocatorManager*)envoy_config_bootstrap_v3_Bootstrap_memory_allocator_manager(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_MemoryAllocatorManager*)_upb_Message_New(&envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_set_memory_allocator_manager(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_StaticResources* envoy_config_bootstrap_v3_Bootstrap_StaticResources_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap_StaticResources*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_StaticResources* envoy_config_bootstrap_v3_Bootstrap_StaticResources_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_StaticResources* ret = envoy_config_bootstrap_v3_Bootstrap_StaticResources_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_StaticResources* envoy_config_bootstrap_v3_Bootstrap_StaticResources_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_StaticResources* ret = envoy_config_bootstrap_v3_Bootstrap_StaticResources_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_StaticResources_serialize(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_StaticResources_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__StaticResources_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_StaticResources_clear_listeners(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_Listener* const* envoy_config_bootstrap_v3_Bootstrap_StaticResources_listeners(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_listener_v3_Listener* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_StaticResources_listeners_upb_array(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_StaticResources_listeners_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_StaticResources_clear_clusters(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_cluster_v3_Cluster* const* envoy_config_bootstrap_v3_Bootstrap_StaticResources_clusters(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_cluster_v3_Cluster* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_StaticResources_clusters_upb_array(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_StaticResources_clusters_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_StaticResources_clear_secrets(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_transport_sockets_tls_v3_Secret* const* envoy_config_bootstrap_v3_Bootstrap_StaticResources_secrets(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_extensions_transport_sockets_tls_v3_Secret* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Bootstrap_StaticResources_secrets_upb_array(const envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Bootstrap_StaticResources_secrets_mutable_upb_array(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct envoy_config_listener_v3_Listener** envoy_config_bootstrap_v3_Bootstrap_StaticResources_mutable_listeners(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_listener_v3_Listener**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_listener_v3_Listener** envoy_config_bootstrap_v3_Bootstrap_StaticResources_resize_listeners(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_listener_v3_Listener**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_listener_v3_Listener* envoy_config_bootstrap_v3_Bootstrap_StaticResources_add_listeners(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_listener_v3_Listener* sub = (struct envoy_config_listener_v3_Listener*)_upb_Message_New(&envoy__config__listener__v3__Listener_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster** envoy_config_bootstrap_v3_Bootstrap_StaticResources_mutable_clusters(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_cluster_v3_Cluster**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster** envoy_config_bootstrap_v3_Bootstrap_StaticResources_resize_clusters(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_cluster_v3_Cluster**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster* envoy_config_bootstrap_v3_Bootstrap_StaticResources_add_clusters(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_Cluster* sub = (struct envoy_config_cluster_v3_Cluster*)_upb_Message_New(&envoy__config__cluster__v3__Cluster_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_Secret** envoy_config_bootstrap_v3_Bootstrap_StaticResources_mutable_secrets(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_extensions_transport_sockets_tls_v3_Secret**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_Secret** envoy_config_bootstrap_v3_Bootstrap_StaticResources_resize_secrets(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_extensions_transport_sockets_tls_v3_Secret**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_transport_sockets_tls_v3_Secret* envoy_config_bootstrap_v3_Bootstrap_StaticResources_add_secrets(envoy_config_bootstrap_v3_Bootstrap_StaticResources* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_transport_sockets_tls_v3_Secret* sub = (struct envoy_extensions_transport_sockets_tls_v3_Secret*)_upb_Message_New(&envoy__extensions__transport_0sockets__tls__v3__Secret_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_DynamicResources* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap_DynamicResources*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_DynamicResources* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_DynamicResources* ret = envoy_config_bootstrap_v3_Bootstrap_DynamicResources_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_DynamicResources* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_DynamicResources* ret = envoy_config_bootstrap_v3_Bootstrap_DynamicResources_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_serialize(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__DynamicResources_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_clear_lds_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_lds_config(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_DynamicResources_has_lds_config(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_clear_cds_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_cds_config(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_DynamicResources_has_cds_config(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_clear_ads_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ApiConfigSource* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_ads_config(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const struct envoy_config_core_v3_ApiConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ApiConfigSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ApiConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_DynamicResources_has_ads_config(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_clear_lds_resources_locator(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_DynamicResources_lds_resources_locator(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_clear_cds_resources_locator(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_DynamicResources_cds_resources_locator(const envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_lds_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_mutable_lds_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_config_bootstrap_v3_Bootstrap_DynamicResources_lds_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_lds_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_cds_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_mutable_cds_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_config_bootstrap_v3_Bootstrap_DynamicResources_cds_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_cds_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_ads_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources *msg, struct envoy_config_core_v3_ApiConfigSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ApiConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ApiConfigSource* envoy_config_bootstrap_v3_Bootstrap_DynamicResources_mutable_ads_config(envoy_config_bootstrap_v3_Bootstrap_DynamicResources* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ApiConfigSource* sub = (struct envoy_config_core_v3_ApiConfigSource*)envoy_config_bootstrap_v3_Bootstrap_DynamicResources_ads_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ApiConfigSource*)_upb_Message_New(&envoy__config__core__v3__ApiConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_ads_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_lds_resources_locator(envoy_config_bootstrap_v3_Bootstrap_DynamicResources *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DynamicResources_set_cds_resources_locator(envoy_config_bootstrap_v3_Bootstrap_DynamicResources *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* ret = envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* ret = envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_serialize(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_clear_log_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_log_format(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* msg) {
  const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* default_val = NULL;
  const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_has_log_format(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_set_log_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig *msg, envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_mutable_log_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* sub = (struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat*)envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_log_format(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_set_log_format(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* ret = envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* ret = envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_serialize(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_json_format = 1,
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_text_format = 2,
  envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_NOT_SET = 0
} envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_oneofcases;
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_oneofcases envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_case(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_log_format_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_clear_log_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__ApplicationLogConfig__LogFormat_msg_init, &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_clear_json_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_json_format(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_has_json_format(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_clear_text_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_text_format(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_has_text_format(const envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_set_json_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_mutable_json_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_json_format(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_set_json_format(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_set_text_format(envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* ret = envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* ret = envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_serialize(const envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__DeferredStatOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_clear_enable_deferred_creation_stats(envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_enable_deferred_creation_stats(const envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_set_enable_deferred_creation_stats(envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* ret = envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* ret = envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_serialize(const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_serialize_ex(const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Bootstrap__GrpcAsyncClientManagerConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_clear_max_cached_entry_idle_duration(envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_max_cached_entry_idle_duration(const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_has_max_cached_entry_idle_duration(const envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_set_max_cached_entry_idle_duration(envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_mutable_max_cached_entry_idle_duration(envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_max_cached_entry_idle_duration(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_set_max_cached_entry_idle_duration(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Admin* envoy_config_bootstrap_v3_Admin_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Admin*)_upb_Message_New(&envoy__config__bootstrap__v3__Admin_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Admin* envoy_config_bootstrap_v3_Admin_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Admin* ret = envoy_config_bootstrap_v3_Admin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Admin_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Admin* envoy_config_bootstrap_v3_Admin_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Admin* ret = envoy_config_bootstrap_v3_Admin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Admin_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Admin_serialize(const envoy_config_bootstrap_v3_Admin* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Admin_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Admin_serialize_ex(const envoy_config_bootstrap_v3_Admin* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Admin_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_clear_access_log_path(envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Admin_access_log_path(const envoy_config_bootstrap_v3_Admin* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_clear_profile_path(envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Admin_profile_path(const envoy_config_bootstrap_v3_Admin* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_clear_address(envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_config_bootstrap_v3_Admin_address(const envoy_config_bootstrap_v3_Admin* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Admin_has_address(const envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_clear_socket_options(envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SocketOption* const* envoy_config_bootstrap_v3_Admin_socket_options(const envoy_config_bootstrap_v3_Admin* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_SocketOption* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Admin_socket_options_upb_array(const envoy_config_bootstrap_v3_Admin* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Admin_socket_options_mutable_upb_array(envoy_config_bootstrap_v3_Admin* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_clear_access_log(envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_accesslog_v3_AccessLog* const* envoy_config_bootstrap_v3_Admin_access_log(const envoy_config_bootstrap_v3_Admin* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_accesslog_v3_AccessLog* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Admin_access_log_upb_array(const envoy_config_bootstrap_v3_Admin* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Admin_access_log_mutable_upb_array(envoy_config_bootstrap_v3_Admin* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_clear_ignore_global_conn_limit(envoy_config_bootstrap_v3_Admin* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_Admin_ignore_global_conn_limit(const envoy_config_bootstrap_v3_Admin* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_Admin_set_access_log_path(envoy_config_bootstrap_v3_Admin *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_set_profile_path(envoy_config_bootstrap_v3_Admin *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_set_address(envoy_config_bootstrap_v3_Admin *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_bootstrap_v3_Admin_mutable_address(envoy_config_bootstrap_v3_Admin* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_config_bootstrap_v3_Admin_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Admin_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_SocketOption** envoy_config_bootstrap_v3_Admin_mutable_socket_options(envoy_config_bootstrap_v3_Admin* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_SocketOption**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_SocketOption** envoy_config_bootstrap_v3_Admin_resize_socket_options(envoy_config_bootstrap_v3_Admin* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_SocketOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_SocketOption* envoy_config_bootstrap_v3_Admin_add_socket_options(envoy_config_bootstrap_v3_Admin* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_SocketOption* sub = (struct envoy_config_core_v3_SocketOption*)_upb_Message_New(&envoy__config__core__v3__SocketOption_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog** envoy_config_bootstrap_v3_Admin_mutable_access_log(envoy_config_bootstrap_v3_Admin* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_accesslog_v3_AccessLog**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog** envoy_config_bootstrap_v3_Admin_resize_access_log(envoy_config_bootstrap_v3_Admin* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_accesslog_v3_AccessLog**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog* envoy_config_bootstrap_v3_Admin_add_access_log(envoy_config_bootstrap_v3_Admin* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_accesslog_v3_AccessLog* sub = (struct envoy_config_accesslog_v3_AccessLog*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLog_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Admin_set_ignore_global_conn_limit(envoy_config_bootstrap_v3_Admin *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_ClusterManager* envoy_config_bootstrap_v3_ClusterManager_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_ClusterManager*)_upb_Message_New(&envoy__config__bootstrap__v3__ClusterManager_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_ClusterManager* envoy_config_bootstrap_v3_ClusterManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_ClusterManager* ret = envoy_config_bootstrap_v3_ClusterManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__ClusterManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_ClusterManager* envoy_config_bootstrap_v3_ClusterManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_ClusterManager* ret = envoy_config_bootstrap_v3_ClusterManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__ClusterManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_ClusterManager_serialize(const envoy_config_bootstrap_v3_ClusterManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__ClusterManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_ClusterManager_serialize_ex(const envoy_config_bootstrap_v3_ClusterManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__ClusterManager_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_clear_local_cluster_name(envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_ClusterManager_local_cluster_name(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_clear_outlier_detection(envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* envoy_config_bootstrap_v3_ClusterManager_outlier_detection(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* default_val = NULL;
  const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_ClusterManager_has_outlier_detection(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_clear_upstream_bind_config(envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_BindConfig* envoy_config_bootstrap_v3_ClusterManager_upstream_bind_config(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  const struct envoy_config_core_v3_BindConfig* default_val = NULL;
  const struct envoy_config_core_v3_BindConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BindConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_ClusterManager_has_upstream_bind_config(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_clear_load_stats_config(envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ApiConfigSource* envoy_config_bootstrap_v3_ClusterManager_load_stats_config(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  const struct envoy_config_core_v3_ApiConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ApiConfigSource* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ApiConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_ClusterManager_has_load_stats_config(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_clear_enable_deferred_cluster_creation(envoy_config_bootstrap_v3_ClusterManager* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_ClusterManager_enable_deferred_cluster_creation(const envoy_config_bootstrap_v3_ClusterManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_set_local_cluster_name(envoy_config_bootstrap_v3_ClusterManager *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_set_outlier_detection(envoy_config_bootstrap_v3_ClusterManager *msg, envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* envoy_config_bootstrap_v3_ClusterManager_mutable_outlier_detection(envoy_config_bootstrap_v3_ClusterManager* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* sub = (struct envoy_config_bootstrap_v3_ClusterManager_OutlierDetection*)envoy_config_bootstrap_v3_ClusterManager_outlier_detection(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_ClusterManager_OutlierDetection*)_upb_Message_New(&envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_ClusterManager_set_outlier_detection(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_set_upstream_bind_config(envoy_config_bootstrap_v3_ClusterManager *msg, struct envoy_config_core_v3_BindConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BindConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_BindConfig* envoy_config_bootstrap_v3_ClusterManager_mutable_upstream_bind_config(envoy_config_bootstrap_v3_ClusterManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_BindConfig* sub = (struct envoy_config_core_v3_BindConfig*)envoy_config_bootstrap_v3_ClusterManager_upstream_bind_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_BindConfig*)_upb_Message_New(&envoy__config__core__v3__BindConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_ClusterManager_set_upstream_bind_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_set_load_stats_config(envoy_config_bootstrap_v3_ClusterManager *msg, struct envoy_config_core_v3_ApiConfigSource* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ApiConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ApiConfigSource* envoy_config_bootstrap_v3_ClusterManager_mutable_load_stats_config(envoy_config_bootstrap_v3_ClusterManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ApiConfigSource* sub = (struct envoy_config_core_v3_ApiConfigSource*)envoy_config_bootstrap_v3_ClusterManager_load_stats_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ApiConfigSource*)_upb_Message_New(&envoy__config__core__v3__ApiConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_ClusterManager_set_load_stats_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_set_enable_deferred_cluster_creation(envoy_config_bootstrap_v3_ClusterManager *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_ClusterManager_OutlierDetection*)_upb_Message_New(&envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* ret = envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* ret = envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_serialize(const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_serialize_ex(const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__ClusterManager__OutlierDetection_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_clear_event_log_path(envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_event_log_path(const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_clear_event_service(envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_EventServiceConfig* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_event_service(const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg) {
  const struct envoy_config_core_v3_EventServiceConfig* default_val = NULL;
  const struct envoy_config_core_v3_EventServiceConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__EventServiceConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_has_event_service(const envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_set_event_log_path(envoy_config_bootstrap_v3_ClusterManager_OutlierDetection *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_set_event_service(envoy_config_bootstrap_v3_ClusterManager_OutlierDetection *msg, struct envoy_config_core_v3_EventServiceConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__EventServiceConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_EventServiceConfig* envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_mutable_event_service(envoy_config_bootstrap_v3_ClusterManager_OutlierDetection* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_EventServiceConfig* sub = (struct envoy_config_core_v3_EventServiceConfig*)envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_event_service(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_EventServiceConfig*)_upb_Message_New(&envoy__config__core__v3__EventServiceConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_set_event_service(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Watchdogs* envoy_config_bootstrap_v3_Watchdogs_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Watchdogs*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdogs_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdogs* envoy_config_bootstrap_v3_Watchdogs_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Watchdogs* ret = envoy_config_bootstrap_v3_Watchdogs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Watchdogs_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdogs* envoy_config_bootstrap_v3_Watchdogs_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Watchdogs* ret = envoy_config_bootstrap_v3_Watchdogs_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Watchdogs_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Watchdogs_serialize(const envoy_config_bootstrap_v3_Watchdogs* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Watchdogs_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Watchdogs_serialize_ex(const envoy_config_bootstrap_v3_Watchdogs* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Watchdogs_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdogs_clear_main_thread_watchdog(envoy_config_bootstrap_v3_Watchdogs* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdogs_main_thread_watchdog(const envoy_config_bootstrap_v3_Watchdogs* msg) {
  const envoy_config_bootstrap_v3_Watchdog* default_val = NULL;
  const envoy_config_bootstrap_v3_Watchdog* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdogs_has_main_thread_watchdog(const envoy_config_bootstrap_v3_Watchdogs* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdogs_clear_worker_watchdog(envoy_config_bootstrap_v3_Watchdogs* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdogs_worker_watchdog(const envoy_config_bootstrap_v3_Watchdogs* msg) {
  const envoy_config_bootstrap_v3_Watchdog* default_val = NULL;
  const envoy_config_bootstrap_v3_Watchdog* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdogs_has_worker_watchdog(const envoy_config_bootstrap_v3_Watchdogs* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_Watchdogs_set_main_thread_watchdog(envoy_config_bootstrap_v3_Watchdogs *msg, envoy_config_bootstrap_v3_Watchdog* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdogs_mutable_main_thread_watchdog(envoy_config_bootstrap_v3_Watchdogs* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Watchdog* sub = (struct envoy_config_bootstrap_v3_Watchdog*)envoy_config_bootstrap_v3_Watchdogs_main_thread_watchdog(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Watchdog*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdog_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdogs_set_main_thread_watchdog(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdogs_set_worker_watchdog(envoy_config_bootstrap_v3_Watchdogs *msg, envoy_config_bootstrap_v3_Watchdog* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdogs_mutable_worker_watchdog(envoy_config_bootstrap_v3_Watchdogs* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Watchdog* sub = (struct envoy_config_bootstrap_v3_Watchdog*)envoy_config_bootstrap_v3_Watchdogs_worker_watchdog(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Watchdog*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdog_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdogs_set_worker_watchdog(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdog_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Watchdog*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdog_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdog_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Watchdog* ret = envoy_config_bootstrap_v3_Watchdog_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Watchdog_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdog* envoy_config_bootstrap_v3_Watchdog_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Watchdog* ret = envoy_config_bootstrap_v3_Watchdog_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Watchdog_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Watchdog_serialize(const envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Watchdog_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Watchdog_serialize_ex(const envoy_config_bootstrap_v3_Watchdog* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Watchdog_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_miss_timeout(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_miss_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_has_miss_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_megamiss_timeout(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_megamiss_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_has_megamiss_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_kill_timeout(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_kill_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_has_kill_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_multikill_timeout(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_multikill_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_has_multikill_timeout(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_multikill_threshold(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_bootstrap_v3_Watchdog_multikill_threshold(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_has_multikill_threshold(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_max_kill_timeout_jitter(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_max_kill_timeout_jitter(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_has_max_kill_timeout_jitter(const envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_clear_actions(envoy_config_bootstrap_v3_Watchdog* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* const* envoy_config_bootstrap_v3_Watchdog_actions(const envoy_config_bootstrap_v3_Watchdog* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_Watchdog_actions_upb_array(const envoy_config_bootstrap_v3_Watchdog* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_Watchdog_actions_mutable_upb_array(envoy_config_bootstrap_v3_Watchdog* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_set_miss_timeout(envoy_config_bootstrap_v3_Watchdog *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_mutable_miss_timeout(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Watchdog_miss_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_set_miss_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_set_megamiss_timeout(envoy_config_bootstrap_v3_Watchdog *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_mutable_megamiss_timeout(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Watchdog_megamiss_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_set_megamiss_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_set_kill_timeout(envoy_config_bootstrap_v3_Watchdog *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_mutable_kill_timeout(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Watchdog_kill_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_set_kill_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_set_multikill_timeout(envoy_config_bootstrap_v3_Watchdog *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_mutable_multikill_timeout(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Watchdog_multikill_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_set_multikill_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_set_multikill_threshold(envoy_config_bootstrap_v3_Watchdog *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_bootstrap_v3_Watchdog_mutable_multikill_threshold(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_bootstrap_v3_Watchdog_multikill_threshold(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_set_multikill_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_set_max_kill_timeout_jitter(envoy_config_bootstrap_v3_Watchdog *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 56), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_Watchdog_mutable_max_kill_timeout_jitter(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_Watchdog_max_kill_timeout_jitter(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_set_max_kill_timeout_jitter(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdog_WatchdogAction** envoy_config_bootstrap_v3_Watchdog_mutable_actions(envoy_config_bootstrap_v3_Watchdog* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_bootstrap_v3_Watchdog_WatchdogAction**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdog_WatchdogAction** envoy_config_bootstrap_v3_Watchdog_resize_actions(envoy_config_bootstrap_v3_Watchdog* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_Watchdog_WatchdogAction**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Watchdog_WatchdogAction* envoy_config_bootstrap_v3_Watchdog_add_actions(envoy_config_bootstrap_v3_Watchdog* msg, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_bootstrap_v3_Watchdog_WatchdogAction* sub = (struct envoy_config_bootstrap_v3_Watchdog_WatchdogAction*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Watchdog_WatchdogAction* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Watchdog_WatchdogAction*)_upb_Message_New(&envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdog_WatchdogAction* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction* ret = envoy_config_bootstrap_v3_Watchdog_WatchdogAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Watchdog_WatchdogAction* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Watchdog_WatchdogAction* ret = envoy_config_bootstrap_v3_Watchdog_WatchdogAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_serialize(const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_serialize_ex(const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Watchdog__WatchdogAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_WatchdogAction_clear_config(envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_config(const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Watchdog_WatchdogAction_has_config(const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_WatchdogAction_clear_event(envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_bootstrap_v3_Watchdog_WatchdogAction_event(const envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_WatchdogAction_set_config(envoy_config_bootstrap_v3_Watchdog_WatchdogAction *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_Watchdog_WatchdogAction_mutable_config(envoy_config_bootstrap_v3_Watchdog_WatchdogAction* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_Watchdog_WatchdogAction_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Watchdog_WatchdogAction_set_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_Watchdog_WatchdogAction_set_event(envoy_config_bootstrap_v3_Watchdog_WatchdogAction *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_FatalAction* envoy_config_bootstrap_v3_FatalAction_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_FatalAction*)_upb_Message_New(&envoy__config__bootstrap__v3__FatalAction_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_FatalAction* envoy_config_bootstrap_v3_FatalAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_FatalAction* ret = envoy_config_bootstrap_v3_FatalAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__FatalAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_FatalAction* envoy_config_bootstrap_v3_FatalAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_FatalAction* ret = envoy_config_bootstrap_v3_FatalAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__FatalAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_FatalAction_serialize(const envoy_config_bootstrap_v3_FatalAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__FatalAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_FatalAction_serialize_ex(const envoy_config_bootstrap_v3_FatalAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__FatalAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_FatalAction_clear_config(envoy_config_bootstrap_v3_FatalAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_FatalAction_config(const envoy_config_bootstrap_v3_FatalAction* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_FatalAction_has_config(const envoy_config_bootstrap_v3_FatalAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_FatalAction_set_config(envoy_config_bootstrap_v3_FatalAction *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_bootstrap_v3_FatalAction_mutable_config(envoy_config_bootstrap_v3_FatalAction* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_bootstrap_v3_FatalAction_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_FatalAction_set_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_Runtime* envoy_config_bootstrap_v3_Runtime_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_Runtime*)_upb_Message_New(&envoy__config__bootstrap__v3__Runtime_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_Runtime* envoy_config_bootstrap_v3_Runtime_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Runtime* ret = envoy_config_bootstrap_v3_Runtime_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Runtime_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_Runtime* envoy_config_bootstrap_v3_Runtime_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_Runtime* ret = envoy_config_bootstrap_v3_Runtime_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__Runtime_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Runtime_serialize(const envoy_config_bootstrap_v3_Runtime* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Runtime_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_Runtime_serialize_ex(const envoy_config_bootstrap_v3_Runtime* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__Runtime_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_clear_symlink_root(envoy_config_bootstrap_v3_Runtime* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Runtime_symlink_root(const envoy_config_bootstrap_v3_Runtime* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_clear_subdirectory(envoy_config_bootstrap_v3_Runtime* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Runtime_subdirectory(const envoy_config_bootstrap_v3_Runtime* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_clear_override_subdirectory(envoy_config_bootstrap_v3_Runtime* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_Runtime_override_subdirectory(const envoy_config_bootstrap_v3_Runtime* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_clear_base(envoy_config_bootstrap_v3_Runtime* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_bootstrap_v3_Runtime_base(const envoy_config_bootstrap_v3_Runtime* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_Runtime_has_base(const envoy_config_bootstrap_v3_Runtime* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_Runtime_set_symlink_root(envoy_config_bootstrap_v3_Runtime *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_set_subdirectory(envoy_config_bootstrap_v3_Runtime *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_set_override_subdirectory(envoy_config_bootstrap_v3_Runtime *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_Runtime_set_base(envoy_config_bootstrap_v3_Runtime *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_bootstrap_v3_Runtime_mutable_base(envoy_config_bootstrap_v3_Runtime* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_bootstrap_v3_Runtime_base(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_Runtime_set_base(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer* envoy_config_bootstrap_v3_RuntimeLayer_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_RuntimeLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer* envoy_config_bootstrap_v3_RuntimeLayer_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer* envoy_config_bootstrap_v3_RuntimeLayer_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_serialize(const envoy_config_bootstrap_v3_RuntimeLayer* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_serialize_ex(const envoy_config_bootstrap_v3_RuntimeLayer* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_static_layer = 2,
  envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_disk_layer = 3,
  envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_admin_layer = 4,
  envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_rtds_layer = 5,
  envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_NOT_SET = 0
} envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_oneofcases;
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_oneofcases envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_case(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_RuntimeLayer_layer_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_clear_layer_specifier(envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer_msg_init, &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_clear_name(envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_RuntimeLayer_name(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_clear_static_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_bootstrap_v3_RuntimeLayer_static_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_RuntimeLayer_has_static_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_clear_disk_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* envoy_config_bootstrap_v3_RuntimeLayer_disk_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* default_val = NULL;
  const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_RuntimeLayer_has_disk_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_clear_admin_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* envoy_config_bootstrap_v3_RuntimeLayer_admin_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* default_val = NULL;
  const envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_RuntimeLayer_has_admin_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_clear_rtds_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* envoy_config_bootstrap_v3_RuntimeLayer_rtds_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* default_val = NULL;
  const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_RuntimeLayer_has_rtds_layer(const envoy_config_bootstrap_v3_RuntimeLayer* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_set_name(envoy_config_bootstrap_v3_RuntimeLayer *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_set_static_layer(envoy_config_bootstrap_v3_RuntimeLayer *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_bootstrap_v3_RuntimeLayer_mutable_static_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_bootstrap_v3_RuntimeLayer_static_layer(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_RuntimeLayer_set_static_layer(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_set_disk_layer(envoy_config_bootstrap_v3_RuntimeLayer *msg, envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* envoy_config_bootstrap_v3_RuntimeLayer_mutable_disk_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* sub = (struct envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer*)envoy_config_bootstrap_v3_RuntimeLayer_disk_layer(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_RuntimeLayer_set_disk_layer(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_set_admin_layer(envoy_config_bootstrap_v3_RuntimeLayer *msg, envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* envoy_config_bootstrap_v3_RuntimeLayer_mutable_admin_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* sub = (struct envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer*)envoy_config_bootstrap_v3_RuntimeLayer_admin_layer(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_RuntimeLayer_set_admin_layer(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_set_rtds_layer(envoy_config_bootstrap_v3_RuntimeLayer *msg, envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* envoy_config_bootstrap_v3_RuntimeLayer_mutable_rtds_layer(envoy_config_bootstrap_v3_RuntimeLayer* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* sub = (struct envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer*)envoy_config_bootstrap_v3_RuntimeLayer_rtds_layer(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_RuntimeLayer_set_rtds_layer(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_serialize(const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_serialize_ex(const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer__DiskLayer_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_clear_symlink_root(envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_symlink_root(const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_clear_append_service_cluster(envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_append_service_cluster(const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_clear_subdirectory(envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_subdirectory(const envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_set_symlink_root(envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_set_append_service_cluster(envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer *msg, bool value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_set_subdirectory(envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_serialize(const envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_serialize_ex(const envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer__AdminLayer_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* ret = envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_serialize(const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_serialize_ex(const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__RuntimeLayer__RtdsLayer_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_clear_name(envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_name(const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_clear_rtds_config(envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_rtds_config(const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_has_rtds_config(const envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_set_name(envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_set_rtds_config(envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_mutable_rtds_config(envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_rtds_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_set_rtds_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_LayeredRuntime* envoy_config_bootstrap_v3_LayeredRuntime_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_LayeredRuntime*)_upb_Message_New(&envoy__config__bootstrap__v3__LayeredRuntime_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_LayeredRuntime* envoy_config_bootstrap_v3_LayeredRuntime_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_LayeredRuntime* ret = envoy_config_bootstrap_v3_LayeredRuntime_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__LayeredRuntime_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_LayeredRuntime* envoy_config_bootstrap_v3_LayeredRuntime_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_LayeredRuntime* ret = envoy_config_bootstrap_v3_LayeredRuntime_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__LayeredRuntime_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_LayeredRuntime_serialize(const envoy_config_bootstrap_v3_LayeredRuntime* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__LayeredRuntime_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_LayeredRuntime_serialize_ex(const envoy_config_bootstrap_v3_LayeredRuntime* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__LayeredRuntime_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_LayeredRuntime_clear_layers(envoy_config_bootstrap_v3_LayeredRuntime* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_bootstrap_v3_RuntimeLayer* const* envoy_config_bootstrap_v3_LayeredRuntime_layers(const envoy_config_bootstrap_v3_LayeredRuntime* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_bootstrap_v3_RuntimeLayer* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_bootstrap_v3_LayeredRuntime_layers_upb_array(const envoy_config_bootstrap_v3_LayeredRuntime* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_bootstrap_v3_LayeredRuntime_layers_mutable_upb_array(envoy_config_bootstrap_v3_LayeredRuntime* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer** envoy_config_bootstrap_v3_LayeredRuntime_mutable_layers(envoy_config_bootstrap_v3_LayeredRuntime* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_bootstrap_v3_RuntimeLayer**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_bootstrap_v3_RuntimeLayer** envoy_config_bootstrap_v3_LayeredRuntime_resize_layers(envoy_config_bootstrap_v3_LayeredRuntime* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_bootstrap_v3_RuntimeLayer**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_bootstrap_v3_RuntimeLayer* envoy_config_bootstrap_v3_LayeredRuntime_add_layers(envoy_config_bootstrap_v3_LayeredRuntime* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_bootstrap_v3_RuntimeLayer* sub = (struct envoy_config_bootstrap_v3_RuntimeLayer*)_upb_Message_New(&envoy__config__bootstrap__v3__RuntimeLayer_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_bootstrap_v3_CustomInlineHeader* envoy_config_bootstrap_v3_CustomInlineHeader_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_CustomInlineHeader*)_upb_Message_New(&envoy__config__bootstrap__v3__CustomInlineHeader_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_CustomInlineHeader* envoy_config_bootstrap_v3_CustomInlineHeader_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_CustomInlineHeader* ret = envoy_config_bootstrap_v3_CustomInlineHeader_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_CustomInlineHeader* envoy_config_bootstrap_v3_CustomInlineHeader_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_CustomInlineHeader* ret = envoy_config_bootstrap_v3_CustomInlineHeader_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_CustomInlineHeader_serialize(const envoy_config_bootstrap_v3_CustomInlineHeader* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_CustomInlineHeader_serialize_ex(const envoy_config_bootstrap_v3_CustomInlineHeader* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__CustomInlineHeader_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_CustomInlineHeader_clear_inline_header_name(envoy_config_bootstrap_v3_CustomInlineHeader* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_bootstrap_v3_CustomInlineHeader_inline_header_name(const envoy_config_bootstrap_v3_CustomInlineHeader* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_CustomInlineHeader_clear_inline_header_type(envoy_config_bootstrap_v3_CustomInlineHeader* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_bootstrap_v3_CustomInlineHeader_inline_header_type(const envoy_config_bootstrap_v3_CustomInlineHeader* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_bootstrap_v3_CustomInlineHeader_set_inline_header_name(envoy_config_bootstrap_v3_CustomInlineHeader *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_CustomInlineHeader_set_inline_header_type(envoy_config_bootstrap_v3_CustomInlineHeader *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_bootstrap_v3_MemoryAllocatorManager* envoy_config_bootstrap_v3_MemoryAllocatorManager_new(upb_Arena* arena) {
  return (envoy_config_bootstrap_v3_MemoryAllocatorManager*)_upb_Message_New(&envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init, arena);
}
UPB_INLINE envoy_config_bootstrap_v3_MemoryAllocatorManager* envoy_config_bootstrap_v3_MemoryAllocatorManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_bootstrap_v3_MemoryAllocatorManager* ret = envoy_config_bootstrap_v3_MemoryAllocatorManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_bootstrap_v3_MemoryAllocatorManager* envoy_config_bootstrap_v3_MemoryAllocatorManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_bootstrap_v3_MemoryAllocatorManager* ret = envoy_config_bootstrap_v3_MemoryAllocatorManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_bootstrap_v3_MemoryAllocatorManager_serialize(const envoy_config_bootstrap_v3_MemoryAllocatorManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_bootstrap_v3_MemoryAllocatorManager_serialize_ex(const envoy_config_bootstrap_v3_MemoryAllocatorManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__bootstrap__v3__MemoryAllocatorManager_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_bootstrap_v3_MemoryAllocatorManager_clear_bytes_to_release(envoy_config_bootstrap_v3_MemoryAllocatorManager* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_config_bootstrap_v3_MemoryAllocatorManager_bytes_to_release(const envoy_config_bootstrap_v3_MemoryAllocatorManager* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_bootstrap_v3_MemoryAllocatorManager_clear_memory_release_interval(envoy_config_bootstrap_v3_MemoryAllocatorManager* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_bootstrap_v3_MemoryAllocatorManager_memory_release_interval(const envoy_config_bootstrap_v3_MemoryAllocatorManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_bootstrap_v3_MemoryAllocatorManager_has_memory_release_interval(const envoy_config_bootstrap_v3_MemoryAllocatorManager* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_bootstrap_v3_MemoryAllocatorManager_set_bytes_to_release(envoy_config_bootstrap_v3_MemoryAllocatorManager *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_bootstrap_v3_MemoryAllocatorManager_set_memory_release_interval(envoy_config_bootstrap_v3_MemoryAllocatorManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_bootstrap_v3_MemoryAllocatorManager_mutable_memory_release_interval(envoy_config_bootstrap_v3_MemoryAllocatorManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_bootstrap_v3_MemoryAllocatorManager_memory_release_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_bootstrap_v3_MemoryAllocatorManager_set_memory_release_interval(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
