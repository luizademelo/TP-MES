
#ifndef UDPA_ANNOTATIONS_SECURITY_PROTO_UPB_H__UPB_H_
#define UDPA_ANNOTATIONS_SECURITY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "udpa/annotations/security.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct udpa_annotations_FieldSecurityAnnotation { upb_Message UPB_PRIVATE(base); } udpa_annotations_FieldSecurityAnnotation;
struct google_protobuf_FieldOptions;

UPB_INLINE udpa_annotations_FieldSecurityAnnotation* udpa_annotations_FieldSecurityAnnotation_new(upb_Arena* arena) {
  return (udpa_annotations_FieldSecurityAnnotation*)_upb_Message_New(&udpa__annotations__FieldSecurityAnnotation_msg_init, arena);
}
UPB_INLINE udpa_annotations_FieldSecurityAnnotation* udpa_annotations_FieldSecurityAnnotation_parse(const char* buf, size_t size, upb_Arena* arena) {
  udpa_annotations_FieldSecurityAnnotation* ret = udpa_annotations_FieldSecurityAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &udpa__annotations__FieldSecurityAnnotation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE udpa_annotations_FieldSecurityAnnotation* udpa_annotations_FieldSecurityAnnotation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  udpa_annotations_FieldSecurityAnnotation* ret = udpa_annotations_FieldSecurityAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &udpa__annotations__FieldSecurityAnnotation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* udpa_annotations_FieldSecurityAnnotation_serialize(const udpa_annotations_FieldSecurityAnnotation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &udpa__annotations__FieldSecurityAnnotation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* udpa_annotations_FieldSecurityAnnotation_serialize_ex(const udpa_annotations_FieldSecurityAnnotation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &udpa__annotations__FieldSecurityAnnotation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void udpa_annotations_FieldSecurityAnnotation_clear_configure_for_untrusted_downstream(udpa_annotations_FieldSecurityAnnotation* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool udpa_annotations_FieldSecurityAnnotation_configure_for_untrusted_downstream(const udpa_annotations_FieldSecurityAnnotation* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void udpa_annotations_FieldSecurityAnnotation_clear_configure_for_untrusted_upstream(udpa_annotations_FieldSecurityAnnotation* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool udpa_annotations_FieldSecurityAnnotation_configure_for_untrusted_upstream(const udpa_annotations_FieldSecurityAnnotation* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void udpa_annotations_FieldSecurityAnnotation_set_configure_for_untrusted_downstream(udpa_annotations_FieldSecurityAnnotation *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void udpa_annotations_FieldSecurityAnnotation_set_configure_for_untrusted_upstream(udpa_annotations_FieldSecurityAnnotation *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE bool udpa_annotations_has_security(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &udpa_annotations_security_ext);
}
UPB_INLINE void udpa_annotations_clear_security(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &udpa_annotations_security_ext);
}
UPB_INLINE const udpa_annotations_FieldSecurityAnnotation* udpa_annotations_security(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &udpa_annotations_security_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const udpa_annotations_FieldSecurityAnnotation* default_val = NULL;
  const udpa_annotations_FieldSecurityAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void udpa_annotations_set_security(struct google_protobuf_FieldOptions* msg, const udpa_annotations_FieldSecurityAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &udpa_annotations_security_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct udpa_annotations_FieldSecurityAnnotation* udpa_annotations_mutable_security(struct google_protobuf_FieldOptions* msg,
                                    upb_Arena* arena) {
  struct udpa_annotations_FieldSecurityAnnotation* sub = (struct udpa_annotations_FieldSecurityAnnotation*)udpa_annotations_security(msg);
  if (sub == NULL) {
    sub = (struct udpa_annotations_FieldSecurityAnnotation*)_upb_Message_New(&udpa__annotations__FieldSecurityAnnotation_msg_init, arena);
    if (sub) udpa_annotations_set_security(msg, sub, arena);
  }
  return sub;
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
