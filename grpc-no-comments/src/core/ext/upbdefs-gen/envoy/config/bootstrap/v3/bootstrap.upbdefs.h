
#ifndef ENVOY_CONFIG_BOOTSTRAP_V3_BOOTSTRAP_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_BOOTSTRAP_V3_BOOTSTRAP_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_StaticResources_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.StaticResources");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_DynamicResources_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.DynamicResources");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.ApplicationLogConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_ApplicationLogConfig_LogFormat_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.ApplicationLogConfig.LogFormat");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_DeferredStatOptions_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.DeferredStatOptions");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_GrpcAsyncClientManagerConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.GrpcAsyncClientManagerConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Bootstrap_CertificateProviderInstancesEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Bootstrap.CertificateProviderInstancesEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Admin_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Admin");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_ClusterManager_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.ClusterManager");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_ClusterManager_OutlierDetection_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.ClusterManager.OutlierDetection");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Watchdogs_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Watchdogs");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Watchdog_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Watchdog");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Watchdog_WatchdogAction_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Watchdog.WatchdogAction");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_FatalAction_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.FatalAction");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_Runtime_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.Runtime");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_RuntimeLayer_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.RuntimeLayer");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_RuntimeLayer_DiskLayer_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.RuntimeLayer.DiskLayer");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_RuntimeLayer_AdminLayer_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.RuntimeLayer.AdminLayer");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_RuntimeLayer_RtdsLayer_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.RuntimeLayer.RtdsLayer");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_LayeredRuntime_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.LayeredRuntime");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_CustomInlineHeader_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.CustomInlineHeader");
}

UPB_INLINE const upb_MessageDef *envoy_config_bootstrap_v3_MemoryAllocatorManager_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.bootstrap.v3.MemoryAllocatorManager");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
