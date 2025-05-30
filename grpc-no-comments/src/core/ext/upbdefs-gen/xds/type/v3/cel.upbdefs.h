
#ifndef XDS_TYPE_V3_CEL_PROTO_UPB_H__UPBDEFS_H_
#define XDS_TYPE_V3_CEL_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init xds_type_v3_cel_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *xds_type_v3_CelExpression_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_v3_cel_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.v3.CelExpression");
}

UPB_INLINE const upb_MessageDef *xds_type_v3_CelExtractString_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_v3_cel_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.v3.CelExtractString");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
