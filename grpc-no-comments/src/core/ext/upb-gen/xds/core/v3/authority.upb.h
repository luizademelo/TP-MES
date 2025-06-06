
/* This file was generated by upb_generator from the input file:
 *
 *     xds/core/v3/authority.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated.
 * NO CHECKED-IN PROTOBUF GENCODE */

#ifndef XDS_CORE_V3_AUTHORITY_PROTO_UPB_H__UPB_H_
#define XDS_CORE_V3_AUTHORITY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/core/v3/authority.upb_minitable.h"

#include "xds/annotations/v3/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_core_v3_Authority { upb_Message UPB_PRIVATE(base); } xds_core_v3_Authority;

UPB_INLINE xds_core_v3_Authority* xds_core_v3_Authority_new(upb_Arena* arena) {
  return (xds_core_v3_Authority*)_upb_Message_New(&xds__core__v3__Authority_msg_init, arena);
}
UPB_INLINE xds_core_v3_Authority* xds_core_v3_Authority_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_Authority* ret = xds_core_v3_Authority_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__Authority_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_Authority* xds_core_v3_Authority_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_Authority* ret = xds_core_v3_Authority_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__Authority_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_Authority_serialize(const xds_core_v3_Authority* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__Authority_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_Authority_serialize_ex(const xds_core_v3_Authority* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__Authority_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_core_v3_Authority_clear_name(xds_core_v3_Authority* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_Authority_name(const xds_core_v3_Authority* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_core_v3_Authority_set_name(xds_core_v3_Authority *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
