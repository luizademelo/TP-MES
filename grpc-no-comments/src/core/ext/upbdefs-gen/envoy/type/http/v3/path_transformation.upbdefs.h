
#ifndef ENVOY_TYPE_HTTP_V3_PATH_TRANSFORMATION_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_TYPE_HTTP_V3_PATH_TRANSFORMATION_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_type_http_v3_path_transformation_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_type_http_v3_PathTransformation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_http_v3_path_transformation_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.http.v3.PathTransformation");
}

UPB_INLINE const upb_MessageDef *envoy_type_http_v3_PathTransformation_Operation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_http_v3_path_transformation_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.http.v3.PathTransformation.Operation");
}

UPB_INLINE const upb_MessageDef *envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_http_v3_path_transformation_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.http.v3.PathTransformation.Operation.NormalizePathRFC3986");
}

UPB_INLINE const upb_MessageDef *envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_http_v3_path_transformation_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.http.v3.PathTransformation.Operation.MergeSlashes");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
