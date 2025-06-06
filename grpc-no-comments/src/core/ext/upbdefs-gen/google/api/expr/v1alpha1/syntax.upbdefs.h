
#ifndef GOOGLE_API_EXPR_V1ALPHA1_SYNTAX_PROTO_UPB_H__UPBDEFS_H_
#define GOOGLE_API_EXPR_V1ALPHA1_SYNTAX_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init google_api_expr_v1alpha1_syntax_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_ParsedExpr_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.ParsedExpr");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_Ident_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.Ident");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_Select_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.Select");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_Call_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.Call");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_CreateList_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.CreateList");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_CreateStruct_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.CreateStruct");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_CreateStruct_Entry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.CreateStruct.Entry");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Expr_Comprehension_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Expr.Comprehension");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_Constant_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.Constant");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_SourceInfo_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.SourceInfo");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_SourceInfo_Extension_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.SourceInfo.Extension");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_SourceInfo_Extension_Version_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.SourceInfo.Extension.Version");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_SourceInfo_PositionsEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.SourceInfo.PositionsEntry");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_SourceInfo_MacroCallsEntry_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.SourceInfo.MacroCallsEntry");
}

UPB_INLINE const upb_MessageDef *google_api_expr_v1alpha1_SourcePosition_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &google_api_expr_v1alpha1_syntax_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "google.api.expr.v1alpha1.SourcePosition");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
