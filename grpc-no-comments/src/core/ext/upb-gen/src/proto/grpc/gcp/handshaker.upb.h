
#ifndef SRC_PROTO_GRPC_GCP_HANDSHAKER_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_GCP_HANDSHAKER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/gcp/handshaker.upb_minitable.h"

#include "src/proto/grpc/gcp/transport_security_common.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_gcp_Endpoint { upb_Message UPB_PRIVATE(base); } grpc_gcp_Endpoint;
typedef struct grpc_gcp_Identity { upb_Message UPB_PRIVATE(base); } grpc_gcp_Identity;
typedef struct grpc_gcp_StartClientHandshakeReq { upb_Message UPB_PRIVATE(base); } grpc_gcp_StartClientHandshakeReq;
typedef struct grpc_gcp_ServerHandshakeParameters { upb_Message UPB_PRIVATE(base); } grpc_gcp_ServerHandshakeParameters;
typedef struct grpc_gcp_StartServerHandshakeReq { upb_Message UPB_PRIVATE(base); } grpc_gcp_StartServerHandshakeReq;
typedef struct grpc_gcp_NextHandshakeMessageReq { upb_Message UPB_PRIVATE(base); } grpc_gcp_NextHandshakeMessageReq;
typedef struct grpc_gcp_HandshakerReq { upb_Message UPB_PRIVATE(base); } grpc_gcp_HandshakerReq;
typedef struct grpc_gcp_HandshakerResult { upb_Message UPB_PRIVATE(base); } grpc_gcp_HandshakerResult;
typedef struct grpc_gcp_HandshakerStatus { upb_Message UPB_PRIVATE(base); } grpc_gcp_HandshakerStatus;
typedef struct grpc_gcp_HandshakerResp { upb_Message UPB_PRIVATE(base); } grpc_gcp_HandshakerResp;
struct grpc_gcp_NegotiatedTransportProtocol;
struct grpc_gcp_RpcProtocolVersions;
struct grpc_gcp_TransportProtocolPreferences;

typedef enum {
  grpc_gcp_HANDSHAKE_PROTOCOL_UNSPECIFIED = 0,
  grpc_gcp_TLS = 1,
  grpc_gcp_ALTS = 2
} grpc_gcp_HandshakeProtocol;

typedef enum {
  grpc_gcp_NETWORK_PROTOCOL_UNSPECIFIED = 0,
  grpc_gcp_TCP = 1,
  grpc_gcp_UDP = 2
} grpc_gcp_NetworkProtocol;

UPB_INLINE grpc_gcp_Endpoint* grpc_gcp_Endpoint_new(upb_Arena* arena) {
  return (grpc_gcp_Endpoint*)_upb_Message_New(&grpc__gcp__Endpoint_msg_init, arena);
}
UPB_INLINE grpc_gcp_Endpoint* grpc_gcp_Endpoint_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_Endpoint* ret = grpc_gcp_Endpoint_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__Endpoint_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_Endpoint* grpc_gcp_Endpoint_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_Endpoint* ret = grpc_gcp_Endpoint_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__Endpoint_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_Endpoint_serialize(const grpc_gcp_Endpoint* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__Endpoint_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_Endpoint_serialize_ex(const grpc_gcp_Endpoint* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__Endpoint_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_Endpoint_clear_ip_address(grpc_gcp_Endpoint* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_Endpoint_ip_address(const grpc_gcp_Endpoint* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_Endpoint_clear_port(grpc_gcp_Endpoint* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_gcp_Endpoint_port(const grpc_gcp_Endpoint* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_Endpoint_clear_protocol(grpc_gcp_Endpoint* msg) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_gcp_Endpoint_protocol(const grpc_gcp_Endpoint* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_gcp_Endpoint_set_ip_address(grpc_gcp_Endpoint *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_Endpoint_set_port(grpc_gcp_Endpoint *msg, int32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_Endpoint_set_protocol(grpc_gcp_Endpoint *msg, int32_t value) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_gcp_Identity* grpc_gcp_Identity_new(upb_Arena* arena) {
  return (grpc_gcp_Identity*)_upb_Message_New(&grpc__gcp__Identity_msg_init, arena);
}
UPB_INLINE grpc_gcp_Identity* grpc_gcp_Identity_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_Identity* ret = grpc_gcp_Identity_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__Identity_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_Identity* grpc_gcp_Identity_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_Identity* ret = grpc_gcp_Identity_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__Identity_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_Identity_serialize(const grpc_gcp_Identity* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__Identity_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_Identity_serialize_ex(const grpc_gcp_Identity* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__Identity_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  grpc_gcp_Identity_identity_oneof_service_account = 1,
  grpc_gcp_Identity_identity_oneof_hostname = 2,
  grpc_gcp_Identity_identity_oneof_NOT_SET = 0
} grpc_gcp_Identity_identity_oneof_oneofcases;
UPB_INLINE grpc_gcp_Identity_identity_oneof_oneofcases grpc_gcp_Identity_identity_oneof_case(const grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (grpc_gcp_Identity_identity_oneof_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_Identity_clear_identity_oneof(grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &grpc__gcp__Identity_msg_init, &field);
}
UPB_INLINE void grpc_gcp_Identity_clear_service_account(grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_Identity_service_account(const grpc_gcp_Identity* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_Identity_has_service_account(const grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_Identity_clear_hostname(grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {2, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_Identity_hostname(const grpc_gcp_Identity* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_Identity_has_hostname(const grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {2, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_Identity_clear_attributes(grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t grpc_gcp_Identity_attributes_size(const grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool grpc_gcp_Identity_attributes_get(const grpc_gcp_Identity* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity__AttributesEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool grpc_gcp_Identity_attributes_next(const grpc_gcp_Identity* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity__AttributesEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _grpc_gcp_Identity_attributes_upb_map(grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity__AttributesEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _grpc_gcp_Identity_attributes_mutable_upb_map(grpc_gcp_Identity* msg, upb_Arena* a) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity__AttributesEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}

UPB_INLINE void grpc_gcp_Identity_set_service_account(grpc_gcp_Identity *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_Identity_set_hostname(grpc_gcp_Identity *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_Identity_attributes_clear(grpc_gcp_Identity* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool grpc_gcp_Identity_attributes_set(grpc_gcp_Identity* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity__AttributesEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool grpc_gcp_Identity_attributes_delete(grpc_gcp_Identity* msg, upb_StringView key) {
  const upb_MiniTableField field = {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE grpc_gcp_StartClientHandshakeReq* grpc_gcp_StartClientHandshakeReq_new(upb_Arena* arena) {
  return (grpc_gcp_StartClientHandshakeReq*)_upb_Message_New(&grpc__gcp__StartClientHandshakeReq_msg_init, arena);
}
UPB_INLINE grpc_gcp_StartClientHandshakeReq* grpc_gcp_StartClientHandshakeReq_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_StartClientHandshakeReq* ret = grpc_gcp_StartClientHandshakeReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__StartClientHandshakeReq_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_StartClientHandshakeReq* grpc_gcp_StartClientHandshakeReq_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_StartClientHandshakeReq* ret = grpc_gcp_StartClientHandshakeReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__StartClientHandshakeReq_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_StartClientHandshakeReq_serialize(const grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__StartClientHandshakeReq_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_StartClientHandshakeReq_serialize_ex(const grpc_gcp_StartClientHandshakeReq* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__StartClientHandshakeReq_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_handshake_security_protocol(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_gcp_StartClientHandshakeReq_handshake_security_protocol(const grpc_gcp_StartClientHandshakeReq* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_application_protocols(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_gcp_StartClientHandshakeReq_application_protocols(const grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_gcp_StartClientHandshakeReq_application_protocols_upb_array(const grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_StartClientHandshakeReq_application_protocols_mutable_upb_array(grpc_gcp_StartClientHandshakeReq* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_record_protocols(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_gcp_StartClientHandshakeReq_record_protocols(const grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_gcp_StartClientHandshakeReq_record_protocols_upb_array(const grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_StartClientHandshakeReq_record_protocols_mutable_upb_array(grpc_gcp_StartClientHandshakeReq* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_target_identities(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Identity* const* grpc_gcp_StartClientHandshakeReq_target_identities(const grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_gcp_Identity* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_gcp_StartClientHandshakeReq_target_identities_upb_array(const grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_StartClientHandshakeReq_target_identities_mutable_upb_array(grpc_gcp_StartClientHandshakeReq* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_local_identity(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Identity* grpc_gcp_StartClientHandshakeReq_local_identity(const grpc_gcp_StartClientHandshakeReq* msg) {
  const grpc_gcp_Identity* default_val = NULL;
  const grpc_gcp_Identity* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_has_local_identity(const grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_local_endpoint(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Endpoint* grpc_gcp_StartClientHandshakeReq_local_endpoint(const grpc_gcp_StartClientHandshakeReq* msg) {
  const grpc_gcp_Endpoint* default_val = NULL;
  const grpc_gcp_Endpoint* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_has_local_endpoint(const grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_remote_endpoint(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Endpoint* grpc_gcp_StartClientHandshakeReq_remote_endpoint(const grpc_gcp_StartClientHandshakeReq* msg) {
  const grpc_gcp_Endpoint* default_val = NULL;
  const grpc_gcp_Endpoint* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_has_remote_endpoint(const grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_target_name(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_StartClientHandshakeReq_target_name(const grpc_gcp_StartClientHandshakeReq* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_rpc_versions(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 88), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_RpcProtocolVersions* grpc_gcp_StartClientHandshakeReq_rpc_versions(const grpc_gcp_StartClientHandshakeReq* msg) {
  const struct grpc_gcp_RpcProtocolVersions* default_val = NULL;
  const struct grpc_gcp_RpcProtocolVersions* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(40, 88), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_has_rpc_versions(const grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 88), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_max_frame_size(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_StartClientHandshakeReq_max_frame_size(const grpc_gcp_StartClientHandshakeReq* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_clear_transport_protocol_preferences(grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 96), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_TransportProtocolPreferences* grpc_gcp_StartClientHandshakeReq_transport_protocol_preferences(const grpc_gcp_StartClientHandshakeReq* msg) {
  const struct grpc_gcp_TransportProtocolPreferences* default_val = NULL;
  const struct grpc_gcp_TransportProtocolPreferences* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(48, 96), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__TransportProtocolPreferences_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_has_transport_protocol_preferences(const grpc_gcp_StartClientHandshakeReq* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 96), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_handshake_security_protocol(grpc_gcp_StartClientHandshakeReq *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* grpc_gcp_StartClientHandshakeReq_mutable_application_protocols(grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_gcp_StartClientHandshakeReq_resize_application_protocols(grpc_gcp_StartClientHandshakeReq* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_add_application_protocols(grpc_gcp_StartClientHandshakeReq* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* grpc_gcp_StartClientHandshakeReq_mutable_record_protocols(grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_gcp_StartClientHandshakeReq_resize_record_protocols(grpc_gcp_StartClientHandshakeReq* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_gcp_StartClientHandshakeReq_add_record_protocols(grpc_gcp_StartClientHandshakeReq* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE grpc_gcp_Identity** grpc_gcp_StartClientHandshakeReq_mutable_target_identities(grpc_gcp_StartClientHandshakeReq* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_gcp_Identity**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_gcp_Identity** grpc_gcp_StartClientHandshakeReq_resize_target_identities(grpc_gcp_StartClientHandshakeReq* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_gcp_Identity**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_gcp_Identity* grpc_gcp_StartClientHandshakeReq_add_target_identities(grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_gcp_Identity* sub = (struct grpc_gcp_Identity*)_upb_Message_New(&grpc__gcp__Identity_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_local_identity(grpc_gcp_StartClientHandshakeReq *msg, grpc_gcp_Identity* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Identity* grpc_gcp_StartClientHandshakeReq_mutable_local_identity(grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_Identity* sub = (struct grpc_gcp_Identity*)grpc_gcp_StartClientHandshakeReq_local_identity(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Identity*)_upb_Message_New(&grpc__gcp__Identity_msg_init, arena);
    if (sub) grpc_gcp_StartClientHandshakeReq_set_local_identity(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_local_endpoint(grpc_gcp_StartClientHandshakeReq *msg, grpc_gcp_Endpoint* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Endpoint* grpc_gcp_StartClientHandshakeReq_mutable_local_endpoint(grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_Endpoint* sub = (struct grpc_gcp_Endpoint*)grpc_gcp_StartClientHandshakeReq_local_endpoint(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Endpoint*)_upb_Message_New(&grpc__gcp__Endpoint_msg_init, arena);
    if (sub) grpc_gcp_StartClientHandshakeReq_set_local_endpoint(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_remote_endpoint(grpc_gcp_StartClientHandshakeReq *msg, grpc_gcp_Endpoint* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Endpoint* grpc_gcp_StartClientHandshakeReq_mutable_remote_endpoint(grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_Endpoint* sub = (struct grpc_gcp_Endpoint*)grpc_gcp_StartClientHandshakeReq_remote_endpoint(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Endpoint*)_upb_Message_New(&grpc__gcp__Endpoint_msg_init, arena);
    if (sub) grpc_gcp_StartClientHandshakeReq_set_remote_endpoint(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_target_name(grpc_gcp_StartClientHandshakeReq *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_rpc_versions(grpc_gcp_StartClientHandshakeReq *msg, struct grpc_gcp_RpcProtocolVersions* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 88), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_RpcProtocolVersions* grpc_gcp_StartClientHandshakeReq_mutable_rpc_versions(grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_RpcProtocolVersions* sub = (struct grpc_gcp_RpcProtocolVersions*)grpc_gcp_StartClientHandshakeReq_rpc_versions(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_RpcProtocolVersions*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions_msg_init, arena);
    if (sub) grpc_gcp_StartClientHandshakeReq_set_rpc_versions(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_max_frame_size(grpc_gcp_StartClientHandshakeReq *msg, uint32_t value) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_StartClientHandshakeReq_set_transport_protocol_preferences(grpc_gcp_StartClientHandshakeReq *msg, struct grpc_gcp_TransportProtocolPreferences* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(48, 96), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__TransportProtocolPreferences_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_TransportProtocolPreferences* grpc_gcp_StartClientHandshakeReq_mutable_transport_protocol_preferences(grpc_gcp_StartClientHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_TransportProtocolPreferences* sub = (struct grpc_gcp_TransportProtocolPreferences*)grpc_gcp_StartClientHandshakeReq_transport_protocol_preferences(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_TransportProtocolPreferences*)_upb_Message_New(&grpc__gcp__TransportProtocolPreferences_msg_init, arena);
    if (sub) grpc_gcp_StartClientHandshakeReq_set_transport_protocol_preferences(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_gcp_ServerHandshakeParameters* grpc_gcp_ServerHandshakeParameters_new(upb_Arena* arena) {
  return (grpc_gcp_ServerHandshakeParameters*)_upb_Message_New(&grpc__gcp__ServerHandshakeParameters_msg_init, arena);
}
UPB_INLINE grpc_gcp_ServerHandshakeParameters* grpc_gcp_ServerHandshakeParameters_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_ServerHandshakeParameters* ret = grpc_gcp_ServerHandshakeParameters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__ServerHandshakeParameters_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_ServerHandshakeParameters* grpc_gcp_ServerHandshakeParameters_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_ServerHandshakeParameters* ret = grpc_gcp_ServerHandshakeParameters_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__ServerHandshakeParameters_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_ServerHandshakeParameters_serialize(const grpc_gcp_ServerHandshakeParameters* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__ServerHandshakeParameters_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_ServerHandshakeParameters_serialize_ex(const grpc_gcp_ServerHandshakeParameters* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__ServerHandshakeParameters_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_ServerHandshakeParameters_clear_record_protocols(grpc_gcp_ServerHandshakeParameters* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_gcp_ServerHandshakeParameters_record_protocols(const grpc_gcp_ServerHandshakeParameters* msg, size_t* size) {
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
UPB_INLINE const upb_Array* _grpc_gcp_ServerHandshakeParameters_record_protocols_upb_array(const grpc_gcp_ServerHandshakeParameters* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_ServerHandshakeParameters_record_protocols_mutable_upb_array(grpc_gcp_ServerHandshakeParameters* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_gcp_ServerHandshakeParameters_clear_local_identities(grpc_gcp_ServerHandshakeParameters* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Identity* const* grpc_gcp_ServerHandshakeParameters_local_identities(const grpc_gcp_ServerHandshakeParameters* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_gcp_Identity* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_gcp_ServerHandshakeParameters_local_identities_upb_array(const grpc_gcp_ServerHandshakeParameters* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_ServerHandshakeParameters_local_identities_mutable_upb_array(grpc_gcp_ServerHandshakeParameters* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE upb_StringView* grpc_gcp_ServerHandshakeParameters_mutable_record_protocols(grpc_gcp_ServerHandshakeParameters* msg, size_t* size) {
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
UPB_INLINE upb_StringView* grpc_gcp_ServerHandshakeParameters_resize_record_protocols(grpc_gcp_ServerHandshakeParameters* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_gcp_ServerHandshakeParameters_add_record_protocols(grpc_gcp_ServerHandshakeParameters* msg, upb_StringView val, upb_Arena* arena) {
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
UPB_INLINE grpc_gcp_Identity** grpc_gcp_ServerHandshakeParameters_mutable_local_identities(grpc_gcp_ServerHandshakeParameters* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_gcp_Identity**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_gcp_Identity** grpc_gcp_ServerHandshakeParameters_resize_local_identities(grpc_gcp_ServerHandshakeParameters* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_gcp_Identity**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_gcp_Identity* grpc_gcp_ServerHandshakeParameters_add_local_identities(grpc_gcp_ServerHandshakeParameters* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_gcp_Identity* sub = (struct grpc_gcp_Identity*)_upb_Message_New(&grpc__gcp__Identity_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE grpc_gcp_StartServerHandshakeReq* grpc_gcp_StartServerHandshakeReq_new(upb_Arena* arena) {
  return (grpc_gcp_StartServerHandshakeReq*)_upb_Message_New(&grpc__gcp__StartServerHandshakeReq_msg_init, arena);
}
UPB_INLINE grpc_gcp_StartServerHandshakeReq* grpc_gcp_StartServerHandshakeReq_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_StartServerHandshakeReq* ret = grpc_gcp_StartServerHandshakeReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__StartServerHandshakeReq_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_StartServerHandshakeReq* grpc_gcp_StartServerHandshakeReq_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_StartServerHandshakeReq* ret = grpc_gcp_StartServerHandshakeReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__StartServerHandshakeReq_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_StartServerHandshakeReq_serialize(const grpc_gcp_StartServerHandshakeReq* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__StartServerHandshakeReq_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_StartServerHandshakeReq_serialize_ex(const grpc_gcp_StartServerHandshakeReq* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__StartServerHandshakeReq_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_application_protocols(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* grpc_gcp_StartServerHandshakeReq_application_protocols(const grpc_gcp_StartServerHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_gcp_StartServerHandshakeReq_application_protocols_upb_array(const grpc_gcp_StartServerHandshakeReq* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_gcp_StartServerHandshakeReq_application_protocols_mutable_upb_array(grpc_gcp_StartServerHandshakeReq* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_handshake_parameters(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t grpc_gcp_StartServerHandshakeReq_handshake_parameters_size(const grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_handshake_parameters_get(const grpc_gcp_StartServerHandshakeReq* msg, int32_t key, grpc_gcp_ServerHandshakeParameters** val) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__ServerHandshakeParameters_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, sizeof(key), val, sizeof(*val));
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_handshake_parameters_next(const grpc_gcp_StartServerHandshakeReq* msg, int32_t* key, const grpc_gcp_ServerHandshakeParameters** val,
                           size_t* iter) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__ServerHandshakeParameters_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _grpc_gcp_StartServerHandshakeReq_handshake_parameters_upb_map(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__ServerHandshakeParameters_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _grpc_gcp_StartServerHandshakeReq_handshake_parameters_mutable_upb_map(grpc_gcp_StartServerHandshakeReq* msg, upb_Arena* a) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__ServerHandshakeParameters_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, sizeof(int32_t), sizeof(grpc_gcp_ServerHandshakeParameters*), a);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_in_bytes(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_StartServerHandshakeReq_in_bytes(const grpc_gcp_StartServerHandshakeReq* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_local_endpoint(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Endpoint* grpc_gcp_StartServerHandshakeReq_local_endpoint(const grpc_gcp_StartServerHandshakeReq* msg) {
  const grpc_gcp_Endpoint* default_val = NULL;
  const grpc_gcp_Endpoint* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_has_local_endpoint(const grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_remote_endpoint(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Endpoint* grpc_gcp_StartServerHandshakeReq_remote_endpoint(const grpc_gcp_StartServerHandshakeReq* msg) {
  const grpc_gcp_Endpoint* default_val = NULL;
  const grpc_gcp_Endpoint* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_has_remote_endpoint(const grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_rpc_versions(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_RpcProtocolVersions* grpc_gcp_StartServerHandshakeReq_rpc_versions(const grpc_gcp_StartServerHandshakeReq* msg) {
  const struct grpc_gcp_RpcProtocolVersions* default_val = NULL;
  const struct grpc_gcp_RpcProtocolVersions* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_has_rpc_versions(const grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_max_frame_size(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_StartServerHandshakeReq_max_frame_size(const grpc_gcp_StartServerHandshakeReq* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {7, UPB_SIZE(32, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_clear_transport_protocol_preferences(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_TransportProtocolPreferences* grpc_gcp_StartServerHandshakeReq_transport_protocol_preferences(const grpc_gcp_StartServerHandshakeReq* msg) {
  const struct grpc_gcp_TransportProtocolPreferences* default_val = NULL;
  const struct grpc_gcp_TransportProtocolPreferences* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__TransportProtocolPreferences_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_has_transport_protocol_preferences(const grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE upb_StringView* grpc_gcp_StartServerHandshakeReq_mutable_application_protocols(grpc_gcp_StartServerHandshakeReq* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* grpc_gcp_StartServerHandshakeReq_resize_application_protocols(grpc_gcp_StartServerHandshakeReq* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_add_application_protocols(grpc_gcp_StartServerHandshakeReq* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_handshake_parameters_clear(grpc_gcp_StartServerHandshakeReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_handshake_parameters_set(grpc_gcp_StartServerHandshakeReq* msg, int32_t key, grpc_gcp_ServerHandshakeParameters* val, upb_Arena* a) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__ServerHandshakeParameters_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, sizeof(key), sizeof(val), a);
  return _upb_Map_Insert(map, &key, sizeof(key), &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool grpc_gcp_StartServerHandshakeReq_handshake_parameters_delete(grpc_gcp_StartServerHandshakeReq* msg, int32_t key) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, sizeof(key), NULL);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_set_in_bytes(grpc_gcp_StartServerHandshakeReq *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_set_local_endpoint(grpc_gcp_StartServerHandshakeReq *msg, grpc_gcp_Endpoint* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Endpoint* grpc_gcp_StartServerHandshakeReq_mutable_local_endpoint(grpc_gcp_StartServerHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_Endpoint* sub = (struct grpc_gcp_Endpoint*)grpc_gcp_StartServerHandshakeReq_local_endpoint(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Endpoint*)_upb_Message_New(&grpc__gcp__Endpoint_msg_init, arena);
    if (sub) grpc_gcp_StartServerHandshakeReq_set_local_endpoint(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_set_remote_endpoint(grpc_gcp_StartServerHandshakeReq *msg, grpc_gcp_Endpoint* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Endpoint_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Endpoint* grpc_gcp_StartServerHandshakeReq_mutable_remote_endpoint(grpc_gcp_StartServerHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_Endpoint* sub = (struct grpc_gcp_Endpoint*)grpc_gcp_StartServerHandshakeReq_remote_endpoint(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Endpoint*)_upb_Message_New(&grpc__gcp__Endpoint_msg_init, arena);
    if (sub) grpc_gcp_StartServerHandshakeReq_set_remote_endpoint(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_set_rpc_versions(grpc_gcp_StartServerHandshakeReq *msg, struct grpc_gcp_RpcProtocolVersions* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_RpcProtocolVersions* grpc_gcp_StartServerHandshakeReq_mutable_rpc_versions(grpc_gcp_StartServerHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_RpcProtocolVersions* sub = (struct grpc_gcp_RpcProtocolVersions*)grpc_gcp_StartServerHandshakeReq_rpc_versions(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_RpcProtocolVersions*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions_msg_init, arena);
    if (sub) grpc_gcp_StartServerHandshakeReq_set_rpc_versions(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_set_max_frame_size(grpc_gcp_StartServerHandshakeReq *msg, uint32_t value) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_StartServerHandshakeReq_set_transport_protocol_preferences(grpc_gcp_StartServerHandshakeReq *msg, struct grpc_gcp_TransportProtocolPreferences* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__TransportProtocolPreferences_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_TransportProtocolPreferences* grpc_gcp_StartServerHandshakeReq_mutable_transport_protocol_preferences(grpc_gcp_StartServerHandshakeReq* msg, upb_Arena* arena) {
  struct grpc_gcp_TransportProtocolPreferences* sub = (struct grpc_gcp_TransportProtocolPreferences*)grpc_gcp_StartServerHandshakeReq_transport_protocol_preferences(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_TransportProtocolPreferences*)_upb_Message_New(&grpc__gcp__TransportProtocolPreferences_msg_init, arena);
    if (sub) grpc_gcp_StartServerHandshakeReq_set_transport_protocol_preferences(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_gcp_NextHandshakeMessageReq* grpc_gcp_NextHandshakeMessageReq_new(upb_Arena* arena) {
  return (grpc_gcp_NextHandshakeMessageReq*)_upb_Message_New(&grpc__gcp__NextHandshakeMessageReq_msg_init, arena);
}
UPB_INLINE grpc_gcp_NextHandshakeMessageReq* grpc_gcp_NextHandshakeMessageReq_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_NextHandshakeMessageReq* ret = grpc_gcp_NextHandshakeMessageReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__NextHandshakeMessageReq_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_NextHandshakeMessageReq* grpc_gcp_NextHandshakeMessageReq_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_NextHandshakeMessageReq* ret = grpc_gcp_NextHandshakeMessageReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__NextHandshakeMessageReq_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_NextHandshakeMessageReq_serialize(const grpc_gcp_NextHandshakeMessageReq* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__NextHandshakeMessageReq_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_NextHandshakeMessageReq_serialize_ex(const grpc_gcp_NextHandshakeMessageReq* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__NextHandshakeMessageReq_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_NextHandshakeMessageReq_clear_in_bytes(grpc_gcp_NextHandshakeMessageReq* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_NextHandshakeMessageReq_in_bytes(const grpc_gcp_NextHandshakeMessageReq* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_gcp_NextHandshakeMessageReq_set_in_bytes(grpc_gcp_NextHandshakeMessageReq *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_gcp_HandshakerReq* grpc_gcp_HandshakerReq_new(upb_Arena* arena) {
  return (grpc_gcp_HandshakerReq*)_upb_Message_New(&grpc__gcp__HandshakerReq_msg_init, arena);
}
UPB_INLINE grpc_gcp_HandshakerReq* grpc_gcp_HandshakerReq_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_HandshakerReq* ret = grpc_gcp_HandshakerReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerReq_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_HandshakerReq* grpc_gcp_HandshakerReq_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_HandshakerReq* ret = grpc_gcp_HandshakerReq_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerReq_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_HandshakerReq_serialize(const grpc_gcp_HandshakerReq* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerReq_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_HandshakerReq_serialize_ex(const grpc_gcp_HandshakerReq* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerReq_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  grpc_gcp_HandshakerReq_req_oneof_client_start = 1,
  grpc_gcp_HandshakerReq_req_oneof_server_start = 2,
  grpc_gcp_HandshakerReq_req_oneof_next = 3,
  grpc_gcp_HandshakerReq_req_oneof_NOT_SET = 0
} grpc_gcp_HandshakerReq_req_oneof_oneofcases;
UPB_INLINE grpc_gcp_HandshakerReq_req_oneof_oneofcases grpc_gcp_HandshakerReq_req_oneof_case(const grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_gcp_HandshakerReq_req_oneof_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerReq_clear_req_oneof(grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &grpc__gcp__HandshakerReq_msg_init, &field);
}
UPB_INLINE void grpc_gcp_HandshakerReq_clear_client_start(grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_StartClientHandshakeReq* grpc_gcp_HandshakerReq_client_start(const grpc_gcp_HandshakerReq* msg) {
  const grpc_gcp_StartClientHandshakeReq* default_val = NULL;
  const grpc_gcp_StartClientHandshakeReq* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartClientHandshakeReq_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerReq_has_client_start(const grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerReq_clear_server_start(grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_StartServerHandshakeReq* grpc_gcp_HandshakerReq_server_start(const grpc_gcp_HandshakerReq* msg) {
  const grpc_gcp_StartServerHandshakeReq* default_val = NULL;
  const grpc_gcp_StartServerHandshakeReq* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerReq_has_server_start(const grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerReq_clear_next(grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_NextHandshakeMessageReq* grpc_gcp_HandshakerReq_next(const grpc_gcp_HandshakerReq* msg) {
  const grpc_gcp_NextHandshakeMessageReq* default_val = NULL;
  const grpc_gcp_NextHandshakeMessageReq* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__NextHandshakeMessageReq_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerReq_has_next(const grpc_gcp_HandshakerReq* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_gcp_HandshakerReq_set_client_start(grpc_gcp_HandshakerReq *msg, grpc_gcp_StartClientHandshakeReq* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartClientHandshakeReq_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_StartClientHandshakeReq* grpc_gcp_HandshakerReq_mutable_client_start(grpc_gcp_HandshakerReq* msg, upb_Arena* arena) {
  struct grpc_gcp_StartClientHandshakeReq* sub = (struct grpc_gcp_StartClientHandshakeReq*)grpc_gcp_HandshakerReq_client_start(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_StartClientHandshakeReq*)_upb_Message_New(&grpc__gcp__StartClientHandshakeReq_msg_init, arena);
    if (sub) grpc_gcp_HandshakerReq_set_client_start(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_HandshakerReq_set_server_start(grpc_gcp_HandshakerReq *msg, grpc_gcp_StartServerHandshakeReq* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__StartServerHandshakeReq_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_StartServerHandshakeReq* grpc_gcp_HandshakerReq_mutable_server_start(grpc_gcp_HandshakerReq* msg, upb_Arena* arena) {
  struct grpc_gcp_StartServerHandshakeReq* sub = (struct grpc_gcp_StartServerHandshakeReq*)grpc_gcp_HandshakerReq_server_start(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_StartServerHandshakeReq*)_upb_Message_New(&grpc__gcp__StartServerHandshakeReq_msg_init, arena);
    if (sub) grpc_gcp_HandshakerReq_set_server_start(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_HandshakerReq_set_next(grpc_gcp_HandshakerReq *msg, grpc_gcp_NextHandshakeMessageReq* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__NextHandshakeMessageReq_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_NextHandshakeMessageReq* grpc_gcp_HandshakerReq_mutable_next(grpc_gcp_HandshakerReq* msg, upb_Arena* arena) {
  struct grpc_gcp_NextHandshakeMessageReq* sub = (struct grpc_gcp_NextHandshakeMessageReq*)grpc_gcp_HandshakerReq_next(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_NextHandshakeMessageReq*)_upb_Message_New(&grpc__gcp__NextHandshakeMessageReq_msg_init, arena);
    if (sub) grpc_gcp_HandshakerReq_set_next(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_gcp_HandshakerResult* grpc_gcp_HandshakerResult_new(upb_Arena* arena) {
  return (grpc_gcp_HandshakerResult*)_upb_Message_New(&grpc__gcp__HandshakerResult_msg_init, arena);
}
UPB_INLINE grpc_gcp_HandshakerResult* grpc_gcp_HandshakerResult_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_HandshakerResult* ret = grpc_gcp_HandshakerResult_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerResult_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_HandshakerResult* grpc_gcp_HandshakerResult_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_HandshakerResult* ret = grpc_gcp_HandshakerResult_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerResult_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_HandshakerResult_serialize(const grpc_gcp_HandshakerResult* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerResult_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_HandshakerResult_serialize_ex(const grpc_gcp_HandshakerResult* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerResult_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_application_protocol(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_HandshakerResult_application_protocol(const grpc_gcp_HandshakerResult* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_record_protocol(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_HandshakerResult_record_protocol(const grpc_gcp_HandshakerResult* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_key_data(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {3, 48, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_HandshakerResult_key_data(const grpc_gcp_HandshakerResult* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, 48, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_peer_identity(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Identity* grpc_gcp_HandshakerResult_peer_identity(const grpc_gcp_HandshakerResult* msg) {
  const grpc_gcp_Identity* default_val = NULL;
  const grpc_gcp_Identity* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerResult_has_peer_identity(const grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_local_identity(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_Identity* grpc_gcp_HandshakerResult_local_identity(const grpc_gcp_HandshakerResult* msg) {
  const grpc_gcp_Identity* default_val = NULL;
  const grpc_gcp_Identity* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerResult_has_local_identity(const grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_keep_channel_open(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool grpc_gcp_HandshakerResult_keep_channel_open(const grpc_gcp_HandshakerResult* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_peer_rpc_versions(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_RpcProtocolVersions* grpc_gcp_HandshakerResult_peer_rpc_versions(const grpc_gcp_HandshakerResult* msg) {
  const struct grpc_gcp_RpcProtocolVersions* default_val = NULL;
  const struct grpc_gcp_RpcProtocolVersions* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerResult_has_peer_rpc_versions(const grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_max_frame_size(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_HandshakerResult_max_frame_size(const grpc_gcp_HandshakerResult* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {8, UPB_SIZE(24, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResult_clear_transport_protocol(grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_NegotiatedTransportProtocol* grpc_gcp_HandshakerResult_transport_protocol(const grpc_gcp_HandshakerResult* msg) {
  const struct grpc_gcp_NegotiatedTransportProtocol* default_val = NULL;
  const struct grpc_gcp_NegotiatedTransportProtocol* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__NegotiatedTransportProtocol_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerResult_has_transport_protocol(const grpc_gcp_HandshakerResult* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_gcp_HandshakerResult_set_application_protocol(grpc_gcp_HandshakerResult *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_record_protocol(grpc_gcp_HandshakerResult *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_key_data(grpc_gcp_HandshakerResult *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, 48, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_peer_identity(grpc_gcp_HandshakerResult *msg, grpc_gcp_Identity* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Identity* grpc_gcp_HandshakerResult_mutable_peer_identity(grpc_gcp_HandshakerResult* msg, upb_Arena* arena) {
  struct grpc_gcp_Identity* sub = (struct grpc_gcp_Identity*)grpc_gcp_HandshakerResult_peer_identity(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Identity*)_upb_Message_New(&grpc__gcp__Identity_msg_init, arena);
    if (sub) grpc_gcp_HandshakerResult_set_peer_identity(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_local_identity(grpc_gcp_HandshakerResult *msg, grpc_gcp_Identity* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__Identity_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_Identity* grpc_gcp_HandshakerResult_mutable_local_identity(grpc_gcp_HandshakerResult* msg, upb_Arena* arena) {
  struct grpc_gcp_Identity* sub = (struct grpc_gcp_Identity*)grpc_gcp_HandshakerResult_local_identity(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_Identity*)_upb_Message_New(&grpc__gcp__Identity_msg_init, arena);
    if (sub) grpc_gcp_HandshakerResult_set_local_identity(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_keep_channel_open(grpc_gcp_HandshakerResult *msg, bool value) {
  const upb_MiniTableField field = {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_peer_rpc_versions(grpc_gcp_HandshakerResult *msg, struct grpc_gcp_RpcProtocolVersions* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_RpcProtocolVersions* grpc_gcp_HandshakerResult_mutable_peer_rpc_versions(grpc_gcp_HandshakerResult* msg, upb_Arena* arena) {
  struct grpc_gcp_RpcProtocolVersions* sub = (struct grpc_gcp_RpcProtocolVersions*)grpc_gcp_HandshakerResult_peer_rpc_versions(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_RpcProtocolVersions*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions_msg_init, arena);
    if (sub) grpc_gcp_HandshakerResult_set_peer_rpc_versions(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_max_frame_size(grpc_gcp_HandshakerResult *msg, uint32_t value) {
  const upb_MiniTableField field = {8, UPB_SIZE(24, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResult_set_transport_protocol(grpc_gcp_HandshakerResult *msg, struct grpc_gcp_NegotiatedTransportProtocol* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(28, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__NegotiatedTransportProtocol_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_NegotiatedTransportProtocol* grpc_gcp_HandshakerResult_mutable_transport_protocol(grpc_gcp_HandshakerResult* msg, upb_Arena* arena) {
  struct grpc_gcp_NegotiatedTransportProtocol* sub = (struct grpc_gcp_NegotiatedTransportProtocol*)grpc_gcp_HandshakerResult_transport_protocol(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_NegotiatedTransportProtocol*)_upb_Message_New(&grpc__gcp__NegotiatedTransportProtocol_msg_init, arena);
    if (sub) grpc_gcp_HandshakerResult_set_transport_protocol(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_gcp_HandshakerStatus* grpc_gcp_HandshakerStatus_new(upb_Arena* arena) {
  return (grpc_gcp_HandshakerStatus*)_upb_Message_New(&grpc__gcp__HandshakerStatus_msg_init, arena);
}
UPB_INLINE grpc_gcp_HandshakerStatus* grpc_gcp_HandshakerStatus_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_HandshakerStatus* ret = grpc_gcp_HandshakerStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerStatus_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_HandshakerStatus* grpc_gcp_HandshakerStatus_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_HandshakerStatus* ret = grpc_gcp_HandshakerStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerStatus_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_HandshakerStatus_serialize(const grpc_gcp_HandshakerStatus* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerStatus_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_HandshakerStatus_serialize_ex(const grpc_gcp_HandshakerStatus* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerStatus_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_HandshakerStatus_clear_code(grpc_gcp_HandshakerStatus* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_HandshakerStatus_code(const grpc_gcp_HandshakerStatus* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerStatus_clear_details(grpc_gcp_HandshakerStatus* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_HandshakerStatus_details(const grpc_gcp_HandshakerStatus* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_gcp_HandshakerStatus_set_code(grpc_gcp_HandshakerStatus *msg, uint32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerStatus_set_details(grpc_gcp_HandshakerStatus *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_gcp_HandshakerResp* grpc_gcp_HandshakerResp_new(upb_Arena* arena) {
  return (grpc_gcp_HandshakerResp*)_upb_Message_New(&grpc__gcp__HandshakerResp_msg_init, arena);
}
UPB_INLINE grpc_gcp_HandshakerResp* grpc_gcp_HandshakerResp_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_HandshakerResp* ret = grpc_gcp_HandshakerResp_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerResp_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_HandshakerResp* grpc_gcp_HandshakerResp_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_HandshakerResp* ret = grpc_gcp_HandshakerResp_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__HandshakerResp_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_HandshakerResp_serialize(const grpc_gcp_HandshakerResp* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerResp_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_HandshakerResp_serialize_ex(const grpc_gcp_HandshakerResp* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__HandshakerResp_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_HandshakerResp_clear_out_frames(grpc_gcp_HandshakerResp* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_HandshakerResp_out_frames(const grpc_gcp_HandshakerResp* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResp_clear_bytes_consumed(grpc_gcp_HandshakerResp* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t grpc_gcp_HandshakerResp_bytes_consumed(const grpc_gcp_HandshakerResp* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_HandshakerResp_clear_result(grpc_gcp_HandshakerResp* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_HandshakerResult* grpc_gcp_HandshakerResp_result(const grpc_gcp_HandshakerResp* msg) {
  const grpc_gcp_HandshakerResult* default_val = NULL;
  const grpc_gcp_HandshakerResult* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__HandshakerResult_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerResp_has_result(const grpc_gcp_HandshakerResp* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_HandshakerResp_clear_status(grpc_gcp_HandshakerResp* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_gcp_HandshakerStatus* grpc_gcp_HandshakerResp_status(const grpc_gcp_HandshakerResp* msg) {
  const grpc_gcp_HandshakerStatus* default_val = NULL;
  const grpc_gcp_HandshakerStatus* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__HandshakerStatus_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_HandshakerResp_has_status(const grpc_gcp_HandshakerResp* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_gcp_HandshakerResp_set_out_frames(grpc_gcp_HandshakerResp *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResp_set_bytes_consumed(grpc_gcp_HandshakerResp *msg, uint32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_HandshakerResp_set_result(grpc_gcp_HandshakerResp *msg, grpc_gcp_HandshakerResult* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__HandshakerResult_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_HandshakerResult* grpc_gcp_HandshakerResp_mutable_result(grpc_gcp_HandshakerResp* msg, upb_Arena* arena) {
  struct grpc_gcp_HandshakerResult* sub = (struct grpc_gcp_HandshakerResult*)grpc_gcp_HandshakerResp_result(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_HandshakerResult*)_upb_Message_New(&grpc__gcp__HandshakerResult_msg_init, arena);
    if (sub) grpc_gcp_HandshakerResp_set_result(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_HandshakerResp_set_status(grpc_gcp_HandshakerResp *msg, grpc_gcp_HandshakerStatus* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__HandshakerStatus_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_HandshakerStatus* grpc_gcp_HandshakerResp_mutable_status(grpc_gcp_HandshakerResp* msg, upb_Arena* arena) {
  struct grpc_gcp_HandshakerStatus* sub = (struct grpc_gcp_HandshakerStatus*)grpc_gcp_HandshakerResp_status(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_HandshakerStatus*)_upb_Message_New(&grpc__gcp__HandshakerStatus_msg_init, arena);
    if (sub) grpc_gcp_HandshakerResp_set_status(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
