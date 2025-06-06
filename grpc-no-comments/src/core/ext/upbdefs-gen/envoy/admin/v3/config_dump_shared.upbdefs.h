
#ifndef ENVOY_ADMIN_V3_CONFIG_DUMP_SHARED_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_ADMIN_V3_CONFIG_DUMP_SHARED_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_admin_v3_config_dump_shared_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_admin_v3_UpdateFailureState_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.UpdateFailureState");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ListenersConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ListenersConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ListenersConfigDump_StaticListener_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ListenersConfigDump.StaticListener");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ListenersConfigDump_DynamicListenerState_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ListenersConfigDump.DynamicListenerState");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ListenersConfigDump_DynamicListener_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ListenersConfigDump.DynamicListener");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ClustersConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ClustersConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ClustersConfigDump_StaticCluster_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ClustersConfigDump.StaticCluster");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ClustersConfigDump_DynamicCluster_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ClustersConfigDump.DynamicCluster");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_RoutesConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.RoutesConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_RoutesConfigDump_StaticRouteConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.RoutesConfigDump.StaticRouteConfig");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.RoutesConfigDump.DynamicRouteConfig");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ScopedRoutesConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ScopedRoutesConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ScopedRoutesConfigDump.InlineScopedRouteConfigs");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.ScopedRoutesConfigDump.DynamicScopedRouteConfigs");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_EndpointsConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.EndpointsConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.EndpointsConfigDump.StaticEndpointConfig");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.EndpointsConfigDump.DynamicEndpointConfig");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_EcdsConfigDump_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.EcdsConfigDump");
}

UPB_INLINE const upb_MessageDef *envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_admin_v3_config_dump_shared_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.admin.v3.EcdsConfigDump.EcdsFilterConfig");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
