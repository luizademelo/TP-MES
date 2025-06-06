
#ifndef ENVOY_CONFIG_TRACE_V3_XRAY_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_TRACE_V3_XRAY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/xray.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_trace_v3_XRayConfig { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_XRayConfig;
typedef struct envoy_config_trace_v3_XRayConfig_SegmentFields { upb_Message UPB_PRIVATE(base); } envoy_config_trace_v3_XRayConfig_SegmentFields;
struct envoy_config_core_v3_DataSource;
struct envoy_config_core_v3_SocketAddress;
struct google_protobuf_Struct;

UPB_INLINE envoy_config_trace_v3_XRayConfig* envoy_config_trace_v3_XRayConfig_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_XRayConfig*)_upb_Message_New(&envoy__config__trace__v3__XRayConfig_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_XRayConfig* envoy_config_trace_v3_XRayConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_XRayConfig* ret = envoy_config_trace_v3_XRayConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__XRayConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_XRayConfig* envoy_config_trace_v3_XRayConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_XRayConfig* ret = envoy_config_trace_v3_XRayConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__XRayConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_XRayConfig_serialize(const envoy_config_trace_v3_XRayConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__XRayConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_XRayConfig_serialize_ex(const envoy_config_trace_v3_XRayConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__XRayConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_clear_daemon_endpoint(envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SocketAddress* envoy_config_trace_v3_XRayConfig_daemon_endpoint(const envoy_config_trace_v3_XRayConfig* msg) {
  const struct envoy_config_core_v3_SocketAddress* default_val = NULL;
  const struct envoy_config_core_v3_SocketAddress* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketAddress_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_XRayConfig_has_daemon_endpoint(const envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_clear_segment_name(envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_XRayConfig_segment_name(const envoy_config_trace_v3_XRayConfig* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_clear_sampling_rule_manifest(envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_DataSource* envoy_config_trace_v3_XRayConfig_sampling_rule_manifest(const envoy_config_trace_v3_XRayConfig* msg) {
  const struct envoy_config_core_v3_DataSource* default_val = NULL;
  const struct envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_XRayConfig_has_sampling_rule_manifest(const envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_clear_segment_fields(envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_trace_v3_XRayConfig_SegmentFields* envoy_config_trace_v3_XRayConfig_segment_fields(const envoy_config_trace_v3_XRayConfig* msg) {
  const envoy_config_trace_v3_XRayConfig_SegmentFields* default_val = NULL;
  const envoy_config_trace_v3_XRayConfig_SegmentFields* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_XRayConfig_has_segment_fields(const envoy_config_trace_v3_XRayConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_XRayConfig_set_daemon_endpoint(envoy_config_trace_v3_XRayConfig *msg, struct envoy_config_core_v3_SocketAddress* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketAddress_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_SocketAddress* envoy_config_trace_v3_XRayConfig_mutable_daemon_endpoint(envoy_config_trace_v3_XRayConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_SocketAddress* sub = (struct envoy_config_core_v3_SocketAddress*)envoy_config_trace_v3_XRayConfig_daemon_endpoint(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_SocketAddress*)_upb_Message_New(&envoy__config__core__v3__SocketAddress_msg_init, arena);
    if (sub) envoy_config_trace_v3_XRayConfig_set_daemon_endpoint(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_set_segment_name(envoy_config_trace_v3_XRayConfig *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_set_sampling_rule_manifest(envoy_config_trace_v3_XRayConfig *msg, struct envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_trace_v3_XRayConfig_mutable_sampling_rule_manifest(envoy_config_trace_v3_XRayConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_trace_v3_XRayConfig_sampling_rule_manifest(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_trace_v3_XRayConfig_set_sampling_rule_manifest(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_set_segment_fields(envoy_config_trace_v3_XRayConfig *msg, envoy_config_trace_v3_XRayConfig_SegmentFields* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_trace_v3_XRayConfig_SegmentFields* envoy_config_trace_v3_XRayConfig_mutable_segment_fields(envoy_config_trace_v3_XRayConfig* msg, upb_Arena* arena) {
  struct envoy_config_trace_v3_XRayConfig_SegmentFields* sub = (struct envoy_config_trace_v3_XRayConfig_SegmentFields*)envoy_config_trace_v3_XRayConfig_segment_fields(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_trace_v3_XRayConfig_SegmentFields*)_upb_Message_New(&envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init, arena);
    if (sub) envoy_config_trace_v3_XRayConfig_set_segment_fields(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_trace_v3_XRayConfig_SegmentFields* envoy_config_trace_v3_XRayConfig_SegmentFields_new(upb_Arena* arena) {
  return (envoy_config_trace_v3_XRayConfig_SegmentFields*)_upb_Message_New(&envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init, arena);
}
UPB_INLINE envoy_config_trace_v3_XRayConfig_SegmentFields* envoy_config_trace_v3_XRayConfig_SegmentFields_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_trace_v3_XRayConfig_SegmentFields* ret = envoy_config_trace_v3_XRayConfig_SegmentFields_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_trace_v3_XRayConfig_SegmentFields* envoy_config_trace_v3_XRayConfig_SegmentFields_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_trace_v3_XRayConfig_SegmentFields* ret = envoy_config_trace_v3_XRayConfig_SegmentFields_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_trace_v3_XRayConfig_SegmentFields_serialize(const envoy_config_trace_v3_XRayConfig_SegmentFields* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_trace_v3_XRayConfig_SegmentFields_serialize_ex(const envoy_config_trace_v3_XRayConfig_SegmentFields* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_SegmentFields_clear_origin(envoy_config_trace_v3_XRayConfig_SegmentFields* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_trace_v3_XRayConfig_SegmentFields_origin(const envoy_config_trace_v3_XRayConfig_SegmentFields* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_SegmentFields_clear_aws(envoy_config_trace_v3_XRayConfig_SegmentFields* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_trace_v3_XRayConfig_SegmentFields_aws(const envoy_config_trace_v3_XRayConfig_SegmentFields* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_trace_v3_XRayConfig_SegmentFields_has_aws(const envoy_config_trace_v3_XRayConfig_SegmentFields* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_trace_v3_XRayConfig_SegmentFields_set_origin(envoy_config_trace_v3_XRayConfig_SegmentFields *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_trace_v3_XRayConfig_SegmentFields_set_aws(envoy_config_trace_v3_XRayConfig_SegmentFields *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_trace_v3_XRayConfig_SegmentFields_mutable_aws(envoy_config_trace_v3_XRayConfig_SegmentFields* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_trace_v3_XRayConfig_SegmentFields_aws(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_trace_v3_XRayConfig_SegmentFields_set_aws(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
