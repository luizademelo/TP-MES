
#ifndef GOOGLE_PROTOBUF_TIMESTAMP_PROTO_UPB_H__UPBDEFS_H_
#define GOOGLE_PROTOBUF_TIMESTAMP_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init google_protobuf_timestamp_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *google_protobuf_Timestamp_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_timestamp_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.Timestamp");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
