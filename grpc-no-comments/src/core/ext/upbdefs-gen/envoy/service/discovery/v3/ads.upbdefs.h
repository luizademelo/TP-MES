
#ifndef ENVOY_SERVICE_DISCOVERY_V3_ADS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_SERVICE_DISCOVERY_V3_ADS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_service_discovery_v3_ads_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_service_discovery_v3_AdsDummy_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_discovery_v3_ads_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.discovery.v3.AdsDummy");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
