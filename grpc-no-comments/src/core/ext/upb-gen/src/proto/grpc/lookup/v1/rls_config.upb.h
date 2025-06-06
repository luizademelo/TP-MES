
#ifndef SRC_PROTO_GRPC_LOOKUP_V1_RLS_CONFIG_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_LOOKUP_V1_RLS_CONFIG_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/lookup/v1/rls_config.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_lookup_v1_NameMatcher { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_NameMatcher;
typedef struct grpc_lookup_v1_GrpcKeyBuilder { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_GrpcKeyBuilder;
typedef struct grpc_lookup_v1_GrpcKeyBuilder_Name { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_GrpcKeyBuilder_Name;
typedef struct grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys;
typedef struct grpc_lookup_v1_HttpKeyBuilder { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_HttpKeyBuilder;
typedef struct grpc_lookup_v1_RouteLookupConfig { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_RouteLookupConfig;
typedef struct grpc_lookup_v1_RouteLookupClusterSpecifier { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_RouteLookupClusterSpecifier;
struct google_protobuf_Duration;

UPB_INLINE grpc_lookup_v1_NameMatcher* grpc_lookup_v1_NameMatcher_new(upb_Arena* arena) {
  return (grpc_lookup_v1_NameMatcher*)_upb_Message_New(&grpc__lookup__v1__NameMatcher_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_NameMatcher* grpc_lookup_v1_NameMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_NameMatcher* ret = grpc_lookup_v1_NameMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__NameMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_NameMatcher* grpc_lookup_v1_NameMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_NameMatcher* ret = grpc_lookup_v1_NameMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__NameMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_NameMatcher_serialize(const grpc_lookup_v1_NameMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__NameMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_NameMatcher_serialize_ex(const grpc_lookup_v1_NameMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__NameMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_NameMatcher_clear_key(grpc_lookup_v1_NameMatcher* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_NameMatcher_key(const grpc_lookup_v1_NameMatcher* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_NameMatcher_clear_names(grpc_lookup_v1_NameMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_lookup_v1_NameMatcher_names(const grpc_lookup_v1_NameMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_NameMatcher_names_upb_array(const grpc_lookup_v1_NameMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_NameMatcher_names_mutable_upb_array(grpc_lookup_v1_NameMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_NameMatcher_clear_required_match(grpc_lookup_v1_NameMatcher* msg) {
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool grpc_lookup_v1_NameMatcher_required_match(const grpc_lookup_v1_NameMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lookup_v1_NameMatcher_set_key(grpc_lookup_v1_NameMatcher *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* grpc_lookup_v1_NameMatcher_mutable_names(grpc_lookup_v1_NameMatcher* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_lookup_v1_NameMatcher_resize_names(grpc_lookup_v1_NameMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_lookup_v1_NameMatcher_add_names(grpc_lookup_v1_NameMatcher* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void grpc_lookup_v1_NameMatcher_set_required_match(grpc_lookup_v1_NameMatcher *msg, bool value) {
  const upb_MiniTableField field = {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder* grpc_lookup_v1_GrpcKeyBuilder_new(upb_Arena* arena) {
  return (grpc_lookup_v1_GrpcKeyBuilder*)_upb_Message_New(&grpc__lookup__v1__GrpcKeyBuilder_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder* grpc_lookup_v1_GrpcKeyBuilder_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_GrpcKeyBuilder* ret = grpc_lookup_v1_GrpcKeyBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__GrpcKeyBuilder_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder* grpc_lookup_v1_GrpcKeyBuilder_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_GrpcKeyBuilder* ret = grpc_lookup_v1_GrpcKeyBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__GrpcKeyBuilder_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_GrpcKeyBuilder_serialize(const grpc_lookup_v1_GrpcKeyBuilder* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__GrpcKeyBuilder_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_GrpcKeyBuilder_serialize_ex(const grpc_lookup_v1_GrpcKeyBuilder* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__GrpcKeyBuilder_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_clear_names(grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_GrpcKeyBuilder_Name* const* grpc_lookup_v1_GrpcKeyBuilder_names(const grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lookup_v1_GrpcKeyBuilder_Name* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_GrpcKeyBuilder_names_upb_array(const grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_GrpcKeyBuilder_names_mutable_upb_array(grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_clear_headers(grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_NameMatcher* const* grpc_lookup_v1_GrpcKeyBuilder_headers(const grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lookup_v1_NameMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_GrpcKeyBuilder_headers_upb_array(const grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_GrpcKeyBuilder_headers_mutable_upb_array(grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_clear_extra_keys(grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* grpc_lookup_v1_GrpcKeyBuilder_extra_keys(const grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* default_val = NULL;
  const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lookup_v1_GrpcKeyBuilder_has_extra_keys(const grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_clear_constant_keys(grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t grpc_lookup_v1_GrpcKeyBuilder_constant_keys_size(const grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool grpc_lookup_v1_GrpcKeyBuilder_constant_keys_get(const grpc_lookup_v1_GrpcKeyBuilder* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool grpc_lookup_v1_GrpcKeyBuilder_constant_keys_next(const grpc_lookup_v1_GrpcKeyBuilder* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _grpc_lookup_v1_GrpcKeyBuilder_constant_keys_upb_map(grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _grpc_lookup_v1_GrpcKeyBuilder_constant_keys_mutable_upb_map(grpc_lookup_v1_GrpcKeyBuilder* msg, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}

UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_Name** grpc_lookup_v1_GrpcKeyBuilder_mutable_names(grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lookup_v1_GrpcKeyBuilder_Name**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_Name** grpc_lookup_v1_GrpcKeyBuilder_resize_names(grpc_lookup_v1_GrpcKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lookup_v1_GrpcKeyBuilder_Name**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lookup_v1_GrpcKeyBuilder_Name* grpc_lookup_v1_GrpcKeyBuilder_add_names(grpc_lookup_v1_GrpcKeyBuilder* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lookup_v1_GrpcKeyBuilder_Name* sub = (struct grpc_lookup_v1_GrpcKeyBuilder_Name*)_upb_Message_New(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE grpc_lookup_v1_NameMatcher** grpc_lookup_v1_GrpcKeyBuilder_mutable_headers(grpc_lookup_v1_GrpcKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lookup_v1_NameMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lookup_v1_NameMatcher** grpc_lookup_v1_GrpcKeyBuilder_resize_headers(grpc_lookup_v1_GrpcKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lookup_v1_NameMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lookup_v1_NameMatcher* grpc_lookup_v1_GrpcKeyBuilder_add_headers(grpc_lookup_v1_GrpcKeyBuilder* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lookup_v1_NameMatcher* sub = (struct grpc_lookup_v1_NameMatcher*)_upb_Message_New(&grpc__lookup__v1__NameMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_set_extra_keys(grpc_lookup_v1_GrpcKeyBuilder *msg, grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* grpc_lookup_v1_GrpcKeyBuilder_mutable_extra_keys(grpc_lookup_v1_GrpcKeyBuilder* msg, upb_Arena* arena) {
  struct grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* sub = (struct grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys*)grpc_lookup_v1_GrpcKeyBuilder_extra_keys(msg);
  if (sub == NULL) {
    sub = (struct grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys*)_upb_Message_New(&grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init, arena);
    if (sub) grpc_lookup_v1_GrpcKeyBuilder_set_extra_keys(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_constant_keys_clear(grpc_lookup_v1_GrpcKeyBuilder* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool grpc_lookup_v1_GrpcKeyBuilder_constant_keys_set(grpc_lookup_v1_GrpcKeyBuilder* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool grpc_lookup_v1_GrpcKeyBuilder_constant_keys_delete(grpc_lookup_v1_GrpcKeyBuilder* msg, upb_StringView key) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_Name* grpc_lookup_v1_GrpcKeyBuilder_Name_new(upb_Arena* arena) {
  return (grpc_lookup_v1_GrpcKeyBuilder_Name*)_upb_Message_New(&grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_Name* grpc_lookup_v1_GrpcKeyBuilder_Name_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_GrpcKeyBuilder_Name* ret = grpc_lookup_v1_GrpcKeyBuilder_Name_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_Name* grpc_lookup_v1_GrpcKeyBuilder_Name_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_GrpcKeyBuilder_Name* ret = grpc_lookup_v1_GrpcKeyBuilder_Name_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_GrpcKeyBuilder_Name_serialize(const grpc_lookup_v1_GrpcKeyBuilder_Name* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_GrpcKeyBuilder_Name_serialize_ex(const grpc_lookup_v1_GrpcKeyBuilder_Name* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_Name_clear_service(grpc_lookup_v1_GrpcKeyBuilder_Name* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_GrpcKeyBuilder_Name_service(const grpc_lookup_v1_GrpcKeyBuilder_Name* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_Name_clear_method(grpc_lookup_v1_GrpcKeyBuilder_Name* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_GrpcKeyBuilder_Name_method(const grpc_lookup_v1_GrpcKeyBuilder_Name* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_Name_set_service(grpc_lookup_v1_GrpcKeyBuilder_Name *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_Name_set_method(grpc_lookup_v1_GrpcKeyBuilder_Name *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_new(upb_Arena* arena) {
  return (grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys*)_upb_Message_New(&grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* ret = grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* ret = grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_serialize(const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_serialize_ex(const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_clear_host(grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_host(const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_clear_service(grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_service(const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_clear_method(grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_method(const grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_set_host(grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_set_service(grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys_set_method(grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lookup_v1_HttpKeyBuilder* grpc_lookup_v1_HttpKeyBuilder_new(upb_Arena* arena) {
  return (grpc_lookup_v1_HttpKeyBuilder*)_upb_Message_New(&grpc__lookup__v1__HttpKeyBuilder_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_HttpKeyBuilder* grpc_lookup_v1_HttpKeyBuilder_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_HttpKeyBuilder* ret = grpc_lookup_v1_HttpKeyBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__HttpKeyBuilder_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_HttpKeyBuilder* grpc_lookup_v1_HttpKeyBuilder_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_HttpKeyBuilder* ret = grpc_lookup_v1_HttpKeyBuilder_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__HttpKeyBuilder_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_HttpKeyBuilder_serialize(const grpc_lookup_v1_HttpKeyBuilder* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__HttpKeyBuilder_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_HttpKeyBuilder_serialize_ex(const grpc_lookup_v1_HttpKeyBuilder* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__HttpKeyBuilder_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_HttpKeyBuilder_clear_host_patterns(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_lookup_v1_HttpKeyBuilder_host_patterns(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_HttpKeyBuilder_host_patterns_upb_array(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_HttpKeyBuilder_host_patterns_mutable_upb_array(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_HttpKeyBuilder_clear_path_patterns(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_lookup_v1_HttpKeyBuilder_path_patterns(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_HttpKeyBuilder_path_patterns_upb_array(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_HttpKeyBuilder_path_patterns_mutable_upb_array(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_HttpKeyBuilder_clear_query_parameters(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_NameMatcher* const* grpc_lookup_v1_HttpKeyBuilder_query_parameters(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lookup_v1_NameMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_HttpKeyBuilder_query_parameters_upb_array(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_HttpKeyBuilder_query_parameters_mutable_upb_array(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_HttpKeyBuilder_clear_headers(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_NameMatcher* const* grpc_lookup_v1_HttpKeyBuilder_headers(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lookup_v1_NameMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_HttpKeyBuilder_headers_upb_array(const grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_HttpKeyBuilder_headers_mutable_upb_array(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_HttpKeyBuilder_clear_constant_keys(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t grpc_lookup_v1_HttpKeyBuilder_constant_keys_size(const grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool grpc_lookup_v1_HttpKeyBuilder_constant_keys_get(const grpc_lookup_v1_HttpKeyBuilder* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool grpc_lookup_v1_HttpKeyBuilder_constant_keys_next(const grpc_lookup_v1_HttpKeyBuilder* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _grpc_lookup_v1_HttpKeyBuilder_constant_keys_upb_map(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _grpc_lookup_v1_HttpKeyBuilder_constant_keys_mutable_upb_map(grpc_lookup_v1_HttpKeyBuilder* msg, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}

UPB_INLINE upb_StringView* grpc_lookup_v1_HttpKeyBuilder_mutable_host_patterns(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_lookup_v1_HttpKeyBuilder_resize_host_patterns(grpc_lookup_v1_HttpKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_lookup_v1_HttpKeyBuilder_add_host_patterns(grpc_lookup_v1_HttpKeyBuilder* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* grpc_lookup_v1_HttpKeyBuilder_mutable_path_patterns(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_lookup_v1_HttpKeyBuilder_resize_path_patterns(grpc_lookup_v1_HttpKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_lookup_v1_HttpKeyBuilder_add_path_patterns(grpc_lookup_v1_HttpKeyBuilder* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE grpc_lookup_v1_NameMatcher** grpc_lookup_v1_HttpKeyBuilder_mutable_query_parameters(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lookup_v1_NameMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lookup_v1_NameMatcher** grpc_lookup_v1_HttpKeyBuilder_resize_query_parameters(grpc_lookup_v1_HttpKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lookup_v1_NameMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lookup_v1_NameMatcher* grpc_lookup_v1_HttpKeyBuilder_add_query_parameters(grpc_lookup_v1_HttpKeyBuilder* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lookup_v1_NameMatcher* sub = (struct grpc_lookup_v1_NameMatcher*)_upb_Message_New(&grpc__lookup__v1__NameMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE grpc_lookup_v1_NameMatcher** grpc_lookup_v1_HttpKeyBuilder_mutable_headers(grpc_lookup_v1_HttpKeyBuilder* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lookup_v1_NameMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lookup_v1_NameMatcher** grpc_lookup_v1_HttpKeyBuilder_resize_headers(grpc_lookup_v1_HttpKeyBuilder* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lookup_v1_NameMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lookup_v1_NameMatcher* grpc_lookup_v1_HttpKeyBuilder_add_headers(grpc_lookup_v1_HttpKeyBuilder* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__NameMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lookup_v1_NameMatcher* sub = (struct grpc_lookup_v1_NameMatcher*)_upb_Message_New(&grpc__lookup__v1__NameMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void grpc_lookup_v1_HttpKeyBuilder_constant_keys_clear(grpc_lookup_v1_HttpKeyBuilder* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool grpc_lookup_v1_HttpKeyBuilder_constant_keys_set(grpc_lookup_v1_HttpKeyBuilder* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool grpc_lookup_v1_HttpKeyBuilder_constant_keys_delete(grpc_lookup_v1_HttpKeyBuilder* msg, upb_StringView key) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE grpc_lookup_v1_RouteLookupConfig* grpc_lookup_v1_RouteLookupConfig_new(upb_Arena* arena) {
  return (grpc_lookup_v1_RouteLookupConfig*)_upb_Message_New(&grpc__lookup__v1__RouteLookupConfig_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_RouteLookupConfig* grpc_lookup_v1_RouteLookupConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupConfig* ret = grpc_lookup_v1_RouteLookupConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_RouteLookupConfig* grpc_lookup_v1_RouteLookupConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupConfig* ret = grpc_lookup_v1_RouteLookupConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupConfig_serialize(const grpc_lookup_v1_RouteLookupConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupConfig_serialize_ex(const grpc_lookup_v1_RouteLookupConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_http_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_HttpKeyBuilder* const* grpc_lookup_v1_RouteLookupConfig_http_keybuilders(const grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lookup_v1_HttpKeyBuilder* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_RouteLookupConfig_http_keybuilders_upb_array(const grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_RouteLookupConfig_http_keybuilders_mutable_upb_array(grpc_lookup_v1_RouteLookupConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_grpc_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_GrpcKeyBuilder* const* grpc_lookup_v1_RouteLookupConfig_grpc_keybuilders(const grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lookup_v1_GrpcKeyBuilder* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_RouteLookupConfig_grpc_keybuilders_upb_array(const grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_RouteLookupConfig_grpc_keybuilders_mutable_upb_array(grpc_lookup_v1_RouteLookupConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_lookup_service(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_RouteLookupConfig_lookup_service(const grpc_lookup_v1_RouteLookupConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_lookup_service_timeout(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* grpc_lookup_v1_RouteLookupConfig_lookup_service_timeout(const grpc_lookup_v1_RouteLookupConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupConfig_has_lookup_service_timeout(const grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_max_age(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* grpc_lookup_v1_RouteLookupConfig_max_age(const grpc_lookup_v1_RouteLookupConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupConfig_has_max_age(const grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_stale_age(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 80), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* grpc_lookup_v1_RouteLookupConfig_stale_age(const grpc_lookup_v1_RouteLookupConfig* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 80), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupConfig_has_stale_age(const grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 80), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_cache_size_bytes(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 88), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t grpc_lookup_v1_RouteLookupConfig_cache_size_bytes(const grpc_lookup_v1_RouteLookupConfig* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {7, UPB_SIZE(56, 88), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_valid_targets(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_lookup_v1_RouteLookupConfig_valid_targets(const grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_RouteLookupConfig_valid_targets_upb_array(const grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_RouteLookupConfig_valid_targets_mutable_upb_array(grpc_lookup_v1_RouteLookupConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_clear_default_target(grpc_lookup_v1_RouteLookupConfig* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_RouteLookupConfig_default_target(const grpc_lookup_v1_RouteLookupConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(44, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE grpc_lookup_v1_HttpKeyBuilder** grpc_lookup_v1_RouteLookupConfig_mutable_http_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lookup_v1_HttpKeyBuilder**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lookup_v1_HttpKeyBuilder** grpc_lookup_v1_RouteLookupConfig_resize_http_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lookup_v1_HttpKeyBuilder**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lookup_v1_HttpKeyBuilder* grpc_lookup_v1_RouteLookupConfig_add_http_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__HttpKeyBuilder_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lookup_v1_HttpKeyBuilder* sub = (struct grpc_lookup_v1_HttpKeyBuilder*)_upb_Message_New(&grpc__lookup__v1__HttpKeyBuilder_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder** grpc_lookup_v1_RouteLookupConfig_mutable_grpc_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lookup_v1_GrpcKeyBuilder**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lookup_v1_GrpcKeyBuilder** grpc_lookup_v1_RouteLookupConfig_resize_grpc_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lookup_v1_GrpcKeyBuilder**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lookup_v1_GrpcKeyBuilder* grpc_lookup_v1_RouteLookupConfig_add_grpc_keybuilders(grpc_lookup_v1_RouteLookupConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__GrpcKeyBuilder_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lookup_v1_GrpcKeyBuilder* sub = (struct grpc_lookup_v1_GrpcKeyBuilder*)_upb_Message_New(&grpc__lookup__v1__GrpcKeyBuilder_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_set_lookup_service(grpc_lookup_v1_RouteLookupConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_set_lookup_service_timeout(grpc_lookup_v1_RouteLookupConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 64), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* grpc_lookup_v1_RouteLookupConfig_mutable_lookup_service_timeout(grpc_lookup_v1_RouteLookupConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)grpc_lookup_v1_RouteLookupConfig_lookup_service_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) grpc_lookup_v1_RouteLookupConfig_set_lookup_service_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_set_max_age(grpc_lookup_v1_RouteLookupConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 72), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* grpc_lookup_v1_RouteLookupConfig_mutable_max_age(grpc_lookup_v1_RouteLookupConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)grpc_lookup_v1_RouteLookupConfig_max_age(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) grpc_lookup_v1_RouteLookupConfig_set_max_age(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_set_stale_age(grpc_lookup_v1_RouteLookupConfig *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 80), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* grpc_lookup_v1_RouteLookupConfig_mutable_stale_age(grpc_lookup_v1_RouteLookupConfig* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)grpc_lookup_v1_RouteLookupConfig_stale_age(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) grpc_lookup_v1_RouteLookupConfig_set_stale_age(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_set_cache_size_bytes(grpc_lookup_v1_RouteLookupConfig *msg, int64_t value) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 88), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* grpc_lookup_v1_RouteLookupConfig_mutable_valid_targets(grpc_lookup_v1_RouteLookupConfig* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_lookup_v1_RouteLookupConfig_resize_valid_targets(grpc_lookup_v1_RouteLookupConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupConfig_add_valid_targets(grpc_lookup_v1_RouteLookupConfig* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void grpc_lookup_v1_RouteLookupConfig_set_default_target(grpc_lookup_v1_RouteLookupConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lookup_v1_RouteLookupClusterSpecifier* grpc_lookup_v1_RouteLookupClusterSpecifier_new(upb_Arena* arena) {
  return (grpc_lookup_v1_RouteLookupClusterSpecifier*)_upb_Message_New(&grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_RouteLookupClusterSpecifier* grpc_lookup_v1_RouteLookupClusterSpecifier_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupClusterSpecifier* ret = grpc_lookup_v1_RouteLookupClusterSpecifier_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_RouteLookupClusterSpecifier* grpc_lookup_v1_RouteLookupClusterSpecifier_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupClusterSpecifier* ret = grpc_lookup_v1_RouteLookupClusterSpecifier_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupClusterSpecifier_serialize(const grpc_lookup_v1_RouteLookupClusterSpecifier* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupClusterSpecifier_serialize_ex(const grpc_lookup_v1_RouteLookupClusterSpecifier* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupClusterSpecifier_clear_route_lookup_config(grpc_lookup_v1_RouteLookupClusterSpecifier* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lookup_v1_RouteLookupConfig* grpc_lookup_v1_RouteLookupClusterSpecifier_route_lookup_config(const grpc_lookup_v1_RouteLookupClusterSpecifier* msg) {
  const grpc_lookup_v1_RouteLookupConfig* default_val = NULL;
  const grpc_lookup_v1_RouteLookupConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupClusterSpecifier_has_route_lookup_config(const grpc_lookup_v1_RouteLookupClusterSpecifier* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_lookup_v1_RouteLookupClusterSpecifier_set_route_lookup_config(grpc_lookup_v1_RouteLookupClusterSpecifier *msg, grpc_lookup_v1_RouteLookupConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lookup_v1_RouteLookupConfig* grpc_lookup_v1_RouteLookupClusterSpecifier_mutable_route_lookup_config(grpc_lookup_v1_RouteLookupClusterSpecifier* msg, upb_Arena* arena) {
  struct grpc_lookup_v1_RouteLookupConfig* sub = (struct grpc_lookup_v1_RouteLookupConfig*)grpc_lookup_v1_RouteLookupClusterSpecifier_route_lookup_config(msg);
  if (sub == NULL) {
    sub = (struct grpc_lookup_v1_RouteLookupConfig*)_upb_Message_New(&grpc__lookup__v1__RouteLookupConfig_msg_init, arena);
    if (sub) grpc_lookup_v1_RouteLookupClusterSpecifier_set_route_lookup_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
