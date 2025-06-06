
#ifndef GOOGLE_PROTOBUF_DURATION_PROTO_UPB_H__UPB_H_
#define GOOGLE_PROTOBUF_DURATION_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/protobuf/duration.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct google_protobuf_Duration { upb_Message UPB_PRIVATE(base); } google_protobuf_Duration;

UPB_INLINE google_protobuf_Duration* google_protobuf_Duration_new(upb_Arena* arena) {
  return (google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
}
UPB_INLINE google_protobuf_Duration* google_protobuf_Duration_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_Duration* ret = google_protobuf_Duration_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Duration_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_Duration* google_protobuf_Duration_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_Duration* ret = google_protobuf_Duration_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Duration_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_Duration_serialize(const google_protobuf_Duration* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Duration_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_Duration_serialize_ex(const google_protobuf_Duration* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Duration_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_Duration_clear_seconds(google_protobuf_Duration* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_protobuf_Duration_seconds(const google_protobuf_Duration* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_protobuf_Duration_clear_nanos(google_protobuf_Duration* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_protobuf_Duration_nanos(const google_protobuf_Duration* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_Duration_set_seconds(google_protobuf_Duration *msg, int64_t value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_protobuf_Duration_set_nanos(google_protobuf_Duration *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
