
#ifndef SRC_PROTO_GRPC_GCP_ALTSCONTEXT_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_GCP_ALTSCONTEXT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/gcp/altscontext.upb_minitable.h"

#include "src/proto/grpc/gcp/transport_security_common.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_gcp_AltsContext { upb_Message UPB_PRIVATE(base); } grpc_gcp_AltsContext;
struct grpc_gcp_RpcProtocolVersions;

UPB_INLINE grpc_gcp_AltsContext* grpc_gcp_AltsContext_new(upb_Arena* arena) {
  return (grpc_gcp_AltsContext*)_upb_Message_New(&grpc__gcp__AltsContext_msg_init, arena);
}
UPB_INLINE grpc_gcp_AltsContext* grpc_gcp_AltsContext_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_gcp_AltsContext* ret = grpc_gcp_AltsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__AltsContext_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_gcp_AltsContext* grpc_gcp_AltsContext_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_gcp_AltsContext* ret = grpc_gcp_AltsContext_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__gcp__AltsContext_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_gcp_AltsContext_serialize(const grpc_gcp_AltsContext* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__AltsContext_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_gcp_AltsContext_serialize_ex(const grpc_gcp_AltsContext* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__gcp__AltsContext_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_gcp_AltsContext_clear_application_protocol(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_AltsContext_application_protocol(const grpc_gcp_AltsContext* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_AltsContext_clear_record_protocol(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_AltsContext_record_protocol(const grpc_gcp_AltsContext* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_AltsContext_clear_security_level(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_gcp_AltsContext_security_level(const grpc_gcp_AltsContext* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_AltsContext_clear_peer_service_account(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_AltsContext_peer_service_account(const grpc_gcp_AltsContext* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_AltsContext_clear_local_service_account(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_gcp_AltsContext_local_service_account(const grpc_gcp_AltsContext* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_gcp_AltsContext_clear_peer_rpc_versions(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct grpc_gcp_RpcProtocolVersions* grpc_gcp_AltsContext_peer_rpc_versions(const grpc_gcp_AltsContext* msg) {
  const struct grpc_gcp_RpcProtocolVersions* default_val = NULL;
  const struct grpc_gcp_RpcProtocolVersions* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(16, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_gcp_AltsContext_has_peer_rpc_versions(const grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_gcp_AltsContext_clear_peer_attributes(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t grpc_gcp_AltsContext_peer_attributes_size(const grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool grpc_gcp_AltsContext_peer_attributes_get(const grpc_gcp_AltsContext* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__AltsContext__PeerAttributesEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool grpc_gcp_AltsContext_peer_attributes_next(const grpc_gcp_AltsContext* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__AltsContext__PeerAttributesEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _grpc_gcp_AltsContext_peer_attributes_upb_map(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__AltsContext__PeerAttributesEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _grpc_gcp_AltsContext_peer_attributes_mutable_upb_map(grpc_gcp_AltsContext* msg, upb_Arena* a) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__AltsContext__PeerAttributesEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}

UPB_INLINE void grpc_gcp_AltsContext_set_application_protocol(grpc_gcp_AltsContext *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_AltsContext_set_record_protocol(grpc_gcp_AltsContext *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_AltsContext_set_security_level(grpc_gcp_AltsContext *msg, int32_t value) {
  const upb_MiniTableField field = {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_AltsContext_set_peer_service_account(grpc_gcp_AltsContext *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_AltsContext_set_local_service_account(grpc_gcp_AltsContext *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_gcp_AltsContext_set_peer_rpc_versions(grpc_gcp_AltsContext *msg, struct grpc_gcp_RpcProtocolVersions* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__RpcProtocolVersions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_gcp_RpcProtocolVersions* grpc_gcp_AltsContext_mutable_peer_rpc_versions(grpc_gcp_AltsContext* msg, upb_Arena* arena) {
  struct grpc_gcp_RpcProtocolVersions* sub = (struct grpc_gcp_RpcProtocolVersions*)grpc_gcp_AltsContext_peer_rpc_versions(msg);
  if (sub == NULL) {
    sub = (struct grpc_gcp_RpcProtocolVersions*)_upb_Message_New(&grpc__gcp__RpcProtocolVersions_msg_init, arena);
    if (sub) grpc_gcp_AltsContext_set_peer_rpc_versions(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_gcp_AltsContext_peer_attributes_clear(grpc_gcp_AltsContext* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool grpc_gcp_AltsContext_peer_attributes_set(grpc_gcp_AltsContext* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__gcp__AltsContext__PeerAttributesEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool grpc_gcp_AltsContext_peer_attributes_delete(grpc_gcp_AltsContext* msg, upb_StringView key) {
  const upb_MiniTableField field = {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
