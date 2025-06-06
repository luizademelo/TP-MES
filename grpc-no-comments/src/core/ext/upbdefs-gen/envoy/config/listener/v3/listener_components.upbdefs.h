
#ifndef ENVOY_CONFIG_LISTENER_V3_LISTENER_COMPONENTS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_LISTENER_V3_LISTENER_COMPONENTS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_listener_v3_listener_components_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_listener_v3_Filter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_listener_v3_listener_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.listener.v3.Filter");
}

UPB_INLINE const upb_MessageDef *envoy_config_listener_v3_FilterChainMatch_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_listener_v3_listener_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.listener.v3.FilterChainMatch");
}

UPB_INLINE const upb_MessageDef *envoy_config_listener_v3_FilterChain_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_listener_v3_listener_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.listener.v3.FilterChain");
}

UPB_INLINE const upb_MessageDef *envoy_config_listener_v3_ListenerFilterChainMatchPredicate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_listener_v3_listener_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.listener.v3.ListenerFilterChainMatchPredicate");
}

UPB_INLINE const upb_MessageDef *envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_listener_v3_listener_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.listener.v3.ListenerFilterChainMatchPredicate.MatchSet");
}

UPB_INLINE const upb_MessageDef *envoy_config_listener_v3_ListenerFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_listener_v3_listener_components_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.listener.v3.ListenerFilter");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
