
#ifndef ENVOY_TYPE_METADATA_V3_METADATA_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_TYPE_METADATA_V3_METADATA_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_type_metadata_v3_metadata_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKey_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKey");
}

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKey_PathSegment_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKey.PathSegment");
}

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKind_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKind");
}

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKind_Request_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKind.Request");
}

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKind_Route_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKind.Route");
}

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKind_Cluster_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKind.Cluster");
}

UPB_INLINE const upb_MessageDef *envoy_type_metadata_v3_MetadataKind_Host_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_metadata_v3_metadata_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.metadata.v3.MetadataKind.Host");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
