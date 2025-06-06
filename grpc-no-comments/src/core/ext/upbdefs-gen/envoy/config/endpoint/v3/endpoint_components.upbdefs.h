
#ifndef ENVOY_CONFIG_ENDPOINT_V3_ENDPOINT_COMPONENTS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_ENDPOINT_V3_ENDPOINT_COMPONENTS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_Endpoint_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.Endpoint");
}

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_Endpoint_HealthCheckConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.Endpoint.HealthCheckConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_Endpoint_AdditionalAddress_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.Endpoint.AdditionalAddress");
}

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_LbEndpoint_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.LbEndpoint");
}

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_LedsClusterLocalityConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.LedsClusterLocalityConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_LocalityLbEndpoints_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.LocalityLbEndpoints");
}

UPB_INLINE const upb_MessageDef *envoy_config_endpoint_v3_LocalityLbEndpoints_LbEndpointList_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_endpoint_v3_endpoint_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.endpoint.v3.LocalityLbEndpoints.LbEndpointList");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
