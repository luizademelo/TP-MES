
#ifndef XDS_CORE_V3_COLLECTION_ENTRY_PROTO_UPB_H__UPB_H_
#define XDS_CORE_V3_COLLECTION_ENTRY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/core/v3/collection_entry.upb_minitable.h"

#include "google/protobuf/any.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/resource_locator.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_core_v3_CollectionEntry { upb_Message UPB_PRIVATE(base); } xds_core_v3_CollectionEntry;
typedef struct xds_core_v3_CollectionEntry_InlineEntry { upb_Message UPB_PRIVATE(base); } xds_core_v3_CollectionEntry_InlineEntry;
struct google_protobuf_Any;
struct xds_core_v3_ResourceLocator;

UPB_INLINE xds_core_v3_CollectionEntry* xds_core_v3_CollectionEntry_new(upb_Arena* arena) {
  return (xds_core_v3_CollectionEntry*)_upb_Message_New(&xds__core__v3__CollectionEntry_msg_init, arena);
}
UPB_INLINE xds_core_v3_CollectionEntry* xds_core_v3_CollectionEntry_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_CollectionEntry* ret = xds_core_v3_CollectionEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__CollectionEntry_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_CollectionEntry* xds_core_v3_CollectionEntry_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_CollectionEntry* ret = xds_core_v3_CollectionEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__CollectionEntry_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_CollectionEntry_serialize(const xds_core_v3_CollectionEntry* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__CollectionEntry_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_CollectionEntry_serialize_ex(const xds_core_v3_CollectionEntry* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__CollectionEntry_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  xds_core_v3_CollectionEntry_resource_specifier_locator = 1,
  xds_core_v3_CollectionEntry_resource_specifier_inline_entry = 2,
  xds_core_v3_CollectionEntry_resource_specifier_NOT_SET = 0
} xds_core_v3_CollectionEntry_resource_specifier_oneofcases;
UPB_INLINE xds_core_v3_CollectionEntry_resource_specifier_oneofcases xds_core_v3_CollectionEntry_resource_specifier_case(const xds_core_v3_CollectionEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_core_v3_CollectionEntry_resource_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_core_v3_CollectionEntry_clear_resource_specifier(xds_core_v3_CollectionEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &xds__core__v3__CollectionEntry_msg_init, &field);
}
UPB_INLINE void xds_core_v3_CollectionEntry_clear_locator(xds_core_v3_CollectionEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_core_v3_ResourceLocator* xds_core_v3_CollectionEntry_locator(const xds_core_v3_CollectionEntry* msg) {
  const struct xds_core_v3_ResourceLocator* default_val = NULL;
  const struct xds_core_v3_ResourceLocator* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_CollectionEntry_has_locator(const xds_core_v3_CollectionEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_core_v3_CollectionEntry_clear_inline_entry(xds_core_v3_CollectionEntry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_core_v3_CollectionEntry_InlineEntry* xds_core_v3_CollectionEntry_inline_entry(const xds_core_v3_CollectionEntry* msg) {
  const xds_core_v3_CollectionEntry_InlineEntry* default_val = NULL;
  const xds_core_v3_CollectionEntry_InlineEntry* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry__InlineEntry_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_CollectionEntry_has_inline_entry(const xds_core_v3_CollectionEntry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void xds_core_v3_CollectionEntry_set_locator(xds_core_v3_CollectionEntry *msg, struct xds_core_v3_ResourceLocator* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_ResourceLocator* xds_core_v3_CollectionEntry_mutable_locator(xds_core_v3_CollectionEntry* msg, upb_Arena* arena) {
  struct xds_core_v3_ResourceLocator* sub = (struct xds_core_v3_ResourceLocator*)xds_core_v3_CollectionEntry_locator(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_ResourceLocator*)_upb_Message_New(&xds__core__v3__ResourceLocator_msg_init, arena);
    if (sub) xds_core_v3_CollectionEntry_set_locator(msg, sub);
  }
  return sub;
}
UPB_INLINE void xds_core_v3_CollectionEntry_set_inline_entry(xds_core_v3_CollectionEntry *msg, xds_core_v3_CollectionEntry_InlineEntry* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry__InlineEntry_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_CollectionEntry_InlineEntry* xds_core_v3_CollectionEntry_mutable_inline_entry(xds_core_v3_CollectionEntry* msg, upb_Arena* arena) {
  struct xds_core_v3_CollectionEntry_InlineEntry* sub = (struct xds_core_v3_CollectionEntry_InlineEntry*)xds_core_v3_CollectionEntry_inline_entry(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_CollectionEntry_InlineEntry*)_upb_Message_New(&xds__core__v3__CollectionEntry__InlineEntry_msg_init, arena);
    if (sub) xds_core_v3_CollectionEntry_set_inline_entry(msg, sub);
  }
  return sub;
}

UPB_INLINE xds_core_v3_CollectionEntry_InlineEntry* xds_core_v3_CollectionEntry_InlineEntry_new(upb_Arena* arena) {
  return (xds_core_v3_CollectionEntry_InlineEntry*)_upb_Message_New(&xds__core__v3__CollectionEntry__InlineEntry_msg_init, arena);
}
UPB_INLINE xds_core_v3_CollectionEntry_InlineEntry* xds_core_v3_CollectionEntry_InlineEntry_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_CollectionEntry_InlineEntry* ret = xds_core_v3_CollectionEntry_InlineEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__CollectionEntry__InlineEntry_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_CollectionEntry_InlineEntry* xds_core_v3_CollectionEntry_InlineEntry_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_CollectionEntry_InlineEntry* ret = xds_core_v3_CollectionEntry_InlineEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__CollectionEntry__InlineEntry_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_CollectionEntry_InlineEntry_serialize(const xds_core_v3_CollectionEntry_InlineEntry* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__CollectionEntry__InlineEntry_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_CollectionEntry_InlineEntry_serialize_ex(const xds_core_v3_CollectionEntry_InlineEntry* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__CollectionEntry__InlineEntry_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_core_v3_CollectionEntry_InlineEntry_clear_name(xds_core_v3_CollectionEntry_InlineEntry* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_CollectionEntry_InlineEntry_name(const xds_core_v3_CollectionEntry_InlineEntry* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_CollectionEntry_InlineEntry_clear_version(xds_core_v3_CollectionEntry_InlineEntry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_CollectionEntry_InlineEntry_version(const xds_core_v3_CollectionEntry_InlineEntry* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_CollectionEntry_InlineEntry_clear_resource(xds_core_v3_CollectionEntry_InlineEntry* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* xds_core_v3_CollectionEntry_InlineEntry_resource(const xds_core_v3_CollectionEntry_InlineEntry* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_CollectionEntry_InlineEntry_has_resource(const xds_core_v3_CollectionEntry_InlineEntry* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void xds_core_v3_CollectionEntry_InlineEntry_set_name(xds_core_v3_CollectionEntry_InlineEntry *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_core_v3_CollectionEntry_InlineEntry_set_version(xds_core_v3_CollectionEntry_InlineEntry *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_core_v3_CollectionEntry_InlineEntry_set_resource(xds_core_v3_CollectionEntry_InlineEntry *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* xds_core_v3_CollectionEntry_InlineEntry_mutable_resource(xds_core_v3_CollectionEntry_InlineEntry* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)xds_core_v3_CollectionEntry_InlineEntry_resource(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) xds_core_v3_CollectionEntry_InlineEntry_set_resource(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
