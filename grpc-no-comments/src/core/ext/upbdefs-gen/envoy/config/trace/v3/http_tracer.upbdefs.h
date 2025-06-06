
#ifndef ENVOY_CONFIG_TRACE_V3_HTTP_TRACER_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_TRACE_V3_HTTP_TRACER_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_trace_v3_http_tracer_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_trace_v3_Tracing_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_trace_v3_http_tracer_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.trace.v3.Tracing");
}

UPB_INLINE const upb_MessageDef *envoy_config_trace_v3_Tracing_Http_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_trace_v3_http_tracer_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.trace.v3.Tracing.Http");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
