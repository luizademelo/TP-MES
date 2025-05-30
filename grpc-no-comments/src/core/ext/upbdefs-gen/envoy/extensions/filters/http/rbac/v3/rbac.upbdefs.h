
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_RBAC_V3_RBAC_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_RBAC_V3_RBAC_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_filters_http_rbac_v3_rbac_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_rbac_v3_RBAC_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_rbac_v3_rbac_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.rbac.v3.RBAC");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_rbac_v3_RBACPerRoute_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_rbac_v3_rbac_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.rbac.v3.RBACPerRoute");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
