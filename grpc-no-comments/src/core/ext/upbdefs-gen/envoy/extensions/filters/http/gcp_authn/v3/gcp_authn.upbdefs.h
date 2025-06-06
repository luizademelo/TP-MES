
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_GCP_AUTHN_V3_GCP_AUTHN_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_GCP_AUTHN_V3_GCP_AUTHN_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_filters_http_gcp_authn_v3_gcp_authn_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_gcp_authn_v3_GcpAuthnFilterConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_gcp_authn_v3_gcp_authn_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.gcp_authn.v3.GcpAuthnFilterConfig");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_gcp_authn_v3_Audience_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_gcp_authn_v3_gcp_authn_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.gcp_authn.v3.Audience");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_gcp_authn_v3_TokenCacheConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_gcp_authn_v3_gcp_authn_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.gcp_authn.v3.TokenCacheConfig");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_gcp_authn_v3_TokenHeader_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_gcp_authn_v3_gcp_authn_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.gcp_authn.v3.TokenHeader");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
