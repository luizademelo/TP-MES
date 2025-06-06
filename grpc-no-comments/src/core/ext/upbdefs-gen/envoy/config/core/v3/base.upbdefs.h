
#ifndef ENVOY_CONFIG_CORE_V3_BASE_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_CONFIG_CORE_V3_BASE_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Locality_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Locality");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_BuildVersion_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.BuildVersion");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Extension_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Extension");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Node_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Node");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Node_DynamicParametersEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Node.DynamicParametersEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Metadata_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Metadata");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Metadata_FilterMetadataEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Metadata.FilterMetadataEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_Metadata_TypedFilterMetadataEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.Metadata.TypedFilterMetadataEntry");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RuntimeUInt32_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RuntimeUInt32");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RuntimePercent_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RuntimePercent");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RuntimeDouble_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RuntimeDouble");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RuntimeFeatureFlag_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RuntimeFeatureFlag");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_KeyValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.KeyValue");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_KeyValuePair_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.KeyValuePair");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_KeyValueAppend_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.KeyValueAppend");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_KeyValueMutation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.KeyValueMutation");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_QueryParameter_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.QueryParameter");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HeaderValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HeaderValue");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HeaderValueOption_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HeaderValueOption");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_HeaderMap_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.HeaderMap");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_WatchedDirectory_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.WatchedDirectory");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_DataSource_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.DataSource");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RetryPolicy_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RetryPolicy");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RetryPolicy_RetryPriority_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RetryPolicy.RetryPriority");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RetryPolicy_RetryHostPredicate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RetryPolicy.RetryHostPredicate");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RemoteDataSource_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RemoteDataSource");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_AsyncDataSource_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.AsyncDataSource");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_TransportSocket_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.TransportSocket");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_RuntimeFractionalPercent_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.RuntimeFractionalPercent");
}

UPB_INLINE const upb_MessageDef *envoy_config_core_v3_ControlPlane_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_core_v3_base_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.core.v3.ControlPlane");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
