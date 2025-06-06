
#ifndef ENVOY_SERVICE_LOAD_STATS_V3_LRS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_SERVICE_LOAD_STATS_V3_LRS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_service_load_stats_v3_lrs_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_service_load_stats_v3_LoadStatsRequest_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_load_stats_v3_lrs_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.load_stats.v3.LoadStatsRequest");
}

UPB_INLINE const upb_MessageDef *envoy_service_load_stats_v3_LoadStatsResponse_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_load_stats_v3_lrs_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.load_stats.v3.LoadStatsResponse");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
