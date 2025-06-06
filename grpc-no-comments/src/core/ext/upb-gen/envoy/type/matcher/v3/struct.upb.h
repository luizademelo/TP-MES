
#ifndef ENVOY_TYPE_MATCHER_V3_STRUCT_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_MATCHER_V3_STRUCT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/matcher/v3/struct.upb_minitable.h"

#include "envoy/type/matcher/v3/value.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_matcher_v3_StructMatcher { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_StructMatcher;
typedef struct envoy_type_matcher_v3_StructMatcher_PathSegment { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_StructMatcher_PathSegment;
struct envoy_type_matcher_v3_ValueMatcher;

UPB_INLINE envoy_type_matcher_v3_StructMatcher* envoy_type_matcher_v3_StructMatcher_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_StructMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StructMatcher_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_StructMatcher* envoy_type_matcher_v3_StructMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_StructMatcher* ret = envoy_type_matcher_v3_StructMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__StructMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_StructMatcher* envoy_type_matcher_v3_StructMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_StructMatcher* ret = envoy_type_matcher_v3_StructMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__StructMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_StructMatcher_serialize(const envoy_type_matcher_v3_StructMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__StructMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_StructMatcher_serialize_ex(const envoy_type_matcher_v3_StructMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__StructMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_StructMatcher_clear_path(envoy_type_matcher_v3_StructMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_matcher_v3_StructMatcher_PathSegment* const* envoy_type_matcher_v3_StructMatcher_path(const envoy_type_matcher_v3_StructMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_type_matcher_v3_StructMatcher_PathSegment* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_type_matcher_v3_StructMatcher_path_upb_array(const envoy_type_matcher_v3_StructMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_type_matcher_v3_StructMatcher_path_mutable_upb_array(envoy_type_matcher_v3_StructMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_type_matcher_v3_StructMatcher_clear_value(envoy_type_matcher_v3_StructMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_StructMatcher_value(const envoy_type_matcher_v3_StructMatcher* msg) {
  const struct envoy_type_matcher_v3_ValueMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_ValueMatcher* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StructMatcher_has_value(const envoy_type_matcher_v3_StructMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE envoy_type_matcher_v3_StructMatcher_PathSegment** envoy_type_matcher_v3_StructMatcher_mutable_path(envoy_type_matcher_v3_StructMatcher* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_type_matcher_v3_StructMatcher_PathSegment**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_type_matcher_v3_StructMatcher_PathSegment** envoy_type_matcher_v3_StructMatcher_resize_path(envoy_type_matcher_v3_StructMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_StructMatcher_PathSegment**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_matcher_v3_StructMatcher_PathSegment* envoy_type_matcher_v3_StructMatcher_add_path(envoy_type_matcher_v3_StructMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_matcher_v3_StructMatcher_PathSegment* sub = (struct envoy_type_matcher_v3_StructMatcher_PathSegment*)_upb_Message_New(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_type_matcher_v3_StructMatcher_set_value(envoy_type_matcher_v3_StructMatcher *msg, struct envoy_type_matcher_v3_ValueMatcher* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ValueMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_ValueMatcher* envoy_type_matcher_v3_StructMatcher_mutable_value(envoy_type_matcher_v3_StructMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_ValueMatcher* sub = (struct envoy_type_matcher_v3_ValueMatcher*)envoy_type_matcher_v3_StructMatcher_value(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_ValueMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ValueMatcher_msg_init, arena);
    if (sub) envoy_type_matcher_v3_StructMatcher_set_value(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_matcher_v3_StructMatcher_PathSegment* envoy_type_matcher_v3_StructMatcher_PathSegment_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_StructMatcher_PathSegment*)_upb_Message_New(&envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_StructMatcher_PathSegment* envoy_type_matcher_v3_StructMatcher_PathSegment_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_StructMatcher_PathSegment* ret = envoy_type_matcher_v3_StructMatcher_PathSegment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_StructMatcher_PathSegment* envoy_type_matcher_v3_StructMatcher_PathSegment_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_StructMatcher_PathSegment* ret = envoy_type_matcher_v3_StructMatcher_PathSegment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_StructMatcher_PathSegment_serialize(const envoy_type_matcher_v3_StructMatcher_PathSegment* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_StructMatcher_PathSegment_serialize_ex(const envoy_type_matcher_v3_StructMatcher_PathSegment* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_matcher_v3_StructMatcher_PathSegment_segment_key = 1,
  envoy_type_matcher_v3_StructMatcher_PathSegment_segment_NOT_SET = 0
} envoy_type_matcher_v3_StructMatcher_PathSegment_segment_oneofcases;
UPB_INLINE envoy_type_matcher_v3_StructMatcher_PathSegment_segment_oneofcases envoy_type_matcher_v3_StructMatcher_PathSegment_segment_case(const envoy_type_matcher_v3_StructMatcher_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_type_matcher_v3_StructMatcher_PathSegment_segment_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_matcher_v3_StructMatcher_PathSegment_clear_segment(envoy_type_matcher_v3_StructMatcher_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__matcher__v3__StructMatcher__PathSegment_msg_init, &field);
}
UPB_INLINE void envoy_type_matcher_v3_StructMatcher_PathSegment_clear_key(envoy_type_matcher_v3_StructMatcher_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_StructMatcher_PathSegment_key(const envoy_type_matcher_v3_StructMatcher_PathSegment* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_matcher_v3_StructMatcher_PathSegment_has_key(const envoy_type_matcher_v3_StructMatcher_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_matcher_v3_StructMatcher_PathSegment_set_key(envoy_type_matcher_v3_StructMatcher_PathSegment *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
