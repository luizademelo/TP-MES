
#ifndef ENVOY_CONFIG_CORE_V3_ADDRESS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CORE_V3_ADDRESS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_core_v3_address_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Pipe_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Pipe");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_EnvoyInternalAddress_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.EnvoyInternalAddress");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SocketAddress_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SocketAddress");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_TcpKeepalive_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.TcpKeepalive");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_ExtraSourceAddress_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.ExtraSourceAddress");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_BindConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.BindConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Address_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Address");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_CidrRange_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_address_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.CidrRange");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
