
#ifndef UDPA_ANNOTATIONS_STATUS_PROTO_UPB_H__UPB_H_
#define UDPA_ANNOTATIONS_STATUS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "udpa/annotations/status.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct udpa_annotations_StatusAnnotation { upb_Message UPB_PRIVATE(base); } udpa_annotations_StatusAnnotation;
struct google_protobuf_FileOptions;

typedef enum {
  udpa_annotations_UNKNOWN = 0,
  udpa_annotations_FROZEN = 1,
  udpa_annotations_ACTIVE = 2,
  udpa_annotations_NEXT_MAJOR_VERSION_CANDIDATE = 3
} udpa_annotations_PackageVersionStatus;

UPB_INLINE udpa_annotations_StatusAnnotation* udpa_annotations_StatusAnnotation_new(upb_Arena* arena) {
  return (udpa_annotations_StatusAnnotation*)_upb_Message_New(&udpa__annotations__StatusAnnotation_msg_init, arena);
}
UPB_INLINE udpa_annotations_StatusAnnotation* udpa_annotations_StatusAnnotation_parse(const char* buf, size_t size, upb_Arena* arena) {
  udpa_annotations_StatusAnnotation* ret = udpa_annotations_StatusAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &udpa__annotations__StatusAnnotation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE udpa_annotations_StatusAnnotation* udpa_annotations_StatusAnnotation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  udpa_annotations_StatusAnnotation* ret = udpa_annotations_StatusAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &udpa__annotations__StatusAnnotation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* udpa_annotations_StatusAnnotation_serialize(const udpa_annotations_StatusAnnotation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &udpa__annotations__StatusAnnotation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* udpa_annotations_StatusAnnotation_serialize_ex(const udpa_annotations_StatusAnnotation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &udpa__annotations__StatusAnnotation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void udpa_annotations_StatusAnnotation_clear_work_in_progress(udpa_annotations_StatusAnnotation* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool udpa_annotations_StatusAnnotation_work_in_progress(const udpa_annotations_StatusAnnotation* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void udpa_annotations_StatusAnnotation_clear_package_version_status(udpa_annotations_StatusAnnotation* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t udpa_annotations_StatusAnnotation_package_version_status(const udpa_annotations_StatusAnnotation* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void udpa_annotations_StatusAnnotation_set_work_in_progress(udpa_annotations_StatusAnnotation *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void udpa_annotations_StatusAnnotation_set_package_version_status(udpa_annotations_StatusAnnotation *msg, int32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE bool udpa_annotations_has_file_status(const struct google_protobuf_FileOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &udpa_annotations_file_status_ext);
}
UPB_INLINE void udpa_annotations_clear_file_status(struct google_protobuf_FileOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &udpa_annotations_file_status_ext);
}
UPB_INLINE const udpa_annotations_StatusAnnotation* udpa_annotations_file_status(const struct google_protobuf_FileOptions* msg) {
  const upb_MiniTableExtension* ext = &udpa_annotations_file_status_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const udpa_annotations_StatusAnnotation* default_val = NULL;
  const udpa_annotations_StatusAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void udpa_annotations_set_file_status(struct google_protobuf_FileOptions* msg, const udpa_annotations_StatusAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &udpa_annotations_file_status_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct udpa_annotations_StatusAnnotation* udpa_annotations_mutable_file_status(struct google_protobuf_FileOptions* msg,
                                    upb_Arena* arena) {
  struct udpa_annotations_StatusAnnotation* sub = (struct udpa_annotations_StatusAnnotation*)udpa_annotations_file_status(msg);
  if (sub == NULL) {
    sub = (struct udpa_annotations_StatusAnnotation*)_upb_Message_New(&udpa__annotations__StatusAnnotation_msg_init, arena);
    if (sub) udpa_annotations_set_file_status(msg, sub, arena);
  }
  return sub;
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
