
#ifndef XDS_ANNOTATIONS_V3_SENSITIVE_PROTO_UPB_H__UPB_H_
#define XDS_ANNOTATIONS_V3_SENSITIVE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/annotations/v3/sensitive.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

struct google_protobuf_FieldOptions;

UPB_INLINE bool xds_annotations_v3_has_sensitive(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &xds_annotations_v3_sensitive_ext);
}
UPB_INLINE void xds_annotations_v3_clear_sensitive(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &xds_annotations_v3_sensitive_ext);
}
UPB_INLINE bool xds_annotations_v3_sensitive(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_sensitive_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_set_sensitive(struct google_protobuf_FieldOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_sensitive_ext;
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
