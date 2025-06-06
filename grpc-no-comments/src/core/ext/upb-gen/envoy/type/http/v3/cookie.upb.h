
#ifndef ENVOY_TYPE_HTTP_V3_COOKIE_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_HTTP_V3_COOKIE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/http/v3/cookie.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_http_v3_Cookie { upb_Message UPB_PRIVATE(base); } envoy_type_http_v3_Cookie;
struct google_protobuf_Duration;

UPB_INLINE envoy_type_http_v3_Cookie* envoy_type_http_v3_Cookie_new(upb_Arena* arena) {
  return (envoy_type_http_v3_Cookie*)_upb_Message_New(&envoy__type__http__v3__Cookie_msg_init, arena);
}
UPB_INLINE envoy_type_http_v3_Cookie* envoy_type_http_v3_Cookie_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_http_v3_Cookie* ret = envoy_type_http_v3_Cookie_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__Cookie_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_http_v3_Cookie* envoy_type_http_v3_Cookie_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_http_v3_Cookie* ret = envoy_type_http_v3_Cookie_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__http__v3__Cookie_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_http_v3_Cookie_serialize(const envoy_type_http_v3_Cookie* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__Cookie_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_http_v3_Cookie_serialize_ex(const envoy_type_http_v3_Cookie* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__http__v3__Cookie_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_http_v3_Cookie_clear_name(envoy_type_http_v3_Cookie* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_http_v3_Cookie_name(const envoy_type_http_v3_Cookie* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_type_http_v3_Cookie_clear_ttl(envoy_type_http_v3_Cookie* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_type_http_v3_Cookie_ttl(const envoy_type_http_v3_Cookie* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_type_http_v3_Cookie_has_ttl(const envoy_type_http_v3_Cookie* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_type_http_v3_Cookie_clear_path(envoy_type_http_v3_Cookie* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_http_v3_Cookie_path(const envoy_type_http_v3_Cookie* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_http_v3_Cookie_set_name(envoy_type_http_v3_Cookie *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_type_http_v3_Cookie_set_ttl(envoy_type_http_v3_Cookie *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_type_http_v3_Cookie_mutable_ttl(envoy_type_http_v3_Cookie* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_type_http_v3_Cookie_ttl(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_type_http_v3_Cookie_set_ttl(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_type_http_v3_Cookie_set_path(envoy_type_http_v3_Cookie *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
