
#ifndef ENVOY_TYPE_METADATA_V3_METADATA_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_METADATA_V3_METADATA_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/metadata/v3/metadata.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_metadata_v3_MetadataKey { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKey;
typedef struct envoy_type_metadata_v3_MetadataKey_PathSegment { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKey_PathSegment;
typedef struct envoy_type_metadata_v3_MetadataKind { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKind;
typedef struct envoy_type_metadata_v3_MetadataKind_Request { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKind_Request;
typedef struct envoy_type_metadata_v3_MetadataKind_Route { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKind_Route;
typedef struct envoy_type_metadata_v3_MetadataKind_Cluster { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKind_Cluster;
typedef struct envoy_type_metadata_v3_MetadataKind_Host { upb_Message UPB_PRIVATE(base); } envoy_type_metadata_v3_MetadataKind_Host;

UPB_INLINE envoy_type_metadata_v3_MetadataKey* envoy_type_metadata_v3_MetadataKey_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKey*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKey* envoy_type_metadata_v3_MetadataKey_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKey* ret = envoy_type_metadata_v3_MetadataKey_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKey_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKey* envoy_type_metadata_v3_MetadataKey_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKey* ret = envoy_type_metadata_v3_MetadataKey_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKey_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKey_serialize(const envoy_type_metadata_v3_MetadataKey* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKey_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKey_serialize_ex(const envoy_type_metadata_v3_MetadataKey* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKey_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKey_clear_key(envoy_type_metadata_v3_MetadataKey* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_metadata_v3_MetadataKey_key(const envoy_type_metadata_v3_MetadataKey* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKey_clear_path(envoy_type_metadata_v3_MetadataKey* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_metadata_v3_MetadataKey_PathSegment* const* envoy_type_metadata_v3_MetadataKey_path(const envoy_type_metadata_v3_MetadataKey* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_type_metadata_v3_MetadataKey_PathSegment* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_type_metadata_v3_MetadataKey_path_upb_array(const envoy_type_metadata_v3_MetadataKey* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_type_metadata_v3_MetadataKey_path_mutable_upb_array(envoy_type_metadata_v3_MetadataKey* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_type_metadata_v3_MetadataKey_set_key(envoy_type_metadata_v3_MetadataKey *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKey_PathSegment** envoy_type_metadata_v3_MetadataKey_mutable_path(envoy_type_metadata_v3_MetadataKey* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_type_metadata_v3_MetadataKey_PathSegment**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_type_metadata_v3_MetadataKey_PathSegment** envoy_type_metadata_v3_MetadataKey_resize_path(envoy_type_metadata_v3_MetadataKey* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_metadata_v3_MetadataKey_PathSegment**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKey_PathSegment* envoy_type_metadata_v3_MetadataKey_add_path(envoy_type_metadata_v3_MetadataKey* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_type_metadata_v3_MetadataKey_PathSegment* sub = (struct envoy_type_metadata_v3_MetadataKey_PathSegment*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_type_metadata_v3_MetadataKey_PathSegment* envoy_type_metadata_v3_MetadataKey_PathSegment_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKey_PathSegment*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKey_PathSegment* envoy_type_metadata_v3_MetadataKey_PathSegment_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKey_PathSegment* ret = envoy_type_metadata_v3_MetadataKey_PathSegment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKey_PathSegment* envoy_type_metadata_v3_MetadataKey_PathSegment_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKey_PathSegment* ret = envoy_type_metadata_v3_MetadataKey_PathSegment_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKey_PathSegment_serialize(const envoy_type_metadata_v3_MetadataKey_PathSegment* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKey_PathSegment_serialize_ex(const envoy_type_metadata_v3_MetadataKey_PathSegment* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_metadata_v3_MetadataKey_PathSegment_segment_key = 1,
  envoy_type_metadata_v3_MetadataKey_PathSegment_segment_NOT_SET = 0
} envoy_type_metadata_v3_MetadataKey_PathSegment_segment_oneofcases;
UPB_INLINE envoy_type_metadata_v3_MetadataKey_PathSegment_segment_oneofcases envoy_type_metadata_v3_MetadataKey_PathSegment_segment_case(const envoy_type_metadata_v3_MetadataKey_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_type_metadata_v3_MetadataKey_PathSegment_segment_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKey_PathSegment_clear_segment(envoy_type_metadata_v3_MetadataKey_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init, &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKey_PathSegment_clear_key(envoy_type_metadata_v3_MetadataKey_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_metadata_v3_MetadataKey_PathSegment_key(const envoy_type_metadata_v3_MetadataKey_PathSegment* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_metadata_v3_MetadataKey_PathSegment_has_key(const envoy_type_metadata_v3_MetadataKey_PathSegment* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_metadata_v3_MetadataKey_PathSegment_set_key(envoy_type_metadata_v3_MetadataKey_PathSegment *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_type_metadata_v3_MetadataKind* envoy_type_metadata_v3_MetadataKind_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKind*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind* envoy_type_metadata_v3_MetadataKind_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind* ret = envoy_type_metadata_v3_MetadataKind_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind* envoy_type_metadata_v3_MetadataKind_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind* ret = envoy_type_metadata_v3_MetadataKind_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_serialize(const envoy_type_metadata_v3_MetadataKind* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_serialize_ex(const envoy_type_metadata_v3_MetadataKind* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_type_metadata_v3_MetadataKind_kind_request = 1,
  envoy_type_metadata_v3_MetadataKind_kind_route = 2,
  envoy_type_metadata_v3_MetadataKind_kind_cluster = 3,
  envoy_type_metadata_v3_MetadataKind_kind_host = 4,
  envoy_type_metadata_v3_MetadataKind_kind_NOT_SET = 0
} envoy_type_metadata_v3_MetadataKind_kind_oneofcases;
UPB_INLINE envoy_type_metadata_v3_MetadataKind_kind_oneofcases envoy_type_metadata_v3_MetadataKind_kind_case(const envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_type_metadata_v3_MetadataKind_kind_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_clear_kind(envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind_msg_init, &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_clear_request(envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_metadata_v3_MetadataKind_Request* envoy_type_metadata_v3_MetadataKind_request(const envoy_type_metadata_v3_MetadataKind* msg) {
  const envoy_type_metadata_v3_MetadataKind_Request* default_val = NULL;
  const envoy_type_metadata_v3_MetadataKind_Request* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Request_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_metadata_v3_MetadataKind_has_request(const envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_clear_route(envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_metadata_v3_MetadataKind_Route* envoy_type_metadata_v3_MetadataKind_route(const envoy_type_metadata_v3_MetadataKind* msg) {
  const envoy_type_metadata_v3_MetadataKind_Route* default_val = NULL;
  const envoy_type_metadata_v3_MetadataKind_Route* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Route_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_metadata_v3_MetadataKind_has_route(const envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_clear_cluster(envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_metadata_v3_MetadataKind_Cluster* envoy_type_metadata_v3_MetadataKind_cluster(const envoy_type_metadata_v3_MetadataKind* msg) {
  const envoy_type_metadata_v3_MetadataKind_Cluster* default_val = NULL;
  const envoy_type_metadata_v3_MetadataKind_Cluster* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Cluster_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_metadata_v3_MetadataKind_has_cluster(const envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_clear_host(envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_type_metadata_v3_MetadataKind_Host* envoy_type_metadata_v3_MetadataKind_host(const envoy_type_metadata_v3_MetadataKind* msg) {
  const envoy_type_metadata_v3_MetadataKind_Host* default_val = NULL;
  const envoy_type_metadata_v3_MetadataKind_Host* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Host_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_metadata_v3_MetadataKind_has_host(const envoy_type_metadata_v3_MetadataKind* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_type_metadata_v3_MetadataKind_set_request(envoy_type_metadata_v3_MetadataKind *msg, envoy_type_metadata_v3_MetadataKind_Request* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Request_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKind_Request* envoy_type_metadata_v3_MetadataKind_mutable_request(envoy_type_metadata_v3_MetadataKind* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKind_Request* sub = (struct envoy_type_metadata_v3_MetadataKind_Request*)envoy_type_metadata_v3_MetadataKind_request(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKind_Request*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Request_msg_init, arena);
    if (sub) envoy_type_metadata_v3_MetadataKind_set_request(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_set_route(envoy_type_metadata_v3_MetadataKind *msg, envoy_type_metadata_v3_MetadataKind_Route* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Route_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKind_Route* envoy_type_metadata_v3_MetadataKind_mutable_route(envoy_type_metadata_v3_MetadataKind* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKind_Route* sub = (struct envoy_type_metadata_v3_MetadataKind_Route*)envoy_type_metadata_v3_MetadataKind_route(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKind_Route*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Route_msg_init, arena);
    if (sub) envoy_type_metadata_v3_MetadataKind_set_route(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_set_cluster(envoy_type_metadata_v3_MetadataKind *msg, envoy_type_metadata_v3_MetadataKind_Cluster* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Cluster_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKind_Cluster* envoy_type_metadata_v3_MetadataKind_mutable_cluster(envoy_type_metadata_v3_MetadataKind* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKind_Cluster* sub = (struct envoy_type_metadata_v3_MetadataKind_Cluster*)envoy_type_metadata_v3_MetadataKind_cluster(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKind_Cluster*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Cluster_msg_init, arena);
    if (sub) envoy_type_metadata_v3_MetadataKind_set_cluster(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_metadata_v3_MetadataKind_set_host(envoy_type_metadata_v3_MetadataKind *msg, envoy_type_metadata_v3_MetadataKind_Host* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__metadata__v3__MetadataKind__Host_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_metadata_v3_MetadataKind_Host* envoy_type_metadata_v3_MetadataKind_mutable_host(envoy_type_metadata_v3_MetadataKind* msg, upb_Arena* arena) {
  struct envoy_type_metadata_v3_MetadataKind_Host* sub = (struct envoy_type_metadata_v3_MetadataKind_Host*)envoy_type_metadata_v3_MetadataKind_host(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_metadata_v3_MetadataKind_Host*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Host_msg_init, arena);
    if (sub) envoy_type_metadata_v3_MetadataKind_set_host(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_type_metadata_v3_MetadataKind_Request* envoy_type_metadata_v3_MetadataKind_Request_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKind_Request*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Request_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Request* envoy_type_metadata_v3_MetadataKind_Request_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Request* ret = envoy_type_metadata_v3_MetadataKind_Request_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Request_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Request* envoy_type_metadata_v3_MetadataKind_Request_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Request* ret = envoy_type_metadata_v3_MetadataKind_Request_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Request_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Request_serialize(const envoy_type_metadata_v3_MetadataKind_Request* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Request_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Request_serialize_ex(const envoy_type_metadata_v3_MetadataKind_Request* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Request_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_type_metadata_v3_MetadataKind_Route* envoy_type_metadata_v3_MetadataKind_Route_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKind_Route*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Route_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Route* envoy_type_metadata_v3_MetadataKind_Route_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Route* ret = envoy_type_metadata_v3_MetadataKind_Route_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Route_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Route* envoy_type_metadata_v3_MetadataKind_Route_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Route* ret = envoy_type_metadata_v3_MetadataKind_Route_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Route_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Route_serialize(const envoy_type_metadata_v3_MetadataKind_Route* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Route_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Route_serialize_ex(const envoy_type_metadata_v3_MetadataKind_Route* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Route_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_type_metadata_v3_MetadataKind_Cluster* envoy_type_metadata_v3_MetadataKind_Cluster_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKind_Cluster*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Cluster_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Cluster* envoy_type_metadata_v3_MetadataKind_Cluster_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Cluster* ret = envoy_type_metadata_v3_MetadataKind_Cluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Cluster* envoy_type_metadata_v3_MetadataKind_Cluster_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Cluster* ret = envoy_type_metadata_v3_MetadataKind_Cluster_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Cluster_serialize(const envoy_type_metadata_v3_MetadataKind_Cluster* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Cluster_serialize_ex(const envoy_type_metadata_v3_MetadataKind_Cluster* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_type_metadata_v3_MetadataKind_Host* envoy_type_metadata_v3_MetadataKind_Host_new(upb_Arena* arena) {
  return (envoy_type_metadata_v3_MetadataKind_Host*)_upb_Message_New(&envoy__type__metadata__v3__MetadataKind__Host_msg_init, arena);
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Host* envoy_type_metadata_v3_MetadataKind_Host_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Host* ret = envoy_type_metadata_v3_MetadataKind_Host_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Host_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_metadata_v3_MetadataKind_Host* envoy_type_metadata_v3_MetadataKind_Host_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_metadata_v3_MetadataKind_Host* ret = envoy_type_metadata_v3_MetadataKind_Host_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__metadata__v3__MetadataKind__Host_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Host_serialize(const envoy_type_metadata_v3_MetadataKind_Host* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Host_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_metadata_v3_MetadataKind_Host_serialize_ex(const envoy_type_metadata_v3_MetadataKind_Host* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__metadata__v3__MetadataKind__Host_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
