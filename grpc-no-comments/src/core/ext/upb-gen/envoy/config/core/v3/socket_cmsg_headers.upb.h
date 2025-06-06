
#ifndef ENVOY_CONFIG_CORE_V3_SOCKET_CMSG_HEADERS_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_SOCKET_CMSG_HEADERS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/socket_cmsg_headers.upb_minitable.h"

#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_SocketCmsgHeaders { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_SocketCmsgHeaders;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_config_core_v3_SocketCmsgHeaders* envoy_config_core_v3_SocketCmsgHeaders_new(upb_Arena* arena) {
  return (envoy_config_core_v3_SocketCmsgHeaders*)_upb_Message_New(&envoy__config__core__v3__SocketCmsgHeaders_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_SocketCmsgHeaders* envoy_config_core_v3_SocketCmsgHeaders_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_SocketCmsgHeaders* ret = envoy_config_core_v3_SocketCmsgHeaders_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SocketCmsgHeaders_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_SocketCmsgHeaders* envoy_config_core_v3_SocketCmsgHeaders_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_SocketCmsgHeaders* ret = envoy_config_core_v3_SocketCmsgHeaders_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__SocketCmsgHeaders_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_SocketCmsgHeaders_serialize(const envoy_config_core_v3_SocketCmsgHeaders* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SocketCmsgHeaders_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_SocketCmsgHeaders_serialize_ex(const envoy_config_core_v3_SocketCmsgHeaders* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__SocketCmsgHeaders_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_SocketCmsgHeaders_clear_level(envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_SocketCmsgHeaders_level(const envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SocketCmsgHeaders_has_level(const envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SocketCmsgHeaders_clear_type(envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_SocketCmsgHeaders_type(const envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_SocketCmsgHeaders_has_type(const envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_SocketCmsgHeaders_clear_expected_size(envoy_config_core_v3_SocketCmsgHeaders* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_core_v3_SocketCmsgHeaders_expected_size(const envoy_config_core_v3_SocketCmsgHeaders* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_SocketCmsgHeaders_set_level(envoy_config_core_v3_SocketCmsgHeaders *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_SocketCmsgHeaders_mutable_level(envoy_config_core_v3_SocketCmsgHeaders* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_SocketCmsgHeaders_level(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_SocketCmsgHeaders_set_level(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_SocketCmsgHeaders_set_type(envoy_config_core_v3_SocketCmsgHeaders *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_SocketCmsgHeaders_mutable_type(envoy_config_core_v3_SocketCmsgHeaders* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_SocketCmsgHeaders_type(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_SocketCmsgHeaders_set_type(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_SocketCmsgHeaders_set_expected_size(envoy_config_core_v3_SocketCmsgHeaders *msg, uint32_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
