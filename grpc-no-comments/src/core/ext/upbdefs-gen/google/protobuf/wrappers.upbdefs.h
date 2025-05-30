
#ifndef GOOGLE_PROTOBUF_WRAPPERS_PROTO_UPB_H__UPBDEFS_H_
#define GOOGLE_PROTOBUF_WRAPPERS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *google_protobuf_DoubleValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.DoubleValue");
}

UPB_INLINE const upb_MessageDef *google_protobuf_FloatValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.FloatValue");
}

UPB_INLINE const upb_MessageDef *google_protobuf_Int64Value_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.Int64Value");
}

UPB_INLINE const upb_MessageDef *google_protobuf_UInt64Value_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.UInt64Value");
}

UPB_INLINE const upb_MessageDef *google_protobuf_Int32Value_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.Int32Value");
}

UPB_INLINE const upb_MessageDef *google_protobuf_UInt32Value_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.UInt32Value");
}

UPB_INLINE const upb_MessageDef *google_protobuf_BoolValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.BoolValue");
}

UPB_INLINE const upb_MessageDef *google_protobuf_StringValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.StringValue");
}

UPB_INLINE const upb_MessageDef *google_protobuf_BytesValue_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_protobuf_wrappers_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.protobuf.BytesValue");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
