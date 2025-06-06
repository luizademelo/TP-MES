
#ifndef ENVOY_SERVICE_STATUS_V3_CSDS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_SERVICE_STATUS_V3_CSDS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_service_status_v3_csds_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_service_status_v3_ClientStatusRequest_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_status_v3_csds_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.status.v3.ClientStatusRequest");
}

UPB_INLINE const upb_MessageDef *envoy_service_status_v3_PerXdsConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_status_v3_csds_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.status.v3.PerXdsConfig");
}

UPB_INLINE const upb_MessageDef *envoy_service_status_v3_ClientConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_status_v3_csds_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.status.v3.ClientConfig");
}

UPB_INLINE const upb_MessageDef *envoy_service_status_v3_ClientConfig_GenericXdsConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_status_v3_csds_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.status.v3.ClientConfig.GenericXdsConfig");
}

UPB_INLINE const upb_MessageDef *envoy_service_status_v3_ClientStatusResponse_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_service_status_v3_csds_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.service.status.v3.ClientStatusResponse");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
