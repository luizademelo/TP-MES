
#ifndef XDS_ANNOTATIONS_V3_VERSIONING_PROTO_UPB_H__UPBDEFS_H_
#define XDS_ANNOTATIONS_V3_VERSIONING_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init xds_annotations_v3_versioning_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *xds_annotations_v3_VersioningAnnotation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_annotations_v3_versioning_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.annotations.v3.VersioningAnnotation");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
