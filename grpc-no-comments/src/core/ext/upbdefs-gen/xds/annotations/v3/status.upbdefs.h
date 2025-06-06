
#ifndef XDS_ANNOTATIONS_V3_STATUS_PROTO_UPB_H__UPBDEFS_H_
#define XDS_ANNOTATIONS_V3_STATUS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *xds_annotations_v3_FileStatusAnnotation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_annotations_v3_status_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.annotations.v3.FileStatusAnnotation");
}

UPB_INLINE const upb_MessageDef *xds_annotations_v3_MessageStatusAnnotation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_annotations_v3_status_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.annotations.v3.MessageStatusAnnotation");
}

UPB_INLINE const upb_MessageDef *xds_annotations_v3_FieldStatusAnnotation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_annotations_v3_status_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.annotations.v3.FieldStatusAnnotation");
}

UPB_INLINE const upb_MessageDef *xds_annotations_v3_StatusAnnotation_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_annotations_v3_status_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.annotations.v3.StatusAnnotation");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
