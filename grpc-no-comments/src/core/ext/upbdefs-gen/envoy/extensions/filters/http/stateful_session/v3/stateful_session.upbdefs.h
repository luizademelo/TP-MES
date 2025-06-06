
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_STATEFUL_SESSION_V3_STATEFUL_SESSION_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_STATEFUL_SESSION_V3_STATEFUL_SESSION_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_filters_http_stateful_session_v3_stateful_session_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_stateful_session_v3_StatefulSession_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_stateful_session_v3_stateful_session_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.stateful_session.v3.StatefulSession");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_stateful_session_v3_stateful_session_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.stateful_session.v3.StatefulSessionPerRoute");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
