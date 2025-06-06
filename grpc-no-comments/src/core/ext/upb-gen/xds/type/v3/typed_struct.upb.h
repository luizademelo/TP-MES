
#ifndef XDS_TYPE_V3_TYPED_STRUCT_PROTO_UPB_H__UPB_H_
#define XDS_TYPE_V3_TYPED_STRUCT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/type/v3/typed_struct.upb_minitable.h"

#include "google/protobuf/struct.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_type_v3_TypedStruct { upb_Message UPB_PRIVATE(base); } xds_type_v3_TypedStruct;
struct google_protobuf_Struct;

UPB_INLINE xds_type_v3_TypedStruct* xds_type_v3_TypedStruct_new(upb_Arena* arena) {
  return (xds_type_v3_TypedStruct*)_upb_Message_New(&xds__type__v3__TypedStruct_msg_init, arena);
}
UPB_INLINE xds_type_v3_TypedStruct* xds_type_v3_TypedStruct_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_v3_TypedStruct* ret = xds_type_v3_TypedStruct_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__TypedStruct_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_v3_TypedStruct* xds_type_v3_TypedStruct_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_v3_TypedStruct* ret = xds_type_v3_TypedStruct_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__TypedStruct_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_v3_TypedStruct_serialize(const xds_type_v3_TypedStruct* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__TypedStruct_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_v3_TypedStruct_serialize_ex(const xds_type_v3_TypedStruct* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__TypedStruct_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_v3_TypedStruct_clear_type_url(xds_type_v3_TypedStruct* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_type_v3_TypedStruct_type_url(const xds_type_v3_TypedStruct* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_type_v3_TypedStruct_clear_value(xds_type_v3_TypedStruct* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* xds_type_v3_TypedStruct_value(const xds_type_v3_TypedStruct* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_v3_TypedStruct_has_value(const xds_type_v3_TypedStruct* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void xds_type_v3_TypedStruct_set_type_url(xds_type_v3_TypedStruct *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_type_v3_TypedStruct_set_value(xds_type_v3_TypedStruct *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* xds_type_v3_TypedStruct_mutable_value(xds_type_v3_TypedStruct* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)xds_type_v3_TypedStruct_value(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) xds_type_v3_TypedStruct_set_value(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
