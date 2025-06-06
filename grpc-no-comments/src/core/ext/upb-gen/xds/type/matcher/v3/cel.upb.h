
#ifndef XDS_TYPE_MATCHER_V3_CEL_PROTO_UPB_H__UPB_H_
#define XDS_TYPE_MATCHER_V3_CEL_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/type/matcher/v3/cel.upb_minitable.h"

#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/type/v3/cel.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_type_matcher_v3_CelMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_CelMatcher;
struct xds_type_v3_CelExpression;

UPB_INLINE xds_type_matcher_v3_CelMatcher* xds_type_matcher_v3_CelMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_CelMatcher*)_upb_Message_New(&xds__type__matcher__v3__CelMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_CelMatcher* xds_type_matcher_v3_CelMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_CelMatcher* ret = xds_type_matcher_v3_CelMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__CelMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_CelMatcher* xds_type_matcher_v3_CelMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_CelMatcher* ret = xds_type_matcher_v3_CelMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__CelMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_CelMatcher_serialize(const xds_type_matcher_v3_CelMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__CelMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_CelMatcher_serialize_ex(const xds_type_matcher_v3_CelMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__CelMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_CelMatcher_clear_expr_match(xds_type_matcher_v3_CelMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_v3_CelExpression* xds_type_matcher_v3_CelMatcher_expr_match(const xds_type_matcher_v3_CelMatcher* msg) {
  const struct xds_type_v3_CelExpression* default_val = NULL;
  const struct xds_type_v3_CelExpression* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__CelExpression_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_matcher_v3_CelMatcher_has_expr_match(const xds_type_matcher_v3_CelMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_type_matcher_v3_CelMatcher_clear_description(xds_type_matcher_v3_CelMatcher* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_type_matcher_v3_CelMatcher_description(const xds_type_matcher_v3_CelMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_type_matcher_v3_CelMatcher_set_expr_match(xds_type_matcher_v3_CelMatcher *msg, struct xds_type_v3_CelExpression* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__CelExpression_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_v3_CelExpression* xds_type_matcher_v3_CelMatcher_mutable_expr_match(xds_type_matcher_v3_CelMatcher* msg, upb_Arena* arena) {
  struct xds_type_v3_CelExpression* sub = (struct xds_type_v3_CelExpression*)xds_type_matcher_v3_CelMatcher_expr_match(msg);
  if (sub == NULL) {
    sub = (struct xds_type_v3_CelExpression*)_upb_Message_New(&xds__type__v3__CelExpression_msg_init, arena);
    if (sub) xds_type_matcher_v3_CelMatcher_set_expr_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void xds_type_matcher_v3_CelMatcher_set_description(xds_type_matcher_v3_CelMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
