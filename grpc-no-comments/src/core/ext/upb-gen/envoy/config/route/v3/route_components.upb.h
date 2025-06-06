
#ifndef ENVOY_CONFIG_ROUTE_V3_ROUTE_COMPONENTS_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_ROUTE_V3_ROUTE_COMPONENTS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/route/v3/route_components.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/proxy_protocol.upb_minitable.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"
#include "envoy/type/matcher/v3/regex.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/metadata/v3/metadata.upb_minitable.h"
#include "envoy/type/tracing/v3/custom_tag.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_route_v3_VirtualHost { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_VirtualHost;
typedef struct envoy_config_route_v3_FilterAction { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_FilterAction;
typedef struct envoy_config_route_v3_RouteList { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteList;
typedef struct envoy_config_route_v3_Route { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_Route;
typedef struct envoy_config_route_v3_WeightedCluster { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_WeightedCluster;
typedef struct envoy_config_route_v3_WeightedCluster_ClusterWeight { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_WeightedCluster_ClusterWeight;
typedef struct envoy_config_route_v3_ClusterSpecifierPlugin { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_ClusterSpecifierPlugin;
typedef struct envoy_config_route_v3_RouteMatch { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteMatch;
typedef struct envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions;
typedef struct envoy_config_route_v3_RouteMatch_TlsContextMatchOptions { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteMatch_TlsContextMatchOptions;
typedef struct envoy_config_route_v3_RouteMatch_ConnectMatcher { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteMatch_ConnectMatcher;
typedef struct envoy_config_route_v3_CorsPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_CorsPolicy;
typedef struct envoy_config_route_v3_RouteAction { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction;
typedef struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_RequestMirrorPolicy;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy_Header { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy_Header;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy_Cookie { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy_Cookie;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter;
typedef struct envoy_config_route_v3_RouteAction_HashPolicy_FilterState { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_HashPolicy_FilterState;
typedef struct envoy_config_route_v3_RouteAction_UpgradeConfig { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_UpgradeConfig;
typedef struct envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig;
typedef struct envoy_config_route_v3_RouteAction_MaxStreamDuration { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RouteAction_MaxStreamDuration;
typedef struct envoy_config_route_v3_RetryPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RetryPolicy;
typedef struct envoy_config_route_v3_RetryPolicy_RetryPriority { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RetryPolicy_RetryPriority;
typedef struct envoy_config_route_v3_RetryPolicy_RetryHostPredicate { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RetryPolicy_RetryHostPredicate;
typedef struct envoy_config_route_v3_RetryPolicy_RetryBackOff { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RetryPolicy_RetryBackOff;
typedef struct envoy_config_route_v3_RetryPolicy_ResetHeader { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RetryPolicy_ResetHeader;
typedef struct envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff;
typedef struct envoy_config_route_v3_HedgePolicy { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_HedgePolicy;
typedef struct envoy_config_route_v3_RedirectAction { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RedirectAction;
typedef struct envoy_config_route_v3_DirectResponseAction { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_DirectResponseAction;
typedef struct envoy_config_route_v3_NonForwardingAction { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_NonForwardingAction;
typedef struct envoy_config_route_v3_Decorator { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_Decorator;
typedef struct envoy_config_route_v3_Tracing { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_Tracing;
typedef struct envoy_config_route_v3_VirtualCluster { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_VirtualCluster;
typedef struct envoy_config_route_v3_RateLimit { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit;
typedef struct envoy_config_route_v3_RateLimit_Action { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action;
typedef struct envoy_config_route_v3_RateLimit_Action_SourceCluster { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_SourceCluster;
typedef struct envoy_config_route_v3_RateLimit_Action_DestinationCluster { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_DestinationCluster;
typedef struct envoy_config_route_v3_RateLimit_Action_RequestHeaders { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_RequestHeaders;
typedef struct envoy_config_route_v3_RateLimit_Action_QueryParameters { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_QueryParameters;
typedef struct envoy_config_route_v3_RateLimit_Action_RemoteAddress { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_RemoteAddress;
typedef struct envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress;
typedef struct envoy_config_route_v3_RateLimit_Action_GenericKey { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_GenericKey;
typedef struct envoy_config_route_v3_RateLimit_Action_HeaderValueMatch { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_HeaderValueMatch;
typedef struct envoy_config_route_v3_RateLimit_Action_DynamicMetaData { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_DynamicMetaData;
typedef struct envoy_config_route_v3_RateLimit_Action_MetaData { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_MetaData;
typedef struct envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch;
typedef struct envoy_config_route_v3_RateLimit_Override { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Override;
typedef struct envoy_config_route_v3_RateLimit_Override_DynamicMetadata { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_Override_DynamicMetadata;
typedef struct envoy_config_route_v3_RateLimit_HitsAddend { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_RateLimit_HitsAddend;
typedef struct envoy_config_route_v3_HeaderMatcher { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_HeaderMatcher;
typedef struct envoy_config_route_v3_QueryParameterMatcher { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_QueryParameterMatcher;
typedef struct envoy_config_route_v3_InternalRedirectPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_InternalRedirectPolicy;
typedef struct envoy_config_route_v3_FilterConfig { upb_Message UPB_PRIVATE(base); } envoy_config_route_v3_FilterConfig;
struct envoy_config_core_v3_DataSource;
struct envoy_config_core_v3_HeaderValueOption;
struct envoy_config_core_v3_Metadata;
struct envoy_config_core_v3_ProxyProtocolConfig;
struct envoy_config_core_v3_RuntimeFractionalPercent;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_type_matcher_v3_MetadataMatcher;
struct envoy_type_matcher_v3_RegexMatchAndSubstitute;
struct envoy_type_matcher_v3_RegexMatcher;
struct envoy_type_matcher_v3_StringMatcher;
struct envoy_type_metadata_v3_MetadataKey;
struct envoy_type_tracing_v3_CustomTag;
struct envoy_type_v3_FractionalPercent;
struct envoy_type_v3_Int64Range;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;
struct google_protobuf_UInt64Value;
struct xds_type_matcher_v3_Matcher;

typedef enum {
  envoy_config_route_v3_RateLimit_Action_MetaData_DYNAMIC = 0,
  envoy_config_route_v3_RateLimit_Action_MetaData_ROUTE_ENTRY = 1
} envoy_config_route_v3_RateLimit_Action_MetaData_Source;

typedef enum {
  envoy_config_route_v3_RedirectAction_MOVED_PERMANENTLY = 0,
  envoy_config_route_v3_RedirectAction_FOUND = 1,
  envoy_config_route_v3_RedirectAction_SEE_OTHER = 2,
  envoy_config_route_v3_RedirectAction_TEMPORARY_REDIRECT = 3,
  envoy_config_route_v3_RedirectAction_PERMANENT_REDIRECT = 4
} envoy_config_route_v3_RedirectAction_RedirectResponseCode;

typedef enum {
  envoy_config_route_v3_RetryPolicy_SECONDS = 0,
  envoy_config_route_v3_RetryPolicy_UNIX_TIMESTAMP = 1
} envoy_config_route_v3_RetryPolicy_ResetHeaderFormat;

typedef enum {
  envoy_config_route_v3_RouteAction_SERVICE_UNAVAILABLE = 0,
  envoy_config_route_v3_RouteAction_NOT_FOUND = 1,
  envoy_config_route_v3_RouteAction_INTERNAL_SERVER_ERROR = 2
} envoy_config_route_v3_RouteAction_ClusterNotFoundResponseCode;

typedef enum {
  envoy_config_route_v3_RouteAction_PASS_THROUGH_INTERNAL_REDIRECT = 0,
  envoy_config_route_v3_RouteAction_HANDLE_INTERNAL_REDIRECT = 1
} envoy_config_route_v3_RouteAction_InternalRedirectAction;

typedef enum {
  envoy_config_route_v3_VirtualHost_NONE = 0,
  envoy_config_route_v3_VirtualHost_EXTERNAL_ONLY = 1,
  envoy_config_route_v3_VirtualHost_ALL = 2
} envoy_config_route_v3_VirtualHost_TlsRequirementType;

UPB_INLINE envoy_config_route_v3_VirtualHost* envoy_config_route_v3_VirtualHost_new(upb_Arena* arena) {
  return (envoy_config_route_v3_VirtualHost*)_upb_Message_New(&envoy__config__route__v3__VirtualHost_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_VirtualHost* envoy_config_route_v3_VirtualHost_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_VirtualHost* ret = envoy_config_route_v3_VirtualHost_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__VirtualHost_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_VirtualHost* envoy_config_route_v3_VirtualHost_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_VirtualHost* ret = envoy_config_route_v3_VirtualHost_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__VirtualHost_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_VirtualHost_serialize(const envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__VirtualHost_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_VirtualHost_serialize_ex(const envoy_config_route_v3_VirtualHost* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__VirtualHost_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_name(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(84, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_VirtualHost_name(const envoy_config_route_v3_VirtualHost* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(84, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_domains(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_VirtualHost_domains(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_domains_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_domains_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_routes(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_Route* const* envoy_config_route_v3_VirtualHost_routes(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_Route* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_routes_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_routes_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_require_tls(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_VirtualHost_require_tls(const envoy_config_route_v3_VirtualHost* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_virtual_clusters(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_VirtualCluster* const* envoy_config_route_v3_VirtualHost_virtual_clusters(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_VirtualCluster* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_virtual_clusters_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualCluster_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_virtual_clusters_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_rate_limits(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit* const* envoy_config_route_v3_VirtualHost_rate_limits(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RateLimit* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_rate_limits_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_rate_limits_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_request_headers_to_add(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_route_v3_VirtualHost_request_headers_to_add(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_request_headers_to_add_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_request_headers_to_add_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_cors(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 64, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_VirtualHost_cors(const envoy_config_route_v3_VirtualHost* msg) {
  const envoy_config_route_v3_CorsPolicy* default_val = NULL;
  const envoy_config_route_v3_CorsPolicy* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 64, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__CorsPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_cors(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 64, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_response_headers_to_add(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_route_v3_VirtualHost_response_headers_to_add(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_response_headers_to_add_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_response_headers_to_add_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_response_headers_to_remove(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_VirtualHost_response_headers_to_remove(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_response_headers_to_remove_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_response_headers_to_remove_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_request_headers_to_remove(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_VirtualHost_request_headers_to_remove(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_request_headers_to_remove_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_request_headers_to_remove_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_include_request_attempt_count(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_include_request_attempt_count(const envoy_config_route_v3_VirtualHost* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_typed_per_filter_config(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_route_v3_VirtualHost_typed_per_filter_config_size(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_typed_per_filter_config_get(const envoy_config_route_v3_VirtualHost* msg, upb_StringView key, struct google_protobuf_Any** val) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_typed_per_filter_config_next(const envoy_config_route_v3_VirtualHost* msg, upb_StringView* key, const struct google_protobuf_Any** val,
                           size_t* iter) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_route_v3_VirtualHost_typed_per_filter_config_upb_map(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_route_v3_VirtualHost_typed_per_filter_config_mutable_upb_map(envoy_config_route_v3_VirtualHost* msg, upb_Arena* a) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Any*), a);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_retry_policy(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 112), 65, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_VirtualHost_retry_policy(const envoy_config_route_v3_VirtualHost* msg) {
  const envoy_config_route_v3_RetryPolicy* default_val = NULL;
  const envoy_config_route_v3_RetryPolicy* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(56, 112), 65, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_retry_policy(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 112), 65, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_hedge_policy(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 120), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_VirtualHost_hedge_policy(const envoy_config_route_v3_VirtualHost* msg) {
  const envoy_config_route_v3_HedgePolicy* default_val = NULL;
  const envoy_config_route_v3_HedgePolicy* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(60, 120), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HedgePolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_hedge_policy(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 120), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_per_request_buffer_limit_bytes(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 128), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_VirtualHost_per_request_buffer_limit_bytes(const envoy_config_route_v3_VirtualHost* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {18, UPB_SIZE(64, 128), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_per_request_buffer_limit_bytes(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 128), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_include_attempt_count_in_response(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_include_attempt_count_in_response(const envoy_config_route_v3_VirtualHost* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_retry_policy_typed_config(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(68, 136), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_route_v3_VirtualHost_retry_policy_typed_config(const envoy_config_route_v3_VirtualHost* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(68, 136), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_retry_policy_typed_config(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(68, 136), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_matcher(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 144), 69, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher* envoy_config_route_v3_VirtualHost_matcher(const envoy_config_route_v3_VirtualHost* msg) {
  const struct xds_type_matcher_v3_Matcher* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher* ret;
  const upb_MiniTableField field = {21, UPB_SIZE(72, 144), 69, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_matcher(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 144), 69, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_request_mirror_policies(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* const* envoy_config_route_v3_VirtualHost_request_mirror_policies(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualHost_request_mirror_policies_upb_array(const envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualHost_request_mirror_policies_mutable_upb_array(envoy_config_route_v3_VirtualHost* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_include_is_timeout_retry_header(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_include_is_timeout_retry_header(const envoy_config_route_v3_VirtualHost* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_clear_metadata(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(80, 160), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_route_v3_VirtualHost_metadata(const envoy_config_route_v3_VirtualHost* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {24, UPB_SIZE(80, 160), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_has_metadata(const envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(80, 160), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_VirtualHost_set_name(envoy_config_route_v3_VirtualHost *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(84, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_config_route_v3_VirtualHost_mutable_domains(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_VirtualHost_resize_domains(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_add_domains(envoy_config_route_v3_VirtualHost* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE envoy_config_route_v3_Route** envoy_config_route_v3_VirtualHost_mutable_routes(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_Route**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_Route** envoy_config_route_v3_VirtualHost_resize_routes(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_Route**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_Route* envoy_config_route_v3_VirtualHost_add_routes(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_Route* sub = (struct envoy_config_route_v3_Route*)_upb_Message_New(&envoy__config__route__v3__Route_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_require_tls(envoy_config_route_v3_VirtualHost *msg, int32_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_route_v3_VirtualCluster** envoy_config_route_v3_VirtualHost_mutable_virtual_clusters(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualCluster_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_VirtualCluster**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_VirtualCluster** envoy_config_route_v3_VirtualHost_resize_virtual_clusters(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_VirtualCluster**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_VirtualCluster* envoy_config_route_v3_VirtualHost_add_virtual_clusters(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualCluster_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_VirtualCluster* sub = (struct envoy_config_route_v3_VirtualCluster*)_upb_Message_New(&envoy__config__route__v3__VirtualCluster_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_config_route_v3_RateLimit** envoy_config_route_v3_VirtualHost_mutable_rate_limits(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RateLimit**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RateLimit** envoy_config_route_v3_VirtualHost_resize_rate_limits(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RateLimit**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit* envoy_config_route_v3_VirtualHost_add_rate_limits(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RateLimit* sub = (struct envoy_config_route_v3_RateLimit*)_upb_Message_New(&envoy__config__route__v3__RateLimit_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_VirtualHost_mutable_request_headers_to_add(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_VirtualHost_resize_request_headers_to_add(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_route_v3_VirtualHost_add_request_headers_to_add(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_cors(envoy_config_route_v3_VirtualHost *msg, envoy_config_route_v3_CorsPolicy* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 64, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__CorsPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_VirtualHost_mutable_cors(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_CorsPolicy* sub = (struct envoy_config_route_v3_CorsPolicy*)envoy_config_route_v3_VirtualHost_cors(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_CorsPolicy*)_upb_Message_New(&envoy__config__route__v3__CorsPolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_cors(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_VirtualHost_mutable_response_headers_to_add(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_VirtualHost_resize_response_headers_to_add(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_route_v3_VirtualHost_add_response_headers_to_add(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_route_v3_VirtualHost_mutable_response_headers_to_remove(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_VirtualHost_resize_response_headers_to_remove(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_add_response_headers_to_remove(envoy_config_route_v3_VirtualHost* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_route_v3_VirtualHost_mutable_request_headers_to_remove(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_VirtualHost_resize_request_headers_to_remove(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_add_request_headers_to_remove(envoy_config_route_v3_VirtualHost* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_include_request_attempt_count(envoy_config_route_v3_VirtualHost *msg, bool value) {
  const upb_MiniTableField field = {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_typed_per_filter_config_clear(envoy_config_route_v3_VirtualHost* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_typed_per_filter_config_set(envoy_config_route_v3_VirtualHost* msg, upb_StringView key, struct google_protobuf_Any* val, upb_Arena* a) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_route_v3_VirtualHost_typed_per_filter_config_delete(envoy_config_route_v3_VirtualHost* msg, upb_StringView key) {
  const upb_MiniTableField field = {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_retry_policy(envoy_config_route_v3_VirtualHost *msg, envoy_config_route_v3_RetryPolicy* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 112), 65, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_VirtualHost_mutable_retry_policy(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RetryPolicy* sub = (struct envoy_config_route_v3_RetryPolicy*)envoy_config_route_v3_VirtualHost_retry_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RetryPolicy*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_retry_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_hedge_policy(envoy_config_route_v3_VirtualHost *msg, envoy_config_route_v3_HedgePolicy* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 120), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HedgePolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_VirtualHost_mutable_hedge_policy(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_HedgePolicy* sub = (struct envoy_config_route_v3_HedgePolicy*)envoy_config_route_v3_VirtualHost_hedge_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_HedgePolicy*)_upb_Message_New(&envoy__config__route__v3__HedgePolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_hedge_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_per_request_buffer_limit_bytes(envoy_config_route_v3_VirtualHost *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 128), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_VirtualHost_mutable_per_request_buffer_limit_bytes(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_VirtualHost_per_request_buffer_limit_bytes(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_per_request_buffer_limit_bytes(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_include_attempt_count_in_response(envoy_config_route_v3_VirtualHost *msg, bool value) {
  const upb_MiniTableField field = {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_retry_policy_typed_config(envoy_config_route_v3_VirtualHost *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(68, 136), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_route_v3_VirtualHost_mutable_retry_policy_typed_config(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_route_v3_VirtualHost_retry_policy_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_retry_policy_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_matcher(envoy_config_route_v3_VirtualHost *msg, struct xds_type_matcher_v3_Matcher* value) {
  const upb_MiniTableField field = {21, UPB_SIZE(72, 144), 69, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher* envoy_config_route_v3_VirtualHost_mutable_matcher(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher* sub = (struct xds_type_matcher_v3_Matcher*)envoy_config_route_v3_VirtualHost_matcher(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher*)_upb_Message_New(&xds__type__matcher__v3__Matcher_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy** envoy_config_route_v3_VirtualHost_mutable_request_mirror_policies(envoy_config_route_v3_VirtualHost* msg, size_t* size) {
  upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RouteAction_RequestMirrorPolicy**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy** envoy_config_route_v3_VirtualHost_resize_request_mirror_policies(envoy_config_route_v3_VirtualHost* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_RequestMirrorPolicy**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy* envoy_config_route_v3_VirtualHost_add_request_mirror_policies(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  upb_MiniTableField field = {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy* sub = (struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy*)_upb_Message_New(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_include_is_timeout_retry_header(envoy_config_route_v3_VirtualHost *msg, bool value) {
  const upb_MiniTableField field = {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_VirtualHost_set_metadata(envoy_config_route_v3_VirtualHost *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {24, UPB_SIZE(80, 160), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_route_v3_VirtualHost_mutable_metadata(envoy_config_route_v3_VirtualHost* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_route_v3_VirtualHost_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_route_v3_VirtualHost_set_metadata(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_FilterAction* envoy_config_route_v3_FilterAction_new(upb_Arena* arena) {
  return (envoy_config_route_v3_FilterAction*)_upb_Message_New(&envoy__config__route__v3__FilterAction_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_FilterAction* envoy_config_route_v3_FilterAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_FilterAction* ret = envoy_config_route_v3_FilterAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__FilterAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_FilterAction* envoy_config_route_v3_FilterAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_FilterAction* ret = envoy_config_route_v3_FilterAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__FilterAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_FilterAction_serialize(const envoy_config_route_v3_FilterAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__FilterAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_FilterAction_serialize_ex(const envoy_config_route_v3_FilterAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__FilterAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_FilterAction_clear_action(envoy_config_route_v3_FilterAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_route_v3_FilterAction_action(const envoy_config_route_v3_FilterAction* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_FilterAction_has_action(const envoy_config_route_v3_FilterAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_FilterAction_set_action(envoy_config_route_v3_FilterAction *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_route_v3_FilterAction_mutable_action(envoy_config_route_v3_FilterAction* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_route_v3_FilterAction_action(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_route_v3_FilterAction_set_action(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteList* envoy_config_route_v3_RouteList_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteList*)_upb_Message_New(&envoy__config__route__v3__RouteList_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteList* envoy_config_route_v3_RouteList_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteList* ret = envoy_config_route_v3_RouteList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteList_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteList* envoy_config_route_v3_RouteList_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteList* ret = envoy_config_route_v3_RouteList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteList_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteList_serialize(const envoy_config_route_v3_RouteList* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteList_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteList_serialize_ex(const envoy_config_route_v3_RouteList* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteList_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteList_clear_routes(envoy_config_route_v3_RouteList* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_Route* const* envoy_config_route_v3_RouteList_routes(const envoy_config_route_v3_RouteList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_Route* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteList_routes_upb_array(const envoy_config_route_v3_RouteList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteList_routes_mutable_upb_array(envoy_config_route_v3_RouteList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_route_v3_Route** envoy_config_route_v3_RouteList_mutable_routes(envoy_config_route_v3_RouteList* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_Route**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_Route** envoy_config_route_v3_RouteList_resize_routes(envoy_config_route_v3_RouteList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_Route**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_Route* envoy_config_route_v3_RouteList_add_routes(envoy_config_route_v3_RouteList* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_Route* sub = (struct envoy_config_route_v3_Route*)_upb_Message_New(&envoy__config__route__v3__Route_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_route_v3_Route* envoy_config_route_v3_Route_new(upb_Arena* arena) {
  return (envoy_config_route_v3_Route*)_upb_Message_New(&envoy__config__route__v3__Route_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_Route* envoy_config_route_v3_Route_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_Route* ret = envoy_config_route_v3_Route_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__Route_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_Route* envoy_config_route_v3_Route_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_Route* ret = envoy_config_route_v3_Route_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__Route_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_Route_serialize(const envoy_config_route_v3_Route* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__Route_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_Route_serialize_ex(const envoy_config_route_v3_Route* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__Route_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_Route_action_route = 2,
  envoy_config_route_v3_Route_action_redirect = 3,
  envoy_config_route_v3_Route_action_direct_response = 7,
  envoy_config_route_v3_Route_action_filter_action = 17,
  envoy_config_route_v3_Route_action_non_forwarding_action = 18,
  envoy_config_route_v3_Route_action_NOT_SET = 0
} envoy_config_route_v3_Route_action_oneofcases;
UPB_INLINE envoy_config_route_v3_Route_action_oneofcases envoy_config_route_v3_Route_action_case(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_Route_action_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_action(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__Route_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_match(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteMatch* envoy_config_route_v3_Route_match(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_RouteMatch* default_val = NULL;
  const envoy_config_route_v3_RouteMatch* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_match(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_route(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction* envoy_config_route_v3_Route_route(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_RouteAction* default_val = NULL;
  const envoy_config_route_v3_RouteAction* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_route(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_redirect(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RedirectAction* envoy_config_route_v3_Route_redirect(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_RedirectAction* default_val = NULL;
  const envoy_config_route_v3_RedirectAction* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RedirectAction_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_redirect(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_metadata(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_route_v3_Route_metadata(const envoy_config_route_v3_Route* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_metadata(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_decorator(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_Decorator* envoy_config_route_v3_Route_decorator(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_Decorator* default_val = NULL;
  const envoy_config_route_v3_Decorator* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Decorator_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_decorator(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_direct_response(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_DirectResponseAction* envoy_config_route_v3_Route_direct_response(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_DirectResponseAction* default_val = NULL;
  const envoy_config_route_v3_DirectResponseAction* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__DirectResponseAction_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_direct_response(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_request_headers_to_add(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_route_v3_Route_request_headers_to_add(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_Route_request_headers_to_add_upb_array(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_Route_request_headers_to_add_mutable_upb_array(envoy_config_route_v3_Route* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_Route_clear_response_headers_to_add(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_route_v3_Route_response_headers_to_add(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_Route_response_headers_to_add_upb_array(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_Route_response_headers_to_add_mutable_upb_array(envoy_config_route_v3_Route* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_Route_clear_response_headers_to_remove(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_Route_response_headers_to_remove(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_Route_response_headers_to_remove_upb_array(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_Route_response_headers_to_remove_mutable_upb_array(envoy_config_route_v3_Route* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_Route_clear_request_headers_to_remove(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_Route_request_headers_to_remove(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_Route_request_headers_to_remove_upb_array(const envoy_config_route_v3_Route* msg, size_t* size) {
  const upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_Route_request_headers_to_remove_mutable_upb_array(envoy_config_route_v3_Route* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_Route_clear_typed_per_filter_config(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_route_v3_Route_typed_per_filter_config_size(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_route_v3_Route_typed_per_filter_config_get(const envoy_config_route_v3_Route* msg, upb_StringView key, struct google_protobuf_Any** val) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_route_v3_Route_typed_per_filter_config_next(const envoy_config_route_v3_Route* msg, upb_StringView* key, const struct google_protobuf_Any** val,
                           size_t* iter) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_route_v3_Route_typed_per_filter_config_upb_map(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_route_v3_Route_typed_per_filter_config_mutable_upb_map(envoy_config_route_v3_Route* msg, upb_Arena* a) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Any*), a);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_name(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_Route_name(const envoy_config_route_v3_Route* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {14, UPB_SIZE(60, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_Route_clear_tracing(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 112), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_Tracing* envoy_config_route_v3_Route_tracing(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_Tracing* default_val = NULL;
  const envoy_config_route_v3_Tracing* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(44, 112), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Tracing_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_tracing(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 112), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_per_request_buffer_limit_bytes(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(48, 120), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_Route_per_request_buffer_limit_bytes(const envoy_config_route_v3_Route* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(48, 120), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_per_request_buffer_limit_bytes(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(48, 120), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_filter_action(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_FilterAction* envoy_config_route_v3_Route_filter_action(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_FilterAction* default_val = NULL;
  const envoy_config_route_v3_FilterAction* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__FilterAction_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_filter_action(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_non_forwarding_action(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_NonForwardingAction* envoy_config_route_v3_Route_non_forwarding_action(const envoy_config_route_v3_Route* msg) {
  const envoy_config_route_v3_NonForwardingAction* default_val = NULL;
  const envoy_config_route_v3_NonForwardingAction* ret;
  const upb_MiniTableField field = {18, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__NonForwardingAction_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Route_has_non_forwarding_action(const envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Route_clear_stat_prefix(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_Route_stat_prefix(const envoy_config_route_v3_Route* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {19, UPB_SIZE(68, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_Route_set_match(envoy_config_route_v3_Route *msg, envoy_config_route_v3_RouteMatch* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteMatch* envoy_config_route_v3_Route_mutable_match(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteMatch* sub = (struct envoy_config_route_v3_RouteMatch*)envoy_config_route_v3_Route_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteMatch*)_upb_Message_New(&envoy__config__route__v3__RouteMatch_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_route(envoy_config_route_v3_Route *msg, envoy_config_route_v3_RouteAction* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction* envoy_config_route_v3_Route_mutable_route(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction* sub = (struct envoy_config_route_v3_RouteAction*)envoy_config_route_v3_Route_route(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction*)_upb_Message_New(&envoy__config__route__v3__RouteAction_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_route(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_redirect(envoy_config_route_v3_Route *msg, envoy_config_route_v3_RedirectAction* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RedirectAction_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RedirectAction* envoy_config_route_v3_Route_mutable_redirect(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RedirectAction* sub = (struct envoy_config_route_v3_RedirectAction*)envoy_config_route_v3_Route_redirect(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RedirectAction*)_upb_Message_New(&envoy__config__route__v3__RedirectAction_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_redirect(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_metadata(envoy_config_route_v3_Route *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_route_v3_Route_mutable_metadata(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_route_v3_Route_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_decorator(envoy_config_route_v3_Route *msg, envoy_config_route_v3_Decorator* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Decorator_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_Decorator* envoy_config_route_v3_Route_mutable_decorator(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_Decorator* sub = (struct envoy_config_route_v3_Decorator*)envoy_config_route_v3_Route_decorator(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_Decorator*)_upb_Message_New(&envoy__config__route__v3__Decorator_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_decorator(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_direct_response(envoy_config_route_v3_Route *msg, envoy_config_route_v3_DirectResponseAction* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__DirectResponseAction_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_DirectResponseAction* envoy_config_route_v3_Route_mutable_direct_response(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_DirectResponseAction* sub = (struct envoy_config_route_v3_DirectResponseAction*)envoy_config_route_v3_Route_direct_response(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_DirectResponseAction*)_upb_Message_New(&envoy__config__route__v3__DirectResponseAction_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_direct_response(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_Route_mutable_request_headers_to_add(envoy_config_route_v3_Route* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_Route_resize_request_headers_to_add(envoy_config_route_v3_Route* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_route_v3_Route_add_request_headers_to_add(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_Route_mutable_response_headers_to_add(envoy_config_route_v3_Route* msg, size_t* size) {
  upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_Route_resize_response_headers_to_add(envoy_config_route_v3_Route* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_route_v3_Route_add_response_headers_to_add(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_route_v3_Route_mutable_response_headers_to_remove(envoy_config_route_v3_Route* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_Route_resize_response_headers_to_remove(envoy_config_route_v3_Route* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_Route_add_response_headers_to_remove(envoy_config_route_v3_Route* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_route_v3_Route_mutable_request_headers_to_remove(envoy_config_route_v3_Route* msg, size_t* size) {
  upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_Route_resize_request_headers_to_remove(envoy_config_route_v3_Route* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_Route_add_request_headers_to_remove(envoy_config_route_v3_Route* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_Route_typed_per_filter_config_clear(envoy_config_route_v3_Route* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_route_v3_Route_typed_per_filter_config_set(envoy_config_route_v3_Route* msg, upb_StringView key, struct google_protobuf_Any* val, upb_Arena* a) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_route_v3_Route_typed_per_filter_config_delete(envoy_config_route_v3_Route* msg, upb_StringView key) {
  const upb_MiniTableField field = {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_config_route_v3_Route_set_name(envoy_config_route_v3_Route *msg, upb_StringView value) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_Route_set_tracing(envoy_config_route_v3_Route *msg, envoy_config_route_v3_Tracing* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 112), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__Tracing_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_Tracing* envoy_config_route_v3_Route_mutable_tracing(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_Tracing* sub = (struct envoy_config_route_v3_Tracing*)envoy_config_route_v3_Route_tracing(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_Tracing*)_upb_Message_New(&envoy__config__route__v3__Tracing_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_tracing(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_per_request_buffer_limit_bytes(envoy_config_route_v3_Route *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(48, 120), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_Route_mutable_per_request_buffer_limit_bytes(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_Route_per_request_buffer_limit_bytes(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_per_request_buffer_limit_bytes(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_filter_action(envoy_config_route_v3_Route *msg, envoy_config_route_v3_FilterAction* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__FilterAction_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_FilterAction* envoy_config_route_v3_Route_mutable_filter_action(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_FilterAction* sub = (struct envoy_config_route_v3_FilterAction*)envoy_config_route_v3_Route_filter_action(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_FilterAction*)_upb_Message_New(&envoy__config__route__v3__FilterAction_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_filter_action(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_non_forwarding_action(envoy_config_route_v3_Route *msg, envoy_config_route_v3_NonForwardingAction* value) {
  const upb_MiniTableField field = {18, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__NonForwardingAction_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_NonForwardingAction* envoy_config_route_v3_Route_mutable_non_forwarding_action(envoy_config_route_v3_Route* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_NonForwardingAction* sub = (struct envoy_config_route_v3_NonForwardingAction*)envoy_config_route_v3_Route_non_forwarding_action(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_NonForwardingAction*)_upb_Message_New(&envoy__config__route__v3__NonForwardingAction_msg_init, arena);
    if (sub) envoy_config_route_v3_Route_set_non_forwarding_action(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Route_set_stat_prefix(envoy_config_route_v3_Route *msg, upb_StringView value) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_WeightedCluster* envoy_config_route_v3_WeightedCluster_new(upb_Arena* arena) {
  return (envoy_config_route_v3_WeightedCluster*)_upb_Message_New(&envoy__config__route__v3__WeightedCluster_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_WeightedCluster* envoy_config_route_v3_WeightedCluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_WeightedCluster* ret = envoy_config_route_v3_WeightedCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__WeightedCluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_WeightedCluster* envoy_config_route_v3_WeightedCluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_WeightedCluster* ret = envoy_config_route_v3_WeightedCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__WeightedCluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_WeightedCluster_serialize(const envoy_config_route_v3_WeightedCluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__WeightedCluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_WeightedCluster_serialize_ex(const envoy_config_route_v3_WeightedCluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__WeightedCluster_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_WeightedCluster_random_value_specifier_header_name = 4,
  envoy_config_route_v3_WeightedCluster_random_value_specifier_NOT_SET = 0
} envoy_config_route_v3_WeightedCluster_random_value_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_WeightedCluster_random_value_specifier_oneofcases envoy_config_route_v3_WeightedCluster_random_value_specifier_case(const envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_WeightedCluster_random_value_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_clear_random_value_specifier(envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__WeightedCluster_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_clear_clusters(envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_WeightedCluster_ClusterWeight* const* envoy_config_route_v3_WeightedCluster_clusters(const envoy_config_route_v3_WeightedCluster* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_WeightedCluster_ClusterWeight* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_WeightedCluster_clusters_upb_array(const envoy_config_route_v3_WeightedCluster* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_WeightedCluster_clusters_mutable_upb_array(envoy_config_route_v3_WeightedCluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_clear_runtime_key_prefix(envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_WeightedCluster_runtime_key_prefix(const envoy_config_route_v3_WeightedCluster* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_clear_total_weight(envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_WeightedCluster_total_weight(const envoy_config_route_v3_WeightedCluster* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_has_total_weight(const envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_clear_header_name(envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_WeightedCluster_header_name(const envoy_config_route_v3_WeightedCluster* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_has_header_name(const envoy_config_route_v3_WeightedCluster* msg) {
  const upb_MiniTableField field = {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE envoy_config_route_v3_WeightedCluster_ClusterWeight** envoy_config_route_v3_WeightedCluster_mutable_clusters(envoy_config_route_v3_WeightedCluster* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_WeightedCluster_ClusterWeight**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_WeightedCluster_ClusterWeight** envoy_config_route_v3_WeightedCluster_resize_clusters(envoy_config_route_v3_WeightedCluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_WeightedCluster_ClusterWeight**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_WeightedCluster_ClusterWeight* envoy_config_route_v3_WeightedCluster_add_clusters(envoy_config_route_v3_WeightedCluster* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_WeightedCluster_ClusterWeight* sub = (struct envoy_config_route_v3_WeightedCluster_ClusterWeight*)_upb_Message_New(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_set_runtime_key_prefix(envoy_config_route_v3_WeightedCluster *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_set_total_weight(envoy_config_route_v3_WeightedCluster *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_WeightedCluster_mutable_total_weight(envoy_config_route_v3_WeightedCluster* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_WeightedCluster_total_weight(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_WeightedCluster_set_total_weight(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_set_header_name(envoy_config_route_v3_WeightedCluster *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_WeightedCluster_ClusterWeight* envoy_config_route_v3_WeightedCluster_ClusterWeight_new(upb_Arena* arena) {
  return (envoy_config_route_v3_WeightedCluster_ClusterWeight*)_upb_Message_New(&envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_WeightedCluster_ClusterWeight* envoy_config_route_v3_WeightedCluster_ClusterWeight_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_WeightedCluster_ClusterWeight* ret = envoy_config_route_v3_WeightedCluster_ClusterWeight_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_WeightedCluster_ClusterWeight* envoy_config_route_v3_WeightedCluster_ClusterWeight_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_WeightedCluster_ClusterWeight* ret = envoy_config_route_v3_WeightedCluster_ClusterWeight_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_WeightedCluster_ClusterWeight_serialize(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_WeightedCluster_ClusterWeight_serialize_ex(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_specifier_host_rewrite_literal = 11,
  envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_specifier_NOT_SET = 0
} envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_specifier_oneofcases envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_specifier_case(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_host_rewrite_specifier(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_name(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_WeightedCluster_ClusterWeight_name(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_weight(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_WeightedCluster_ClusterWeight_weight(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_has_weight(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_metadata_match(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_route_v3_WeightedCluster_ClusterWeight_metadata_match(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_has_metadata_match(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_request_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_route_v3_WeightedCluster_ClusterWeight_request_headers_to_add(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_request_headers_to_add_upb_array(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_request_headers_to_add_mutable_upb_array(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_response_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HeaderValueOption* const* envoy_config_route_v3_WeightedCluster_ClusterWeight_response_headers_to_add(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_response_headers_to_add_upb_array(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_response_headers_to_add_mutable_upb_array(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValueOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_response_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_WeightedCluster_ClusterWeight_response_headers_to_remove(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_response_headers_to_remove_upb_array(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_response_headers_to_remove_mutable_upb_array(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_request_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_WeightedCluster_ClusterWeight_request_headers_to_remove(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_request_headers_to_remove_upb_array(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_WeightedCluster_ClusterWeight_request_headers_to_remove_mutable_upb_array(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_typed_per_filter_config(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_size(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_get(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_StringView key, struct google_protobuf_Any** val) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_next(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_StringView* key, const struct google_protobuf_Any** val,
                           size_t* iter) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_upb_map(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_mutable_upb_map(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_Arena* a) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Any*), a);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_host_rewrite_literal(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_WeightedCluster_ClusterWeight_host_rewrite_literal(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_has_host_rewrite_literal(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_clear_cluster_header(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(52, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_WeightedCluster_ClusterWeight_cluster_header(const envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {12, UPB_SIZE(52, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_set_name(envoy_config_route_v3_WeightedCluster_ClusterWeight *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_set_weight(envoy_config_route_v3_WeightedCluster_ClusterWeight *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_WeightedCluster_ClusterWeight_mutable_weight(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_WeightedCluster_ClusterWeight_weight(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_WeightedCluster_ClusterWeight_set_weight(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_set_metadata_match(envoy_config_route_v3_WeightedCluster_ClusterWeight *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_route_v3_WeightedCluster_ClusterWeight_mutable_metadata_match(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_route_v3_WeightedCluster_ClusterWeight_metadata_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_route_v3_WeightedCluster_ClusterWeight_set_metadata_match(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_WeightedCluster_ClusterWeight_mutable_request_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_WeightedCluster_ClusterWeight_resize_request_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_route_v3_WeightedCluster_ClusterWeight_add_request_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_WeightedCluster_ClusterWeight_mutable_response_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption** envoy_config_route_v3_WeightedCluster_ClusterWeight_resize_response_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HeaderValueOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValueOption* envoy_config_route_v3_WeightedCluster_ClusterWeight_add_response_headers_to_add(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_route_v3_WeightedCluster_ClusterWeight_mutable_response_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_WeightedCluster_ClusterWeight_resize_response_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_add_response_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_route_v3_WeightedCluster_ClusterWeight_mutable_request_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_WeightedCluster_ClusterWeight_resize_request_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_add_request_headers_to_remove(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_clear(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_set(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_StringView key, struct google_protobuf_Any* val, upb_Arena* a) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_delete(envoy_config_route_v3_WeightedCluster_ClusterWeight* msg, upb_StringView key) {
  const upb_MiniTableField field = {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_set_host_rewrite_literal(envoy_config_route_v3_WeightedCluster_ClusterWeight *msg, upb_StringView value) {
  const upb_MiniTableField field = {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_WeightedCluster_ClusterWeight_set_cluster_header(envoy_config_route_v3_WeightedCluster_ClusterWeight *msg, upb_StringView value) {
  const upb_MiniTableField field = {12, UPB_SIZE(52, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_ClusterSpecifierPlugin* envoy_config_route_v3_ClusterSpecifierPlugin_new(upb_Arena* arena) {
  return (envoy_config_route_v3_ClusterSpecifierPlugin*)_upb_Message_New(&envoy__config__route__v3__ClusterSpecifierPlugin_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_ClusterSpecifierPlugin* envoy_config_route_v3_ClusterSpecifierPlugin_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_ClusterSpecifierPlugin* ret = envoy_config_route_v3_ClusterSpecifierPlugin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_ClusterSpecifierPlugin* envoy_config_route_v3_ClusterSpecifierPlugin_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_ClusterSpecifierPlugin* ret = envoy_config_route_v3_ClusterSpecifierPlugin_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_ClusterSpecifierPlugin_serialize(const envoy_config_route_v3_ClusterSpecifierPlugin* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_ClusterSpecifierPlugin_serialize_ex(const envoy_config_route_v3_ClusterSpecifierPlugin* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_ClusterSpecifierPlugin_clear_extension(envoy_config_route_v3_ClusterSpecifierPlugin* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_ClusterSpecifierPlugin_extension(const envoy_config_route_v3_ClusterSpecifierPlugin* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_ClusterSpecifierPlugin_has_extension(const envoy_config_route_v3_ClusterSpecifierPlugin* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_ClusterSpecifierPlugin_clear_is_optional(envoy_config_route_v3_ClusterSpecifierPlugin* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_ClusterSpecifierPlugin_is_optional(const envoy_config_route_v3_ClusterSpecifierPlugin* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_ClusterSpecifierPlugin_set_extension(envoy_config_route_v3_ClusterSpecifierPlugin *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_ClusterSpecifierPlugin_mutable_extension(envoy_config_route_v3_ClusterSpecifierPlugin* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_route_v3_ClusterSpecifierPlugin_extension(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_ClusterSpecifierPlugin_set_extension(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_ClusterSpecifierPlugin_set_is_optional(envoy_config_route_v3_ClusterSpecifierPlugin *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteMatch* envoy_config_route_v3_RouteMatch_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteMatch*)_upb_Message_New(&envoy__config__route__v3__RouteMatch_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteMatch* envoy_config_route_v3_RouteMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch* ret = envoy_config_route_v3_RouteMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteMatch* envoy_config_route_v3_RouteMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch* ret = envoy_config_route_v3_RouteMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_serialize(const envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_serialize_ex(const envoy_config_route_v3_RouteMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RouteMatch_path_specifier_prefix = 1,
  envoy_config_route_v3_RouteMatch_path_specifier_path = 2,
  envoy_config_route_v3_RouteMatch_path_specifier_safe_regex = 10,
  envoy_config_route_v3_RouteMatch_path_specifier_connect_matcher = 12,
  envoy_config_route_v3_RouteMatch_path_specifier_path_separated_prefix = 14,
  envoy_config_route_v3_RouteMatch_path_specifier_path_match_policy = 15,
  envoy_config_route_v3_RouteMatch_path_specifier_NOT_SET = 0
} envoy_config_route_v3_RouteMatch_path_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RouteMatch_path_specifier_oneofcases envoy_config_route_v3_RouteMatch_path_specifier_case(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteMatch_path_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_path_specifier(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_prefix(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteMatch_prefix(const envoy_config_route_v3_RouteMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_prefix(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_path(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteMatch_path(const envoy_config_route_v3_RouteMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_path(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_case_sensitive(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteMatch_case_sensitive(const envoy_config_route_v3_RouteMatch* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_case_sensitive(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_headers(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HeaderMatcher* const* envoy_config_route_v3_RouteMatch_headers(const envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteMatch_headers_upb_array(const envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteMatch_headers_mutable_upb_array(envoy_config_route_v3_RouteMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_query_parameters(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_QueryParameterMatcher* const* envoy_config_route_v3_RouteMatch_query_parameters(const envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_QueryParameterMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteMatch_query_parameters_upb_array(const envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteMatch_query_parameters_mutable_upb_array(envoy_config_route_v3_RouteMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_grpc(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* envoy_config_route_v3_RouteMatch_grpc(const envoy_config_route_v3_RouteMatch* msg) {
  const envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* default_val = NULL;
  const envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_grpc(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_runtime_fraction(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_RouteMatch_runtime_fraction(const envoy_config_route_v3_RouteMatch* msg) {
  const struct envoy_config_core_v3_RuntimeFractionalPercent* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeFractionalPercent* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(28, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_runtime_fraction(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_safe_regex(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatcher* envoy_config_route_v3_RouteMatch_safe_regex(const envoy_config_route_v3_RouteMatch* msg) {
  const struct envoy_type_matcher_v3_RegexMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatcher* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_safe_regex(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_tls_context(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 72), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* envoy_config_route_v3_RouteMatch_tls_context(const envoy_config_route_v3_RouteMatch* msg) {
  const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* default_val = NULL;
  const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(32, 72), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_tls_context(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 72), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_connect_matcher(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteMatch_ConnectMatcher* envoy_config_route_v3_RouteMatch_connect_matcher(const envoy_config_route_v3_RouteMatch* msg) {
  const envoy_config_route_v3_RouteMatch_ConnectMatcher* default_val = NULL;
  const envoy_config_route_v3_RouteMatch_ConnectMatcher* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_connect_matcher(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_dynamic_metadata(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_MetadataMatcher* const* envoy_config_route_v3_RouteMatch_dynamic_metadata(const envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_matcher_v3_MetadataMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteMatch_dynamic_metadata_upb_array(const envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteMatch_dynamic_metadata_mutable_upb_array(envoy_config_route_v3_RouteMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_path_separated_prefix(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteMatch_path_separated_prefix(const envoy_config_route_v3_RouteMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {14, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_path_separated_prefix(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_clear_path_match_policy(envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RouteMatch_path_match_policy(const envoy_config_route_v3_RouteMatch* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_has_path_match_policy(const envoy_config_route_v3_RouteMatch* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteMatch_set_prefix(envoy_config_route_v3_RouteMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_path(envoy_config_route_v3_RouteMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_case_sensitive(envoy_config_route_v3_RouteMatch *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteMatch_mutable_case_sensitive(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteMatch_case_sensitive(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_case_sensitive(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RouteMatch_mutable_headers(envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RouteMatch_resize_headers(envoy_config_route_v3_RouteMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_RouteMatch_add_headers(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher** envoy_config_route_v3_RouteMatch_mutable_query_parameters(envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_QueryParameterMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher** envoy_config_route_v3_RouteMatch_resize_query_parameters(envoy_config_route_v3_RouteMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_QueryParameterMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_QueryParameterMatcher* envoy_config_route_v3_RouteMatch_add_query_parameters(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_QueryParameterMatcher* sub = (struct envoy_config_route_v3_QueryParameterMatcher*)_upb_Message_New(&envoy__config__route__v3__QueryParameterMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_grpc(envoy_config_route_v3_RouteMatch *msg, envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* envoy_config_route_v3_RouteMatch_mutable_grpc(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* sub = (struct envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions*)envoy_config_route_v3_RouteMatch_grpc(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions*)_upb_Message_New(&envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_grpc(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_runtime_fraction(envoy_config_route_v3_RouteMatch *msg, struct envoy_config_core_v3_RuntimeFractionalPercent* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_RouteMatch_mutable_runtime_fraction(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeFractionalPercent* sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)envoy_config_route_v3_RouteMatch_runtime_fraction(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)_upb_Message_New(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_runtime_fraction(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_safe_regex(envoy_config_route_v3_RouteMatch *msg, struct envoy_type_matcher_v3_RegexMatcher* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatcher* envoy_config_route_v3_RouteMatch_mutable_safe_regex(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatcher* sub = (struct envoy_type_matcher_v3_RegexMatcher*)envoy_config_route_v3_RouteMatch_safe_regex(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatcher*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatcher_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_safe_regex(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_tls_context(envoy_config_route_v3_RouteMatch *msg, envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(32, 72), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* envoy_config_route_v3_RouteMatch_mutable_tls_context(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* sub = (struct envoy_config_route_v3_RouteMatch_TlsContextMatchOptions*)envoy_config_route_v3_RouteMatch_tls_context(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteMatch_TlsContextMatchOptions*)_upb_Message_New(&envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_tls_context(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_connect_matcher(envoy_config_route_v3_RouteMatch *msg, envoy_config_route_v3_RouteMatch_ConnectMatcher* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteMatch_ConnectMatcher* envoy_config_route_v3_RouteMatch_mutable_connect_matcher(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteMatch_ConnectMatcher* sub = (struct envoy_config_route_v3_RouteMatch_ConnectMatcher*)envoy_config_route_v3_RouteMatch_connect_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteMatch_ConnectMatcher*)_upb_Message_New(&envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_connect_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher** envoy_config_route_v3_RouteMatch_mutable_dynamic_metadata(envoy_config_route_v3_RouteMatch* msg, size_t* size) {
  upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_matcher_v3_MetadataMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher** envoy_config_route_v3_RouteMatch_resize_dynamic_metadata(envoy_config_route_v3_RouteMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_matcher_v3_MetadataMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_route_v3_RouteMatch_add_dynamic_metadata(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_matcher_v3_MetadataMatcher* sub = (struct envoy_type_matcher_v3_MetadataMatcher*)_upb_Message_New(&envoy__type__matcher__v3__MetadataMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_path_separated_prefix(envoy_config_route_v3_RouteMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {14, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_set_path_match_policy(envoy_config_route_v3_RouteMatch *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RouteMatch_mutable_path_match_policy(envoy_config_route_v3_RouteMatch* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_route_v3_RouteMatch_path_match_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_set_path_match_policy(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions*)_upb_Message_New(&envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* ret = envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* ret = envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_serialize(const envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions_serialize_ex(const envoy_config_route_v3_RouteMatch_GrpcRouteMatchOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteMatch_TlsContextMatchOptions*)_upb_Message_New(&envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* ret = envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* ret = envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_serialize(const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_serialize_ex(const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_clear_presented(envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_presented(const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_has_presented(const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_clear_validated(envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_validated(const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_has_validated(const envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_set_presented(envoy_config_route_v3_RouteMatch_TlsContextMatchOptions *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_mutable_presented(envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_presented(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_set_presented(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_set_validated(envoy_config_route_v3_RouteMatch_TlsContextMatchOptions *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_mutable_validated(envoy_config_route_v3_RouteMatch_TlsContextMatchOptions* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_validated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteMatch_TlsContextMatchOptions_set_validated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteMatch_ConnectMatcher* envoy_config_route_v3_RouteMatch_ConnectMatcher_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteMatch_ConnectMatcher*)_upb_Message_New(&envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteMatch_ConnectMatcher* envoy_config_route_v3_RouteMatch_ConnectMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch_ConnectMatcher* ret = envoy_config_route_v3_RouteMatch_ConnectMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteMatch_ConnectMatcher* envoy_config_route_v3_RouteMatch_ConnectMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteMatch_ConnectMatcher* ret = envoy_config_route_v3_RouteMatch_ConnectMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_ConnectMatcher_serialize(const envoy_config_route_v3_RouteMatch_ConnectMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteMatch_ConnectMatcher_serialize_ex(const envoy_config_route_v3_RouteMatch_ConnectMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_CorsPolicy_new(upb_Arena* arena) {
  return (envoy_config_route_v3_CorsPolicy*)_upb_Message_New(&envoy__config__route__v3__CorsPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_CorsPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_CorsPolicy* ret = envoy_config_route_v3_CorsPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__CorsPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_CorsPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_CorsPolicy* ret = envoy_config_route_v3_CorsPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__CorsPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_CorsPolicy_serialize(const envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__CorsPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_CorsPolicy_serialize_ex(const envoy_config_route_v3_CorsPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__CorsPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_CorsPolicy_enabled_specifier_filter_enabled = 9,
  envoy_config_route_v3_CorsPolicy_enabled_specifier_NOT_SET = 0
} envoy_config_route_v3_CorsPolicy_enabled_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_CorsPolicy_enabled_specifier_oneofcases envoy_config_route_v3_CorsPolicy_enabled_specifier_case(const envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_CorsPolicy_enabled_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_enabled_specifier(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__CorsPolicy_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_allow_methods(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_CorsPolicy_allow_methods(const envoy_config_route_v3_CorsPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_allow_headers(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_CorsPolicy_allow_headers(const envoy_config_route_v3_CorsPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_expose_headers(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_CorsPolicy_expose_headers(const envoy_config_route_v3_CorsPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_max_age(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {5, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_CorsPolicy_max_age(const envoy_config_route_v3_CorsPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_allow_credentials(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_CorsPolicy_allow_credentials(const envoy_config_route_v3_CorsPolicy* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_CorsPolicy_has_allow_credentials(const envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_filter_enabled(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_CorsPolicy_filter_enabled(const envoy_config_route_v3_CorsPolicy* msg) {
  const struct envoy_config_core_v3_RuntimeFractionalPercent* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeFractionalPercent* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_CorsPolicy_has_filter_enabled(const envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_shadow_enabled(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(16, 88), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_CorsPolicy_shadow_enabled(const envoy_config_route_v3_CorsPolicy* msg) {
  const struct envoy_config_core_v3_RuntimeFractionalPercent* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeFractionalPercent* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(16, 88), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_CorsPolicy_has_shadow_enabled(const envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(16, 88), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_allow_origin_string_match(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* const* envoy_config_route_v3_CorsPolicy_allow_origin_string_match(const envoy_config_route_v3_CorsPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_type_matcher_v3_StringMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_CorsPolicy_allow_origin_string_match_upb_array(const envoy_config_route_v3_CorsPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_CorsPolicy_allow_origin_string_match_mutable_upb_array(envoy_config_route_v3_CorsPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_allow_private_network_access(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_CorsPolicy_allow_private_network_access(const envoy_config_route_v3_CorsPolicy* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(24, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_CorsPolicy_has_allow_private_network_access(const envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_clear_forward_not_matching_preflights(envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_CorsPolicy_forward_not_matching_preflights(const envoy_config_route_v3_CorsPolicy* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(28, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_CorsPolicy_has_forward_not_matching_preflights(const envoy_config_route_v3_CorsPolicy* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_allow_methods(envoy_config_route_v3_CorsPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_allow_headers(envoy_config_route_v3_CorsPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_expose_headers(envoy_config_route_v3_CorsPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_max_age(envoy_config_route_v3_CorsPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_allow_credentials(envoy_config_route_v3_CorsPolicy *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_CorsPolicy_mutable_allow_credentials(envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_CorsPolicy_allow_credentials(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_CorsPolicy_set_allow_credentials(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_filter_enabled(envoy_config_route_v3_CorsPolicy *msg, struct envoy_config_core_v3_RuntimeFractionalPercent* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_CorsPolicy_mutable_filter_enabled(envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeFractionalPercent* sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)envoy_config_route_v3_CorsPolicy_filter_enabled(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)_upb_Message_New(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_CorsPolicy_set_filter_enabled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_shadow_enabled(envoy_config_route_v3_CorsPolicy *msg, struct envoy_config_core_v3_RuntimeFractionalPercent* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(16, 88), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_CorsPolicy_mutable_shadow_enabled(envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeFractionalPercent* sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)envoy_config_route_v3_CorsPolicy_shadow_enabled(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)_upb_Message_New(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_CorsPolicy_set_shadow_enabled(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher** envoy_config_route_v3_CorsPolicy_mutable_allow_origin_string_match(envoy_config_route_v3_CorsPolicy* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_type_matcher_v3_StringMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher** envoy_config_route_v3_CorsPolicy_resize_allow_origin_string_match(envoy_config_route_v3_CorsPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_matcher_v3_StringMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_route_v3_CorsPolicy_add_allow_origin_string_match(envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_allow_private_network_access(envoy_config_route_v3_CorsPolicy *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_CorsPolicy_mutable_allow_private_network_access(envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_CorsPolicy_allow_private_network_access(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_CorsPolicy_set_allow_private_network_access(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_CorsPolicy_set_forward_not_matching_preflights(envoy_config_route_v3_CorsPolicy *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_CorsPolicy_mutable_forward_not_matching_preflights(envoy_config_route_v3_CorsPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_CorsPolicy_forward_not_matching_preflights(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_CorsPolicy_set_forward_not_matching_preflights(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteAction* envoy_config_route_v3_RouteAction_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction*)_upb_Message_New(&envoy__config__route__v3__RouteAction_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction* envoy_config_route_v3_RouteAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction* ret = envoy_config_route_v3_RouteAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction* envoy_config_route_v3_RouteAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction* ret = envoy_config_route_v3_RouteAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_serialize(const envoy_config_route_v3_RouteAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_serialize_ex(const envoy_config_route_v3_RouteAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RouteAction_cluster_specifier_cluster = 1,
  envoy_config_route_v3_RouteAction_cluster_specifier_cluster_header = 2,
  envoy_config_route_v3_RouteAction_cluster_specifier_weighted_clusters = 3,
  envoy_config_route_v3_RouteAction_cluster_specifier_cluster_specifier_plugin = 37,
  envoy_config_route_v3_RouteAction_cluster_specifier_inline_cluster_specifier_plugin = 39,
  envoy_config_route_v3_RouteAction_cluster_specifier_NOT_SET = 0
} envoy_config_route_v3_RouteAction_cluster_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RouteAction_cluster_specifier_oneofcases envoy_config_route_v3_RouteAction_cluster_specifier_case(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_cluster_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_cluster_specifier(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction_msg_init, &field);
}
typedef enum {
  envoy_config_route_v3_RouteAction_host_rewrite_specifier_host_rewrite_literal = 6,
  envoy_config_route_v3_RouteAction_host_rewrite_specifier_auto_host_rewrite = 7,
  envoy_config_route_v3_RouteAction_host_rewrite_specifier_host_rewrite_header = 29,
  envoy_config_route_v3_RouteAction_host_rewrite_specifier_host_rewrite_path_regex = 35,
  envoy_config_route_v3_RouteAction_host_rewrite_specifier_NOT_SET = 0
} envoy_config_route_v3_RouteAction_host_rewrite_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RouteAction_host_rewrite_specifier_oneofcases envoy_config_route_v3_RouteAction_host_rewrite_specifier_case(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_host_rewrite_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_host_rewrite_specifier(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_cluster(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_cluster(const envoy_config_route_v3_RouteAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_cluster(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_cluster_header(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_cluster_header(const envoy_config_route_v3_RouteAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_cluster_header(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_weighted_clusters(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_WeightedCluster* envoy_config_route_v3_RouteAction_weighted_clusters(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_WeightedCluster* default_val = NULL;
  const envoy_config_route_v3_WeightedCluster* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_weighted_clusters(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_metadata_match(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 80), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_route_v3_RouteAction_metadata_match(const envoy_config_route_v3_RouteAction* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 80), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_metadata_match(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 80), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_prefix_rewrite(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(112, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_prefix_rewrite(const envoy_config_route_v3_RouteAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(112, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_host_rewrite_literal(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_host_rewrite_literal(const envoy_config_route_v3_RouteAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_host_rewrite_literal(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_auto_host_rewrite(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_auto_host_rewrite(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_auto_host_rewrite(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_timeout(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 88), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_timeout(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(16, 88), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_timeout(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 88), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_retry_policy(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_RouteAction_retry_policy(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_RetryPolicy* default_val = NULL;
  const envoy_config_route_v3_RetryPolicy* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_retry_policy(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_priority(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_RouteAction_priority(const envoy_config_route_v3_RouteAction* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {11, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_rate_limits(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit* const* envoy_config_route_v3_RouteAction_rate_limits(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RateLimit* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteAction_rate_limits_upb_array(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteAction_rate_limits_mutable_upb_array(envoy_config_route_v3_RouteAction* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_include_vh_rate_limits(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(32, 112), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_include_vh_rate_limits(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(32, 112), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_include_vh_rate_limits(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(32, 112), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_hash_policy(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy* const* envoy_config_route_v3_RouteAction_hash_policy(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RouteAction_HashPolicy* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteAction_hash_policy_upb_array(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteAction_hash_policy_mutable_upb_array(envoy_config_route_v3_RouteAction* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_cors(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(40, 128), 68, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_RouteAction_cors(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_CorsPolicy* default_val = NULL;
  const envoy_config_route_v3_CorsPolicy* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(40, 128), 68, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__CorsPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_cors(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(40, 128), 68, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_cluster_not_found_response_code(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_RouteAction_cluster_not_found_response_code(const envoy_config_route_v3_RouteAction* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {20, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_max_grpc_timeout(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(48, 136), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_max_grpc_timeout(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {23, UPB_SIZE(48, 136), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_max_grpc_timeout(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(48, 136), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_idle_timeout(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(52, 144), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_idle_timeout(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {24, UPB_SIZE(52, 144), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_idle_timeout(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(52, 144), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_upgrade_configs(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_UpgradeConfig* const* envoy_config_route_v3_RouteAction_upgrade_configs(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RouteAction_UpgradeConfig* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteAction_upgrade_configs_upb_array(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteAction_upgrade_configs_mutable_upb_array(envoy_config_route_v3_RouteAction* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_internal_redirect_action(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(60, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_RouteAction_internal_redirect_action(const envoy_config_route_v3_RouteAction* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {26, UPB_SIZE(60, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_hedge_policy(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(64, 160), 71, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_RouteAction_hedge_policy(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_HedgePolicy* default_val = NULL;
  const envoy_config_route_v3_HedgePolicy* ret;
  const upb_MiniTableField field = {27, UPB_SIZE(64, 160), 71, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HedgePolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_hedge_policy(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(64, 160), 71, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_grpc_timeout_offset(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(68, 168), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_grpc_timeout_offset(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {28, UPB_SIZE(68, 168), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_grpc_timeout_offset(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(68, 168), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_host_rewrite_header(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_host_rewrite_header(const envoy_config_route_v3_RouteAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {29, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_host_rewrite_header(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_request_mirror_policies(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* const* envoy_config_route_v3_RouteAction_request_mirror_policies(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteAction_request_mirror_policies_upb_array(const envoy_config_route_v3_RouteAction* msg, size_t* size) {
  const upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteAction_request_mirror_policies_mutable_upb_array(envoy_config_route_v3_RouteAction* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_max_internal_redirects(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(76, 184), 73, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_RouteAction_max_internal_redirects(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {31, UPB_SIZE(76, 184), 73, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_max_internal_redirects(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(76, 184), 73, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_regex_rewrite(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(80, 192), 74, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RouteAction_regex_rewrite(const envoy_config_route_v3_RouteAction* msg) {
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* ret;
  const upb_MiniTableField field = {32, UPB_SIZE(80, 192), 74, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_regex_rewrite(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(80, 192), 74, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_retry_policy_typed_config(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(84, 200), 75, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_route_v3_RouteAction_retry_policy_typed_config(const envoy_config_route_v3_RouteAction* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {33, UPB_SIZE(84, 200), 75, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_retry_policy_typed_config(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(84, 200), 75, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_internal_redirect_policy(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(88, 208), 76, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_InternalRedirectPolicy* envoy_config_route_v3_RouteAction_internal_redirect_policy(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_InternalRedirectPolicy* default_val = NULL;
  const envoy_config_route_v3_InternalRedirectPolicy* ret;
  const upb_MiniTableField field = {34, UPB_SIZE(88, 208), 76, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__InternalRedirectPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_internal_redirect_policy(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(88, 208), 76, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_host_rewrite_path_regex(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RouteAction_host_rewrite_path_regex(const envoy_config_route_v3_RouteAction* msg) {
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* ret;
  const upb_MiniTableField field = {35, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_host_rewrite_path_regex(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {35, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_max_stream_duration(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(92, 216), 77, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_MaxStreamDuration* envoy_config_route_v3_RouteAction_max_stream_duration(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_RouteAction_MaxStreamDuration* default_val = NULL;
  const envoy_config_route_v3_RouteAction_MaxStreamDuration* ret;
  const upb_MiniTableField field = {36, UPB_SIZE(92, 216), 77, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_max_stream_duration(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(92, 216), 77, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_cluster_specifier_plugin(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {37, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_cluster_specifier_plugin(const envoy_config_route_v3_RouteAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {37, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_cluster_specifier_plugin(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {37, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_append_x_forwarded_host(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {38, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_append_x_forwarded_host(const envoy_config_route_v3_RouteAction* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {38, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_inline_cluster_specifier_plugin(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {39, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_ClusterSpecifierPlugin* envoy_config_route_v3_RouteAction_inline_cluster_specifier_plugin(const envoy_config_route_v3_RouteAction* msg) {
  const envoy_config_route_v3_ClusterSpecifierPlugin* default_val = NULL;
  const envoy_config_route_v3_ClusterSpecifierPlugin* ret;
  const upb_MiniTableField field = {39, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ClusterSpecifierPlugin_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_inline_cluster_specifier_plugin(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {39, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_early_data_policy(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(96, 224), 78, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RouteAction_early_data_policy(const envoy_config_route_v3_RouteAction* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {40, UPB_SIZE(96, 224), 78, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_early_data_policy(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(96, 224), 78, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_clear_path_rewrite_policy(envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(100, 232), 79, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RouteAction_path_rewrite_policy(const envoy_config_route_v3_RouteAction* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {41, UPB_SIZE(100, 232), 79, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_has_path_rewrite_policy(const envoy_config_route_v3_RouteAction* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(100, 232), 79, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteAction_set_cluster(envoy_config_route_v3_RouteAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_cluster_header(envoy_config_route_v3_RouteAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_weighted_clusters(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_WeightedCluster* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__WeightedCluster_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_WeightedCluster* envoy_config_route_v3_RouteAction_mutable_weighted_clusters(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_WeightedCluster* sub = (struct envoy_config_route_v3_WeightedCluster*)envoy_config_route_v3_RouteAction_weighted_clusters(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_WeightedCluster*)_upb_Message_New(&envoy__config__route__v3__WeightedCluster_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_weighted_clusters(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_metadata_match(envoy_config_route_v3_RouteAction *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 80), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_route_v3_RouteAction_mutable_metadata_match(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_route_v3_RouteAction_metadata_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_metadata_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_prefix_rewrite(envoy_config_route_v3_RouteAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(112, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_host_rewrite_literal(envoy_config_route_v3_RouteAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_auto_host_rewrite(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_mutable_auto_host_rewrite(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteAction_auto_host_rewrite(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_auto_host_rewrite(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_timeout(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 88), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_mutable_timeout(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_retry_policy(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_RetryPolicy* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_RouteAction_mutable_retry_policy(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RetryPolicy* sub = (struct envoy_config_route_v3_RetryPolicy*)envoy_config_route_v3_RouteAction_retry_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RetryPolicy*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_retry_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_priority(envoy_config_route_v3_RouteAction *msg, int32_t value) {
  const upb_MiniTableField field = {11, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_route_v3_RateLimit** envoy_config_route_v3_RouteAction_mutable_rate_limits(envoy_config_route_v3_RouteAction* msg, size_t* size) {
  upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RateLimit**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RateLimit** envoy_config_route_v3_RouteAction_resize_rate_limits(envoy_config_route_v3_RouteAction* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RateLimit**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit* envoy_config_route_v3_RouteAction_add_rate_limits(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RateLimit* sub = (struct envoy_config_route_v3_RateLimit*)_upb_Message_New(&envoy__config__route__v3__RateLimit_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_include_vh_rate_limits(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(32, 112), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_mutable_include_vh_rate_limits(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteAction_include_vh_rate_limits(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_include_vh_rate_limits(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy** envoy_config_route_v3_RouteAction_mutable_hash_policy(envoy_config_route_v3_RouteAction* msg, size_t* size) {
  upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RouteAction_HashPolicy**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy** envoy_config_route_v3_RouteAction_resize_hash_policy(envoy_config_route_v3_RouteAction* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_HashPolicy**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy* envoy_config_route_v3_RouteAction_add_hash_policy(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  upb_MiniTableField field = {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RouteAction_HashPolicy* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_cors(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_CorsPolicy* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(40, 128), 68, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__CorsPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_CorsPolicy* envoy_config_route_v3_RouteAction_mutable_cors(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_CorsPolicy* sub = (struct envoy_config_route_v3_CorsPolicy*)envoy_config_route_v3_RouteAction_cors(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_CorsPolicy*)_upb_Message_New(&envoy__config__route__v3__CorsPolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_cors(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_cluster_not_found_response_code(envoy_config_route_v3_RouteAction *msg, int32_t value) {
  const upb_MiniTableField field = {20, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_max_grpc_timeout(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {23, UPB_SIZE(48, 136), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_mutable_max_grpc_timeout(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_max_grpc_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_max_grpc_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_idle_timeout(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {24, UPB_SIZE(52, 144), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_mutable_idle_timeout(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_idle_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_idle_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig** envoy_config_route_v3_RouteAction_mutable_upgrade_configs(envoy_config_route_v3_RouteAction* msg, size_t* size) {
  upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RouteAction_UpgradeConfig**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig** envoy_config_route_v3_RouteAction_resize_upgrade_configs(envoy_config_route_v3_RouteAction* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_UpgradeConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_UpgradeConfig* envoy_config_route_v3_RouteAction_add_upgrade_configs(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  upb_MiniTableField field = {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RouteAction_UpgradeConfig* sub = (struct envoy_config_route_v3_RouteAction_UpgradeConfig*)_upb_Message_New(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_internal_redirect_action(envoy_config_route_v3_RouteAction *msg, int32_t value) {
  const upb_MiniTableField field = {26, UPB_SIZE(60, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_hedge_policy(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_HedgePolicy* value) {
  const upb_MiniTableField field = {27, UPB_SIZE(64, 160), 71, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HedgePolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_RouteAction_mutable_hedge_policy(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_HedgePolicy* sub = (struct envoy_config_route_v3_HedgePolicy*)envoy_config_route_v3_RouteAction_hedge_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_HedgePolicy*)_upb_Message_New(&envoy__config__route__v3__HedgePolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_hedge_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_grpc_timeout_offset(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {28, UPB_SIZE(68, 168), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_mutable_grpc_timeout_offset(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_grpc_timeout_offset(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_grpc_timeout_offset(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_host_rewrite_header(envoy_config_route_v3_RouteAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {29, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy** envoy_config_route_v3_RouteAction_mutable_request_mirror_policies(envoy_config_route_v3_RouteAction* msg, size_t* size) {
  upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RouteAction_RequestMirrorPolicy**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy** envoy_config_route_v3_RouteAction_resize_request_mirror_policies(envoy_config_route_v3_RouteAction* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_RequestMirrorPolicy**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy* envoy_config_route_v3_RouteAction_add_request_mirror_policies(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  upb_MiniTableField field = {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy* sub = (struct envoy_config_route_v3_RouteAction_RequestMirrorPolicy*)_upb_Message_New(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_max_internal_redirects(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {31, UPB_SIZE(76, 184), 73, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_RouteAction_mutable_max_internal_redirects(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_RouteAction_max_internal_redirects(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_max_internal_redirects(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_regex_rewrite(envoy_config_route_v3_RouteAction *msg, struct envoy_type_matcher_v3_RegexMatchAndSubstitute* value) {
  const upb_MiniTableField field = {32, UPB_SIZE(80, 192), 74, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RouteAction_mutable_regex_rewrite(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatchAndSubstitute* sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)envoy_config_route_v3_RouteAction_regex_rewrite(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_regex_rewrite(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_retry_policy_typed_config(envoy_config_route_v3_RouteAction *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {33, UPB_SIZE(84, 200), 75, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_route_v3_RouteAction_mutable_retry_policy_typed_config(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_route_v3_RouteAction_retry_policy_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_retry_policy_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_internal_redirect_policy(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_InternalRedirectPolicy* value) {
  const upb_MiniTableField field = {34, UPB_SIZE(88, 208), 76, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__InternalRedirectPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_InternalRedirectPolicy* envoy_config_route_v3_RouteAction_mutable_internal_redirect_policy(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_InternalRedirectPolicy* sub = (struct envoy_config_route_v3_InternalRedirectPolicy*)envoy_config_route_v3_RouteAction_internal_redirect_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_InternalRedirectPolicy*)_upb_Message_New(&envoy__config__route__v3__InternalRedirectPolicy_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_internal_redirect_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_host_rewrite_path_regex(envoy_config_route_v3_RouteAction *msg, struct envoy_type_matcher_v3_RegexMatchAndSubstitute* value) {
  const upb_MiniTableField field = {35, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RouteAction_mutable_host_rewrite_path_regex(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatchAndSubstitute* sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)envoy_config_route_v3_RouteAction_host_rewrite_path_regex(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_host_rewrite_path_regex(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_max_stream_duration(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_RouteAction_MaxStreamDuration* value) {
  const upb_MiniTableField field = {36, UPB_SIZE(92, 216), 77, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_MaxStreamDuration* envoy_config_route_v3_RouteAction_mutable_max_stream_duration(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_MaxStreamDuration* sub = (struct envoy_config_route_v3_RouteAction_MaxStreamDuration*)envoy_config_route_v3_RouteAction_max_stream_duration(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_MaxStreamDuration*)_upb_Message_New(&envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_max_stream_duration(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_cluster_specifier_plugin(envoy_config_route_v3_RouteAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {37, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_append_x_forwarded_host(envoy_config_route_v3_RouteAction *msg, bool value) {
  const upb_MiniTableField field = {38, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_inline_cluster_specifier_plugin(envoy_config_route_v3_RouteAction *msg, envoy_config_route_v3_ClusterSpecifierPlugin* value) {
  const upb_MiniTableField field = {39, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__ClusterSpecifierPlugin_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_ClusterSpecifierPlugin* envoy_config_route_v3_RouteAction_mutable_inline_cluster_specifier_plugin(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_ClusterSpecifierPlugin* sub = (struct envoy_config_route_v3_ClusterSpecifierPlugin*)envoy_config_route_v3_RouteAction_inline_cluster_specifier_plugin(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_ClusterSpecifierPlugin*)_upb_Message_New(&envoy__config__route__v3__ClusterSpecifierPlugin_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_inline_cluster_specifier_plugin(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_early_data_policy(envoy_config_route_v3_RouteAction *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {40, UPB_SIZE(96, 224), 78, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RouteAction_mutable_early_data_policy(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_route_v3_RouteAction_early_data_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_early_data_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_set_path_rewrite_policy(envoy_config_route_v3_RouteAction *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {41, UPB_SIZE(100, 232), 79, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RouteAction_mutable_path_rewrite_policy(envoy_config_route_v3_RouteAction* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_route_v3_RouteAction_path_rewrite_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_set_path_rewrite_policy(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_RequestMirrorPolicy*)_upb_Message_New(&envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_RequestMirrorPolicy* ret = envoy_config_route_v3_RouteAction_RequestMirrorPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_RequestMirrorPolicy* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_RequestMirrorPolicy* ret = envoy_config_route_v3_RouteAction_RequestMirrorPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_serialize(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_serialize_ex(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_clear_cluster(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_RequestMirrorPolicy_cluster(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_clear_runtime_fraction(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_runtime_fraction(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const struct envoy_config_core_v3_RuntimeFractionalPercent* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeFractionalPercent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_RequestMirrorPolicy_has_runtime_fraction(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_clear_trace_sampled(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_trace_sampled(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_RequestMirrorPolicy_has_trace_sampled(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_clear_cluster_header(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_RequestMirrorPolicy_cluster_header(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_clear_disable_shadow_host_suffix_append(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_RequestMirrorPolicy_disable_shadow_host_suffix_append(const envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_cluster(envoy_config_route_v3_RouteAction_RequestMirrorPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_runtime_fraction(envoy_config_route_v3_RouteAction_RequestMirrorPolicy *msg, struct envoy_config_core_v3_RuntimeFractionalPercent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_mutable_runtime_fraction(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeFractionalPercent* sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)envoy_config_route_v3_RouteAction_RequestMirrorPolicy_runtime_fraction(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeFractionalPercent*)_upb_Message_New(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_runtime_fraction(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_trace_sampled(envoy_config_route_v3_RouteAction_RequestMirrorPolicy *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_RequestMirrorPolicy_mutable_trace_sampled(envoy_config_route_v3_RouteAction_RequestMirrorPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteAction_RequestMirrorPolicy_trace_sampled(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_trace_sampled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_cluster_header(envoy_config_route_v3_RouteAction_RequestMirrorPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_RequestMirrorPolicy_set_disable_shadow_host_suffix_append(envoy_config_route_v3_RouteAction_RequestMirrorPolicy *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy* envoy_config_route_v3_RouteAction_HashPolicy_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy* envoy_config_route_v3_RouteAction_HashPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy* ret = envoy_config_route_v3_RouteAction_HashPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy* envoy_config_route_v3_RouteAction_HashPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy* ret = envoy_config_route_v3_RouteAction_HashPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_serialize(const envoy_config_route_v3_RouteAction_HashPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_header = 1,
  envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_cookie = 2,
  envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_connection_properties = 3,
  envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_query_parameter = 5,
  envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_filter_state = 6,
  envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_NOT_SET = 0
} envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_oneofcases envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_case(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_HashPolicy_policy_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_policy_specifier(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_header(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy_Header* envoy_config_route_v3_RouteAction_HashPolicy_header(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const envoy_config_route_v3_RouteAction_HashPolicy_Header* default_val = NULL;
  const envoy_config_route_v3_RouteAction_HashPolicy_Header* ret;
  const upb_MiniTableField field = {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_has_header(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_cookie(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {2, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* envoy_config_route_v3_RouteAction_HashPolicy_cookie(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* default_val = NULL;
  const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* ret;
  const upb_MiniTableField field = {2, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_has_cookie(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {2, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_connection_properties(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {3, 16, -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* envoy_config_route_v3_RouteAction_HashPolicy_connection_properties(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* default_val = NULL;
  const envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* ret;
  const upb_MiniTableField field = {3, 16, -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_has_connection_properties(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {3, 16, -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_terminal(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_terminal(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_query_parameter(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {5, 16, -13, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* envoy_config_route_v3_RouteAction_HashPolicy_query_parameter(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* default_val = NULL;
  const envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* ret;
  const upb_MiniTableField field = {5, 16, -13, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_has_query_parameter(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {5, 16, -13, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_clear_filter_state(envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {6, 16, -13, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy_FilterState* envoy_config_route_v3_RouteAction_HashPolicy_filter_state(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const envoy_config_route_v3_RouteAction_HashPolicy_FilterState* default_val = NULL;
  const envoy_config_route_v3_RouteAction_HashPolicy_FilterState* ret;
  const upb_MiniTableField field = {6, 16, -13, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_has_filter_state(const envoy_config_route_v3_RouteAction_HashPolicy* msg) {
  const upb_MiniTableField field = {6, 16, -13, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_set_header(envoy_config_route_v3_RouteAction_HashPolicy *msg, envoy_config_route_v3_RouteAction_HashPolicy_Header* value) {
  const upb_MiniTableField field = {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy_Header* envoy_config_route_v3_RouteAction_HashPolicy_mutable_header(envoy_config_route_v3_RouteAction_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_HashPolicy_Header* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_Header*)envoy_config_route_v3_RouteAction_HashPolicy_header(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_Header*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_set_header(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_set_cookie(envoy_config_route_v3_RouteAction_HashPolicy *msg, envoy_config_route_v3_RouteAction_HashPolicy_Cookie* value) {
  const upb_MiniTableField field = {2, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy_Cookie* envoy_config_route_v3_RouteAction_HashPolicy_mutable_cookie(envoy_config_route_v3_RouteAction_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_HashPolicy_Cookie* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_Cookie*)envoy_config_route_v3_RouteAction_HashPolicy_cookie(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_Cookie*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_set_cookie(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_set_connection_properties(envoy_config_route_v3_RouteAction_HashPolicy *msg, envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* value) {
  const upb_MiniTableField field = {3, 16, -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* envoy_config_route_v3_RouteAction_HashPolicy_mutable_connection_properties(envoy_config_route_v3_RouteAction_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties*)envoy_config_route_v3_RouteAction_HashPolicy_connection_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_set_connection_properties(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_set_terminal(envoy_config_route_v3_RouteAction_HashPolicy *msg, bool value) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_set_query_parameter(envoy_config_route_v3_RouteAction_HashPolicy *msg, envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* value) {
  const upb_MiniTableField field = {5, 16, -13, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* envoy_config_route_v3_RouteAction_HashPolicy_mutable_query_parameter(envoy_config_route_v3_RouteAction_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter*)envoy_config_route_v3_RouteAction_HashPolicy_query_parameter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_set_query_parameter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_set_filter_state(envoy_config_route_v3_RouteAction_HashPolicy *msg, envoy_config_route_v3_RouteAction_HashPolicy_FilterState* value) {
  const upb_MiniTableField field = {6, 16, -13, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy_FilterState* envoy_config_route_v3_RouteAction_HashPolicy_mutable_filter_state(envoy_config_route_v3_RouteAction_HashPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_HashPolicy_FilterState* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_FilterState*)envoy_config_route_v3_RouteAction_HashPolicy_filter_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_FilterState*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_set_filter_state(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_Header* envoy_config_route_v3_RouteAction_HashPolicy_Header_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy_Header*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_Header* envoy_config_route_v3_RouteAction_HashPolicy_Header_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_Header* ret = envoy_config_route_v3_RouteAction_HashPolicy_Header_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_Header* envoy_config_route_v3_RouteAction_HashPolicy_Header_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_Header* ret = envoy_config_route_v3_RouteAction_HashPolicy_Header_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_Header_serialize(const envoy_config_route_v3_RouteAction_HashPolicy_Header* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_Header_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy_Header* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Header_clear_header_name(envoy_config_route_v3_RouteAction_HashPolicy_Header* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_Header_header_name(const envoy_config_route_v3_RouteAction_HashPolicy_Header* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Header_clear_regex_rewrite(envoy_config_route_v3_RouteAction_HashPolicy_Header* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RouteAction_HashPolicy_Header_regex_rewrite(const envoy_config_route_v3_RouteAction_HashPolicy_Header* msg) {
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_Header_has_regex_rewrite(const envoy_config_route_v3_RouteAction_HashPolicy_Header* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Header_set_header_name(envoy_config_route_v3_RouteAction_HashPolicy_Header *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Header_set_regex_rewrite(envoy_config_route_v3_RouteAction_HashPolicy_Header *msg, struct envoy_type_matcher_v3_RegexMatchAndSubstitute* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RouteAction_HashPolicy_Header_mutable_regex_rewrite(envoy_config_route_v3_RouteAction_HashPolicy_Header* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatchAndSubstitute* sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)envoy_config_route_v3_RouteAction_HashPolicy_Header_regex_rewrite(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_Header_set_regex_rewrite(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* ret = envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* ret = envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_serialize(const envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_clear_name(envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_name(const envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_clear_value(envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_value(const envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_set_name(envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute_set_value(envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_Cookie* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy_Cookie*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_Cookie* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_Cookie* ret = envoy_config_route_v3_RouteAction_HashPolicy_Cookie_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_Cookie* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_Cookie* ret = envoy_config_route_v3_RouteAction_HashPolicy_Cookie_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_serialize(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_clear_name(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_Cookie_name(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_clear_ttl(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_ttl(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_Cookie_has_ttl(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_clear_path(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_Cookie_path(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_clear_attributes(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* const* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_attributes(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RouteAction_HashPolicy_Cookie_attributes_upb_array(const envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RouteAction_HashPolicy_Cookie_attributes_mutable_upb_array(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_set_name(envoy_config_route_v3_RouteAction_HashPolicy_Cookie *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_set_ttl(envoy_config_route_v3_RouteAction_HashPolicy_Cookie *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_mutable_ttl(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_HashPolicy_Cookie_ttl(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_HashPolicy_Cookie_set_ttl(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_Cookie_set_path(envoy_config_route_v3_RouteAction_HashPolicy_Cookie *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute** envoy_config_route_v3_RouteAction_HashPolicy_Cookie_mutable_attributes(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute** envoy_config_route_v3_RouteAction_HashPolicy_Cookie_resize_attributes(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* envoy_config_route_v3_RouteAction_HashPolicy_Cookie_add_attributes(envoy_config_route_v3_RouteAction_HashPolicy_Cookie* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute* sub = (struct envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* ret = envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* ret = envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_serialize(const envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_clear_source_ip(envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_source_ip(const envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties_set_source_ip(envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* ret = envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* ret = envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_serialize(const envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_clear_name(envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_name(const envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter_set_name(envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_FilterState* envoy_config_route_v3_RouteAction_HashPolicy_FilterState_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_HashPolicy_FilterState*)_upb_Message_New(&envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_FilterState* envoy_config_route_v3_RouteAction_HashPolicy_FilterState_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_FilterState* ret = envoy_config_route_v3_RouteAction_HashPolicy_FilterState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_HashPolicy_FilterState* envoy_config_route_v3_RouteAction_HashPolicy_FilterState_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_HashPolicy_FilterState* ret = envoy_config_route_v3_RouteAction_HashPolicy_FilterState_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_FilterState_serialize(const envoy_config_route_v3_RouteAction_HashPolicy_FilterState* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_HashPolicy_FilterState_serialize_ex(const envoy_config_route_v3_RouteAction_HashPolicy_FilterState* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_FilterState_clear_key(envoy_config_route_v3_RouteAction_HashPolicy_FilterState* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_HashPolicy_FilterState_key(const envoy_config_route_v3_RouteAction_HashPolicy_FilterState* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_HashPolicy_FilterState_set_key(envoy_config_route_v3_RouteAction_HashPolicy_FilterState *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_UpgradeConfig*)_upb_Message_New(&envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_UpgradeConfig* ret = envoy_config_route_v3_RouteAction_UpgradeConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_UpgradeConfig* ret = envoy_config_route_v3_RouteAction_UpgradeConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_UpgradeConfig_serialize(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_UpgradeConfig_serialize_ex(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_clear_upgrade_type(envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RouteAction_UpgradeConfig_upgrade_type(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_clear_enabled(envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_UpgradeConfig_enabled(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_UpgradeConfig_has_enabled(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_clear_connect_config(envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_connect_config(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* default_val = NULL;
  const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_UpgradeConfig_has_connect_config(const envoy_config_route_v3_RouteAction_UpgradeConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_set_upgrade_type(envoy_config_route_v3_RouteAction_UpgradeConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_set_enabled(envoy_config_route_v3_RouteAction_UpgradeConfig *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RouteAction_UpgradeConfig_mutable_enabled(envoy_config_route_v3_RouteAction_UpgradeConfig* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RouteAction_UpgradeConfig_enabled(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_UpgradeConfig_set_enabled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_set_connect_config(envoy_config_route_v3_RouteAction_UpgradeConfig *msg, envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_mutable_connect_config(envoy_config_route_v3_RouteAction_UpgradeConfig* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* sub = (struct envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig*)envoy_config_route_v3_RouteAction_UpgradeConfig_connect_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig*)_upb_Message_New(&envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_UpgradeConfig_set_connect_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig*)_upb_Message_New(&envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* ret = envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* ret = envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_serialize(const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_serialize_ex(const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_clear_proxy_protocol_config(envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ProxyProtocolConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_proxy_protocol_config(const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg) {
  const struct envoy_config_core_v3_ProxyProtocolConfig* default_val = NULL;
  const struct envoy_config_core_v3_ProxyProtocolConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ProxyProtocolConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_has_proxy_protocol_config(const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_clear_allow_post(envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_allow_post(const envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_set_proxy_protocol_config(envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig *msg, struct envoy_config_core_v3_ProxyProtocolConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ProxyProtocolConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ProxyProtocolConfig* envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_mutable_proxy_protocol_config(envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ProxyProtocolConfig* sub = (struct envoy_config_core_v3_ProxyProtocolConfig*)envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_proxy_protocol_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ProxyProtocolConfig*)_upb_Message_New(&envoy__config__core__v3__ProxyProtocolConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_set_proxy_protocol_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig_set_allow_post(envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RouteAction_MaxStreamDuration* envoy_config_route_v3_RouteAction_MaxStreamDuration_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RouteAction_MaxStreamDuration*)_upb_Message_New(&envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RouteAction_MaxStreamDuration* envoy_config_route_v3_RouteAction_MaxStreamDuration_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_MaxStreamDuration* ret = envoy_config_route_v3_RouteAction_MaxStreamDuration_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RouteAction_MaxStreamDuration* envoy_config_route_v3_RouteAction_MaxStreamDuration_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RouteAction_MaxStreamDuration* ret = envoy_config_route_v3_RouteAction_MaxStreamDuration_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_MaxStreamDuration_serialize(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RouteAction_MaxStreamDuration_serialize_ex(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_MaxStreamDuration_clear_max_stream_duration(envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_MaxStreamDuration_max_stream_duration(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_MaxStreamDuration_has_max_stream_duration(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_MaxStreamDuration_clear_grpc_timeout_header_max(envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_MaxStreamDuration_grpc_timeout_header_max(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_MaxStreamDuration_has_grpc_timeout_header_max(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RouteAction_MaxStreamDuration_clear_grpc_timeout_header_offset(envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_MaxStreamDuration_grpc_timeout_header_offset(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RouteAction_MaxStreamDuration_has_grpc_timeout_header_offset(const envoy_config_route_v3_RouteAction_MaxStreamDuration* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RouteAction_MaxStreamDuration_set_max_stream_duration(envoy_config_route_v3_RouteAction_MaxStreamDuration *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_MaxStreamDuration_mutable_max_stream_duration(envoy_config_route_v3_RouteAction_MaxStreamDuration* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_MaxStreamDuration_max_stream_duration(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_MaxStreamDuration_set_max_stream_duration(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_MaxStreamDuration_set_grpc_timeout_header_max(envoy_config_route_v3_RouteAction_MaxStreamDuration *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_MaxStreamDuration_mutable_grpc_timeout_header_max(envoy_config_route_v3_RouteAction_MaxStreamDuration* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_MaxStreamDuration_grpc_timeout_header_max(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_MaxStreamDuration_set_grpc_timeout_header_max(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RouteAction_MaxStreamDuration_set_grpc_timeout_header_offset(envoy_config_route_v3_RouteAction_MaxStreamDuration *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RouteAction_MaxStreamDuration_mutable_grpc_timeout_header_offset(envoy_config_route_v3_RouteAction_MaxStreamDuration* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RouteAction_MaxStreamDuration_grpc_timeout_header_offset(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RouteAction_MaxStreamDuration_set_grpc_timeout_header_offset(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_RetryPolicy_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RetryPolicy*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_RetryPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy* ret = envoy_config_route_v3_RetryPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy* envoy_config_route_v3_RetryPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy* ret = envoy_config_route_v3_RetryPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_serialize(const envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_serialize_ex(const envoy_config_route_v3_RetryPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retry_on(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(56, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RetryPolicy_retry_on(const envoy_config_route_v3_RetryPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(56, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_num_retries(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_RetryPolicy_num_retries(const envoy_config_route_v3_RetryPolicy* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_has_num_retries(const envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_per_try_timeout(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_per_try_timeout(const envoy_config_route_v3_RetryPolicy* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_has_per_try_timeout(const envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retry_priority(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy_RetryPriority* envoy_config_route_v3_RetryPolicy_retry_priority(const envoy_config_route_v3_RetryPolicy* msg) {
  const envoy_config_route_v3_RetryPolicy_RetryPriority* default_val = NULL;
  const envoy_config_route_v3_RetryPolicy_RetryPriority* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_has_retry_priority(const envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retry_host_predicate(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* const* envoy_config_route_v3_RetryPolicy_retry_host_predicate(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RetryPolicy_retry_host_predicate_upb_array(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RetryPolicy_retry_host_predicate_mutable_upb_array(envoy_config_route_v3_RetryPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_host_selection_retry_max_attempts(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {6, 64, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_route_v3_RetryPolicy_host_selection_retry_max_attempts(const envoy_config_route_v3_RetryPolicy* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {6, 64, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retriable_status_codes(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* envoy_config_route_v3_RetryPolicy_retriable_status_codes(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RetryPolicy_retriable_status_codes_upb_array(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RetryPolicy_retriable_status_codes_mutable_upb_array(envoy_config_route_v3_RetryPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retry_back_off(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 80), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy_RetryBackOff* envoy_config_route_v3_RetryPolicy_retry_back_off(const envoy_config_route_v3_RetryPolicy* msg) {
  const envoy_config_route_v3_RetryPolicy_RetryBackOff* default_val = NULL;
  const envoy_config_route_v3_RetryPolicy_RetryBackOff* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(32, 80), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_has_retry_back_off(const envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 80), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retriable_headers(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HeaderMatcher* const* envoy_config_route_v3_RetryPolicy_retriable_headers(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RetryPolicy_retriable_headers_upb_array(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RetryPolicy_retriable_headers_mutable_upb_array(envoy_config_route_v3_RetryPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retriable_request_headers(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HeaderMatcher* const* envoy_config_route_v3_RetryPolicy_retriable_request_headers(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RetryPolicy_retriable_request_headers_upb_array(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RetryPolicy_retriable_request_headers_mutable_upb_array(envoy_config_route_v3_RetryPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_rate_limited_retry_back_off(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 104), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* envoy_config_route_v3_RetryPolicy_rate_limited_retry_back_off(const envoy_config_route_v3_RetryPolicy* msg) {
  const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* default_val = NULL;
  const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(44, 104), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_has_rate_limited_retry_back_off(const envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 104), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_retry_options_predicates(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_config_route_v3_RetryPolicy_retry_options_predicates(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_RetryPolicy_retry_options_predicates_upb_array(const envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RetryPolicy_retry_options_predicates_mutable_upb_array(envoy_config_route_v3_RetryPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_clear_per_try_idle_timeout(envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 120), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_per_try_idle_timeout(const envoy_config_route_v3_RetryPolicy* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(52, 120), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_has_per_try_idle_timeout(const envoy_config_route_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 120), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_retry_on(envoy_config_route_v3_RetryPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(56, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_num_retries(envoy_config_route_v3_RetryPolicy *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_RetryPolicy_mutable_num_retries(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_RetryPolicy_num_retries(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_set_num_retries(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_per_try_timeout(envoy_config_route_v3_RetryPolicy *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_mutable_per_try_timeout(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RetryPolicy_per_try_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_set_per_try_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_retry_priority(envoy_config_route_v3_RetryPolicy *msg, envoy_config_route_v3_RetryPolicy_RetryPriority* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy_RetryPriority* envoy_config_route_v3_RetryPolicy_mutable_retry_priority(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RetryPolicy_RetryPriority* sub = (struct envoy_config_route_v3_RetryPolicy_RetryPriority*)envoy_config_route_v3_RetryPolicy_retry_priority(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RetryPolicy_RetryPriority*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_set_retry_priority(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryHostPredicate** envoy_config_route_v3_RetryPolicy_mutable_retry_host_predicate(envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RetryPolicy_RetryHostPredicate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryHostPredicate** envoy_config_route_v3_RetryPolicy_resize_retry_host_predicate(envoy_config_route_v3_RetryPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RetryPolicy_RetryHostPredicate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy_RetryHostPredicate* envoy_config_route_v3_RetryPolicy_add_retry_host_predicate(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RetryPolicy_RetryHostPredicate* sub = (struct envoy_config_route_v3_RetryPolicy_RetryHostPredicate*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_host_selection_retry_max_attempts(envoy_config_route_v3_RetryPolicy *msg, int64_t value) {
  const upb_MiniTableField field = {6, 64, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE uint32_t* envoy_config_route_v3_RetryPolicy_mutable_retriable_status_codes(envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* envoy_config_route_v3_RetryPolicy_resize_retriable_status_codes(envoy_config_route_v3_RetryPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_add_retriable_status_codes(envoy_config_route_v3_RetryPolicy* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_retry_back_off(envoy_config_route_v3_RetryPolicy *msg, envoy_config_route_v3_RetryPolicy_RetryBackOff* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 80), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy_RetryBackOff* envoy_config_route_v3_RetryPolicy_mutable_retry_back_off(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RetryPolicy_RetryBackOff* sub = (struct envoy_config_route_v3_RetryPolicy_RetryBackOff*)envoy_config_route_v3_RetryPolicy_retry_back_off(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RetryPolicy_RetryBackOff*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_set_retry_back_off(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RetryPolicy_mutable_retriable_headers(envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RetryPolicy_resize_retriable_headers(envoy_config_route_v3_RetryPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_RetryPolicy_add_retriable_headers(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RetryPolicy_mutable_retriable_request_headers(envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RetryPolicy_resize_retriable_request_headers(envoy_config_route_v3_RetryPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_RetryPolicy_add_retriable_request_headers(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_rate_limited_retry_back_off(envoy_config_route_v3_RetryPolicy *msg, envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(44, 104), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* envoy_config_route_v3_RetryPolicy_mutable_rate_limited_retry_back_off(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* sub = (struct envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff*)envoy_config_route_v3_RetryPolicy_rate_limited_retry_back_off(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_set_rate_limited_retry_back_off(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_route_v3_RetryPolicy_mutable_retry_options_predicates(envoy_config_route_v3_RetryPolicy* msg, size_t* size) {
  upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_route_v3_RetryPolicy_resize_retry_options_predicates(envoy_config_route_v3_RetryPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RetryPolicy_add_retry_options_predicates(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_RetryPolicy_set_per_try_idle_timeout(envoy_config_route_v3_RetryPolicy *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(52, 120), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_mutable_per_try_idle_timeout(envoy_config_route_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RetryPolicy_per_try_idle_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_set_per_try_idle_timeout(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryPriority* envoy_config_route_v3_RetryPolicy_RetryPriority_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RetryPolicy_RetryPriority*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryPriority* envoy_config_route_v3_RetryPolicy_RetryPriority_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RetryPriority* ret = envoy_config_route_v3_RetryPolicy_RetryPriority_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryPriority* envoy_config_route_v3_RetryPolicy_RetryPriority_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RetryPriority* ret = envoy_config_route_v3_RetryPolicy_RetryPriority_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RetryPriority_serialize(const envoy_config_route_v3_RetryPolicy_RetryPriority* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RetryPriority_serialize_ex(const envoy_config_route_v3_RetryPolicy_RetryPriority* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RetryPolicy_RetryPriority_config_type_typed_config = 3,
  envoy_config_route_v3_RetryPolicy_RetryPriority_config_type_NOT_SET = 0
} envoy_config_route_v3_RetryPolicy_RetryPriority_config_type_oneofcases;
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryPriority_config_type_oneofcases envoy_config_route_v3_RetryPolicy_RetryPriority_config_type_case(const envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RetryPolicy_RetryPriority_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryPriority_clear_config_type(envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryPriority_clear_name(envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RetryPolicy_RetryPriority_name(const envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryPriority_clear_typed_config(envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_route_v3_RetryPolicy_RetryPriority_typed_config(const envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_RetryPriority_has_typed_config(const envoy_config_route_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryPriority_set_name(envoy_config_route_v3_RetryPolicy_RetryPriority *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryPriority_set_typed_config(envoy_config_route_v3_RetryPolicy_RetryPriority *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_route_v3_RetryPolicy_RetryPriority_mutable_typed_config(envoy_config_route_v3_RetryPolicy_RetryPriority* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_route_v3_RetryPolicy_RetryPriority_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_RetryPriority_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryHostPredicate* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RetryPolicy_RetryHostPredicate*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryHostPredicate* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RetryHostPredicate* ret = envoy_config_route_v3_RetryPolicy_RetryHostPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryHostPredicate* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RetryHostPredicate* ret = envoy_config_route_v3_RetryPolicy_RetryHostPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_serialize(const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_serialize_ex(const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RetryPolicy_RetryHostPredicate_config_type_typed_config = 3,
  envoy_config_route_v3_RetryPolicy_RetryHostPredicate_config_type_NOT_SET = 0
} envoy_config_route_v3_RetryPolicy_RetryHostPredicate_config_type_oneofcases;
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryHostPredicate_config_type_oneofcases envoy_config_route_v3_RetryPolicy_RetryHostPredicate_config_type_case(const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RetryPolicy_RetryHostPredicate_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryHostPredicate_clear_config_type(envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryHostPredicate_clear_name(envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RetryPolicy_RetryHostPredicate_name(const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryHostPredicate_clear_typed_config(envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_typed_config(const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_RetryHostPredicate_has_typed_config(const envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryHostPredicate_set_name(envoy_config_route_v3_RetryPolicy_RetryHostPredicate *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryHostPredicate_set_typed_config(envoy_config_route_v3_RetryPolicy_RetryHostPredicate *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_route_v3_RetryPolicy_RetryHostPredicate_mutable_typed_config(envoy_config_route_v3_RetryPolicy_RetryHostPredicate* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_route_v3_RetryPolicy_RetryHostPredicate_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_RetryHostPredicate_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryBackOff* envoy_config_route_v3_RetryPolicy_RetryBackOff_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RetryPolicy_RetryBackOff*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryBackOff* envoy_config_route_v3_RetryPolicy_RetryBackOff_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RetryBackOff* ret = envoy_config_route_v3_RetryPolicy_RetryBackOff_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RetryBackOff* envoy_config_route_v3_RetryPolicy_RetryBackOff_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RetryBackOff* ret = envoy_config_route_v3_RetryPolicy_RetryBackOff_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RetryBackOff_serialize(const envoy_config_route_v3_RetryPolicy_RetryBackOff* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RetryBackOff_serialize_ex(const envoy_config_route_v3_RetryPolicy_RetryBackOff* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryBackOff_clear_base_interval(envoy_config_route_v3_RetryPolicy_RetryBackOff* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_RetryBackOff_base_interval(const envoy_config_route_v3_RetryPolicy_RetryBackOff* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_RetryBackOff_has_base_interval(const envoy_config_route_v3_RetryPolicy_RetryBackOff* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryBackOff_clear_max_interval(envoy_config_route_v3_RetryPolicy_RetryBackOff* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_RetryBackOff_max_interval(const envoy_config_route_v3_RetryPolicy_RetryBackOff* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_RetryBackOff_has_max_interval(const envoy_config_route_v3_RetryPolicy_RetryBackOff* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryBackOff_set_base_interval(envoy_config_route_v3_RetryPolicy_RetryBackOff *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_RetryBackOff_mutable_base_interval(envoy_config_route_v3_RetryPolicy_RetryBackOff* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RetryPolicy_RetryBackOff_base_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_RetryBackOff_set_base_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RetryBackOff_set_max_interval(envoy_config_route_v3_RetryPolicy_RetryBackOff *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_RetryBackOff_mutable_max_interval(envoy_config_route_v3_RetryPolicy_RetryBackOff* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RetryPolicy_RetryBackOff_max_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_RetryBackOff_set_max_interval(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RetryPolicy_ResetHeader* envoy_config_route_v3_RetryPolicy_ResetHeader_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RetryPolicy_ResetHeader*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_ResetHeader* envoy_config_route_v3_RetryPolicy_ResetHeader_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_ResetHeader* ret = envoy_config_route_v3_RetryPolicy_ResetHeader_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_ResetHeader* envoy_config_route_v3_RetryPolicy_ResetHeader_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_ResetHeader* ret = envoy_config_route_v3_RetryPolicy_ResetHeader_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_ResetHeader_serialize(const envoy_config_route_v3_RetryPolicy_ResetHeader* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_ResetHeader_serialize_ex(const envoy_config_route_v3_RetryPolicy_ResetHeader* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_ResetHeader_clear_name(envoy_config_route_v3_RetryPolicy_ResetHeader* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RetryPolicy_ResetHeader_name(const envoy_config_route_v3_RetryPolicy_ResetHeader* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_ResetHeader_clear_format(envoy_config_route_v3_RetryPolicy_ResetHeader* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_RetryPolicy_ResetHeader_format(const envoy_config_route_v3_RetryPolicy_ResetHeader* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RetryPolicy_ResetHeader_set_name(envoy_config_route_v3_RetryPolicy_ResetHeader *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_ResetHeader_set_format(envoy_config_route_v3_RetryPolicy_ResetHeader *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* ret = envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* ret = envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_serialize(const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_serialize_ex(const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_clear_reset_headers(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RetryPolicy_ResetHeader* const* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_reset_headers(const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RetryPolicy_ResetHeader* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_reset_headers_upb_array(const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_reset_headers_mutable_upb_array(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_clear_max_interval(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_max_interval(const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_has_max_interval(const envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE envoy_config_route_v3_RetryPolicy_ResetHeader** envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_mutable_reset_headers(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RetryPolicy_ResetHeader**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RetryPolicy_ResetHeader** envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_resize_reset_headers(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RetryPolicy_ResetHeader**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RetryPolicy_ResetHeader* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_add_reset_headers(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RetryPolicy_ResetHeader* sub = (struct envoy_config_route_v3_RetryPolicy_ResetHeader*)_upb_Message_New(&envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_set_max_interval(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_mutable_max_interval(envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_max_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff_set_max_interval(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_HedgePolicy_new(upb_Arena* arena) {
  return (envoy_config_route_v3_HedgePolicy*)_upb_Message_New(&envoy__config__route__v3__HedgePolicy_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_HedgePolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_HedgePolicy* ret = envoy_config_route_v3_HedgePolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__HedgePolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_HedgePolicy* envoy_config_route_v3_HedgePolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_HedgePolicy* ret = envoy_config_route_v3_HedgePolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__HedgePolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_HedgePolicy_serialize(const envoy_config_route_v3_HedgePolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__HedgePolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_HedgePolicy_serialize_ex(const envoy_config_route_v3_HedgePolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__HedgePolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_HedgePolicy_clear_initial_requests(envoy_config_route_v3_HedgePolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_HedgePolicy_initial_requests(const envoy_config_route_v3_HedgePolicy* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HedgePolicy_has_initial_requests(const envoy_config_route_v3_HedgePolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HedgePolicy_clear_additional_request_chance(envoy_config_route_v3_HedgePolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_HedgePolicy_additional_request_chance(const envoy_config_route_v3_HedgePolicy* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HedgePolicy_has_additional_request_chance(const envoy_config_route_v3_HedgePolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HedgePolicy_clear_hedge_on_per_try_timeout(envoy_config_route_v3_HedgePolicy* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_HedgePolicy_hedge_on_per_try_timeout(const envoy_config_route_v3_HedgePolicy* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_HedgePolicy_set_initial_requests(envoy_config_route_v3_HedgePolicy *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_HedgePolicy_mutable_initial_requests(envoy_config_route_v3_HedgePolicy* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_HedgePolicy_initial_requests(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_HedgePolicy_set_initial_requests(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_HedgePolicy_set_additional_request_chance(envoy_config_route_v3_HedgePolicy *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_HedgePolicy_mutable_additional_request_chance(envoy_config_route_v3_HedgePolicy* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_route_v3_HedgePolicy_additional_request_chance(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_HedgePolicy_set_additional_request_chance(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_HedgePolicy_set_hedge_on_per_try_timeout(envoy_config_route_v3_HedgePolicy *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RedirectAction* envoy_config_route_v3_RedirectAction_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RedirectAction*)_upb_Message_New(&envoy__config__route__v3__RedirectAction_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RedirectAction* envoy_config_route_v3_RedirectAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RedirectAction* ret = envoy_config_route_v3_RedirectAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RedirectAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RedirectAction* envoy_config_route_v3_RedirectAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RedirectAction* ret = envoy_config_route_v3_RedirectAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RedirectAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RedirectAction_serialize(const envoy_config_route_v3_RedirectAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RedirectAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RedirectAction_serialize_ex(const envoy_config_route_v3_RedirectAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RedirectAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_https_redirect = 4,
  envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_scheme_redirect = 7,
  envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_NOT_SET = 0
} envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_oneofcases envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_case(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RedirectAction_scheme_rewrite_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_scheme_rewrite_specifier(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RedirectAction_msg_init, &field);
}
typedef enum {
  envoy_config_route_v3_RedirectAction_path_rewrite_specifier_path_redirect = 2,
  envoy_config_route_v3_RedirectAction_path_rewrite_specifier_prefix_rewrite = 5,
  envoy_config_route_v3_RedirectAction_path_rewrite_specifier_regex_rewrite = 9,
  envoy_config_route_v3_RedirectAction_path_rewrite_specifier_NOT_SET = 0
} envoy_config_route_v3_RedirectAction_path_rewrite_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RedirectAction_path_rewrite_specifier_oneofcases envoy_config_route_v3_RedirectAction_path_rewrite_specifier_case(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RedirectAction_path_rewrite_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_path_rewrite_specifier(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RedirectAction_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_host_redirect(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RedirectAction_host_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_path_redirect(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RedirectAction_path_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_has_path_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_response_code(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_RedirectAction_response_code(const envoy_config_route_v3_RedirectAction* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_https_redirect(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_https_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_has_https_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_prefix_rewrite(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RedirectAction_prefix_rewrite(const envoy_config_route_v3_RedirectAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_has_prefix_rewrite(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_strip_query(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_strip_query(const envoy_config_route_v3_RedirectAction* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_scheme_redirect(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 48), -21, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RedirectAction_scheme_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 48), -21, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_has_scheme_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 48), -21, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_port_redirect(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {8, 16, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_route_v3_RedirectAction_port_redirect(const envoy_config_route_v3_RedirectAction* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {8, 16, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_clear_regex_rewrite(envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 64), -25, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RedirectAction_regex_rewrite(const envoy_config_route_v3_RedirectAction* msg) {
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatchAndSubstitute* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(44, 64), -25, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RedirectAction_has_regex_rewrite(const envoy_config_route_v3_RedirectAction* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 64), -25, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RedirectAction_set_host_redirect(envoy_config_route_v3_RedirectAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_path_redirect(envoy_config_route_v3_RedirectAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_response_code(envoy_config_route_v3_RedirectAction *msg, int32_t value) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_https_redirect(envoy_config_route_v3_RedirectAction *msg, bool value) {
  const upb_MiniTableField field = {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_prefix_rewrite(envoy_config_route_v3_RedirectAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_strip_query(envoy_config_route_v3_RedirectAction *msg, bool value) {
  const upb_MiniTableField field = {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_scheme_redirect(envoy_config_route_v3_RedirectAction *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 48), -21, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_port_redirect(envoy_config_route_v3_RedirectAction *msg, uint32_t value) {
  const upb_MiniTableField field = {8, 16, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RedirectAction_set_regex_rewrite(envoy_config_route_v3_RedirectAction *msg, struct envoy_type_matcher_v3_RegexMatchAndSubstitute* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 64), -25, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatchAndSubstitute* envoy_config_route_v3_RedirectAction_mutable_regex_rewrite(envoy_config_route_v3_RedirectAction* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatchAndSubstitute* sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)envoy_config_route_v3_RedirectAction_regex_rewrite(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatchAndSubstitute*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init, arena);
    if (sub) envoy_config_route_v3_RedirectAction_set_regex_rewrite(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_DirectResponseAction* envoy_config_route_v3_DirectResponseAction_new(upb_Arena* arena) {
  return (envoy_config_route_v3_DirectResponseAction*)_upb_Message_New(&envoy__config__route__v3__DirectResponseAction_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_DirectResponseAction* envoy_config_route_v3_DirectResponseAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_DirectResponseAction* ret = envoy_config_route_v3_DirectResponseAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__DirectResponseAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_DirectResponseAction* envoy_config_route_v3_DirectResponseAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_DirectResponseAction* ret = envoy_config_route_v3_DirectResponseAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__DirectResponseAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_DirectResponseAction_serialize(const envoy_config_route_v3_DirectResponseAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__DirectResponseAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_DirectResponseAction_serialize_ex(const envoy_config_route_v3_DirectResponseAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__DirectResponseAction_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_DirectResponseAction_clear_status(envoy_config_route_v3_DirectResponseAction* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_route_v3_DirectResponseAction_status(const envoy_config_route_v3_DirectResponseAction* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_DirectResponseAction_clear_body(envoy_config_route_v3_DirectResponseAction* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_route_v3_DirectResponseAction_body(const envoy_config_route_v3_DirectResponseAction* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_DirectResponseAction_has_body(const envoy_config_route_v3_DirectResponseAction* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_DirectResponseAction_set_status(envoy_config_route_v3_DirectResponseAction *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_DirectResponseAction_set_body(envoy_config_route_v3_DirectResponseAction *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_route_v3_DirectResponseAction_mutable_body(envoy_config_route_v3_DirectResponseAction* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_route_v3_DirectResponseAction_body(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_route_v3_DirectResponseAction_set_body(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_NonForwardingAction* envoy_config_route_v3_NonForwardingAction_new(upb_Arena* arena) {
  return (envoy_config_route_v3_NonForwardingAction*)_upb_Message_New(&envoy__config__route__v3__NonForwardingAction_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_NonForwardingAction* envoy_config_route_v3_NonForwardingAction_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_NonForwardingAction* ret = envoy_config_route_v3_NonForwardingAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__NonForwardingAction_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_NonForwardingAction* envoy_config_route_v3_NonForwardingAction_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_NonForwardingAction* ret = envoy_config_route_v3_NonForwardingAction_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__NonForwardingAction_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_NonForwardingAction_serialize(const envoy_config_route_v3_NonForwardingAction* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__NonForwardingAction_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_NonForwardingAction_serialize_ex(const envoy_config_route_v3_NonForwardingAction* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__NonForwardingAction_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_route_v3_Decorator* envoy_config_route_v3_Decorator_new(upb_Arena* arena) {
  return (envoy_config_route_v3_Decorator*)_upb_Message_New(&envoy__config__route__v3__Decorator_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_Decorator* envoy_config_route_v3_Decorator_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_Decorator* ret = envoy_config_route_v3_Decorator_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__Decorator_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_Decorator* envoy_config_route_v3_Decorator_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_Decorator* ret = envoy_config_route_v3_Decorator_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__Decorator_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_Decorator_serialize(const envoy_config_route_v3_Decorator* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__Decorator_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_Decorator_serialize_ex(const envoy_config_route_v3_Decorator* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__Decorator_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_Decorator_clear_operation(envoy_config_route_v3_Decorator* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_Decorator_operation(const envoy_config_route_v3_Decorator* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_Decorator_clear_propagate(envoy_config_route_v3_Decorator* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_Decorator_propagate(const envoy_config_route_v3_Decorator* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Decorator_has_propagate(const envoy_config_route_v3_Decorator* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_Decorator_set_operation(envoy_config_route_v3_Decorator *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_Decorator_set_propagate(envoy_config_route_v3_Decorator *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_Decorator_mutable_propagate(envoy_config_route_v3_Decorator* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_Decorator_propagate(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_Decorator_set_propagate(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_Tracing* envoy_config_route_v3_Tracing_new(upb_Arena* arena) {
  return (envoy_config_route_v3_Tracing*)_upb_Message_New(&envoy__config__route__v3__Tracing_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_Tracing* envoy_config_route_v3_Tracing_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_Tracing* ret = envoy_config_route_v3_Tracing_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__Tracing_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_Tracing* envoy_config_route_v3_Tracing_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_Tracing* ret = envoy_config_route_v3_Tracing_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__Tracing_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_Tracing_serialize(const envoy_config_route_v3_Tracing* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__Tracing_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_Tracing_serialize_ex(const envoy_config_route_v3_Tracing* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__Tracing_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_Tracing_clear_client_sampling(envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_Tracing_client_sampling(const envoy_config_route_v3_Tracing* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Tracing_has_client_sampling(const envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Tracing_clear_random_sampling(envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_Tracing_random_sampling(const envoy_config_route_v3_Tracing* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Tracing_has_random_sampling(const envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Tracing_clear_overall_sampling(envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_Tracing_overall_sampling(const envoy_config_route_v3_Tracing* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_Tracing_has_overall_sampling(const envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_Tracing_clear_custom_tags(envoy_config_route_v3_Tracing* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_tracing_v3_CustomTag* const* envoy_config_route_v3_Tracing_custom_tags(const envoy_config_route_v3_Tracing* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_Tracing_custom_tags_upb_array(const envoy_config_route_v3_Tracing* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_Tracing_custom_tags_mutable_upb_array(envoy_config_route_v3_Tracing* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__tracing__v3__CustomTag_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_route_v3_Tracing_set_client_sampling(envoy_config_route_v3_Tracing *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_Tracing_mutable_client_sampling(envoy_config_route_v3_Tracing* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_route_v3_Tracing_client_sampling(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_Tracing_set_client_sampling(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Tracing_set_random_sampling(envoy_config_route_v3_Tracing *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_Tracing_mutable_random_sampling(envoy_config_route_v3_Tracing* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_route_v3_Tracing_random_sampling(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_Tracing_set_random_sampling(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_Tracing_set_overall_sampling(envoy_config_route_v3_Tracing *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_route_v3_Tracing_mutable_overall_sampling(envoy_config_route_v3_Tracing* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_route_v3_Tracing_overall_sampling(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_route_v3_Tracing_set_overall_sampling(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_type_tracing_v3_CustomTag** envoy_config_route_v3_Tracing_mutable_custom_tags(envoy_config_route_v3_Tracing* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_type_tracing_v3_CustomTag** envoy_config_route_v3_Tracing_resize_custom_tags(envoy_config_route_v3_Tracing* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_type_tracing_v3_CustomTag**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_tracing_v3_CustomTag* envoy_config_route_v3_Tracing_add_custom_tags(envoy_config_route_v3_Tracing* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_config_route_v3_VirtualCluster* envoy_config_route_v3_VirtualCluster_new(upb_Arena* arena) {
  return (envoy_config_route_v3_VirtualCluster*)_upb_Message_New(&envoy__config__route__v3__VirtualCluster_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_VirtualCluster* envoy_config_route_v3_VirtualCluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_VirtualCluster* ret = envoy_config_route_v3_VirtualCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__VirtualCluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_VirtualCluster* envoy_config_route_v3_VirtualCluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_VirtualCluster* ret = envoy_config_route_v3_VirtualCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__VirtualCluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_VirtualCluster_serialize(const envoy_config_route_v3_VirtualCluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__VirtualCluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_VirtualCluster_serialize_ex(const envoy_config_route_v3_VirtualCluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__VirtualCluster_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_VirtualCluster_clear_name(envoy_config_route_v3_VirtualCluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_VirtualCluster_name(const envoy_config_route_v3_VirtualCluster* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_VirtualCluster_clear_headers(envoy_config_route_v3_VirtualCluster* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HeaderMatcher* const* envoy_config_route_v3_VirtualCluster_headers(const envoy_config_route_v3_VirtualCluster* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_VirtualCluster_headers_upb_array(const envoy_config_route_v3_VirtualCluster* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_VirtualCluster_headers_mutable_upb_array(envoy_config_route_v3_VirtualCluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_route_v3_VirtualCluster_set_name(envoy_config_route_v3_VirtualCluster *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_VirtualCluster_mutable_headers(envoy_config_route_v3_VirtualCluster* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_VirtualCluster_resize_headers(envoy_config_route_v3_VirtualCluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_VirtualCluster_add_headers(envoy_config_route_v3_VirtualCluster* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_route_v3_RateLimit* envoy_config_route_v3_RateLimit_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit*)_upb_Message_New(&envoy__config__route__v3__RateLimit_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit* envoy_config_route_v3_RateLimit_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit* ret = envoy_config_route_v3_RateLimit_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit* envoy_config_route_v3_RateLimit_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit* ret = envoy_config_route_v3_RateLimit_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_serialize(const envoy_config_route_v3_RateLimit* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_serialize_ex(const envoy_config_route_v3_RateLimit* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_clear_stage(envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_RateLimit_stage(const envoy_config_route_v3_RateLimit* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_has_stage(const envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_clear_disable_key(envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_disable_key(const envoy_config_route_v3_RateLimit* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_clear_actions(envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action* const* envoy_config_route_v3_RateLimit_actions(const envoy_config_route_v3_RateLimit* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_RateLimit_Action* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RateLimit_actions_upb_array(const envoy_config_route_v3_RateLimit* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RateLimit_actions_mutable_upb_array(envoy_config_route_v3_RateLimit* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_clear_limit(envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Override* envoy_config_route_v3_RateLimit_limit(const envoy_config_route_v3_RateLimit* msg) {
  const envoy_config_route_v3_RateLimit_Override* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Override* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Override_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_has_limit(const envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_clear_hits_addend(envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_HitsAddend* envoy_config_route_v3_RateLimit_hits_addend(const envoy_config_route_v3_RateLimit* msg) {
  const envoy_config_route_v3_RateLimit_HitsAddend* default_val = NULL;
  const envoy_config_route_v3_RateLimit_HitsAddend* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__HitsAddend_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_has_hits_addend(const envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_clear_apply_on_stream_done(envoy_config_route_v3_RateLimit* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_apply_on_stream_done(const envoy_config_route_v3_RateLimit* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_set_stage(envoy_config_route_v3_RateLimit *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_RateLimit_mutable_stage(envoy_config_route_v3_RateLimit* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_RateLimit_stage(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_set_stage(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_set_disable_key(envoy_config_route_v3_RateLimit *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action** envoy_config_route_v3_RateLimit_mutable_actions(envoy_config_route_v3_RateLimit* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_RateLimit_Action**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action** envoy_config_route_v3_RateLimit_resize_actions(envoy_config_route_v3_RateLimit* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RateLimit_Action**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action* envoy_config_route_v3_RateLimit_add_actions(envoy_config_route_v3_RateLimit* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_RateLimit_Action* sub = (struct envoy_config_route_v3_RateLimit_Action*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_set_limit(envoy_config_route_v3_RateLimit *msg, envoy_config_route_v3_RateLimit_Override* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Override_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Override* envoy_config_route_v3_RateLimit_mutable_limit(envoy_config_route_v3_RateLimit* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Override* sub = (struct envoy_config_route_v3_RateLimit_Override*)envoy_config_route_v3_RateLimit_limit(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Override*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Override_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_set_limit(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_set_hits_addend(envoy_config_route_v3_RateLimit *msg, envoy_config_route_v3_RateLimit_HitsAddend* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__HitsAddend_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_HitsAddend* envoy_config_route_v3_RateLimit_mutable_hits_addend(envoy_config_route_v3_RateLimit* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_HitsAddend* sub = (struct envoy_config_route_v3_RateLimit_HitsAddend*)envoy_config_route_v3_RateLimit_hits_addend(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_HitsAddend*)_upb_Message_New(&envoy__config__route__v3__RateLimit__HitsAddend_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_set_hits_addend(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_set_apply_on_stream_done(envoy_config_route_v3_RateLimit *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action* envoy_config_route_v3_RateLimit_Action_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action* envoy_config_route_v3_RateLimit_Action_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action* ret = envoy_config_route_v3_RateLimit_Action_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action* envoy_config_route_v3_RateLimit_Action_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action* ret = envoy_config_route_v3_RateLimit_Action_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_serialize(const envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_serialize_ex(const envoy_config_route_v3_RateLimit_Action* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RateLimit_Action_action_specifier_source_cluster = 1,
  envoy_config_route_v3_RateLimit_Action_action_specifier_destination_cluster = 2,
  envoy_config_route_v3_RateLimit_Action_action_specifier_request_headers = 3,
  envoy_config_route_v3_RateLimit_Action_action_specifier_query_parameters = 12,
  envoy_config_route_v3_RateLimit_Action_action_specifier_remote_address = 4,
  envoy_config_route_v3_RateLimit_Action_action_specifier_generic_key = 5,
  envoy_config_route_v3_RateLimit_Action_action_specifier_header_value_match = 6,
  envoy_config_route_v3_RateLimit_Action_action_specifier_dynamic_metadata = 7,
  envoy_config_route_v3_RateLimit_Action_action_specifier_metadata = 8,
  envoy_config_route_v3_RateLimit_Action_action_specifier_extension = 9,
  envoy_config_route_v3_RateLimit_Action_action_specifier_masked_remote_address = 10,
  envoy_config_route_v3_RateLimit_Action_action_specifier_query_parameter_value_match = 11,
  envoy_config_route_v3_RateLimit_Action_action_specifier_NOT_SET = 0
} envoy_config_route_v3_RateLimit_Action_action_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RateLimit_Action_action_specifier_oneofcases envoy_config_route_v3_RateLimit_Action_action_specifier_case(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RateLimit_Action_action_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_action_specifier(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_source_cluster(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_SourceCluster* envoy_config_route_v3_RateLimit_Action_source_cluster(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_SourceCluster* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_SourceCluster* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_source_cluster(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_destination_cluster(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_DestinationCluster* envoy_config_route_v3_RateLimit_Action_destination_cluster(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_DestinationCluster* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_DestinationCluster* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_destination_cluster(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_request_headers(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_RequestHeaders* envoy_config_route_v3_RateLimit_Action_request_headers(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_RequestHeaders* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_RequestHeaders* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_request_headers(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_remote_address(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_RemoteAddress* envoy_config_route_v3_RateLimit_Action_remote_address(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_RemoteAddress* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_RemoteAddress* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_remote_address(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_generic_key(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_GenericKey* envoy_config_route_v3_RateLimit_Action_generic_key(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_GenericKey* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_GenericKey* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_generic_key(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_header_value_match(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* envoy_config_route_v3_RateLimit_Action_header_value_match(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_header_value_match(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_dynamic_metadata(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* envoy_config_route_v3_RateLimit_Action_dynamic_metadata(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_dynamic_metadata(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_metadata(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_MetaData* envoy_config_route_v3_RateLimit_Action_metadata(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_MetaData* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_MetaData* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__MetaData_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_metadata(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_extension(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RateLimit_Action_extension(const envoy_config_route_v3_RateLimit_Action* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_extension(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_masked_remote_address(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* envoy_config_route_v3_RateLimit_Action_masked_remote_address(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_masked_remote_address(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_query_parameter_value_match(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* envoy_config_route_v3_RateLimit_Action_query_parameter_value_match(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_query_parameter_value_match(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_clear_query_parameters(envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Action_QueryParameters* envoy_config_route_v3_RateLimit_Action_query_parameters(const envoy_config_route_v3_RateLimit_Action* msg) {
  const envoy_config_route_v3_RateLimit_Action_QueryParameters* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Action_QueryParameters* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_has_query_parameters(const envoy_config_route_v3_RateLimit_Action* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_source_cluster(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_SourceCluster* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_SourceCluster* envoy_config_route_v3_RateLimit_Action_mutable_source_cluster(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_SourceCluster* sub = (struct envoy_config_route_v3_RateLimit_Action_SourceCluster*)envoy_config_route_v3_RateLimit_Action_source_cluster(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_SourceCluster*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_source_cluster(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_destination_cluster(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_DestinationCluster* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_DestinationCluster* envoy_config_route_v3_RateLimit_Action_mutable_destination_cluster(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_DestinationCluster* sub = (struct envoy_config_route_v3_RateLimit_Action_DestinationCluster*)envoy_config_route_v3_RateLimit_Action_destination_cluster(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_DestinationCluster*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_destination_cluster(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_request_headers(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_RequestHeaders* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_RequestHeaders* envoy_config_route_v3_RateLimit_Action_mutable_request_headers(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_RequestHeaders* sub = (struct envoy_config_route_v3_RateLimit_Action_RequestHeaders*)envoy_config_route_v3_RateLimit_Action_request_headers(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_RequestHeaders*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_request_headers(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_remote_address(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_RemoteAddress* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_RemoteAddress* envoy_config_route_v3_RateLimit_Action_mutable_remote_address(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_RemoteAddress* sub = (struct envoy_config_route_v3_RateLimit_Action_RemoteAddress*)envoy_config_route_v3_RateLimit_Action_remote_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_RemoteAddress*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_remote_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_generic_key(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_GenericKey* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_GenericKey* envoy_config_route_v3_RateLimit_Action_mutable_generic_key(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_GenericKey* sub = (struct envoy_config_route_v3_RateLimit_Action_GenericKey*)envoy_config_route_v3_RateLimit_Action_generic_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_GenericKey*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_generic_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_header_value_match(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* envoy_config_route_v3_RateLimit_Action_mutable_header_value_match(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* sub = (struct envoy_config_route_v3_RateLimit_Action_HeaderValueMatch*)envoy_config_route_v3_RateLimit_Action_header_value_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_HeaderValueMatch*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_header_value_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_dynamic_metadata(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_DynamicMetaData* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_DynamicMetaData* envoy_config_route_v3_RateLimit_Action_mutable_dynamic_metadata(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_DynamicMetaData* sub = (struct envoy_config_route_v3_RateLimit_Action_DynamicMetaData*)envoy_config_route_v3_RateLimit_Action_dynamic_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_DynamicMetaData*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_dynamic_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_metadata(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_MetaData* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__MetaData_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_MetaData* envoy_config_route_v3_RateLimit_Action_mutable_metadata(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_MetaData* sub = (struct envoy_config_route_v3_RateLimit_Action_MetaData*)envoy_config_route_v3_RateLimit_Action_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_MetaData*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__MetaData_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_extension(envoy_config_route_v3_RateLimit_Action *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_RateLimit_Action_mutable_extension(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_route_v3_RateLimit_Action_extension(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_extension(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_masked_remote_address(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* envoy_config_route_v3_RateLimit_Action_mutable_masked_remote_address(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* sub = (struct envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress*)envoy_config_route_v3_RateLimit_Action_masked_remote_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_masked_remote_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_query_parameter_value_match(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* envoy_config_route_v3_RateLimit_Action_mutable_query_parameter_value_match(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* sub = (struct envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch*)envoy_config_route_v3_RateLimit_Action_query_parameter_value_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_query_parameter_value_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_set_query_parameters(envoy_config_route_v3_RateLimit_Action *msg, envoy_config_route_v3_RateLimit_Action_QueryParameters* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Action_QueryParameters* envoy_config_route_v3_RateLimit_Action_mutable_query_parameters(envoy_config_route_v3_RateLimit_Action* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Action_QueryParameters* sub = (struct envoy_config_route_v3_RateLimit_Action_QueryParameters*)envoy_config_route_v3_RateLimit_Action_query_parameters(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Action_QueryParameters*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_set_query_parameters(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_SourceCluster* envoy_config_route_v3_RateLimit_Action_SourceCluster_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_SourceCluster*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_SourceCluster* envoy_config_route_v3_RateLimit_Action_SourceCluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_SourceCluster* ret = envoy_config_route_v3_RateLimit_Action_SourceCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_SourceCluster* envoy_config_route_v3_RateLimit_Action_SourceCluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_SourceCluster* ret = envoy_config_route_v3_RateLimit_Action_SourceCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_SourceCluster_serialize(const envoy_config_route_v3_RateLimit_Action_SourceCluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_SourceCluster_serialize_ex(const envoy_config_route_v3_RateLimit_Action_SourceCluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_DestinationCluster* envoy_config_route_v3_RateLimit_Action_DestinationCluster_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_DestinationCluster*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_DestinationCluster* envoy_config_route_v3_RateLimit_Action_DestinationCluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_DestinationCluster* ret = envoy_config_route_v3_RateLimit_Action_DestinationCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_DestinationCluster* envoy_config_route_v3_RateLimit_Action_DestinationCluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_DestinationCluster* ret = envoy_config_route_v3_RateLimit_Action_DestinationCluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_DestinationCluster_serialize(const envoy_config_route_v3_RateLimit_Action_DestinationCluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_DestinationCluster_serialize_ex(const envoy_config_route_v3_RateLimit_Action_DestinationCluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_RequestHeaders* envoy_config_route_v3_RateLimit_Action_RequestHeaders_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_RequestHeaders*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_RequestHeaders* envoy_config_route_v3_RateLimit_Action_RequestHeaders_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_RequestHeaders* ret = envoy_config_route_v3_RateLimit_Action_RequestHeaders_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_RequestHeaders* envoy_config_route_v3_RateLimit_Action_RequestHeaders_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_RequestHeaders* ret = envoy_config_route_v3_RateLimit_Action_RequestHeaders_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_RequestHeaders_serialize(const envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_RequestHeaders_serialize_ex(const envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_RequestHeaders_clear_header_name(envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_RequestHeaders_header_name(const envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_RequestHeaders_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_RequestHeaders_descriptor_key(const envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_RequestHeaders_clear_skip_if_absent(envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg) {
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_RequestHeaders_skip_if_absent(const envoy_config_route_v3_RateLimit_Action_RequestHeaders* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_RequestHeaders_set_header_name(envoy_config_route_v3_RateLimit_Action_RequestHeaders *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_RequestHeaders_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_RequestHeaders *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_RequestHeaders_set_skip_if_absent(envoy_config_route_v3_RateLimit_Action_RequestHeaders *msg, bool value) {
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_QueryParameters* envoy_config_route_v3_RateLimit_Action_QueryParameters_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_QueryParameters*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_QueryParameters* envoy_config_route_v3_RateLimit_Action_QueryParameters_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_QueryParameters* ret = envoy_config_route_v3_RateLimit_Action_QueryParameters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_QueryParameters* envoy_config_route_v3_RateLimit_Action_QueryParameters_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_QueryParameters* ret = envoy_config_route_v3_RateLimit_Action_QueryParameters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_QueryParameters_serialize(const envoy_config_route_v3_RateLimit_Action_QueryParameters* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_QueryParameters_serialize_ex(const envoy_config_route_v3_RateLimit_Action_QueryParameters* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameters_clear_query_parameter_name(envoy_config_route_v3_RateLimit_Action_QueryParameters* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_QueryParameters_query_parameter_name(const envoy_config_route_v3_RateLimit_Action_QueryParameters* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameters_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_QueryParameters* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_QueryParameters_descriptor_key(const envoy_config_route_v3_RateLimit_Action_QueryParameters* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameters_clear_skip_if_absent(envoy_config_route_v3_RateLimit_Action_QueryParameters* msg) {
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_QueryParameters_skip_if_absent(const envoy_config_route_v3_RateLimit_Action_QueryParameters* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameters_set_query_parameter_name(envoy_config_route_v3_RateLimit_Action_QueryParameters *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameters_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_QueryParameters *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameters_set_skip_if_absent(envoy_config_route_v3_RateLimit_Action_QueryParameters *msg, bool value) {
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_RemoteAddress* envoy_config_route_v3_RateLimit_Action_RemoteAddress_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_RemoteAddress*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_RemoteAddress* envoy_config_route_v3_RateLimit_Action_RemoteAddress_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_RemoteAddress* ret = envoy_config_route_v3_RateLimit_Action_RemoteAddress_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_RemoteAddress* envoy_config_route_v3_RateLimit_Action_RemoteAddress_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_RemoteAddress* ret = envoy_config_route_v3_RateLimit_Action_RemoteAddress_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_RemoteAddress_serialize(const envoy_config_route_v3_RateLimit_Action_RemoteAddress* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_RemoteAddress_serialize_ex(const envoy_config_route_v3_RateLimit_Action_RemoteAddress* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* ret = envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* ret = envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_serialize(const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_serialize_ex(const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_clear_v4_prefix_mask_len(envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_v4_prefix_mask_len(const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_has_v4_prefix_mask_len(const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_clear_v6_prefix_mask_len(envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_v6_prefix_mask_len(const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_has_v6_prefix_mask_len(const envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_set_v4_prefix_mask_len(envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_mutable_v4_prefix_mask_len(envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_v4_prefix_mask_len(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_set_v4_prefix_mask_len(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_set_v6_prefix_mask_len(envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_mutable_v6_prefix_mask_len(envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_v6_prefix_mask_len(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress_set_v6_prefix_mask_len(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_GenericKey* envoy_config_route_v3_RateLimit_Action_GenericKey_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_GenericKey*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_GenericKey* envoy_config_route_v3_RateLimit_Action_GenericKey_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_GenericKey* ret = envoy_config_route_v3_RateLimit_Action_GenericKey_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_GenericKey* envoy_config_route_v3_RateLimit_Action_GenericKey_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_GenericKey* ret = envoy_config_route_v3_RateLimit_Action_GenericKey_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_GenericKey_serialize(const envoy_config_route_v3_RateLimit_Action_GenericKey* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_GenericKey_serialize_ex(const envoy_config_route_v3_RateLimit_Action_GenericKey* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_GenericKey_clear_descriptor_value(envoy_config_route_v3_RateLimit_Action_GenericKey* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_GenericKey_descriptor_value(const envoy_config_route_v3_RateLimit_Action_GenericKey* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_GenericKey_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_GenericKey* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_GenericKey_descriptor_key(const envoy_config_route_v3_RateLimit_Action_GenericKey* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_GenericKey_set_descriptor_value(envoy_config_route_v3_RateLimit_Action_GenericKey *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_GenericKey_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_GenericKey *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_HeaderValueMatch*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* ret = envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* ret = envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_serialize(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_serialize_ex(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_clear_descriptor_value(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_descriptor_value(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_clear_expect_match(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_expect_match(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_has_expect_match(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_clear_headers(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_HeaderMatcher* const* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_headers(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_headers_upb_array(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_headers_mutable_upb_array(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_descriptor_key(const envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_set_descriptor_value(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_set_expect_match(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_mutable_expect_match(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_expect_match(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_set_expect_match(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_mutable_headers(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher** envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_resize_headers(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_add_headers(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_HeaderValueMatch_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_HeaderValueMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_DynamicMetaData* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_DynamicMetaData*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_DynamicMetaData* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_DynamicMetaData* ret = envoy_config_route_v3_RateLimit_Action_DynamicMetaData_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_DynamicMetaData* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_DynamicMetaData* ret = envoy_config_route_v3_RateLimit_Action_DynamicMetaData_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_serialize(const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_serialize_ex(const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_DynamicMetaData_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_DynamicMetaData_descriptor_key(const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_DynamicMetaData_clear_metadata_key(envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_metadata_v3_MetadataKey* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_metadata_key(const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  const struct envoy_type_metadata_v3_MetadataKey* default_val = NULL;
  const struct envoy_type_metadata_v3_MetadataKey* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_DynamicMetaData_has_metadata_key(const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_DynamicMetaData_clear_default_value(envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_DynamicMetaData_default_value(const envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_DynamicMetaData_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_DynamicMetaData *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_DynamicMetaData_set_metadata_key(envoy_config_route_v3_RateLimit_Action_DynamicMetaData *msg, struct envoy_type_metadata_v3_MetadataKey* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKey* envoy_config_route_v3_RateLimit_Action_DynamicMetaData_mutable_metadata_key(envoy_config_route_v3_RateLimit_Action_DynamicMetaData* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKey* sub = (struct envoy_type_metadata_v3_MetadataKey*)envoy_config_route_v3_RateLimit_Action_DynamicMetaData_metadata_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKey*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_DynamicMetaData_set_metadata_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_DynamicMetaData_set_default_value(envoy_config_route_v3_RateLimit_Action_DynamicMetaData *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_MetaData* envoy_config_route_v3_RateLimit_Action_MetaData_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_MetaData*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__MetaData_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_MetaData* envoy_config_route_v3_RateLimit_Action_MetaData_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_MetaData* ret = envoy_config_route_v3_RateLimit_Action_MetaData_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_MetaData* envoy_config_route_v3_RateLimit_Action_MetaData_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_MetaData* ret = envoy_config_route_v3_RateLimit_Action_MetaData_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_MetaData_serialize(const envoy_config_route_v3_RateLimit_Action_MetaData* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_MetaData_serialize_ex(const envoy_config_route_v3_RateLimit_Action_MetaData* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_MetaData_descriptor_key(const envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_clear_metadata_key(envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_metadata_v3_MetadataKey* envoy_config_route_v3_RateLimit_Action_MetaData_metadata_key(const envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const struct envoy_type_metadata_v3_MetadataKey* default_val = NULL;
  const struct envoy_type_metadata_v3_MetadataKey* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_MetaData_has_metadata_key(const envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_clear_default_value(envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_MetaData_default_value(const envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_clear_source(envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_route_v3_RateLimit_Action_MetaData_source(const envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_clear_skip_if_absent(envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_MetaData_skip_if_absent(const envoy_config_route_v3_RateLimit_Action_MetaData* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_MetaData *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_set_metadata_key(envoy_config_route_v3_RateLimit_Action_MetaData *msg, struct envoy_type_metadata_v3_MetadataKey* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKey* envoy_config_route_v3_RateLimit_Action_MetaData_mutable_metadata_key(envoy_config_route_v3_RateLimit_Action_MetaData* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKey* sub = (struct envoy_type_metadata_v3_MetadataKey*)envoy_config_route_v3_RateLimit_Action_MetaData_metadata_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKey*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_MetaData_set_metadata_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_set_default_value(envoy_config_route_v3_RateLimit_Action_MetaData *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_set_source(envoy_config_route_v3_RateLimit_Action_MetaData *msg, int32_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_MetaData_set_skip_if_absent(envoy_config_route_v3_RateLimit_Action_MetaData *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* ret = envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* ret = envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_serialize(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_serialize_ex(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_clear_descriptor_value(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_descriptor_value(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_clear_expect_match(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_expect_match(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_has_expect_match(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_clear_query_parameters(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_QueryParameterMatcher* const* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_query_parameters(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_route_v3_QueryParameterMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_query_parameters_upb_array(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_query_parameters_mutable_upb_array(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_clear_descriptor_key(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_descriptor_key(const envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_set_descriptor_value(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_set_expect_match(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_mutable_expect_match(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_expect_match(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_set_expect_match(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher** envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_mutable_query_parameters(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_route_v3_QueryParameterMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher** envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_resize_query_parameters(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_QueryParameterMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_QueryParameterMatcher* envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_add_query_parameters(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__QueryParameterMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_QueryParameterMatcher* sub = (struct envoy_config_route_v3_QueryParameterMatcher*)_upb_Message_New(&envoy__config__route__v3__QueryParameterMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch_set_descriptor_key(envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_RateLimit_Override* envoy_config_route_v3_RateLimit_Override_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Override*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Override_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Override* envoy_config_route_v3_RateLimit_Override_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Override* ret = envoy_config_route_v3_RateLimit_Override_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Override_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Override* envoy_config_route_v3_RateLimit_Override_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Override* ret = envoy_config_route_v3_RateLimit_Override_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Override_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Override_serialize(const envoy_config_route_v3_RateLimit_Override* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Override_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Override_serialize_ex(const envoy_config_route_v3_RateLimit_Override* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Override_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_RateLimit_Override_override_specifier_dynamic_metadata = 1,
  envoy_config_route_v3_RateLimit_Override_override_specifier_NOT_SET = 0
} envoy_config_route_v3_RateLimit_Override_override_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_RateLimit_Override_override_specifier_oneofcases envoy_config_route_v3_RateLimit_Override_override_specifier_case(const envoy_config_route_v3_RateLimit_Override* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_RateLimit_Override_override_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Override_clear_override_specifier(envoy_config_route_v3_RateLimit_Override* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Override_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Override_clear_dynamic_metadata(envoy_config_route_v3_RateLimit_Override* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* envoy_config_route_v3_RateLimit_Override_dynamic_metadata(const envoy_config_route_v3_RateLimit_Override* msg) {
  const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* default_val = NULL;
  const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Override_has_dynamic_metadata(const envoy_config_route_v3_RateLimit_Override* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Override_set_dynamic_metadata(envoy_config_route_v3_RateLimit_Override *msg, envoy_config_route_v3_RateLimit_Override_DynamicMetadata* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_RateLimit_Override_DynamicMetadata* envoy_config_route_v3_RateLimit_Override_mutable_dynamic_metadata(envoy_config_route_v3_RateLimit_Override* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_RateLimit_Override_DynamicMetadata* sub = (struct envoy_config_route_v3_RateLimit_Override_DynamicMetadata*)envoy_config_route_v3_RateLimit_Override_dynamic_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_RateLimit_Override_DynamicMetadata*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Override_set_dynamic_metadata(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RateLimit_Override_DynamicMetadata* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_Override_DynamicMetadata*)_upb_Message_New(&envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_Override_DynamicMetadata* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Override_DynamicMetadata* ret = envoy_config_route_v3_RateLimit_Override_DynamicMetadata_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_Override_DynamicMetadata* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_Override_DynamicMetadata* ret = envoy_config_route_v3_RateLimit_Override_DynamicMetadata_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_serialize(const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_serialize_ex(const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_Override_DynamicMetadata_clear_metadata_key(envoy_config_route_v3_RateLimit_Override_DynamicMetadata* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_metadata_v3_MetadataKey* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_metadata_key(const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* msg) {
  const struct envoy_type_metadata_v3_MetadataKey* default_val = NULL;
  const struct envoy_type_metadata_v3_MetadataKey* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_Override_DynamicMetadata_has_metadata_key(const envoy_config_route_v3_RateLimit_Override_DynamicMetadata* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_RateLimit_Override_DynamicMetadata_set_metadata_key(envoy_config_route_v3_RateLimit_Override_DynamicMetadata *msg, struct envoy_type_metadata_v3_MetadataKey* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKey* envoy_config_route_v3_RateLimit_Override_DynamicMetadata_mutable_metadata_key(envoy_config_route_v3_RateLimit_Override_DynamicMetadata* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKey* sub = (struct envoy_type_metadata_v3_MetadataKey*)envoy_config_route_v3_RateLimit_Override_DynamicMetadata_metadata_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKey*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_Override_DynamicMetadata_set_metadata_key(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_route_v3_RateLimit_HitsAddend* envoy_config_route_v3_RateLimit_HitsAddend_new(upb_Arena* arena) {
  return (envoy_config_route_v3_RateLimit_HitsAddend*)_upb_Message_New(&envoy__config__route__v3__RateLimit__HitsAddend_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_RateLimit_HitsAddend* envoy_config_route_v3_RateLimit_HitsAddend_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_HitsAddend* ret = envoy_config_route_v3_RateLimit_HitsAddend_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__HitsAddend_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_RateLimit_HitsAddend* envoy_config_route_v3_RateLimit_HitsAddend_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_RateLimit_HitsAddend* ret = envoy_config_route_v3_RateLimit_HitsAddend_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__RateLimit__HitsAddend_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_HitsAddend_serialize(const envoy_config_route_v3_RateLimit_HitsAddend* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__HitsAddend_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_RateLimit_HitsAddend_serialize_ex(const envoy_config_route_v3_RateLimit_HitsAddend* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__RateLimit__HitsAddend_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_HitsAddend_clear_number(envoy_config_route_v3_RateLimit_HitsAddend* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_route_v3_RateLimit_HitsAddend_number(const envoy_config_route_v3_RateLimit_HitsAddend* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_RateLimit_HitsAddend_has_number(const envoy_config_route_v3_RateLimit_HitsAddend* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_RateLimit_HitsAddend_clear_format(envoy_config_route_v3_RateLimit_HitsAddend* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_RateLimit_HitsAddend_format(const envoy_config_route_v3_RateLimit_HitsAddend* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_RateLimit_HitsAddend_set_number(envoy_config_route_v3_RateLimit_HitsAddend *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_route_v3_RateLimit_HitsAddend_mutable_number(envoy_config_route_v3_RateLimit_HitsAddend* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_route_v3_RateLimit_HitsAddend_number(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_route_v3_RateLimit_HitsAddend_set_number(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_RateLimit_HitsAddend_set_format(envoy_config_route_v3_RateLimit_HitsAddend *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_HeaderMatcher_new(upb_Arena* arena) {
  return (envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_HeaderMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_HeaderMatcher* ret = envoy_config_route_v3_HeaderMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__HeaderMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_HeaderMatcher* envoy_config_route_v3_HeaderMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_HeaderMatcher* ret = envoy_config_route_v3_HeaderMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__HeaderMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_HeaderMatcher_serialize(const envoy_config_route_v3_HeaderMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__HeaderMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_HeaderMatcher_serialize_ex(const envoy_config_route_v3_HeaderMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__HeaderMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_exact_match = 4,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_safe_regex_match = 11,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_range_match = 6,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_present_match = 7,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_prefix_match = 9,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_suffix_match = 10,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_contains_match = 12,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_string_match = 13,
  envoy_config_route_v3_HeaderMatcher_header_match_specifier_NOT_SET = 0
} envoy_config_route_v3_HeaderMatcher_header_match_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_HeaderMatcher_header_match_specifier_oneofcases envoy_config_route_v3_HeaderMatcher_header_match_specifier_case(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_HeaderMatcher_header_match_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_header_match_specifier(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__HeaderMatcher_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_name(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_HeaderMatcher_name(const envoy_config_route_v3_HeaderMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_exact_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_HeaderMatcher_exact_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_exact_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_range_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Int64Range* envoy_config_route_v3_HeaderMatcher_range_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const struct envoy_type_v3_Int64Range* default_val = NULL;
  const struct envoy_type_v3_Int64Range* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_range_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_present_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_present_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_present_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_invert_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {8, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_invert_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_prefix_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_HeaderMatcher_prefix_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_prefix_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_suffix_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_HeaderMatcher_suffix_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {10, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_suffix_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_safe_regex_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(24, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_RegexMatcher* envoy_config_route_v3_HeaderMatcher_safe_regex_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const struct envoy_type_matcher_v3_RegexMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_RegexMatcher* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(24, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_safe_regex_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(24, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_contains_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_HeaderMatcher_contains_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {12, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_contains_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_string_match(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(24, 32), -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_route_v3_HeaderMatcher_string_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(24, 32), -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_has_string_match(const envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(24, 32), -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_clear_treat_missing_header_as_empty(envoy_config_route_v3_HeaderMatcher* msg) {
  const upb_MiniTableField field = {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_HeaderMatcher_treat_missing_header_as_empty(const envoy_config_route_v3_HeaderMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_name(envoy_config_route_v3_HeaderMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_exact_match(envoy_config_route_v3_HeaderMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_range_match(envoy_config_route_v3_HeaderMatcher *msg, struct envoy_type_v3_Int64Range* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int64Range_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Int64Range* envoy_config_route_v3_HeaderMatcher_mutable_range_match(envoy_config_route_v3_HeaderMatcher* msg, upb_Arena* arena) {
  struct envoy_type_v3_Int64Range* sub = (struct envoy_type_v3_Int64Range*)envoy_config_route_v3_HeaderMatcher_range_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Int64Range*)_upb_Message_New(&envoy__type__v3__Int64Range_msg_init, arena);
    if (sub) envoy_config_route_v3_HeaderMatcher_set_range_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_present_match(envoy_config_route_v3_HeaderMatcher *msg, bool value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_invert_match(envoy_config_route_v3_HeaderMatcher *msg, bool value) {
  const upb_MiniTableField field = {8, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_prefix_match(envoy_config_route_v3_HeaderMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_suffix_match(envoy_config_route_v3_HeaderMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_safe_regex_match(envoy_config_route_v3_HeaderMatcher *msg, struct envoy_type_matcher_v3_RegexMatcher* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(24, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__RegexMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_RegexMatcher* envoy_config_route_v3_HeaderMatcher_mutable_safe_regex_match(envoy_config_route_v3_HeaderMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_RegexMatcher* sub = (struct envoy_type_matcher_v3_RegexMatcher*)envoy_config_route_v3_HeaderMatcher_safe_regex_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_RegexMatcher*)_upb_Message_New(&envoy__type__matcher__v3__RegexMatcher_msg_init, arena);
    if (sub) envoy_config_route_v3_HeaderMatcher_set_safe_regex_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_contains_match(envoy_config_route_v3_HeaderMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {12, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_string_match(envoy_config_route_v3_HeaderMatcher *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(24, 32), -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_route_v3_HeaderMatcher_mutable_string_match(envoy_config_route_v3_HeaderMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_route_v3_HeaderMatcher_string_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_route_v3_HeaderMatcher_set_string_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_HeaderMatcher_set_treat_missing_header_as_empty(envoy_config_route_v3_HeaderMatcher *msg, bool value) {
  const upb_MiniTableField field = {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_QueryParameterMatcher* envoy_config_route_v3_QueryParameterMatcher_new(upb_Arena* arena) {
  return (envoy_config_route_v3_QueryParameterMatcher*)_upb_Message_New(&envoy__config__route__v3__QueryParameterMatcher_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher* envoy_config_route_v3_QueryParameterMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_QueryParameterMatcher* ret = envoy_config_route_v3_QueryParameterMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__QueryParameterMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher* envoy_config_route_v3_QueryParameterMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_QueryParameterMatcher* ret = envoy_config_route_v3_QueryParameterMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__QueryParameterMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_QueryParameterMatcher_serialize(const envoy_config_route_v3_QueryParameterMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__QueryParameterMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_QueryParameterMatcher_serialize_ex(const envoy_config_route_v3_QueryParameterMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__QueryParameterMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_string_match = 5,
  envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_present_match = 6,
  envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_NOT_SET = 0
} envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_oneofcases;
UPB_INLINE envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_oneofcases envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_case(const envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_route_v3_QueryParameterMatcher_query_parameter_match_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_clear_query_parameter_match_specifier(envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__route__v3__QueryParameterMatcher_msg_init, &field);
}
UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_clear_name(envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_route_v3_QueryParameterMatcher_name(const envoy_config_route_v3_QueryParameterMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_clear_string_match(envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_route_v3_QueryParameterMatcher_string_match(const envoy_config_route_v3_QueryParameterMatcher* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_QueryParameterMatcher_has_string_match(const envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_clear_present_match(envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 32), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_QueryParameterMatcher_present_match(const envoy_config_route_v3_QueryParameterMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 32), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_QueryParameterMatcher_has_present_match(const envoy_config_route_v3_QueryParameterMatcher* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 32), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_set_name(envoy_config_route_v3_QueryParameterMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_set_string_match(envoy_config_route_v3_QueryParameterMatcher *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_route_v3_QueryParameterMatcher_mutable_string_match(envoy_config_route_v3_QueryParameterMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_route_v3_QueryParameterMatcher_string_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_route_v3_QueryParameterMatcher_set_string_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_QueryParameterMatcher_set_present_match(envoy_config_route_v3_QueryParameterMatcher *msg, bool value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 32), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_route_v3_InternalRedirectPolicy* envoy_config_route_v3_InternalRedirectPolicy_new(upb_Arena* arena) {
  return (envoy_config_route_v3_InternalRedirectPolicy*)_upb_Message_New(&envoy__config__route__v3__InternalRedirectPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_InternalRedirectPolicy* envoy_config_route_v3_InternalRedirectPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_InternalRedirectPolicy* ret = envoy_config_route_v3_InternalRedirectPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__InternalRedirectPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_InternalRedirectPolicy* envoy_config_route_v3_InternalRedirectPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_InternalRedirectPolicy* ret = envoy_config_route_v3_InternalRedirectPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__InternalRedirectPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_InternalRedirectPolicy_serialize(const envoy_config_route_v3_InternalRedirectPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__InternalRedirectPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_InternalRedirectPolicy_serialize_ex(const envoy_config_route_v3_InternalRedirectPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__InternalRedirectPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_clear_max_internal_redirects(envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_route_v3_InternalRedirectPolicy_max_internal_redirects(const envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_InternalRedirectPolicy_has_max_internal_redirects(const envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_clear_redirect_response_codes(envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* envoy_config_route_v3_InternalRedirectPolicy_redirect_response_codes(const envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_InternalRedirectPolicy_redirect_response_codes_upb_array(const envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_InternalRedirectPolicy_redirect_response_codes_mutable_upb_array(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_clear_predicates(envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* const* envoy_config_route_v3_InternalRedirectPolicy_predicates(const envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_route_v3_InternalRedirectPolicy_predicates_upb_array(const envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_InternalRedirectPolicy_predicates_mutable_upb_array(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_clear_allow_cross_scheme_redirect(envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_InternalRedirectPolicy_allow_cross_scheme_redirect(const envoy_config_route_v3_InternalRedirectPolicy* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_clear_response_headers_to_copy(envoy_config_route_v3_InternalRedirectPolicy* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_route_v3_InternalRedirectPolicy_response_headers_to_copy(const envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_route_v3_InternalRedirectPolicy_response_headers_to_copy_upb_array(const envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_route_v3_InternalRedirectPolicy_response_headers_to_copy_mutable_upb_array(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_set_max_internal_redirects(envoy_config_route_v3_InternalRedirectPolicy *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_route_v3_InternalRedirectPolicy_mutable_max_internal_redirects(envoy_config_route_v3_InternalRedirectPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_route_v3_InternalRedirectPolicy_max_internal_redirects(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_route_v3_InternalRedirectPolicy_set_max_internal_redirects(msg, sub);
  }
  return sub;
}
UPB_INLINE uint32_t* envoy_config_route_v3_InternalRedirectPolicy_mutable_redirect_response_codes(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* envoy_config_route_v3_InternalRedirectPolicy_resize_redirect_response_codes(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_InternalRedirectPolicy_add_redirect_response_codes(envoy_config_route_v3_InternalRedirectPolicy* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_route_v3_InternalRedirectPolicy_mutable_predicates(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig** envoy_config_route_v3_InternalRedirectPolicy_resize_predicates(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_TypedExtensionConfig**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_route_v3_InternalRedirectPolicy_add_predicates(envoy_config_route_v3_InternalRedirectPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_route_v3_InternalRedirectPolicy_set_allow_cross_scheme_redirect(envoy_config_route_v3_InternalRedirectPolicy *msg, bool value) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_config_route_v3_InternalRedirectPolicy_mutable_response_headers_to_copy(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_route_v3_InternalRedirectPolicy_resize_response_headers_to_copy(envoy_config_route_v3_InternalRedirectPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_route_v3_InternalRedirectPolicy_add_response_headers_to_copy(envoy_config_route_v3_InternalRedirectPolicy* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_config_route_v3_FilterConfig* envoy_config_route_v3_FilterConfig_new(upb_Arena* arena) {
  return (envoy_config_route_v3_FilterConfig*)_upb_Message_New(&envoy__config__route__v3__FilterConfig_msg_init, arena);
}
UPB_INLINE envoy_config_route_v3_FilterConfig* envoy_config_route_v3_FilterConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_route_v3_FilterConfig* ret = envoy_config_route_v3_FilterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__FilterConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_route_v3_FilterConfig* envoy_config_route_v3_FilterConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_route_v3_FilterConfig* ret = envoy_config_route_v3_FilterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__route__v3__FilterConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_route_v3_FilterConfig_serialize(const envoy_config_route_v3_FilterConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__FilterConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_route_v3_FilterConfig_serialize_ex(const envoy_config_route_v3_FilterConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__route__v3__FilterConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_route_v3_FilterConfig_clear_config(envoy_config_route_v3_FilterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_route_v3_FilterConfig_config(const envoy_config_route_v3_FilterConfig* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_route_v3_FilterConfig_has_config(const envoy_config_route_v3_FilterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_route_v3_FilterConfig_clear_is_optional(envoy_config_route_v3_FilterConfig* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_FilterConfig_is_optional(const envoy_config_route_v3_FilterConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_route_v3_FilterConfig_clear_disabled(envoy_config_route_v3_FilterConfig* msg) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_route_v3_FilterConfig_disabled(const envoy_config_route_v3_FilterConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_route_v3_FilterConfig_set_config(envoy_config_route_v3_FilterConfig *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_route_v3_FilterConfig_mutable_config(envoy_config_route_v3_FilterConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_route_v3_FilterConfig_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_route_v3_FilterConfig_set_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_route_v3_FilterConfig_set_is_optional(envoy_config_route_v3_FilterConfig *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_route_v3_FilterConfig_set_disabled(envoy_config_route_v3_FilterConfig *msg, bool value) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
