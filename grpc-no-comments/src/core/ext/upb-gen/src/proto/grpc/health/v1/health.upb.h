
#ifndef SRC_PROTO_GRPC_HEALTH_V1_HEALTH_PROTO_UPB_H__UPB_H_
#define SRC_PROTO_GRPC_HEALTH_V1_HEALTH_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "src/proto/grpc/health/v1/health.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct grpc_health_v1_HealthCheckRequest { upb_Message UPB_PRIVATE(base); } grpc_health_v1_HealthCheckRequest;
typedef struct grpc_health_v1_HealthCheckResponse { upb_Message UPB_PRIVATE(base); } grpc_health_v1_HealthCheckResponse;

typedef enum {
  grpc_health_v1_HealthCheckResponse_UNKNOWN = 0,
  grpc_health_v1_HealthCheckResponse_SERVING = 1,
  grpc_health_v1_HealthCheckResponse_NOT_SERVING = 2,
  grpc_health_v1_HealthCheckResponse_SERVICE_UNKNOWN = 3
} grpc_health_v1_HealthCheckResponse_ServingStatus;

UPB_INLINE grpc_health_v1_HealthCheckRequest* grpc_health_v1_HealthCheckRequest_new(upb_Arena* arena) {
  return (grpc_health_v1_HealthCheckRequest*)_upb_Message_New(&grpc__health__v1__HealthCheckRequest_msg_init, arena);
}
UPB_INLINE grpc_health_v1_HealthCheckRequest* grpc_health_v1_HealthCheckRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_health_v1_HealthCheckRequest* ret = grpc_health_v1_HealthCheckRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__health__v1__HealthCheckRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_health_v1_HealthCheckRequest* grpc_health_v1_HealthCheckRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_health_v1_HealthCheckRequest* ret = grpc_health_v1_HealthCheckRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__health__v1__HealthCheckRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_health_v1_HealthCheckRequest_serialize(const grpc_health_v1_HealthCheckRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__health__v1__HealthCheckRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_health_v1_HealthCheckRequest_serialize_ex(const grpc_health_v1_HealthCheckRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__health__v1__HealthCheckRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_health_v1_HealthCheckRequest_clear_service(grpc_health_v1_HealthCheckRequest* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView grpc_health_v1_HealthCheckRequest_service(const grpc_health_v1_HealthCheckRequest* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_health_v1_HealthCheckRequest_set_service(grpc_health_v1_HealthCheckRequest *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE grpc_health_v1_HealthCheckResponse* grpc_health_v1_HealthCheckResponse_new(upb_Arena* arena) {
  return (grpc_health_v1_HealthCheckResponse*)_upb_Message_New(&grpc__health__v1__HealthCheckResponse_msg_init, arena);
}
UPB_INLINE grpc_health_v1_HealthCheckResponse* grpc_health_v1_HealthCheckResponse_parse(const char* buf, size_t size, upb_Arena* arena) {
  grpc_health_v1_HealthCheckResponse* ret = grpc_health_v1_HealthCheckResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__health__v1__HealthCheckResponse_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE grpc_health_v1_HealthCheckResponse* grpc_health_v1_HealthCheckResponse_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  grpc_health_v1_HealthCheckResponse* ret = grpc_health_v1_HealthCheckResponse_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &grpc__health__v1__HealthCheckResponse_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* grpc_health_v1_HealthCheckResponse_serialize(const grpc_health_v1_HealthCheckResponse* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__health__v1__HealthCheckResponse_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* grpc_health_v1_HealthCheckResponse_serialize_ex(const grpc_health_v1_HealthCheckResponse* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &grpc__health__v1__HealthCheckResponse_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void grpc_health_v1_HealthCheckResponse_clear_status(grpc_health_v1_HealthCheckResponse* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t grpc_health_v1_HealthCheckResponse_status(const grpc_health_v1_HealthCheckResponse* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void grpc_health_v1_HealthCheckResponse_set_status(grpc_health_v1_HealthCheckResponse *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
