
#ifndef ENVOY_CONFIG_CORE_V3_HEALTH_CHECK_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CORE_V3_HEALTH_CHECK_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_core_v3_health_check_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthStatusSet_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthStatusSet");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_Payload_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.Payload");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_HttpHealthCheck_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.HttpHealthCheck");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_TcpHealthCheck_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.TcpHealthCheck");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_RedisHealthCheck_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.RedisHealthCheck");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_GrpcHealthCheck_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.GrpcHealthCheck");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_CustomHealthCheck_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.CustomHealthCheck");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HealthCheck_TlsOptions_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_health_check_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HealthCheck.TlsOptions");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
