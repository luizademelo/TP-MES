
#ifndef XDS_TYPE_V3_CEL_PROTO_UPB_H__UPB_H_
#define XDS_TYPE_V3_CEL_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/type/v3/cel.upb_minitable.h"

#include "google/api/expr/v1alpha1/checked.upb_minitable.h"
#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_type_v3_CelExpression { upb_Message UPB_PRIVATE(base); } xds_type_v3_CelExpression;
typedef struct xds_type_v3_CelExtractString { upb_Message UPB_PRIVATE(base); } xds_type_v3_CelExtractString;
struct google_api_expr_v1alpha1_CheckedExpr;
struct google_api_expr_v1alpha1_ParsedExpr;
struct google_protobuf_StringValue;

UPB_INLINE xds_type_v3_CelExpression* xds_type_v3_CelExpression_new(upb_Arena* arena) {
  return (xds_type_v3_CelExpression*)_upb_Message_New(&xds__type__v3__CelExpression_msg_init, arena);
}
UPB_INLINE xds_type_v3_CelExpression* xds_type_v3_CelExpression_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_v3_CelExpression* ret = xds_type_v3_CelExpression_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__CelExpression_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_v3_CelExpression* xds_type_v3_CelExpression_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_v3_CelExpression* ret = xds_type_v3_CelExpression_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__CelExpression_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_v3_CelExpression_serialize(const xds_type_v3_CelExpression* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__CelExpression_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_v3_CelExpression_serialize_ex(const xds_type_v3_CelExpression* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__CelExpression_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  xds_type_v3_CelExpression_expr_specifier_parsed_expr = 1,
  xds_type_v3_CelExpression_expr_specifier_checked_expr = 2,
  xds_type_v3_CelExpression_expr_specifier_NOT_SET = 0
} xds_type_v3_CelExpression_expr_specifier_oneofcases;
UPB_INLINE xds_type_v3_CelExpression_expr_specifier_oneofcases xds_type_v3_CelExpression_expr_specifier_case(const xds_type_v3_CelExpression* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_type_v3_CelExpression_expr_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_type_v3_CelExpression_clear_expr_specifier(xds_type_v3_CelExpression* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &xds__type__v3__CelExpression_msg_init, &field);
}
UPB_INLINE void xds_type_v3_CelExpression_clear_parsed_expr(xds_type_v3_CelExpression* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_ParsedExpr* xds_type_v3_CelExpression_parsed_expr(const xds_type_v3_CelExpression* msg) {
  const struct google_api_expr_v1alpha1_ParsedExpr* default_val = NULL;
  const struct google_api_expr_v1alpha1_ParsedExpr* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__ParsedExpr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_v3_CelExpression_has_parsed_expr(const xds_type_v3_CelExpression* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_type_v3_CelExpression_clear_checked_expr(xds_type_v3_CelExpression* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_CheckedExpr* xds_type_v3_CelExpression_checked_expr(const xds_type_v3_CelExpression* msg) {
  const struct google_api_expr_v1alpha1_CheckedExpr* default_val = NULL;
  const struct google_api_expr_v1alpha1_CheckedExpr* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_v3_CelExpression_has_checked_expr(const xds_type_v3_CelExpression* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void xds_type_v3_CelExpression_set_parsed_expr(xds_type_v3_CelExpression *msg, struct google_api_expr_v1alpha1_ParsedExpr* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__ParsedExpr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_ParsedExpr* xds_type_v3_CelExpression_mutable_parsed_expr(xds_type_v3_CelExpression* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_ParsedExpr* sub = (struct google_api_expr_v1alpha1_ParsedExpr*)xds_type_v3_CelExpression_parsed_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_ParsedExpr*)_upb_Message_New(&google__api__expr__v1alpha1__ParsedExpr_msg_init, arena);
    if (sub) xds_type_v3_CelExpression_set_parsed_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void xds_type_v3_CelExpression_set_checked_expr(xds_type_v3_CelExpression *msg, struct google_api_expr_v1alpha1_CheckedExpr* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_CheckedExpr* xds_type_v3_CelExpression_mutable_checked_expr(xds_type_v3_CelExpression* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_CheckedExpr* sub = (struct google_api_expr_v1alpha1_CheckedExpr*)xds_type_v3_CelExpression_checked_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_CheckedExpr*)_upb_Message_New(&google__api__expr__v1alpha1__CheckedExpr_msg_init, arena);
    if (sub) xds_type_v3_CelExpression_set_checked_expr(msg, sub);
  }
  return sub;
}

UPB_INLINE xds_type_v3_CelExtractString* xds_type_v3_CelExtractString_new(upb_Arena* arena) {
  return (xds_type_v3_CelExtractString*)_upb_Message_New(&xds__type__v3__CelExtractString_msg_init, arena);
}
UPB_INLINE xds_type_v3_CelExtractString* xds_type_v3_CelExtractString_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_v3_CelExtractString* ret = xds_type_v3_CelExtractString_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__CelExtractString_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_v3_CelExtractString* xds_type_v3_CelExtractString_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_v3_CelExtractString* ret = xds_type_v3_CelExtractString_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__CelExtractString_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_v3_CelExtractString_serialize(const xds_type_v3_CelExtractString* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__CelExtractString_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_v3_CelExtractString_serialize_ex(const xds_type_v3_CelExtractString* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__CelExtractString_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_v3_CelExtractString_clear_expr_extract(xds_type_v3_CelExtractString* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_type_v3_CelExpression* xds_type_v3_CelExtractString_expr_extract(const xds_type_v3_CelExtractString* msg) {
  const xds_type_v3_CelExpression* default_val = NULL;
  const xds_type_v3_CelExpression* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__CelExpression_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_v3_CelExtractString_has_expr_extract(const xds_type_v3_CelExtractString* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_type_v3_CelExtractString_clear_default_value(xds_type_v3_CelExtractString* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_StringValue* xds_type_v3_CelExtractString_default_value(const xds_type_v3_CelExtractString* msg) {
  const struct google_protobuf_StringValue* default_val = NULL;
  const struct google_protobuf_StringValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__StringValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_v3_CelExtractString_has_default_value(const xds_type_v3_CelExtractString* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void xds_type_v3_CelExtractString_set_expr_extract(xds_type_v3_CelExtractString *msg, xds_type_v3_CelExpression* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__CelExpression_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_v3_CelExpression* xds_type_v3_CelExtractString_mutable_expr_extract(xds_type_v3_CelExtractString* msg, upb_Arena* arena) {
  struct xds_type_v3_CelExpression* sub = (struct xds_type_v3_CelExpression*)xds_type_v3_CelExtractString_expr_extract(msg);
  if (sub == NULL) {
    sub = (struct xds_type_v3_CelExpression*)_upb_Message_New(&xds__type__v3__CelExpression_msg_init, arena);
    if (sub) xds_type_v3_CelExtractString_set_expr_extract(msg, sub);
  }
  return sub;
}
UPB_INLINE void xds_type_v3_CelExtractString_set_default_value(xds_type_v3_CelExtractString *msg, struct google_protobuf_StringValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__StringValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_StringValue* xds_type_v3_CelExtractString_mutable_default_value(xds_type_v3_CelExtractString* msg, upb_Arena* arena) {
  struct google_protobuf_StringValue* sub = (struct google_protobuf_StringValue*)xds_type_v3_CelExtractString_default_value(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_StringValue*)_upb_Message_New(&google__protobuf__StringValue_msg_init, arena);
    if (sub) xds_type_v3_CelExtractString_set_default_value(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
