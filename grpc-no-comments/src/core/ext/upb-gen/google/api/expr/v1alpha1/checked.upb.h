
#ifndef GOOGLE_API_EXPR_V1ALPHA1_CHECKED_PROTO_UPB_H__UPB_H_
#define GOOGLE_API_EXPR_V1ALPHA1_CHECKED_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/api/expr/v1alpha1/checked.upb_minitable.h"

#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"
#include "google/protobuf/empty.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct google_api_expr_v1alpha1_CheckedExpr { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_CheckedExpr;
typedef struct google_api_expr_v1alpha1_Type { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Type;
typedef struct google_api_expr_v1alpha1_Type_ListType { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Type_ListType;
typedef struct google_api_expr_v1alpha1_Type_MapType { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Type_MapType;
typedef struct google_api_expr_v1alpha1_Type_FunctionType { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Type_FunctionType;
typedef struct google_api_expr_v1alpha1_Type_AbstractType { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Type_AbstractType;
typedef struct google_api_expr_v1alpha1_Decl { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Decl;
typedef struct google_api_expr_v1alpha1_Decl_IdentDecl { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Decl_IdentDecl;
typedef struct google_api_expr_v1alpha1_Decl_FunctionDecl { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Decl_FunctionDecl;
typedef struct google_api_expr_v1alpha1_Decl_FunctionDecl_Overload { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Decl_FunctionDecl_Overload;
typedef struct google_api_expr_v1alpha1_Reference { upb_Message UPB_PRIVATE(base); } google_api_expr_v1alpha1_Reference;
struct google_api_expr_v1alpha1_Constant;
struct google_api_expr_v1alpha1_Expr;
struct google_api_expr_v1alpha1_SourceInfo;
struct google_protobuf_Empty;

typedef enum {
  google_api_expr_v1alpha1_Type_PRIMITIVE_TYPE_UNSPECIFIED = 0,
  google_api_expr_v1alpha1_Type_BOOL = 1,
  google_api_expr_v1alpha1_Type_INT64 = 2,
  google_api_expr_v1alpha1_Type_UINT64 = 3,
  google_api_expr_v1alpha1_Type_DOUBLE = 4,
  google_api_expr_v1alpha1_Type_STRING = 5,
  google_api_expr_v1alpha1_Type_BYTES = 6
} google_api_expr_v1alpha1_Type_PrimitiveType;

typedef enum {
  google_api_expr_v1alpha1_Type_WELL_KNOWN_TYPE_UNSPECIFIED = 0,
  google_api_expr_v1alpha1_Type_ANY = 1,
  google_api_expr_v1alpha1_Type_TIMESTAMP = 2,
  google_api_expr_v1alpha1_Type_DURATION = 3
} google_api_expr_v1alpha1_Type_WellKnownType;

UPB_INLINE google_api_expr_v1alpha1_CheckedExpr* google_api_expr_v1alpha1_CheckedExpr_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_CheckedExpr*)_upb_Message_New(&google__api__expr__v1alpha1__CheckedExpr_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_CheckedExpr* google_api_expr_v1alpha1_CheckedExpr_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_CheckedExpr* ret = google_api_expr_v1alpha1_CheckedExpr_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__CheckedExpr_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_CheckedExpr* google_api_expr_v1alpha1_CheckedExpr_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_CheckedExpr* ret = google_api_expr_v1alpha1_CheckedExpr_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__CheckedExpr_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_CheckedExpr_serialize(const google_api_expr_v1alpha1_CheckedExpr* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__CheckedExpr_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_CheckedExpr_serialize_ex(const google_api_expr_v1alpha1_CheckedExpr* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__CheckedExpr_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_clear_reference_map(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t google_api_expr_v1alpha1_CheckedExpr_reference_map_size(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_reference_map_get(const google_api_expr_v1alpha1_CheckedExpr* msg, int64_t key, google_api_expr_v1alpha1_Reference** val) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Reference_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, sizeof(key), val, sizeof(*val));
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_reference_map_next(const google_api_expr_v1alpha1_CheckedExpr* msg, int64_t* key, const google_api_expr_v1alpha1_Reference** val,
                           size_t* iter) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Reference_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _google_api_expr_v1alpha1_CheckedExpr_reference_map_upb_map(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Reference_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _google_api_expr_v1alpha1_CheckedExpr_reference_map_mutable_upb_map(google_api_expr_v1alpha1_CheckedExpr* msg, upb_Arena* a) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Reference_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, sizeof(int64_t), sizeof(google_api_expr_v1alpha1_Reference*), a);
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_clear_type_map(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t google_api_expr_v1alpha1_CheckedExpr_type_map_size(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_type_map_get(const google_api_expr_v1alpha1_CheckedExpr* msg, int64_t key, google_api_expr_v1alpha1_Type** val) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, sizeof(key), val, sizeof(*val));
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_type_map_next(const google_api_expr_v1alpha1_CheckedExpr* msg, int64_t* key, const google_api_expr_v1alpha1_Type** val,
                           size_t* iter) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _google_api_expr_v1alpha1_CheckedExpr_type_map_upb_map(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _google_api_expr_v1alpha1_CheckedExpr_type_map_mutable_upb_map(google_api_expr_v1alpha1_CheckedExpr* msg, upb_Arena* a) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, sizeof(int64_t), sizeof(google_api_expr_v1alpha1_Type*), a);
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_clear_expr(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_CheckedExpr_expr(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  const struct google_api_expr_v1alpha1_Expr* default_val = NULL;
  const struct google_api_expr_v1alpha1_Expr* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_has_expr(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_clear_source_info(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_CheckedExpr_source_info(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  const struct google_api_expr_v1alpha1_SourceInfo* default_val = NULL;
  const struct google_api_expr_v1alpha1_SourceInfo* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_has_source_info(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_clear_expr_version(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_CheckedExpr_expr_version(const google_api_expr_v1alpha1_CheckedExpr* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_reference_map_clear(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_reference_map_set(google_api_expr_v1alpha1_CheckedExpr* msg, int64_t key, google_api_expr_v1alpha1_Reference* val, upb_Arena* a) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Reference_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, sizeof(key), sizeof(val), a);
  return _upb_Map_Insert(map, &key, sizeof(key), &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_reference_map_delete(google_api_expr_v1alpha1_CheckedExpr* msg, int64_t key) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, sizeof(key), NULL);
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_type_map_clear(google_api_expr_v1alpha1_CheckedExpr* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_type_map_set(google_api_expr_v1alpha1_CheckedExpr* msg, int64_t key, google_api_expr_v1alpha1_Type* val, upb_Arena* a) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, sizeof(key), sizeof(val), a);
  return _upb_Map_Insert(map, &key, sizeof(key), &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool google_api_expr_v1alpha1_CheckedExpr_type_map_delete(google_api_expr_v1alpha1_CheckedExpr* msg, int64_t key) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, sizeof(key), NULL);
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_set_expr(google_api_expr_v1alpha1_CheckedExpr *msg, struct google_api_expr_v1alpha1_Expr* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Expr_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Expr* google_api_expr_v1alpha1_CheckedExpr_mutable_expr(google_api_expr_v1alpha1_CheckedExpr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Expr* sub = (struct google_api_expr_v1alpha1_Expr*)google_api_expr_v1alpha1_CheckedExpr_expr(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Expr*)_upb_Message_New(&google__api__expr__v1alpha1__Expr_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_CheckedExpr_set_expr(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_set_source_info(google_api_expr_v1alpha1_CheckedExpr *msg, struct google_api_expr_v1alpha1_SourceInfo* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__SourceInfo_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_SourceInfo* google_api_expr_v1alpha1_CheckedExpr_mutable_source_info(google_api_expr_v1alpha1_CheckedExpr* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_SourceInfo* sub = (struct google_api_expr_v1alpha1_SourceInfo*)google_api_expr_v1alpha1_CheckedExpr_source_info(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_SourceInfo*)_upb_Message_New(&google__api__expr__v1alpha1__SourceInfo_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_CheckedExpr_set_source_info(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_CheckedExpr_set_expr_version(google_api_expr_v1alpha1_CheckedExpr *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type* ret = google_api_expr_v1alpha1_Type_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type* ret = google_api_expr_v1alpha1_Type_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_serialize(const google_api_expr_v1alpha1_Type* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_serialize_ex(const google_api_expr_v1alpha1_Type* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  google_api_expr_v1alpha1_Type_type_kind_dyn = 1,
  google_api_expr_v1alpha1_Type_type_kind_null = 2,
  google_api_expr_v1alpha1_Type_type_kind_primitive = 3,
  google_api_expr_v1alpha1_Type_type_kind_wrapper = 4,
  google_api_expr_v1alpha1_Type_type_kind_well_known = 5,
  google_api_expr_v1alpha1_Type_type_kind_list_type = 6,
  google_api_expr_v1alpha1_Type_type_kind_map_type = 7,
  google_api_expr_v1alpha1_Type_type_kind_function = 8,
  google_api_expr_v1alpha1_Type_type_kind_message_type = 9,
  google_api_expr_v1alpha1_Type_type_kind_type_param = 10,
  google_api_expr_v1alpha1_Type_type_kind_type = 11,
  google_api_expr_v1alpha1_Type_type_kind_error = 12,
  google_api_expr_v1alpha1_Type_type_kind_abstract_type = 14,
  google_api_expr_v1alpha1_Type_type_kind_NOT_SET = 0
} google_api_expr_v1alpha1_Type_type_kind_oneofcases;
UPB_INLINE google_api_expr_v1alpha1_Type_type_kind_oneofcases google_api_expr_v1alpha1_Type_type_kind_case(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Type_type_kind_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_type_kind(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type_msg_init, &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_dyn(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Empty* google_api_expr_v1alpha1_Type_dyn(const google_api_expr_v1alpha1_Type* msg) {
  const struct google_protobuf_Empty* default_val = NULL;
  const struct google_protobuf_Empty* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_dyn(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_null(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_Type_null(const google_api_expr_v1alpha1_Type* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_null(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_primitive(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_Type_primitive(const google_api_expr_v1alpha1_Type* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_primitive(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_wrapper(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_Type_wrapper(const google_api_expr_v1alpha1_Type* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_wrapper(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_well_known(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_api_expr_v1alpha1_Type_well_known(const google_api_expr_v1alpha1_Type* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_well_known(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_list_type(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type_ListType* google_api_expr_v1alpha1_Type_list_type(const google_api_expr_v1alpha1_Type* msg) {
  const google_api_expr_v1alpha1_Type_ListType* default_val = NULL;
  const google_api_expr_v1alpha1_Type_ListType* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__ListType_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_list_type(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_map_type(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type_MapType* google_api_expr_v1alpha1_Type_map_type(const google_api_expr_v1alpha1_Type* msg) {
  const google_api_expr_v1alpha1_Type_MapType* default_val = NULL;
  const google_api_expr_v1alpha1_Type_MapType* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__MapType_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_map_type(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_function(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type_FunctionType* google_api_expr_v1alpha1_Type_function(const google_api_expr_v1alpha1_Type* msg) {
  const google_api_expr_v1alpha1_Type_FunctionType* default_val = NULL;
  const google_api_expr_v1alpha1_Type_FunctionType* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__FunctionType_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_function(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_message_type(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Type_message_type(const google_api_expr_v1alpha1_Type* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_message_type(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_type_param(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Type_type_param(const google_api_expr_v1alpha1_Type* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_type_param(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_type(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_type(const google_api_expr_v1alpha1_Type* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_type(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_error(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Empty* google_api_expr_v1alpha1_Type_error(const google_api_expr_v1alpha1_Type* msg) {
  const struct google_protobuf_Empty* default_val = NULL;
  const struct google_protobuf_Empty* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_error(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_clear_abstract_type(google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type_AbstractType* google_api_expr_v1alpha1_Type_abstract_type(const google_api_expr_v1alpha1_Type* msg) {
  const google_api_expr_v1alpha1_Type_AbstractType* default_val = NULL;
  const google_api_expr_v1alpha1_Type_AbstractType* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__AbstractType_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_has_abstract_type(const google_api_expr_v1alpha1_Type* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Type_set_dyn(google_api_expr_v1alpha1_Type *msg, struct google_protobuf_Empty* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Empty* google_api_expr_v1alpha1_Type_mutable_dyn(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_protobuf_Empty* sub = (struct google_protobuf_Empty*)google_api_expr_v1alpha1_Type_dyn(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Empty*)_upb_Message_New(&google__protobuf__Empty_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_dyn(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_null(google_api_expr_v1alpha1_Type *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_primitive(google_api_expr_v1alpha1_Type *msg, int32_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_wrapper(google_api_expr_v1alpha1_Type *msg, int32_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_well_known(google_api_expr_v1alpha1_Type *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_list_type(google_api_expr_v1alpha1_Type *msg, google_api_expr_v1alpha1_Type_ListType* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__ListType_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type_ListType* google_api_expr_v1alpha1_Type_mutable_list_type(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type_ListType* sub = (struct google_api_expr_v1alpha1_Type_ListType*)google_api_expr_v1alpha1_Type_list_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type_ListType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__ListType_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_list_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_map_type(google_api_expr_v1alpha1_Type *msg, google_api_expr_v1alpha1_Type_MapType* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__MapType_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type_MapType* google_api_expr_v1alpha1_Type_mutable_map_type(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type_MapType* sub = (struct google_api_expr_v1alpha1_Type_MapType*)google_api_expr_v1alpha1_Type_map_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type_MapType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__MapType_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_map_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_function(google_api_expr_v1alpha1_Type *msg, google_api_expr_v1alpha1_Type_FunctionType* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__FunctionType_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type_FunctionType* google_api_expr_v1alpha1_Type_mutable_function(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type_FunctionType* sub = (struct google_api_expr_v1alpha1_Type_FunctionType*)google_api_expr_v1alpha1_Type_function(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type_FunctionType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__FunctionType_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_function(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_message_type(google_api_expr_v1alpha1_Type *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_type_param(google_api_expr_v1alpha1_Type *msg, upb_StringView value) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_type(google_api_expr_v1alpha1_Type *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_mutable_type(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Type_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_error(google_api_expr_v1alpha1_Type *msg, struct google_protobuf_Empty* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Empty_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Empty* google_api_expr_v1alpha1_Type_mutable_error(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_protobuf_Empty* sub = (struct google_protobuf_Empty*)google_api_expr_v1alpha1_Type_error(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Empty*)_upb_Message_New(&google__protobuf__Empty_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_error(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_set_abstract_type(google_api_expr_v1alpha1_Type *msg, google_api_expr_v1alpha1_Type_AbstractType* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type__AbstractType_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type_AbstractType* google_api_expr_v1alpha1_Type_mutable_abstract_type(google_api_expr_v1alpha1_Type* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type_AbstractType* sub = (struct google_api_expr_v1alpha1_Type_AbstractType*)google_api_expr_v1alpha1_Type_abstract_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type_AbstractType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__AbstractType_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_set_abstract_type(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Type_ListType* google_api_expr_v1alpha1_Type_ListType_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Type_ListType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__ListType_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Type_ListType* google_api_expr_v1alpha1_Type_ListType_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_ListType* ret = google_api_expr_v1alpha1_Type_ListType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__ListType_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Type_ListType* google_api_expr_v1alpha1_Type_ListType_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_ListType* ret = google_api_expr_v1alpha1_Type_ListType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__ListType_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_ListType_serialize(const google_api_expr_v1alpha1_Type_ListType* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__ListType_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_ListType_serialize_ex(const google_api_expr_v1alpha1_Type_ListType* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__ListType_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_ListType_clear_elem_type(google_api_expr_v1alpha1_Type_ListType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_ListType_elem_type(const google_api_expr_v1alpha1_Type_ListType* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_ListType_has_elem_type(const google_api_expr_v1alpha1_Type_ListType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Type_ListType_set_elem_type(google_api_expr_v1alpha1_Type_ListType *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_ListType_mutable_elem_type(google_api_expr_v1alpha1_Type_ListType* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Type_ListType_elem_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_ListType_set_elem_type(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Type_MapType* google_api_expr_v1alpha1_Type_MapType_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Type_MapType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__MapType_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Type_MapType* google_api_expr_v1alpha1_Type_MapType_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_MapType* ret = google_api_expr_v1alpha1_Type_MapType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__MapType_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Type_MapType* google_api_expr_v1alpha1_Type_MapType_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_MapType* ret = google_api_expr_v1alpha1_Type_MapType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__MapType_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_MapType_serialize(const google_api_expr_v1alpha1_Type_MapType* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__MapType_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_MapType_serialize_ex(const google_api_expr_v1alpha1_Type_MapType* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__MapType_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_MapType_clear_key_type(google_api_expr_v1alpha1_Type_MapType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_MapType_key_type(const google_api_expr_v1alpha1_Type_MapType* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_MapType_has_key_type(const google_api_expr_v1alpha1_Type_MapType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_MapType_clear_value_type(google_api_expr_v1alpha1_Type_MapType* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_MapType_value_type(const google_api_expr_v1alpha1_Type_MapType* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_MapType_has_value_type(const google_api_expr_v1alpha1_Type_MapType* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Type_MapType_set_key_type(google_api_expr_v1alpha1_Type_MapType *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_MapType_mutable_key_type(google_api_expr_v1alpha1_Type_MapType* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Type_MapType_key_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_MapType_set_key_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_MapType_set_value_type(google_api_expr_v1alpha1_Type_MapType *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_MapType_mutable_value_type(google_api_expr_v1alpha1_Type_MapType* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Type_MapType_value_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_MapType_set_value_type(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Type_FunctionType* google_api_expr_v1alpha1_Type_FunctionType_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Type_FunctionType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__FunctionType_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Type_FunctionType* google_api_expr_v1alpha1_Type_FunctionType_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_FunctionType* ret = google_api_expr_v1alpha1_Type_FunctionType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__FunctionType_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Type_FunctionType* google_api_expr_v1alpha1_Type_FunctionType_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_FunctionType* ret = google_api_expr_v1alpha1_Type_FunctionType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__FunctionType_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_FunctionType_serialize(const google_api_expr_v1alpha1_Type_FunctionType* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__FunctionType_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_FunctionType_serialize_ex(const google_api_expr_v1alpha1_Type_FunctionType* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__FunctionType_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_FunctionType_clear_result_type(google_api_expr_v1alpha1_Type_FunctionType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_FunctionType_result_type(const google_api_expr_v1alpha1_Type_FunctionType* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Type_FunctionType_has_result_type(const google_api_expr_v1alpha1_Type_FunctionType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Type_FunctionType_clear_arg_types(google_api_expr_v1alpha1_Type_FunctionType* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* const* google_api_expr_v1alpha1_Type_FunctionType_arg_types(const google_api_expr_v1alpha1_Type_FunctionType* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Type* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Type_FunctionType_arg_types_upb_array(const google_api_expr_v1alpha1_Type_FunctionType* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Type_FunctionType_arg_types_mutable_upb_array(google_api_expr_v1alpha1_Type_FunctionType* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void google_api_expr_v1alpha1_Type_FunctionType_set_result_type(google_api_expr_v1alpha1_Type_FunctionType *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_FunctionType_mutable_result_type(google_api_expr_v1alpha1_Type_FunctionType* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Type_FunctionType_result_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Type_FunctionType_set_result_type(msg, sub);
  }
  return sub;
}
UPB_INLINE google_api_expr_v1alpha1_Type** google_api_expr_v1alpha1_Type_FunctionType_mutable_arg_types(google_api_expr_v1alpha1_Type_FunctionType* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Type**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Type** google_api_expr_v1alpha1_Type_FunctionType_resize_arg_types(google_api_expr_v1alpha1_Type_FunctionType* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Type**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_FunctionType_add_arg_types(google_api_expr_v1alpha1_Type_FunctionType* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Type_AbstractType* google_api_expr_v1alpha1_Type_AbstractType_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Type_AbstractType*)_upb_Message_New(&google__api__expr__v1alpha1__Type__AbstractType_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Type_AbstractType* google_api_expr_v1alpha1_Type_AbstractType_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_AbstractType* ret = google_api_expr_v1alpha1_Type_AbstractType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__AbstractType_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Type_AbstractType* google_api_expr_v1alpha1_Type_AbstractType_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Type_AbstractType* ret = google_api_expr_v1alpha1_Type_AbstractType_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Type__AbstractType_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_AbstractType_serialize(const google_api_expr_v1alpha1_Type_AbstractType* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__AbstractType_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Type_AbstractType_serialize_ex(const google_api_expr_v1alpha1_Type_AbstractType* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Type__AbstractType_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_AbstractType_clear_name(google_api_expr_v1alpha1_Type_AbstractType* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Type_AbstractType_name(const google_api_expr_v1alpha1_Type_AbstractType* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Type_AbstractType_clear_parameter_types(google_api_expr_v1alpha1_Type_AbstractType* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* const* google_api_expr_v1alpha1_Type_AbstractType_parameter_types(const google_api_expr_v1alpha1_Type_AbstractType* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Type* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Type_AbstractType_parameter_types_upb_array(const google_api_expr_v1alpha1_Type_AbstractType* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Type_AbstractType_parameter_types_mutable_upb_array(google_api_expr_v1alpha1_Type_AbstractType* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void google_api_expr_v1alpha1_Type_AbstractType_set_name(google_api_expr_v1alpha1_Type_AbstractType *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE google_api_expr_v1alpha1_Type** google_api_expr_v1alpha1_Type_AbstractType_mutable_parameter_types(google_api_expr_v1alpha1_Type_AbstractType* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Type**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Type** google_api_expr_v1alpha1_Type_AbstractType_resize_parameter_types(google_api_expr_v1alpha1_Type_AbstractType* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Type**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Type_AbstractType_add_parameter_types(google_api_expr_v1alpha1_Type_AbstractType* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Decl* google_api_expr_v1alpha1_Decl_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Decl*)_upb_Message_New(&google__api__expr__v1alpha1__Decl_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Decl* google_api_expr_v1alpha1_Decl_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl* ret = google_api_expr_v1alpha1_Decl_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Decl* google_api_expr_v1alpha1_Decl_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl* ret = google_api_expr_v1alpha1_Decl_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_serialize(const google_api_expr_v1alpha1_Decl* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_serialize_ex(const google_api_expr_v1alpha1_Decl* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  google_api_expr_v1alpha1_Decl_decl_kind_ident = 2,
  google_api_expr_v1alpha1_Decl_decl_kind_function = 3,
  google_api_expr_v1alpha1_Decl_decl_kind_NOT_SET = 0
} google_api_expr_v1alpha1_Decl_decl_kind_oneofcases;
UPB_INLINE google_api_expr_v1alpha1_Decl_decl_kind_oneofcases google_api_expr_v1alpha1_Decl_decl_kind_case(const google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Decl_decl_kind_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_clear_decl_kind(google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl_msg_init, &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_clear_name(google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Decl_name(const google_api_expr_v1alpha1_Decl* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_clear_ident(google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Decl_IdentDecl* google_api_expr_v1alpha1_Decl_ident(const google_api_expr_v1alpha1_Decl* msg) {
  const google_api_expr_v1alpha1_Decl_IdentDecl* default_val = NULL;
  const google_api_expr_v1alpha1_Decl_IdentDecl* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__IdentDecl_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_has_ident(const google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_clear_function(google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Decl_FunctionDecl* google_api_expr_v1alpha1_Decl_function(const google_api_expr_v1alpha1_Decl* msg) {
  const google_api_expr_v1alpha1_Decl_FunctionDecl* default_val = NULL;
  const google_api_expr_v1alpha1_Decl_FunctionDecl* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_has_function(const google_api_expr_v1alpha1_Decl* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Decl_set_name(google_api_expr_v1alpha1_Decl *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_set_ident(google_api_expr_v1alpha1_Decl *msg, google_api_expr_v1alpha1_Decl_IdentDecl* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__IdentDecl_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Decl_IdentDecl* google_api_expr_v1alpha1_Decl_mutable_ident(google_api_expr_v1alpha1_Decl* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Decl_IdentDecl* sub = (struct google_api_expr_v1alpha1_Decl_IdentDecl*)google_api_expr_v1alpha1_Decl_ident(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Decl_IdentDecl*)_upb_Message_New(&google__api__expr__v1alpha1__Decl__IdentDecl_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Decl_set_ident(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_set_function(google_api_expr_v1alpha1_Decl *msg, google_api_expr_v1alpha1_Decl_FunctionDecl* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Decl_FunctionDecl* google_api_expr_v1alpha1_Decl_mutable_function(google_api_expr_v1alpha1_Decl* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Decl_FunctionDecl* sub = (struct google_api_expr_v1alpha1_Decl_FunctionDecl*)google_api_expr_v1alpha1_Decl_function(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Decl_FunctionDecl*)_upb_Message_New(&google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Decl_set_function(msg, sub);
  }
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Decl_IdentDecl* google_api_expr_v1alpha1_Decl_IdentDecl_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Decl_IdentDecl*)_upb_Message_New(&google__api__expr__v1alpha1__Decl__IdentDecl_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Decl_IdentDecl* google_api_expr_v1alpha1_Decl_IdentDecl_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl_IdentDecl* ret = google_api_expr_v1alpha1_Decl_IdentDecl_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Decl_IdentDecl* google_api_expr_v1alpha1_Decl_IdentDecl_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl_IdentDecl* ret = google_api_expr_v1alpha1_Decl_IdentDecl_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_IdentDecl_serialize(const google_api_expr_v1alpha1_Decl_IdentDecl* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_IdentDecl_serialize_ex(const google_api_expr_v1alpha1_Decl_IdentDecl* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_IdentDecl_clear_type(google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Decl_IdentDecl_type(const google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_IdentDecl_has_type(const google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_IdentDecl_clear_value(google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Decl_IdentDecl_value(const google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const struct google_api_expr_v1alpha1_Constant* default_val = NULL;
  const struct google_api_expr_v1alpha1_Constant* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Constant_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_IdentDecl_has_value(const google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_IdentDecl_clear_doc(google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Decl_IdentDecl_doc(const google_api_expr_v1alpha1_Decl_IdentDecl* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_Decl_IdentDecl_set_type(google_api_expr_v1alpha1_Decl_IdentDecl *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Decl_IdentDecl_mutable_type(google_api_expr_v1alpha1_Decl_IdentDecl* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Decl_IdentDecl_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Decl_IdentDecl_set_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_IdentDecl_set_value(google_api_expr_v1alpha1_Decl_IdentDecl *msg, struct google_api_expr_v1alpha1_Constant* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Constant_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Decl_IdentDecl_mutable_value(google_api_expr_v1alpha1_Decl_IdentDecl* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Constant* sub = (struct google_api_expr_v1alpha1_Constant*)google_api_expr_v1alpha1_Decl_IdentDecl_value(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Constant*)_upb_Message_New(&google__api__expr__v1alpha1__Constant_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Decl_IdentDecl_set_value(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_IdentDecl_set_doc(google_api_expr_v1alpha1_Decl_IdentDecl *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl* google_api_expr_v1alpha1_Decl_FunctionDecl_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Decl_FunctionDecl*)_upb_Message_New(&google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl* google_api_expr_v1alpha1_Decl_FunctionDecl_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl_FunctionDecl* ret = google_api_expr_v1alpha1_Decl_FunctionDecl_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl* google_api_expr_v1alpha1_Decl_FunctionDecl_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl_FunctionDecl* ret = google_api_expr_v1alpha1_Decl_FunctionDecl_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_FunctionDecl_serialize(const google_api_expr_v1alpha1_Decl_FunctionDecl* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_FunctionDecl_serialize_ex(const google_api_expr_v1alpha1_Decl_FunctionDecl* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_clear_overloads(google_api_expr_v1alpha1_Decl_FunctionDecl* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* const* google_api_expr_v1alpha1_Decl_FunctionDecl_overloads(const google_api_expr_v1alpha1_Decl_FunctionDecl* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Decl_FunctionDecl_overloads_upb_array(const google_api_expr_v1alpha1_Decl_FunctionDecl* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Decl_FunctionDecl_overloads_mutable_upb_array(google_api_expr_v1alpha1_Decl_FunctionDecl* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl_Overload** google_api_expr_v1alpha1_Decl_FunctionDecl_mutable_overloads(google_api_expr_v1alpha1_Decl_FunctionDecl* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Decl_FunctionDecl_Overload**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl_Overload** google_api_expr_v1alpha1_Decl_FunctionDecl_resize_overloads(google_api_expr_v1alpha1_Decl_FunctionDecl* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Decl_FunctionDecl_Overload**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* google_api_expr_v1alpha1_Decl_FunctionDecl_add_overloads(google_api_expr_v1alpha1_Decl_FunctionDecl* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* sub = (struct google_api_expr_v1alpha1_Decl_FunctionDecl_Overload*)_upb_Message_New(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Decl_FunctionDecl_Overload*)_upb_Message_New(&google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* ret = google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* ret = google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_serialize(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_serialize_ex(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_clear_overload_id(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_overload_id(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_clear_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* const* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_params(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_expr_v1alpha1_Type* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_params_upb_array(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_params_mutable_upb_array(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_clear_type_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_type_params(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_type_params_upb_array(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_type_params_mutable_upb_array(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_clear_result_type(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_result_type(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const google_api_expr_v1alpha1_Type* default_val = NULL;
  const google_api_expr_v1alpha1_Type* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_has_result_type(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_clear_is_instance_function(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_is_instance_function(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_clear_doc(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_doc(const google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_set_overload_id(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE google_api_expr_v1alpha1_Type** google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_mutable_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_expr_v1alpha1_Type**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_expr_v1alpha1_Type** google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_resize_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_expr_v1alpha1_Type**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_add_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE upb_StringView* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_mutable_type_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_resize_type_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_add_type_params(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_set_result_type(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload *msg, google_api_expr_v1alpha1_Type* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Type_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Type* google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_mutable_result_type(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Type* sub = (struct google_api_expr_v1alpha1_Type*)google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_result_type(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Type*)_upb_Message_New(&google__api__expr__v1alpha1__Type_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_set_result_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_set_is_instance_function(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_set_doc(google_api_expr_v1alpha1_Decl_FunctionDecl_Overload *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_expr_v1alpha1_Reference* google_api_expr_v1alpha1_Reference_new(upb_Arena* arena) {
  return (google_api_expr_v1alpha1_Reference*)_upb_Message_New(&google__api__expr__v1alpha1__Reference_msg_init, arena);
}
UPB_INLINE google_api_expr_v1alpha1_Reference* google_api_expr_v1alpha1_Reference_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_expr_v1alpha1_Reference* ret = google_api_expr_v1alpha1_Reference_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Reference_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_expr_v1alpha1_Reference* google_api_expr_v1alpha1_Reference_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_expr_v1alpha1_Reference* ret = google_api_expr_v1alpha1_Reference_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__expr__v1alpha1__Reference_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_expr_v1alpha1_Reference_serialize(const google_api_expr_v1alpha1_Reference* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Reference_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_expr_v1alpha1_Reference_serialize_ex(const google_api_expr_v1alpha1_Reference* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__expr__v1alpha1__Reference_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_expr_v1alpha1_Reference_clear_name(google_api_expr_v1alpha1_Reference* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_expr_v1alpha1_Reference_name(const google_api_expr_v1alpha1_Reference* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_expr_v1alpha1_Reference_clear_overload_id(google_api_expr_v1alpha1_Reference* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* google_api_expr_v1alpha1_Reference_overload_id(const google_api_expr_v1alpha1_Reference* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_expr_v1alpha1_Reference_overload_id_upb_array(const google_api_expr_v1alpha1_Reference* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_expr_v1alpha1_Reference_overload_id_mutable_upb_array(google_api_expr_v1alpha1_Reference* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_expr_v1alpha1_Reference_clear_value(google_api_expr_v1alpha1_Reference* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Reference_value(const google_api_expr_v1alpha1_Reference* msg) {
  const struct google_api_expr_v1alpha1_Constant* default_val = NULL;
  const struct google_api_expr_v1alpha1_Constant* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Constant_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_expr_v1alpha1_Reference_has_value(const google_api_expr_v1alpha1_Reference* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void google_api_expr_v1alpha1_Reference_set_name(google_api_expr_v1alpha1_Reference *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* google_api_expr_v1alpha1_Reference_mutable_overload_id(google_api_expr_v1alpha1_Reference* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* google_api_expr_v1alpha1_Reference_resize_overload_id(google_api_expr_v1alpha1_Reference* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool google_api_expr_v1alpha1_Reference_add_overload_id(google_api_expr_v1alpha1_Reference* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void google_api_expr_v1alpha1_Reference_set_value(google_api_expr_v1alpha1_Reference *msg, struct google_api_expr_v1alpha1_Constant* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__expr__v1alpha1__Constant_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_expr_v1alpha1_Constant* google_api_expr_v1alpha1_Reference_mutable_value(google_api_expr_v1alpha1_Reference* msg, upb_Arena* arena) {
  struct google_api_expr_v1alpha1_Constant* sub = (struct google_api_expr_v1alpha1_Constant*)google_api_expr_v1alpha1_Reference_value(msg);
  if (sub == NULL) {
    sub = (struct google_api_expr_v1alpha1_Constant*)_upb_Message_New(&google__api__expr__v1alpha1__Constant_msg_init, arena);
    if (sub) google_api_expr_v1alpha1_Reference_set_value(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
