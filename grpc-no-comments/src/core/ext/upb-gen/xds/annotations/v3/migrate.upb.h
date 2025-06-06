
#ifndef XDS_ANNOTATIONS_V3_MIGRATE_PROTO_UPB_H__UPB_H_
#define XDS_ANNOTATIONS_V3_MIGRATE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/annotations/v3/migrate.upb_minitable.h"

#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_annotations_v3_MigrateAnnotation { upb_Message UPB_PRIVATE(base); } xds_annotations_v3_MigrateAnnotation;
typedef struct xds_annotations_v3_FieldMigrateAnnotation { upb_Message UPB_PRIVATE(base); } xds_annotations_v3_FieldMigrateAnnotation;
typedef struct xds_annotations_v3_FileMigrateAnnotation { upb_Message UPB_PRIVATE(base); } xds_annotations_v3_FileMigrateAnnotation;
struct google_protobuf_EnumOptions;
struct google_protobuf_EnumValueOptions;
struct google_protobuf_FieldOptions;
struct google_protobuf_FileOptions;
struct google_protobuf_MessageOptions;

UPB_INLINE xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_MigrateAnnotation_new(upb_Arena* arena) {
  return (xds_annotations_v3_MigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__MigrateAnnotation_msg_init, arena);
}
UPB_INLINE xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_MigrateAnnotation_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_annotations_v3_MigrateAnnotation* ret = xds_annotations_v3_MigrateAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__annotations__v3__MigrateAnnotation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_MigrateAnnotation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_annotations_v3_MigrateAnnotation* ret = xds_annotations_v3_MigrateAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__annotations__v3__MigrateAnnotation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_annotations_v3_MigrateAnnotation_serialize(const xds_annotations_v3_MigrateAnnotation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__annotations__v3__MigrateAnnotation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_annotations_v3_MigrateAnnotation_serialize_ex(const xds_annotations_v3_MigrateAnnotation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__annotations__v3__MigrateAnnotation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_annotations_v3_MigrateAnnotation_clear_rename(xds_annotations_v3_MigrateAnnotation* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_annotations_v3_MigrateAnnotation_rename(const xds_annotations_v3_MigrateAnnotation* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_annotations_v3_MigrateAnnotation_set_rename(xds_annotations_v3_MigrateAnnotation *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE xds_annotations_v3_FieldMigrateAnnotation* xds_annotations_v3_FieldMigrateAnnotation_new(upb_Arena* arena) {
  return (xds_annotations_v3_FieldMigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__FieldMigrateAnnotation_msg_init, arena);
}
UPB_INLINE xds_annotations_v3_FieldMigrateAnnotation* xds_annotations_v3_FieldMigrateAnnotation_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_annotations_v3_FieldMigrateAnnotation* ret = xds_annotations_v3_FieldMigrateAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__annotations__v3__FieldMigrateAnnotation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_annotations_v3_FieldMigrateAnnotation* xds_annotations_v3_FieldMigrateAnnotation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_annotations_v3_FieldMigrateAnnotation* ret = xds_annotations_v3_FieldMigrateAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__annotations__v3__FieldMigrateAnnotation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_annotations_v3_FieldMigrateAnnotation_serialize(const xds_annotations_v3_FieldMigrateAnnotation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__annotations__v3__FieldMigrateAnnotation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_annotations_v3_FieldMigrateAnnotation_serialize_ex(const xds_annotations_v3_FieldMigrateAnnotation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__annotations__v3__FieldMigrateAnnotation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_annotations_v3_FieldMigrateAnnotation_clear_rename(xds_annotations_v3_FieldMigrateAnnotation* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_annotations_v3_FieldMigrateAnnotation_rename(const xds_annotations_v3_FieldMigrateAnnotation* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_FieldMigrateAnnotation_clear_oneof_promotion(xds_annotations_v3_FieldMigrateAnnotation* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_annotations_v3_FieldMigrateAnnotation_oneof_promotion(const xds_annotations_v3_FieldMigrateAnnotation* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_annotations_v3_FieldMigrateAnnotation_set_rename(xds_annotations_v3_FieldMigrateAnnotation *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_annotations_v3_FieldMigrateAnnotation_set_oneof_promotion(xds_annotations_v3_FieldMigrateAnnotation *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE xds_annotations_v3_FileMigrateAnnotation* xds_annotations_v3_FileMigrateAnnotation_new(upb_Arena* arena) {
  return (xds_annotations_v3_FileMigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__FileMigrateAnnotation_msg_init, arena);
}
UPB_INLINE xds_annotations_v3_FileMigrateAnnotation* xds_annotations_v3_FileMigrateAnnotation_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_annotations_v3_FileMigrateAnnotation* ret = xds_annotations_v3_FileMigrateAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__annotations__v3__FileMigrateAnnotation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_annotations_v3_FileMigrateAnnotation* xds_annotations_v3_FileMigrateAnnotation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_annotations_v3_FileMigrateAnnotation* ret = xds_annotations_v3_FileMigrateAnnotation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__annotations__v3__FileMigrateAnnotation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_annotations_v3_FileMigrateAnnotation_serialize(const xds_annotations_v3_FileMigrateAnnotation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__annotations__v3__FileMigrateAnnotation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_annotations_v3_FileMigrateAnnotation_serialize_ex(const xds_annotations_v3_FileMigrateAnnotation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__annotations__v3__FileMigrateAnnotation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_annotations_v3_FileMigrateAnnotation_clear_move_to_package(xds_annotations_v3_FileMigrateAnnotation* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_annotations_v3_FileMigrateAnnotation_move_to_package(const xds_annotations_v3_FileMigrateAnnotation* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_annotations_v3_FileMigrateAnnotation_set_move_to_package(xds_annotations_v3_FileMigrateAnnotation *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE bool xds_annotations_v3_has_message_migrate(const struct google_protobuf_MessageOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &xds_annotations_v3_message_migrate_ext);
}
UPB_INLINE void xds_annotations_v3_clear_message_migrate(struct google_protobuf_MessageOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &xds_annotations_v3_message_migrate_ext);
}
UPB_INLINE const xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_message_migrate(const struct google_protobuf_MessageOptions* msg) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_message_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const xds_annotations_v3_MigrateAnnotation* default_val = NULL;
  const xds_annotations_v3_MigrateAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_set_message_migrate(struct google_protobuf_MessageOptions* msg, const xds_annotations_v3_MigrateAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_message_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_mutable_message_migrate(struct google_protobuf_MessageOptions* msg,
                                    upb_Arena* arena) {
  struct xds_annotations_v3_MigrateAnnotation* sub = (struct xds_annotations_v3_MigrateAnnotation*)xds_annotations_v3_message_migrate(msg);
  if (sub == NULL) {
    sub = (struct xds_annotations_v3_MigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__MigrateAnnotation_msg_init, arena);
    if (sub) xds_annotations_v3_set_message_migrate(msg, sub, arena);
  }
  return sub;
}
UPB_INLINE bool xds_annotations_v3_has_field_migrate(const struct google_protobuf_FieldOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &xds_annotations_v3_field_migrate_ext);
}
UPB_INLINE void xds_annotations_v3_clear_field_migrate(struct google_protobuf_FieldOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &xds_annotations_v3_field_migrate_ext);
}
UPB_INLINE const xds_annotations_v3_FieldMigrateAnnotation* xds_annotations_v3_field_migrate(const struct google_protobuf_FieldOptions* msg) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_field_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const xds_annotations_v3_FieldMigrateAnnotation* default_val = NULL;
  const xds_annotations_v3_FieldMigrateAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_set_field_migrate(struct google_protobuf_FieldOptions* msg, const xds_annotations_v3_FieldMigrateAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_field_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct xds_annotations_v3_FieldMigrateAnnotation* xds_annotations_v3_mutable_field_migrate(struct google_protobuf_FieldOptions* msg,
                                    upb_Arena* arena) {
  struct xds_annotations_v3_FieldMigrateAnnotation* sub = (struct xds_annotations_v3_FieldMigrateAnnotation*)xds_annotations_v3_field_migrate(msg);
  if (sub == NULL) {
    sub = (struct xds_annotations_v3_FieldMigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__FieldMigrateAnnotation_msg_init, arena);
    if (sub) xds_annotations_v3_set_field_migrate(msg, sub, arena);
  }
  return sub;
}
UPB_INLINE bool xds_annotations_v3_has_enum_migrate(const struct google_protobuf_EnumOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &xds_annotations_v3_enum_migrate_ext);
}
UPB_INLINE void xds_annotations_v3_clear_enum_migrate(struct google_protobuf_EnumOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &xds_annotations_v3_enum_migrate_ext);
}
UPB_INLINE const xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_enum_migrate(const struct google_protobuf_EnumOptions* msg) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_enum_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const xds_annotations_v3_MigrateAnnotation* default_val = NULL;
  const xds_annotations_v3_MigrateAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_set_enum_migrate(struct google_protobuf_EnumOptions* msg, const xds_annotations_v3_MigrateAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_enum_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_mutable_enum_migrate(struct google_protobuf_EnumOptions* msg,
                                    upb_Arena* arena) {
  struct xds_annotations_v3_MigrateAnnotation* sub = (struct xds_annotations_v3_MigrateAnnotation*)xds_annotations_v3_enum_migrate(msg);
  if (sub == NULL) {
    sub = (struct xds_annotations_v3_MigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__MigrateAnnotation_msg_init, arena);
    if (sub) xds_annotations_v3_set_enum_migrate(msg, sub, arena);
  }
  return sub;
}
UPB_INLINE bool xds_annotations_v3_has_enum_value_migrate(const struct google_protobuf_EnumValueOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &xds_annotations_v3_enum_value_migrate_ext);
}
UPB_INLINE void xds_annotations_v3_clear_enum_value_migrate(struct google_protobuf_EnumValueOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &xds_annotations_v3_enum_value_migrate_ext);
}
UPB_INLINE const xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_enum_value_migrate(const struct google_protobuf_EnumValueOptions* msg) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_enum_value_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const xds_annotations_v3_MigrateAnnotation* default_val = NULL;
  const xds_annotations_v3_MigrateAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_set_enum_value_migrate(struct google_protobuf_EnumValueOptions* msg, const xds_annotations_v3_MigrateAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_enum_value_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct xds_annotations_v3_MigrateAnnotation* xds_annotations_v3_mutable_enum_value_migrate(struct google_protobuf_EnumValueOptions* msg,
                                    upb_Arena* arena) {
  struct xds_annotations_v3_MigrateAnnotation* sub = (struct xds_annotations_v3_MigrateAnnotation*)xds_annotations_v3_enum_value_migrate(msg);
  if (sub == NULL) {
    sub = (struct xds_annotations_v3_MigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__MigrateAnnotation_msg_init, arena);
    if (sub) xds_annotations_v3_set_enum_value_migrate(msg, sub, arena);
  }
  return sub;
}
UPB_INLINE bool xds_annotations_v3_has_file_migrate(const struct google_protobuf_FileOptions* msg) {
  return upb_Message_HasExtension((upb_Message*)msg, &xds_annotations_v3_file_migrate_ext);
}
UPB_INLINE void xds_annotations_v3_clear_file_migrate(struct google_protobuf_FileOptions* msg) {
  upb_Message_ClearExtension((upb_Message*)msg, &xds_annotations_v3_file_migrate_ext);
}
UPB_INLINE const xds_annotations_v3_FileMigrateAnnotation* xds_annotations_v3_file_migrate(const struct google_protobuf_FileOptions* msg) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_file_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  const xds_annotations_v3_FileMigrateAnnotation* default_val = NULL;
  const xds_annotations_v3_FileMigrateAnnotation* ret;
  _upb_Message_GetExtensionField((upb_Message*)msg, ext, &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_annotations_v3_set_file_migrate(struct google_protobuf_FileOptions* msg, const xds_annotations_v3_FileMigrateAnnotation* val, upb_Arena* arena) {
  const upb_MiniTableExtension* ext = &xds_annotations_v3_file_migrate_ext;
  UPB_ASSUME(upb_MiniTableField_IsScalar(&ext->UPB_PRIVATE(field)));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(
                 &ext->UPB_PRIVATE(field)) == UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  bool ok = upb_Message_SetExtension((upb_Message*)msg, ext, &val, arena);
  UPB_ASSERT(ok);
}
UPB_INLINE struct xds_annotations_v3_FileMigrateAnnotation* xds_annotations_v3_mutable_file_migrate(struct google_protobuf_FileOptions* msg,
                                    upb_Arena* arena) {
  struct xds_annotations_v3_FileMigrateAnnotation* sub = (struct xds_annotations_v3_FileMigrateAnnotation*)xds_annotations_v3_file_migrate(msg);
  if (sub == NULL) {
    sub = (struct xds_annotations_v3_FileMigrateAnnotation*)_upb_Message_New(&xds__annotations__v3__FileMigrateAnnotation_msg_init, arena);
    if (sub) xds_annotations_v3_set_file_migrate(msg, sub, arena);
  }
  return sub;
}
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
