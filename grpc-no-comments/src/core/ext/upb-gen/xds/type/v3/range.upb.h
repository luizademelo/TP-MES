
#ifndef XDS_TYPE_V3_RANGE_PROTO_UPB_H__UPB_H_
#define XDS_TYPE_V3_RANGE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/type/v3/range.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_type_v3_Int64Range { upb_Message UPB_PRIVATE(base); } xds_type_v3_Int64Range;
typedef struct xds_type_v3_Int32Range { upb_Message UPB_PRIVATE(base); } xds_type_v3_Int32Range;
typedef struct xds_type_v3_DoubleRange { upb_Message UPB_PRIVATE(base); } xds_type_v3_DoubleRange;

UPB_INLINE xds_type_v3_Int64Range* xds_type_v3_Int64Range_new(upb_Arena* arena) {
  return (xds_type_v3_Int64Range*)_upb_Message_New(&xds__type__v3__Int64Range_msg_init, arena);
}
UPB_INLINE xds_type_v3_Int64Range* xds_type_v3_Int64Range_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_v3_Int64Range* ret = xds_type_v3_Int64Range_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__Int64Range_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_v3_Int64Range* xds_type_v3_Int64Range_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_v3_Int64Range* ret = xds_type_v3_Int64Range_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__Int64Range_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_v3_Int64Range_serialize(const xds_type_v3_Int64Range* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__Int64Range_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_v3_Int64Range_serialize_ex(const xds_type_v3_Int64Range* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__Int64Range_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_v3_Int64Range_clear_start(xds_type_v3_Int64Range* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t xds_type_v3_Int64Range_start(const xds_type_v3_Int64Range* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_type_v3_Int64Range_clear_end(xds_type_v3_Int64Range* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t xds_type_v3_Int64Range_end(const xds_type_v3_Int64Range* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_type_v3_Int64Range_set_start(xds_type_v3_Int64Range *msg, int64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_type_v3_Int64Range_set_end(xds_type_v3_Int64Range *msg, int64_t value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE xds_type_v3_Int32Range* xds_type_v3_Int32Range_new(upb_Arena* arena) {
  return (xds_type_v3_Int32Range*)_upb_Message_New(&xds__type__v3__Int32Range_msg_init, arena);
}
UPB_INLINE xds_type_v3_Int32Range* xds_type_v3_Int32Range_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_v3_Int32Range* ret = xds_type_v3_Int32Range_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__Int32Range_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_v3_Int32Range* xds_type_v3_Int32Range_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_v3_Int32Range* ret = xds_type_v3_Int32Range_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__Int32Range_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_v3_Int32Range_serialize(const xds_type_v3_Int32Range* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__Int32Range_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_v3_Int32Range_serialize_ex(const xds_type_v3_Int32Range* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__Int32Range_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_v3_Int32Range_clear_start(xds_type_v3_Int32Range* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t xds_type_v3_Int32Range_start(const xds_type_v3_Int32Range* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_type_v3_Int32Range_clear_end(xds_type_v3_Int32Range* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t xds_type_v3_Int32Range_end(const xds_type_v3_Int32Range* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_type_v3_Int32Range_set_start(xds_type_v3_Int32Range *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_type_v3_Int32Range_set_end(xds_type_v3_Int32Range *msg, int32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE xds_type_v3_DoubleRange* xds_type_v3_DoubleRange_new(upb_Arena* arena) {
  return (xds_type_v3_DoubleRange*)_upb_Message_New(&xds__type__v3__DoubleRange_msg_init, arena);
}
UPB_INLINE xds_type_v3_DoubleRange* xds_type_v3_DoubleRange_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_v3_DoubleRange* ret = xds_type_v3_DoubleRange_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__DoubleRange_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_v3_DoubleRange* xds_type_v3_DoubleRange_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_v3_DoubleRange* ret = xds_type_v3_DoubleRange_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__v3__DoubleRange_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_v3_DoubleRange_serialize(const xds_type_v3_DoubleRange* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__DoubleRange_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_v3_DoubleRange_serialize_ex(const xds_type_v3_DoubleRange* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__v3__DoubleRange_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_v3_DoubleRange_clear_start(xds_type_v3_DoubleRange* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_type_v3_DoubleRange_start(const xds_type_v3_DoubleRange* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_type_v3_DoubleRange_clear_end(xds_type_v3_DoubleRange* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_type_v3_DoubleRange_end(const xds_type_v3_DoubleRange* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_type_v3_DoubleRange_set_start(xds_type_v3_DoubleRange *msg, double value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_type_v3_DoubleRange_set_end(xds_type_v3_DoubleRange *msg, double value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
