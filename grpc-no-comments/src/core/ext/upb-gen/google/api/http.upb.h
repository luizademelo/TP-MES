
#ifndef GOOGLE_API_HTTP_PROTO_UPB_H__UPB_H_
#define GOOGLE_API_HTTP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/api/http.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct google_api_Http { upb_Message UPB_PRIVATE(base); } google_api_Http;
typedef struct google_api_HttpRule { upb_Message UPB_PRIVATE(base); } google_api_HttpRule;
typedef struct google_api_CustomHttpPattern { upb_Message UPB_PRIVATE(base); } google_api_CustomHttpPattern;

UPB_INLINE google_api_Http* google_api_Http_new(upb_Arena* arena) {
  return (google_api_Http*)_upb_Message_New(&google__api__Http_msg_init, arena);
}
UPB_INLINE google_api_Http* google_api_Http_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_Http* ret = google_api_Http_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__Http_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_Http* google_api_Http_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_Http* ret = google_api_Http_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__Http_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_Http_serialize(const google_api_Http* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__Http_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_Http_serialize_ex(const google_api_Http* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__Http_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_Http_clear_rules(google_api_Http* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_HttpRule* const* google_api_Http_rules(const google_api_Http* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_HttpRule* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_Http_rules_upb_array(const google_api_Http* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_Http_rules_mutable_upb_array(google_api_Http* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_Http_clear_fully_decode_reserved_expansion(google_api_Http* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool google_api_Http_fully_decode_reserved_expansion(const google_api_Http* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE google_api_HttpRule** google_api_Http_mutable_rules(google_api_Http* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_HttpRule**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_HttpRule** google_api_Http_resize_rules(google_api_Http* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_HttpRule**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_HttpRule* google_api_Http_add_rules(google_api_Http* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_HttpRule* sub = (struct google_api_HttpRule*)_upb_Message_New(&google__api__HttpRule_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void google_api_Http_set_fully_decode_reserved_expansion(google_api_Http *msg, bool value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_HttpRule* google_api_HttpRule_new(upb_Arena* arena) {
  return (google_api_HttpRule*)_upb_Message_New(&google__api__HttpRule_msg_init, arena);
}
UPB_INLINE google_api_HttpRule* google_api_HttpRule_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_HttpRule* ret = google_api_HttpRule_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__HttpRule_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_HttpRule* google_api_HttpRule_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_HttpRule* ret = google_api_HttpRule_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__HttpRule_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_HttpRule_serialize(const google_api_HttpRule* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__HttpRule_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_HttpRule_serialize_ex(const google_api_HttpRule* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__HttpRule_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  google_api_HttpRule_pattern_get = 2,
  google_api_HttpRule_pattern_put = 3,
  google_api_HttpRule_pattern_post = 4,
  google_api_HttpRule_pattern_delete = 5,
  google_api_HttpRule_pattern_patch = 6,
  google_api_HttpRule_pattern_custom = 8,
  google_api_HttpRule_pattern_NOT_SET = 0
} google_api_HttpRule_pattern_oneofcases;
UPB_INLINE google_api_HttpRule_pattern_oneofcases google_api_HttpRule_pattern_case(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (google_api_HttpRule_pattern_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_pattern(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &google__api__HttpRule_msg_init, &field);
}
UPB_INLINE void google_api_HttpRule_clear_selector(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_selector(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_HttpRule_clear_get(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_get(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_HttpRule_has_get(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_put(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_put(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_HttpRule_has_put(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_post(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_post(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_HttpRule_has_post(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_delete(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_delete(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_HttpRule_has_delete(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_patch(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_patch(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_HttpRule_has_patch(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_body(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_body(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_HttpRule_clear_custom(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_CustomHttpPattern* google_api_HttpRule_custom(const google_api_HttpRule* msg) {
  const google_api_CustomHttpPattern* default_val = NULL;
  const google_api_CustomHttpPattern* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__CustomHttpPattern_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool google_api_HttpRule_has_custom(const google_api_HttpRule* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void google_api_HttpRule_clear_additional_bindings(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const google_api_HttpRule* const* google_api_HttpRule_additional_bindings(const google_api_HttpRule* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const google_api_HttpRule* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _google_api_HttpRule_additional_bindings_upb_array(const google_api_HttpRule* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _google_api_HttpRule_additional_bindings_mutable_upb_array(google_api_HttpRule* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void google_api_HttpRule_clear_response_body(google_api_HttpRule* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_HttpRule_response_body(const google_api_HttpRule* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {12, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_HttpRule_set_selector(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_get(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_put(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_post(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_delete(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_patch(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_body(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_HttpRule_set_custom(google_api_HttpRule *msg, google_api_CustomHttpPattern* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 64), UPB_SIZE(-13, -9), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__CustomHttpPattern_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_api_CustomHttpPattern* google_api_HttpRule_mutable_custom(google_api_HttpRule* msg, upb_Arena* arena) {
  struct google_api_CustomHttpPattern* sub = (struct google_api_CustomHttpPattern*)google_api_HttpRule_custom(msg);
  if (sub == NULL) {
    sub = (struct google_api_CustomHttpPattern*)_upb_Message_New(&google__api__CustomHttpPattern_msg_init, arena);
    if (sub) google_api_HttpRule_set_custom(msg, sub);
  }
  return sub;
}
UPB_INLINE google_api_HttpRule** google_api_HttpRule_mutable_additional_bindings(google_api_HttpRule* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (google_api_HttpRule**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE google_api_HttpRule** google_api_HttpRule_resize_additional_bindings(google_api_HttpRule* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (google_api_HttpRule**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_api_HttpRule* google_api_HttpRule_add_additional_bindings(google_api_HttpRule* msg, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(8, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__api__HttpRule_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_api_HttpRule* sub = (struct google_api_HttpRule*)_upb_Message_New(&google__api__HttpRule_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void google_api_HttpRule_set_response_body(google_api_HttpRule *msg, upb_StringView value) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_api_CustomHttpPattern* google_api_CustomHttpPattern_new(upb_Arena* arena) {
  return (google_api_CustomHttpPattern*)_upb_Message_New(&google__api__CustomHttpPattern_msg_init, arena);
}
UPB_INLINE google_api_CustomHttpPattern* google_api_CustomHttpPattern_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_api_CustomHttpPattern* ret = google_api_CustomHttpPattern_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__CustomHttpPattern_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_api_CustomHttpPattern* google_api_CustomHttpPattern_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_api_CustomHttpPattern* ret = google_api_CustomHttpPattern_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__api__CustomHttpPattern_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_api_CustomHttpPattern_serialize(const google_api_CustomHttpPattern* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__CustomHttpPattern_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_api_CustomHttpPattern_serialize_ex(const google_api_CustomHttpPattern* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__api__CustomHttpPattern_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_api_CustomHttpPattern_clear_kind(google_api_CustomHttpPattern* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_CustomHttpPattern_kind(const google_api_CustomHttpPattern* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void google_api_CustomHttpPattern_clear_path(google_api_CustomHttpPattern* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_api_CustomHttpPattern_path(const google_api_CustomHttpPattern* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_api_CustomHttpPattern_set_kind(google_api_CustomHttpPattern *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void google_api_CustomHttpPattern_set_path(google_api_CustomHttpPattern *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
