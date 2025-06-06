
#ifndef ENVOY_CONFIG_CORE_V3_GRPC_SERVICE_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CORE_V3_GRPC_SERVICE_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_EnvoyGrpc_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.EnvoyGrpc");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_SslCredentials_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.SslCredentials");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_GoogleLocalCredentials_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.GoogleLocalCredentials");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelCredentials_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelCredentials");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_ServiceAccountJWTAccessCredentials_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.ServiceAccountJWTAccessCredentials");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_GoogleIAMCredentials_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.GoogleIAMCredentials");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_MetadataCredentialsFromPlugin_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.MetadataCredentialsFromPlugin");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_CallCredentials_StsService_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.CallCredentials.StsService");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelArgs");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_Value_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelArgs.Value");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_GrpcService_GoogleGrpc_ChannelArgs_ArgsEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_grpc_service_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.GrpcService.GoogleGrpc.ChannelArgs.ArgsEntry");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
