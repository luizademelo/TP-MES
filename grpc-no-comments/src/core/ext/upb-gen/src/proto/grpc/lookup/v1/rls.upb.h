
#ifndef SRC_PROTO_GRPC_LOOKUP_V1_RLS_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_LOOKUP_V1_RLS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/lookup/v1/rls.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_lookup_v1_RouteLookupRequest { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_RouteLookupRequest;
typedef struct grpc_lookup_v1_RouteLookupResponse { upb_Message UPB_PRIVATE(base); } grpc_lookup_v1_RouteLookupResponse;

typedef enum {
  grpc_lookup_v1_RouteLookupRequest_REASON_UNKNOWN = 0,
  grpc_lookup_v1_RouteLookupRequest_REASON_MISS = 1,
  grpc_lookup_v1_RouteLookupRequest_REASON_STALE = 2
} grpc_lookup_v1_RouteLookupRequest_Reason;

UPB_INLINE grpc_lookup_v1_RouteLookupRequest* grpc_lookup_v1_RouteLookupRequest_new(upb_Arena* arena) {
  return (grpc_lookup_v1_RouteLookupRequest*)_upb_Message_New(&grpc__lookup__v1__RouteLookupRequest_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_RouteLookupRequest* grpc_lookup_v1_RouteLookupRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupRequest* ret = grpc_lookup_v1_RouteLookupRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_RouteLookupRequest* grpc_lookup_v1_RouteLookupRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupRequest* ret = grpc_lookup_v1_RouteLookupRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupRequest_serialize(const grpc_lookup_v1_RouteLookupRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupRequest_serialize_ex(const grpc_lookup_v1_RouteLookupRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_clear_target_type(grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_RouteLookupRequest_target_type(const grpc_lookup_v1_RouteLookupRequest* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_clear_key_map(grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t grpc_lookup_v1_RouteLookupRequest_key_map_size(const grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupRequest_key_map_get(const grpc_lookup_v1_RouteLookupRequest* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupRequest_key_map_next(const grpc_lookup_v1_RouteLookupRequest* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _grpc_lookup_v1_RouteLookupRequest_key_map_upb_map(grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _grpc_lookup_v1_RouteLookupRequest_key_map_mutable_upb_map(grpc_lookup_v1_RouteLookupRequest* msg, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_clear_reason(grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 8), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_lookup_v1_RouteLookupRequest_reason(const grpc_lookup_v1_RouteLookupRequest* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 8), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_clear_stale_header_data(grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_RouteLookupRequest_stale_header_data(const grpc_lookup_v1_RouteLookupRequest* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_set_target_type(grpc_lookup_v1_RouteLookupRequest *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_key_map_clear(grpc_lookup_v1_RouteLookupRequest* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupRequest_key_map_set(grpc_lookup_v1_RouteLookupRequest* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupRequest_key_map_delete(grpc_lookup_v1_RouteLookupRequest* msg, upb_StringView key) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_set_reason(grpc_lookup_v1_RouteLookupRequest *msg, int32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 8), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lookup_v1_RouteLookupRequest_set_stale_header_data(grpc_lookup_v1_RouteLookupRequest *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lookup_v1_RouteLookupResponse* grpc_lookup_v1_RouteLookupResponse_new(upb_Arena* arena) {
  return (grpc_lookup_v1_RouteLookupResponse*)_upb_Message_New(&grpc__lookup__v1__RouteLookupResponse_msg_init, arena);
}
UPB_INLINE grpc_lookup_v1_RouteLookupResponse* grpc_lookup_v1_RouteLookupResponse_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupResponse* ret = grpc_lookup_v1_RouteLookupResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupResponse_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lookup_v1_RouteLookupResponse* grpc_lookup_v1_RouteLookupResponse_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lookup_v1_RouteLookupResponse* ret = grpc_lookup_v1_RouteLookupResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lookup__v1__RouteLookupResponse_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupResponse_serialize(const grpc_lookup_v1_RouteLookupResponse* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupResponse_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lookup_v1_RouteLookupResponse_serialize_ex(const grpc_lookup_v1_RouteLookupResponse* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lookup__v1__RouteLookupResponse_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupResponse_clear_header_data(grpc_lookup_v1_RouteLookupResponse* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lookup_v1_RouteLookupResponse_header_data(const grpc_lookup_v1_RouteLookupResponse* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lookup_v1_RouteLookupResponse_clear_targets(grpc_lookup_v1_RouteLookupResponse* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_lookup_v1_RouteLookupResponse_targets(const grpc_lookup_v1_RouteLookupResponse* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lookup_v1_RouteLookupResponse_targets_upb_array(const grpc_lookup_v1_RouteLookupResponse* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lookup_v1_RouteLookupResponse_targets_mutable_upb_array(grpc_lookup_v1_RouteLookupResponse* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void grpc_lookup_v1_RouteLookupResponse_set_header_data(grpc_lookup_v1_RouteLookupResponse *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* grpc_lookup_v1_RouteLookupResponse_mutable_targets(grpc_lookup_v1_RouteLookupResponse* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_lookup_v1_RouteLookupResponse_resize_targets(grpc_lookup_v1_RouteLookupResponse* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_lookup_v1_RouteLookupResponse_add_targets(grpc_lookup_v1_RouteLookupResponse* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
