
#ifndef ENVOY_ANNOTATIONS_RESOURCE_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_ANNOTATIONS_RESOURCE_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_annotations_resource_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_annotations_ResourceAnnotation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_annotations_resource_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.annotations.ResourceAnnotation");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
