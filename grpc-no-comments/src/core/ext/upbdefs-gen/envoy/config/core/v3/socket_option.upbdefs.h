
#ifndef ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CORE_V3_SOCKET_OPTION_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_core_v3_socket_option_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SocketOption_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_socket_option_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SocketOption");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SocketOption_SocketType_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_socket_option_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SocketOption.SocketType");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SocketOption_SocketType_Stream_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_socket_option_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SocketOption.SocketType.Stream");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SocketOption_SocketType_Datagram_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_socket_option_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SocketOption.SocketType.Datagram");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_SocketOptionsOverride_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_socket_option_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.SocketOptionsOverride");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
