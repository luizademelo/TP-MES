
#ifndef ENVOY_TYPE_MATCHER_V3_PATH_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_TYPE_MATCHER_V3_PATH_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_type_matcher_v3_path_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_type_matcher_v3_PathMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_matcher_v3_path_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.matcher.v3.PathMatcher");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
