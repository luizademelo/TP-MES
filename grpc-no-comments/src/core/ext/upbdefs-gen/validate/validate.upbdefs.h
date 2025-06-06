
#ifndef VALIDATE_VALIDATE_PROTO_UPB_H__UPBDEFS_H_
#define VALIDATE_VALIDATE_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *validate_FieldRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.FieldRules");
}

UPB_INLINE const upb_MessageDef *validate_FloatRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.FloatRules");
}

UPB_INLINE const upb_MessageDef *validate_DoubleRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.DoubleRules");
}

UPB_INLINE const upb_MessageDef *validate_Int32Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.Int32Rules");
}

UPB_INLINE const upb_MessageDef *validate_Int64Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.Int64Rules");
}

UPB_INLINE const upb_MessageDef *validate_UInt32Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.UInt32Rules");
}

UPB_INLINE const upb_MessageDef *validate_UInt64Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.UInt64Rules");
}

UPB_INLINE const upb_MessageDef *validate_SInt32Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.SInt32Rules");
}

UPB_INLINE const upb_MessageDef *validate_SInt64Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.SInt64Rules");
}

UPB_INLINE const upb_MessageDef *validate_Fixed32Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.Fixed32Rules");
}

UPB_INLINE const upb_MessageDef *validate_Fixed64Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.Fixed64Rules");
}

UPB_INLINE const upb_MessageDef *validate_SFixed32Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.SFixed32Rules");
}

UPB_INLINE const upb_MessageDef *validate_SFixed64Rules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.SFixed64Rules");
}

UPB_INLINE const upb_MessageDef *validate_BoolRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.BoolRules");
}

UPB_INLINE const upb_MessageDef *validate_StringRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.StringRules");
}

UPB_INLINE const upb_MessageDef *validate_BytesRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.BytesRules");
}

UPB_INLINE const upb_MessageDef *validate_EnumRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.EnumRules");
}

UPB_INLINE const upb_MessageDef *validate_MessageRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.MessageRules");
}

UPB_INLINE const upb_MessageDef *validate_RepeatedRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.RepeatedRules");
}

UPB_INLINE const upb_MessageDef *validate_MapRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.MapRules");
}

UPB_INLINE const upb_MessageDef *validate_AnyRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.AnyRules");
}

UPB_INLINE const upb_MessageDef *validate_DurationRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.DurationRules");
}

UPB_INLINE const upb_MessageDef *validate_TimestampRules_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &validate_validate_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "validate.TimestampRules");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
