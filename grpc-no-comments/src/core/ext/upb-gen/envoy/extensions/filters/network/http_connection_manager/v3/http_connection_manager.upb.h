
#ifndef ENVOY_EXTENSIONS_FILTERS_NETWORK_HTTP_CONNECTION_MANAGER_V3_HTTP_CONNECTION_MANAGER_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_FILTERS_NETWORK_HTTP_CONNECTION_MANAGER_V3_HTTP_CONNECTION_MANAGER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upb_minitable.h"

#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/protocol.upb_minitable.h"
#include "envoy/config/core/v3/substitution_format_string.upb_minitable.h"
#include "envoy/config/route/v3/route.upb_minitable.h"
#include "envoy/config/route/v3/scoped_route.upb_minitable.h"
#include "envoy/config/trace/v3/http_tracer.upb_minitable.h"
#include "envoy/type/http/v3/path_transformation.upb_minitable.h"
#include "envoy/type/tracing/v3/custom_tag.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
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

typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_Rds { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_Rds;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension;
typedef struct envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager;
struct envoy_config_accesslog_v3_AccessLog;
struct envoy_config_accesslog_v3_AccessLogFilter;
struct envoy_config_core_v3_CidrRange;
struct envoy_config_core_v3_ConfigSource;
struct envoy_config_core_v3_DataSource;
struct envoy_config_core_v3_ExtensionConfigSource;
struct envoy_config_core_v3_HeaderValueOption;
struct envoy_config_core_v3_Http1ProtocolOptions;
struct envoy_config_core_v3_Http2ProtocolOptions;
struct envoy_config_core_v3_Http3ProtocolOptions;
struct envoy_config_core_v3_HttpProtocolOptions;
struct envoy_config_core_v3_SchemeHeaderTransformation;
struct envoy_config_core_v3_SubstitutionFormatString;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_route_v3_RouteConfiguration;
struct envoy_config_route_v3_ScopedRouteConfiguration;
struct envoy_config_trace_v3_Tracing_Http;
struct envoy_type_http_v3_PathTransformation;
struct envoy_type_tracing_v3_CustomTag;
struct envoy_type_v3_Percent;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;

typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_AUTO = 0,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HTTP1 = 1,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HTTP2 = 2,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HTTP3 = 3
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_CodecType;

typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SANITIZE = 0,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_FORWARD_ONLY = 1,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_APPEND_FORWARD = 2,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SANITIZE_SET = 3,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ALWAYS_FORWARD_ONLY = 4
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ForwardClientCertDetails;

typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_IMPLEMENTATION_SPECIFIC_DEFAULT = 0,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_KEEP_UNCHANGED = 1,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_REJECT_REQUEST = 2,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UNESCAPE_AND_REDIRECT = 3,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UNESCAPE_AND_FORWARD = 4
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathWithEscapedSlashesAction;

typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_OVERWRITE = 0,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_APPEND_IF_ABSENT = 1,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PASS_THROUGH = 2
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ServerHeaderTransformation;

typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_INGRESS = 0,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_EGRESS = 1
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_OperationName;

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_rds = 3,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_route_config = 4,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_scoped_routes = 31,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_case(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_route_specifier(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, &field);
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_port_mode_strip_any_host_port = 42,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_port_mode_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_port_mode_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_port_mode_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_port_mode_case(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {42, UPB_SIZE(184, 368), UPB_SIZE(-181, -49), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_port_mode_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_strip_port_mode(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {42, UPB_SIZE(184, 368), UPB_SIZE(-181, -49), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_codec_type(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {1, 24, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_codec_type(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 24, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_stat_prefix(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(188, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_stat_prefix(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(188, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_rds(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_Rds* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_rds(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_Rds* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_Rds* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_rds(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_route_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_RouteConfiguration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_route_v3_RouteConfiguration* default_val = NULL;
  const struct envoy_config_route_v3_RouteConfiguration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteConfiguration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_route_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_http_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http_filters(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http_filters_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http_filters_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_add_user_agent(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 112), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_user_agent(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 112), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_add_user_agent(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 112), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_tracing(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 120), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_tracing(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 120), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_tracing(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 120), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_http_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 128), 66, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_core_v3_Http1ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http1ProtocolOptions* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(40, 128), 66, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_http_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 128), 66, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_http2_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 136), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http2_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_core_v3_Http2ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http2ProtocolOptions* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(44, 136), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_http2_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 136), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_server_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(196, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_server_name(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {10, UPB_SIZE(196, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_drain_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 144), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_drain_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(48, 144), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_drain_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 144), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_access_log(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_accesslog_v3_AccessLog* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_use_remote_address(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(56, 160), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_use_remote_address(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(56, 160), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_use_remote_address(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(56, 160), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_generate_request_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(60, 168), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_generate_request_id(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(60, 168), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_generate_request_id(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(60, 168), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_forward_client_cert_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(64, 28), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_forward_client_cert_details(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {16, UPB_SIZE(64, 28), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_set_current_client_cert_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(68, 176), 71, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_current_client_cert_details(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(68, 176), 71, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_set_current_client_cert_details(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(68, 176), 71, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_proxy_100_continue(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {18, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_proxy_100_continue(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {18, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_xff_num_trusted_hops(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(72, 32), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_xff_num_trusted_hops(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {19, UPB_SIZE(72, 32), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_represent_ipv4_remote_address_as_ipv4_mapped_ipv6(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_represent_ipv4_remote_address_as_ipv4_mapped_ipv6(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_skip_xff_append(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {21, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_skip_xff_append(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {21, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_via(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(204, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_via(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {22, UPB_SIZE(204, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_upgrade_configs(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_upgrade_configs(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_upgrade_configs_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_upgrade_configs_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_stream_idle_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(80, 192), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_stream_idle_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {24, UPB_SIZE(80, 192), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_stream_idle_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(80, 192), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_internal_address_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 200), 73, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_internal_address_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* ret;
  const upb_MiniTableField field = {25, UPB_SIZE(84, 200), 73, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_internal_address_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 200), 73, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_delayed_close_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 208), 74, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_delayed_close_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {26, UPB_SIZE(88, 208), 74, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_delayed_close_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 208), 74, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_request_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(92, 216), 75, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_request_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {28, UPB_SIZE(92, 216), 75, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_request_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(92, 216), 75, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_max_request_headers_kb(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(96, 224), 76, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_max_request_headers_kb(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {29, UPB_SIZE(96, 224), 76, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_max_request_headers_kb(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(96, 224), 76, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_normalize_path(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(100, 232), 77, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_normalize_path(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {30, UPB_SIZE(100, 232), 77, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_normalize_path(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(100, 232), 77, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_scoped_routes(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_scoped_routes(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* ret;
  const upb_MiniTableField field = {31, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_scoped_routes(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_preserve_external_request_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {32, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_preserve_external_request_id(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {32, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_merge_slashes(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {33, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_merge_slashes(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {33, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_server_header_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(104, 36), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_server_header_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {34, UPB_SIZE(104, 36), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_common_http_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(108, 240), 78, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HttpProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_common_http_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_core_v3_HttpProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_HttpProtocolOptions* ret;
  const upb_MiniTableField field = {35, UPB_SIZE(108, 240), 78, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_common_http_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(108, 240), 78, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_request_id_extension(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 248), 79, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_request_id_extension(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* ret;
  const upb_MiniTableField field = {36, UPB_SIZE(112, 248), 79, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_request_id_extension(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 248), 79, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_always_set_request_id_in_response(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {37, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_always_set_request_id_in_response(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {37, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_local_reply_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(116, 256), 80, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_local_reply_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* ret;
  const upb_MiniTableField field = {38, UPB_SIZE(116, 256), 80, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_local_reply_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(116, 256), 80, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_strip_matching_host_port(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {39, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_matching_host_port(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {39, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_stream_error_on_invalid_http_message(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(120, 264), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_stream_error_on_invalid_http_message(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {40, UPB_SIZE(120, 264), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_stream_error_on_invalid_http_message(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(120, 264), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_request_headers_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(124, 272), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_request_headers_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {41, UPB_SIZE(124, 272), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_request_headers_timeout(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(124, 272), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_strip_any_host_port(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {42, UPB_SIZE(184, 368), UPB_SIZE(-181, -49), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_any_host_port(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {42, UPB_SIZE(184, 368), UPB_SIZE(-181, -49), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_strip_any_host_port(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {42, UPB_SIZE(184, 368), UPB_SIZE(-181, -49), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_path_normalization_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 280), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_path_normalization_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* ret;
  const upb_MiniTableField field = {43, UPB_SIZE(128, 280), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_path_normalization_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 280), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_http3_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {44, UPB_SIZE(132, 288), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http3_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_core_v3_Http3ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http3ProtocolOptions* ret;
  const upb_MiniTableField field = {44, UPB_SIZE(132, 288), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_http3_protocol_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {44, UPB_SIZE(132, 288), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_path_with_escaped_slashes_action(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {45, UPB_SIZE(136, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_path_with_escaped_slashes_action(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {45, UPB_SIZE(136, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_original_ip_detection_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_original_ip_detection_extensions(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_original_ip_detection_extensions_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_original_ip_detection_extensions_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_strip_trailing_host_dot(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {47, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_strip_trailing_host_dot(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {47, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_scheme_header_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {48, UPB_SIZE(144, 304), 85, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SchemeHeaderTransformation* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_scheme_header_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_core_v3_SchemeHeaderTransformation* default_val = NULL;
  const struct envoy_config_core_v3_SchemeHeaderTransformation* ret;
  const upb_MiniTableField field = {48, UPB_SIZE(144, 304), 85, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SchemeHeaderTransformation_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_scheme_header_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {48, UPB_SIZE(144, 304), 85, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_proxy_status_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {49, UPB_SIZE(148, 312), 86, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_proxy_status_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* ret;
  const upb_MiniTableField field = {49, UPB_SIZE(148, 312), 86, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_proxy_status_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {49, UPB_SIZE(148, 312), 86, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_typed_header_validation_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {50, UPB_SIZE(152, 320), 87, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_typed_header_validation_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {50, UPB_SIZE(152, 320), 87, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_typed_header_validation_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {50, UPB_SIZE(152, 320), 87, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_append_x_forwarded_port(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {51, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_append_x_forwarded_port(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {51, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_early_header_mutation_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_early_header_mutation_extensions(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_early_header_mutation_extensions_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  const upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_early_header_mutation_extensions_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_add_proxy_protocol_connection_state(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {53, UPB_SIZE(160, 336), 88, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_proxy_protocol_connection_state(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {53, UPB_SIZE(160, 336), 88, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_add_proxy_protocol_connection_state(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {53, UPB_SIZE(160, 336), 88, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_access_log_flush_interval(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {54, UPB_SIZE(164, 344), 89, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log_flush_interval(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {54, UPB_SIZE(164, 344), 89, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_access_log_flush_interval(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {54, UPB_SIZE(164, 344), 89, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_flush_access_log_on_new_request(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {55, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_flush_access_log_on_new_request(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {55, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_access_log_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {56, UPB_SIZE(168, 352), 90, 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* ret;
  const upb_MiniTableField field = {56, UPB_SIZE(168, 352), 90, 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_has_access_log_options(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {56, UPB_SIZE(168, 352), 90, 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_append_local_overload(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {57, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_append_local_overload(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {57, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_clear_http1_safe_max_connection_duration(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  const upb_MiniTableField field = {58, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http1_safe_max_connection_duration(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {58, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_codec_type(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, int32_t value) {
  const upb_MiniTableField field = {1, 24, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_stat_prefix(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(188, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_rds(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_Rds* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_Rds* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_rds(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_Rds* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_Rds*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_rds(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_Rds*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_rds(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_route_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_route_v3_RouteConfiguration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteConfiguration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteConfiguration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_route_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteConfiguration* sub = (struct envoy_config_route_v3_RouteConfiguration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_route_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteConfiguration*)_upb_Message_New(&envoy__config__route__v3__RouteConfiguration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_route_config(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_http_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_resize_http_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_http_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 104), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_add_user_agent(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 112), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_add_user_agent(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_user_agent(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_add_user_agent(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_tracing(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 120), 65, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_tracing(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_tracing(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_tracing(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_core_v3_Http1ProtocolOptions* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 128), 66, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_http_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http1ProtocolOptions* sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http1ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http2_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_core_v3_Http2ProtocolOptions* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 136), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_http2_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http2ProtocolOptions* sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http2_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http2ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http2_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_server_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, upb_StringView value) {
  const upb_MiniTableField field = {10, UPB_SIZE(196, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_drain_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 144), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_drain_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_drain_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_drain_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_access_log(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_resize_access_log(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_accesslog_v3_AccessLog**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_access_log(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(52, 152), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_use_remote_address(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(56, 160), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_use_remote_address(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_use_remote_address(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_use_remote_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_generate_request_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(60, 168), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_generate_request_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_generate_request_id(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_generate_request_id(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_forward_client_cert_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, int32_t value) {
  const upb_MiniTableField field = {16, UPB_SIZE(64, 28), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_set_current_client_cert_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(68, 176), 71, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_set_current_client_cert_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_current_client_cert_details(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_set_current_client_cert_details(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_proxy_100_continue(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {18, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_xff_num_trusted_hops(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, uint32_t value) {
  const upb_MiniTableField field = {19, UPB_SIZE(72, 32), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_represent_ipv4_remote_address_as_ipv4_mapped_ipv6(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {20, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_skip_xff_append(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {21, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_via(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, upb_StringView value) {
  const upb_MiniTableField field = {22, UPB_SIZE(204, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_upgrade_configs(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_resize_upgrade_configs(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_upgrade_configs(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {23, UPB_SIZE(76, 184), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_stream_idle_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {24, UPB_SIZE(80, 192), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_stream_idle_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_stream_idle_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_stream_idle_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_internal_address_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* value) {
  const upb_MiniTableField field = {25, UPB_SIZE(84, 200), 73, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_internal_address_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_internal_address_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_internal_address_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_delayed_close_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {26, UPB_SIZE(88, 208), 74, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_delayed_close_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_delayed_close_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_delayed_close_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_request_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {28, UPB_SIZE(92, 216), 75, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_request_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_request_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_request_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_max_request_headers_kb(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {29, UPB_SIZE(96, 224), 76, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_max_request_headers_kb(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_max_request_headers_kb(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_max_request_headers_kb(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_normalize_path(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {30, UPB_SIZE(100, 232), 77, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_normalize_path(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_normalize_path(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_normalize_path(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_scoped_routes(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* value) {
  const upb_MiniTableField field = {31, UPB_SIZE(176, 360), UPB_SIZE(-173, -45), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_scoped_routes(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_scoped_routes(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_scoped_routes(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_preserve_external_request_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {32, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_merge_slashes(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {33, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_server_header_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, int32_t value) {
  const upb_MiniTableField field = {34, UPB_SIZE(104, 36), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_common_http_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_core_v3_HttpProtocolOptions* value) {
  const upb_MiniTableField field = {35, UPB_SIZE(108, 240), 78, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HttpProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_common_http_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HttpProtocolOptions* sub = (struct envoy_config_core_v3_HttpProtocolOptions*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_common_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HttpProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__HttpProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_common_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_request_id_extension(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* value) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 248), 79, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_request_id_extension(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_request_id_extension(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_request_id_extension(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_always_set_request_id_in_response(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {37, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_local_reply_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* value) {
  const upb_MiniTableField field = {38, UPB_SIZE(116, 256), 80, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_local_reply_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_local_reply_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_local_reply_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_strip_matching_host_port(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {39, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_stream_error_on_invalid_http_message(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {40, UPB_SIZE(120, 264), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_stream_error_on_invalid_http_message(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_stream_error_on_invalid_http_message(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_stream_error_on_invalid_http_message(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_request_headers_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {41, UPB_SIZE(124, 272), 82, 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_request_headers_timeout(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_request_headers_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_request_headers_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_strip_any_host_port(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {42, UPB_SIZE(184, 368), UPB_SIZE(-181, -49), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_path_normalization_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* value) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 280), 83, 25, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_path_normalization_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_path_normalization_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_path_normalization_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http3_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_core_v3_Http3ProtocolOptions* value) {
  const upb_MiniTableField field = {44, UPB_SIZE(132, 288), 84, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_http3_protocol_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http3ProtocolOptions* sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_http3_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http3ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http3_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_path_with_escaped_slashes_action(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, int32_t value) {
  const upb_MiniTableField field = {45, UPB_SIZE(136, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_original_ip_detection_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_resize_original_ip_detection_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_original_ip_detection_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {46, UPB_SIZE(140, 296), 0, 27, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_strip_trailing_host_dot(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {47, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_scheme_header_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_core_v3_SchemeHeaderTransformation* value) {
  const upb_MiniTableField field = {48, UPB_SIZE(144, 304), 85, 28, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SchemeHeaderTransformation_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_SchemeHeaderTransformation* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_scheme_header_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_SchemeHeaderTransformation* sub = (struct envoy_config_core_v3_SchemeHeaderTransformation*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_scheme_header_transformation(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_SchemeHeaderTransformation*)_upb_Message_New(&envoy__config__core__v3__SchemeHeaderTransformation_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_scheme_header_transformation(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_proxy_status_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* value) {
  const upb_MiniTableField field = {49, UPB_SIZE(148, 312), 86, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_proxy_status_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_proxy_status_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_proxy_status_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_typed_header_validation_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {50, UPB_SIZE(152, 320), 87, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_typed_header_validation_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_typed_header_validation_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_typed_header_validation_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_append_x_forwarded_port(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {51, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_early_header_mutation_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t* size) {
  upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_resize_early_header_mutation_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_early_header_mutation_extensions(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  upb_MiniTableField field = {52, UPB_SIZE(156, 328), 0, 31, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_add_proxy_protocol_connection_state(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {53, UPB_SIZE(160, 336), 88, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_add_proxy_protocol_connection_state(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_add_proxy_protocol_connection_state(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_add_proxy_protocol_connection_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_access_log_flush_interval(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {54, UPB_SIZE(164, 344), 89, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_access_log_flush_interval(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log_flush_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_access_log_flush_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_flush_access_log_on_new_request(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {55, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_access_log_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* value) {
  const upb_MiniTableField field = {56, UPB_SIZE(168, 352), 90, 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_mutable_access_log_options(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_access_log_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_access_log_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_append_local_overload(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {57, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_set_http1_safe_max_connection_duration(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager *msg, bool value) {
  const upb_MiniTableField field = {58, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__Tracing_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_client_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_client_sampling(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_has_client_sampling(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_random_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_random_sampling(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_has_random_sampling(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_overall_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_overall_sampling(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_has_overall_sampling(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_verbose(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_verbose(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_max_path_tag_length(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_max_path_tag_length(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_has_max_path_tag_length(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_custom_tags(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_tracing_v3_CustomTag* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_custom_tags(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_tracing_v3_CustomTag* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_custom_tags_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_custom_tags_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_provider(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_trace_v3_Tracing_Http* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_provider(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const struct envoy_config_trace_v3_Tracing_Http* default_val = NULL;
  const struct envoy_config_trace_v3_Tracing_Http* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__Tracing__Http_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_has_provider(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_clear_spawn_upstream_span(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_spawn_upstream_span(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_has_spawn_upstream_span(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_client_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_client_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_client_sampling(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_client_sampling(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_random_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_random_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_random_sampling(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_random_sampling(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_overall_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_overall_sampling(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_overall_sampling(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_overall_sampling(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_verbose(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_max_path_tag_length(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_max_path_tag_length(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_max_path_tag_length(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_max_path_tag_length(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_type_tracing_v3_CustomTag** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_custom_tags(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_tracing_v3_CustomTag**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_tracing_v3_CustomTag** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_resize_custom_tags(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_tracing_v3_CustomTag**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_tracing_v3_CustomTag* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_add_custom_tags(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_tracing_v3_CustomTag* sub = (struct envoy_type_tracing_v3_CustomTag*)_upb_Message_New(&envoy__type__tracing__v3__CustomTag_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_provider(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, struct envoy_config_trace_v3_Tracing_Http* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 56), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__Tracing__Http_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_trace_v3_Tracing_Http* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_provider(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  struct envoy_config_trace_v3_Tracing_Http* sub = (struct envoy_config_trace_v3_Tracing_Http*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_provider(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_trace_v3_Tracing_Http*)_upb_Message_New(&envoy__config__trace__v3__Tracing__Http_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_provider(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_spawn_upstream_span(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 64), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_mutable_spawn_upstream_span(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_spawn_upstream_span(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_Tracing_set_spawn_upstream_span(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__InternalAddressConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_clear_unix_sockets(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_unix_sockets(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_clear_cidr_ranges(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_cidr_ranges(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_CidrRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_cidr_ranges_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_cidr_ranges_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_set_unix_sockets(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_mutable_cidr_ranges(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_CidrRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_resize_cidr_ranges(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_CidrRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig_add_cidr_ranges(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_InternalAddressConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__SetCurrentClientCertDetails_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_clear_subject(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const upb_MiniTableField field = {1, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_subject(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {1, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_has_subject(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const upb_MiniTableField field = {1, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_clear_cert(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_cert(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_clear_dns(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const upb_MiniTableField field = {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_dns(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_clear_uri(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const upb_MiniTableField field = {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_uri(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_clear_chain(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_chain(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_set_subject(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {1, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_mutable_subject(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_subject(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_set_subject(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_set_cert(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_set_dns(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails *msg, bool value) {
  const upb_MiniTableField field = {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_set_uri(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails *msg, bool value) {
  const upb_MiniTableField field = {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails_set_chain(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_SetCurrentClientCertDetails *msg, bool value) {
  const upb_MiniTableField field = {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__UpgradeConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_clear_upgrade_type(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_upgrade_type(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_clear_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* const* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_filters(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_filters_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_filters_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_clear_enabled(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_enabled(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_has_enabled(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_set_upgrade_type(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_mutable_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter** envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_resize_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_add_filters(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_set_enabled(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_mutable_enabled(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_enabled(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_UpgradeConfig_set_enabled(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__PathNormalizationOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_clear_forwarding_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_http_v3_PathTransformation* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_forwarding_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg) {
  const struct envoy_type_http_v3_PathTransformation* default_val = NULL;
  const struct envoy_type_http_v3_PathTransformation* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_has_forwarding_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_clear_http_filter_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_http_v3_PathTransformation* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_http_filter_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg) {
  const struct envoy_type_http_v3_PathTransformation* default_val = NULL;
  const struct envoy_type_http_v3_PathTransformation* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_has_http_filter_transformation(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_set_forwarding_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions *msg, struct envoy_type_http_v3_PathTransformation* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_http_v3_PathTransformation* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_mutable_forwarding_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg, upb_Arena* arena) {
  struct envoy_type_http_v3_PathTransformation* sub = (struct envoy_type_http_v3_PathTransformation*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_forwarding_transformation(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_http_v3_PathTransformation*)_upb_Message_New(&envoy__type__http__v3__PathTransformation_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_set_forwarding_transformation(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_set_http_filter_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions *msg, struct envoy_type_http_v3_PathTransformation* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_http_v3_PathTransformation* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_mutable_http_filter_transformation(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions* msg, upb_Arena* arena) {
  struct envoy_type_http_v3_PathTransformation* sub = (struct envoy_type_http_v3_PathTransformation*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_http_filter_transformation(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_http_v3_PathTransformation*)_upb_Message_New(&envoy__type__http__v3__PathTransformation_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_PathNormalizationOptions_set_http_filter_transformation(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_use_node_id = 5,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_literal_proxy_name = 6,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_case(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {5, 16, -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_proxy_name_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_proxy_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {5, 16, -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__ProxyStatusConfig_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_remove_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_remove_details(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_remove_connection_termination_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_remove_connection_termination_details(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_remove_response_flags(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_remove_response_flags(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_set_recommended_response_code(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {4, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_recommended_response_code(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_use_node_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {5, 16, -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_use_node_id(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 16, -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_has_use_node_id(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {5, 16, -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_clear_literal_proxy_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {6, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_literal_proxy_name(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_has_literal_proxy_name(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig* msg) {
  const upb_MiniTableField field = {6, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_remove_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_remove_connection_termination_details(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_remove_response_flags(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig *msg, bool value) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_set_recommended_response_code(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig *msg, bool value) {
  const upb_MiniTableField field = {4, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_use_node_id(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig *msg, bool value) {
  const upb_MiniTableField field = {5, 16, -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig_set_literal_proxy_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_ProxyStatusConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager__HcmAccessLogOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_clear_access_log_flush_interval(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_access_log_flush_interval(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_has_access_log_flush_interval(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_clear_flush_access_log_on_new_request(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_flush_access_log_on_new_request(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_clear_flush_log_on_tunnel_successfully_established(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_flush_log_on_tunnel_successfully_established(const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_set_access_log_flush_interval(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_mutable_access_log_flush_interval(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_access_log_flush_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_set_access_log_flush_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_set_flush_access_log_on_new_request(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions_set_flush_log_on_tunnel_successfully_established(envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_HcmAccessLogOptions *msg, bool value) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* ret = envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__LocalReplyConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_clear_mappers(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* const* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_mappers(const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_mappers_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_mappers_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_clear_body_format(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SubstitutionFormatString* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_body_format(const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg) {
  const struct envoy_config_core_v3_SubstitutionFormatString* default_val = NULL;
  const struct envoy_config_core_v3_SubstitutionFormatString* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SubstitutionFormatString_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_has_body_format(const envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper** envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_mutable_mappers(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper** envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_resize_mappers(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_add_mappers(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_set_body_format(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig *msg, struct envoy_config_core_v3_SubstitutionFormatString* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SubstitutionFormatString_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_SubstitutionFormatString* envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_mutable_body_format(envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_SubstitutionFormatString* sub = (struct envoy_config_core_v3_SubstitutionFormatString*)envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_body_format(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_SubstitutionFormatString*)_upb_Message_New(&envoy__config__core__v3__SubstitutionFormatString_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_LocalReplyConfig_set_body_format(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* ret = envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* ret = envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ResponseMapper_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_clear_filter(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_accesslog_v3_AccessLogFilter* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_filter(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const struct envoy_config_accesslog_v3_AccessLogFilter* default_val = NULL;
  const struct envoy_config_accesslog_v3_AccessLogFilter* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_has_filter(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_clear_status_code(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_status_code(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_has_status_code(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_clear_body(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_body(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_has_body(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_clear_body_format_override(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SubstitutionFormatString* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_body_format_override(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const struct envoy_config_core_v3_SubstitutionFormatString* default_val = NULL;
  const struct envoy_config_core_v3_SubstitutionFormatString* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SubstitutionFormatString_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_has_body_format_override(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_clear_headers_to_add(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_headers_to_add(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_HeaderValueOption* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_headers_to_add_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_headers_to_add_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_filter(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper *msg, struct envoy_config_accesslog_v3_AccessLogFilter* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLogFilter* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_mutable_filter(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_AccessLogFilter* sub = (struct envoy_config_accesslog_v3_AccessLogFilter*)envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_AccessLogFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLogFilter_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_status_code(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_mutable_status_code(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_status_code(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_status_code(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_body(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_mutable_body(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_body(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_body(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_body_format_override(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper *msg, struct envoy_config_core_v3_SubstitutionFormatString* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SubstitutionFormatString_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_SubstitutionFormatString* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_mutable_body_format_override(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_SubstitutionFormatString* sub = (struct envoy_config_core_v3_SubstitutionFormatString*)envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_body_format_override(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_SubstitutionFormatString*)_upb_Message_New(&envoy__config__core__v3__SubstitutionFormatString_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_set_body_format_override(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_mutable_headers_to_add(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_HeaderValueOption**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_resize_headers_to_add(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper_add_headers_to_add(envoy_extensions_filters_network_http_connection_manager_v3_ResponseMapper* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HeaderValueOption* sub = (struct envoy_config_core_v3_HeaderValueOption*)_upb_Message_New(&envoy__config__core__v3__HeaderValueOption_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_Rds* envoy_extensions_filters_network_http_connection_manager_v3_Rds_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_Rds*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_Rds* envoy_extensions_filters_network_http_connection_manager_v3_Rds_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_Rds* ret = envoy_extensions_filters_network_http_connection_manager_v3_Rds_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_Rds* envoy_extensions_filters_network_http_connection_manager_v3_Rds_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_Rds* ret = envoy_extensions_filters_network_http_connection_manager_v3_Rds_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_Rds_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_Rds_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__Rds_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_Rds_clear_config_source(envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_Rds_config_source(const envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_Rds_has_config_source(const envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_Rds_clear_route_config_name(envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_Rds_route_config_name(const envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_Rds_set_config_source(envoy_extensions_filters_network_http_connection_manager_v3_Rds *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_Rds_mutable_config_source(envoy_extensions_filters_network_http_connection_manager_v3_Rds* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_extensions_filters_network_http_connection_manager_v3_Rds_config_source(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_Rds_set_config_source(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_Rds_set_route_config_name(envoy_extensions_filters_network_http_connection_manager_v3_Rds *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_clear_scoped_route_configurations(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_ScopedRouteConfiguration* const* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_scoped_route_configurations(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_route_v3_ScopedRouteConfiguration* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_scoped_route_configurations_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_scoped_route_configurations_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct envoy_config_route_v3_ScopedRouteConfiguration** envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_mutable_scoped_route_configurations(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_route_v3_ScopedRouteConfiguration**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_route_v3_ScopedRouteConfiguration** envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_resize_scoped_route_configurations(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_route_v3_ScopedRouteConfiguration**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_ScopedRouteConfiguration* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList_add_scoped_route_configurations(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_ScopedRouteConfiguration* sub = (struct envoy_config_route_v3_ScopedRouteConfiguration*)_upb_Message_New(&envoy__config__route__v3__ScopedRouteConfiguration_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_scoped_route_configurations_list = 4,
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_scoped_rds = 5,
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_case(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_config_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_clear_config_specifier(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_clear_name(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_name(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_clear_scope_key_builder(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_scope_key_builder(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_has_scope_key_builder(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_clear_rds_config_source(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_rds_config_source(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_has_rds_config_source(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_clear_scoped_route_configurations_list(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_scoped_route_configurations_list(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_has_scoped_route_configurations_list(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_clear_scoped_rds(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_scoped_rds(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_has_scoped_rds(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_name(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_scope_key_builder(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes *msg, envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_mutable_scope_key_builder(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_scope_key_builder(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_scope_key_builder(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_rds_config_source(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_mutable_rds_config_source(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_rds_config_source(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_rds_config_source(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_scoped_route_configurations_list(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes *msg, envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_mutable_scoped_route_configurations_list(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_scoped_route_configurations_list(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRouteConfigurationsList*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRouteConfigurationsList_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_scoped_route_configurations_list(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_scoped_rds(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes *msg, envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), UPB_SIZE(-21, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_mutable_scoped_rds(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_scoped_rds(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_set_scoped_rds(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_clear_fragments(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* const* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_fragments(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_fragments_upb_array(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_fragments_mutable_upb_array(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder** envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_mutable_fragments(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder** envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_resize_fragments(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_add_fragments(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_type_header_value_extractor = 1,
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_type_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_type_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_type_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_type_case(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_clear_type(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_clear_header_value_extractor(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_header_value_extractor(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_has_header_value_extractor(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_set_header_value_extractor(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder *msg, envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_mutable_header_value_extractor(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_header_value_extractor(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_set_header_value_extractor(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_index = 3,
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_element = 4,
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_case(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_extract_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_clear_extract_type(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_clear_name(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_name(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_clear_element_separator(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_element_separator(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_clear_index(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_index(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_has_index(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_clear_element(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_element(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_has_element(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_set_name(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_set_element_separator(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_set_index(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor *msg, uint32_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_set_element(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor *msg, envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_mutable_element(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_element(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_set_element(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRoutes__ScopeKeyBuilder__FragmentBuilder__HeaderValueExtractor__KvElement_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_clear_separator(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_separator(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_clear_key(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_key(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_set_separator(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement_set_key(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRoutes_ScopeKeyBuilder_FragmentBuilder_HeaderValueExtractor_KvElement *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* ret = envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__ScopedRds_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_clear_scoped_rds_config_source(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_scoped_rds_config_source(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_has_scoped_rds_config_source(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_clear_srds_resources_locator(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_srds_resources_locator(const envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_set_scoped_rds_config_source(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_mutable_scoped_rds_config_source(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_scoped_rds_config_source(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_set_scoped_rds_config_source(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds_set_srds_resources_locator(envoy_extensions_filters_network_http_connection_manager_v3_ScopedRds *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* ret = envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_typed_config = 4,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_config_discovery = 5,
  envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_NOT_SET = 0
} envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_oneofcases;
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_oneofcases envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_case(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_clear_config_type(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_clear_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_name(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_clear_typed_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_typed_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_has_typed_config(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_clear_config_discovery(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ExtensionConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_discovery(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const struct envoy_config_core_v3_ExtensionConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ExtensionConfigSource* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_has_config_discovery(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_clear_is_optional(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_is_optional(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_clear_disabled(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  const upb_MiniTableField field = {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_disabled(const envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_name(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_typed_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_mutable_typed_config(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_config_discovery(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter *msg, struct envoy_config_core_v3_ExtensionConfigSource* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ExtensionConfigSource* envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_mutable_config_discovery(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ExtensionConfigSource* sub = (struct envoy_config_core_v3_ExtensionConfigSource*)envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_config_discovery(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ExtensionConfigSource*)_upb_Message_New(&envoy__config__core__v3__ExtensionConfigSource_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_config_discovery(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_is_optional(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter *msg, bool value) {
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter_set_disabled(envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter *msg, bool value) {
  const upb_MiniTableField field = {7, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* ret = envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* ret = envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__RequestIDExtension_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_clear_typed_config(envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_typed_config(const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_has_typed_config(const envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_set_typed_config(envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_mutable_typed_config(envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_RequestIDExtension_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_new(upb_Arena* arena) {
  return (envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__EnvoyMobileHttpConnectionManager_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* ret = envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__EnvoyMobileHttpConnectionManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* ret = envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__network__http_0connection_0manager__v3__EnvoyMobileHttpConnectionManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_serialize(const envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__EnvoyMobileHttpConnectionManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_serialize_ex(const envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__network__http_0connection_0manager__v3__EnvoyMobileHttpConnectionManager_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_clear_config(envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_config(const envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* msg) {
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* default_val = NULL;
  const envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_has_config(const envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_set_config(envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager *msg, envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_mutable_config(envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager*)envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpConnectionManager_msg_init, arena);
    if (sub) envoy_extensions_filters_network_http_connection_manager_v3_EnvoyMobileHttpConnectionManager_set_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
