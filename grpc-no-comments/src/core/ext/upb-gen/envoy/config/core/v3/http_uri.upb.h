
#ifndef ENVOY_CONFIG_CORE_V3_HTTP_URI_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_HTTP_URI_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/http_uri.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_HttpUri { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HttpUri;
struct google_protobuf_Duration;

UPB_INLINE envoy_config_core_v3_HttpUri* envoy_config_core_v3_HttpUri_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HttpUri*)_upb_Message_New(&envoy__config__core__v3__HttpUri_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HttpUri* envoy_config_core_v3_HttpUri_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HttpUri* ret = envoy_config_core_v3_HttpUri_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HttpUri_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HttpUri* envoy_config_core_v3_HttpUri_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HttpUri* ret = envoy_config_core_v3_HttpUri_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HttpUri_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HttpUri_serialize(const envoy_config_core_v3_HttpUri* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HttpUri_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HttpUri_serialize_ex(const envoy_config_core_v3_HttpUri* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HttpUri_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_HttpUri_http_upstream_type_cluster = 2,
  envoy_config_core_v3_HttpUri_http_upstream_type_NOT_SET = 0
} envoy_config_core_v3_HttpUri_http_upstream_type_oneofcases;
UPB_INLINE envoy_config_core_v3_HttpUri_http_upstream_type_oneofcases envoy_config_core_v3_HttpUri_http_upstream_type_case(const envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HttpUri_http_upstream_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HttpUri_clear_http_upstream_type(envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__HttpUri_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_HttpUri_clear_uri(envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HttpUri_uri(const envoy_config_core_v3_HttpUri* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HttpUri_clear_cluster(envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HttpUri_cluster(const envoy_config_core_v3_HttpUri* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HttpUri_has_cluster(const envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HttpUri_clear_timeout(envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_core_v3_HttpUri_timeout(const envoy_config_core_v3_HttpUri* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HttpUri_has_timeout(const envoy_config_core_v3_HttpUri* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_HttpUri_set_uri(envoy_config_core_v3_HttpUri *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HttpUri_set_cluster(envoy_config_core_v3_HttpUri *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HttpUri_set_timeout(envoy_config_core_v3_HttpUri *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_core_v3_HttpUri_mutable_timeout(envoy_config_core_v3_HttpUri* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_core_v3_HttpUri_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_core_v3_HttpUri_set_timeout(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
