
#ifndef GOOGLE_API_EXPR_V1ALPHA1_CHECKED_PROTO_UPB_H__UPBDEFS_H_
#define GOOGLE_API_EXPR_V1ALPHA1_CHECKED_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init google_api_expr_v1alpha1_checked_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_CheckedExpr_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.CheckedExpr");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_CheckedExpr_ReferenceMapEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.CheckedExpr.ReferenceMapEntry");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_CheckedExpr_TypeMapEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.CheckedExpr.TypeMapEntry");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Type_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Type");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Type_ListType_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Type.ListType");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Type_MapType_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Type.MapType");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Type_FunctionType_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Type.FunctionType");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Type_AbstractType_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Type.AbstractType");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Decl_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Decl");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Decl_IdentDecl_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Decl.IdentDecl");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Decl_FunctionDecl_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Decl.FunctionDecl");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Decl_FunctionDecl_Overload_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Decl.FunctionDecl.Overload");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Reference_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_checked_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Reference");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
