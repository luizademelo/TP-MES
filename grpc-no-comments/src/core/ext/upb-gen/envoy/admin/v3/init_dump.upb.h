
#ifndef ENVOY_ADMIN_V3_INIT_DUMP_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_INIT_DUMP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/init_dump.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_UnreadyTargetsDumps { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_UnreadyTargetsDumps;
typedef struct envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump;

UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps* envoy_admin_v3_UnreadyTargetsDumps_new(upb_Arena* arena) {
  return (envoy_admin_v3_UnreadyTargetsDumps*)_upb_Message_New(&envoy__admin__v3__UnreadyTargetsDumps_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps* envoy_admin_v3_UnreadyTargetsDumps_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_UnreadyTargetsDumps* ret = envoy_admin_v3_UnreadyTargetsDumps_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__UnreadyTargetsDumps_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps* envoy_admin_v3_UnreadyTargetsDumps_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_UnreadyTargetsDumps* ret = envoy_admin_v3_UnreadyTargetsDumps_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__UnreadyTargetsDumps_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_UnreadyTargetsDumps_serialize(const envoy_admin_v3_UnreadyTargetsDumps* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__UnreadyTargetsDumps_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_UnreadyTargetsDumps_serialize_ex(const envoy_admin_v3_UnreadyTargetsDumps* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__UnreadyTargetsDumps_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_UnreadyTargetsDumps_clear_unready_targets_dumps(envoy_admin_v3_UnreadyTargetsDumps* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* const* envoy_admin_v3_UnreadyTargetsDumps_unready_targets_dumps(const envoy_admin_v3_UnreadyTargetsDumps* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_UnreadyTargetsDumps_unready_targets_dumps_upb_array(const envoy_admin_v3_UnreadyTargetsDumps* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_UnreadyTargetsDumps_unready_targets_dumps_mutable_upb_array(envoy_admin_v3_UnreadyTargetsDumps* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump** envoy_admin_v3_UnreadyTargetsDumps_mutable_unready_targets_dumps(envoy_admin_v3_UnreadyTargetsDumps* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump** envoy_admin_v3_UnreadyTargetsDumps_resize_unready_targets_dumps(envoy_admin_v3_UnreadyTargetsDumps* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* envoy_admin_v3_UnreadyTargetsDumps_add_unready_targets_dumps(envoy_admin_v3_UnreadyTargetsDumps* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* sub = (struct envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump*)_upb_Message_New(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump*)_upb_Message_New(&envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* ret = envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* ret = envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_serialize(const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_serialize_ex(const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__UnreadyTargetsDumps__UnreadyTargetsDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_clear_name(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_name(const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_clear_target_names(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_target_names(const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_target_names_upb_array(const envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_target_names_mutable_upb_array(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_set_name(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_mutable_target_names(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_resize_target_names(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump_add_target_names(envoy_admin_v3_UnreadyTargetsDumps_UnreadyTargetsDump* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
