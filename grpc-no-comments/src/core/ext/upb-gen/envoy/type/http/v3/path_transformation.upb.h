
#ifndef ENVOY_TYPE_HTTP_V3_PATH_TRANSFORMATION_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_HTTP_V3_PATH_TRANSFORMATION_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/http/v3/path_transformation.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_http_v3_PathTransformation { upb_Message UPB_PRIVATE(base); } envoy_type_http_v3_PathTransformation;
typedef struct envoy_type_http_v3_PathTransformation_Operation { upb_Message UPB_PRIVATE(base); } envoy_type_http_v3_PathTransformation_Operation;
typedef struct envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986 { upb_Message UPB_PRIVATE(base); } envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986;
typedef struct envoy_type_http_v3_PathTransformation_Operation_MergeSlashes { upb_Message UPB_PRIVATE(base); } envoy_type_http_v3_PathTransformation_Operation_MergeSlashes;

UPB_INLINE envoy_type_http_v3_PathTransformation* envoy_type_http_v3_PathTransformation_new(upb_Arena* arena) {
  return (envoy_type_http_v3_PathTransformation*)_upb_Message_New(&envoy__type__http__v3__PathTransformation_msg_init, arena);
}
UPB_INLINE envoy_type_http_v3_PathTransformation* envoy_type_http_v3_PathTransformation_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation* ret = envoy_type_http_v3_PathTransformation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_http_v3_PathTransformation* envoy_type_http_v3_PathTransformation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation* ret = envoy_type_http_v3_PathTransformation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_serialize(const envoy_type_http_v3_PathTransformation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_serialize_ex(const envoy_type_http_v3_PathTransformation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_http_v3_PathTransformation_clear_operations(envoy_type_http_v3_PathTransformation* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_http_v3_PathTransformation_Operation* const* envoy_type_http_v3_PathTransformation_operations(const envoy_type_http_v3_PathTransformation* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_type_http_v3_PathTransformation_Operation* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_type_http_v3_PathTransformation_operations_upb_array(const envoy_type_http_v3_PathTransformation* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_type_http_v3_PathTransformation_operations_mutable_upb_array(envoy_type_http_v3_PathTransformation* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_type_http_v3_PathTransformation_Operation** envoy_type_http_v3_PathTransformation_mutable_operations(envoy_type_http_v3_PathTransformation* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_type_http_v3_PathTransformation_Operation**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation** envoy_type_http_v3_PathTransformation_resize_operations(envoy_type_http_v3_PathTransformation* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_http_v3_PathTransformation_Operation**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_http_v3_PathTransformation_Operation* envoy_type_http_v3_PathTransformation_add_operations(envoy_type_http_v3_PathTransformation* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_http_v3_PathTransformation_Operation* sub = (struct envoy_type_http_v3_PathTransformation_Operation*)_upb_Message_New(&envoy__type__http__v3__PathTransformation__Operation_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_type_http_v3_PathTransformation_Operation* envoy_type_http_v3_PathTransformation_Operation_new(upb_Arena* arena) {
  return (envoy_type_http_v3_PathTransformation_Operation*)_upb_Message_New(&envoy__type__http__v3__PathTransformation__Operation_msg_init, arena);
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation* envoy_type_http_v3_PathTransformation_Operation_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation_Operation* ret = envoy_type_http_v3_PathTransformation_Operation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation__Operation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation* envoy_type_http_v3_PathTransformation_Operation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation_Operation* ret = envoy_type_http_v3_PathTransformation_Operation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation__Operation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_Operation_serialize(const envoy_type_http_v3_PathTransformation_Operation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_Operation_serialize_ex(const envoy_type_http_v3_PathTransformation_Operation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_http_v3_PathTransformation_Operation_operation_specifier_normalize_path_rfc_3986 = 2,
  envoy_type_http_v3_PathTransformation_Operation_operation_specifier_merge_slashes = 3,
  envoy_type_http_v3_PathTransformation_Operation_operation_specifier_NOT_SET = 0
} envoy_type_http_v3_PathTransformation_Operation_operation_specifier_oneofcases;
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_operation_specifier_oneofcases envoy_type_http_v3_PathTransformation_Operation_operation_specifier_case(const envoy_type_http_v3_PathTransformation_Operation* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_http_v3_PathTransformation_Operation_operation_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_http_v3_PathTransformation_Operation_clear_operation_specifier(envoy_type_http_v3_PathTransformation_Operation* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation_msg_init, &field);
}
UPB_INLINE void envoy_type_http_v3_PathTransformation_Operation_clear_normalize_path_rfc_3986(envoy_type_http_v3_PathTransformation_Operation* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* envoy_type_http_v3_PathTransformation_Operation_normalize_path_rfc_3986(const envoy_type_http_v3_PathTransformation_Operation* msg) {
  const envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* default_val = NULL;
  const envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_http_v3_PathTransformation_Operation_has_normalize_path_rfc_3986(const envoy_type_http_v3_PathTransformation_Operation* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_http_v3_PathTransformation_Operation_clear_merge_slashes(envoy_type_http_v3_PathTransformation_Operation* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* envoy_type_http_v3_PathTransformation_Operation_merge_slashes(const envoy_type_http_v3_PathTransformation_Operation* msg) {
  const envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* default_val = NULL;
  const envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_http_v3_PathTransformation_Operation_has_merge_slashes(const envoy_type_http_v3_PathTransformation_Operation* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_http_v3_PathTransformation_Operation_set_normalize_path_rfc_3986(envoy_type_http_v3_PathTransformation_Operation *msg, envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* envoy_type_http_v3_PathTransformation_Operation_mutable_normalize_path_rfc_3986(envoy_type_http_v3_PathTransformation_Operation* msg, upb_Arena* arena) {
  struct envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* sub = (struct envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986*)envoy_type_http_v3_PathTransformation_Operation_normalize_path_rfc_3986(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986*)_upb_Message_New(&envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init, arena);
    if (sub) envoy_type_http_v3_PathTransformation_Operation_set_normalize_path_rfc_3986(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_http_v3_PathTransformation_Operation_set_merge_slashes(envoy_type_http_v3_PathTransformation_Operation *msg, envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* envoy_type_http_v3_PathTransformation_Operation_mutable_merge_slashes(envoy_type_http_v3_PathTransformation_Operation* msg, upb_Arena* arena) {
  struct envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* sub = (struct envoy_type_http_v3_PathTransformation_Operation_MergeSlashes*)envoy_type_http_v3_PathTransformation_Operation_merge_slashes(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_http_v3_PathTransformation_Operation_MergeSlashes*)_upb_Message_New(&envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init, arena);
    if (sub) envoy_type_http_v3_PathTransformation_Operation_set_merge_slashes(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_new(upb_Arena* arena) {
  return (envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986*)_upb_Message_New(&envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init, arena);
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* ret = envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* ret = envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_serialize(const envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986_serialize_ex(const envoy_type_http_v3_PathTransformation_Operation_NormalizePathRFC3986* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation__NormalizePathRFC3986_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_new(upb_Arena* arena) {
  return (envoy_type_http_v3_PathTransformation_Operation_MergeSlashes*)_upb_Message_New(&envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init, arena);
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* ret = envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* ret = envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_serialize(const envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_http_v3_PathTransformation_Operation_MergeSlashes_serialize_ex(const envoy_type_http_v3_PathTransformation_Operation_MergeSlashes* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__PathTransformation__Operation__MergeSlashes_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
