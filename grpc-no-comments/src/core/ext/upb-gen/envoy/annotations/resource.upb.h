
#ifndef ENVOY_ANNOTATIONS_RESOURCE_PROTO_UPB_H__UPB_H_
#define ENVOY_ANNOTATIONS_RESOURCE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/annotations/resource.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_annotations_ResourceAnnotation { upb_Message UPB_PRIVATE(base); } envoy_annotations_ResourceAnnotation;
struct google_protobuf_ServiceOptions;

UPB_INLINE envoy_annotations_ResourceAnnotation* envoy_annotations_ResourceAnnotation_new(upb_Arena* arena) {
  return (envoy_annotations_ResourceAnnotation*)_upb_Message_New(&envoy__annotations__ResourceAnnotation_msg_init, arena);
}
UPB_INLINE envoy_annotations_ResourceAnnotation* envoy_annotations_ResourceAnnotation_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_annotations_ResourceAnnotation* ret = envoy_annotations_ResourceAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__annotations__ResourceAnnotation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_annotations_ResourceAnnotation* envoy_annotations_ResourceAnnotation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_annotations_ResourceAnnotation* ret = envoy_annotations_ResourceAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__annotations__ResourceAnnotation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_annotations_ResourceAnnotation_serialize(const envoy_annotations_ResourceAnnotation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__annotations__ResourceAnnotation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_annotations_ResourceAnnotation_serialize_ex(const envoy_annotations_ResourceAnnotation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__annotations__ResourceAnnotation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_annotations_ResourceAnnotation_clear_type(envoy_annotations_ResourceAnnotation* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_annotations_ResourceAnnotation_type(const envoy_annotations_ResourceAnnotation* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_annotations_ResourceAnnotation_set_type(envoy_annotations_ResourceAnnotation *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE bool envoy_annotations_has_resource(const struct google_protobuf_ServiceOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &envoy_annotations_resource_ext);
}
UPB_INLINE void envoy_annotations_clear_resource(struct google_protobuf_ServiceOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &envoy_annotations_resource_ext);
}
UPB_INLINE const envoy_annotations_ResourceAnnotation* envoy_annotations_resource(const struct google_protobuf_ServiceOptions* msg) {
  const upb_MiniTableExtension* ext = &envoy_annotations_resource_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const envoy_annotations_ResourceAnnotation* default_val = NULL;
  const envoy_annotations_ResourceAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_annotations_set_resource(struct google_protobuf_ServiceOptions* msg, const envoy_annotations_ResourceAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &envoy_annotations_resource_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct envoy_annotations_ResourceAnnotation* envoy_annotations_mutable_resource(struct google_protobuf_ServiceOptions* msg,
                                    upb_Arena* arena) {
  struct envoy_annotations_ResourceAnnotation* sub = (struct envoy_annotations_ResourceAnnotation*)envoy_annotations_resource(msg);
  if (sub == NULL) {
    sub = (struct envoy_annotations_ResourceAnnotation*)_upb_Message_New(&envoy__annotations__ResourceAnnotation_msg_init, arena);
    if (sub) envoy_annotations_set_resource(msg, sub, arena);
  }
  return sub;
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
