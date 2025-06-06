
#ifndef ENVOY_ANNOTATIONS_DEPRECATION_PROTO_UPB_H__UPB_H_
#define ENVOY_ANNOTATIONS_DEPRECATION_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/annotations/deprecation.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

struct google_protobuf_EnumValueOptions;
struct google_protobuf_FieldOptions;

UPB_INLINE bool envoy_annotations_has_disallowed_by_default(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &envoy_annotations_disallowed_by_default_ext);
}
UPB_INLINE void envoy_annotations_clear_disallowed_by_default(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &envoy_annotations_disallowed_by_default_ext);
}
UPB_INLINE bool envoy_annotations_disallowed_by_default(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &envoy_annotations_disallowed_by_default_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_annotations_set_disallowed_by_default(struct google_protobuf_FieldOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &envoy_annotations_disallowed_by_default_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE bool envoy_annotations_has_deprecated_at_minor_version(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &envoy_annotations_deprecated_at_minor_version_ext);
}
UPB_INLINE void envoy_annotations_clear_deprecated_at_minor_version(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &envoy_annotations_deprecated_at_minor_version_ext);
}
UPB_INLINE upb_StringView envoy_annotations_deprecated_at_minor_version(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &envoy_annotations_deprecated_at_minor_version_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_StringView);
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_annotations_set_deprecated_at_minor_version(struct google_protobuf_FieldOptions* msg, upb_StringView val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &envoy_annotations_deprecated_at_minor_version_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_StringView);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE bool envoy_annotations_has_disallowed_by_default_enum(const struct google_protobuf_EnumValueOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &envoy_annotations_disallowed_by_default_enum_ext);
}
UPB_INLINE void envoy_annotations_clear_disallowed_by_default_enum(struct google_protobuf_EnumValueOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &envoy_annotations_disallowed_by_default_enum_ext);
}
UPB_INLINE bool envoy_annotations_disallowed_by_default_enum(const struct google_protobuf_EnumValueOptions* msg) {
  const upb_MiniTableExtension* ext = &envoy_annotations_disallowed_by_default_enum_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool default_val = false;
  bool ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_annotations_set_disallowed_by_default_enum(struct google_protobuf_EnumValueOptions* msg, bool val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &envoy_annotations_disallowed_by_default_enum_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_1Byte);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE bool envoy_annotations_has_deprecated_at_minor_version_enum(const struct google_protobuf_EnumValueOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &envoy_annotations_deprecated_at_minor_version_enum_ext);
}
UPB_INLINE void envoy_annotations_clear_deprecated_at_minor_version_enum(struct google_protobuf_EnumValueOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &envoy_annotations_deprecated_at_minor_version_enum_ext);
}
UPB_INLINE upb_StringView envoy_annotations_deprecated_at_minor_version_enum(const struct google_protobuf_EnumValueOptions* msg) {
  const upb_MiniTableExtension* ext = &envoy_annotations_deprecated_at_minor_version_enum_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_StringView);
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_annotations_set_deprecated_at_minor_version_enum(struct google_protobuf_EnumValueOptions* msg, upb_StringView val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &envoy_annotations_deprecated_at_minor_version_enum_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == kUpb_FieldRep_StringView);
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
