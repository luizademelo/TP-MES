
#ifndef GOOGLE_PROTOBUF_EMPTY_PROTO_UPB_H__UPB_H_
#define GOOGLE_PROTOBUF_EMPTY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/protobuf/empty.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct google_protobuf_Empty { upb_Message UPB_PRIVATE(base); } google_protobuf_Empty;

UPB_INLINE google_protobuf_Empty* google_protobuf_Empty_new(upb_Arena* arena) {
  return (google_protobuf_Empty*)_upb_Message_New(&google__protobuf__Empty_msg_init, arena);
}
UPB_INLINE google_protobuf_Empty* google_protobuf_Empty_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_Empty* ret = google_protobuf_Empty_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Empty_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_Empty* google_protobuf_Empty_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_Empty* ret = google_protobuf_Empty_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Empty_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_Empty_serialize(const google_protobuf_Empty* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Empty_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_Empty_serialize_ex(const google_protobuf_Empty* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Empty_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
