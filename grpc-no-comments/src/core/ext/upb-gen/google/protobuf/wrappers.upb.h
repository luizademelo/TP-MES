
#ifndef GOOGLE_PROTOBUF_WRAPPERS_PROTO_UPB_H__UPB_H_
#define GOOGLE_PROTOBUF_WRAPPERS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "google/protobuf/wrappers.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct google_protobuf_DoubleValue { upb_Message UPB_PRIVATE(base); } google_protobuf_DoubleValue;
typedef struct google_protobuf_FloatValue { upb_Message UPB_PRIVATE(base); } google_protobuf_FloatValue;
typedef struct google_protobuf_Int64Value { upb_Message UPB_PRIVATE(base); } google_protobuf_Int64Value;
typedef struct google_protobuf_UInt64Value { upb_Message UPB_PRIVATE(base); } google_protobuf_UInt64Value;
typedef struct google_protobuf_Int32Value { upb_Message UPB_PRIVATE(base); } google_protobuf_Int32Value;
typedef struct google_protobuf_UInt32Value { upb_Message UPB_PRIVATE(base); } google_protobuf_UInt32Value;
typedef struct google_protobuf_BoolValue { upb_Message UPB_PRIVATE(base); } google_protobuf_BoolValue;
typedef struct google_protobuf_StringValue { upb_Message UPB_PRIVATE(base); } google_protobuf_StringValue;
typedef struct google_protobuf_BytesValue { upb_Message UPB_PRIVATE(base); } google_protobuf_BytesValue;

UPB_INLINE google_protobuf_DoubleValue* google_protobuf_DoubleValue_new(upb_Arena* arena) {
  return (google_protobuf_DoubleValue*)_upb_Message_New(&google__protobuf__DoubleValue_msg_init, arena);
}
UPB_INLINE google_protobuf_DoubleValue* google_protobuf_DoubleValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_DoubleValue* ret = google_protobuf_DoubleValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__DoubleValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_DoubleValue* google_protobuf_DoubleValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_DoubleValue* ret = google_protobuf_DoubleValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__DoubleValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_DoubleValue_serialize(const google_protobuf_DoubleValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__DoubleValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_DoubleValue_serialize_ex(const google_protobuf_DoubleValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__DoubleValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_DoubleValue_clear_value(google_protobuf_DoubleValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double google_protobuf_DoubleValue_value(const google_protobuf_DoubleValue* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_DoubleValue_set_value(google_protobuf_DoubleValue *msg, double value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_FloatValue* google_protobuf_FloatValue_new(upb_Arena* arena) {
  return (google_protobuf_FloatValue*)_upb_Message_New(&google__protobuf__FloatValue_msg_init, arena);
}
UPB_INLINE google_protobuf_FloatValue* google_protobuf_FloatValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_FloatValue* ret = google_protobuf_FloatValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__FloatValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_FloatValue* google_protobuf_FloatValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_FloatValue* ret = google_protobuf_FloatValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__FloatValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_FloatValue_serialize(const google_protobuf_FloatValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__FloatValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_FloatValue_serialize_ex(const google_protobuf_FloatValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__FloatValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_FloatValue_clear_value(google_protobuf_FloatValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE float google_protobuf_FloatValue_value(const google_protobuf_FloatValue* msg) {
  float default_val = 0;
  float ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_FloatValue_set_value(google_protobuf_FloatValue *msg, float value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_Int64Value* google_protobuf_Int64Value_new(upb_Arena* arena) {
  return (google_protobuf_Int64Value*)_upb_Message_New(&google__protobuf__Int64Value_msg_init, arena);
}
UPB_INLINE google_protobuf_Int64Value* google_protobuf_Int64Value_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_Int64Value* ret = google_protobuf_Int64Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Int64Value_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_Int64Value* google_protobuf_Int64Value_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_Int64Value* ret = google_protobuf_Int64Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Int64Value_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_Int64Value_serialize(const google_protobuf_Int64Value* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Int64Value_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_Int64Value_serialize_ex(const google_protobuf_Int64Value* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Int64Value_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_Int64Value_clear_value(google_protobuf_Int64Value* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t google_protobuf_Int64Value_value(const google_protobuf_Int64Value* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_Int64Value_set_value(google_protobuf_Int64Value *msg, int64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_UInt64Value* google_protobuf_UInt64Value_new(upb_Arena* arena) {
  return (google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
}
UPB_INLINE google_protobuf_UInt64Value* google_protobuf_UInt64Value_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_UInt64Value* ret = google_protobuf_UInt64Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__UInt64Value_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_UInt64Value* google_protobuf_UInt64Value_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_UInt64Value* ret = google_protobuf_UInt64Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__UInt64Value_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_UInt64Value_serialize(const google_protobuf_UInt64Value* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__UInt64Value_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_UInt64Value_serialize_ex(const google_protobuf_UInt64Value* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__UInt64Value_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_UInt64Value_clear_value(google_protobuf_UInt64Value* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t google_protobuf_UInt64Value_value(const google_protobuf_UInt64Value* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_UInt64Value_set_value(google_protobuf_UInt64Value *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_Int32Value* google_protobuf_Int32Value_new(upb_Arena* arena) {
  return (google_protobuf_Int32Value*)_upb_Message_New(&google__protobuf__Int32Value_msg_init, arena);
}
UPB_INLINE google_protobuf_Int32Value* google_protobuf_Int32Value_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_Int32Value* ret = google_protobuf_Int32Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Int32Value_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_Int32Value* google_protobuf_Int32Value_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_Int32Value* ret = google_protobuf_Int32Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__Int32Value_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_Int32Value_serialize(const google_protobuf_Int32Value* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Int32Value_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_Int32Value_serialize_ex(const google_protobuf_Int32Value* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__Int32Value_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_Int32Value_clear_value(google_protobuf_Int32Value* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t google_protobuf_Int32Value_value(const google_protobuf_Int32Value* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_Int32Value_set_value(google_protobuf_Int32Value *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_UInt32Value* google_protobuf_UInt32Value_new(upb_Arena* arena) {
  return (google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
}
UPB_INLINE google_protobuf_UInt32Value* google_protobuf_UInt32Value_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_UInt32Value* ret = google_protobuf_UInt32Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__UInt32Value_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_UInt32Value* google_protobuf_UInt32Value_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_UInt32Value* ret = google_protobuf_UInt32Value_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__UInt32Value_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_UInt32Value_serialize(const google_protobuf_UInt32Value* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__UInt32Value_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_UInt32Value_serialize_ex(const google_protobuf_UInt32Value* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__UInt32Value_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_UInt32Value_clear_value(google_protobuf_UInt32Value* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t google_protobuf_UInt32Value_value(const google_protobuf_UInt32Value* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_UInt32Value_set_value(google_protobuf_UInt32Value *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_BoolValue* google_protobuf_BoolValue_new(upb_Arena* arena) {
  return (google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
}
UPB_INLINE google_protobuf_BoolValue* google_protobuf_BoolValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_BoolValue* ret = google_protobuf_BoolValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__BoolValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_BoolValue* google_protobuf_BoolValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_BoolValue* ret = google_protobuf_BoolValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__BoolValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_BoolValue_serialize(const google_protobuf_BoolValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__BoolValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_BoolValue_serialize_ex(const google_protobuf_BoolValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__BoolValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_BoolValue_clear_value(google_protobuf_BoolValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool google_protobuf_BoolValue_value(const google_protobuf_BoolValue* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_BoolValue_set_value(google_protobuf_BoolValue *msg, bool value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_StringValue* google_protobuf_StringValue_new(upb_Arena* arena) {
  return (google_protobuf_StringValue*)_upb_Message_New(&google__protobuf__StringValue_msg_init, arena);
}
UPB_INLINE google_protobuf_StringValue* google_protobuf_StringValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_StringValue* ret = google_protobuf_StringValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__StringValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_StringValue* google_protobuf_StringValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_StringValue* ret = google_protobuf_StringValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__StringValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_StringValue_serialize(const google_protobuf_StringValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__StringValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_StringValue_serialize_ex(const google_protobuf_StringValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__StringValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_StringValue_clear_value(google_protobuf_StringValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_protobuf_StringValue_value(const google_protobuf_StringValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_StringValue_set_value(google_protobuf_StringValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE google_protobuf_BytesValue* google_protobuf_BytesValue_new(upb_Arena* arena) {
  return (google_protobuf_BytesValue*)_upb_Message_New(&google__protobuf__BytesValue_msg_init, arena);
}
UPB_INLINE google_protobuf_BytesValue* google_protobuf_BytesValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  google_protobuf_BytesValue* ret = google_protobuf_BytesValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__BytesValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE google_protobuf_BytesValue* google_protobuf_BytesValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  google_protobuf_BytesValue* ret = google_protobuf_BytesValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &google__protobuf__BytesValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* google_protobuf_BytesValue_serialize(const google_protobuf_BytesValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__BytesValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* google_protobuf_BytesValue_serialize_ex(const google_protobuf_BytesValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &google__protobuf__BytesValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void google_protobuf_BytesValue_clear_value(google_protobuf_BytesValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView google_protobuf_BytesValue_value(const google_protobuf_BytesValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void google_protobuf_BytesValue_set_value(google_protobuf_BytesValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
