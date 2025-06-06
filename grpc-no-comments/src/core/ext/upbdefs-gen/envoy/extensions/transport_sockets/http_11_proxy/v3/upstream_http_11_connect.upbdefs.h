
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_HTTP_11_PROXY_V3_UPSTREAM_HTTP_11_CONNECT_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_HTTP_11_PROXY_V3_UPSTREAM_HTTP_11_CONNECT_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_transport_sockets_http_11_proxy_v3_upstream_http_11_connect_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_http_11_proxy_v3_upstream_http_11_connect_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.http_11_proxy.v3.Http11ProxyUpstreamTransport");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
