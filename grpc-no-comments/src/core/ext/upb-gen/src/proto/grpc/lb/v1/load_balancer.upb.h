
#ifndef SRC_PROTO_GRPC_LB_V1_LOAD_BALANCER_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_LB_V1_LOAD_BALANCER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/lb/v1/load_balancer.upb_minitable.h"

#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_lb_v1_LoadBalanceRequest { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_LoadBalanceRequest;
typedef struct grpc_lb_v1_InitialLoadBalanceRequest { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_InitialLoadBalanceRequest;
typedef struct grpc_lb_v1_ClientStatsPerToken { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_ClientStatsPerToken;
typedef struct grpc_lb_v1_ClientStats { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_ClientStats;
typedef struct grpc_lb_v1_LoadBalanceResponse { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_LoadBalanceResponse;
typedef struct grpc_lb_v1_FallbackResponse { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_FallbackResponse;
typedef struct grpc_lb_v1_InitialLoadBalanceResponse { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_InitialLoadBalanceResponse;
typedef struct grpc_lb_v1_ServerList { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_ServerList;
typedef struct grpc_lb_v1_Server { upb_Message UPB_PRIVATE(base); } grpc_lb_v1_Server;
struct google_protobuf_Duration;
struct google_protobuf_Timestamp;

UPB_INLINE grpc_lb_v1_LoadBalanceRequest* grpc_lb_v1_LoadBalanceRequest_new(upb_Arena* arena) {
  return (grpc_lb_v1_LoadBalanceRequest*)_upb_Message_New(&grpc__lb__v1__LoadBalanceRequest_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_LoadBalanceRequest* grpc_lb_v1_LoadBalanceRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_LoadBalanceRequest* ret = grpc_lb_v1_LoadBalanceRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__LoadBalanceRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_LoadBalanceRequest* grpc_lb_v1_LoadBalanceRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_LoadBalanceRequest* ret = grpc_lb_v1_LoadBalanceRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__LoadBalanceRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_LoadBalanceRequest_serialize(const grpc_lb_v1_LoadBalanceRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__LoadBalanceRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_LoadBalanceRequest_serialize_ex(const grpc_lb_v1_LoadBalanceRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__LoadBalanceRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_initial_request = 1,
  grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_client_stats = 2,
  grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_NOT_SET = 0
} grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_oneofcases;
UPB_INLINE grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_oneofcases grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_case(const grpc_lb_v1_LoadBalanceRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lb_v1_LoadBalanceRequest_load_balance_request_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceRequest_clear_load_balance_request_type(grpc_lb_v1_LoadBalanceRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &grpc__lb__v1__LoadBalanceRequest_msg_init, &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceRequest_clear_initial_request(grpc_lb_v1_LoadBalanceRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_InitialLoadBalanceRequest* grpc_lb_v1_LoadBalanceRequest_initial_request(const grpc_lb_v1_LoadBalanceRequest* msg) {
  const grpc_lb_v1_InitialLoadBalanceRequest* default_val = NULL;
  const grpc_lb_v1_InitialLoadBalanceRequest* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__InitialLoadBalanceRequest_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_LoadBalanceRequest_has_initial_request(const grpc_lb_v1_LoadBalanceRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceRequest_clear_client_stats(grpc_lb_v1_LoadBalanceRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_ClientStats* grpc_lb_v1_LoadBalanceRequest_client_stats(const grpc_lb_v1_LoadBalanceRequest* msg) {
  const grpc_lb_v1_ClientStats* default_val = NULL;
  const grpc_lb_v1_ClientStats* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStats_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_LoadBalanceRequest_has_client_stats(const grpc_lb_v1_LoadBalanceRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_lb_v1_LoadBalanceRequest_set_initial_request(grpc_lb_v1_LoadBalanceRequest *msg, grpc_lb_v1_InitialLoadBalanceRequest* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__InitialLoadBalanceRequest_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lb_v1_InitialLoadBalanceRequest* grpc_lb_v1_LoadBalanceRequest_mutable_initial_request(grpc_lb_v1_LoadBalanceRequest* msg, upb_Arena* arena) {
  struct grpc_lb_v1_InitialLoadBalanceRequest* sub = (struct grpc_lb_v1_InitialLoadBalanceRequest*)grpc_lb_v1_LoadBalanceRequest_initial_request(msg);
  if (sub == NULL) {
    sub = (struct grpc_lb_v1_InitialLoadBalanceRequest*)_upb_Message_New(&grpc__lb__v1__InitialLoadBalanceRequest_msg_init, arena);
    if (sub) grpc_lb_v1_LoadBalanceRequest_set_initial_request(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lb_v1_LoadBalanceRequest_set_client_stats(grpc_lb_v1_LoadBalanceRequest *msg, grpc_lb_v1_ClientStats* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStats_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lb_v1_ClientStats* grpc_lb_v1_LoadBalanceRequest_mutable_client_stats(grpc_lb_v1_LoadBalanceRequest* msg, upb_Arena* arena) {
  struct grpc_lb_v1_ClientStats* sub = (struct grpc_lb_v1_ClientStats*)grpc_lb_v1_LoadBalanceRequest_client_stats(msg);
  if (sub == NULL) {
    sub = (struct grpc_lb_v1_ClientStats*)_upb_Message_New(&grpc__lb__v1__ClientStats_msg_init, arena);
    if (sub) grpc_lb_v1_LoadBalanceRequest_set_client_stats(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_lb_v1_InitialLoadBalanceRequest* grpc_lb_v1_InitialLoadBalanceRequest_new(upb_Arena* arena) {
  return (grpc_lb_v1_InitialLoadBalanceRequest*)_upb_Message_New(&grpc__lb__v1__InitialLoadBalanceRequest_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_InitialLoadBalanceRequest* grpc_lb_v1_InitialLoadBalanceRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_InitialLoadBalanceRequest* ret = grpc_lb_v1_InitialLoadBalanceRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__InitialLoadBalanceRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_InitialLoadBalanceRequest* grpc_lb_v1_InitialLoadBalanceRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_InitialLoadBalanceRequest* ret = grpc_lb_v1_InitialLoadBalanceRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__InitialLoadBalanceRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_InitialLoadBalanceRequest_serialize(const grpc_lb_v1_InitialLoadBalanceRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__InitialLoadBalanceRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_InitialLoadBalanceRequest_serialize_ex(const grpc_lb_v1_InitialLoadBalanceRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__InitialLoadBalanceRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lb_v1_InitialLoadBalanceRequest_clear_name(grpc_lb_v1_InitialLoadBalanceRequest* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lb_v1_InitialLoadBalanceRequest_name(const grpc_lb_v1_InitialLoadBalanceRequest* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lb_v1_InitialLoadBalanceRequest_set_name(grpc_lb_v1_InitialLoadBalanceRequest *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lb_v1_ClientStatsPerToken* grpc_lb_v1_ClientStatsPerToken_new(upb_Arena* arena) {
  return (grpc_lb_v1_ClientStatsPerToken*)_upb_Message_New(&grpc__lb__v1__ClientStatsPerToken_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_ClientStatsPerToken* grpc_lb_v1_ClientStatsPerToken_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_ClientStatsPerToken* ret = grpc_lb_v1_ClientStatsPerToken_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__ClientStatsPerToken_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_ClientStatsPerToken* grpc_lb_v1_ClientStatsPerToken_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_ClientStatsPerToken* ret = grpc_lb_v1_ClientStatsPerToken_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__ClientStatsPerToken_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_ClientStatsPerToken_serialize(const grpc_lb_v1_ClientStatsPerToken* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__ClientStatsPerToken_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_ClientStatsPerToken_serialize_ex(const grpc_lb_v1_ClientStatsPerToken* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__ClientStatsPerToken_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lb_v1_ClientStatsPerToken_clear_load_balance_token(grpc_lb_v1_ClientStatsPerToken* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lb_v1_ClientStatsPerToken_load_balance_token(const grpc_lb_v1_ClientStatsPerToken* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_ClientStatsPerToken_clear_num_calls(grpc_lb_v1_ClientStatsPerToken* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t grpc_lb_v1_ClientStatsPerToken_num_calls(const grpc_lb_v1_ClientStatsPerToken* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lb_v1_ClientStatsPerToken_set_load_balance_token(grpc_lb_v1_ClientStatsPerToken *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_ClientStatsPerToken_set_num_calls(grpc_lb_v1_ClientStatsPerToken *msg, int64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_lb_v1_ClientStats* grpc_lb_v1_ClientStats_new(upb_Arena* arena) {
  return (grpc_lb_v1_ClientStats*)_upb_Message_New(&grpc__lb__v1__ClientStats_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_ClientStats* grpc_lb_v1_ClientStats_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_ClientStats* ret = grpc_lb_v1_ClientStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__ClientStats_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_ClientStats* grpc_lb_v1_ClientStats_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_ClientStats* ret = grpc_lb_v1_ClientStats_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__ClientStats_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_ClientStats_serialize(const grpc_lb_v1_ClientStats* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__ClientStats_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_ClientStats_serialize_ex(const grpc_lb_v1_ClientStats* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__ClientStats_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lb_v1_ClientStats_clear_timestamp(grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* grpc_lb_v1_ClientStats_timestamp(const grpc_lb_v1_ClientStats* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_ClientStats_has_timestamp(const grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lb_v1_ClientStats_clear_num_calls_started(grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t grpc_lb_v1_ClientStats_num_calls_started(const grpc_lb_v1_ClientStats* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_ClientStats_clear_num_calls_finished(grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t grpc_lb_v1_ClientStats_num_calls_finished(const grpc_lb_v1_ClientStats* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_ClientStats_clear_num_calls_finished_with_client_failed_to_send(grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {6, 40, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t grpc_lb_v1_ClientStats_num_calls_finished_with_client_failed_to_send(const grpc_lb_v1_ClientStats* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {6, 40, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_ClientStats_clear_num_calls_finished_known_received(grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {7, 48, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t grpc_lb_v1_ClientStats_num_calls_finished_known_received(const grpc_lb_v1_ClientStats* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {7, 48, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_ClientStats_clear_calls_finished_with_drop(grpc_lb_v1_ClientStats* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_ClientStatsPerToken* const* grpc_lb_v1_ClientStats_calls_finished_with_drop(const grpc_lb_v1_ClientStats* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStatsPerToken_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lb_v1_ClientStatsPerToken* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lb_v1_ClientStats_calls_finished_with_drop_upb_array(const grpc_lb_v1_ClientStats* msg, size_t* size) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStatsPerToken_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lb_v1_ClientStats_calls_finished_with_drop_mutable_upb_array(grpc_lb_v1_ClientStats* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStatsPerToken_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void grpc_lb_v1_ClientStats_set_timestamp(grpc_lb_v1_ClientStats *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* grpc_lb_v1_ClientStats_mutable_timestamp(grpc_lb_v1_ClientStats* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)grpc_lb_v1_ClientStats_timestamp(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) grpc_lb_v1_ClientStats_set_timestamp(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lb_v1_ClientStats_set_num_calls_started(grpc_lb_v1_ClientStats *msg, int64_t value) {
  const upb_MiniTableField field = {2, 24, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_ClientStats_set_num_calls_finished(grpc_lb_v1_ClientStats *msg, int64_t value) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_ClientStats_set_num_calls_finished_with_client_failed_to_send(grpc_lb_v1_ClientStats *msg, int64_t value) {
  const upb_MiniTableField field = {6, 40, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_ClientStats_set_num_calls_finished_known_received(grpc_lb_v1_ClientStats *msg, int64_t value) {
  const upb_MiniTableField field = {7, 48, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE grpc_lb_v1_ClientStatsPerToken** grpc_lb_v1_ClientStats_mutable_calls_finished_with_drop(grpc_lb_v1_ClientStats* msg, size_t* size) {
  upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStatsPerToken_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lb_v1_ClientStatsPerToken**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lb_v1_ClientStatsPerToken** grpc_lb_v1_ClientStats_resize_calls_finished_with_drop(grpc_lb_v1_ClientStats* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lb_v1_ClientStatsPerToken**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lb_v1_ClientStatsPerToken* grpc_lb_v1_ClientStats_add_calls_finished_with_drop(grpc_lb_v1_ClientStats* msg, upb_Arena* arena) {
  upb_MiniTableField field = {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ClientStatsPerToken_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lb_v1_ClientStatsPerToken* sub = (struct grpc_lb_v1_ClientStatsPerToken*)_upb_Message_New(&grpc__lb__v1__ClientStatsPerToken_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE grpc_lb_v1_LoadBalanceResponse* grpc_lb_v1_LoadBalanceResponse_new(upb_Arena* arena) {
  return (grpc_lb_v1_LoadBalanceResponse*)_upb_Message_New(&grpc__lb__v1__LoadBalanceResponse_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_LoadBalanceResponse* grpc_lb_v1_LoadBalanceResponse_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_LoadBalanceResponse* ret = grpc_lb_v1_LoadBalanceResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__LoadBalanceResponse_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_LoadBalanceResponse* grpc_lb_v1_LoadBalanceResponse_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_LoadBalanceResponse* ret = grpc_lb_v1_LoadBalanceResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__LoadBalanceResponse_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_LoadBalanceResponse_serialize(const grpc_lb_v1_LoadBalanceResponse* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__LoadBalanceResponse_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_LoadBalanceResponse_serialize_ex(const grpc_lb_v1_LoadBalanceResponse* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__LoadBalanceResponse_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_initial_response = 1,
  grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_server_list = 2,
  grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_fallback_response = 3,
  grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_NOT_SET = 0
} grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_oneofcases;
UPB_INLINE grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_oneofcases grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_case(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lb_v1_LoadBalanceResponse_load_balance_response_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_clear_load_balance_response_type(grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &grpc__lb__v1__LoadBalanceResponse_msg_init, &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_clear_initial_response(grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_InitialLoadBalanceResponse* grpc_lb_v1_LoadBalanceResponse_initial_response(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const grpc_lb_v1_InitialLoadBalanceResponse* default_val = NULL;
  const grpc_lb_v1_InitialLoadBalanceResponse* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__InitialLoadBalanceResponse_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_LoadBalanceResponse_has_initial_response(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_clear_server_list(grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_ServerList* grpc_lb_v1_LoadBalanceResponse_server_list(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const grpc_lb_v1_ServerList* default_val = NULL;
  const grpc_lb_v1_ServerList* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ServerList_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_LoadBalanceResponse_has_server_list(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_clear_fallback_response(grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_FallbackResponse* grpc_lb_v1_LoadBalanceResponse_fallback_response(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const grpc_lb_v1_FallbackResponse* default_val = NULL;
  const grpc_lb_v1_FallbackResponse* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__FallbackResponse_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_LoadBalanceResponse_has_fallback_response(const grpc_lb_v1_LoadBalanceResponse* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_set_initial_response(grpc_lb_v1_LoadBalanceResponse *msg, grpc_lb_v1_InitialLoadBalanceResponse* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__InitialLoadBalanceResponse_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lb_v1_InitialLoadBalanceResponse* grpc_lb_v1_LoadBalanceResponse_mutable_initial_response(grpc_lb_v1_LoadBalanceResponse* msg, upb_Arena* arena) {
  struct grpc_lb_v1_InitialLoadBalanceResponse* sub = (struct grpc_lb_v1_InitialLoadBalanceResponse*)grpc_lb_v1_LoadBalanceResponse_initial_response(msg);
  if (sub == NULL) {
    sub = (struct grpc_lb_v1_InitialLoadBalanceResponse*)_upb_Message_New(&grpc__lb__v1__InitialLoadBalanceResponse_msg_init, arena);
    if (sub) grpc_lb_v1_LoadBalanceResponse_set_initial_response(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_set_server_list(grpc_lb_v1_LoadBalanceResponse *msg, grpc_lb_v1_ServerList* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__ServerList_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lb_v1_ServerList* grpc_lb_v1_LoadBalanceResponse_mutable_server_list(grpc_lb_v1_LoadBalanceResponse* msg, upb_Arena* arena) {
  struct grpc_lb_v1_ServerList* sub = (struct grpc_lb_v1_ServerList*)grpc_lb_v1_LoadBalanceResponse_server_list(msg);
  if (sub == NULL) {
    sub = (struct grpc_lb_v1_ServerList*)_upb_Message_New(&grpc__lb__v1__ServerList_msg_init, arena);
    if (sub) grpc_lb_v1_LoadBalanceResponse_set_server_list(msg, sub);
  }
  return sub;
}
UPB_INLINE void grpc_lb_v1_LoadBalanceResponse_set_fallback_response(grpc_lb_v1_LoadBalanceResponse *msg, grpc_lb_v1_FallbackResponse* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__FallbackResponse_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct grpc_lb_v1_FallbackResponse* grpc_lb_v1_LoadBalanceResponse_mutable_fallback_response(grpc_lb_v1_LoadBalanceResponse* msg, upb_Arena* arena) {
  struct grpc_lb_v1_FallbackResponse* sub = (struct grpc_lb_v1_FallbackResponse*)grpc_lb_v1_LoadBalanceResponse_fallback_response(msg);
  if (sub == NULL) {
    sub = (struct grpc_lb_v1_FallbackResponse*)_upb_Message_New(&grpc__lb__v1__FallbackResponse_msg_init, arena);
    if (sub) grpc_lb_v1_LoadBalanceResponse_set_fallback_response(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_lb_v1_FallbackResponse* grpc_lb_v1_FallbackResponse_new(upb_Arena* arena) {
  return (grpc_lb_v1_FallbackResponse*)_upb_Message_New(&grpc__lb__v1__FallbackResponse_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_FallbackResponse* grpc_lb_v1_FallbackResponse_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_FallbackResponse* ret = grpc_lb_v1_FallbackResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__FallbackResponse_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_FallbackResponse* grpc_lb_v1_FallbackResponse_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_FallbackResponse* ret = grpc_lb_v1_FallbackResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__FallbackResponse_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_FallbackResponse_serialize(const grpc_lb_v1_FallbackResponse* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__FallbackResponse_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_FallbackResponse_serialize_ex(const grpc_lb_v1_FallbackResponse* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__FallbackResponse_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE grpc_lb_v1_InitialLoadBalanceResponse* grpc_lb_v1_InitialLoadBalanceResponse_new(upb_Arena* arena) {
  return (grpc_lb_v1_InitialLoadBalanceResponse*)_upb_Message_New(&grpc__lb__v1__InitialLoadBalanceResponse_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_InitialLoadBalanceResponse* grpc_lb_v1_InitialLoadBalanceResponse_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_InitialLoadBalanceResponse* ret = grpc_lb_v1_InitialLoadBalanceResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__InitialLoadBalanceResponse_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_InitialLoadBalanceResponse* grpc_lb_v1_InitialLoadBalanceResponse_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_InitialLoadBalanceResponse* ret = grpc_lb_v1_InitialLoadBalanceResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__InitialLoadBalanceResponse_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_InitialLoadBalanceResponse_serialize(const grpc_lb_v1_InitialLoadBalanceResponse* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__InitialLoadBalanceResponse_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_InitialLoadBalanceResponse_serialize_ex(const grpc_lb_v1_InitialLoadBalanceResponse* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__InitialLoadBalanceResponse_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lb_v1_InitialLoadBalanceResponse_clear_client_stats_report_interval(grpc_lb_v1_InitialLoadBalanceResponse* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* grpc_lb_v1_InitialLoadBalanceResponse_client_stats_report_interval(const grpc_lb_v1_InitialLoadBalanceResponse* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool grpc_lb_v1_InitialLoadBalanceResponse_has_client_stats_report_interval(const grpc_lb_v1_InitialLoadBalanceResponse* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void grpc_lb_v1_InitialLoadBalanceResponse_set_client_stats_report_interval(grpc_lb_v1_InitialLoadBalanceResponse *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* grpc_lb_v1_InitialLoadBalanceResponse_mutable_client_stats_report_interval(grpc_lb_v1_InitialLoadBalanceResponse* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)grpc_lb_v1_InitialLoadBalanceResponse_client_stats_report_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) grpc_lb_v1_InitialLoadBalanceResponse_set_client_stats_report_interval(msg, sub);
  }
  return sub;
}

UPB_INLINE grpc_lb_v1_ServerList* grpc_lb_v1_ServerList_new(upb_Arena* arena) {
  return (grpc_lb_v1_ServerList*)_upb_Message_New(&grpc__lb__v1__ServerList_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_ServerList* grpc_lb_v1_ServerList_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_ServerList* ret = grpc_lb_v1_ServerList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__ServerList_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_ServerList* grpc_lb_v1_ServerList_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_ServerList* ret = grpc_lb_v1_ServerList_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__ServerList_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_ServerList_serialize(const grpc_lb_v1_ServerList* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__ServerList_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_ServerList_serialize_ex(const grpc_lb_v1_ServerList* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__ServerList_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lb_v1_ServerList_clear_servers(grpc_lb_v1_ServerList* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const grpc_lb_v1_Server* const* grpc_lb_v1_ServerList_servers(const grpc_lb_v1_ServerList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__Server_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const grpc_lb_v1_Server* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _grpc_lb_v1_ServerList_servers_upb_array(const grpc_lb_v1_ServerList* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__Server_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _grpc_lb_v1_ServerList_servers_mutable_upb_array(grpc_lb_v1_ServerList* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__Server_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE grpc_lb_v1_Server** grpc_lb_v1_ServerList_mutable_servers(grpc_lb_v1_ServerList* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__Server_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (grpc_lb_v1_Server**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE grpc_lb_v1_Server** grpc_lb_v1_ServerList_resize_servers(grpc_lb_v1_ServerList* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (grpc_lb_v1_Server**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct grpc_lb_v1_Server* grpc_lb_v1_ServerList_add_servers(grpc_lb_v1_ServerList* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&grpc__lb__v1__Server_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct grpc_lb_v1_Server* sub = (struct grpc_lb_v1_Server*)_upb_Message_New(&grpc__lb__v1__Server_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE grpc_lb_v1_Server* grpc_lb_v1_Server_new(upb_Arena* arena) {
  return (grpc_lb_v1_Server*)_upb_Message_New(&grpc__lb__v1__Server_msg_init, arena);
}
UPB_INLINE grpc_lb_v1_Server* grpc_lb_v1_Server_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_lb_v1_Server* ret = grpc_lb_v1_Server_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__Server_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_lb_v1_Server* grpc_lb_v1_Server_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_lb_v1_Server* ret = grpc_lb_v1_Server_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__lb__v1__Server_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_lb_v1_Server_serialize(const grpc_lb_v1_Server* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__Server_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_lb_v1_Server_serialize_ex(const grpc_lb_v1_Server* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__lb__v1__Server_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_lb_v1_Server_clear_ip_address(grpc_lb_v1_Server* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lb_v1_Server_ip_address(const grpc_lb_v1_Server* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_Server_clear_port(grpc_lb_v1_Server* msg) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_lb_v1_Server_port(const grpc_lb_v1_Server* msg) {
  int32_t default_val = (int32_t)0;
  int32_t ret;
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_Server_clear_load_balance_token(grpc_lb_v1_Server* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_lb_v1_Server_load_balance_token(const grpc_lb_v1_Server* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void grpc_lb_v1_Server_clear_drop(grpc_lb_v1_Server* msg) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool grpc_lb_v1_Server_drop(const grpc_lb_v1_Server* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_lb_v1_Server_set_ip_address(grpc_lb_v1_Server *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_Server_set_port(grpc_lb_v1_Server *msg, int32_t value) {
  const upb_MiniTableField field = {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_Server_set_load_balance_token(grpc_lb_v1_Server *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void grpc_lb_v1_Server_set_drop(grpc_lb_v1_Server *msg, bool value) {
  const upb_MiniTableField field = {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
