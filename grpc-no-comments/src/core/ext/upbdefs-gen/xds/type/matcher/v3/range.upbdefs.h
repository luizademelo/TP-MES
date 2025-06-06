
#ifndef XDS_TYPE_MATCHER_V3_RANGE_PROTO_UPB_H__UPBDEFS_H_
#define XDS_TYPE_MATCHER_V3_RANGE_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init xds_type_matcher_v3_range_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *xds_type_matcher_v3_Int64RangeMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_matcher_v3_range_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.matcher.v3.Int64RangeMatcher");
}

UPB_INLINE const upb_MessageDef *xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_matcher_v3_range_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.matcher.v3.Int64RangeMatcher.RangeMatcher");
}

UPB_INLINE const upb_MessageDef *xds_type_matcher_v3_Int32RangeMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_matcher_v3_range_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.matcher.v3.Int32RangeMatcher");
}

UPB_INLINE const upb_MessageDef *xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_matcher_v3_range_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.matcher.v3.Int32RangeMatcher.RangeMatcher");
}

UPB_INLINE const upb_MessageDef *xds_type_matcher_v3_DoubleRangeMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_matcher_v3_range_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.matcher.v3.DoubleRangeMatcher");
}

UPB_INLINE const upb_MessageDef *xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_type_matcher_v3_range_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.type.matcher.v3.DoubleRangeMatcher.RangeMatcher");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
