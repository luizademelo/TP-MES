
#ifndef ENVOY_CONFIG_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_accesslog_v3_accesslog_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_AccessLog_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.AccessLog");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_AccessLogFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.AccessLogFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_ComparisonFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.ComparisonFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_StatusCodeFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.StatusCodeFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_DurationFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.DurationFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_NotHealthCheckFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.NotHealthCheckFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_TraceableFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.TraceableFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_RuntimeFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.RuntimeFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_AndFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.AndFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_OrFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.OrFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_HeaderFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.HeaderFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_ResponseFlagFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.ResponseFlagFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_GrpcStatusFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.GrpcStatusFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_MetadataFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.MetadataFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_LogTypeFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.LogTypeFilter");
}

UPB_INLINE const upb_MessageDef *envoy_config_accesslog_v3_ExtensionFilter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_accesslog_v3_accesslog_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.accesslog.v3.ExtensionFilter");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
