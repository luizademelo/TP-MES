
#ifndef ENVOY_CONFIG_CLUSTER_V3_CLUSTER_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CLUSTER_V3_CLUSTER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/cluster/v3/cluster.upb_minitable.h"

#include "envoy/config/cluster/v3/circuit_breaker.upb_minitable.h"
#include "envoy/config/cluster/v3/filter.upb_minitable.h"
#include "envoy/config/cluster/v3/outlier_detection.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/health_check.upb_minitable.h"
#include "envoy/config/core/v3/protocol.upb_minitable.h"
#include "envoy/config/core/v3/resolver.upb_minitable.h"
#include "envoy/config/endpoint/v3/endpoint.upb_minitable.h"
#include "envoy/type/metadata/v3/metadata.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/core/v3/collection_entry.upb_minitable.h"
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

typedef struct envoy_config_cluster_v3_ClusterCollection { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_ClusterCollection;
typedef struct envoy_config_cluster_v3_Cluster { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster;
typedef struct envoy_config_cluster_v3_Cluster_TransportSocketMatch { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_TransportSocketMatch;
typedef struct envoy_config_cluster_v3_Cluster_CustomClusterType { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_CustomClusterType;
typedef struct envoy_config_cluster_v3_Cluster_EdsClusterConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_EdsClusterConfig;
typedef struct envoy_config_cluster_v3_Cluster_LbSubsetConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_LbSubsetConfig;
typedef struct envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector;
typedef struct envoy_config_cluster_v3_Cluster_SlowStartConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_SlowStartConfig;
typedef struct envoy_config_cluster_v3_Cluster_RoundRobinLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_RoundRobinLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_LeastRequestLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_LeastRequestLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_RingHashLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_RingHashLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_MaglevLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_MaglevLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_OriginalDstLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_OriginalDstLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_CommonLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_CommonLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig;
typedef struct envoy_config_cluster_v3_Cluster_RefreshRate { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_RefreshRate;
typedef struct envoy_config_cluster_v3_Cluster_PreconnectPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Cluster_PreconnectPolicy;
typedef struct envoy_config_cluster_v3_LoadBalancingPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_LoadBalancingPolicy;
typedef struct envoy_config_cluster_v3_LoadBalancingPolicy_Policy { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_LoadBalancingPolicy_Policy;
typedef struct envoy_config_cluster_v3_UpstreamConnectionOptions { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_UpstreamConnectionOptions;
typedef struct envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig;
typedef struct envoy_config_cluster_v3_TrackClusterStats { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_TrackClusterStats;
struct envoy_config_cluster_v3_CircuitBreakers;
struct envoy_config_cluster_v3_Filter;
struct envoy_config_cluster_v3_OutlierDetection;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_BindConfig;
struct envoy_config_core_v3_ConfigSource;
struct envoy_config_core_v3_DnsResolutionConfig;
struct envoy_config_core_v3_HealthCheck;
struct envoy_config_core_v3_HealthStatusSet;
struct envoy_config_core_v3_Http1ProtocolOptions;
struct envoy_config_core_v3_Http2ProtocolOptions;
struct envoy_config_core_v3_HttpProtocolOptions;
struct envoy_config_core_v3_Metadata;
struct envoy_config_core_v3_RuntimeDouble;
struct envoy_config_core_v3_TcpKeepalive;
struct envoy_config_core_v3_TransportSocket;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_core_v3_UpstreamHttpProtocolOptions;
struct envoy_config_endpoint_v3_ClusterLoadAssignment;
struct envoy_type_metadata_v3_MetadataKey;
struct envoy_type_v3_Percent;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_DoubleValue;
struct google_protobuf_Duration;
struct google_protobuf_Struct;
struct google_protobuf_UInt32Value;
struct google_protobuf_UInt64Value;
struct xds_core_v3_CollectionEntry;

typedef enum {
  envoy_config_cluster_v3_Cluster_USE_CONFIGURED_PROTOCOL = 0,
  envoy_config_cluster_v3_Cluster_USE_DOWNSTREAM_PROTOCOL = 1
} envoy_config_cluster_v3_Cluster_ClusterProtocolSelection;

typedef enum {
  envoy_config_cluster_v3_Cluster_STATIC = 0,
  envoy_config_cluster_v3_Cluster_STRICT_DNS = 1,
  envoy_config_cluster_v3_Cluster_LOGICAL_DNS = 2,
  envoy_config_cluster_v3_Cluster_EDS = 3,
  envoy_config_cluster_v3_Cluster_ORIGINAL_DST = 4
} envoy_config_cluster_v3_Cluster_DiscoveryType;

typedef enum {
  envoy_config_cluster_v3_Cluster_AUTO = 0,
  envoy_config_cluster_v3_Cluster_V4_ONLY = 1,
  envoy_config_cluster_v3_Cluster_V6_ONLY = 2,
  envoy_config_cluster_v3_Cluster_V4_PREFERRED = 3,
  envoy_config_cluster_v3_Cluster_ALL = 4
} envoy_config_cluster_v3_Cluster_DnsLookupFamily;

typedef enum {
  envoy_config_cluster_v3_Cluster_ROUND_ROBIN = 0,
  envoy_config_cluster_v3_Cluster_LEAST_REQUEST = 1,
  envoy_config_cluster_v3_Cluster_RING_HASH = 2,
  envoy_config_cluster_v3_Cluster_RANDOM = 3,
  envoy_config_cluster_v3_Cluster_MAGLEV = 5,
  envoy_config_cluster_v3_Cluster_CLUSTER_PROVIDED = 6,
  envoy_config_cluster_v3_Cluster_LOAD_BALANCING_POLICY_CONFIG = 7
} envoy_config_cluster_v3_Cluster_LbPolicy;

typedef enum {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_NO_FALLBACK = 0,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_ANY_ENDPOINT = 1,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_DEFAULT_SUBSET = 2
} envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetFallbackPolicy;

typedef enum {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_METADATA_NO_FALLBACK = 0,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_FALLBACK_LIST = 1
} envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetMetadataFallbackPolicy;

typedef enum {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_NOT_DEFINED = 0,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_NO_FALLBACK = 1,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_ANY_ENDPOINT = 2,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_DEFAULT_SUBSET = 3,
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_KEYS_SUBSET = 4
} envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_LbSubsetSelectorFallbackPolicy;

typedef enum {
  envoy_config_cluster_v3_Cluster_RingHashLbConfig_XX_HASH = 0,
  envoy_config_cluster_v3_Cluster_RingHashLbConfig_MURMUR_HASH_2 = 1
} envoy_config_cluster_v3_Cluster_RingHashLbConfig_HashFunction;

typedef enum {
  envoy_config_cluster_v3_UpstreamConnectionOptions_DEFAULT = 0,
  envoy_config_cluster_v3_UpstreamConnectionOptions_V4 = 1,
  envoy_config_cluster_v3_UpstreamConnectionOptions_V6 = 2
} envoy_config_cluster_v3_UpstreamConnectionOptions_FirstAddressFamilyVersion;

UPB_INLINE envoy_config_cluster_v3_ClusterCollection* envoy_config_cluster_v3_ClusterCollection_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_ClusterCollection*)_upb_Message_New(&envoy__config__cluster__v3__ClusterCollection_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_ClusterCollection* envoy_config_cluster_v3_ClusterCollection_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_ClusterCollection* ret = envoy_config_cluster_v3_ClusterCollection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__ClusterCollection_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_ClusterCollection* envoy_config_cluster_v3_ClusterCollection_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_ClusterCollection* ret = envoy_config_cluster_v3_ClusterCollection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__ClusterCollection_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_ClusterCollection_serialize(const envoy_config_cluster_v3_ClusterCollection* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__ClusterCollection_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_ClusterCollection_serialize_ex(const envoy_config_cluster_v3_ClusterCollection* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__ClusterCollection_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_ClusterCollection_clear_entries(envoy_config_cluster_v3_ClusterCollection* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_core_v3_CollectionEntry* envoy_config_cluster_v3_ClusterCollection_entries(const envoy_config_cluster_v3_ClusterCollection* msg) {
  const struct xds_core_v3_CollectionEntry* default_val = NULL;
  const struct xds_core_v3_CollectionEntry* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_ClusterCollection_has_entries(const envoy_config_cluster_v3_ClusterCollection* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_ClusterCollection_set_entries(envoy_config_cluster_v3_ClusterCollection *msg, struct xds_core_v3_CollectionEntry* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_CollectionEntry* envoy_config_cluster_v3_ClusterCollection_mutable_entries(envoy_config_cluster_v3_ClusterCollection* msg, upb_Arena* arena) {
  struct xds_core_v3_CollectionEntry* sub = (struct xds_core_v3_CollectionEntry*)envoy_config_cluster_v3_ClusterCollection_entries(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_CollectionEntry*)_upb_Message_New(&xds__core__v3__CollectionEntry_msg_init, arena);
    if (sub) envoy_config_cluster_v3_ClusterCollection_set_entries(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster* envoy_config_cluster_v3_Cluster_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster*)_upb_Message_New(&envoy__config__cluster__v3__Cluster_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster* envoy_config_cluster_v3_Cluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster* ret = envoy_config_cluster_v3_Cluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster* envoy_config_cluster_v3_Cluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster* ret = envoy_config_cluster_v3_Cluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_serialize(const envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_serialize_ex(const envoy_config_cluster_v3_Cluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_cluster_v3_Cluster_cluster_discovery_type_type = 2,
  envoy_config_cluster_v3_Cluster_cluster_discovery_type_cluster_type = 38,
  envoy_config_cluster_v3_Cluster_cluster_discovery_type_NOT_SET = 0
} envoy_config_cluster_v3_Cluster_cluster_discovery_type_oneofcases;
UPB_INLINE envoy_config_cluster_v3_Cluster_cluster_discovery_type_oneofcases envoy_config_cluster_v3_Cluster_cluster_discovery_type_case(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_Cluster_cluster_discovery_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_cluster_discovery_type(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster_msg_init, &field);
}
typedef enum {
  envoy_config_cluster_v3_Cluster_lb_config_ring_hash_lb_config = 23,
  envoy_config_cluster_v3_Cluster_lb_config_maglev_lb_config = 52,
  envoy_config_cluster_v3_Cluster_lb_config_original_dst_lb_config = 34,
  envoy_config_cluster_v3_Cluster_lb_config_least_request_lb_config = 37,
  envoy_config_cluster_v3_Cluster_lb_config_round_robin_lb_config = 56,
  envoy_config_cluster_v3_Cluster_lb_config_NOT_SET = 0
} envoy_config_cluster_v3_Cluster_lb_config_oneofcases;
UPB_INLINE envoy_config_cluster_v3_Cluster_lb_config_oneofcases envoy_config_cluster_v3_Cluster_lb_config_case(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_Cluster_lb_config_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster_msg_init, &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_name(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(188, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Cluster_name(const envoy_config_cluster_v3_Cluster* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(188, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_type(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_type(const envoy_config_cluster_v3_Cluster* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_type(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_eds_cluster_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_EdsClusterConfig* envoy_config_cluster_v3_Cluster_eds_cluster_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_EdsClusterConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_EdsClusterConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_eds_cluster_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_connect_timeout(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_connect_timeout(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_connect_timeout(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_per_connection_buffer_limit_bytes(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_per_connection_buffer_limit_bytes(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_per_connection_buffer_limit_bytes(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_lb_policy(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_lb_policy(const envoy_config_cluster_v3_Cluster* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_health_checks(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HealthCheck* const* envoy_config_cluster_v3_Cluster_health_checks(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_HealthCheck* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_health_checks_upb_array(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_health_checks_mutable_upb_array(envoy_config_cluster_v3_Cluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_max_requests_per_connection(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 104), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_max_requests_per_connection(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(40, 104), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_max_requests_per_connection(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 104), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_circuit_breakers(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 112), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_cluster_v3_CircuitBreakers* envoy_config_cluster_v3_Cluster_circuit_breakers(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_cluster_v3_CircuitBreakers* default_val = NULL;
  const struct envoy_config_cluster_v3_CircuitBreakers* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(44, 112), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_circuit_breakers(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 112), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_http_protocol_options(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 120), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http1ProtocolOptions* envoy_config_cluster_v3_Cluster_http_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_Http1ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http1ProtocolOptions* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(48, 120), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_http_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 120), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_http2_protocol_options(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(52, 128), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http2ProtocolOptions* envoy_config_cluster_v3_Cluster_http2_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_Http2ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http2ProtocolOptions* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(52, 128), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_http2_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(52, 128), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_dns_refresh_rate(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 136), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_dns_refresh_rate(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(56, 136), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_dns_refresh_rate(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 136), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_dns_lookup_family(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_dns_lookup_family(const envoy_config_cluster_v3_Cluster* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {17, UPB_SIZE(60, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_dns_resolvers(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* const* envoy_config_cluster_v3_Cluster_dns_resolvers(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_dns_resolvers_upb_array(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_dns_resolvers_mutable_upb_array(envoy_config_cluster_v3_Cluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_outlier_detection(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 152), 72, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_cluster_v3_OutlierDetection* envoy_config_cluster_v3_Cluster_outlier_detection(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_cluster_v3_OutlierDetection* default_val = NULL;
  const struct envoy_config_cluster_v3_OutlierDetection* ret;
  const upb_MiniTableField field = {19, UPB_SIZE(68, 152), 72, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__OutlierDetection_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_outlier_detection(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 152), 72, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_cleanup_interval(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(72, 160), 73, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_cleanup_interval(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(72, 160), 73, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_cleanup_interval(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(72, 160), 73, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_upstream_bind_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 168), 74, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_BindConfig* envoy_config_cluster_v3_Cluster_upstream_bind_config(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_BindConfig* default_val = NULL;
  const struct envoy_config_core_v3_BindConfig* ret;
  const upb_MiniTableField field = {21, UPB_SIZE(76, 168), 74, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BindConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_upstream_bind_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 168), 74, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_lb_subset_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 176), 75, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_LbSubsetConfig* envoy_config_cluster_v3_Cluster_lb_subset_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_LbSubsetConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_LbSubsetConfig* ret;
  const upb_MiniTableField field = {22, UPB_SIZE(80, 176), 75, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_lb_subset_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 176), 75, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_ring_hash_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_RingHashLbConfig* envoy_config_cluster_v3_Cluster_ring_hash_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_RingHashLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_RingHashLbConfig* ret;
  const upb_MiniTableField field = {23, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_ring_hash_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_transport_socket(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(84, 184), 76, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TransportSocket* envoy_config_cluster_v3_Cluster_transport_socket(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_TransportSocket* default_val = NULL;
  const struct envoy_config_core_v3_TransportSocket* ret;
  const upb_MiniTableField field = {24, UPB_SIZE(84, 184), 76, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_transport_socket(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(84, 184), 76, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_metadata(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(88, 192), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_cluster_v3_Cluster_metadata(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {25, UPB_SIZE(88, 192), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_metadata(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(88, 192), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_protocol_selection(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(92, 28), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_protocol_selection(const envoy_config_cluster_v3_Cluster* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {26, UPB_SIZE(92, 28), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_common_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(96, 200), 78, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_CommonLbConfig* envoy_config_cluster_v3_Cluster_common_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_CommonLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_CommonLbConfig* ret;
  const upb_MiniTableField field = {27, UPB_SIZE(96, 200), 78, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_common_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(96, 200), 78, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_alt_stat_name(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(196, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Cluster_alt_stat_name(const envoy_config_cluster_v3_Cluster* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {28, UPB_SIZE(196, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_common_http_protocol_options(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(100, 208), 79, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HttpProtocolOptions* envoy_config_cluster_v3_Cluster_common_http_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_HttpProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_HttpProtocolOptions* ret;
  const upb_MiniTableField field = {29, UPB_SIZE(100, 208), 79, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_common_http_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(100, 208), 79, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_upstream_connection_options(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(104, 216), 80, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_UpstreamConnectionOptions* envoy_config_cluster_v3_Cluster_upstream_connection_options(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_UpstreamConnectionOptions* default_val = NULL;
  const envoy_config_cluster_v3_UpstreamConnectionOptions* ret;
  const upb_MiniTableField field = {30, UPB_SIZE(104, 216), 80, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_upstream_connection_options(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(104, 216), 80, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_close_connections_on_host_health_failure(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {31, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_close_connections_on_host_health_failure(const envoy_config_cluster_v3_Cluster* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {31, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_ignore_health_on_host_removal(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {32, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_ignore_health_on_host_removal(const envoy_config_cluster_v3_Cluster* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {32, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_load_assignment(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 224), 81, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_endpoint_v3_ClusterLoadAssignment* envoy_config_cluster_v3_Cluster_load_assignment(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_endpoint_v3_ClusterLoadAssignment* default_val = NULL;
  const struct envoy_config_endpoint_v3_ClusterLoadAssignment* ret;
  const upb_MiniTableField field = {33, UPB_SIZE(108, 224), 81, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_load_assignment(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 224), 81, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_original_dst_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* envoy_config_cluster_v3_Cluster_original_dst_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* ret;
  const upb_MiniTableField field = {34, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_original_dst_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_typed_extension_protocol_options(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_size(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_get(const envoy_config_cluster_v3_Cluster* msg, upb_StringView key, struct google_protobuf_Any** val) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TypedExtensionProtocolOptionsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_next(const envoy_config_cluster_v3_Cluster* msg, upb_StringView* key, const struct google_protobuf_Any** val,
                           size_t* iter) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TypedExtensionProtocolOptionsEntry_msg_init);
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
UPB_INLINE const upb_Map* _envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_upb_map(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TypedExtensionProtocolOptionsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_mutable_upb_map(envoy_config_cluster_v3_Cluster* msg, upb_Arena* a) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TypedExtensionProtocolOptionsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Any*), a);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_least_request_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {37, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* envoy_config_cluster_v3_Cluster_least_request_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* ret;
  const upb_MiniTableField field = {37, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_least_request_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {37, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_cluster_type(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_CustomClusterType* envoy_config_cluster_v3_Cluster_cluster_type(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_CustomClusterType* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_CustomClusterType* ret;
  const upb_MiniTableField field = {38, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_cluster_type(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {38, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_respect_dns_ttl(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {39, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_respect_dns_ttl(const envoy_config_cluster_v3_Cluster* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {39, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_filters(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_cluster_v3_Filter* const* envoy_config_cluster_v3_Cluster_filters(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Filter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_cluster_v3_Filter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_filters_upb_array(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Filter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_filters_mutable_upb_array(envoy_config_cluster_v3_Cluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Filter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_load_balancing_policy(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(120, 248), 82, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_LoadBalancingPolicy* envoy_config_cluster_v3_Cluster_load_balancing_policy(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_LoadBalancingPolicy* default_val = NULL;
  const envoy_config_cluster_v3_LoadBalancingPolicy* ret;
  const upb_MiniTableField field = {41, UPB_SIZE(120, 248), 82, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_load_balancing_policy(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {41, UPB_SIZE(120, 248), 82, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_lrs_server(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {42, UPB_SIZE(124, 256), 83, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_config_cluster_v3_Cluster_lrs_server(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {42, UPB_SIZE(124, 256), 83, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_lrs_server(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {42, UPB_SIZE(124, 256), 83, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_transport_socket_matches(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_TransportSocketMatch* const* envoy_config_cluster_v3_Cluster_transport_socket_matches(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_cluster_v3_Cluster_TransportSocketMatch* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_transport_socket_matches_upb_array(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_transport_socket_matches_mutable_upb_array(envoy_config_cluster_v3_Cluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_dns_failure_refresh_rate(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {44, UPB_SIZE(132, 272), 84, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_RefreshRate* envoy_config_cluster_v3_Cluster_dns_failure_refresh_rate(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_RefreshRate* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_RefreshRate* ret;
  const upb_MiniTableField field = {44, UPB_SIZE(132, 272), 84, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__RefreshRate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_dns_failure_refresh_rate(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {44, UPB_SIZE(132, 272), 84, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_use_tcp_for_dns_lookups(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {45, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_use_tcp_for_dns_lookups(const envoy_config_cluster_v3_Cluster* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {45, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_upstream_http_protocol_options(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {46, UPB_SIZE(136, 280), 85, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_UpstreamHttpProtocolOptions* envoy_config_cluster_v3_Cluster_upstream_http_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_UpstreamHttpProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_UpstreamHttpProtocolOptions* ret;
  const upb_MiniTableField field = {46, UPB_SIZE(136, 280), 85, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_upstream_http_protocol_options(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {46, UPB_SIZE(136, 280), 85, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_track_timeout_budgets(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {47, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_track_timeout_budgets(const envoy_config_cluster_v3_Cluster* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {47, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_upstream_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {48, UPB_SIZE(140, 288), 86, 31, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_Cluster_upstream_config(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {48, UPB_SIZE(140, 288), 86, 31, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_upstream_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {48, UPB_SIZE(140, 288), 86, 31, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_track_cluster_stats(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {49, UPB_SIZE(144, 296), 87, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_TrackClusterStats* envoy_config_cluster_v3_Cluster_track_cluster_stats(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_TrackClusterStats* default_val = NULL;
  const envoy_config_cluster_v3_TrackClusterStats* ret;
  const upb_MiniTableField field = {49, UPB_SIZE(144, 296), 87, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__TrackClusterStats_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_track_cluster_stats(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {49, UPB_SIZE(144, 296), 87, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_preconnect_policy(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {50, UPB_SIZE(148, 304), 88, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_PreconnectPolicy* envoy_config_cluster_v3_Cluster_preconnect_policy(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_PreconnectPolicy* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_PreconnectPolicy* ret;
  const upb_MiniTableField field = {50, UPB_SIZE(148, 304), 88, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_preconnect_policy(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {50, UPB_SIZE(148, 304), 88, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_connection_pool_per_downstream_connection(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {51, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_connection_pool_per_downstream_connection(const envoy_config_cluster_v3_Cluster* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {51, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_maglev_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {52, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_MaglevLbConfig* envoy_config_cluster_v3_Cluster_maglev_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_MaglevLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_MaglevLbConfig* ret;
  const upb_MiniTableField field = {52, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_maglev_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {52, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_dns_resolution_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {53, UPB_SIZE(152, 312), 89, 35, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DnsResolutionConfig* envoy_config_cluster_v3_Cluster_dns_resolution_config(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_DnsResolutionConfig* default_val = NULL;
  const struct envoy_config_core_v3_DnsResolutionConfig* ret;
  const upb_MiniTableField field = {53, UPB_SIZE(152, 312), 89, 35, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DnsResolutionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_dns_resolution_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {53, UPB_SIZE(152, 312), 89, 35, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_wait_for_warm_on_init(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {54, UPB_SIZE(156, 320), 90, 36, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_cluster_v3_Cluster_wait_for_warm_on_init(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {54, UPB_SIZE(156, 320), 90, 36, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_wait_for_warm_on_init(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {54, UPB_SIZE(156, 320), 90, 36, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_typed_dns_resolver_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {55, UPB_SIZE(160, 328), 91, 37, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_Cluster_typed_dns_resolver_config(const envoy_config_cluster_v3_Cluster* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {55, UPB_SIZE(160, 328), 91, 37, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_typed_dns_resolver_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {55, UPB_SIZE(160, 328), 91, 37, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_round_robin_lb_config(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {56, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 38, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* envoy_config_cluster_v3_Cluster_round_robin_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* ret;
  const upb_MiniTableField field = {56, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 38, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_round_robin_lb_config(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {56, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 38, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_lrs_report_endpoint_metrics(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_cluster_v3_Cluster_lrs_report_endpoint_metrics(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_lrs_report_endpoint_metrics_upb_array(const envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  const upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_lrs_report_endpoint_metrics_mutable_upb_array(envoy_config_cluster_v3_Cluster* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_clear_dns_jitter(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {58, UPB_SIZE(168, 344), 92, 39, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_dns_jitter(const envoy_config_cluster_v3_Cluster* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {58, UPB_SIZE(168, 344), 92, 39, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_has_dns_jitter(const envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {58, UPB_SIZE(168, 344), 92, 39, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_set_name(envoy_config_cluster_v3_Cluster *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(188, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_type(envoy_config_cluster_v3_Cluster *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_eds_cluster_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_EdsClusterConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_EdsClusterConfig* envoy_config_cluster_v3_Cluster_mutable_eds_cluster_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_EdsClusterConfig* sub = (struct envoy_config_cluster_v3_Cluster_EdsClusterConfig*)envoy_config_cluster_v3_Cluster_eds_cluster_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_EdsClusterConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_eds_cluster_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_connect_timeout(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_mutable_connect_timeout(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_connect_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_connect_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_per_connection_buffer_limit_bytes(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_mutable_per_connection_buffer_limit_bytes(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_Cluster_per_connection_buffer_limit_bytes(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_per_connection_buffer_limit_bytes(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_lb_policy(envoy_config_cluster_v3_Cluster *msg, int32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck** envoy_config_cluster_v3_Cluster_mutable_health_checks(envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_HealthCheck**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck** envoy_config_cluster_v3_Cluster_resize_health_checks(envoy_config_cluster_v3_Cluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_HealthCheck**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HealthCheck* envoy_config_cluster_v3_Cluster_add_health_checks(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(36, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthCheck_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HealthCheck* sub = (struct envoy_config_core_v3_HealthCheck*)_upb_Message_New(&envoy__config__core__v3__HealthCheck_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_max_requests_per_connection(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 104), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_mutable_max_requests_per_connection(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_Cluster_max_requests_per_connection(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_max_requests_per_connection(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_circuit_breakers(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_cluster_v3_CircuitBreakers* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 112), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__CircuitBreakers_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_CircuitBreakers* envoy_config_cluster_v3_Cluster_mutable_circuit_breakers(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_CircuitBreakers* sub = (struct envoy_config_cluster_v3_CircuitBreakers*)envoy_config_cluster_v3_Cluster_circuit_breakers(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_CircuitBreakers*)_upb_Message_New(&envoy__config__cluster__v3__CircuitBreakers_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_circuit_breakers(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_http_protocol_options(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_Http1ProtocolOptions* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(48, 120), 69, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http1ProtocolOptions* envoy_config_cluster_v3_Cluster_mutable_http_protocol_options(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http1ProtocolOptions* sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)envoy_config_cluster_v3_Cluster_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http1ProtocolOptions_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_http2_protocol_options(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_Http2ProtocolOptions* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(52, 128), 70, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http2ProtocolOptions* envoy_config_cluster_v3_Cluster_mutable_http2_protocol_options(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http2ProtocolOptions* sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)envoy_config_cluster_v3_Cluster_http2_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http2ProtocolOptions_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_http2_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_dns_refresh_rate(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(56, 136), 71, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_mutable_dns_refresh_rate(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_dns_refresh_rate(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_dns_refresh_rate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_dns_lookup_family(envoy_config_cluster_v3_Cluster *msg, int32_t value) {
  const upb_MiniTableField field = {17, UPB_SIZE(60, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address** envoy_config_cluster_v3_Cluster_mutable_dns_resolvers(envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_Address** envoy_config_cluster_v3_Cluster_resize_dns_resolvers(envoy_config_cluster_v3_Cluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_Address**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_cluster_v3_Cluster_add_dns_resolvers(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  upb_MiniTableField field = {18, UPB_SIZE(64, 144), 0, 9, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_outlier_detection(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_cluster_v3_OutlierDetection* value) {
  const upb_MiniTableField field = {19, UPB_SIZE(68, 152), 72, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__OutlierDetection_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_OutlierDetection* envoy_config_cluster_v3_Cluster_mutable_outlier_detection(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_OutlierDetection* sub = (struct envoy_config_cluster_v3_OutlierDetection*)envoy_config_cluster_v3_Cluster_outlier_detection(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_OutlierDetection*)_upb_Message_New(&envoy__config__cluster__v3__OutlierDetection_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_outlier_detection(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_cleanup_interval(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(72, 160), 73, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_mutable_cleanup_interval(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_cleanup_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_cleanup_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_upstream_bind_config(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_BindConfig* value) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 168), 74, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BindConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_BindConfig* envoy_config_cluster_v3_Cluster_mutable_upstream_bind_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_BindConfig* sub = (struct envoy_config_core_v3_BindConfig*)envoy_config_cluster_v3_Cluster_upstream_bind_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_BindConfig*)_upb_Message_New(&envoy__config__core__v3__BindConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_upstream_bind_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_lb_subset_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_LbSubsetConfig* value) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 176), 75, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_LbSubsetConfig* envoy_config_cluster_v3_Cluster_mutable_lb_subset_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_LbSubsetConfig* sub = (struct envoy_config_cluster_v3_Cluster_LbSubsetConfig*)envoy_config_cluster_v3_Cluster_lb_subset_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_LbSubsetConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_lb_subset_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_ring_hash_lb_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_RingHashLbConfig* value) {
  const upb_MiniTableField field = {23, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_RingHashLbConfig* envoy_config_cluster_v3_Cluster_mutable_ring_hash_lb_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_RingHashLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_RingHashLbConfig*)envoy_config_cluster_v3_Cluster_ring_hash_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_RingHashLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_ring_hash_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_transport_socket(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_TransportSocket* value) {
  const upb_MiniTableField field = {24, UPB_SIZE(84, 184), 76, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TransportSocket* envoy_config_cluster_v3_Cluster_mutable_transport_socket(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TransportSocket* sub = (struct envoy_config_core_v3_TransportSocket*)envoy_config_cluster_v3_Cluster_transport_socket(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TransportSocket*)_upb_Message_New(&envoy__config__core__v3__TransportSocket_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_transport_socket(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_metadata(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {25, UPB_SIZE(88, 192), 77, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_cluster_v3_Cluster_mutable_metadata(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_cluster_v3_Cluster_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_protocol_selection(envoy_config_cluster_v3_Cluster *msg, int32_t value) {
  const upb_MiniTableField field = {26, UPB_SIZE(92, 28), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_common_lb_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_CommonLbConfig* value) {
  const upb_MiniTableField field = {27, UPB_SIZE(96, 200), 78, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_CommonLbConfig* envoy_config_cluster_v3_Cluster_mutable_common_lb_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_CommonLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig*)envoy_config_cluster_v3_Cluster_common_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_common_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_alt_stat_name(envoy_config_cluster_v3_Cluster *msg, upb_StringView value) {
  const upb_MiniTableField field = {28, UPB_SIZE(196, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_common_http_protocol_options(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_HttpProtocolOptions* value) {
  const upb_MiniTableField field = {29, UPB_SIZE(100, 208), 79, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HttpProtocolOptions* envoy_config_cluster_v3_Cluster_mutable_common_http_protocol_options(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HttpProtocolOptions* sub = (struct envoy_config_core_v3_HttpProtocolOptions*)envoy_config_cluster_v3_Cluster_common_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HttpProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__HttpProtocolOptions_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_common_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_upstream_connection_options(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_UpstreamConnectionOptions* value) {
  const upb_MiniTableField field = {30, UPB_SIZE(104, 216), 80, 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_UpstreamConnectionOptions* envoy_config_cluster_v3_Cluster_mutable_upstream_connection_options(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_UpstreamConnectionOptions* sub = (struct envoy_config_cluster_v3_UpstreamConnectionOptions*)envoy_config_cluster_v3_Cluster_upstream_connection_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_UpstreamConnectionOptions*)_upb_Message_New(&envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_upstream_connection_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_close_connections_on_host_health_failure(envoy_config_cluster_v3_Cluster *msg, bool value) {
  const upb_MiniTableField field = {31, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_ignore_health_on_host_removal(envoy_config_cluster_v3_Cluster *msg, bool value) {
  const upb_MiniTableField field = {32, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_load_assignment(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_endpoint_v3_ClusterLoadAssignment* value) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 224), 81, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_endpoint_v3_ClusterLoadAssignment* envoy_config_cluster_v3_Cluster_mutable_load_assignment(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_endpoint_v3_ClusterLoadAssignment* sub = (struct envoy_config_endpoint_v3_ClusterLoadAssignment*)envoy_config_cluster_v3_Cluster_load_assignment(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_endpoint_v3_ClusterLoadAssignment*)_upb_Message_New(&envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_load_assignment(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_original_dst_lb_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* value) {
  const upb_MiniTableField field = {34, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* envoy_config_cluster_v3_Cluster_mutable_original_dst_lb_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_OriginalDstLbConfig*)envoy_config_cluster_v3_Cluster_original_dst_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_OriginalDstLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_original_dst_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_clear(envoy_config_cluster_v3_Cluster* msg) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_set(envoy_config_cluster_v3_Cluster* msg, upb_StringView key, struct google_protobuf_Any* val, upb_Arena* a) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TypedExtensionProtocolOptionsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_typed_extension_protocol_options_delete(envoy_config_cluster_v3_Cluster* msg, upb_StringView key) {
  const upb_MiniTableField field = {36, UPB_SIZE(112, 232), 0, 22, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_least_request_lb_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* value) {
  const upb_MiniTableField field = {37, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* envoy_config_cluster_v3_Cluster_mutable_least_request_lb_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_LeastRequestLbConfig*)envoy_config_cluster_v3_Cluster_least_request_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_LeastRequestLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_least_request_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_cluster_type(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_CustomClusterType* value) {
  const upb_MiniTableField field = {38, UPB_SIZE(176, 352), UPB_SIZE(-173, -33), 24, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_CustomClusterType* envoy_config_cluster_v3_Cluster_mutable_cluster_type(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_CustomClusterType* sub = (struct envoy_config_cluster_v3_Cluster_CustomClusterType*)envoy_config_cluster_v3_Cluster_cluster_type(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_CustomClusterType*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_cluster_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_respect_dns_ttl(envoy_config_cluster_v3_Cluster *msg, bool value) {
  const upb_MiniTableField field = {39, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Filter** envoy_config_cluster_v3_Cluster_mutable_filters(envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Filter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_cluster_v3_Filter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_cluster_v3_Filter** envoy_config_cluster_v3_Cluster_resize_filters(envoy_config_cluster_v3_Cluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_cluster_v3_Filter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_Filter* envoy_config_cluster_v3_Cluster_add_filters(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  upb_MiniTableField field = {40, UPB_SIZE(116, 240), 0, 25, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Filter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_Filter* sub = (struct envoy_config_cluster_v3_Filter*)_upb_Message_New(&envoy__config__cluster__v3__Filter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_load_balancing_policy(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_LoadBalancingPolicy* value) {
  const upb_MiniTableField field = {41, UPB_SIZE(120, 248), 82, 26, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_LoadBalancingPolicy* envoy_config_cluster_v3_Cluster_mutable_load_balancing_policy(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_LoadBalancingPolicy* sub = (struct envoy_config_cluster_v3_LoadBalancingPolicy*)envoy_config_cluster_v3_Cluster_load_balancing_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_LoadBalancingPolicy*)_upb_Message_New(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_load_balancing_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_lrs_server(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {42, UPB_SIZE(124, 256), 83, 27, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_cluster_v3_Cluster_mutable_lrs_server(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_config_cluster_v3_Cluster_lrs_server(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_lrs_server(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_TransportSocketMatch** envoy_config_cluster_v3_Cluster_mutable_transport_socket_matches(envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_cluster_v3_Cluster_TransportSocketMatch**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_cluster_v3_Cluster_TransportSocketMatch** envoy_config_cluster_v3_Cluster_resize_transport_socket_matches(envoy_config_cluster_v3_Cluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_Cluster_TransportSocketMatch**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_TransportSocketMatch* envoy_config_cluster_v3_Cluster_add_transport_socket_matches(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  upb_MiniTableField field = {43, UPB_SIZE(128, 264), 0, 28, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_Cluster_TransportSocketMatch* sub = (struct envoy_config_cluster_v3_Cluster_TransportSocketMatch*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_dns_failure_refresh_rate(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_RefreshRate* value) {
  const upb_MiniTableField field = {44, UPB_SIZE(132, 272), 84, 29, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__RefreshRate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_RefreshRate* envoy_config_cluster_v3_Cluster_mutable_dns_failure_refresh_rate(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_RefreshRate* sub = (struct envoy_config_cluster_v3_Cluster_RefreshRate*)envoy_config_cluster_v3_Cluster_dns_failure_refresh_rate(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_RefreshRate*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__RefreshRate_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_dns_failure_refresh_rate(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_use_tcp_for_dns_lookups(envoy_config_cluster_v3_Cluster *msg, bool value) {
  const upb_MiniTableField field = {45, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_upstream_http_protocol_options(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_UpstreamHttpProtocolOptions* value) {
  const upb_MiniTableField field = {46, UPB_SIZE(136, 280), 85, 30, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_UpstreamHttpProtocolOptions* envoy_config_cluster_v3_Cluster_mutable_upstream_http_protocol_options(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_UpstreamHttpProtocolOptions* sub = (struct envoy_config_core_v3_UpstreamHttpProtocolOptions*)envoy_config_cluster_v3_Cluster_upstream_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_UpstreamHttpProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_upstream_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_track_timeout_budgets(envoy_config_cluster_v3_Cluster *msg, bool value) {
  const upb_MiniTableField field = {47, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_upstream_config(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {48, UPB_SIZE(140, 288), 86, 31, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_Cluster_mutable_upstream_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_cluster_v3_Cluster_upstream_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_upstream_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_track_cluster_stats(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_TrackClusterStats* value) {
  const upb_MiniTableField field = {49, UPB_SIZE(144, 296), 87, 32, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__TrackClusterStats_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_TrackClusterStats* envoy_config_cluster_v3_Cluster_mutable_track_cluster_stats(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_TrackClusterStats* sub = (struct envoy_config_cluster_v3_TrackClusterStats*)envoy_config_cluster_v3_Cluster_track_cluster_stats(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_TrackClusterStats*)_upb_Message_New(&envoy__config__cluster__v3__TrackClusterStats_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_track_cluster_stats(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_preconnect_policy(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_PreconnectPolicy* value) {
  const upb_MiniTableField field = {50, UPB_SIZE(148, 304), 88, 33, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_PreconnectPolicy* envoy_config_cluster_v3_Cluster_mutable_preconnect_policy(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_PreconnectPolicy* sub = (struct envoy_config_cluster_v3_Cluster_PreconnectPolicy*)envoy_config_cluster_v3_Cluster_preconnect_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_PreconnectPolicy*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_preconnect_policy(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_connection_pool_per_downstream_connection(envoy_config_cluster_v3_Cluster *msg, bool value) {
  const upb_MiniTableField field = {51, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_maglev_lb_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_MaglevLbConfig* value) {
  const upb_MiniTableField field = {52, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 34, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_MaglevLbConfig* envoy_config_cluster_v3_Cluster_mutable_maglev_lb_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_MaglevLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_MaglevLbConfig*)envoy_config_cluster_v3_Cluster_maglev_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_MaglevLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_maglev_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_dns_resolution_config(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_DnsResolutionConfig* value) {
  const upb_MiniTableField field = {53, UPB_SIZE(152, 312), 89, 35, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DnsResolutionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DnsResolutionConfig* envoy_config_cluster_v3_Cluster_mutable_dns_resolution_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DnsResolutionConfig* sub = (struct envoy_config_core_v3_DnsResolutionConfig*)envoy_config_cluster_v3_Cluster_dns_resolution_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DnsResolutionConfig*)_upb_Message_New(&envoy__config__core__v3__DnsResolutionConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_dns_resolution_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_wait_for_warm_on_init(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {54, UPB_SIZE(156, 320), 90, 36, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_cluster_v3_Cluster_mutable_wait_for_warm_on_init(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_cluster_v3_Cluster_wait_for_warm_on_init(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_wait_for_warm_on_init(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_typed_dns_resolver_config(envoy_config_cluster_v3_Cluster *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {55, UPB_SIZE(160, 328), 91, 37, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_Cluster_mutable_typed_dns_resolver_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_cluster_v3_Cluster_typed_dns_resolver_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_typed_dns_resolver_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_round_robin_lb_config(envoy_config_cluster_v3_Cluster *msg, envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* value) {
  const upb_MiniTableField field = {56, UPB_SIZE(184, 360), UPB_SIZE(-181, -37), 38, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* envoy_config_cluster_v3_Cluster_mutable_round_robin_lb_config(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_RoundRobinLbConfig*)envoy_config_cluster_v3_Cluster_round_robin_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_RoundRobinLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_round_robin_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE upb_StringView* envoy_config_cluster_v3_Cluster_mutable_lrs_report_endpoint_metrics(envoy_config_cluster_v3_Cluster* msg, size_t* size) {
  upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_cluster_v3_Cluster_resize_lrs_report_endpoint_metrics(envoy_config_cluster_v3_Cluster* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_add_lrs_report_endpoint_metrics(envoy_config_cluster_v3_Cluster* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {57, UPB_SIZE(164, 336), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_cluster_v3_Cluster_set_dns_jitter(envoy_config_cluster_v3_Cluster *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {58, UPB_SIZE(168, 344), 92, 39, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_mutable_dns_jitter(envoy_config_cluster_v3_Cluster* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_dns_jitter(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_set_dns_jitter(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_TransportSocketMatch* envoy_config_cluster_v3_Cluster_TransportSocketMatch_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_TransportSocketMatch*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_TransportSocketMatch* envoy_config_cluster_v3_Cluster_TransportSocketMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_TransportSocketMatch* ret = envoy_config_cluster_v3_Cluster_TransportSocketMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_TransportSocketMatch* envoy_config_cluster_v3_Cluster_TransportSocketMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_TransportSocketMatch* ret = envoy_config_cluster_v3_Cluster_TransportSocketMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_TransportSocketMatch_serialize(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_TransportSocketMatch_serialize_ex(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__TransportSocketMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_TransportSocketMatch_clear_name(envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Cluster_TransportSocketMatch_name(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_TransportSocketMatch_clear_match(envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_cluster_v3_Cluster_TransportSocketMatch_match(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_TransportSocketMatch_has_match(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_TransportSocketMatch_clear_transport_socket(envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TransportSocket* envoy_config_cluster_v3_Cluster_TransportSocketMatch_transport_socket(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const struct envoy_config_core_v3_TransportSocket* default_val = NULL;
  const struct envoy_config_core_v3_TransportSocket* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_TransportSocketMatch_has_transport_socket(const envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_TransportSocketMatch_set_name(envoy_config_cluster_v3_Cluster_TransportSocketMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_TransportSocketMatch_set_match(envoy_config_cluster_v3_Cluster_TransportSocketMatch *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_cluster_v3_Cluster_TransportSocketMatch_mutable_match(envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_cluster_v3_Cluster_TransportSocketMatch_match(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_TransportSocketMatch_set_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_TransportSocketMatch_set_transport_socket(envoy_config_cluster_v3_Cluster_TransportSocketMatch *msg, struct envoy_config_core_v3_TransportSocket* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TransportSocket* envoy_config_cluster_v3_Cluster_TransportSocketMatch_mutable_transport_socket(envoy_config_cluster_v3_Cluster_TransportSocketMatch* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TransportSocket* sub = (struct envoy_config_core_v3_TransportSocket*)envoy_config_cluster_v3_Cluster_TransportSocketMatch_transport_socket(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TransportSocket*)_upb_Message_New(&envoy__config__core__v3__TransportSocket_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_TransportSocketMatch_set_transport_socket(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_CustomClusterType* envoy_config_cluster_v3_Cluster_CustomClusterType_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_CustomClusterType*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CustomClusterType* envoy_config_cluster_v3_Cluster_CustomClusterType_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CustomClusterType* ret = envoy_config_cluster_v3_Cluster_CustomClusterType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CustomClusterType* envoy_config_cluster_v3_Cluster_CustomClusterType_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CustomClusterType* ret = envoy_config_cluster_v3_Cluster_CustomClusterType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CustomClusterType_serialize(const envoy_config_cluster_v3_Cluster_CustomClusterType* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CustomClusterType_serialize_ex(const envoy_config_cluster_v3_Cluster_CustomClusterType* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CustomClusterType_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CustomClusterType_clear_name(envoy_config_cluster_v3_Cluster_CustomClusterType* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Cluster_CustomClusterType_name(const envoy_config_cluster_v3_Cluster_CustomClusterType* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CustomClusterType_clear_typed_config(envoy_config_cluster_v3_Cluster_CustomClusterType* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_cluster_v3_Cluster_CustomClusterType_typed_config(const envoy_config_cluster_v3_Cluster_CustomClusterType* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CustomClusterType_has_typed_config(const envoy_config_cluster_v3_Cluster_CustomClusterType* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_CustomClusterType_set_name(envoy_config_cluster_v3_Cluster_CustomClusterType *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CustomClusterType_set_typed_config(envoy_config_cluster_v3_Cluster_CustomClusterType *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_cluster_v3_Cluster_CustomClusterType_mutable_typed_config(envoy_config_cluster_v3_Cluster_CustomClusterType* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_cluster_v3_Cluster_CustomClusterType_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CustomClusterType_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_EdsClusterConfig* envoy_config_cluster_v3_Cluster_EdsClusterConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_EdsClusterConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_EdsClusterConfig* envoy_config_cluster_v3_Cluster_EdsClusterConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_EdsClusterConfig* ret = envoy_config_cluster_v3_Cluster_EdsClusterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_EdsClusterConfig* envoy_config_cluster_v3_Cluster_EdsClusterConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_EdsClusterConfig* ret = envoy_config_cluster_v3_Cluster_EdsClusterConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_EdsClusterConfig_serialize(const envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_EdsClusterConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__EdsClusterConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_EdsClusterConfig_clear_eds_config(envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ConfigSource* envoy_config_cluster_v3_Cluster_EdsClusterConfig_eds_config(const envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg) {
  const struct envoy_config_core_v3_ConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ConfigSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_EdsClusterConfig_has_eds_config(const envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_EdsClusterConfig_clear_service_name(envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Cluster_EdsClusterConfig_service_name(const envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_EdsClusterConfig_set_eds_config(envoy_config_cluster_v3_Cluster_EdsClusterConfig *msg, struct envoy_config_core_v3_ConfigSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ConfigSource* envoy_config_cluster_v3_Cluster_EdsClusterConfig_mutable_eds_config(envoy_config_cluster_v3_Cluster_EdsClusterConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ConfigSource* sub = (struct envoy_config_core_v3_ConfigSource*)envoy_config_cluster_v3_Cluster_EdsClusterConfig_eds_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ConfigSource*)_upb_Message_New(&envoy__config__core__v3__ConfigSource_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_EdsClusterConfig_set_eds_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_EdsClusterConfig_set_service_name(envoy_config_cluster_v3_Cluster_EdsClusterConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig* envoy_config_cluster_v3_Cluster_LbSubsetConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_LbSubsetConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig* envoy_config_cluster_v3_Cluster_LbSubsetConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig* ret = envoy_config_cluster_v3_Cluster_LbSubsetConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig* envoy_config_cluster_v3_Cluster_LbSubsetConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig* ret = envoy_config_cluster_v3_Cluster_LbSubsetConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_LbSubsetConfig_serialize(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_LbSubsetConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__LbSubsetConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_fallback_policy(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_LbSubsetConfig_fallback_policy(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_default_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_cluster_v3_Cluster_LbSubsetConfig_default_subset(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_has_default_subset(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_subset_selectors(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* const* envoy_config_cluster_v3_Cluster_LbSubsetConfig_subset_selectors(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_LbSubsetConfig_subset_selectors_upb_array(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_LbSubsetConfig_subset_selectors_mutable_upb_array(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_locality_weight_aware(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_locality_weight_aware(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_scale_locality_weight(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {5, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_scale_locality_weight(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_panic_mode_any(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {6, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_panic_mode_any(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_list_as_any(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {7, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_list_as_any(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_clear_metadata_fallback_policy(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_LbSubsetConfig_metadata_fallback_policy(const envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {8, UPB_SIZE(28, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_fallback_policy(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, int32_t value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_default_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_cluster_v3_Cluster_LbSubsetConfig_mutable_default_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_cluster_v3_Cluster_LbSubsetConfig_default_subset(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_default_subset(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector** envoy_config_cluster_v3_Cluster_LbSubsetConfig_mutable_subset_selectors(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector** envoy_config_cluster_v3_Cluster_LbSubsetConfig_resize_subset_selectors(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* envoy_config_cluster_v3_Cluster_LbSubsetConfig_add_subset_selectors(envoy_config_cluster_v3_Cluster_LbSubsetConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* sub = (struct envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_locality_weight_aware(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, bool value) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_scale_locality_weight(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, bool value) {
  const upb_MiniTableField field = {5, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_panic_mode_any(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, bool value) {
  const upb_MiniTableField field = {6, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_list_as_any(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, bool value) {
  const upb_MiniTableField field = {7, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_set_metadata_fallback_policy(envoy_config_cluster_v3_Cluster_LbSubsetConfig *msg, int32_t value) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* ret = envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* ret = envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_serialize(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_serialize_ex(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__LbSubsetConfig__LbSubsetSelector_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_clear_keys(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_keys(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_keys_upb_array(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_keys_mutable_upb_array(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_clear_fallback_policy(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_fallback_policy(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_clear_fallback_keys_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_fallback_keys_subset(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_fallback_keys_subset_upb_array(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_fallback_keys_subset_mutable_upb_array(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_clear_single_host_per_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_single_host_per_subset(const envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE upb_StringView* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_mutable_keys(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_resize_keys(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_add_keys(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_set_fallback_policy(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_mutable_fallback_keys_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_resize_fallback_keys_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_add_fallback_keys_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_set_single_host_per_subset(envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector *msg, bool value) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_SlowStartConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_SlowStartConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_SlowStartConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_SlowStartConfig* ret = envoy_config_cluster_v3_Cluster_SlowStartConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_SlowStartConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_SlowStartConfig* ret = envoy_config_cluster_v3_Cluster_SlowStartConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_SlowStartConfig_serialize(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_SlowStartConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_SlowStartConfig_clear_slow_start_window(envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_SlowStartConfig_slow_start_window(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_SlowStartConfig_has_slow_start_window(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_SlowStartConfig_clear_aggression(envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeDouble* envoy_config_cluster_v3_Cluster_SlowStartConfig_aggression(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const struct envoy_config_core_v3_RuntimeDouble* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeDouble* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeDouble_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_SlowStartConfig_has_aggression(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_SlowStartConfig_clear_min_weight_percent(envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_cluster_v3_Cluster_SlowStartConfig_min_weight_percent(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_SlowStartConfig_has_min_weight_percent(const envoy_config_cluster_v3_Cluster_SlowStartConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_SlowStartConfig_set_slow_start_window(envoy_config_cluster_v3_Cluster_SlowStartConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_SlowStartConfig_mutable_slow_start_window(envoy_config_cluster_v3_Cluster_SlowStartConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_SlowStartConfig_slow_start_window(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_SlowStartConfig_set_slow_start_window(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_SlowStartConfig_set_aggression(envoy_config_cluster_v3_Cluster_SlowStartConfig *msg, struct envoy_config_core_v3_RuntimeDouble* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeDouble_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeDouble* envoy_config_cluster_v3_Cluster_SlowStartConfig_mutable_aggression(envoy_config_cluster_v3_Cluster_SlowStartConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeDouble* sub = (struct envoy_config_core_v3_RuntimeDouble*)envoy_config_cluster_v3_Cluster_SlowStartConfig_aggression(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeDouble*)_upb_Message_New(&envoy__config__core__v3__RuntimeDouble_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_SlowStartConfig_set_aggression(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_SlowStartConfig_set_min_weight_percent(envoy_config_cluster_v3_Cluster_SlowStartConfig *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_cluster_v3_Cluster_SlowStartConfig_mutable_min_weight_percent(envoy_config_cluster_v3_Cluster_SlowStartConfig* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_cluster_v3_Cluster_SlowStartConfig_min_weight_percent(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_SlowStartConfig_set_min_weight_percent(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_RoundRobinLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* ret = envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* ret = envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_serialize(const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__RoundRobinLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_clear_slow_start_config(envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_slow_start_config(const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* msg) {
  const envoy_config_cluster_v3_Cluster_SlowStartConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_SlowStartConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_has_slow_start_config(const envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_set_slow_start_config(envoy_config_cluster_v3_Cluster_RoundRobinLbConfig *msg, envoy_config_cluster_v3_Cluster_SlowStartConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_mutable_slow_start_config(envoy_config_cluster_v3_Cluster_RoundRobinLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_SlowStartConfig* sub = (struct envoy_config_cluster_v3_Cluster_SlowStartConfig*)envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_slow_start_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_SlowStartConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_set_slow_start_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_LeastRequestLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* ret = envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* ret = envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_serialize(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__LeastRequestLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_clear_choice_count(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_choice_count(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_has_choice_count(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_clear_active_request_bias(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeDouble* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_active_request_bias(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const struct envoy_config_core_v3_RuntimeDouble* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeDouble* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeDouble_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_has_active_request_bias(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_clear_slow_start_config(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_slow_start_config(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const envoy_config_cluster_v3_Cluster_SlowStartConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_SlowStartConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_has_slow_start_config(const envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_set_choice_count(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_mutable_choice_count(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_choice_count(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_set_choice_count(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_set_active_request_bias(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig *msg, struct envoy_config_core_v3_RuntimeDouble* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeDouble_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeDouble* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_mutable_active_request_bias(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeDouble* sub = (struct envoy_config_core_v3_RuntimeDouble*)envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_active_request_bias(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeDouble*)_upb_Message_New(&envoy__config__core__v3__RuntimeDouble_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_set_active_request_bias(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_set_slow_start_config(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig *msg, envoy_config_cluster_v3_Cluster_SlowStartConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_SlowStartConfig* envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_mutable_slow_start_config(envoy_config_cluster_v3_Cluster_LeastRequestLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_SlowStartConfig* sub = (struct envoy_config_cluster_v3_Cluster_SlowStartConfig*)envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_slow_start_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_SlowStartConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__SlowStartConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_set_slow_start_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_RingHashLbConfig* envoy_config_cluster_v3_Cluster_RingHashLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_RingHashLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_RingHashLbConfig* envoy_config_cluster_v3_Cluster_RingHashLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_RingHashLbConfig* ret = envoy_config_cluster_v3_Cluster_RingHashLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_RingHashLbConfig* envoy_config_cluster_v3_Cluster_RingHashLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_RingHashLbConfig* ret = envoy_config_cluster_v3_Cluster_RingHashLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_RingHashLbConfig_serialize(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_RingHashLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__RingHashLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RingHashLbConfig_clear_minimum_ring_size(envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_RingHashLbConfig_minimum_ring_size(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_RingHashLbConfig_has_minimum_ring_size(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RingHashLbConfig_clear_hash_function(envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_Cluster_RingHashLbConfig_hash_function(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RingHashLbConfig_clear_maximum_ring_size(envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_RingHashLbConfig_maximum_ring_size(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_RingHashLbConfig_has_maximum_ring_size(const envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_RingHashLbConfig_set_minimum_ring_size(envoy_config_cluster_v3_Cluster_RingHashLbConfig *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_RingHashLbConfig_mutable_minimum_ring_size(envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_cluster_v3_Cluster_RingHashLbConfig_minimum_ring_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_RingHashLbConfig_set_minimum_ring_size(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RingHashLbConfig_set_hash_function(envoy_config_cluster_v3_Cluster_RingHashLbConfig *msg, int32_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RingHashLbConfig_set_maximum_ring_size(envoy_config_cluster_v3_Cluster_RingHashLbConfig *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_RingHashLbConfig_mutable_maximum_ring_size(envoy_config_cluster_v3_Cluster_RingHashLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_cluster_v3_Cluster_RingHashLbConfig_maximum_ring_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_RingHashLbConfig_set_maximum_ring_size(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_MaglevLbConfig* envoy_config_cluster_v3_Cluster_MaglevLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_MaglevLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_MaglevLbConfig* envoy_config_cluster_v3_Cluster_MaglevLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_MaglevLbConfig* ret = envoy_config_cluster_v3_Cluster_MaglevLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_MaglevLbConfig* envoy_config_cluster_v3_Cluster_MaglevLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_MaglevLbConfig* ret = envoy_config_cluster_v3_Cluster_MaglevLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_MaglevLbConfig_serialize(const envoy_config_cluster_v3_Cluster_MaglevLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_MaglevLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_MaglevLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__MaglevLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_MaglevLbConfig_clear_table_size(envoy_config_cluster_v3_Cluster_MaglevLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_MaglevLbConfig_table_size(const envoy_config_cluster_v3_Cluster_MaglevLbConfig* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_MaglevLbConfig_has_table_size(const envoy_config_cluster_v3_Cluster_MaglevLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_MaglevLbConfig_set_table_size(envoy_config_cluster_v3_Cluster_MaglevLbConfig *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_MaglevLbConfig_mutable_table_size(envoy_config_cluster_v3_Cluster_MaglevLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_cluster_v3_Cluster_MaglevLbConfig_table_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_MaglevLbConfig_set_table_size(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_OriginalDstLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* ret = envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* ret = envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_serialize(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__OriginalDstLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_clear_use_http_header(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_use_http_header(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_clear_http_header_name(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_http_header_name(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_clear_upstream_port_override(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_upstream_port_override(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_has_upstream_port_override(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_clear_metadata_key(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_metadata_v3_MetadataKey* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_metadata_key(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const struct envoy_type_metadata_v3_MetadataKey* default_val = NULL;
  const struct envoy_type_metadata_v3_MetadataKey* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_has_metadata_key(const envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_set_use_http_header(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_set_http_header_name(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_set_upstream_port_override(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_mutable_upstream_port_override(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_upstream_port_override(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_set_upstream_port_override(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_set_metadata_key(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig *msg, struct envoy_type_metadata_v3_MetadataKey* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKey* envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_mutable_metadata_key(envoy_config_cluster_v3_Cluster_OriginalDstLbConfig* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKey* sub = (struct envoy_type_metadata_v3_MetadataKey*)envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_metadata_key(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKey*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_set_metadata_key(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_CommonLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_serialize(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_zone_aware_lb_config = 2,
  envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_locality_weighted_lb_config = 3,
  envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_NOT_SET = 0
} envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_oneofcases;
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_oneofcases envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_case(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_config_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_locality_config_specifier(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig_msg_init, &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_healthy_panic_threshold(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_cluster_v3_Cluster_CommonLbConfig_healthy_panic_threshold(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_has_healthy_panic_threshold(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_zone_aware_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_zone_aware_lb_config(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_has_zone_aware_lb_config(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_locality_weighted_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_weighted_lb_config(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_has_locality_weighted_lb_config(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_update_merge_window(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_CommonLbConfig_update_merge_window(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_has_update_merge_window(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_ignore_new_hosts_until_first_hc(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_ignore_new_hosts_until_first_hc(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_close_connections_on_host_set_change(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_close_connections_on_host_set_change(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_consistent_hashing_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 32), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_consistent_hashing_lb_config(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* default_val = NULL;
  const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(20, 32), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_has_consistent_hashing_lb_config(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 32), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_clear_override_host_status(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 40), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HealthStatusSet* envoy_config_cluster_v3_Cluster_CommonLbConfig_override_host_status(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const struct envoy_config_core_v3_HealthStatusSet* default_val = NULL;
  const struct envoy_config_core_v3_HealthStatusSet* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(24, 40), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthStatusSet_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_has_override_host_status(const envoy_config_cluster_v3_Cluster_CommonLbConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 40), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_healthy_panic_threshold(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_cluster_v3_Cluster_CommonLbConfig_mutable_healthy_panic_threshold(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_cluster_v3_Cluster_CommonLbConfig_healthy_panic_threshold(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_set_healthy_panic_threshold(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_zone_aware_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_mutable_zone_aware_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig*)envoy_config_cluster_v3_Cluster_CommonLbConfig_zone_aware_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_set_zone_aware_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_locality_weighted_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_mutable_locality_weighted_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig*)envoy_config_cluster_v3_Cluster_CommonLbConfig_locality_weighted_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_set_locality_weighted_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_update_merge_window(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 24), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_CommonLbConfig_mutable_update_merge_window(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_CommonLbConfig_update_merge_window(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_set_update_merge_window(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_ignore_new_hosts_until_first_hc(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_close_connections_on_host_set_change(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, bool value) {
  const upb_MiniTableField field = {6, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_consistent_hashing_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 32), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_mutable_consistent_hashing_lb_config(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig*)envoy_config_cluster_v3_Cluster_CommonLbConfig_consistent_hashing_lb_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_set_consistent_hashing_lb_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_set_override_host_status(envoy_config_cluster_v3_Cluster_CommonLbConfig *msg, struct envoy_config_core_v3_HealthStatusSet* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 40), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HealthStatusSet_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HealthStatusSet* envoy_config_cluster_v3_Cluster_CommonLbConfig_mutable_override_host_status(envoy_config_cluster_v3_Cluster_CommonLbConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HealthStatusSet* sub = (struct envoy_config_core_v3_HealthStatusSet*)envoy_config_cluster_v3_Cluster_CommonLbConfig_override_host_status(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HealthStatusSet*)_upb_Message_New(&envoy__config__core__v3__HealthStatusSet_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_set_override_host_status(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_serialize(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ZoneAwareLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_clear_routing_enabled(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_routing_enabled(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_has_routing_enabled(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_clear_min_cluster_size(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_min_cluster_size(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_has_min_cluster_size(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_clear_fail_traffic_on_panic(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_fail_traffic_on_panic(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_set_routing_enabled(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_mutable_routing_enabled(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_routing_enabled(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_set_routing_enabled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_set_min_cluster_size(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_mutable_min_cluster_size(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_min_cluster_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_set_min_cluster_size(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_set_fail_traffic_on_panic(envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_serialize(const envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig__LocalityWeightedLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* ret = envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_serialize(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_serialize_ex(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__CommonLbConfig__ConsistentHashingLbConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_clear_use_hostname_for_hashing(envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_use_hostname_for_hashing(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_clear_hash_balance_factor(envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_hash_balance_factor(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_has_hash_balance_factor(const envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_set_use_hostname_for_hashing(envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_set_hash_balance_factor(envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_mutable_hash_balance_factor(envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_hash_balance_factor(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_set_hash_balance_factor(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_RefreshRate* envoy_config_cluster_v3_Cluster_RefreshRate_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_RefreshRate*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__RefreshRate_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_RefreshRate* envoy_config_cluster_v3_Cluster_RefreshRate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_RefreshRate* ret = envoy_config_cluster_v3_Cluster_RefreshRate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__RefreshRate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_RefreshRate* envoy_config_cluster_v3_Cluster_RefreshRate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_RefreshRate* ret = envoy_config_cluster_v3_Cluster_RefreshRate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__RefreshRate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_RefreshRate_serialize(const envoy_config_cluster_v3_Cluster_RefreshRate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__RefreshRate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_RefreshRate_serialize_ex(const envoy_config_cluster_v3_Cluster_RefreshRate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__RefreshRate_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RefreshRate_clear_base_interval(envoy_config_cluster_v3_Cluster_RefreshRate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_RefreshRate_base_interval(const envoy_config_cluster_v3_Cluster_RefreshRate* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_RefreshRate_has_base_interval(const envoy_config_cluster_v3_Cluster_RefreshRate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RefreshRate_clear_max_interval(envoy_config_cluster_v3_Cluster_RefreshRate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_RefreshRate_max_interval(const envoy_config_cluster_v3_Cluster_RefreshRate* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_RefreshRate_has_max_interval(const envoy_config_cluster_v3_Cluster_RefreshRate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_RefreshRate_set_base_interval(envoy_config_cluster_v3_Cluster_RefreshRate *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_RefreshRate_mutable_base_interval(envoy_config_cluster_v3_Cluster_RefreshRate* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_RefreshRate_base_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_RefreshRate_set_base_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_RefreshRate_set_max_interval(envoy_config_cluster_v3_Cluster_RefreshRate *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_cluster_v3_Cluster_RefreshRate_mutable_max_interval(envoy_config_cluster_v3_Cluster_RefreshRate* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_cluster_v3_Cluster_RefreshRate_max_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_RefreshRate_set_max_interval(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_Cluster_PreconnectPolicy* envoy_config_cluster_v3_Cluster_PreconnectPolicy_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Cluster_PreconnectPolicy*)_upb_Message_New(&envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Cluster_PreconnectPolicy* envoy_config_cluster_v3_Cluster_PreconnectPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_PreconnectPolicy* ret = envoy_config_cluster_v3_Cluster_PreconnectPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Cluster_PreconnectPolicy* envoy_config_cluster_v3_Cluster_PreconnectPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Cluster_PreconnectPolicy* ret = envoy_config_cluster_v3_Cluster_PreconnectPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_PreconnectPolicy_serialize(const envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Cluster_PreconnectPolicy_serialize_ex(const envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Cluster__PreconnectPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_PreconnectPolicy_clear_per_upstream_preconnect_ratio(envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_DoubleValue* envoy_config_cluster_v3_Cluster_PreconnectPolicy_per_upstream_preconnect_ratio(const envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg) {
  const struct google_protobuf_DoubleValue* default_val = NULL;
  const struct google_protobuf_DoubleValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__DoubleValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_PreconnectPolicy_has_per_upstream_preconnect_ratio(const envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_PreconnectPolicy_clear_predictive_preconnect_ratio(envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_DoubleValue* envoy_config_cluster_v3_Cluster_PreconnectPolicy_predictive_preconnect_ratio(const envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg) {
  const struct google_protobuf_DoubleValue* default_val = NULL;
  const struct google_protobuf_DoubleValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__DoubleValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Cluster_PreconnectPolicy_has_predictive_preconnect_ratio(const envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Cluster_PreconnectPolicy_set_per_upstream_preconnect_ratio(envoy_config_cluster_v3_Cluster_PreconnectPolicy *msg, struct google_protobuf_DoubleValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__DoubleValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_DoubleValue* envoy_config_cluster_v3_Cluster_PreconnectPolicy_mutable_per_upstream_preconnect_ratio(envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_DoubleValue* sub = (struct google_protobuf_DoubleValue*)envoy_config_cluster_v3_Cluster_PreconnectPolicy_per_upstream_preconnect_ratio(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_DoubleValue*)_upb_Message_New(&google__protobuf__DoubleValue_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_PreconnectPolicy_set_per_upstream_preconnect_ratio(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Cluster_PreconnectPolicy_set_predictive_preconnect_ratio(envoy_config_cluster_v3_Cluster_PreconnectPolicy *msg, struct google_protobuf_DoubleValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__DoubleValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_DoubleValue* envoy_config_cluster_v3_Cluster_PreconnectPolicy_mutable_predictive_preconnect_ratio(envoy_config_cluster_v3_Cluster_PreconnectPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_DoubleValue* sub = (struct google_protobuf_DoubleValue*)envoy_config_cluster_v3_Cluster_PreconnectPolicy_predictive_preconnect_ratio(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_DoubleValue*)_upb_Message_New(&google__protobuf__DoubleValue_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Cluster_PreconnectPolicy_set_predictive_preconnect_ratio(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy* envoy_config_cluster_v3_LoadBalancingPolicy_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_LoadBalancingPolicy*)_upb_Message_New(&envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy* envoy_config_cluster_v3_LoadBalancingPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_LoadBalancingPolicy* ret = envoy_config_cluster_v3_LoadBalancingPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy* envoy_config_cluster_v3_LoadBalancingPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_LoadBalancingPolicy* ret = envoy_config_cluster_v3_LoadBalancingPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_LoadBalancingPolicy_serialize(const envoy_config_cluster_v3_LoadBalancingPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_LoadBalancingPolicy_serialize_ex(const envoy_config_cluster_v3_LoadBalancingPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__LoadBalancingPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_LoadBalancingPolicy_clear_policies(envoy_config_cluster_v3_LoadBalancingPolicy* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_LoadBalancingPolicy_Policy* const* envoy_config_cluster_v3_LoadBalancingPolicy_policies(const envoy_config_cluster_v3_LoadBalancingPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_cluster_v3_LoadBalancingPolicy_Policy* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_cluster_v3_LoadBalancingPolicy_policies_upb_array(const envoy_config_cluster_v3_LoadBalancingPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_cluster_v3_LoadBalancingPolicy_policies_mutable_upb_array(envoy_config_cluster_v3_LoadBalancingPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy_Policy** envoy_config_cluster_v3_LoadBalancingPolicy_mutable_policies(envoy_config_cluster_v3_LoadBalancingPolicy* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_cluster_v3_LoadBalancingPolicy_Policy**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy_Policy** envoy_config_cluster_v3_LoadBalancingPolicy_resize_policies(envoy_config_cluster_v3_LoadBalancingPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_cluster_v3_LoadBalancingPolicy_Policy**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_cluster_v3_LoadBalancingPolicy_Policy* envoy_config_cluster_v3_LoadBalancingPolicy_add_policies(envoy_config_cluster_v3_LoadBalancingPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_cluster_v3_LoadBalancingPolicy_Policy* sub = (struct envoy_config_cluster_v3_LoadBalancingPolicy_Policy*)_upb_Message_New(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy_Policy* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_LoadBalancingPolicy_Policy*)_upb_Message_New(&envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy_Policy* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_LoadBalancingPolicy_Policy* ret = envoy_config_cluster_v3_LoadBalancingPolicy_Policy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_LoadBalancingPolicy_Policy* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_LoadBalancingPolicy_Policy* ret = envoy_config_cluster_v3_LoadBalancingPolicy_Policy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_serialize(const envoy_config_cluster_v3_LoadBalancingPolicy_Policy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_serialize_ex(const envoy_config_cluster_v3_LoadBalancingPolicy_Policy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__LoadBalancingPolicy__Policy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_LoadBalancingPolicy_Policy_clear_typed_extension_config(envoy_config_cluster_v3_LoadBalancingPolicy_Policy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_typed_extension_config(const envoy_config_cluster_v3_LoadBalancingPolicy_Policy* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_LoadBalancingPolicy_Policy_has_typed_extension_config(const envoy_config_cluster_v3_LoadBalancingPolicy_Policy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_LoadBalancingPolicy_Policy_set_typed_extension_config(envoy_config_cluster_v3_LoadBalancingPolicy_Policy *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_cluster_v3_LoadBalancingPolicy_Policy_mutable_typed_extension_config(envoy_config_cluster_v3_LoadBalancingPolicy_Policy* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_cluster_v3_LoadBalancingPolicy_Policy_typed_extension_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_LoadBalancingPolicy_Policy_set_typed_extension_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_UpstreamConnectionOptions* envoy_config_cluster_v3_UpstreamConnectionOptions_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_UpstreamConnectionOptions*)_upb_Message_New(&envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_UpstreamConnectionOptions* envoy_config_cluster_v3_UpstreamConnectionOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_UpstreamConnectionOptions* ret = envoy_config_cluster_v3_UpstreamConnectionOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_UpstreamConnectionOptions* envoy_config_cluster_v3_UpstreamConnectionOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_UpstreamConnectionOptions* ret = envoy_config_cluster_v3_UpstreamConnectionOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_UpstreamConnectionOptions_serialize(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_UpstreamConnectionOptions_serialize_ex(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__UpstreamConnectionOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_clear_tcp_keepalive(envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TcpKeepalive* envoy_config_cluster_v3_UpstreamConnectionOptions_tcp_keepalive(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const struct envoy_config_core_v3_TcpKeepalive* default_val = NULL;
  const struct envoy_config_core_v3_TcpKeepalive* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TcpKeepalive_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_UpstreamConnectionOptions_has_tcp_keepalive(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_clear_set_local_interface_name_on_upstream_connections(envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_UpstreamConnectionOptions_set_local_interface_name_on_upstream_connections(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_clear_happy_eyeballs_config(envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* envoy_config_cluster_v3_UpstreamConnectionOptions_happy_eyeballs_config(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* default_val = NULL;
  const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_UpstreamConnectionOptions_has_happy_eyeballs_config(const envoy_config_cluster_v3_UpstreamConnectionOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_set_tcp_keepalive(envoy_config_cluster_v3_UpstreamConnectionOptions *msg, struct envoy_config_core_v3_TcpKeepalive* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TcpKeepalive_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TcpKeepalive* envoy_config_cluster_v3_UpstreamConnectionOptions_mutable_tcp_keepalive(envoy_config_cluster_v3_UpstreamConnectionOptions* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TcpKeepalive* sub = (struct envoy_config_core_v3_TcpKeepalive*)envoy_config_cluster_v3_UpstreamConnectionOptions_tcp_keepalive(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TcpKeepalive*)_upb_Message_New(&envoy__config__core__v3__TcpKeepalive_msg_init, arena);
    if (sub) envoy_config_cluster_v3_UpstreamConnectionOptions_set_tcp_keepalive(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_set_set_local_interface_name_on_upstream_connections(envoy_config_cluster_v3_UpstreamConnectionOptions *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_set_happy_eyeballs_config(envoy_config_cluster_v3_UpstreamConnectionOptions *msg, envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* envoy_config_cluster_v3_UpstreamConnectionOptions_mutable_happy_eyeballs_config(envoy_config_cluster_v3_UpstreamConnectionOptions* msg, upb_Arena* arena) {
  struct envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* sub = (struct envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig*)envoy_config_cluster_v3_UpstreamConnectionOptions_happy_eyeballs_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig*)_upb_Message_New(&envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init, arena);
    if (sub) envoy_config_cluster_v3_UpstreamConnectionOptions_set_happy_eyeballs_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig*)_upb_Message_New(&envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* ret = envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* ret = envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_serialize(const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_serialize_ex(const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__UpstreamConnectionOptions__HappyEyeballsConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_clear_first_address_family_version(envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_first_address_family_version(const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_clear_first_address_family_count(envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_first_address_family_count(const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_has_first_address_family_count(const envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_set_first_address_family_version(envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_set_first_address_family_count(envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_mutable_first_address_family_count(envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_first_address_family_count(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_set_first_address_family_count(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_cluster_v3_TrackClusterStats* envoy_config_cluster_v3_TrackClusterStats_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_TrackClusterStats*)_upb_Message_New(&envoy__config__cluster__v3__TrackClusterStats_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_TrackClusterStats* envoy_config_cluster_v3_TrackClusterStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_TrackClusterStats* ret = envoy_config_cluster_v3_TrackClusterStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__TrackClusterStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_TrackClusterStats* envoy_config_cluster_v3_TrackClusterStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_TrackClusterStats* ret = envoy_config_cluster_v3_TrackClusterStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__TrackClusterStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_TrackClusterStats_serialize(const envoy_config_cluster_v3_TrackClusterStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__TrackClusterStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_TrackClusterStats_serialize_ex(const envoy_config_cluster_v3_TrackClusterStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__TrackClusterStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_TrackClusterStats_clear_timeout_budgets(envoy_config_cluster_v3_TrackClusterStats* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_TrackClusterStats_timeout_budgets(const envoy_config_cluster_v3_TrackClusterStats* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_TrackClusterStats_clear_request_response_sizes(envoy_config_cluster_v3_TrackClusterStats* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_TrackClusterStats_request_response_sizes(const envoy_config_cluster_v3_TrackClusterStats* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_TrackClusterStats_clear_per_endpoint_stats(envoy_config_cluster_v3_TrackClusterStats* msg) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_cluster_v3_TrackClusterStats_per_endpoint_stats(const envoy_config_cluster_v3_TrackClusterStats* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_cluster_v3_TrackClusterStats_set_timeout_budgets(envoy_config_cluster_v3_TrackClusterStats *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_TrackClusterStats_set_request_response_sizes(envoy_config_cluster_v3_TrackClusterStats *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_TrackClusterStats_set_per_endpoint_stats(envoy_config_cluster_v3_TrackClusterStats *msg, bool value) {
  const upb_MiniTableField field = {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
