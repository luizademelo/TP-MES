
#ifndef ENVOY_EXTENSIONS_UPSTREAMS_HTTP_V3_HTTP_PROTOCOL_OPTIONS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_UPSTREAMS_HTTP_V3_HTTP_PROTOCOL_OPTIONS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_upstreams_http_v3_http_protocol_options_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_upstreams_http_v3_HttpProtocolOptions_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_upstreams_http_v3_http_protocol_options_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.upstreams.http.v3.HttpProtocolOptions");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_upstreams_http_v3_http_protocol_options_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.upstreams.http.v3.HttpProtocolOptions.ExplicitHttpConfig");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_upstreams_http_v3_http_protocol_options_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.upstreams.http.v3.HttpProtocolOptions.UseDownstreamHttpConfig");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_upstreams_http_v3_http_protocol_options_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.upstreams.http.v3.HttpProtocolOptions.AutoHttpConfig");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
