
#ifndef ENVOY_EXTENSIONS_FILTERS_COMMON_FAULT_V3_FAULT_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_FILTERS_COMMON_FAULT_V3_FAULT_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_filters_common_fault_v3_fault_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_common_fault_v3_FaultDelay_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_common_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.common.fault.v3.FaultDelay");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_common_fault_v3_FaultDelay_HeaderDelay_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_common_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.common.fault.v3.FaultDelay.HeaderDelay");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_common_fault_v3_FaultRateLimit_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_common_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.common.fault.v3.FaultRateLimit");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_common_fault_v3_FaultRateLimit_FixedLimit_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_common_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.common.fault.v3.FaultRateLimit.FixedLimit");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_filters_common_fault_v3_FaultRateLimit_HeaderLimit_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_filters_common_fault_v3_fault_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.filters.common.fault.v3.FaultRateLimit.HeaderLimit");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
