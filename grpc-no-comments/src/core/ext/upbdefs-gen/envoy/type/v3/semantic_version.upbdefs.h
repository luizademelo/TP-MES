
#ifndef ENVOY_TYPE_V3_SEMANTIC_VERSION_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_TYPE_V3_SEMANTIC_VERSION_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_type_v3_semantic_version_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_type_v3_SemanticVersion_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_type_v3_semantic_version_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.type.v3.SemanticVersion");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
