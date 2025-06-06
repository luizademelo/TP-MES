
#ifndef XDS_CORE_V3_COLLECTION_ENTRY_PROTO_UPB_H__UPBDEFS_H_
#define XDS_CORE_V3_COLLECTION_ENTRY_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init xds_core_v3_collection_entry_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *xds_core_v3_CollectionEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_core_v3_collection_entry_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.core.v3.CollectionEntry");
}

UPB_INLINE const upb_MessageDef *xds_core_v3_CollectionEntry_InlineEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &xds_core_v3_collection_entry_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "xds.core.v3.CollectionEntry.InlineEntry");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
