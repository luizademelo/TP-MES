
#ifndef ENVOY_CONFIG_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/data/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_accesslog_v3_AccessLog { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_AccessLog;
typedef struct envoy_config_accesslog_v3_AccessLogFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_AccessLogFilter;
typedef struct envoy_config_accesslog_v3_ComparisonFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_ComparisonFilter;
typedef struct envoy_config_accesslog_v3_StatusCodeFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_StatusCodeFilter;
typedef struct envoy_config_accesslog_v3_DurationFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_DurationFilter;
typedef struct envoy_config_accesslog_v3_NotHealthCheckFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_NotHealthCheckFilter;
typedef struct envoy_config_accesslog_v3_TraceableFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_TraceableFilter;
typedef struct envoy_config_accesslog_v3_RuntimeFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_RuntimeFilter;
typedef struct envoy_config_accesslog_v3_AndFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_AndFilter;
typedef struct envoy_config_accesslog_v3_OrFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_OrFilter;
typedef struct envoy_config_accesslog_v3_HeaderFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_HeaderFilter;
typedef struct envoy_config_accesslog_v3_ResponseFlagFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_ResponseFlagFilter;
typedef struct envoy_config_accesslog_v3_GrpcStatusFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_GrpcStatusFilter;
typedef struct envoy_config_accesslog_v3_MetadataFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_MetadataFilter;
typedef struct envoy_config_accesslog_v3_LogTypeFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_LogTypeFilter;
typedef struct envoy_config_accesslog_v3_ExtensionFilter { upb_Message UPB_PRIVATE(base); } envoy_config_accesslog_v3_ExtensionFilter;
struct envoy_config_core_v3_RuntimeUInt32;
struct envoy_config_route_v3_HeaderMatcher;
struct envoy_type_matcher_v3_MetadataMatcher;
struct envoy_type_v3_FractionalPercent;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;

typedef enum {
  envoy_config_accesslog_v3_ComparisonFilter_EQ = 0,
  envoy_config_accesslog_v3_ComparisonFilter_GE = 1,
  envoy_config_accesslog_v3_ComparisonFilter_LE = 2
} envoy_config_accesslog_v3_ComparisonFilter_Op;

typedef enum {
  envoy_config_accesslog_v3_GrpcStatusFilter_OK = 0,
  envoy_config_accesslog_v3_GrpcStatusFilter_CANCELED = 1,
  envoy_config_accesslog_v3_GrpcStatusFilter_UNKNOWN = 2,
  envoy_config_accesslog_v3_GrpcStatusFilter_INVALID_ARGUMENT = 3,
  envoy_config_accesslog_v3_GrpcStatusFilter_DEADLINE_EXCEEDED = 4,
  envoy_config_accesslog_v3_GrpcStatusFilter_NOT_FOUND = 5,
  envoy_config_accesslog_v3_GrpcStatusFilter_ALREADY_EXISTS = 6,
  envoy_config_accesslog_v3_GrpcStatusFilter_PERMISSION_DENIED = 7,
  envoy_config_accesslog_v3_GrpcStatusFilter_RESOURCE_EXHAUSTED = 8,
  envoy_config_accesslog_v3_GrpcStatusFilter_FAILED_PRECONDITION = 9,
  envoy_config_accesslog_v3_GrpcStatusFilter_ABORTED = 10,
  envoy_config_accesslog_v3_GrpcStatusFilter_OUT_OF_RANGE = 11,
  envoy_config_accesslog_v3_GrpcStatusFilter_UNIMPLEMENTED = 12,
  envoy_config_accesslog_v3_GrpcStatusFilter_INTERNAL = 13,
  envoy_config_accesslog_v3_GrpcStatusFilter_UNAVAILABLE = 14,
  envoy_config_accesslog_v3_GrpcStatusFilter_DATA_LOSS = 15,
  envoy_config_accesslog_v3_GrpcStatusFilter_UNAUTHENTICATED = 16
} envoy_config_accesslog_v3_GrpcStatusFilter_Status;

UPB_INLINE envoy_config_accesslog_v3_AccessLog* envoy_config_accesslog_v3_AccessLog_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_AccessLog*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLog_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_AccessLog* envoy_config_accesslog_v3_AccessLog_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_AccessLog* ret = envoy_config_accesslog_v3_AccessLog_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__AccessLog_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_AccessLog* envoy_config_accesslog_v3_AccessLog_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_AccessLog* ret = envoy_config_accesslog_v3_AccessLog_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__AccessLog_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_AccessLog_serialize(const envoy_config_accesslog_v3_AccessLog* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AccessLog_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_AccessLog_serialize_ex(const envoy_config_accesslog_v3_AccessLog* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AccessLog_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_accesslog_v3_AccessLog_config_type_typed_config = 4,
  envoy_config_accesslog_v3_AccessLog_config_type_NOT_SET = 0
} envoy_config_accesslog_v3_AccessLog_config_type_oneofcases;
UPB_INLINE envoy_config_accesslog_v3_AccessLog_config_type_oneofcases envoy_config_accesslog_v3_AccessLog_config_type_case(const envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_accesslog_v3_AccessLog_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLog_clear_config_type(envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AccessLog_msg_init, &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLog_clear_name(envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_accesslog_v3_AccessLog_name(const envoy_config_accesslog_v3_AccessLog* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLog_clear_filter(envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_AccessLog_filter(const envoy_config_accesslog_v3_AccessLog* msg) {
  const envoy_config_accesslog_v3_AccessLogFilter* default_val = NULL;
  const envoy_config_accesslog_v3_AccessLogFilter* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLog_has_filter(const envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLog_clear_typed_config(envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_accesslog_v3_AccessLog_typed_config(const envoy_config_accesslog_v3_AccessLog* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLog_has_typed_config(const envoy_config_accesslog_v3_AccessLog* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_AccessLog_set_name(envoy_config_accesslog_v3_AccessLog *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLog_set_filter(envoy_config_accesslog_v3_AccessLog *msg, envoy_config_accesslog_v3_AccessLogFilter* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_AccessLog_mutable_filter(envoy_config_accesslog_v3_AccessLog* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_AccessLogFilter* sub = (struct envoy_config_accesslog_v3_AccessLogFilter*)envoy_config_accesslog_v3_AccessLog_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_AccessLogFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLogFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLog_set_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLog_set_typed_config(envoy_config_accesslog_v3_AccessLog *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_accesslog_v3_AccessLog_mutable_typed_config(envoy_config_accesslog_v3_AccessLog* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_accesslog_v3_AccessLog_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLog_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_AccessLogFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_AccessLogFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLogFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_AccessLogFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_AccessLogFilter* ret = envoy_config_accesslog_v3_AccessLogFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__AccessLogFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_AccessLogFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_AccessLogFilter* ret = envoy_config_accesslog_v3_AccessLogFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__AccessLogFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_AccessLogFilter_serialize(const envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AccessLogFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_AccessLogFilter_serialize_ex(const envoy_config_accesslog_v3_AccessLogFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AccessLogFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_status_code_filter = 1,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_duration_filter = 2,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_not_health_check_filter = 3,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_traceable_filter = 4,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_runtime_filter = 5,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_and_filter = 6,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_or_filter = 7,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_header_filter = 8,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_response_flag_filter = 9,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_grpc_status_filter = 10,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_extension_filter = 11,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_metadata_filter = 12,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_log_type_filter = 13,
  envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_NOT_SET = 0
} envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_oneofcases;
UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_oneofcases envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_case(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_accesslog_v3_AccessLogFilter_filter_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_filter_specifier(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AccessLogFilter_msg_init, &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_status_code_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_StatusCodeFilter* envoy_config_accesslog_v3_AccessLogFilter_status_code_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_StatusCodeFilter* default_val = NULL;
  const envoy_config_accesslog_v3_StatusCodeFilter* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__StatusCodeFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_status_code_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_duration_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_DurationFilter* envoy_config_accesslog_v3_AccessLogFilter_duration_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_DurationFilter* default_val = NULL;
  const envoy_config_accesslog_v3_DurationFilter* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__DurationFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_duration_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_not_health_check_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_NotHealthCheckFilter* envoy_config_accesslog_v3_AccessLogFilter_not_health_check_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_NotHealthCheckFilter* default_val = NULL;
  const envoy_config_accesslog_v3_NotHealthCheckFilter* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_not_health_check_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_traceable_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_TraceableFilter* envoy_config_accesslog_v3_AccessLogFilter_traceable_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_TraceableFilter* default_val = NULL;
  const envoy_config_accesslog_v3_TraceableFilter* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__TraceableFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_traceable_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_runtime_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_RuntimeFilter* envoy_config_accesslog_v3_AccessLogFilter_runtime_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_RuntimeFilter* default_val = NULL;
  const envoy_config_accesslog_v3_RuntimeFilter* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__RuntimeFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_runtime_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_and_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_AndFilter* envoy_config_accesslog_v3_AccessLogFilter_and_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_AndFilter* default_val = NULL;
  const envoy_config_accesslog_v3_AndFilter* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AndFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_and_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_or_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_OrFilter* envoy_config_accesslog_v3_AccessLogFilter_or_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_OrFilter* default_val = NULL;
  const envoy_config_accesslog_v3_OrFilter* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__OrFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_or_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_header_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_HeaderFilter* envoy_config_accesslog_v3_AccessLogFilter_header_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_HeaderFilter* default_val = NULL;
  const envoy_config_accesslog_v3_HeaderFilter* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__HeaderFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_header_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_response_flag_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_ResponseFlagFilter* envoy_config_accesslog_v3_AccessLogFilter_response_flag_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_ResponseFlagFilter* default_val = NULL;
  const envoy_config_accesslog_v3_ResponseFlagFilter* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ResponseFlagFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_response_flag_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_grpc_status_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_GrpcStatusFilter* envoy_config_accesslog_v3_AccessLogFilter_grpc_status_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_GrpcStatusFilter* default_val = NULL;
  const envoy_config_accesslog_v3_GrpcStatusFilter* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__GrpcStatusFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_grpc_status_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_extension_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_ExtensionFilter* envoy_config_accesslog_v3_AccessLogFilter_extension_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_ExtensionFilter* default_val = NULL;
  const envoy_config_accesslog_v3_ExtensionFilter* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ExtensionFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_extension_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_metadata_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_MetadataFilter* envoy_config_accesslog_v3_AccessLogFilter_metadata_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_MetadataFilter* default_val = NULL;
  const envoy_config_accesslog_v3_MetadataFilter* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__MetadataFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_metadata_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_clear_log_type_filter(envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_LogTypeFilter* envoy_config_accesslog_v3_AccessLogFilter_log_type_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const envoy_config_accesslog_v3_LogTypeFilter* default_val = NULL;
  const envoy_config_accesslog_v3_LogTypeFilter* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__LogTypeFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_AccessLogFilter_has_log_type_filter(const envoy_config_accesslog_v3_AccessLogFilter* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_status_code_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_StatusCodeFilter* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__StatusCodeFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_StatusCodeFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_status_code_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_StatusCodeFilter* sub = (struct envoy_config_accesslog_v3_StatusCodeFilter*)envoy_config_accesslog_v3_AccessLogFilter_status_code_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_StatusCodeFilter*)_upb_Message_New(&envoy__config__accesslog__v3__StatusCodeFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_status_code_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_duration_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_DurationFilter* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__DurationFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_DurationFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_duration_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_DurationFilter* sub = (struct envoy_config_accesslog_v3_DurationFilter*)envoy_config_accesslog_v3_AccessLogFilter_duration_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_DurationFilter*)_upb_Message_New(&envoy__config__accesslog__v3__DurationFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_duration_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_not_health_check_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_NotHealthCheckFilter* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_NotHealthCheckFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_not_health_check_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_NotHealthCheckFilter* sub = (struct envoy_config_accesslog_v3_NotHealthCheckFilter*)envoy_config_accesslog_v3_AccessLogFilter_not_health_check_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_NotHealthCheckFilter*)_upb_Message_New(&envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_not_health_check_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_traceable_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_TraceableFilter* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__TraceableFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_TraceableFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_traceable_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_TraceableFilter* sub = (struct envoy_config_accesslog_v3_TraceableFilter*)envoy_config_accesslog_v3_AccessLogFilter_traceable_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_TraceableFilter*)_upb_Message_New(&envoy__config__accesslog__v3__TraceableFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_traceable_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_runtime_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_RuntimeFilter* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__RuntimeFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_RuntimeFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_runtime_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_RuntimeFilter* sub = (struct envoy_config_accesslog_v3_RuntimeFilter*)envoy_config_accesslog_v3_AccessLogFilter_runtime_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_RuntimeFilter*)_upb_Message_New(&envoy__config__accesslog__v3__RuntimeFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_runtime_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_and_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_AndFilter* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AndFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_AndFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_and_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_AndFilter* sub = (struct envoy_config_accesslog_v3_AndFilter*)envoy_config_accesslog_v3_AccessLogFilter_and_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_AndFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AndFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_and_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_or_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_OrFilter* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__OrFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_OrFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_or_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_OrFilter* sub = (struct envoy_config_accesslog_v3_OrFilter*)envoy_config_accesslog_v3_AccessLogFilter_or_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_OrFilter*)_upb_Message_New(&envoy__config__accesslog__v3__OrFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_or_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_header_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_HeaderFilter* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__HeaderFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_HeaderFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_header_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_HeaderFilter* sub = (struct envoy_config_accesslog_v3_HeaderFilter*)envoy_config_accesslog_v3_AccessLogFilter_header_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_HeaderFilter*)_upb_Message_New(&envoy__config__accesslog__v3__HeaderFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_header_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_response_flag_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_ResponseFlagFilter* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ResponseFlagFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_ResponseFlagFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_response_flag_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_ResponseFlagFilter* sub = (struct envoy_config_accesslog_v3_ResponseFlagFilter*)envoy_config_accesslog_v3_AccessLogFilter_response_flag_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_ResponseFlagFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ResponseFlagFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_response_flag_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_grpc_status_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_GrpcStatusFilter* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__GrpcStatusFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_GrpcStatusFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_grpc_status_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_GrpcStatusFilter* sub = (struct envoy_config_accesslog_v3_GrpcStatusFilter*)envoy_config_accesslog_v3_AccessLogFilter_grpc_status_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_GrpcStatusFilter*)_upb_Message_New(&envoy__config__accesslog__v3__GrpcStatusFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_grpc_status_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_extension_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_ExtensionFilter* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ExtensionFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_ExtensionFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_extension_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_ExtensionFilter* sub = (struct envoy_config_accesslog_v3_ExtensionFilter*)envoy_config_accesslog_v3_AccessLogFilter_extension_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_ExtensionFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ExtensionFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_extension_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_metadata_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_MetadataFilter* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__MetadataFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_MetadataFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_metadata_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_MetadataFilter* sub = (struct envoy_config_accesslog_v3_MetadataFilter*)envoy_config_accesslog_v3_AccessLogFilter_metadata_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_MetadataFilter*)_upb_Message_New(&envoy__config__accesslog__v3__MetadataFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_metadata_filter(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_AccessLogFilter_set_log_type_filter(envoy_config_accesslog_v3_AccessLogFilter *msg, envoy_config_accesslog_v3_LogTypeFilter* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(12, 16), -9, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__LogTypeFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_LogTypeFilter* envoy_config_accesslog_v3_AccessLogFilter_mutable_log_type_filter(envoy_config_accesslog_v3_AccessLogFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_LogTypeFilter* sub = (struct envoy_config_accesslog_v3_LogTypeFilter*)envoy_config_accesslog_v3_AccessLogFilter_log_type_filter(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_LogTypeFilter*)_upb_Message_New(&envoy__config__accesslog__v3__LogTypeFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_AccessLogFilter_set_log_type_filter(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_ComparisonFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_ComparisonFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ComparisonFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_ComparisonFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_ComparisonFilter* ret = envoy_config_accesslog_v3_ComparisonFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__ComparisonFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_ComparisonFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_ComparisonFilter* ret = envoy_config_accesslog_v3_ComparisonFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__ComparisonFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_ComparisonFilter_serialize(const envoy_config_accesslog_v3_ComparisonFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ComparisonFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_ComparisonFilter_serialize_ex(const envoy_config_accesslog_v3_ComparisonFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ComparisonFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_ComparisonFilter_clear_op(envoy_config_accesslog_v3_ComparisonFilter* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_accesslog_v3_ComparisonFilter_op(const envoy_config_accesslog_v3_ComparisonFilter* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_accesslog_v3_ComparisonFilter_clear_value(envoy_config_accesslog_v3_ComparisonFilter* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_RuntimeUInt32* envoy_config_accesslog_v3_ComparisonFilter_value(const envoy_config_accesslog_v3_ComparisonFilter* msg) {
  const struct envoy_config_core_v3_RuntimeUInt32* default_val = NULL;
  const struct envoy_config_core_v3_RuntimeUInt32* ret;
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeUInt32_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_ComparisonFilter_has_value(const envoy_config_accesslog_v3_ComparisonFilter* msg) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_ComparisonFilter_set_op(envoy_config_accesslog_v3_ComparisonFilter *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_accesslog_v3_ComparisonFilter_set_value(envoy_config_accesslog_v3_ComparisonFilter *msg, struct envoy_config_core_v3_RuntimeUInt32* value) {
  const upb_MiniTableField field = {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RuntimeUInt32_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RuntimeUInt32* envoy_config_accesslog_v3_ComparisonFilter_mutable_value(envoy_config_accesslog_v3_ComparisonFilter* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RuntimeUInt32* sub = (struct envoy_config_core_v3_RuntimeUInt32*)envoy_config_accesslog_v3_ComparisonFilter_value(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RuntimeUInt32*)_upb_Message_New(&envoy__config__core__v3__RuntimeUInt32_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_ComparisonFilter_set_value(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_StatusCodeFilter* envoy_config_accesslog_v3_StatusCodeFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_StatusCodeFilter*)_upb_Message_New(&envoy__config__accesslog__v3__StatusCodeFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_StatusCodeFilter* envoy_config_accesslog_v3_StatusCodeFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_StatusCodeFilter* ret = envoy_config_accesslog_v3_StatusCodeFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__StatusCodeFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_StatusCodeFilter* envoy_config_accesslog_v3_StatusCodeFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_StatusCodeFilter* ret = envoy_config_accesslog_v3_StatusCodeFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__StatusCodeFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_StatusCodeFilter_serialize(const envoy_config_accesslog_v3_StatusCodeFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__StatusCodeFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_StatusCodeFilter_serialize_ex(const envoy_config_accesslog_v3_StatusCodeFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__StatusCodeFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_StatusCodeFilter_clear_comparison(envoy_config_accesslog_v3_StatusCodeFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_StatusCodeFilter_comparison(const envoy_config_accesslog_v3_StatusCodeFilter* msg) {
  const envoy_config_accesslog_v3_ComparisonFilter* default_val = NULL;
  const envoy_config_accesslog_v3_ComparisonFilter* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ComparisonFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_StatusCodeFilter_has_comparison(const envoy_config_accesslog_v3_StatusCodeFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_StatusCodeFilter_set_comparison(envoy_config_accesslog_v3_StatusCodeFilter *msg, envoy_config_accesslog_v3_ComparisonFilter* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ComparisonFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_StatusCodeFilter_mutable_comparison(envoy_config_accesslog_v3_StatusCodeFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_ComparisonFilter* sub = (struct envoy_config_accesslog_v3_ComparisonFilter*)envoy_config_accesslog_v3_StatusCodeFilter_comparison(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_ComparisonFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ComparisonFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_StatusCodeFilter_set_comparison(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_DurationFilter* envoy_config_accesslog_v3_DurationFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_DurationFilter*)_upb_Message_New(&envoy__config__accesslog__v3__DurationFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_DurationFilter* envoy_config_accesslog_v3_DurationFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_DurationFilter* ret = envoy_config_accesslog_v3_DurationFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__DurationFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_DurationFilter* envoy_config_accesslog_v3_DurationFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_DurationFilter* ret = envoy_config_accesslog_v3_DurationFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__DurationFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_DurationFilter_serialize(const envoy_config_accesslog_v3_DurationFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__DurationFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_DurationFilter_serialize_ex(const envoy_config_accesslog_v3_DurationFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__DurationFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_DurationFilter_clear_comparison(envoy_config_accesslog_v3_DurationFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_DurationFilter_comparison(const envoy_config_accesslog_v3_DurationFilter* msg) {
  const envoy_config_accesslog_v3_ComparisonFilter* default_val = NULL;
  const envoy_config_accesslog_v3_ComparisonFilter* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ComparisonFilter_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_DurationFilter_has_comparison(const envoy_config_accesslog_v3_DurationFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_DurationFilter_set_comparison(envoy_config_accesslog_v3_DurationFilter *msg, envoy_config_accesslog_v3_ComparisonFilter* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__ComparisonFilter_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_ComparisonFilter* envoy_config_accesslog_v3_DurationFilter_mutable_comparison(envoy_config_accesslog_v3_DurationFilter* msg, upb_Arena* arena) {
  struct envoy_config_accesslog_v3_ComparisonFilter* sub = (struct envoy_config_accesslog_v3_ComparisonFilter*)envoy_config_accesslog_v3_DurationFilter_comparison(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_accesslog_v3_ComparisonFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ComparisonFilter_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_DurationFilter_set_comparison(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_NotHealthCheckFilter* envoy_config_accesslog_v3_NotHealthCheckFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_NotHealthCheckFilter*)_upb_Message_New(&envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_NotHealthCheckFilter* envoy_config_accesslog_v3_NotHealthCheckFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_NotHealthCheckFilter* ret = envoy_config_accesslog_v3_NotHealthCheckFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_NotHealthCheckFilter* envoy_config_accesslog_v3_NotHealthCheckFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_NotHealthCheckFilter* ret = envoy_config_accesslog_v3_NotHealthCheckFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_NotHealthCheckFilter_serialize(const envoy_config_accesslog_v3_NotHealthCheckFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_NotHealthCheckFilter_serialize_ex(const envoy_config_accesslog_v3_NotHealthCheckFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_accesslog_v3_TraceableFilter* envoy_config_accesslog_v3_TraceableFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_TraceableFilter*)_upb_Message_New(&envoy__config__accesslog__v3__TraceableFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_TraceableFilter* envoy_config_accesslog_v3_TraceableFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_TraceableFilter* ret = envoy_config_accesslog_v3_TraceableFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__TraceableFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_TraceableFilter* envoy_config_accesslog_v3_TraceableFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_TraceableFilter* ret = envoy_config_accesslog_v3_TraceableFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__TraceableFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_TraceableFilter_serialize(const envoy_config_accesslog_v3_TraceableFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__TraceableFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_TraceableFilter_serialize_ex(const envoy_config_accesslog_v3_TraceableFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__TraceableFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_accesslog_v3_RuntimeFilter* envoy_config_accesslog_v3_RuntimeFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_RuntimeFilter*)_upb_Message_New(&envoy__config__accesslog__v3__RuntimeFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_RuntimeFilter* envoy_config_accesslog_v3_RuntimeFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_RuntimeFilter* ret = envoy_config_accesslog_v3_RuntimeFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__RuntimeFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_RuntimeFilter* envoy_config_accesslog_v3_RuntimeFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_RuntimeFilter* ret = envoy_config_accesslog_v3_RuntimeFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__RuntimeFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_RuntimeFilter_serialize(const envoy_config_accesslog_v3_RuntimeFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__RuntimeFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_RuntimeFilter_serialize_ex(const envoy_config_accesslog_v3_RuntimeFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__RuntimeFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_RuntimeFilter_clear_runtime_key(envoy_config_accesslog_v3_RuntimeFilter* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_accesslog_v3_RuntimeFilter_runtime_key(const envoy_config_accesslog_v3_RuntimeFilter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_accesslog_v3_RuntimeFilter_clear_percent_sampled(envoy_config_accesslog_v3_RuntimeFilter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_accesslog_v3_RuntimeFilter_percent_sampled(const envoy_config_accesslog_v3_RuntimeFilter* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_RuntimeFilter_has_percent_sampled(const envoy_config_accesslog_v3_RuntimeFilter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_RuntimeFilter_clear_use_independent_randomness(envoy_config_accesslog_v3_RuntimeFilter* msg) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_accesslog_v3_RuntimeFilter_use_independent_randomness(const envoy_config_accesslog_v3_RuntimeFilter* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_accesslog_v3_RuntimeFilter_set_runtime_key(envoy_config_accesslog_v3_RuntimeFilter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_accesslog_v3_RuntimeFilter_set_percent_sampled(envoy_config_accesslog_v3_RuntimeFilter *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_accesslog_v3_RuntimeFilter_mutable_percent_sampled(envoy_config_accesslog_v3_RuntimeFilter* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_accesslog_v3_RuntimeFilter_percent_sampled(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_RuntimeFilter_set_percent_sampled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_RuntimeFilter_set_use_independent_randomness(envoy_config_accesslog_v3_RuntimeFilter *msg, bool value) {
  const upb_MiniTableField field = {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_accesslog_v3_AndFilter* envoy_config_accesslog_v3_AndFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_AndFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AndFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_AndFilter* envoy_config_accesslog_v3_AndFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_AndFilter* ret = envoy_config_accesslog_v3_AndFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__AndFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_AndFilter* envoy_config_accesslog_v3_AndFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_AndFilter* ret = envoy_config_accesslog_v3_AndFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__AndFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_AndFilter_serialize(const envoy_config_accesslog_v3_AndFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AndFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_AndFilter_serialize_ex(const envoy_config_accesslog_v3_AndFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__AndFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_AndFilter_clear_filters(envoy_config_accesslog_v3_AndFilter* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_AccessLogFilter* const* envoy_config_accesslog_v3_AndFilter_filters(const envoy_config_accesslog_v3_AndFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_accesslog_v3_AccessLogFilter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_accesslog_v3_AndFilter_filters_upb_array(const envoy_config_accesslog_v3_AndFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_accesslog_v3_AndFilter_filters_mutable_upb_array(envoy_config_accesslog_v3_AndFilter* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter** envoy_config_accesslog_v3_AndFilter_mutable_filters(envoy_config_accesslog_v3_AndFilter* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_accesslog_v3_AccessLogFilter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter** envoy_config_accesslog_v3_AndFilter_resize_filters(envoy_config_accesslog_v3_AndFilter* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_accesslog_v3_AccessLogFilter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_AndFilter_add_filters(envoy_config_accesslog_v3_AndFilter* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_accesslog_v3_AccessLogFilter* sub = (struct envoy_config_accesslog_v3_AccessLogFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLogFilter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_OrFilter* envoy_config_accesslog_v3_OrFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_OrFilter*)_upb_Message_New(&envoy__config__accesslog__v3__OrFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_OrFilter* envoy_config_accesslog_v3_OrFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_OrFilter* ret = envoy_config_accesslog_v3_OrFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__OrFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_OrFilter* envoy_config_accesslog_v3_OrFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_OrFilter* ret = envoy_config_accesslog_v3_OrFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__OrFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_OrFilter_serialize(const envoy_config_accesslog_v3_OrFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__OrFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_OrFilter_serialize_ex(const envoy_config_accesslog_v3_OrFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__OrFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_OrFilter_clear_filters(envoy_config_accesslog_v3_OrFilter* msg) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_accesslog_v3_AccessLogFilter* const* envoy_config_accesslog_v3_OrFilter_filters(const envoy_config_accesslog_v3_OrFilter* msg, size_t* size) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_accesslog_v3_AccessLogFilter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_accesslog_v3_OrFilter_filters_upb_array(const envoy_config_accesslog_v3_OrFilter* msg, size_t* size) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_accesslog_v3_OrFilter_filters_mutable_upb_array(envoy_config_accesslog_v3_OrFilter* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter** envoy_config_accesslog_v3_OrFilter_mutable_filters(envoy_config_accesslog_v3_OrFilter* msg, size_t* size) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_accesslog_v3_AccessLogFilter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_accesslog_v3_AccessLogFilter** envoy_config_accesslog_v3_OrFilter_resize_filters(envoy_config_accesslog_v3_OrFilter* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_accesslog_v3_AccessLogFilter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLogFilter* envoy_config_accesslog_v3_OrFilter_add_filters(envoy_config_accesslog_v3_OrFilter* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLogFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_accesslog_v3_AccessLogFilter* sub = (struct envoy_config_accesslog_v3_AccessLogFilter*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLogFilter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_HeaderFilter* envoy_config_accesslog_v3_HeaderFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_HeaderFilter*)_upb_Message_New(&envoy__config__accesslog__v3__HeaderFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_HeaderFilter* envoy_config_accesslog_v3_HeaderFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_HeaderFilter* ret = envoy_config_accesslog_v3_HeaderFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__HeaderFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_HeaderFilter* envoy_config_accesslog_v3_HeaderFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_HeaderFilter* ret = envoy_config_accesslog_v3_HeaderFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__HeaderFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_HeaderFilter_serialize(const envoy_config_accesslog_v3_HeaderFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__HeaderFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_HeaderFilter_serialize_ex(const envoy_config_accesslog_v3_HeaderFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__HeaderFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_HeaderFilter_clear_header(envoy_config_accesslog_v3_HeaderFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_HeaderMatcher* envoy_config_accesslog_v3_HeaderFilter_header(const envoy_config_accesslog_v3_HeaderFilter* msg) {
  const struct envoy_config_route_v3_HeaderMatcher* default_val = NULL;
  const struct envoy_config_route_v3_HeaderMatcher* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_HeaderFilter_has_header(const envoy_config_accesslog_v3_HeaderFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_HeaderFilter_set_header(envoy_config_accesslog_v3_HeaderFilter *msg, struct envoy_config_route_v3_HeaderMatcher* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_config_accesslog_v3_HeaderFilter_mutable_header(envoy_config_accesslog_v3_HeaderFilter* msg, upb_Arena* arena) {
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)envoy_config_accesslog_v3_HeaderFilter_header(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_HeaderFilter_set_header(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_ResponseFlagFilter* envoy_config_accesslog_v3_ResponseFlagFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_ResponseFlagFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ResponseFlagFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_ResponseFlagFilter* envoy_config_accesslog_v3_ResponseFlagFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_ResponseFlagFilter* ret = envoy_config_accesslog_v3_ResponseFlagFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_ResponseFlagFilter* envoy_config_accesslog_v3_ResponseFlagFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_ResponseFlagFilter* ret = envoy_config_accesslog_v3_ResponseFlagFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_ResponseFlagFilter_serialize(const envoy_config_accesslog_v3_ResponseFlagFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_ResponseFlagFilter_serialize_ex(const envoy_config_accesslog_v3_ResponseFlagFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_ResponseFlagFilter_clear_flags(envoy_config_accesslog_v3_ResponseFlagFilter* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_accesslog_v3_ResponseFlagFilter_flags(const envoy_config_accesslog_v3_ResponseFlagFilter* msg, size_t* size) {
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
UPB_INLINE const upb_Array* _envoy_config_accesslog_v3_ResponseFlagFilter_flags_upb_array(const envoy_config_accesslog_v3_ResponseFlagFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_accesslog_v3_ResponseFlagFilter_flags_mutable_upb_array(envoy_config_accesslog_v3_ResponseFlagFilter* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE upb_StringView* envoy_config_accesslog_v3_ResponseFlagFilter_mutable_flags(envoy_config_accesslog_v3_ResponseFlagFilter* msg, size_t* size) {
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
UPB_INLINE upb_StringView* envoy_config_accesslog_v3_ResponseFlagFilter_resize_flags(envoy_config_accesslog_v3_ResponseFlagFilter* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_accesslog_v3_ResponseFlagFilter_add_flags(envoy_config_accesslog_v3_ResponseFlagFilter* msg, upb_StringView val, upb_Arena* arena) {
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

UPB_INLINE envoy_config_accesslog_v3_GrpcStatusFilter* envoy_config_accesslog_v3_GrpcStatusFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_GrpcStatusFilter*)_upb_Message_New(&envoy__config__accesslog__v3__GrpcStatusFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_GrpcStatusFilter* envoy_config_accesslog_v3_GrpcStatusFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_GrpcStatusFilter* ret = envoy_config_accesslog_v3_GrpcStatusFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_GrpcStatusFilter* envoy_config_accesslog_v3_GrpcStatusFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_GrpcStatusFilter* ret = envoy_config_accesslog_v3_GrpcStatusFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_GrpcStatusFilter_serialize(const envoy_config_accesslog_v3_GrpcStatusFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_GrpcStatusFilter_serialize_ex(const envoy_config_accesslog_v3_GrpcStatusFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_GrpcStatusFilter_clear_statuses(envoy_config_accesslog_v3_GrpcStatusFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* envoy_config_accesslog_v3_GrpcStatusFilter_statuses(const envoy_config_accesslog_v3_GrpcStatusFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_accesslog_v3_GrpcStatusFilter_statuses_upb_array(const envoy_config_accesslog_v3_GrpcStatusFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_accesslog_v3_GrpcStatusFilter_statuses_mutable_upb_array(envoy_config_accesslog_v3_GrpcStatusFilter* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_accesslog_v3_GrpcStatusFilter_clear_exclude(envoy_config_accesslog_v3_GrpcStatusFilter* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_accesslog_v3_GrpcStatusFilter_exclude(const envoy_config_accesslog_v3_GrpcStatusFilter* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE int32_t* envoy_config_accesslog_v3_GrpcStatusFilter_mutable_statuses(envoy_config_accesslog_v3_GrpcStatusFilter* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* envoy_config_accesslog_v3_GrpcStatusFilter_resize_statuses(envoy_config_accesslog_v3_GrpcStatusFilter* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_accesslog_v3_GrpcStatusFilter_add_statuses(envoy_config_accesslog_v3_GrpcStatusFilter* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_accesslog_v3_GrpcStatusFilter_set_exclude(envoy_config_accesslog_v3_GrpcStatusFilter *msg, bool value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_accesslog_v3_MetadataFilter* envoy_config_accesslog_v3_MetadataFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_MetadataFilter*)_upb_Message_New(&envoy__config__accesslog__v3__MetadataFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_MetadataFilter* envoy_config_accesslog_v3_MetadataFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_MetadataFilter* ret = envoy_config_accesslog_v3_MetadataFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__MetadataFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_MetadataFilter* envoy_config_accesslog_v3_MetadataFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_MetadataFilter* ret = envoy_config_accesslog_v3_MetadataFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__MetadataFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_MetadataFilter_serialize(const envoy_config_accesslog_v3_MetadataFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__MetadataFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_MetadataFilter_serialize_ex(const envoy_config_accesslog_v3_MetadataFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__MetadataFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_MetadataFilter_clear_matcher(envoy_config_accesslog_v3_MetadataFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_accesslog_v3_MetadataFilter_matcher(const envoy_config_accesslog_v3_MetadataFilter* msg) {
  const struct envoy_type_matcher_v3_MetadataMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_MetadataMatcher* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_MetadataFilter_has_matcher(const envoy_config_accesslog_v3_MetadataFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_MetadataFilter_clear_match_if_key_not_found(envoy_config_accesslog_v3_MetadataFilter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_accesslog_v3_MetadataFilter_match_if_key_not_found(const envoy_config_accesslog_v3_MetadataFilter* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_MetadataFilter_has_match_if_key_not_found(const envoy_config_accesslog_v3_MetadataFilter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_MetadataFilter_set_matcher(envoy_config_accesslog_v3_MetadataFilter *msg, struct envoy_type_matcher_v3_MetadataMatcher* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__MetadataMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_MetadataMatcher* envoy_config_accesslog_v3_MetadataFilter_mutable_matcher(envoy_config_accesslog_v3_MetadataFilter* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_MetadataMatcher* sub = (struct envoy_type_matcher_v3_MetadataMatcher*)envoy_config_accesslog_v3_MetadataFilter_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_MetadataMatcher*)_upb_Message_New(&envoy__type__matcher__v3__MetadataMatcher_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_MetadataFilter_set_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_accesslog_v3_MetadataFilter_set_match_if_key_not_found(envoy_config_accesslog_v3_MetadataFilter *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_accesslog_v3_MetadataFilter_mutable_match_if_key_not_found(envoy_config_accesslog_v3_MetadataFilter* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_accesslog_v3_MetadataFilter_match_if_key_not_found(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_MetadataFilter_set_match_if_key_not_found(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_accesslog_v3_LogTypeFilter* envoy_config_accesslog_v3_LogTypeFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_LogTypeFilter*)_upb_Message_New(&envoy__config__accesslog__v3__LogTypeFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_LogTypeFilter* envoy_config_accesslog_v3_LogTypeFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_LogTypeFilter* ret = envoy_config_accesslog_v3_LogTypeFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__LogTypeFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_LogTypeFilter* envoy_config_accesslog_v3_LogTypeFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_LogTypeFilter* ret = envoy_config_accesslog_v3_LogTypeFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__LogTypeFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_LogTypeFilter_serialize(const envoy_config_accesslog_v3_LogTypeFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__LogTypeFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_LogTypeFilter_serialize_ex(const envoy_config_accesslog_v3_LogTypeFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__LogTypeFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_accesslog_v3_LogTypeFilter_clear_types(envoy_config_accesslog_v3_LogTypeFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t const* envoy_config_accesslog_v3_LogTypeFilter_types(const envoy_config_accesslog_v3_LogTypeFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_accesslog_v3_LogTypeFilter_types_upb_array(const envoy_config_accesslog_v3_LogTypeFilter* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_accesslog_v3_LogTypeFilter_types_mutable_upb_array(envoy_config_accesslog_v3_LogTypeFilter* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_accesslog_v3_LogTypeFilter_clear_exclude(envoy_config_accesslog_v3_LogTypeFilter* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_accesslog_v3_LogTypeFilter_exclude(const envoy_config_accesslog_v3_LogTypeFilter* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE int32_t* envoy_config_accesslog_v3_LogTypeFilter_mutable_types(envoy_config_accesslog_v3_LogTypeFilter* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (int32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE int32_t* envoy_config_accesslog_v3_LogTypeFilter_resize_types(envoy_config_accesslog_v3_LogTypeFilter* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (int32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_accesslog_v3_LogTypeFilter_add_types(envoy_config_accesslog_v3_LogTypeFilter* msg, int32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_accesslog_v3_LogTypeFilter_set_exclude(envoy_config_accesslog_v3_LogTypeFilter *msg, bool value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_accesslog_v3_ExtensionFilter* envoy_config_accesslog_v3_ExtensionFilter_new(upb_Arena* arena) {
  return (envoy_config_accesslog_v3_ExtensionFilter*)_upb_Message_New(&envoy__config__accesslog__v3__ExtensionFilter_msg_init, arena);
}
UPB_INLINE envoy_config_accesslog_v3_ExtensionFilter* envoy_config_accesslog_v3_ExtensionFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_accesslog_v3_ExtensionFilter* ret = envoy_config_accesslog_v3_ExtensionFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__ExtensionFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_accesslog_v3_ExtensionFilter* envoy_config_accesslog_v3_ExtensionFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_accesslog_v3_ExtensionFilter* ret = envoy_config_accesslog_v3_ExtensionFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__accesslog__v3__ExtensionFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_accesslog_v3_ExtensionFilter_serialize(const envoy_config_accesslog_v3_ExtensionFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ExtensionFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_accesslog_v3_ExtensionFilter_serialize_ex(const envoy_config_accesslog_v3_ExtensionFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ExtensionFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_accesslog_v3_ExtensionFilter_config_type_typed_config = 3,
  envoy_config_accesslog_v3_ExtensionFilter_config_type_NOT_SET = 0
} envoy_config_accesslog_v3_ExtensionFilter_config_type_oneofcases;
UPB_INLINE envoy_config_accesslog_v3_ExtensionFilter_config_type_oneofcases envoy_config_accesslog_v3_ExtensionFilter_config_type_case(const envoy_config_accesslog_v3_ExtensionFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_accesslog_v3_ExtensionFilter_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_accesslog_v3_ExtensionFilter_clear_config_type(envoy_config_accesslog_v3_ExtensionFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__accesslog__v3__ExtensionFilter_msg_init, &field);
}
UPB_INLINE void envoy_config_accesslog_v3_ExtensionFilter_clear_name(envoy_config_accesslog_v3_ExtensionFilter* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_accesslog_v3_ExtensionFilter_name(const envoy_config_accesslog_v3_ExtensionFilter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_accesslog_v3_ExtensionFilter_clear_typed_config(envoy_config_accesslog_v3_ExtensionFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_accesslog_v3_ExtensionFilter_typed_config(const envoy_config_accesslog_v3_ExtensionFilter* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_accesslog_v3_ExtensionFilter_has_typed_config(const envoy_config_accesslog_v3_ExtensionFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_accesslog_v3_ExtensionFilter_set_name(envoy_config_accesslog_v3_ExtensionFilter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_accesslog_v3_ExtensionFilter_set_typed_config(envoy_config_accesslog_v3_ExtensionFilter *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_accesslog_v3_ExtensionFilter_mutable_typed_config(envoy_config_accesslog_v3_ExtensionFilter* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_accesslog_v3_ExtensionFilter_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_accesslog_v3_ExtensionFilter_set_typed_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
