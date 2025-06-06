
#ifndef XDS_TYPE_MATCHER_V3_RANGE_PROTO_UPB_H__UPB_H_
#define XDS_TYPE_MATCHER_V3_RANGE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/type/matcher/v3/range.upb_minitable.h"

#include "xds/type/v3/range.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_type_matcher_v3_Int64RangeMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_Int64RangeMatcher;
typedef struct xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher;
typedef struct xds_type_matcher_v3_Int32RangeMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_Int32RangeMatcher;
typedef struct xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher;
typedef struct xds_type_matcher_v3_DoubleRangeMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_DoubleRangeMatcher;
typedef struct xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher;
struct xds_type_matcher_v3_Matcher_OnMatch;
struct xds_type_v3_DoubleRange;
struct xds_type_v3_Int32Range;
struct xds_type_v3_Int64Range;

UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_Int64RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__Int64RangeMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_Int64RangeMatcher* ret = xds_type_matcher_v3_Int64RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int64RangeMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_Int64RangeMatcher* ret = xds_type_matcher_v3_Int64RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int64RangeMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_Int64RangeMatcher_serialize(const xds_type_matcher_v3_Int64RangeMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int64RangeMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_Int64RangeMatcher_serialize_ex(const xds_type_matcher_v3_Int64RangeMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int64RangeMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_Int64RangeMatcher_clear_range_matchers(xds_type_matcher_v3_Int64RangeMatcher* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* const* xds_type_matcher_v3_Int64RangeMatcher_range_matchers(const xds_type_matcher_v3_Int64RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_Int64RangeMatcher_range_matchers_upb_array(const xds_type_matcher_v3_Int64RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_Int64RangeMatcher_range_matchers_mutable_upb_array(xds_type_matcher_v3_Int64RangeMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher** xds_type_matcher_v3_Int64RangeMatcher_mutable_range_matchers(xds_type_matcher_v3_Int64RangeMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher** xds_type_matcher_v3_Int64RangeMatcher_resize_range_matchers(xds_type_matcher_v3_Int64RangeMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_add_range_matchers(xds_type_matcher_v3_Int64RangeMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* sub = (struct xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* ret = xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* ret = xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_serialize(const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_serialize_ex(const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int64RangeMatcher__RangeMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_clear_ranges(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_v3_Int64Range* const* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_ranges(const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int64Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct xds_type_v3_Int64Range* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_ranges_upb_array(const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int64Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_ranges_mutable_upb_array(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_clear_on_match(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_on_match(const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg) {
  const struct xds_type_matcher_v3_Matcher_OnMatch* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher_OnMatch* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_has_on_match(const xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE struct xds_type_v3_Int64Range** xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_mutable_ranges(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct xds_type_v3_Int64Range**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct xds_type_v3_Int64Range** xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_resize_ranges(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct xds_type_v3_Int64Range**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_v3_Int64Range* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_add_ranges(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int64Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_v3_Int64Range* sub = (struct xds_type_v3_Int64Range*)_upb_Message_New(&xds__type__v3__Int64Range_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_set_on_match(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher *msg, struct xds_type_matcher_v3_Matcher_OnMatch* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_mutable_on_match(xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher_OnMatch* sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_on_match(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&xds__type__matcher__v3__Matcher__OnMatch_msg_init, arena);
    if (sub) xds_type_matcher_v3_Int64RangeMatcher_RangeMatcher_set_on_match(msg, sub);
  }
  return sub;
}

UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_Int32RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__Int32RangeMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_Int32RangeMatcher* ret = xds_type_matcher_v3_Int32RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int32RangeMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_Int32RangeMatcher* ret = xds_type_matcher_v3_Int32RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int32RangeMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_Int32RangeMatcher_serialize(const xds_type_matcher_v3_Int32RangeMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int32RangeMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_Int32RangeMatcher_serialize_ex(const xds_type_matcher_v3_Int32RangeMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int32RangeMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_Int32RangeMatcher_clear_range_matchers(xds_type_matcher_v3_Int32RangeMatcher* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* const* xds_type_matcher_v3_Int32RangeMatcher_range_matchers(const xds_type_matcher_v3_Int32RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_Int32RangeMatcher_range_matchers_upb_array(const xds_type_matcher_v3_Int32RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_Int32RangeMatcher_range_matchers_mutable_upb_array(xds_type_matcher_v3_Int32RangeMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher** xds_type_matcher_v3_Int32RangeMatcher_mutable_range_matchers(xds_type_matcher_v3_Int32RangeMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher** xds_type_matcher_v3_Int32RangeMatcher_resize_range_matchers(xds_type_matcher_v3_Int32RangeMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_add_range_matchers(xds_type_matcher_v3_Int32RangeMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* sub = (struct xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* ret = xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* ret = xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_serialize(const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_serialize_ex(const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__Int32RangeMatcher__RangeMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_clear_ranges(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_v3_Int32Range* const* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_ranges(const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int32Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct xds_type_v3_Int32Range* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_ranges_upb_array(const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int32Range_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_ranges_mutable_upb_array(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int32Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_clear_on_match(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_on_match(const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg) {
  const struct xds_type_matcher_v3_Matcher_OnMatch* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher_OnMatch* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_has_on_match(const xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE struct xds_type_v3_Int32Range** xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_mutable_ranges(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int32Range_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct xds_type_v3_Int32Range**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct xds_type_v3_Int32Range** xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_resize_ranges(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct xds_type_v3_Int32Range**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_v3_Int32Range* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_add_ranges(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__Int32Range_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_v3_Int32Range* sub = (struct xds_type_v3_Int32Range*)_upb_Message_New(&xds__type__v3__Int32Range_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_set_on_match(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher *msg, struct xds_type_matcher_v3_Matcher_OnMatch* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_mutable_on_match(xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher_OnMatch* sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_on_match(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&xds__type__matcher__v3__Matcher__OnMatch_msg_init, arena);
    if (sub) xds_type_matcher_v3_Int32RangeMatcher_RangeMatcher_set_on_match(msg, sub);
  }
  return sub;
}

UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_DoubleRangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__DoubleRangeMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_DoubleRangeMatcher* ret = xds_type_matcher_v3_DoubleRangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__DoubleRangeMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_DoubleRangeMatcher* ret = xds_type_matcher_v3_DoubleRangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__DoubleRangeMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_DoubleRangeMatcher_serialize(const xds_type_matcher_v3_DoubleRangeMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__DoubleRangeMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_DoubleRangeMatcher_serialize_ex(const xds_type_matcher_v3_DoubleRangeMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__DoubleRangeMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_DoubleRangeMatcher_clear_range_matchers(xds_type_matcher_v3_DoubleRangeMatcher* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* const* xds_type_matcher_v3_DoubleRangeMatcher_range_matchers(const xds_type_matcher_v3_DoubleRangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_DoubleRangeMatcher_range_matchers_upb_array(const xds_type_matcher_v3_DoubleRangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_DoubleRangeMatcher_range_matchers_mutable_upb_array(xds_type_matcher_v3_DoubleRangeMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher** xds_type_matcher_v3_DoubleRangeMatcher_mutable_range_matchers(xds_type_matcher_v3_DoubleRangeMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher** xds_type_matcher_v3_DoubleRangeMatcher_resize_range_matchers(xds_type_matcher_v3_DoubleRangeMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_add_range_matchers(xds_type_matcher_v3_DoubleRangeMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* sub = (struct xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher*)_upb_Message_New(&xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* ret = xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* ret = xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_serialize(const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_serialize_ex(const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__DoubleRangeMatcher__RangeMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_clear_ranges(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_v3_DoubleRange* const* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_ranges(const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__DoubleRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct xds_type_v3_DoubleRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_ranges_upb_array(const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__DoubleRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_ranges_mutable_upb_array(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__DoubleRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_clear_on_match(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_on_match(const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg) {
  const struct xds_type_matcher_v3_Matcher_OnMatch* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher_OnMatch* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_has_on_match(const xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE struct xds_type_v3_DoubleRange** xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_mutable_ranges(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__DoubleRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct xds_type_v3_DoubleRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct xds_type_v3_DoubleRange** xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_resize_ranges(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct xds_type_v3_DoubleRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_v3_DoubleRange* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_add_ranges(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__v3__DoubleRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_v3_DoubleRange* sub = (struct xds_type_v3_DoubleRange*)_upb_Message_New(&xds__type__v3__DoubleRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_set_on_match(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher *msg, struct xds_type_matcher_v3_Matcher_OnMatch* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_mutable_on_match(xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher_OnMatch* sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_on_match(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&xds__type__matcher__v3__Matcher__OnMatch_msg_init, arena);
    if (sub) xds_type_matcher_v3_DoubleRangeMatcher_RangeMatcher_set_on_match(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
