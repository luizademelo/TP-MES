
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_FAULT_V3_FAULT_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_FAULT_V3_FAULT_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_filters_http_fault_v3_fault_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_fault_v3_FaultAbort_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.fault.v3.FaultAbort");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.fault.v3.FaultAbort.HeaderAbort");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_http_fault_v3_HTTPFault_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_http_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.http.fault.v3.HTTPFault");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
