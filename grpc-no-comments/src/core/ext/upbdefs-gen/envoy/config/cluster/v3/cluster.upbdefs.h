
#ifndef ENVOY_CONFIG_CLUSTER_V3_CLUSTER_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CLUSTER_V3_CLUSTER_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_cluster_v3_cluster_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_ClusterCollection_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.ClusterCollection");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_TransportSocketMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.TransportSocketMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_CustomClusterType_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.CustomClusterType");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_EdsClusterConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.EdsClusterConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_LbSubsetConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.LbSubsetConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_LbSubsetConfig_LbSubsetSelector_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.LbSubsetConfig.LbSubsetSelector");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_SlowStartConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.SlowStartConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_RoundRobinLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.RoundRobinLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_LeastRequestLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.LeastRequestLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_RingHashLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.RingHashLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_MaglevLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.MaglevLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_OriginalDstLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.OriginalDstLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_CommonLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.CommonLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_CommonLbConfig_ZoneAwareLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.CommonLbConfig.ZoneAwareLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_CommonLbConfig_LocalityWeightedLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.CommonLbConfig.LocalityWeightedLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_CommonLbConfig_ConsistentHashingLbConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.CommonLbConfig.ConsistentHashingLbConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_RefreshRate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.RefreshRate");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_PreconnectPolicy_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.PreconnectPolicy");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_Cluster_TypedExtensionProtocolOptionsEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.Cluster.TypedExtensionProtocolOptionsEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_LoadBalancingPolicy_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.LoadBalancingPolicy");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_LoadBalancingPolicy_Policy_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.LoadBalancingPolicy.Policy");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_UpstreamConnectionOptions_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.UpstreamConnectionOptions");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_UpstreamConnectionOptions_HappyEyeballsConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.UpstreamConnectionOptions.HappyEyeballsConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_cluster_v3_TrackClusterStats_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_cluster_v3_cluster_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.cluster.v3.TrackClusterStats");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
