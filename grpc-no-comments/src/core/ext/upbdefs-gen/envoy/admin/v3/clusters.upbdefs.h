
#ifndef ENVOY_ADMIN_V3_CLUSTERS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_ADMIN_V3_CLUSTERS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_admin_v3_clusters_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_admin_v3_Clusters_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_clusters_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.Clusters");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ClusterStatus_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_clusters_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ClusterStatus");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_HostStatus_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_clusters_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.HostStatus");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_HostHealthStatus_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_clusters_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.HostHealthStatus");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
