
#ifndef ENVOY_CONFIG_ROUTE_V3_SCOPED_ROUTE_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_ROUTE_V3_SCOPED_ROUTE_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_route_v3_scoped_route_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_route_v3_ScopedRouteConfiguration_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_route_v3_scoped_route_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.route.v3.ScopedRouteConfiguration");
}

UPB_INLINE const upb_MessageDef *envoy_config_route_v3_ScopedRouteConfiguration_Key_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_route_v3_scoped_route_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.route.v3.ScopedRouteConfiguration.Key");
}

UPB_INLINE const upb_MessageDef *envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_route_v3_scoped_route_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.route.v3.ScopedRouteConfiguration.Key.Fragment");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
