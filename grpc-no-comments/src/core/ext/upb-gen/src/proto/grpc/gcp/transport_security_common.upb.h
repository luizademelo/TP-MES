
#ifndef SRC_PROTO_GRPC_GCP_TRANSPORT_SECURITY_COMMON_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_GCP_TRANSPORT_SECURITY_COMMON_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/gcp/transport_security_common.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_gcp_RpcProtocolVersions { upb_Message UPB_PRIVATE(base); } grpc_gcp_RpcProtocolVersions;
typedef struct grpc_gcp_RpcProtocolVersions_Version { upb_Message UPB_PRIVATE(base); } grpc_gcp_RpcProtocolVersions_Version;
typedef struct grpc_gcp_TransportProtocolPreferences { upb_Message UPB_PRIVATE(base); } grpc_gcp_TransportProtocolPreferences;
typedef struct grpc_gcp_NegotiatedTransportProtocol { upb_Message UPB_PRIVATE(base); } grpc_gcp_NegotiatedTransportProtocol;

typedef enum {
  grpc_gcp_SECURITY_NONE = 0,
  grpc_gcp_INTEGRITY_ONLY = 1,
  grpc_gcp_INTEGRITY_AND_PRIVACY = 2
} grpc_gcp_SecurityLevel;

UPB_INLINE grpc_gcp_RpcProtocolVersions* grpc_gcp_RpcProtocolVersions_new(upb_Arena* arena) {
  return (grpc_gcp_RpcProtocolVersions*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions_msg_init, arena);
}
UPB_INLINE grpc_gcp_RpcProtocolVersions* grpc_gcp_RpcProtocolVersions_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_RpcProtocolVersions* ret = grpc_gcp_RpcProtocolVersions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__RpcProtocolVersions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_RpcProtocolVersions* grpc_gcp_RpcProtocolVersions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_RpcProtocolVersions* ret = grpc_gcp_RpcProtocolVersions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__RpcProtocolVersions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_RpcProtocolVersions_serialize(const grpc_gcp_RpcProtocolVersions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__RpcProtocolVersions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_RpcProtocolVersions_serialize_ex(const grpc_gcp_RpcProtocolVersions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__RpcProtocolVersions_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_RpcProtocolVersions_clear_max_rpc_version(grpc_gcp_RpcProtocolVersions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_max_rpc_version(const grpc_gcp_RpcProtocolVersions* msg) {
  const grpc_gcp_RpcProtocolVersions_Version* default_val = NULL;
  const grpc_gcp_RpcProtocolVersions_Version* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions__Version_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_RpcProtocolVersions_has_max_rpc_version(const grpc_gcp_RpcProtocolVersions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_RpcProtocolVersions_clear_min_rpc_version(grpc_gcp_RpcProtocolVersions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_min_rpc_version(const grpc_gcp_RpcProtocolVersions* msg) {
  const grpc_gcp_RpcProtocolVersions_Version* default_val = NULL;
  const grpc_gcp_RpcProtocolVersions_Version* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions__Version_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_RpcProtocolVersions_has_min_rpc_version(const grpc_gcp_RpcProtocolVersions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_gcp_RpcProtocolVersions_set_max_rpc_version(grpc_gcp_RpcProtocolVersions *msg, grpc_gcp_RpcProtocolVersions_Version* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions__Version_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_mutable_max_rpc_version(grpc_gcp_RpcProtocolVersions* msg, upb_Arena* arena) {
  struct grpc_gcp_RpcProtocolVersions_Version* sub = (struct grpc_gcp_RpcProtocolVersions_Version*)grpc_gcp_RpcProtocolVersions_max_rpc_version(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_RpcProtocolVersions_Version*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions__Version_msg_init, arena);
    if (sub) grpc_gcp_RpcProtocolVersions_set_max_rpc_version(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_RpcProtocolVersions_set_min_rpc_version(grpc_gcp_RpcProtocolVersions *msg, grpc_gcp_RpcProtocolVersions_Version* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions__Version_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_mutable_min_rpc_version(grpc_gcp_RpcProtocolVersions* msg, upb_Arena* arena) {
  struct grpc_gcp_RpcProtocolVersions_Version* sub = (struct grpc_gcp_RpcProtocolVersions_Version*)grpc_gcp_RpcProtocolVersions_min_rpc_version(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_RpcProtocolVersions_Version*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions__Version_msg_init, arena);
    if (sub) grpc_gcp_RpcProtocolVersions_set_min_rpc_version(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_Version_new(upb_Arena* arena) {
  return (grpc_gcp_RpcProtocolVersions_Version*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions__Version_msg_init, arena);
}
UPB_INLINE grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_Version_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_RpcProtocolVersions_Version* ret = grpc_gcp_RpcProtocolVersions_Version_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__RpcProtocolVersions__Version_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_RpcProtocolVersions_Version* grpc_gcp_RpcProtocolVersions_Version_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_RpcProtocolVersions_Version* ret = grpc_gcp_RpcProtocolVersions_Version_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__RpcProtocolVersions__Version_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_RpcProtocolVersions_Version_serialize(const grpc_gcp_RpcProtocolVersions_Version* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__RpcProtocolVersions__Version_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_RpcProtocolVersions_Version_serialize_ex(const grpc_gcp_RpcProtocolVersions_Version* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__RpcProtocolVersions__Version_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_RpcProtocolVersions_Version_clear_major(grpc_gcp_RpcProtocolVersions_Version* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_RpcProtocolVersions_Version_major(const grpc_gcp_RpcProtocolVersions_Version* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_RpcProtocolVersions_Version_clear_minor(grpc_gcp_RpcProtocolVersions_Version* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_RpcProtocolVersions_Version_minor(const grpc_gcp_RpcProtocolVersions_Version* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_gcp_RpcProtocolVersions_Version_set_major(grpc_gcp_RpcProtocolVersions_Version *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_RpcProtocolVersions_Version_set_minor(grpc_gcp_RpcProtocolVersions_Version *msg, uint32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_gcp_TransportProtocolPreferences* grpc_gcp_TransportProtocolPreferences_new(upb_Arena* arena) {
  return (grpc_gcp_TransportProtocolPreferences*)_upb_Message_New(&grpc__gcp__TransportProtocolPreferences_msg_init, arena);
}
UPB_INLINE grpc_gcp_TransportProtocolPreferences* grpc_gcp_TransportProtocolPreferences_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_TransportProtocolPreferences* ret = grpc_gcp_TransportProtocolPreferences_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__TransportProtocolPreferences_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_TransportProtocolPreferences* grpc_gcp_TransportProtocolPreferences_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_TransportProtocolPreferences* ret = grpc_gcp_TransportProtocolPreferences_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__TransportProtocolPreferences_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_TransportProtocolPreferences_serialize(const grpc_gcp_TransportProtocolPreferences* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__TransportProtocolPreferences_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_TransportProtocolPreferences_serialize_ex(const grpc_gcp_TransportProtocolPreferences* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__TransportProtocolPreferences_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_TransportProtocolPreferences_clear_transport_protocol(grpc_gcp_TransportProtocolPreferences* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_gcp_TransportProtocolPreferences_transport_protocol(const grpc_gcp_TransportProtocolPreferences* msg, size_t* size) {
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
UPB_INLINE const upb_Array* _grpc_gcp_TransportProtocolPreferences_transport_protocol_upb_array(const grpc_gcp_TransportProtocolPreferences* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_TransportProtocolPreferences_transport_protocol_mutable_upb_array(grpc_gcp_TransportProtocolPreferences* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE upb_StringView* grpc_gcp_TransportProtocolPreferences_mutable_transport_protocol(grpc_gcp_TransportProtocolPreferences* msg, size_t* size) {
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
UPB_INLINE upb_StringView* grpc_gcp_TransportProtocolPreferences_resize_transport_protocol(grpc_gcp_TransportProtocolPreferences* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_gcp_TransportProtocolPreferences_add_transport_protocol(grpc_gcp_TransportProtocolPreferences* msg, upb_StringView val, upb_Arena* arena) {
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

UPB_INLINE grpc_gcp_NegotiatedTransportProtocol* grpc_gcp_NegotiatedTransportProtocol_new(upb_Arena* arena) {
  return (grpc_gcp_NegotiatedTransportProtocol*)_upb_Message_New(&grpc__gcp__NegotiatedTransportProtocol_msg_init, arena);
}
UPB_INLINE grpc_gcp_NegotiatedTransportProtocol* grpc_gcp_NegotiatedTransportProtocol_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_NegotiatedTransportProtocol* ret = grpc_gcp_NegotiatedTransportProtocol_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__NegotiatedTransportProtocol_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_NegotiatedTransportProtocol* grpc_gcp_NegotiatedTransportProtocol_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_NegotiatedTransportProtocol* ret = grpc_gcp_NegotiatedTransportProtocol_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__NegotiatedTransportProtocol_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_NegotiatedTransportProtocol_serialize(const grpc_gcp_NegotiatedTransportProtocol* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__NegotiatedTransportProtocol_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_NegotiatedTransportProtocol_serialize_ex(const grpc_gcp_NegotiatedTransportProtocol* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__NegotiatedTransportProtocol_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_NegotiatedTransportProtocol_clear_transport_protocol(grpc_gcp_NegotiatedTransportProtocol* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_NegotiatedTransportProtocol_transport_protocol(const grpc_gcp_NegotiatedTransportProtocol* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_gcp_NegotiatedTransportProtocol_set_transport_protocol(grpc_gcp_NegotiatedTransportProtocol *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
