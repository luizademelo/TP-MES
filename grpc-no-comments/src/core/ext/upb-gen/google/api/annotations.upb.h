
#ifndef GOOGLE_API_ANNOTATIONS_PROTO_UPB_H__UPB_H_
#define GOOGLE_API_ANNOTATIONS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/api/annotations.upb_minitable.h"

#include "google/api/http.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

struct google_protobuf_MethodOptions;

UPB_INLINE bool google_api_has_http(const struct google_protobuf_MethodOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &google_api_http_ext);
}
UPB_INLINE void google_api_clear_http(struct google_protobuf_MethodOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &google_api_http_ext);
}
UPB_INLINE const struct google_api_HttpRule* google_api_http(const struct google_protobuf_MethodOptions* msg) {
  const upb_MiniTableExtension* ext = &google_api_http_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const struct google_api_HttpRule* default_val = NULL;
  const struct google_api_HttpRule* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_set_http(struct google_protobuf_MethodOptions* msg, const struct google_api_HttpRule* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &google_api_http_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct google_api_HttpRule* google_api_mutable_http(struct google_protobuf_MethodOptions* msg,
                                    upb_Arena* arena) {
  struct google_api_HttpRule* sub = (struct google_api_HttpRule*)google_api_http(msg);
  if (sub == NULL) {
    sub = (struct google_api_HttpRule*)_upb_Message_New(&google__api__HttpRule_msg_init, arena);
    if (sub) google_api_set_http(msg, sub, arena);
  }
  return sub;
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
