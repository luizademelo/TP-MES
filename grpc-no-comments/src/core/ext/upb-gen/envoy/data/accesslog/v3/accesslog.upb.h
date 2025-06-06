
#ifndef ENVOY_DATA_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPB_H_
#define ENVOY_DATA_ACCESSLOG_V3_ACCESSLOG_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/data/accesslog/v3/accesslog.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_data_accesslog_v3_TCPAccessLogEntry { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_TCPAccessLogEntry;
typedef struct envoy_data_accesslog_v3_HTTPAccessLogEntry { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_HTTPAccessLogEntry;
typedef struct envoy_data_accesslog_v3_ConnectionProperties { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_ConnectionProperties;
typedef struct envoy_data_accesslog_v3_AccessLogCommon { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_AccessLogCommon;
typedef struct envoy_data_accesslog_v3_ResponseFlags { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_ResponseFlags;
typedef struct envoy_data_accesslog_v3_ResponseFlags_Unauthorized { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_ResponseFlags_Unauthorized;
typedef struct envoy_data_accesslog_v3_TLSProperties { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_TLSProperties;
typedef struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_TLSProperties_CertificateProperties;
typedef struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName;
typedef struct envoy_data_accesslog_v3_HTTPRequestProperties { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_HTTPRequestProperties;
typedef struct envoy_data_accesslog_v3_HTTPResponseProperties { upb_Message UPB_PRIVATE(base); } envoy_data_accesslog_v3_HTTPResponseProperties;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_Metadata;
struct google_protobuf_Duration;
struct google_protobuf_Timestamp;
struct google_protobuf_UInt32Value;

typedef enum {
  envoy_data_accesslog_v3_NotSet = 0,
  envoy_data_accesslog_v3_TcpUpstreamConnected = 1,
  envoy_data_accesslog_v3_TcpPeriodic = 2,
  envoy_data_accesslog_v3_TcpConnectionEnd = 3,
  envoy_data_accesslog_v3_DownstreamStart = 4,
  envoy_data_accesslog_v3_DownstreamPeriodic = 5,
  envoy_data_accesslog_v3_DownstreamEnd = 6,
  envoy_data_accesslog_v3_UpstreamPoolReady = 7,
  envoy_data_accesslog_v3_UpstreamPeriodic = 8,
  envoy_data_accesslog_v3_UpstreamEnd = 9,
  envoy_data_accesslog_v3_DownstreamTunnelSuccessfullyEstablished = 10,
  envoy_data_accesslog_v3_UdpTunnelUpstreamConnected = 11,
  envoy_data_accesslog_v3_UdpPeriodic = 12,
  envoy_data_accesslog_v3_UdpSessionEnd = 13
} envoy_data_accesslog_v3_AccessLogType;

typedef enum {
  envoy_data_accesslog_v3_HTTPAccessLogEntry_PROTOCOL_UNSPECIFIED = 0,
  envoy_data_accesslog_v3_HTTPAccessLogEntry_HTTP10 = 1,
  envoy_data_accesslog_v3_HTTPAccessLogEntry_HTTP11 = 2,
  envoy_data_accesslog_v3_HTTPAccessLogEntry_HTTP2 = 3,
  envoy_data_accesslog_v3_HTTPAccessLogEntry_HTTP3 = 4
} envoy_data_accesslog_v3_HTTPAccessLogEntry_HTTPVersion;

typedef enum {
  envoy_data_accesslog_v3_ResponseFlags_Unauthorized_REASON_UNSPECIFIED = 0,
  envoy_data_accesslog_v3_ResponseFlags_Unauthorized_EXTERNAL_SERVICE = 1
} envoy_data_accesslog_v3_ResponseFlags_Unauthorized_Reason;

typedef enum {
  envoy_data_accesslog_v3_TLSProperties_VERSION_UNSPECIFIED = 0,
  envoy_data_accesslog_v3_TLSProperties_TLSv1 = 1,
  envoy_data_accesslog_v3_TLSProperties_TLSv1_1 = 2,
  envoy_data_accesslog_v3_TLSProperties_TLSv1_2 = 3,
  envoy_data_accesslog_v3_TLSProperties_TLSv1_3 = 4
} envoy_data_accesslog_v3_TLSProperties_TLSVersion;

UPB_INLINE envoy_data_accesslog_v3_TCPAccessLogEntry* envoy_data_accesslog_v3_TCPAccessLogEntry_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_TCPAccessLogEntry*)_upb_Message_New(&envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_TCPAccessLogEntry* envoy_data_accesslog_v3_TCPAccessLogEntry_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_TCPAccessLogEntry* ret = envoy_data_accesslog_v3_TCPAccessLogEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_TCPAccessLogEntry* envoy_data_accesslog_v3_TCPAccessLogEntry_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_TCPAccessLogEntry* ret = envoy_data_accesslog_v3_TCPAccessLogEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_TCPAccessLogEntry_serialize(const envoy_data_accesslog_v3_TCPAccessLogEntry* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_TCPAccessLogEntry_serialize_ex(const envoy_data_accesslog_v3_TCPAccessLogEntry* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TCPAccessLogEntry_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_TCPAccessLogEntry_clear_common_properties(envoy_data_accesslog_v3_TCPAccessLogEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_TCPAccessLogEntry_common_properties(const envoy_data_accesslog_v3_TCPAccessLogEntry* msg) {
  const envoy_data_accesslog_v3_AccessLogCommon* default_val = NULL;
  const envoy_data_accesslog_v3_AccessLogCommon* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TCPAccessLogEntry_has_common_properties(const envoy_data_accesslog_v3_TCPAccessLogEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TCPAccessLogEntry_clear_connection_properties(envoy_data_accesslog_v3_TCPAccessLogEntry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_ConnectionProperties* envoy_data_accesslog_v3_TCPAccessLogEntry_connection_properties(const envoy_data_accesslog_v3_TCPAccessLogEntry* msg) {
  const envoy_data_accesslog_v3_ConnectionProperties* default_val = NULL;
  const envoy_data_accesslog_v3_ConnectionProperties* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__ConnectionProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TCPAccessLogEntry_has_connection_properties(const envoy_data_accesslog_v3_TCPAccessLogEntry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_data_accesslog_v3_TCPAccessLogEntry_set_common_properties(envoy_data_accesslog_v3_TCPAccessLogEntry *msg, envoy_data_accesslog_v3_AccessLogCommon* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_TCPAccessLogEntry_mutable_common_properties(envoy_data_accesslog_v3_TCPAccessLogEntry* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_AccessLogCommon* sub = (struct envoy_data_accesslog_v3_AccessLogCommon*)envoy_data_accesslog_v3_TCPAccessLogEntry_common_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_AccessLogCommon*)_upb_Message_New(&envoy__data__accesslog__v3__AccessLogCommon_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_TCPAccessLogEntry_set_common_properties(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_TCPAccessLogEntry_set_connection_properties(envoy_data_accesslog_v3_TCPAccessLogEntry *msg, envoy_data_accesslog_v3_ConnectionProperties* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__ConnectionProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_ConnectionProperties* envoy_data_accesslog_v3_TCPAccessLogEntry_mutable_connection_properties(envoy_data_accesslog_v3_TCPAccessLogEntry* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_ConnectionProperties* sub = (struct envoy_data_accesslog_v3_ConnectionProperties*)envoy_data_accesslog_v3_TCPAccessLogEntry_connection_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_ConnectionProperties*)_upb_Message_New(&envoy__data__accesslog__v3__ConnectionProperties_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_TCPAccessLogEntry_set_connection_properties(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_data_accesslog_v3_HTTPAccessLogEntry* envoy_data_accesslog_v3_HTTPAccessLogEntry_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_HTTPAccessLogEntry*)_upb_Message_New(&envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_HTTPAccessLogEntry* envoy_data_accesslog_v3_HTTPAccessLogEntry_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_HTTPAccessLogEntry* ret = envoy_data_accesslog_v3_HTTPAccessLogEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_HTTPAccessLogEntry* envoy_data_accesslog_v3_HTTPAccessLogEntry_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_HTTPAccessLogEntry* ret = envoy_data_accesslog_v3_HTTPAccessLogEntry_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_HTTPAccessLogEntry_serialize(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_HTTPAccessLogEntry_serialize_ex(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__HTTPAccessLogEntry_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_clear_common_properties(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_HTTPAccessLogEntry_common_properties(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const envoy_data_accesslog_v3_AccessLogCommon* default_val = NULL;
  const envoy_data_accesslog_v3_AccessLogCommon* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPAccessLogEntry_has_common_properties(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_clear_protocol_version(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_data_accesslog_v3_HTTPAccessLogEntry_protocol_version(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_clear_request(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_HTTPRequestProperties* envoy_data_accesslog_v3_HTTPAccessLogEntry_request(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const envoy_data_accesslog_v3_HTTPRequestProperties* default_val = NULL;
  const envoy_data_accesslog_v3_HTTPRequestProperties* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPAccessLogEntry_has_request(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_clear_response(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_HTTPResponseProperties* envoy_data_accesslog_v3_HTTPAccessLogEntry_response(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const envoy_data_accesslog_v3_HTTPResponseProperties* default_val = NULL;
  const envoy_data_accesslog_v3_HTTPResponseProperties* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPAccessLogEntry_has_response(const envoy_data_accesslog_v3_HTTPAccessLogEntry* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_set_common_properties(envoy_data_accesslog_v3_HTTPAccessLogEntry *msg, envoy_data_accesslog_v3_AccessLogCommon* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_HTTPAccessLogEntry_mutable_common_properties(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_AccessLogCommon* sub = (struct envoy_data_accesslog_v3_AccessLogCommon*)envoy_data_accesslog_v3_HTTPAccessLogEntry_common_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_AccessLogCommon*)_upb_Message_New(&envoy__data__accesslog__v3__AccessLogCommon_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_HTTPAccessLogEntry_set_common_properties(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_set_protocol_version(envoy_data_accesslog_v3_HTTPAccessLogEntry *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_set_request(envoy_data_accesslog_v3_HTTPAccessLogEntry *msg, envoy_data_accesslog_v3_HTTPRequestProperties* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_HTTPRequestProperties* envoy_data_accesslog_v3_HTTPAccessLogEntry_mutable_request(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_HTTPRequestProperties* sub = (struct envoy_data_accesslog_v3_HTTPRequestProperties*)envoy_data_accesslog_v3_HTTPAccessLogEntry_request(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_HTTPRequestProperties*)_upb_Message_New(&envoy__data__accesslog__v3__HTTPRequestProperties_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_HTTPAccessLogEntry_set_request(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPAccessLogEntry_set_response(envoy_data_accesslog_v3_HTTPAccessLogEntry *msg, envoy_data_accesslog_v3_HTTPResponseProperties* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_HTTPResponseProperties* envoy_data_accesslog_v3_HTTPAccessLogEntry_mutable_response(envoy_data_accesslog_v3_HTTPAccessLogEntry* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_HTTPResponseProperties* sub = (struct envoy_data_accesslog_v3_HTTPResponseProperties*)envoy_data_accesslog_v3_HTTPAccessLogEntry_response(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_HTTPResponseProperties*)_upb_Message_New(&envoy__data__accesslog__v3__HTTPResponseProperties_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_HTTPAccessLogEntry_set_response(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_data_accesslog_v3_ConnectionProperties* envoy_data_accesslog_v3_ConnectionProperties_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_ConnectionProperties*)_upb_Message_New(&envoy__data__accesslog__v3__ConnectionProperties_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_ConnectionProperties* envoy_data_accesslog_v3_ConnectionProperties_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_ConnectionProperties* ret = envoy_data_accesslog_v3_ConnectionProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__ConnectionProperties_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_ConnectionProperties* envoy_data_accesslog_v3_ConnectionProperties_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_ConnectionProperties* ret = envoy_data_accesslog_v3_ConnectionProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__ConnectionProperties_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_ConnectionProperties_serialize(const envoy_data_accesslog_v3_ConnectionProperties* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__ConnectionProperties_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_ConnectionProperties_serialize_ex(const envoy_data_accesslog_v3_ConnectionProperties* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__ConnectionProperties_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_ConnectionProperties_clear_received_bytes(envoy_data_accesslog_v3_ConnectionProperties* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_ConnectionProperties_received_bytes(const envoy_data_accesslog_v3_ConnectionProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ConnectionProperties_clear_sent_bytes(envoy_data_accesslog_v3_ConnectionProperties* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_ConnectionProperties_sent_bytes(const envoy_data_accesslog_v3_ConnectionProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_ConnectionProperties_set_received_bytes(envoy_data_accesslog_v3_ConnectionProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ConnectionProperties_set_sent_bytes(envoy_data_accesslog_v3_ConnectionProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_AccessLogCommon_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_AccessLogCommon*)_upb_Message_New(&envoy__data__accesslog__v3__AccessLogCommon_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_AccessLogCommon_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_AccessLogCommon* ret = envoy_data_accesslog_v3_AccessLogCommon_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__AccessLogCommon_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_AccessLogCommon* envoy_data_accesslog_v3_AccessLogCommon_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_AccessLogCommon* ret = envoy_data_accesslog_v3_AccessLogCommon_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__AccessLogCommon_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_AccessLogCommon_serialize(const envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__AccessLogCommon_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_AccessLogCommon_serialize_ex(const envoy_data_accesslog_v3_AccessLogCommon* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__AccessLogCommon_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_sample_rate(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(144, 120), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_data_accesslog_v3_AccessLogCommon_sample_rate(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, UPB_SIZE(144, 120), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_downstream_remote_address(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 128), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_downstream_remote_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 128), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_downstream_remote_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 128), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_downstream_local_address(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 136), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_downstream_local_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 136), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_downstream_local_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 136), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_tls_properties(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 144), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_TLSProperties* envoy_data_accesslog_v3_AccessLogCommon_tls_properties(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const envoy_data_accesslog_v3_TLSProperties* default_val = NULL;
  const envoy_data_accesslog_v3_TLSProperties* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 144), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_tls_properties(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 144), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_start_time(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 152), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_data_accesslog_v3_AccessLogCommon_start_time(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 152), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_start_time(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 152), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_last_rx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 160), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_last_rx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 160), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_last_rx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 160), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_first_upstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 168), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_first_upstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(32, 168), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_first_upstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 168), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_last_upstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 176), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_last_upstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(36, 176), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_last_upstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 176), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_first_upstream_rx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 184), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_first_upstream_rx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(40, 184), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_first_upstream_rx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 184), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_last_upstream_rx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 192), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_last_upstream_rx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(44, 192), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_last_upstream_rx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 192), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_first_downstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(48, 200), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_first_downstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(48, 200), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_first_downstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(48, 200), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_time_to_last_downstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(52, 208), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_time_to_last_downstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(52, 208), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_time_to_last_downstream_tx_byte(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(52, 208), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_remote_address(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(56, 216), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_upstream_remote_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(56, 216), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_upstream_remote_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(56, 216), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_local_address(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 224), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_upstream_local_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {14, UPB_SIZE(60, 224), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_upstream_local_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 224), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_cluster(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(96, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_AccessLogCommon_upstream_cluster(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {15, UPB_SIZE(96, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_response_flags(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(64, 232), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_ResponseFlags* envoy_data_accesslog_v3_AccessLogCommon_response_flags(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const envoy_data_accesslog_v3_ResponseFlags* default_val = NULL;
  const envoy_data_accesslog_v3_ResponseFlags* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(64, 232), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__ResponseFlags_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_response_flags(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(64, 232), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_metadata(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(68, 240), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_data_accesslog_v3_AccessLogCommon_metadata(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {17, UPB_SIZE(68, 240), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_metadata(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {17, UPB_SIZE(68, 240), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_transport_failure_reason(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(104, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_AccessLogCommon_upstream_transport_failure_reason(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {18, UPB_SIZE(104, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_route_name(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(112, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_AccessLogCommon_route_name(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {19, UPB_SIZE(112, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_downstream_direct_remote_address(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(72, 248), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_downstream_direct_remote_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(72, 248), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_downstream_direct_remote_address(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(72, 248), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_filter_state_objects(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_size(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_get(const envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView key, struct google_protobuf_Any** val) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_next(const envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView* key, const struct google_protobuf_Any** val,
                           size_t* iter) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_upb_map(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_mutable_upb_map(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* a) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Any*), a);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_custom_tags(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_data_accesslog_v3_AccessLogCommon_custom_tags_size(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_custom_tags_get(const envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_custom_tags_next(const envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_data_accesslog_v3_AccessLogCommon_custom_tags_upb_map(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_data_accesslog_v3_AccessLogCommon_custom_tags_mutable_upb_map(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* a) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_duration(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(84, 272), 80, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_duration(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {23, UPB_SIZE(84, 272), 80, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_has_duration(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {23, UPB_SIZE(84, 272), 80, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_request_attempt_count(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(88, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_data_accesslog_v3_AccessLogCommon_upstream_request_attempt_count(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {24, UPB_SIZE(88, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_connection_termination_details(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(120, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_AccessLogCommon_connection_termination_details(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {25, UPB_SIZE(120, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_stream_id(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(128, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_AccessLogCommon_stream_id(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {26, UPB_SIZE(128, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_intermediate_log_entry(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {27, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_intermediate_log_entry(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {27, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_downstream_transport_failure_reason(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(136, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_AccessLogCommon_downstream_transport_failure_reason(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {28, UPB_SIZE(136, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_downstream_wire_bytes_sent(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(152, 280), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_AccessLogCommon_downstream_wire_bytes_sent(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {29, UPB_SIZE(152, 280), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_downstream_wire_bytes_received(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {30, UPB_SIZE(160, 288), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_AccessLogCommon_downstream_wire_bytes_received(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {30, UPB_SIZE(160, 288), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_wire_bytes_sent(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {31, UPB_SIZE(168, 296), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_AccessLogCommon_upstream_wire_bytes_sent(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {31, UPB_SIZE(168, 296), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_upstream_wire_bytes_received(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(176, 304), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_AccessLogCommon_upstream_wire_bytes_received(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {32, UPB_SIZE(176, 304), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_clear_access_log_type(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(92, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_data_accesslog_v3_AccessLogCommon_access_log_type(const envoy_data_accesslog_v3_AccessLogCommon* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {33, UPB_SIZE(92, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_sample_rate(envoy_data_accesslog_v3_AccessLogCommon *msg, double value) {
  const upb_MiniTableField field = {1, UPB_SIZE(144, 120), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_downstream_remote_address(envoy_data_accesslog_v3_AccessLogCommon *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 128), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_mutable_downstream_remote_address(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_data_accesslog_v3_AccessLogCommon_downstream_remote_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_downstream_remote_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_downstream_local_address(envoy_data_accesslog_v3_AccessLogCommon *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 136), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_mutable_downstream_local_address(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_data_accesslog_v3_AccessLogCommon_downstream_local_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_downstream_local_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_tls_properties(envoy_data_accesslog_v3_AccessLogCommon *msg, envoy_data_accesslog_v3_TLSProperties* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 144), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_TLSProperties* envoy_data_accesslog_v3_AccessLogCommon_mutable_tls_properties(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_TLSProperties* sub = (struct envoy_data_accesslog_v3_TLSProperties*)envoy_data_accesslog_v3_AccessLogCommon_tls_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_TLSProperties*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_tls_properties(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_start_time(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 152), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_data_accesslog_v3_AccessLogCommon_mutable_start_time(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_data_accesslog_v3_AccessLogCommon_start_time(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_start_time(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_rx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 160), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_last_rx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_last_rx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_rx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_first_upstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 168), 69, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_first_upstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_first_upstream_tx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_first_upstream_tx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_upstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(36, 176), 70, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_last_upstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_last_upstream_tx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_upstream_tx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_first_upstream_rx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(40, 184), 71, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_first_upstream_rx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_first_upstream_rx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_first_upstream_rx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_upstream_rx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(44, 192), 72, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_last_upstream_rx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_last_upstream_rx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_upstream_rx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_first_downstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(48, 200), 73, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_first_downstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_first_downstream_tx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_first_downstream_tx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_downstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(52, 208), 74, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_time_to_last_downstream_tx_byte(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_time_to_last_downstream_tx_byte(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_time_to_last_downstream_tx_byte(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_remote_address(envoy_data_accesslog_v3_AccessLogCommon *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(56, 216), 75, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_mutable_upstream_remote_address(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_data_accesslog_v3_AccessLogCommon_upstream_remote_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_upstream_remote_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_local_address(envoy_data_accesslog_v3_AccessLogCommon *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {14, UPB_SIZE(60, 224), 76, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_mutable_upstream_local_address(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_data_accesslog_v3_AccessLogCommon_upstream_local_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_upstream_local_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_cluster(envoy_data_accesslog_v3_AccessLogCommon *msg, upb_StringView value) {
  const upb_MiniTableField field = {15, UPB_SIZE(96, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_response_flags(envoy_data_accesslog_v3_AccessLogCommon *msg, envoy_data_accesslog_v3_ResponseFlags* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(64, 232), 77, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__ResponseFlags_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_ResponseFlags* envoy_data_accesslog_v3_AccessLogCommon_mutable_response_flags(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_ResponseFlags* sub = (struct envoy_data_accesslog_v3_ResponseFlags*)envoy_data_accesslog_v3_AccessLogCommon_response_flags(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_ResponseFlags*)_upb_Message_New(&envoy__data__accesslog__v3__ResponseFlags_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_response_flags(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_metadata(envoy_data_accesslog_v3_AccessLogCommon *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {17, UPB_SIZE(68, 240), 78, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_data_accesslog_v3_AccessLogCommon_mutable_metadata(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_data_accesslog_v3_AccessLogCommon_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_transport_failure_reason(envoy_data_accesslog_v3_AccessLogCommon *msg, upb_StringView value) {
  const upb_MiniTableField field = {18, UPB_SIZE(104, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_route_name(envoy_data_accesslog_v3_AccessLogCommon *msg, upb_StringView value) {
  const upb_MiniTableField field = {19, UPB_SIZE(112, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_downstream_direct_remote_address(envoy_data_accesslog_v3_AccessLogCommon *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(72, 248), 79, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_data_accesslog_v3_AccessLogCommon_mutable_downstream_direct_remote_address(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_data_accesslog_v3_AccessLogCommon_downstream_direct_remote_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_downstream_direct_remote_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_clear(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_set(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView key, struct google_protobuf_Any* val, upb_Arena* a) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__FilterStateObjectsEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_filter_state_objects_delete(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView key) {
  const upb_MiniTableField field = {21, UPB_SIZE(76, 256), 0, 16, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_custom_tags_clear(envoy_data_accesslog_v3_AccessLogCommon* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_custom_tags_set(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__AccessLogCommon__CustomTagsEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_data_accesslog_v3_AccessLogCommon_custom_tags_delete(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_StringView key) {
  const upb_MiniTableField field = {22, UPB_SIZE(80, 264), 0, 17, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_duration(envoy_data_accesslog_v3_AccessLogCommon *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {23, UPB_SIZE(84, 272), 80, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_data_accesslog_v3_AccessLogCommon_mutable_duration(envoy_data_accesslog_v3_AccessLogCommon* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_data_accesslog_v3_AccessLogCommon_duration(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_AccessLogCommon_set_duration(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_request_attempt_count(envoy_data_accesslog_v3_AccessLogCommon *msg, uint32_t value) {
  const upb_MiniTableField field = {24, UPB_SIZE(88, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_connection_termination_details(envoy_data_accesslog_v3_AccessLogCommon *msg, upb_StringView value) {
  const upb_MiniTableField field = {25, UPB_SIZE(120, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_stream_id(envoy_data_accesslog_v3_AccessLogCommon *msg, upb_StringView value) {
  const upb_MiniTableField field = {26, UPB_SIZE(128, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_intermediate_log_entry(envoy_data_accesslog_v3_AccessLogCommon *msg, bool value) {
  const upb_MiniTableField field = {27, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_downstream_transport_failure_reason(envoy_data_accesslog_v3_AccessLogCommon *msg, upb_StringView value) {
  const upb_MiniTableField field = {28, UPB_SIZE(136, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_downstream_wire_bytes_sent(envoy_data_accesslog_v3_AccessLogCommon *msg, uint64_t value) {
  const upb_MiniTableField field = {29, UPB_SIZE(152, 280), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_downstream_wire_bytes_received(envoy_data_accesslog_v3_AccessLogCommon *msg, uint64_t value) {
  const upb_MiniTableField field = {30, UPB_SIZE(160, 288), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_wire_bytes_sent(envoy_data_accesslog_v3_AccessLogCommon *msg, uint64_t value) {
  const upb_MiniTableField field = {31, UPB_SIZE(168, 296), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_upstream_wire_bytes_received(envoy_data_accesslog_v3_AccessLogCommon *msg, uint64_t value) {
  const upb_MiniTableField field = {32, UPB_SIZE(176, 304), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_AccessLogCommon_set_access_log_type(envoy_data_accesslog_v3_AccessLogCommon *msg, int32_t value) {
  const upb_MiniTableField field = {33, UPB_SIZE(92, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_ResponseFlags* envoy_data_accesslog_v3_ResponseFlags_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_ResponseFlags*)_upb_Message_New(&envoy__data__accesslog__v3__ResponseFlags_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_ResponseFlags* envoy_data_accesslog_v3_ResponseFlags_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_ResponseFlags* ret = envoy_data_accesslog_v3_ResponseFlags_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__ResponseFlags_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_ResponseFlags* envoy_data_accesslog_v3_ResponseFlags_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_ResponseFlags* ret = envoy_data_accesslog_v3_ResponseFlags_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__ResponseFlags_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_ResponseFlags_serialize(const envoy_data_accesslog_v3_ResponseFlags* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__ResponseFlags_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_ResponseFlags_serialize_ex(const envoy_data_accesslog_v3_ResponseFlags* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__ResponseFlags_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_failed_local_healthcheck(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_failed_local_healthcheck(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_no_healthy_upstream(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {2, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_no_healthy_upstream(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_request_timeout(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {3, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_request_timeout(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {3, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_local_reset(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {4, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_local_reset(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_remote_reset(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {5, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_remote_reset(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_connection_failure(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {6, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_connection_failure(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {6, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_connection_termination(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {7, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_connection_termination(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {7, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_overflow(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {8, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_overflow(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {8, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_no_route_found(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {9, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_no_route_found(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {9, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_delay_injected(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {10, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_delay_injected(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {10, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_fault_injected(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {11, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_fault_injected(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {11, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_rate_limited(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {12, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_rate_limited(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {12, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_unauthorized_details(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_ResponseFlags_Unauthorized* envoy_data_accesslog_v3_ResponseFlags_unauthorized_details(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  const envoy_data_accesslog_v3_ResponseFlags_Unauthorized* default_val = NULL;
  const envoy_data_accesslog_v3_ResponseFlags_Unauthorized* ret;
  const upb_MiniTableField field = {13, UPB_SIZE(36, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_has_unauthorized_details(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_rate_limit_service_error(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {14, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_rate_limit_service_error(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {14, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_downstream_connection_termination(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {15, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_downstream_connection_termination(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {15, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_retry_limit_exceeded(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {16, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_retry_limit_exceeded(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {16, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_stream_idle_timeout(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {17, 24, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_stream_idle_timeout(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {17, 24, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_invalid_envoy_request_headers(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {18, 25, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_invalid_envoy_request_headers(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {18, 25, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_downstream_protocol_error(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {19, 26, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_downstream_protocol_error(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {19, 26, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_max_stream_duration_reached(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {20, 27, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_max_stream_duration_reached(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {20, 27, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_response_from_cache_filter(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {21, 28, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_response_from_cache_filter(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {21, 28, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_no_filter_config_found(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {22, 29, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_no_filter_config_found(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {22, 29, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_duration_timeout(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {23, 30, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_duration_timeout(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {23, 30, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_upstream_protocol_error(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {24, 31, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_upstream_protocol_error(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {24, 31, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_no_cluster_found(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {25, 32, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_no_cluster_found(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {25, 32, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_overload_manager(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {26, 33, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_overload_manager(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {26, 33, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_dns_resolution_failure(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {27, 34, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_dns_resolution_failure(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {27, 34, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_clear_downstream_remote_reset(envoy_data_accesslog_v3_ResponseFlags* msg) {
  const upb_MiniTableField field = {28, 35, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_data_accesslog_v3_ResponseFlags_downstream_remote_reset(const envoy_data_accesslog_v3_ResponseFlags* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {28, 35, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_failed_local_healthcheck(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_no_healthy_upstream(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {2, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_request_timeout(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {3, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_local_reset(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {4, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_remote_reset(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {5, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_connection_failure(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {6, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_connection_termination(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {7, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_overflow(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {8, 16, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_no_route_found(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {9, 17, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_delay_injected(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {10, 18, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_fault_injected(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {11, 19, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_rate_limited(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {12, 20, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_unauthorized_details(envoy_data_accesslog_v3_ResponseFlags *msg, envoy_data_accesslog_v3_ResponseFlags_Unauthorized* value) {
  const upb_MiniTableField field = {13, UPB_SIZE(36, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_ResponseFlags_Unauthorized* envoy_data_accesslog_v3_ResponseFlags_mutable_unauthorized_details(envoy_data_accesslog_v3_ResponseFlags* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_ResponseFlags_Unauthorized* sub = (struct envoy_data_accesslog_v3_ResponseFlags_Unauthorized*)envoy_data_accesslog_v3_ResponseFlags_unauthorized_details(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_ResponseFlags_Unauthorized*)_upb_Message_New(&envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_ResponseFlags_set_unauthorized_details(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_rate_limit_service_error(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {14, 21, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_downstream_connection_termination(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {15, 22, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_retry_limit_exceeded(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {16, 23, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_stream_idle_timeout(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {17, 24, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_invalid_envoy_request_headers(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {18, 25, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_downstream_protocol_error(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {19, 26, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_max_stream_duration_reached(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {20, 27, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_response_from_cache_filter(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {21, 28, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_no_filter_config_found(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {22, 29, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_duration_timeout(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {23, 30, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_upstream_protocol_error(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {24, 31, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_no_cluster_found(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {25, 32, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_overload_manager(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {26, 33, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_dns_resolution_failure(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {27, 34, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_set_downstream_remote_reset(envoy_data_accesslog_v3_ResponseFlags *msg, bool value) {
  const upb_MiniTableField field = {28, 35, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

/* envoy.data.accesslog.v3.ResponseFlags.Unauthorized */

UPB_INLINE envoy_data_accesslog_v3_ResponseFlags_Unauthorized* envoy_data_accesslog_v3_ResponseFlags_Unauthorized_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_ResponseFlags_Unauthorized*)_upb_Message_New(&envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_ResponseFlags_Unauthorized* envoy_data_accesslog_v3_ResponseFlags_Unauthorized_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_ResponseFlags_Unauthorized* ret = envoy_data_accesslog_v3_ResponseFlags_Unauthorized_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_ResponseFlags_Unauthorized* envoy_data_accesslog_v3_ResponseFlags_Unauthorized_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_ResponseFlags_Unauthorized* ret = envoy_data_accesslog_v3_ResponseFlags_Unauthorized_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_ResponseFlags_Unauthorized_serialize(const envoy_data_accesslog_v3_ResponseFlags_Unauthorized* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_ResponseFlags_Unauthorized_serialize_ex(const envoy_data_accesslog_v3_ResponseFlags_Unauthorized* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__ResponseFlags__Unauthorized_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_Unauthorized_clear_reason(envoy_data_accesslog_v3_ResponseFlags_Unauthorized* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_data_accesslog_v3_ResponseFlags_Unauthorized_reason(const envoy_data_accesslog_v3_ResponseFlags_Unauthorized* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_ResponseFlags_Unauthorized_set_reason(envoy_data_accesslog_v3_ResponseFlags_Unauthorized *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_TLSProperties* envoy_data_accesslog_v3_TLSProperties_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_TLSProperties*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties* envoy_data_accesslog_v3_TLSProperties_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_TLSProperties* ret = envoy_data_accesslog_v3_TLSProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TLSProperties_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties* envoy_data_accesslog_v3_TLSProperties_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_TLSProperties* ret = envoy_data_accesslog_v3_TLSProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TLSProperties_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_TLSProperties_serialize(const envoy_data_accesslog_v3_TLSProperties* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_TLSProperties_serialize_ex(const envoy_data_accesslog_v3_TLSProperties* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_tls_version(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_data_accesslog_v3_TLSProperties_tls_version(const envoy_data_accesslog_v3_TLSProperties* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_tls_cipher_suite(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_data_accesslog_v3_TLSProperties_tls_cipher_suite(const envoy_data_accesslog_v3_TLSProperties* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TLSProperties_has_tls_cipher_suite(const envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_tls_sni_hostname(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_tls_sni_hostname(const envoy_data_accesslog_v3_TLSProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_local_certificate_properties(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_local_certificate_properties(const envoy_data_accesslog_v3_TLSProperties* msg) {
  const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* default_val = NULL;
  const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TLSProperties_has_local_certificate_properties(const envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_peer_certificate_properties(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_peer_certificate_properties(const envoy_data_accesslog_v3_TLSProperties* msg) {
  const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* default_val = NULL;
  const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TLSProperties_has_peer_certificate_properties(const envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_tls_session_id(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_tls_session_id(const envoy_data_accesslog_v3_TLSProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_clear_ja3_fingerprint(envoy_data_accesslog_v3_TLSProperties* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_ja3_fingerprint(const envoy_data_accesslog_v3_TLSProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_tls_version(envoy_data_accesslog_v3_TLSProperties *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_tls_cipher_suite(envoy_data_accesslog_v3_TLSProperties *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_data_accesslog_v3_TLSProperties_mutable_tls_cipher_suite(envoy_data_accesslog_v3_TLSProperties* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_data_accesslog_v3_TLSProperties_tls_cipher_suite(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_TLSProperties_set_tls_cipher_suite(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_tls_sni_hostname(envoy_data_accesslog_v3_TLSProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_local_certificate_properties(envoy_data_accesslog_v3_TLSProperties *msg, envoy_data_accesslog_v3_TLSProperties_CertificateProperties* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_mutable_local_certificate_properties(envoy_data_accesslog_v3_TLSProperties* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties* sub = (struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties*)envoy_data_accesslog_v3_TLSProperties_local_certificate_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_TLSProperties_set_local_certificate_properties(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_peer_certificate_properties(envoy_data_accesslog_v3_TLSProperties *msg, envoy_data_accesslog_v3_TLSProperties_CertificateProperties* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_mutable_peer_certificate_properties(envoy_data_accesslog_v3_TLSProperties* msg, upb_Arena* arena) {
  struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties* sub = (struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties*)envoy_data_accesslog_v3_TLSProperties_peer_certificate_properties(msg);
  if (sub == NULL) {
    sub = (struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_TLSProperties_set_peer_certificate_properties(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_tls_session_id(envoy_data_accesslog_v3_TLSProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_set_ja3_fingerprint(envoy_data_accesslog_v3_TLSProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_TLSProperties_CertificateProperties*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties* ret = envoy_data_accesslog_v3_TLSProperties_CertificateProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties* ret = envoy_data_accesslog_v3_TLSProperties_CertificateProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_serialize(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_serialize_ex(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_clear_subject_alt_name(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* const* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_subject_alt_name(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_data_accesslog_v3_TLSProperties_CertificateProperties_subject_alt_name_upb_array(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_data_accesslog_v3_TLSProperties_CertificateProperties_subject_alt_name_mutable_upb_array(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_clear_subject(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_CertificateProperties_subject(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_clear_issuer(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_CertificateProperties_issuer(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName** envoy_data_accesslog_v3_TLSProperties_CertificateProperties_mutable_subject_alt_name(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName** envoy_data_accesslog_v3_TLSProperties_CertificateProperties_resize_subject_alt_name(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_add_subject_alt_name(envoy_data_accesslog_v3_TLSProperties_CertificateProperties* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(8, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* sub = (struct envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_set_subject(envoy_data_accesslog_v3_TLSProperties_CertificateProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_set_issuer(envoy_data_accesslog_v3_TLSProperties_CertificateProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName*)_upb_Message_New(&envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* ret = envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* ret = envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_serialize(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_serialize_ex(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_uri = 1,
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_dns = 2,
  envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_NOT_SET = 0
} envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_oneofcases;
UPB_INLINE envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_oneofcases envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_case(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_san_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_clear_san(envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__data__accesslog__v3__TLSProperties__CertificateProperties__SubjectAltName_msg_init, &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_clear_uri(envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_uri(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_has_uri(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_clear_dns(envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_dns(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_has_dns(const envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_set_uri(envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName_set_dns(envoy_data_accesslog_v3_TLSProperties_CertificateProperties_SubjectAltName *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_HTTPRequestProperties* envoy_data_accesslog_v3_HTTPRequestProperties_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_HTTPRequestProperties*)_upb_Message_New(&envoy__data__accesslog__v3__HTTPRequestProperties_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_HTTPRequestProperties* envoy_data_accesslog_v3_HTTPRequestProperties_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_HTTPRequestProperties* ret = envoy_data_accesslog_v3_HTTPRequestProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_HTTPRequestProperties* envoy_data_accesslog_v3_HTTPRequestProperties_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_HTTPRequestProperties* ret = envoy_data_accesslog_v3_HTTPRequestProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_HTTPRequestProperties_serialize(const envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_HTTPRequestProperties_serialize_ex(const envoy_data_accesslog_v3_HTTPRequestProperties* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__HTTPRequestProperties_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_request_method(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_data_accesslog_v3_HTTPRequestProperties_request_method(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_scheme(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_scheme(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_authority(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_authority(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_port(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_data_accesslog_v3_HTTPRequestProperties_port(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPRequestProperties_has_port(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_path(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_path(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_user_agent(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_user_agent(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_referer(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_referer(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_forwarded_for(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(64, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_forwarded_for(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(64, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_request_id(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(72, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_request_id(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(72, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_original_path(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(80, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPRequestProperties_original_path(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {10, UPB_SIZE(80, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_request_headers_bytes(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(88, 152), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_bytes(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {11, UPB_SIZE(88, 152), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_request_body_bytes(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(96, 160), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPRequestProperties_request_body_bytes(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {12, UPB_SIZE(96, 160), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_request_headers(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_size(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_get(const envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_next(const envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_upb_map(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_mutable_upb_map(envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_Arena* a) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_upstream_header_bytes_sent(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(104, 176), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPRequestProperties_upstream_header_bytes_sent(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {14, UPB_SIZE(104, 176), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_clear_downstream_header_bytes_received(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(112, 184), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPRequestProperties_downstream_header_bytes_received(const envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {15, UPB_SIZE(112, 184), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_request_method(envoy_data_accesslog_v3_HTTPRequestProperties *msg, int32_t value) {
  const upb_MiniTableField field = {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_scheme(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_authority(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_port(envoy_data_accesslog_v3_HTTPRequestProperties *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_data_accesslog_v3_HTTPRequestProperties_mutable_port(envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_data_accesslog_v3_HTTPRequestProperties_port(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_HTTPRequestProperties_set_port(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_path(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {5, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_user_agent(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_referer(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(56, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_forwarded_for(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(64, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_request_id(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(72, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_original_path(envoy_data_accesslog_v3_HTTPRequestProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {10, UPB_SIZE(80, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_request_headers_bytes(envoy_data_accesslog_v3_HTTPRequestProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {11, UPB_SIZE(88, 152), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_request_body_bytes(envoy_data_accesslog_v3_HTTPRequestProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {12, UPB_SIZE(96, 160), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_clear(envoy_data_accesslog_v3_HTTPRequestProperties* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_set(envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPRequestProperties__RequestHeadersEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPRequestProperties_request_headers_delete(envoy_data_accesslog_v3_HTTPRequestProperties* msg, upb_StringView key) {
  const upb_MiniTableField field = {13, UPB_SIZE(20, 168), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_upstream_header_bytes_sent(envoy_data_accesslog_v3_HTTPRequestProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {14, UPB_SIZE(104, 176), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPRequestProperties_set_downstream_header_bytes_received(envoy_data_accesslog_v3_HTTPRequestProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {15, UPB_SIZE(112, 184), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_data_accesslog_v3_HTTPResponseProperties* envoy_data_accesslog_v3_HTTPResponseProperties_new(upb_Arena* arena) {
  return (envoy_data_accesslog_v3_HTTPResponseProperties*)_upb_Message_New(&envoy__data__accesslog__v3__HTTPResponseProperties_msg_init, arena);
}
UPB_INLINE envoy_data_accesslog_v3_HTTPResponseProperties* envoy_data_accesslog_v3_HTTPResponseProperties_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_data_accesslog_v3_HTTPResponseProperties* ret = envoy_data_accesslog_v3_HTTPResponseProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_data_accesslog_v3_HTTPResponseProperties* envoy_data_accesslog_v3_HTTPResponseProperties_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_data_accesslog_v3_HTTPResponseProperties* ret = envoy_data_accesslog_v3_HTTPResponseProperties_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_data_accesslog_v3_HTTPResponseProperties_serialize(const envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_data_accesslog_v3_HTTPResponseProperties_serialize_ex(const envoy_data_accesslog_v3_HTTPResponseProperties* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__data__accesslog__v3__HTTPResponseProperties_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_response_code(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_data_accesslog_v3_HTTPResponseProperties_response_code(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_has_response_code(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_response_headers_bytes(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_bytes(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_response_body_bytes(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 48), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPResponseProperties_response_body_bytes(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 48), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_response_headers(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_size(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_get(const envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_next(const envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_upb_map(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_mutable_upb_map(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_response_trailers(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_size(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_get(const envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_next(const envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_upb_map(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_mutable_upb_map(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_response_code_details(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_data_accesslog_v3_HTTPResponseProperties_response_code_details(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_upstream_header_bytes_received(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(48, 72), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPResponseProperties_upstream_header_bytes_received(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {7, UPB_SIZE(48, 72), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_clear_downstream_header_bytes_sent(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(56, 80), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_data_accesslog_v3_HTTPResponseProperties_downstream_header_bytes_sent(const envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {8, UPB_SIZE(56, 80), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_set_response_code(envoy_data_accesslog_v3_HTTPResponseProperties *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_data_accesslog_v3_HTTPResponseProperties_mutable_response_code(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_data_accesslog_v3_HTTPResponseProperties_response_code(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_data_accesslog_v3_HTTPResponseProperties_set_response_code(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_set_response_headers_bytes(envoy_data_accesslog_v3_HTTPResponseProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 40), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_set_response_body_bytes(envoy_data_accesslog_v3_HTTPResponseProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 48), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_clear(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_set(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseHeadersEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_headers_delete(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView key) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_clear(envoy_data_accesslog_v3_HTTPResponseProperties* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_set(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__data__accesslog__v3__HTTPResponseProperties__ResponseTrailersEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_data_accesslog_v3_HTTPResponseProperties_response_trailers_delete(envoy_data_accesslog_v3_HTTPResponseProperties* msg, upb_StringView key) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_set_response_code_details(envoy_data_accesslog_v3_HTTPResponseProperties *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_set_upstream_header_bytes_received(envoy_data_accesslog_v3_HTTPResponseProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {7, UPB_SIZE(48, 72), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_data_accesslog_v3_HTTPResponseProperties_set_downstream_header_bytes_sent(envoy_data_accesslog_v3_HTTPResponseProperties *msg, uint64_t value) {
  const upb_MiniTableField field = {8, UPB_SIZE(56, 80), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
