
#ifndef UDPA_ANNOTATIONS_SENSITIVE_PROTO_UPB_H__UPB_H_
#define UDPA_ANNOTATIONS_SENSITIVE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "udpa/annotations/sensitive.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

struct google_protobuf_FieldOptions;

UPB_INLINE bool udpa_annotations_has_sensitive(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &udpa_annotations_sensitive_ext);
}
UPB_INLINE void udpa_annotations_clear_sensitive(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &udpa_annotations_sensitive_ext);
}
UPB_INLINE bool udpa_annotations_sensitive(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &udpa_annotations_sensitive_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void udpa_annotations_set_sensitive(struct google_protobuf_FieldOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &udpa_annotations_sensitive_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
