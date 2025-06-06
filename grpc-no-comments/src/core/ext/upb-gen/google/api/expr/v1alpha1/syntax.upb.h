
#ifndef GOOGLE_API_EXPR_V1ALPHA1_SYNTAX_PROTO_UPB_H__UPB_H_
#define GOOGLE_API_EXPR_V1ALPHA1_SYNTAX_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct google_api_expr_v1alpha1_ParsedExpr { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_ParsedExpr;
typedef struct google_api_expr_v1alpha1_Expr { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr;
typedef struct google_api_expr_v1alpha1_Expr_Ident { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_Ident;
typedef struct google_api_expr_v1alpha1_Expr_Select { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_Select;
typedef struct google_api_expr_v1alpha1_Expr_Call { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_Call;
typedef struct google_api_expr_v1alpha1_Expr_CreateList { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_CreateList;
typedef struct google_api_expr_v1alpha1_Expr_CreateStruct { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_CreateStruct;
typedef struct google_api_expr_v1alpha1_Expr_CreateStruct_Entry { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_CreateStruct_Entry;
typedef struct google_api_expr_v1alpha1_Expr_Comprehension { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Expr_Comprehension;
typedef struct google_api_expr_v1alpha1_Constant { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Constant;
typedef struct google_api_expr_v1alpha1_SourceInfo { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_SourceInfo;
typedef struct google_api_expr_v1alpha1_SourceInfo_Extension { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_SourceInfo_Extension;
typedef struct google_api_expr_v1alpha1_SourceInfo_Extension_Version { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_SourceInfo_Extension_Version;
typedef struct google_api_expr_v1alpha1_SourcePosition { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_SourcePosition;
struct google_protobuf_Duration;
struct google_protobuf_Timestamp;

typedef enum {
  google_api_expr_v1alpha1_SourceInfo_Extension_COMPONENT_UNSPECIFIED = 0,
  google_api_expr_v1alpha1_SourceInfo_Extension_COMPONENT_PARSER = 1,
  google_api_expr_v1alpha1_SourceInfo_Extension_COMPONENT_TYPE_CHECKER = 2,
  google_api_expr_v1alpha1_SourceInfo_Extension_COMPONENT_RUNTIME = 3
} google_api_expr_v1alpha1_SourceInfo_Extension_Component;

UPB_INLINE google_api_expr_v1alpha1_ParsedExpr* google_api_expr_v1alpha1_ParsedExpr_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_ParsedExpr*)_upb_Message_New(&google__api__expr__v1alpha1__ParsedExpr_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_ParsedExpr* google_api_expr_v1alpha1_ParsedExpr_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_ParsedExpr* ret = google_api_expr_v1alpha1_ParsedExpr_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__ParsedExpr_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_ParsedExpr* google_api_expr_v1alpha1_ParsedExpr_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_ParsedExpr* ret = google_api_expr_v1alpha1_ParsedExpr_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__ParsedExpr_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_ParsedExpr_serialize(const google_api_expr_v1alpha1_ParsedExpr* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__ParsedExpr_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_ParsedExpr_serialize_ex(const google_api_expr_v1alpha1_ParsedExpr* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__ParsedExpr_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_ParsedExpr_clear_expr(google_api_expr_v1alpha1_ParsedExpr* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_ParsedExpr_expr(const google_api_expr_v1alpha1_ParsedExpr* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_ParsedExpr_has_expr(const google_api_expr_v1alpha1_ParsedExpr* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_ParsedExpr_clear_source_info(google_api_expr_v1alpha1_ParsedExpr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_ParsedExpr_source_info(const google_api_expr_v1alpha1_ParsedExpr* msg) {
  const google_api_expr_v1alpha1_SourceInfo* default_val = NULL;
  const google_api_expr_v1alpha1_SourceInfo* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_ParsedExpr_has_source_info(const google_api_expr_v1alpha1_ParsedExpr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_ParsedExpr_set_expr(google_api_expr_v1alpha1_ParsedExpr *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_ParsedExpr_mutable_expr(google_api_expr_v1alpha1_ParsedExpr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_ParsedExpr_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_ParsedExpr_set_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_ParsedExpr_set_source_info(google_api_expr_v1alpha1_ParsedExpr *msg, google_api_expr_v1alpha1_SourceInfo* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_ParsedExpr_mutable_source_info(google_api_expr_v1alpha1_ParsedExpr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_SourceInfo* sub = (struct google_api_expr_v1alpha1_SourceInfo*)google_api_expr_v1alpha1_ParsedExpr_source_info(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_SourceInfo*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_ParsedExpr_set_source_info(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr* ret = google_api_expr_v1alpha1_Expr_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr* ret = google_api_expr_v1alpha1_Expr_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_serialize(const google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_serialize_ex(const google_api_expr_v1alpha1_Expr* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  google_api_expr_v1alpha1_Expr_expr_kind_const_expr = 3,
  google_api_expr_v1alpha1_Expr_expr_kind_ident_expr = 4,
  google_api_expr_v1alpha1_Expr_expr_kind_select_expr = 5,
  google_api_expr_v1alpha1_Expr_expr_kind_call_expr = 6,
  google_api_expr_v1alpha1_Expr_expr_kind_list_expr = 7,
  google_api_expr_v1alpha1_Expr_expr_kind_struct_expr = 8,
  google_api_expr_v1alpha1_Expr_expr_kind_comprehension_expr = 9,
  google_api_expr_v1alpha1_Expr_expr_kind_NOT_SET = 0
} google_api_expr_v1alpha1_Expr_expr_kind_oneofcases;
UPB_INLINE google_api_expr_v1alpha1_Expr_expr_kind_oneofcases google_api_expr_v1alpha1_Expr_expr_kind_case(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 24), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Expr_expr_kind_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_expr_kind(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 24), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr_msg_init, &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_id(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_api_expr_v1alpha1_Expr_id(const google_api_expr_v1alpha1_Expr* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_const_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 24), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Expr_const_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Constant* default_val = NULL;
  const google_api_expr_v1alpha1_Constant* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 24), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Constant_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_const_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 24), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_ident_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 24), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_Ident* google_api_expr_v1alpha1_Expr_ident_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Expr_Ident* default_val = NULL;
  const google_api_expr_v1alpha1_Expr_Ident* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 24), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Ident_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_ident_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 24), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_select_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 24), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_Select* google_api_expr_v1alpha1_Expr_select_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Expr_Select* default_val = NULL;
  const google_api_expr_v1alpha1_Expr_Select* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 24), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Select_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_select_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 24), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_call_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 24), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_Call* google_api_expr_v1alpha1_Expr_call_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Expr_Call* default_val = NULL;
  const google_api_expr_v1alpha1_Expr_Call* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 24), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Call_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_call_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 24), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_list_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 24), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_CreateList* google_api_expr_v1alpha1_Expr_list_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Expr_CreateList* default_val = NULL;
  const google_api_expr_v1alpha1_Expr_CreateList* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 24), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateList_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_list_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 24), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_struct_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 24), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_CreateStruct* google_api_expr_v1alpha1_Expr_struct_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Expr_CreateStruct* default_val = NULL;
  const google_api_expr_v1alpha1_Expr_CreateStruct* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 24), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_struct_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 24), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_clear_comprehension_expr(google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 24), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_Comprehension* google_api_expr_v1alpha1_Expr_comprehension_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const google_api_expr_v1alpha1_Expr_Comprehension* default_val = NULL;
  const google_api_expr_v1alpha1_Expr_Comprehension* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 24), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Comprehension_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_has_comprehension_expr(const google_api_expr_v1alpha1_Expr* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 24), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_set_id(google_api_expr_v1alpha1_Expr *msg, int64_t value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_const_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Constant* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 24), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Constant_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Expr_mutable_const_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Constant* sub = (struct google_api_expr_v1alpha1_Constant*)google_api_expr_v1alpha1_Expr_const_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Constant*)_upb_Message_New(&google__api__expr__v1alpha1__Constant_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_const_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_ident_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Expr_Ident* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 24), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Ident_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_Ident* google_api_expr_v1alpha1_Expr_mutable_ident_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr_Ident* sub = (struct google_api_expr_v1alpha1_Expr_Ident*)google_api_expr_v1alpha1_Expr_ident_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr_Ident*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Ident_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_ident_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_select_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Expr_Select* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 24), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Select_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_Select* google_api_expr_v1alpha1_Expr_mutable_select_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr_Select* sub = (struct google_api_expr_v1alpha1_Expr_Select*)google_api_expr_v1alpha1_Expr_select_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr_Select*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Select_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_select_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_call_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Expr_Call* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 24), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Call_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_Call* google_api_expr_v1alpha1_Expr_mutable_call_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr_Call* sub = (struct google_api_expr_v1alpha1_Expr_Call*)google_api_expr_v1alpha1_Expr_call_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr_Call*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Call_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_call_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_list_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Expr_CreateList* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 24), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateList_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_CreateList* google_api_expr_v1alpha1_Expr_mutable_list_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr_CreateList* sub = (struct google_api_expr_v1alpha1_Expr_CreateList*)google_api_expr_v1alpha1_Expr_list_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr_CreateList*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__CreateList_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_list_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_struct_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Expr_CreateStruct* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 24), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_CreateStruct* google_api_expr_v1alpha1_Expr_mutable_struct_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr_CreateStruct* sub = (struct google_api_expr_v1alpha1_Expr_CreateStruct*)google_api_expr_v1alpha1_Expr_struct_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr_CreateStruct*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__CreateStruct_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_struct_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_set_comprehension_expr(google_api_expr_v1alpha1_Expr *msg, google_api_expr_v1alpha1_Expr_Comprehension* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 24), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__Comprehension_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_Comprehension* google_api_expr_v1alpha1_Expr_mutable_comprehension_expr(google_api_expr_v1alpha1_Expr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr_Comprehension* sub = (struct google_api_expr_v1alpha1_Expr_Comprehension*)google_api_expr_v1alpha1_Expr_comprehension_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr_Comprehension*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Comprehension_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_set_comprehension_expr(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Expr_Ident* google_api_expr_v1alpha1_Expr_Ident_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_Ident*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Ident_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Ident* google_api_expr_v1alpha1_Expr_Ident_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Ident* ret = google_api_expr_v1alpha1_Expr_Ident_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Ident_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Ident* google_api_expr_v1alpha1_Expr_Ident_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Ident* ret = google_api_expr_v1alpha1_Expr_Ident_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Ident_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Ident_serialize(const google_api_expr_v1alpha1_Expr_Ident* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Ident_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Ident_serialize_ex(const google_api_expr_v1alpha1_Expr_Ident* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Ident_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Ident_clear_name(google_api_expr_v1alpha1_Expr_Ident* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_Ident_name(const google_api_expr_v1alpha1_Expr_Ident* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_Ident_set_name(google_api_expr_v1alpha1_Expr_Ident *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Expr_Select* google_api_expr_v1alpha1_Expr_Select_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_Select*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Select_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Select* google_api_expr_v1alpha1_Expr_Select_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Select* ret = google_api_expr_v1alpha1_Expr_Select_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Select_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Select* google_api_expr_v1alpha1_Expr_Select_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Select* ret = google_api_expr_v1alpha1_Expr_Select_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Select_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Select_serialize(const google_api_expr_v1alpha1_Expr_Select* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Select_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Select_serialize_ex(const google_api_expr_v1alpha1_Expr_Select* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Select_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Select_clear_operand(google_api_expr_v1alpha1_Expr_Select* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Select_operand(const google_api_expr_v1alpha1_Expr_Select* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Select_has_operand(const google_api_expr_v1alpha1_Expr_Select* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Select_clear_field(google_api_expr_v1alpha1_Expr_Select* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_Select_field(const google_api_expr_v1alpha1_Expr_Select* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Select_clear_test_only(google_api_expr_v1alpha1_Expr_Select* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Select_test_only(const google_api_expr_v1alpha1_Expr_Select* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_Select_set_operand(google_api_expr_v1alpha1_Expr_Select *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Select_mutable_operand(google_api_expr_v1alpha1_Expr_Select* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Select_operand(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Select_set_operand(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Select_set_field(google_api_expr_v1alpha1_Expr_Select *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Select_set_test_only(google_api_expr_v1alpha1_Expr_Select *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Expr_Call* google_api_expr_v1alpha1_Expr_Call_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_Call*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Call_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Call* google_api_expr_v1alpha1_Expr_Call_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Call* ret = google_api_expr_v1alpha1_Expr_Call_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Call_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Call* google_api_expr_v1alpha1_Expr_Call_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Call* ret = google_api_expr_v1alpha1_Expr_Call_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Call_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Call_serialize(const google_api_expr_v1alpha1_Expr_Call* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Call_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Call_serialize_ex(const google_api_expr_v1alpha1_Expr_Call* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Call_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Call_clear_target(google_api_expr_v1alpha1_Expr_Call* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Call_target(const google_api_expr_v1alpha1_Expr_Call* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Call_has_target(const google_api_expr_v1alpha1_Expr_Call* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Call_clear_function(google_api_expr_v1alpha1_Expr_Call* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_Call_function(const google_api_expr_v1alpha1_Expr_Call* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Call_clear_args(google_api_expr_v1alpha1_Expr_Call* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* const* google_api_expr_v1alpha1_Expr_Call_args(const google_api_expr_v1alpha1_Expr_Call* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Expr* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Expr_Call_args_upb_array(const google_api_expr_v1alpha1_Expr_Call* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Expr_Call_args_mutable_upb_array(google_api_expr_v1alpha1_Expr_Call* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_Call_set_target(google_api_expr_v1alpha1_Expr_Call *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Call_mutable_target(google_api_expr_v1alpha1_Expr_Call* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Call_target(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Call_set_target(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Call_set_function(google_api_expr_v1alpha1_Expr_Call *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE google_api_expr_v1alpha1_Expr** google_api_expr_v1alpha1_Expr_Call_mutable_args(google_api_expr_v1alpha1_Expr_Call* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Expr**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Expr** google_api_expr_v1alpha1_Expr_Call_resize_args(google_api_expr_v1alpha1_Expr_Call* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Expr**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Call_add_args(google_api_expr_v1alpha1_Expr_Call* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Expr_CreateList* google_api_expr_v1alpha1_Expr_CreateList_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_CreateList*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__CreateList_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateList* google_api_expr_v1alpha1_Expr_CreateList_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_CreateList* ret = google_api_expr_v1alpha1_Expr_CreateList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__CreateList_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateList* google_api_expr_v1alpha1_Expr_CreateList_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_CreateList* ret = google_api_expr_v1alpha1_Expr_CreateList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__CreateList_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_CreateList_serialize(const google_api_expr_v1alpha1_Expr_CreateList* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateList_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_CreateList_serialize_ex(const google_api_expr_v1alpha1_Expr_CreateList* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateList_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateList_clear_elements(google_api_expr_v1alpha1_Expr_CreateList* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* const* google_api_expr_v1alpha1_Expr_CreateList_elements(const google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Expr* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Expr_CreateList_elements_upb_array(const google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Expr_CreateList_elements_mutable_upb_array(google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateList_clear_optional_indices(google_api_expr_v1alpha1_Expr_CreateList* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* google_api_expr_v1alpha1_Expr_CreateList_optional_indices(const google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Expr_CreateList_optional_indices_upb_array(const google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Expr_CreateList_optional_indices_mutable_upb_array(google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE google_api_expr_v1alpha1_Expr** google_api_expr_v1alpha1_Expr_CreateList_mutable_elements(google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Expr**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Expr** google_api_expr_v1alpha1_Expr_CreateList_resize_elements(google_api_expr_v1alpha1_Expr_CreateList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Expr**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_CreateList_add_elements(google_api_expr_v1alpha1_Expr_CreateList* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE int32_t* google_api_expr_v1alpha1_Expr_CreateList_mutable_optional_indices(google_api_expr_v1alpha1_Expr_CreateList* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* google_api_expr_v1alpha1_Expr_CreateList_resize_optional_indices(google_api_expr_v1alpha1_Expr_CreateList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_CreateList_add_optional_indices(google_api_expr_v1alpha1_Expr_CreateList* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}

UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct* google_api_expr_v1alpha1_Expr_CreateStruct_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_CreateStruct*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__CreateStruct_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct* google_api_expr_v1alpha1_Expr_CreateStruct_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_CreateStruct* ret = google_api_expr_v1alpha1_Expr_CreateStruct_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__CreateStruct_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct* google_api_expr_v1alpha1_Expr_CreateStruct_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_CreateStruct* ret = google_api_expr_v1alpha1_Expr_CreateStruct_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__CreateStruct_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_CreateStruct_serialize(const google_api_expr_v1alpha1_Expr_CreateStruct* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateStruct_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_CreateStruct_serialize_ex(const google_api_expr_v1alpha1_Expr_CreateStruct* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateStruct_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_clear_message_name(google_api_expr_v1alpha1_Expr_CreateStruct* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_CreateStruct_message_name(const google_api_expr_v1alpha1_Expr_CreateStruct* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_clear_entries(google_api_expr_v1alpha1_Expr_CreateStruct* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* const* google_api_expr_v1alpha1_Expr_CreateStruct_entries(const google_api_expr_v1alpha1_Expr_CreateStruct* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Expr_CreateStruct_entries_upb_array(const google_api_expr_v1alpha1_Expr_CreateStruct* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Expr_CreateStruct_entries_mutable_upb_array(google_api_expr_v1alpha1_Expr_CreateStruct* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_set_message_name(google_api_expr_v1alpha1_Expr_CreateStruct *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct_Entry** google_api_expr_v1alpha1_Expr_CreateStruct_mutable_entries(google_api_expr_v1alpha1_Expr_CreateStruct* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Expr_CreateStruct_Entry**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct_Entry** google_api_expr_v1alpha1_Expr_CreateStruct_resize_entries(google_api_expr_v1alpha1_Expr_CreateStruct* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Expr_CreateStruct_Entry**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr_CreateStruct_Entry* google_api_expr_v1alpha1_Expr_CreateStruct_add_entries(google_api_expr_v1alpha1_Expr_CreateStruct* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Expr_CreateStruct_Entry* sub = (struct google_api_expr_v1alpha1_Expr_CreateStruct_Entry*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct_Entry* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_CreateStruct_Entry*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct_Entry* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_CreateStruct_Entry* ret = google_api_expr_v1alpha1_Expr_CreateStruct_Entry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct_Entry* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_CreateStruct_Entry* ret = google_api_expr_v1alpha1_Expr_CreateStruct_Entry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_serialize(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_serialize_ex(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_field_key = 2,
  google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_map_key = 3,
  google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_NOT_SET = 0
} google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_oneofcases;
UPB_INLINE google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_oneofcases google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_case(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Expr_CreateStruct_Entry_key_kind_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_clear_key_kind(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__CreateStruct__Entry_msg_init, &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_clear_id(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {1, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_api_expr_v1alpha1_Expr_CreateStruct_Entry_id(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_clear_field_key(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_CreateStruct_Entry_field_key(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_CreateStruct_Entry_has_field_key(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_clear_map_key(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_map_key(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_CreateStruct_Entry_has_map_key(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_clear_value(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_value(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_CreateStruct_Entry_has_value(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_clear_optional_entry(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_CreateStruct_Entry_optional_entry(const google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_id(google_api_expr_v1alpha1_Expr_CreateStruct_Entry *msg, int64_t value) {
  const upb_MiniTableField field = {1, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_field_key(google_api_expr_v1alpha1_Expr_CreateStruct_Entry *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_map_key(google_api_expr_v1alpha1_Expr_CreateStruct_Entry *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_mutable_map_key(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_CreateStruct_Entry_map_key(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_map_key(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_value(google_api_expr_v1alpha1_Expr_CreateStruct_Entry *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_CreateStruct_Entry_mutable_value(google_api_expr_v1alpha1_Expr_CreateStruct_Entry* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_CreateStruct_Entry_value(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_value(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_CreateStruct_Entry_set_optional_entry(google_api_expr_v1alpha1_Expr_CreateStruct_Entry *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Expr_Comprehension* google_api_expr_v1alpha1_Expr_Comprehension_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Expr_Comprehension*)_upb_Message_New(&google__api__expr__v1alpha1__Expr__Comprehension_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Comprehension* google_api_expr_v1alpha1_Expr_Comprehension_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Comprehension* ret = google_api_expr_v1alpha1_Expr_Comprehension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Comprehension_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Expr_Comprehension* google_api_expr_v1alpha1_Expr_Comprehension_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Expr_Comprehension* ret = google_api_expr_v1alpha1_Expr_Comprehension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Expr__Comprehension_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Comprehension_serialize(const google_api_expr_v1alpha1_Expr_Comprehension* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Comprehension_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Expr_Comprehension_serialize_ex(const google_api_expr_v1alpha1_Expr_Comprehension* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Expr__Comprehension_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_iter_var(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_Comprehension_iter_var(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_iter_range(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_iter_range(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Comprehension_has_iter_range(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_accu_var(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_Comprehension_accu_var(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_accu_init(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_accu_init(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Comprehension_has_accu_init(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_loop_condition(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_loop_condition(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Comprehension_has_loop_condition(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_loop_step(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_loop_step(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Comprehension_has_loop_step(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_result(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 96), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_result(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const google_api_expr_v1alpha1_Expr* default_val = NULL;
  const google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(28, 96), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Expr_Comprehension_has_result(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 96), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_clear_iter_var2(google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  const upb_MiniTableField field = {8, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Expr_Comprehension_iter_var2(const google_api_expr_v1alpha1_Expr_Comprehension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_iter_var(google_api_expr_v1alpha1_Expr_Comprehension *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_iter_range(google_api_expr_v1alpha1_Expr_Comprehension *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_mutable_iter_range(google_api_expr_v1alpha1_Expr_Comprehension* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Comprehension_iter_range(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Comprehension_set_iter_range(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_accu_var(google_api_expr_v1alpha1_Expr_Comprehension *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_accu_init(google_api_expr_v1alpha1_Expr_Comprehension *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_mutable_accu_init(google_api_expr_v1alpha1_Expr_Comprehension* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Comprehension_accu_init(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Comprehension_set_accu_init(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_loop_condition(google_api_expr_v1alpha1_Expr_Comprehension *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_mutable_loop_condition(google_api_expr_v1alpha1_Expr_Comprehension* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Comprehension_loop_condition(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Comprehension_set_loop_condition(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_loop_step(google_api_expr_v1alpha1_Expr_Comprehension *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_mutable_loop_step(google_api_expr_v1alpha1_Expr_Comprehension* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Comprehension_loop_step(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Comprehension_set_loop_step(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_result(google_api_expr_v1alpha1_Expr_Comprehension *msg, google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(28, 96), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_Expr_Comprehension_mutable_result(google_api_expr_v1alpha1_Expr_Comprehension* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_Expr_Comprehension_result(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Expr_Comprehension_set_result(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Expr_Comprehension_set_iter_var2(google_api_expr_v1alpha1_Expr_Comprehension *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Constant_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Constant*)_upb_Message_New(&google__api__expr__v1alpha1__Constant_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Constant_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Constant* ret = google_api_expr_v1alpha1_Constant_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Constant_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Constant_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Constant* ret = google_api_expr_v1alpha1_Constant_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Constant_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Constant_serialize(const google_api_expr_v1alpha1_Constant* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Constant_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Constant_serialize_ex(const google_api_expr_v1alpha1_Constant* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Constant_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  google_api_expr_v1alpha1_Constant_constant_kind_null_value = 1,
  google_api_expr_v1alpha1_Constant_constant_kind_bool_value = 2,
  google_api_expr_v1alpha1_Constant_constant_kind_int64_value = 3,
  google_api_expr_v1alpha1_Constant_constant_kind_uint64_value = 4,
  google_api_expr_v1alpha1_Constant_constant_kind_double_value = 5,
  google_api_expr_v1alpha1_Constant_constant_kind_string_value = 6,
  google_api_expr_v1alpha1_Constant_constant_kind_bytes_value = 7,
  google_api_expr_v1alpha1_Constant_constant_kind_duration_value = 8,
  google_api_expr_v1alpha1_Constant_constant_kind_timestamp_value = 9,
  google_api_expr_v1alpha1_Constant_constant_kind_NOT_SET = 0
} google_api_expr_v1alpha1_Constant_constant_kind_oneofcases;
UPB_INLINE google_api_expr_v1alpha1_Constant_constant_kind_oneofcases google_api_expr_v1alpha1_Constant_constant_kind_case(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Constant_constant_kind_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_constant_kind(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Constant_msg_init, &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_null_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_Constant_null_value(const google_api_expr_v1alpha1_Constant* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_null_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_bool_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_bool_value(const google_api_expr_v1alpha1_Constant* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_bool_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_int64_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {3, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_api_expr_v1alpha1_Constant_int64_value(const google_api_expr_v1alpha1_Constant* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {3, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_int64_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {3, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_uint64_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {4, 16, -9, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t google_api_expr_v1alpha1_Constant_uint64_value(const google_api_expr_v1alpha1_Constant* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, 16, -9, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_uint64_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {4, 16, -9, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_double_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {5, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double google_api_expr_v1alpha1_Constant_double_value(const google_api_expr_v1alpha1_Constant* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {5, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_double_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {5, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_string_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {6, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Constant_string_value(const google_api_expr_v1alpha1_Constant* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_string_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {6, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_bytes_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {7, 16, -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Constant_bytes_value(const google_api_expr_v1alpha1_Constant* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, 16, -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_bytes_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {7, 16, -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_duration_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {8, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* google_api_expr_v1alpha1_Constant_duration_value(const google_api_expr_v1alpha1_Constant* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {8, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_duration_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {8, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_clear_timestamp_value(google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {9, 16, -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* google_api_expr_v1alpha1_Constant_timestamp_value(const google_api_expr_v1alpha1_Constant* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {9, 16, -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Constant_has_timestamp_value(const google_api_expr_v1alpha1_Constant* msg) {
  const upb_MiniTableField field = {9, 16, -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Constant_set_null_value(google_api_expr_v1alpha1_Constant *msg, int32_t value) {
  const upb_MiniTableField field = {1, 16, -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_bool_value(google_api_expr_v1alpha1_Constant *msg, bool value) {
  const upb_MiniTableField field = {2, 16, -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_int64_value(google_api_expr_v1alpha1_Constant *msg, int64_t value) {
  const upb_MiniTableField field = {3, 16, -9, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_uint64_value(google_api_expr_v1alpha1_Constant *msg, uint64_t value) {
  const upb_MiniTableField field = {4, 16, -9, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_double_value(google_api_expr_v1alpha1_Constant *msg, double value) {
  const upb_MiniTableField field = {5, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_string_value(google_api_expr_v1alpha1_Constant *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, 16, -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_bytes_value(google_api_expr_v1alpha1_Constant *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, 16, -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_duration_value(google_api_expr_v1alpha1_Constant *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {8, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* google_api_expr_v1alpha1_Constant_mutable_duration_value(google_api_expr_v1alpha1_Constant* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)google_api_expr_v1alpha1_Constant_duration_value(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Constant_set_duration_value(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Constant_set_timestamp_value(google_api_expr_v1alpha1_Constant *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {9, 16, -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* google_api_expr_v1alpha1_Constant_mutable_timestamp_value(google_api_expr_v1alpha1_Constant* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)google_api_expr_v1alpha1_Constant_timestamp_value(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Constant_set_timestamp_value(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_SourceInfo_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_SourceInfo*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_SourceInfo_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourceInfo* ret = google_api_expr_v1alpha1_SourceInfo_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourceInfo_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_SourceInfo_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourceInfo* ret = google_api_expr_v1alpha1_SourceInfo_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourceInfo_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourceInfo_serialize(const google_api_expr_v1alpha1_SourceInfo* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourceInfo_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourceInfo_serialize_ex(const google_api_expr_v1alpha1_SourceInfo* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourceInfo_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_clear_syntax_version(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_SourceInfo_syntax_version(const google_api_expr_v1alpha1_SourceInfo* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_clear_location(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_SourceInfo_location(const google_api_expr_v1alpha1_SourceInfo* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_clear_line_offsets(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* google_api_expr_v1alpha1_SourceInfo_line_offsets(const google_api_expr_v1alpha1_SourceInfo* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_SourceInfo_line_offsets_upb_array(const google_api_expr_v1alpha1_SourceInfo* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_SourceInfo_line_offsets_mutable_upb_array(google_api_expr_v1alpha1_SourceInfo* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_clear_positions(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t google_api_expr_v1alpha1_SourceInfo_positions_size(const google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_positions_get(const google_api_expr_v1alpha1_SourceInfo* msg, int64_t key, int32_t* val) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__PositionsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, sizeof(key), val, sizeof(*val));
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_positions_next(const google_api_expr_v1alpha1_SourceInfo* msg, int64_t* key, int32_t* val,
                           size_t* iter) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__PositionsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _google_api_expr_v1alpha1_SourceInfo_positions_upb_map(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__PositionsEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _google_api_expr_v1alpha1_SourceInfo_positions_mutable_upb_map(google_api_expr_v1alpha1_SourceInfo* msg, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__PositionsEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, sizeof(int64_t), sizeof(int32_t), a);
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_clear_macro_calls(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t google_api_expr_v1alpha1_SourceInfo_macro_calls_size(const google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_macro_calls_get(const google_api_expr_v1alpha1_SourceInfo* msg, int64_t key, google_api_expr_v1alpha1_Expr** val) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__MacroCallsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, sizeof(key), val, sizeof(*val));
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_macro_calls_next(const google_api_expr_v1alpha1_SourceInfo* msg, int64_t* key, const google_api_expr_v1alpha1_Expr** val,
                           size_t* iter) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__MacroCallsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _google_api_expr_v1alpha1_SourceInfo_macro_calls_upb_map(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__MacroCallsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _google_api_expr_v1alpha1_SourceInfo_macro_calls_mutable_upb_map(google_api_expr_v1alpha1_SourceInfo* msg, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__MacroCallsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, sizeof(int64_t), sizeof(google_api_expr_v1alpha1_Expr*), a);
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_clear_extensions(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_SourceInfo_Extension* const* google_api_expr_v1alpha1_SourceInfo_extensions(const google_api_expr_v1alpha1_SourceInfo* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_SourceInfo_Extension* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_SourceInfo_extensions_upb_array(const google_api_expr_v1alpha1_SourceInfo* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_SourceInfo_extensions_mutable_upb_array(google_api_expr_v1alpha1_SourceInfo* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_set_syntax_version(google_api_expr_v1alpha1_SourceInfo *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_set_location(google_api_expr_v1alpha1_SourceInfo *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* google_api_expr_v1alpha1_SourceInfo_mutable_line_offsets(google_api_expr_v1alpha1_SourceInfo* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* google_api_expr_v1alpha1_SourceInfo_resize_line_offsets(google_api_expr_v1alpha1_SourceInfo* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_add_line_offsets(google_api_expr_v1alpha1_SourceInfo* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_positions_clear(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_positions_set(google_api_expr_v1alpha1_SourceInfo* msg, int64_t key, int32_t val, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__PositionsEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, sizeof(key), sizeof(val), a);
  return _upb_Map_Insert(map, &key, sizeof(key), &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_positions_delete(google_api_expr_v1alpha1_SourceInfo* msg, int64_t key) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, sizeof(key), NULL);
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_macro_calls_clear(google_api_expr_v1alpha1_SourceInfo* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_macro_calls_set(google_api_expr_v1alpha1_SourceInfo* msg, int64_t key, google_api_expr_v1alpha1_Expr* val, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__MacroCallsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, sizeof(key), sizeof(val), a);
  return _upb_Map_Insert(map, &key, sizeof(key), &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_macro_calls_delete(google_api_expr_v1alpha1_SourceInfo* msg, int64_t key) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, sizeof(key), NULL);
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension** google_api_expr_v1alpha1_SourceInfo_mutable_extensions(google_api_expr_v1alpha1_SourceInfo* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_SourceInfo_Extension**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension** google_api_expr_v1alpha1_SourceInfo_resize_extensions(google_api_expr_v1alpha1_SourceInfo* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_SourceInfo_Extension**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_SourceInfo_Extension* google_api_expr_v1alpha1_SourceInfo_add_extensions(google_api_expr_v1alpha1_SourceInfo* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_SourceInfo_Extension* sub = (struct google_api_expr_v1alpha1_SourceInfo_Extension*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension* google_api_expr_v1alpha1_SourceInfo_Extension_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_SourceInfo_Extension*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo__Extension_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension* google_api_expr_v1alpha1_SourceInfo_Extension_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourceInfo_Extension* ret = google_api_expr_v1alpha1_SourceInfo_Extension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourceInfo__Extension_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension* google_api_expr_v1alpha1_SourceInfo_Extension_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourceInfo_Extension* ret = google_api_expr_v1alpha1_SourceInfo_Extension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourceInfo__Extension_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourceInfo_Extension_serialize(const google_api_expr_v1alpha1_SourceInfo_Extension* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourceInfo__Extension_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourceInfo_Extension_serialize_ex(const google_api_expr_v1alpha1_SourceInfo_Extension* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourceInfo__Extension_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_clear_id(google_api_expr_v1alpha1_SourceInfo_Extension* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_SourceInfo_Extension_id(const google_api_expr_v1alpha1_SourceInfo_Extension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_clear_affected_components(google_api_expr_v1alpha1_SourceInfo_Extension* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* google_api_expr_v1alpha1_SourceInfo_Extension_affected_components(const google_api_expr_v1alpha1_SourceInfo_Extension* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_SourceInfo_Extension_affected_components_upb_array(const google_api_expr_v1alpha1_SourceInfo_Extension* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_SourceInfo_Extension_affected_components_mutable_upb_array(google_api_expr_v1alpha1_SourceInfo_Extension* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_clear_version(google_api_expr_v1alpha1_SourceInfo_Extension* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_SourceInfo_Extension_Version* google_api_expr_v1alpha1_SourceInfo_Extension_version(const google_api_expr_v1alpha1_SourceInfo_Extension* msg) {
  const google_api_expr_v1alpha1_SourceInfo_Extension_Version* default_val = NULL;
  const google_api_expr_v1alpha1_SourceInfo_Extension_Version* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_Extension_has_version(const google_api_expr_v1alpha1_SourceInfo_Extension* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_set_id(google_api_expr_v1alpha1_SourceInfo_Extension *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE int32_t* google_api_expr_v1alpha1_SourceInfo_Extension_mutable_affected_components(google_api_expr_v1alpha1_SourceInfo_Extension* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* google_api_expr_v1alpha1_SourceInfo_Extension_resize_affected_components(google_api_expr_v1alpha1_SourceInfo_Extension* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool google_api_expr_v1alpha1_SourceInfo_Extension_add_affected_components(google_api_expr_v1alpha1_SourceInfo_Extension* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &val, sizeof(val));
  return true;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_set_version(google_api_expr_v1alpha1_SourceInfo_Extension *msg, google_api_expr_v1alpha1_SourceInfo_Extension_Version* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_SourceInfo_Extension_Version* google_api_expr_v1alpha1_SourceInfo_Extension_mutable_version(google_api_expr_v1alpha1_SourceInfo_Extension* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_SourceInfo_Extension_Version* sub = (struct google_api_expr_v1alpha1_SourceInfo_Extension_Version*)google_api_expr_v1alpha1_SourceInfo_Extension_version(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_SourceInfo_Extension_Version*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_SourceInfo_Extension_set_version(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension_Version* google_api_expr_v1alpha1_SourceInfo_Extension_Version_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_SourceInfo_Extension_Version*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension_Version* google_api_expr_v1alpha1_SourceInfo_Extension_Version_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourceInfo_Extension_Version* ret = google_api_expr_v1alpha1_SourceInfo_Extension_Version_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_SourceInfo_Extension_Version* google_api_expr_v1alpha1_SourceInfo_Extension_Version_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourceInfo_Extension_Version* ret = google_api_expr_v1alpha1_SourceInfo_Extension_Version_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourceInfo_Extension_Version_serialize(const google_api_expr_v1alpha1_SourceInfo_Extension_Version* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourceInfo_Extension_Version_serialize_ex(const google_api_expr_v1alpha1_SourceInfo_Extension_Version* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourceInfo__Extension__Version_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_Version_clear_major(google_api_expr_v1alpha1_SourceInfo_Extension_Version* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_api_expr_v1alpha1_SourceInfo_Extension_Version_major(const google_api_expr_v1alpha1_SourceInfo_Extension_Version* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_Version_clear_minor(google_api_expr_v1alpha1_SourceInfo_Extension_Version* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_api_expr_v1alpha1_SourceInfo_Extension_Version_minor(const google_api_expr_v1alpha1_SourceInfo_Extension_Version* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_Version_set_major(google_api_expr_v1alpha1_SourceInfo_Extension_Version *msg, int64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_SourceInfo_Extension_Version_set_minor(google_api_expr_v1alpha1_SourceInfo_Extension_Version *msg, int64_t value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_SourcePosition* google_api_expr_v1alpha1_SourcePosition_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_SourcePosition*)_upb_Message_New(&google__api__expr__v1alpha1__SourcePosition_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_SourcePosition* google_api_expr_v1alpha1_SourcePosition_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourcePosition* ret = google_api_expr_v1alpha1_SourcePosition_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourcePosition_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_SourcePosition* google_api_expr_v1alpha1_SourcePosition_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_SourcePosition* ret = google_api_expr_v1alpha1_SourcePosition_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__SourcePosition_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourcePosition_serialize(const google_api_expr_v1alpha1_SourcePosition* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourcePosition_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_SourcePosition_serialize_ex(const google_api_expr_v1alpha1_SourcePosition* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__SourcePosition_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_clear_location(google_api_expr_v1alpha1_SourcePosition* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_SourcePosition_location(const google_api_expr_v1alpha1_SourcePosition* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_clear_offset(google_api_expr_v1alpha1_SourcePosition* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_SourcePosition_offset(const google_api_expr_v1alpha1_SourcePosition* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_clear_line(google_api_expr_v1alpha1_SourcePosition* msg) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_SourcePosition_line(const google_api_expr_v1alpha1_SourcePosition* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_clear_column(google_api_expr_v1alpha1_SourcePosition* msg) {
  const upb_MiniTableField field = {4, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_SourcePosition_column(const google_api_expr_v1alpha1_SourcePosition* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {4, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_set_location(google_api_expr_v1alpha1_SourcePosition *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_set_offset(google_api_expr_v1alpha1_SourcePosition *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_set_line(google_api_expr_v1alpha1_SourcePosition *msg, int32_t value) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_SourcePosition_set_column(google_api_expr_v1alpha1_SourcePosition *msg, int32_t value) {
  const upb_MiniTableField field = {4, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
